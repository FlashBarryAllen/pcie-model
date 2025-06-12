#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <pthread.h>
#include <errno.h>

#define SOCKET_PATH "/tmp/pcie_cosim_socket"
#define BUFFER_SIZE 1024

void *handle_client(void *arg) {
    int client_sock = *(int*)arg;
    char buffer[BUFFER_SIZE];
    free(arg);

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        ssize_t bytes_received = recv(client_sock, buffer, BUFFER_SIZE - 1, 0);
        
        if (bytes_received <= 0) {
            if (bytes_received < 0) {
                perror("接收数据失败");
            }
            printf("客户端断开连接\n");
            break;
        }
        
        printf("收到消息(%zd 字节): %s\n", bytes_received, buffer);
        
        // 发送响应
        char response[BUFFER_SIZE];
        snprintf(response, BUFFER_SIZE, "服务器已收到 %zd 字节: %s", bytes_received, buffer);
        ssize_t bytes_sent = send(client_sock, response, strlen(response), 0);
        
        if (bytes_sent < 0) {
            perror("发送响应失败");
            break;
        }
    }
    
    close(client_sock);
    return NULL;
}

int main() {
    int server_sock;
    struct sockaddr_un server_addr;
    
    // 创建Unix域socket
    if ((server_sock = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        perror("创建socket失败");
        exit(EXIT_FAILURE);
    }
    
    // 删除已存在的socket文件
    if (unlink(SOCKET_PATH) < 0 && errno != ENOENT) {
        perror("删除旧的socket文件失败");
        exit(EXIT_FAILURE);
    }
    
    // 配置服务器地址
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);
    
    // 绑定socket
    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("绑定socket失败");
        exit(EXIT_FAILURE);
    }
    
    // 设置socket文件权限
    if (chmod(SOCKET_PATH, 0666) < 0) {
        perror("设置socket文件权限失败");
        exit(EXIT_FAILURE);
    }
    
    // 监听连接
    if (listen(server_sock, 5) < 0) {
        perror("监听失败");
        exit(EXIT_FAILURE);
    }
    
    printf("Unix域socket服务器启动成功\n");
    printf("Socket路径: %s\n", SOCKET_PATH);
    
    while (1) {
        struct sockaddr_un client_addr;
        socklen_t client_len = sizeof(client_addr);
        
        int *client_sock = malloc(sizeof(int));
        *client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_len);
        
        if (*client_sock < 0) {
            perror("接受连接失败");
            free(client_sock);
            continue;
        }
        
        printf("新客户端连接成功\n");
        
        // 创建新线程处理客户端连接
        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, handle_client, client_sock) < 0) {
            perror("创建线程失败");
            close(*client_sock);
            free(client_sock);
            continue;
        }
        pthread_detach(thread_id);
    }
    
    close(server_sock);
    unlink(SOCKET_PATH);
    return 0;
}

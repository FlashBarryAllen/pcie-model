#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>

#define SOCKET_PATH "/tmp/pcie_cosim_socket"
#define BUFFER_SIZE 1024

int main() {
    int sock;
    struct sockaddr_un server_addr;
    char buffer[BUFFER_SIZE];
    
    // 创建Unix域socket
    if ((sock = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        perror("创建socket失败");
        exit(EXIT_FAILURE);
    }
    
    // 配置服务器地址
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);
    
    // 连接到服务器
    printf("正在连接到服务器...\n");
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("连接服务器失败");
        exit(EXIT_FAILURE);
    }
    
    printf("已连接到Unix域socket服务器\n");
    printf("Socket路径: %s\n", SOCKET_PATH);
    
    while (1) {
        printf("\n请输入消息 (输入 'quit' 退出): ");
        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            break;
        }
        
        // 移除换行符
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') {
            buffer[len-1] = '\0';
            len--;
        }
        
        if (strcmp(buffer, "quit") == 0) {
            printf("正在退出...\n");
            break;
        }
        
        // 发送消息
        ssize_t bytes_sent = send(sock, buffer, len, 0);
        if (bytes_sent < 0) {
            perror("发送消息失败");
            break;
        }
        
        // 接收服务器响应
        memset(buffer, 0, BUFFER_SIZE);
        ssize_t bytes_received = recv(sock, buffer, BUFFER_SIZE - 1, 0);
        
        if (bytes_received < 0) {
            perror("接收响应失败");
            break;
        } else if (bytes_received == 0) {
            printf("服务器关闭了连接\n");
            break;
        }
        
        printf("服务器响应: %s\n", buffer);
    }
    
    close(sock);
    return 0;
}

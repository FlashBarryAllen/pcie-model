#ifndef PCIE_CFG_H
#define PCIE_CFG_H

#include <cstdint>
#include <vector>
#include <cstring>
#include <iostream>
#include <string>


struct PCIeType0Header {
    uint16_t vendorID;
    uint16_t deviceID;
    uint16_t command;
    uint16_t status;
    uint8_t revisionID;
    uint8_t baseClass;
    uint8_t subClass;
    uint8_t progIf;
    uint8_t bist;
    uint8_t headerType;
    uint8_t latencyTimer;
    uint8_t cacheLineSize;
    uint32_t baseAddress0;
    uint32_t baseAddress1;
    uint32_t baseAddress2;
    uint32_t baseAddress3;
    uint32_t baseAddress4;
    uint32_t baseAddress5;
    uint32_t cardbusCisPointer;
    uint16_t subsystemVendorID;
    uint16_t subsystemID;
    uint32_t expansionRomBaseAddress;
    uint8_t capabilitiesPointer;
    uint8_t interruptLine;
    uint8_t interruptPin;
    uint8_t minGnt;
    uint8_t maxLat;
};

struct PCIeBarCfg {
    uint32_t bar_flags;
	uint32_t io_bar_flags;
};

struct PCIeMsixCfg {
    uint32_t table_size;
    uint32_t table_bir;
	uint32_t table_offset;
	uint32_t pba;
};

struct PCIeFuncCfg {
    struct PCIeType0Header header;
    struct PCIeBarCfg bars;
    struct PCIeMsixCfg msix;
};

PCIeFuncCfg getpfcfgfromxml(const char* xml_file);

#endif // PCIE_CFG_H
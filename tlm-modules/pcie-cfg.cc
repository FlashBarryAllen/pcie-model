#include <iostream>
#include <string>
#include "tinyxml2.h"
#include "pcie-cfg.h"

using namespace std;
using namespace tinyxml2;

PCIeFuncCfg getpfcfgfromxml(const char* xml_file)
{
    PCIeFuncCfg cfg = {};

    XMLDocument doc;
    doc.LoadFile(xml_file);

    XMLElement* root = doc.FirstChildElement("cfg_hdr_spc");
    XMLElement* hdrElement = root->FirstChildElement("hdr");

    hdrElement->QueryAttribute("vendor_id", (int*)&cfg.header.vendorID);
    cout << "Vendor ID: 0x" << hex << cfg.header.vendorID << dec << endl;

    hdrElement->QueryAttribute("device_id", (int*)&cfg.header.deviceID);
    cout << "Device ID: 0x" << hex << cfg.header.deviceID << dec << endl;

    hdrElement->QueryAttribute("command", (int*)&cfg.header.command);
    cout << "Command: 0x" << hex << cfg.header.command << dec << endl;

    hdrElement->QueryAttribute("status", (int*)&cfg.header.status);
    cout << "Status: 0x" << hex << cfg.header.status << dec << endl;

    hdrElement->QueryAttribute("revision_id", (int*)&cfg.header.revisionID);
    cout << "Revision ID: 0x" << hex << static_cast<int>(cfg.header.revisionID) << dec << endl;

    hdrElement->QueryAttribute("base_class", (int*)&cfg.header.baseClass);
    cout << "Base Class: 0x" << hex << static_cast<int>(cfg.header.baseClass) << dec << endl;

    hdrElement->QueryAttribute("sub_class", (int*)&cfg.header.subClass);
    cout << "Sub Class: 0x" << hex << static_cast<int>(cfg.header.subClass) << dec << endl;

    hdrElement->QueryAttribute("prog_if", (int*)&cfg.header.progIf);
    cout << "Programming Interface: 0x" << hex << static_cast<int>(cfg.header.progIf) << dec << endl;

    hdrElement->QueryAttribute("bist", (int*)&cfg.header.bist);
    cout << "BIST: 0x" << hex << static_cast<int>(cfg.header.bist) << dec << endl;

    hdrElement->QueryAttribute("header_type", (int*)&cfg.header.headerType);
    cout << "Header Type: 0x" << hex << static_cast<int>(cfg.header.headerType) << dec << endl;

    hdrElement->QueryAttribute("latency_timer", (int*)&cfg.header.latencyTimer);
    cout << "Latency Timer: 0x" << hex << static_cast<int>(cfg.header.latencyTimer) << dec << endl;

    hdrElement->QueryAttribute("cache_line_size", (int*)&cfg.header.cacheLineSize);
    cout << "Cache Line Size: 0x" << hex << static_cast<int>(cfg.header.cacheLineSize) << dec << endl;

    hdrElement->QueryAttribute("base_address_0", (int*)&cfg.header.baseAddress0);
    cout << "Base Address 0: 0x" << hex << cfg.header.baseAddress0 << dec << endl;

    hdrElement->QueryAttribute("base_address_1", (int*)&cfg.header.baseAddress1);
    cout << "Base Address 1: 0x" << hex << cfg.header.baseAddress1 << dec << endl;

    hdrElement->QueryAttribute("base_address_2", (int*)&cfg.header.baseAddress2);
    cout << "Base Address 2: 0x" << hex << cfg.header.baseAddress2 << dec << endl;

    hdrElement->QueryAttribute("base_address_3", (int*)&cfg.header.baseAddress3);
    cout << "Base Address 3: 0x" << hex << cfg.header.baseAddress3 << dec << endl;

    hdrElement->QueryAttribute("base_address_4", (int*)&cfg.header.baseAddress4);
    cout << "Base Address 4: 0x" << hex << cfg.header.baseAddress4 << dec << endl;

    hdrElement->QueryAttribute("base_address_5", (int*)&cfg.header.baseAddress5);
    cout << "Base Address 5: 0x" << hex << cfg.header.baseAddress5 << dec << endl;

    hdrElement->QueryAttribute("cardbus_cis_pointer", (int*)&cfg.header.cardbusCisPointer);
    cout << "Cardbus CIS Pointer: 0x" << hex << cfg.header.cardbusCisPointer << dec << endl;

    hdrElement->QueryAttribute("subsystem_vendor_id", (int*)&cfg.header.subsystemVendorID);
    cout << "Subsystem Vendor ID: 0x" << hex << cfg.header.subsystemVendorID << dec << endl;

    hdrElement->QueryAttribute("subsystem_id", (int*)&cfg.header.subsystemID);
    cout << "Subsystem ID: 0x" << hex << cfg.header.subsystemID << dec << endl;

    hdrElement->QueryAttribute("expansion_rom_base_address", (int*)&cfg.header.expansionRomBaseAddress);
    cout << "Expansion ROM Base Address: 0x" << hex << cfg.header.expansionRomBaseAddress << dec << endl;

    hdrElement->QueryAttribute("capabilities_pointer", (int*)&cfg.header.capabilitiesPointer);
    cout << "Capabilities Pointer: 0x" << hex << static_cast<int>(cfg.header.capabilitiesPointer) << dec << endl;

    hdrElement->QueryAttribute("interrupt_line", (int*)&cfg.header.interruptLine);
    cout << "Interrupt Line: 0x" << hex << static_cast<int>(cfg.header.interruptLine) << dec << endl;

    hdrElement->QueryAttribute("interrupt_pin", (int*)&cfg.header.interruptPin);
    cout << "Interrupt Pin: 0x" << hex << static_cast<int>(cfg.header.interruptPin) << dec << endl;

    hdrElement->QueryAttribute("min_gnt", (int*)&cfg.header.minGnt);
    cout << "Min Gnt: 0x" << hex << static_cast<int>(cfg.header.minGnt) << dec << endl;

    hdrElement->QueryAttribute("max_lat", (int*)&cfg.header.maxLat);
    cout << "Max Lat: 0x" << hex << static_cast<int>(cfg.header.maxLat) << dec << endl;

    XMLElement* barElement = hdrElement->NextSiblingElement("bar");
    barElement->QueryAttribute("bar_flags", (int*)&cfg.bars.bar_flags);
    cout << "Bar Flags: 0x" << hex << static_cast<int>(cfg.bars.bar_flags) << dec << endl;

    XMLElement* msixElement = barElement->NextSiblingElement("msix");
    msixElement->QueryAttribute("table_size", (int*)&cfg.msix.table_size);
    cout << "MSI-X Table Size: 0x" << hex << static_cast<int>(cfg.msix.table_size) << dec << endl;
    msixElement->QueryAttribute("table_offset", (int*)&cfg.msix.table_offset);
    cout << "MSI-X Table Offset: 0x" << hex << static_cast<int>(cfg.msix.table_offset) << dec << endl;
    msixElement->QueryAttribute("pba", (int*)&cfg.msix.pba);
    cout << "MSI-X PBA: 0x" << hex << static_cast<int>(cfg.msix.pba) << dec << endl;

    return cfg;
}
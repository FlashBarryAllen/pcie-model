#include <iostream>
#include <string>
#include "tinyxml2.h"
#include "pcie-cfg.h"

using namespace std;
using namespace tinyxml2;

PCIeType0Header getpfcfgfromxml(const char* xml_file)
{
    PCIeType0Header header = {};

    XMLDocument doc;
    doc.LoadFile(xml_file);

    XMLElement* root = doc.FirstChildElement("cfg_hdr_spc");
    XMLElement* hdrElement = root->FirstChildElement("hdr");

    hdrElement->QueryAttribute("vendor_id", (int*)&header.vendorID);
    cout << "Vendor ID: 0x" << hex << header.vendorID << dec << endl;

    hdrElement->QueryAttribute("device_id", (int*)&header.deviceID);
    cout << "Device ID: 0x" << hex << header.deviceID << dec << endl;

    hdrElement->QueryAttribute("command", (int*)&header.command);
    cout << "Command: 0x" << hex << header.command << dec << endl;

    hdrElement->QueryAttribute("status", (int*)&header.status);
    cout << "Status: 0x" << hex << header.status << dec << endl;

    hdrElement->QueryAttribute("revision_id", (int*)&header.revisionID);
    cout << "Revision ID: 0x" << hex << static_cast<int>(header.revisionID) << dec << endl;

    hdrElement->QueryAttribute("base_class", (int*)&header.baseClass);
    cout << "Base Class: 0x" << hex << static_cast<int>(header.baseClass) << dec << endl;

    hdrElement->QueryAttribute("sub_class", (int*)&header.subClass);
    cout << "Sub Class: 0x" << hex << static_cast<int>(header.subClass) << dec << endl;

    hdrElement->QueryAttribute("prog_if", (int*)&header.progIf);
    cout << "Programming Interface: 0x" << hex << static_cast<int>(header.progIf) << dec << endl;

    hdrElement->QueryAttribute("bist", (int*)&header.bist);
    cout << "BIST: 0x" << hex << static_cast<int>(header.bist) << dec << endl;

    hdrElement->QueryAttribute("header_type", (int*)&header.headerType);
    cout << "Header Type: 0x" << hex << static_cast<int>(header.headerType) << dec << endl;

    hdrElement->QueryAttribute("latency_timer", (int*)&header.latencyTimer);
    cout << "Latency Timer: 0x" << hex << static_cast<int>(header.latencyTimer) << dec << endl;

    hdrElement->QueryAttribute("cache_line_size", (int*)&header.cacheLineSize);
    cout << "Cache Line Size: 0x" << hex << static_cast<int>(header.cacheLineSize) << dec << endl;

    hdrElement->QueryAttribute("base_address_0", (int*)&header.baseAddress0);
    cout << "Base Address 0: 0x" << hex << header.baseAddress0 << dec << endl;

    hdrElement->QueryAttribute("base_address_1", (int*)&header.baseAddress1);
    cout << "Base Address 1: 0x" << hex << header.baseAddress1 << dec << endl;

    hdrElement->QueryAttribute("base_address_2", (int*)&header.baseAddress2);
    cout << "Base Address 2: 0x" << hex << header.baseAddress2 << dec << endl;

    hdrElement->QueryAttribute("base_address_3", (int*)&header.baseAddress3);
    cout << "Base Address 3: 0x" << hex << header.baseAddress3 << dec << endl;

    hdrElement->QueryAttribute("base_address_4", (int*)&header.baseAddress4);
    cout << "Base Address 4: 0x" << hex << header.baseAddress4 << dec << endl;

    hdrElement->QueryAttribute("base_address_5", (int*)&header.baseAddress5);
    cout << "Base Address 5: 0x" << hex << header.baseAddress5 << dec << endl;

    hdrElement->QueryAttribute("cardbus_cis_pointer", (int*)&header.cardbusCisPointer);
    cout << "Cardbus CIS Pointer: 0x" << hex << header.cardbusCisPointer << dec << endl;

    hdrElement->QueryAttribute("subsystem_vendor_id", (int*)&header.subsystemVendorID);
    cout << "Subsystem Vendor ID: 0x" << hex << header.subsystemVendorID << dec << endl;

    hdrElement->QueryAttribute("subsystem_id", (int*)&header.subsystemID);
    cout << "Subsystem ID: 0x" << hex << header.subsystemID << dec << endl;

    hdrElement->QueryAttribute("expansion_rom_base_address", (int*)&header.expansionRomBaseAddress);
    cout << "Expansion ROM Base Address: 0x" << hex << header.expansionRomBaseAddress << dec << endl;

    hdrElement->QueryAttribute("capabilities_pointer", (int*)&header.capabilitiesPointer);
    cout << "Capabilities Pointer: 0x" << hex << static_cast<int>(header.capabilitiesPointer) << dec << endl;

    hdrElement->QueryAttribute("interrupt_line", (int*)&header.interruptLine);
    cout << "Interrupt Line: 0x" << hex << static_cast<int>(header.interruptLine) << dec << endl;

    hdrElement->QueryAttribute("interrupt_pin", (int*)&header.interruptPin);
    cout << "Interrupt Pin: 0x" << hex << static_cast<int>(header.interruptPin) << dec << endl;

    hdrElement->QueryAttribute("min_gnt", (int*)&header.minGnt);
    cout << "Min Gnt: 0x" << hex << static_cast<int>(header.minGnt) << dec << endl;

    hdrElement->QueryAttribute("max_lat", (int*)&header.maxLat);
    cout << "Max Lat: 0x" << hex << static_cast<int>(header.maxLat) << dec << endl;

    return header;
}
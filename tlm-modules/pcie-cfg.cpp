#include "pcie-cfg.h"

#include <iostream>
#include "tinyxml2.h"
#include <string>

//using namespace tinyxml2;
using namespace std;

PCIeType0Header getpfcfgfromxml(const char* xml_file)
{
	PCIeType0Header header;
    XMLDocument doc;
    XMLError error = doc.LoadFile(xml_file);

    if (error != XML_SUCCESS) {
        cerr << "Error loading XML file: " << doc.ErrorStr() << endl;
        return 1;
    }

    XMLNode* root = doc.FirstChildElement("cfg_hdr_spc");
    if (root == nullptr) {
        cerr << "Error: Root element 'cfg_hdr_spc' not found." << endl;
        return 1;
    }

    XMLElement* vendorIdElement = root->FirstChildElement("vendor_id");
    if (vendorIdElement) {
        cout << "Vendor ID: " << vendorIdElement->GetText() << endl;
    }

    XMLElement* deviceIdElement = root->FirstChildElement("device_id");
    if (deviceIdElement) {
        cout << "Device ID: " << deviceIdElement->GetText() << endl;
    }

    XMLElement* subsystemIdElement = root->FirstChildElement("subsystem_id");
    if (subsystemIdElement) {
        cout << "Subsystem ID: " << subsystemIdElement->GetText() << endl;
    }

    XMLElement* subsystemVendorIdElement = root->FirstChildElement("subsystem_vendor_id");
    if (subsystemVendorIdElement) {
        cout << "Subsystem Vendor ID: " << subsystemVendorIdElement->GetText() << endl;
    }

    XMLElement* classCodeElement = root->FirstChildElement("class_code");
    if (classCodeElement) {
        cout << "Class Code: " << classCodeElement->GetText() << endl;
    }

    XMLElement* revisionIdElement = root->FirstChildElement("revision_id");
    if (revisionIdElement) {
        cout << "Revision ID: " << revisionIdElement->GetText() << endl;
    }

    XMLElement* progIfElement = root->FirstChildElement("prog_if");
    if (progIfElement) {
        cout << "Programming Interface: " << progIfElement->GetText() << endl;
    }

    XMLElement* subclassCodeElement = root->FirstChildElement("subclass_code");
    if (subclassCodeElement) {
        cout << "Subclass Code: " << subclassCodeElement->GetText() << endl;
    }

    XMLElement* headerTypeElement = root->FirstChildElement("header_type");
    if (headerTypeElement) {
        cout << "Header Type: " << headerTypeElement->GetText() << endl;
    }

    XMLElement* bistElement = root->FirstChildElement("bist");
    if (bistElement) {
        cout << "BIST: " << bistElement->GetText() << endl;
    }

    XMLElement* latencyTimerElement = root->FirstChildElement("latency_timer");
    if (latencyTimerElement) {
        cout << "Latency Timer: " << latencyTimerElement->GetText() << endl;
    }

    XMLElement* cacheLineSizeElement = root->FirstChildElement("cache_line_size");
    if (cacheLineSizeElement) {
        cout << "Cache Line Size: " << cacheLineSizeElement->GetText() << endl;
    }

    XMLElement* maxLatElement = root->FirstChildElement("max_lat");
    if (maxLatElement) {
        cout << "Max Lat: " << maxLatElement->GetText() << endl;
    }

    XMLElement* minGntElement = root->FirstChildElement("min_gnt");
    if (minGntElement) {
        cout << "Min Gnt: " << minGntElement->GetText() << endl;
    }

    // 注意：您的 XML 中 "max_lat" 出现了两次，这里会读取到第一个
    // 如果您希望读取第二个，您可能需要使用 NextSiblingElement("max_lat")
    XMLElement* maxLatElement2 = root->FirstChildElement("max_lat");
    if (maxLatElement2 && maxLatElement2->NextSiblingElement("max_lat")) {
        cout << "Max Lat (Second): " << maxLatElement2->NextSiblingElement("max_lat")->GetText() << endl;
    }

    return header;
}
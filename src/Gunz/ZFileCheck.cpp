#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <sstream>


uint32_t crc32(const std::vector<uint8_t>& data) {
    uint32_t crc = 0xFFFFFFFF;
    for (auto byte : data) {
        crc = crc ^ byte;
        for (int j = 0; j < 8; j++) {
            crc = (crc >> 1) ^ ((crc & 1) ? 0xEDB88320 : 0);
        }
    }
    return ~crc;
}

std::vector<uint8_t> readFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
    }
    return std::vector<uint8_t>((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

std::string ZItemCRC32() {
    try {
        std::string filename = "/system/zitem.xml";
        auto data = readFile(filename);
        uint32_t crc = crc32(data);

        std::stringstream ss; // Declare stringstream object
        ss << std::hex << crc; // Use stringstream to convert crc to hex string
        return ss.str();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return "";
    }
}
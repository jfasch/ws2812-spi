#pragma once

#include <string>
#include <vector>
#include <cstdint>


class SPIDevice
{
public:
    SPIDevice(const std::string& path);
    ~SPIDevice();
    void write_bitstream(const std::vector<uint8_t>& bits);

private:
    int _fd;
};

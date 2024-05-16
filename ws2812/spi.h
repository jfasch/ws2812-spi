#pragma once

#include "ws2812_strip.h"

#include <string>
#include <vector>
#include <cstdint>


class SPIDevice
{
public:
    SPIDevice(const std::string& path);
    ~SPIDevice();

    void write(const WS2812Strip&);

public:
    SPIDevice(const SPIDevice&) = delete;
    SPIDevice& operator=(const SPIDevice&) = delete;

private:
    int _fd;
};

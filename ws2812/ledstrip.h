#pragma once

#include "grb.h"

#include <vector>
#include <cstddef>


using SPIBit = std::bitset<5>;
static const SPIBit SPI_B0 = 0b11000;
static const SPIBit SPI_B1 = 0b11100;

class LEDStrip
{
public:
    LEDStrip(std::size_t n) : _grbs(n) {}

    const GRB& operator[](std::size_t i) const { return _grbs[i]; }
    GRB& operator[](std::size_t i) { return _grbs[i]; }

    void create_spi_bits(std::vector<SPIBit>&) const;

private:
    std::vector<GRB> _grbs;
};

std::vector<uint8_t> spibits_to_bitstream(const std::vector<SPIBit>&);

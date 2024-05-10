#pragma once

#include "grb.h"

#include <vector>
#include <cstddef>


class LEDStrip
{
public:
    LEDStrip(std::size_t n) : _grbs(n) {}

    const GRB& operator[](std::size_t i) const { return _grbs[i]; }
    GRB& operator[](std::size_t i) { return _grbs[i]; }

    std::vector<bool> create_logical_bitstream() const;

private:
    std::vector<GRB> _grbs;
};

std::vector<uint8_t> logical_to_spi(const std::vector<bool>&, uint8_t low, uint8_t high);

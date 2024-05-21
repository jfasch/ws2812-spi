#pragma once

#include <algorithm>
#include <cstdint>
#include <bitset>


class GRB
{
public:
    GRB()
    : _g(0), _r(0), _b(0) {}
    GRB(uint8_t g, uint8_t r, uint8_t b)
    : _g(g), _r(r), _b(b) {}

    uint8_t g() const { return _g; }
    uint8_t r() const { return _r; }
    uint8_t b() const { return _b; }

    bool operator==(const GRB& rhs) const
    {
        return _g == rhs._g && _r == rhs._r && _b == rhs._b;
    }

private:
    uint8_t _g;
    uint8_t _r;
    uint8_t _b;
};

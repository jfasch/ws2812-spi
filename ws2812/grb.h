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

    bool operator==(const GRB& rhs) const
    {
        return _g == rhs._g && _r == rhs._r && _b == rhs._b;
    }

    std::bitset<24> bits() const
    {
        std::bitset<8> g(_g), r(_r), b(_b);
        std::bitset<24> ret;
        
        int dstidx = 0;
        for (int i=7; i>=0; --i)
            ret[dstidx++] = g[i];
        for (int i=7; i>=0; --i)
            ret[dstidx++] = r[i];
        for (int i=7; i>=0; --i)
            ret[dstidx++] = b[i];

        return ret;
    }

private:
    uint8_t _g;
    uint8_t _r;
    uint8_t _b;
};

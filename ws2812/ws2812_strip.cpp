#include "ws2812_strip.h"

#include <bitset>

// todo jjj
#include <iostream>
using namespace std;


const WS2812Strip::Profile WS2812Strip::RASPBERRY = { 17000000, 50, 0b11111110, 0b11100000 };

WS2812Strip::WS2812Strip(std::size_t n, Profile p)
: _mem(n*24 + p.n_zero_bytes),
  _profile(p) 
{
    for (size_t i=0; i<n*24; i++)
        _mem[i] = _profile.ZERO;
}

GRB WS2812Strip::get(size_t pos) const
{ 
    size_t off = pos * 24;

    std::bitset<8> g, r, b;

    for (int i=7; i>=0; i--)
        if (_mem[off++] == _profile.ONE)
            g[i] = true;
        else
            g[i] = false;
    for (int i=7; i>=0; i--)
        if (_mem[off++] == _profile.ONE)
            r[i] = true;
        else
            r[i] = false;
    for (int i=7; i>=0; i--)
        if (_mem[off++] == _profile.ONE)
            b[i] = true;
        else
            b[i] = false;

    return GRB(g.to_ulong(), r.to_ulong(), b.to_ulong());
}

void WS2812Strip::set(size_t pos, const GRB& grb)
{
    size_t off = pos * 24;

    std::bitset<8> g = grb.g();
    for (int i=7; i>=0; i--)
        if (g[i])
            _mem[off++] = _profile.ONE;
        else
            _mem[off++] = _profile.ZERO;

    std::bitset<8> r = grb.r();
    for (int i=7; i>=0; i--)
        if (r[i])
            _mem[off++] = _profile.ONE;
        else
            _mem[off++] = _profile.ZERO;

    std::bitset<8> b = grb.b();
    for (int i=7; i>=0; i--)
        if (b[i])
            _mem[off++] = _profile.ONE;
        else
            _mem[off++] = _profile.ZERO;
}

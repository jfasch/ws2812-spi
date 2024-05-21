#include "ws2812_strip.h"


const WS2812Strip::Profile WS2812Strip::RASPBERRY = { 17000000, 50, 0b11111110, 0b11100000 };

WS2812Strip::WS2812Strip(std::size_t n, Profile p)
: _mem(n*24 + p.n_zero_bytes),
  _profile(p) 
{
    for (size_t i=0; i<n*24; i++)
        _mem[i] = _profile.ZERO;
}

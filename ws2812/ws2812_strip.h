#pragma once

#include "grb.h"

#include <vector>
#include <cstddef>


class WS2812Strip
{
public:
    struct Profile
    {
        const uint32_t frequency_hz;
        const uint32_t n_zero_bytes;
        const uint8_t ONE;
        const uint8_t ZERO;
    };

    static const Profile RASPBERRY;

public:
    WS2812Strip(std::size_t n, Profile p);

    GRB get(size_t pos) const
    { 
        auto offp = &_mem[pos*24];

        uint8_t g{}, r{}, b{};

        for (int i=7; i>=0; i--)
            if (*offp++ == _profile.ONE)
                g |= 1<<i;
            else
                g &= ~(1<<i);
        for (int i=7; i>=0; i--)
            if (*offp++ == _profile.ONE)
                r |= 1<<i;
            else
                r &= ~(1<<i);
        for (int i=7; i>=0; i--)
            if (*offp++ == _profile.ONE)
                b |= 1<<i;
            else
                b &= ~(1<<i);

        return GRB(g, r, b);
    }

    void set(size_t pos, const GRB& grb)
    {
        auto offp = &_mem[pos*24];

        for (int i=7; i>=0; i--)
            if (grb.g() & (1<<i))
                *offp++ = _profile.ONE;
            else
                *offp++ = _profile.ZERO;

        for (int i=7; i>=0; i--)
            if (grb.r() & (1<<i))
                *offp++ = _profile.ONE;
            else
                *offp++ = _profile.ZERO;

        for (int i=7; i>=0; i--)
            if (grb.b() & (1<<i))
                *offp++ = _profile.ONE;
            else
                *offp++ = _profile.ZERO;
    }


    const std::vector<uint8_t>& mem() const { return _mem; }
    const Profile& profile() const { return _profile; }

private:
    std::vector<uint8_t> _mem;
    Profile _profile;
};

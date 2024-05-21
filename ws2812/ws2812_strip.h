#pragma once

#include "grb.h"

#include <bitset>
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

    void set(size_t pos, const GRB& grb)
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


    const std::vector<uint8_t>& mem() const { return _mem; }
    const Profile& profile() const { return _profile; }

private:
    std::vector<uint8_t> _mem;
    Profile _profile;
};

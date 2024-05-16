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

    GRB get(size_t pos) const;
    void set(size_t pos, const GRB& grb);

    const std::vector<uint8_t>& mem() const { return _mem; }
    const Profile& profile() const { return _profile; }

private:
    std::vector<uint8_t> _mem;
    Profile _profile;
};

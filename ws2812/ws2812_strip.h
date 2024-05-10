#pragma once

#include "grb.h"

#include <vector>
#include <cstddef>


class WS2812Strip
{
public:
    struct Profile
    {
        const int frequency_hz;
        const uint8_t ONE;
        const uint8_t ZERO;
    };

    static constexpr Profile RASPBERRY = { 17000000, 0b11100000, 0b11111110 };
    static constexpr Profile INVALID = { 0, 0, 0 };   // todo: remove

    class GRBRef
    {
    public:
        GRBRef(std::vector<uint8_t>& mem, size_t pos)
        : _mem(mem), _pos(pos) {}

        const std::vector<uint8_t>& mem() const { return _mem; }
        size_t pos() const { return _pos; }

        bool operator==(const GRBRef& rhs) const { return
                _mem[_pos] == rhs._mem[_pos] &&
                _mem[_pos+1] == rhs._mem[_pos+1] &&
                _mem[_pos+2] == rhs._mem[_pos+2];
        }
        bool operator!=(const GRBRef& rhs) const { return !operator==(rhs); }

        bool operator==(const GRB& rhs) const { return
                _mem[_pos] == rhs.g() &&
                _mem[_pos+1] == rhs.r() &&
                _mem[_pos+2] == rhs.b();
        }
        bool operator!=(const GRB& rhs) const { return !operator==(rhs); }

        GRBRef& operator=(const GRB& rhs)
        {
            _mem[_pos] = rhs.g();
            _mem[_pos+1] = rhs.r();
            _mem[_pos+2] = rhs.b();
            return *this;
        }

    private:
        std::vector<uint8_t>& _mem;
        size_t _pos;
    };

    class GRBConstRef
    {
    public:
        GRBConstRef(const std::vector<uint8_t>& mem, size_t pos)
        : _mem(mem), _pos(pos) {}
        GRBConstRef(const GRBRef& grb)
        : _mem(grb.mem()), _pos(grb.pos()) {}

        bool operator==(const GRBConstRef& rhs) const { return
                _mem[_pos] == rhs._mem[_pos] &&
                _mem[_pos+1] == rhs._mem[_pos+1] &&
                _mem[_pos+2] == rhs._mem[_pos+2];
        }
        bool operator!=(const GRBConstRef& rhs) const { return !operator==(rhs); }

        bool operator==(const GRB& rhs) const { return
                _mem[_pos] == rhs.g() &&
                _mem[_pos+1] == rhs.r() &&
                _mem[_pos+2] == rhs.b();
        }
        bool operator!=(const GRB& rhs) const { return !operator==(rhs); }

        std::bitset<24> bits() const
        {
            std::bitset<8> g(_mem[_pos]), r(_mem[_pos+1]), b(_mem[_pos+2]);
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
        const std::vector<uint8_t>& _mem;
        size_t _pos;
    };

public:
    WS2812Strip(std::size_t n) : _grbs(n), _profile(INVALID) {}
    WS2812Strip(std::size_t n, Profile p);

    GRBRef operator[](std::size_t i) { return GRBRef(_mem, i); }
    GRBConstRef operator[](std::size_t i) const { return GRBConstRef(_mem, i); }

    const std::vector<uint8_t>& mem() const { return _mem; }


    std::vector<bool> create_logical_bitstream() const;

private:
    std::vector<GRB> _grbs; // todo: remove

    std::vector<uint8_t> _mem;
    Profile _profile;
};

std::vector<uint8_t> logical_to_spi(const std::vector<bool>&, uint8_t low, uint8_t high);

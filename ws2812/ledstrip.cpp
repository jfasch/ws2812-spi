#include "ledstrip.h"

#include <iostream>
using namespace std;


std::vector<bool> LEDStrip::create_logical_bitstream() const
{
    std::vector<bool> logical_bitstream;

    for (auto grb: _grbs) {
        auto bits = grb.bits();
        for (size_t i=0; i<bits.size(); i++) {
            auto bit = bits[i];
            if (bit)
                logical_bitstream.push_back(true);
            else
                logical_bitstream.push_back(false);
        }
    }

    return logical_bitstream;
}

std::vector<uint8_t> logical_to_spi(
    const std::vector<bool>& logical_bits, 
    uint8_t low, uint8_t high)
{
    std::vector<uint8_t> spi_bitstream;

    // uint8_t byte = 0;
    // int byte_pos = 7;
    for (auto logical_bit: logical_bits) {
        // std::bitset<5> bit = logical_bit? HIGH: LOW;

        // for (int i=4; i>=0; i--) {
        //     if (bit[i])
        //         byte |= (1<<byte_pos);
        //     byte_pos--;
        //     if (byte_pos == -1) {
        //         spi_bitstream.push_back(byte);
        //         byte = 0;
        //         byte_pos = 7;
        //     }
        // }

        if (logical_bit)
            spi_bitstream.push_back(high);
        else
            spi_bitstream.push_back(low);
    }

    // terminate bitstream ("reset", as per datasheet, >50us)
    for (int i=0; i<20; i++)
        spi_bitstream.push_back(0);

    return spi_bitstream;
}

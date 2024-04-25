#include "ledstrip.h"

#include <iostream>
using namespace std;


void LEDStrip::create_spi_bits(std::vector<SPIBit>& spi_bits) const
{
    for (auto grb: _grbs) {
        auto bits = grb.bits();
        for (size_t i=0; i<bits.size(); i++) {
            auto bit = bits[i];
            if (bit)
                spi_bits.push_back(SPI_B1);
            else
                spi_bits.push_back(SPI_B0);
        }
    }
}

std::vector<uint8_t> spibits_to_bitstream(const std::vector<SPIBit>& spi_bits)
{
    std::vector<uint8_t> bitstream;

    uint8_t byte = 0;
    int byte_pos = 7;
    for (auto spi_bit: spi_bits) {
        for (int i=4; i>=0; i--) {
            if (spi_bit[i])
                byte |= (1<<byte_pos);
            byte_pos--;
            if (byte_pos == -1) {
                bitstream.push_back(byte);
                byte = 0;
                byte_pos = 7;
            }
        }
    }

    // terminate bitstream ("reset", as per datasheet). this adds 8
    // bits which is more than 5.
    bitstream.push_back(0);

    return bitstream;
}

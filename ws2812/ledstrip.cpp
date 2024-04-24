#include "ledstrip.h"


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

std::vector<uint8_t> spi_bits_to_bitstream(const std::vector<SPIBit>& spi_bits)
{
    size_t nbytes = spi_bits.size() * 5 / 8;
    nbytes += 1; // for termination/reset

    // hier gschieht ein wunder

    return std::vector<uint8_t>(nbytes);
}

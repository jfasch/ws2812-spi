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

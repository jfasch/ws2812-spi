#include <spi.h>
#include <ledstrip.h>


int main(int argc, char** argv)
{
    SPIDevice spidev(argv[1]);

    LEDStrip led_strip(2);
    led_strip[0] = GRB(1, 2, 3);
    led_strip[1] = GRB(3, 4, 5);

    std::vector<SPIBit> spi_bits;
    led_strip.create_spi_bits(spi_bits);

    std::vector<uint8_t> bitstream = spibits_to_bitstream(spi_bits);

    spidev.write_bitstream(bitstream);

    return 0;
}

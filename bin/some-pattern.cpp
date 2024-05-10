#include <spi.h>
#include <ledstrip.h>


int main(int argc, char** argv)
{
    SPIDevice spidev(argv[1]);

    LEDStrip led_strip(9);
    // led_strip[0] = GRB(1, 2, 3);
    // led_strip[1] = GRB(3, 4, 5);

    // led_strip[0] = GRB(0, 0, 255);
    // led_strip[1] = GRB(0, 255, 0);
    // led_strip[2] = GRB(255, 0, 0);

    led_strip[ 0] = GRB(255, 0, 0);
    led_strip[ 1] = GRB(0, 255, 0);
    led_strip[ 2] = GRB(0, 0, 255);
    led_strip[ 3] = GRB(255, 0, 0);
    led_strip[ 4] = GRB(0, 255, 0);
    led_strip[ 5] = GRB(0, 0, 255);
    led_strip[ 6] = GRB(255, 0, 0);
    led_strip[ 7] = GRB(0, 255, 0);
    led_strip[ 8] = GRB(0, 0, 255);
    led_strip[ 9] = GRB(255, 0, 0);
    led_strip[10] = GRB(0, 255, 0);
    led_strip[11] = GRB(0, 0, 255);

    std::vector<bool> logical_bitstream = led_strip.create_logical_bitstream();
    std::vector<uint8_t> spi_bitstream = logical_to_spi(logical_bitstream, 0b11100000, 0b11111110);

    spidev.write_bitstream(spi_bitstream);

    return 0;
}

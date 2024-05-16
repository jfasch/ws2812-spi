#include <ws2812_strip.h>
#include <spi.h>

#include <iostream>
#include <thread>
#include <chrono>
using namespace std::chrono_literals;


int main(int argc, char** argv)
{
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << "<SPI-device> <#LEDs> <frequency(Hz)>\n";
        return 1;
    }

    SPIDevice spi(argv[1]);

    size_t n_leds = std::stoul(argv[2]);
    WS2812Strip leds(n_leds, WS2812Strip::RASPBERRY);

    size_t interval_ms = std::stoul(argv[3]);

    size_t pos = 0;
    while (true) {
        std::cout << pos << '\n';
        for (size_t i=0; i<n_leds; i++)
            leds.set(i, GRB(0,0,0));
        leds.set(pos, GRB(255,0,0));

        spi.write(leds);

        std::this_thread::sleep_for(std::chrono::duration<long double, std::milli>(interval_ms));
        pos++;
        pos %= n_leds;
    }

    return 0;
}

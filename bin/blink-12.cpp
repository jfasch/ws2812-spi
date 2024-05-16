#include <ws2812_strip.h>
#include <spi.h>

#include <thread>
#include <chrono>
using namespace std::chrono_literals;


int main(int argc, char** argv)
{
    SPIDevice spidev(argv[1]);

    WS2812Strip led_strip(12, WS2812Strip::RASPBERRY);
    while (true) {
        led_strip.set( 0, GRB(255, 0, 0));
        led_strip.set( 1, GRB(0, 255, 0));
        led_strip.set( 2, GRB(0, 0, 255));
        led_strip.set( 3, GRB(255, 0, 0));
        led_strip.set( 4, GRB(0, 255, 0));
        led_strip.set( 5, GRB(0, 0, 255));
        led_strip.set( 6, GRB(255, 0, 0));
        led_strip.set( 7, GRB(0, 255, 0));
        led_strip.set( 8, GRB(0, 0, 255));
        led_strip.set( 9, GRB(255, 0, 0));
        led_strip.set(10, GRB(0, 255, 0));
        led_strip.set(11, GRB(0, 0, 255));

        spidev.write(led_strip);
        std::this_thread::sleep_for(1s);

        led_strip.set( 0, GRB(50, 50, 50));
        led_strip.set( 1, GRB(50, 50, 50));
        led_strip.set( 2, GRB(50, 50, 50));
        led_strip.set( 3, GRB(50, 50, 50));
        led_strip.set( 4, GRB(50, 50, 50));
        led_strip.set( 5, GRB(50, 50, 50));
        led_strip.set( 6, GRB(50, 50, 50));
        led_strip.set( 7, GRB(50, 50, 50));
        led_strip.set( 8, GRB(50, 50, 50));
        led_strip.set( 9, GRB(50, 50, 50));
        led_strip.set(10, GRB(50, 50, 50));
        led_strip.set(11, GRB(50, 50, 50));

        spidev.write(led_strip);
        std::this_thread::sleep_for(1s);

        led_strip.set( 0, GRB(0, 0, 255));
        led_strip.set( 1, GRB(0, 255, 0));
        led_strip.set( 2, GRB(255, 0, 0));
        led_strip.set( 3, GRB(0, 0, 255));
        led_strip.set( 4, GRB(0, 255, 0));
        led_strip.set( 5, GRB(255, 0, 0));
        led_strip.set( 6, GRB(0, 0, 255));
        led_strip.set( 7, GRB(0, 255, 0));
        led_strip.set( 8, GRB(255, 0, 0));
        led_strip.set( 9, GRB(0, 0, 255));
        led_strip.set(10, GRB(0, 255, 0));
        led_strip.set(11, GRB(255, 0, 0));

        spidev.write(led_strip);
    }

    return 0;
}

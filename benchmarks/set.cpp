#include <ws2812_strip.h>


int main(int argc, char** argv)
{
    WS2812Strip led_strip(10000, WS2812Strip::RASPBERRY);
    uint8_t g = 1, r = 2, b = 3;
    for (size_t i=0; i<10000; i++)
        led_strip.set(i, GRB(g++, r++, b++));
    return 0;
}

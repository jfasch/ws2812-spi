#include <ws2812_strip.h>

#include <gtest/gtest.h>
#include <bitset>


TEST(ws2812_strip, default_value)
{
    const WS2812Strip led_strip(2);

    ASSERT_EQ(led_strip[0], GRB());
    ASSERT_EQ(led_strip[1], GRB());

    ASSERT_EQ(led_strip[0].bits(), std::bitset<24>());
    ASSERT_EQ(led_strip[1].bits(), std::bitset<24>());
}

TEST(ws2812_strip, set_values)
{
    WS2812Strip led_strip(2);
    led_strip[0] = GRB(1, 2, 3);
    ASSERT_EQ(led_strip[0], GRB(1, 2, 3));

    led_strip[1] = GRB(3, 4, 5);
    ASSERT_EQ(led_strip[1], GRB(3, 4, 5));
}

TEST(ws2812_strip, create_logical_bitstream)
{
    WS2812Strip led_strip(2);
    led_strip[0] = GRB(1, 2, 3);
    led_strip[1] = GRB(3, 4, 5);

    std::vector<bool> logical_bits = led_strip.create_logical_bitstream();

    // [0]

    // g/1
    ASSERT_EQ(logical_bits[ 0], false);
    ASSERT_EQ(logical_bits[ 1], false);
    ASSERT_EQ(logical_bits[ 2], false);
    ASSERT_EQ(logical_bits[ 3], false);
    ASSERT_EQ(logical_bits[ 4], false);
    ASSERT_EQ(logical_bits[ 5], false);
    ASSERT_EQ(logical_bits[ 6], false);
    ASSERT_EQ(logical_bits[ 7], true);

    // r/2
    ASSERT_EQ(logical_bits[ 8], false);
    ASSERT_EQ(logical_bits[ 9], false);
    ASSERT_EQ(logical_bits[10], false);
    ASSERT_EQ(logical_bits[11], false);
    ASSERT_EQ(logical_bits[12], false);
    ASSERT_EQ(logical_bits[13], false);
    ASSERT_EQ(logical_bits[14], true);
    ASSERT_EQ(logical_bits[15], false);

    // b/3
    ASSERT_EQ(logical_bits[16], false);
    ASSERT_EQ(logical_bits[17], false);
    ASSERT_EQ(logical_bits[18], false);
    ASSERT_EQ(logical_bits[19], false);
    ASSERT_EQ(logical_bits[20], false);
    ASSERT_EQ(logical_bits[21], false);
    ASSERT_EQ(logical_bits[22], true);
    ASSERT_EQ(logical_bits[23], true);


    // [1]

    // g/3
    ASSERT_EQ(logical_bits[24], false);
    ASSERT_EQ(logical_bits[25], false);
    ASSERT_EQ(logical_bits[26], false);
    ASSERT_EQ(logical_bits[27], false);
    ASSERT_EQ(logical_bits[28], false);
    ASSERT_EQ(logical_bits[29], false);
    ASSERT_EQ(logical_bits[30], true);
    ASSERT_EQ(logical_bits[31], true);

    // r/4
    ASSERT_EQ(logical_bits[32], false);
    ASSERT_EQ(logical_bits[33], false);
    ASSERT_EQ(logical_bits[34], false);
    ASSERT_EQ(logical_bits[35], false);
    ASSERT_EQ(logical_bits[36], false);
    ASSERT_EQ(logical_bits[37], true);
    ASSERT_EQ(logical_bits[38], false);
    ASSERT_EQ(logical_bits[39], false);

    // b/5
    ASSERT_EQ(logical_bits[40], false);
    ASSERT_EQ(logical_bits[41], false);
    ASSERT_EQ(logical_bits[42], false);
    ASSERT_EQ(logical_bits[43], false);
    ASSERT_EQ(logical_bits[44], false);
    ASSERT_EQ(logical_bits[45], true);
    ASSERT_EQ(logical_bits[46], false);
    ASSERT_EQ(logical_bits[47], true);
}

TEST(ws2812_strip, bitstream)
{
    WS2812Strip led_strip(2);
    led_strip[0] = GRB(1, 2, 3);
    led_strip[1] = GRB(3, 4, 5);

    std::vector<bool> logical_bits = led_strip.create_logical_bitstream();
    std::vector<uint8_t> spi_bits = logical_to_spi(logical_bits, 0b11100000, 0b11111110);

    ASSERT_EQ(spi_bits.size(), 68);

    // [0]

    // g/1
    ASSERT_EQ(spi_bits[ 0], 0b11100000);
    ASSERT_EQ(spi_bits[ 1], 0b11100000);
    ASSERT_EQ(spi_bits[ 2], 0b11100000);
    ASSERT_EQ(spi_bits[ 3], 0b11100000);
    ASSERT_EQ(spi_bits[ 4], 0b11100000);
    ASSERT_EQ(spi_bits[ 5], 0b11100000);
    ASSERT_EQ(spi_bits[ 6], 0b11100000);
    ASSERT_EQ(spi_bits[ 7], 0b11111110);

    // r/2
    ASSERT_EQ(spi_bits[ 8], 0b11100000);
    ASSERT_EQ(spi_bits[ 9], 0b11100000);
    ASSERT_EQ(spi_bits[10], 0b11100000);
    ASSERT_EQ(spi_bits[11], 0b11100000);
    ASSERT_EQ(spi_bits[12], 0b11100000);
    ASSERT_EQ(spi_bits[13], 0b11100000);
    ASSERT_EQ(spi_bits[14], 0b11111110);
    ASSERT_EQ(spi_bits[15], 0b11100000);

    // b/3
    ASSERT_EQ(spi_bits[16], 0b11100000);
    ASSERT_EQ(spi_bits[17], 0b11100000);
    ASSERT_EQ(spi_bits[18], 0b11100000);
    ASSERT_EQ(spi_bits[19], 0b11100000);
    ASSERT_EQ(spi_bits[20], 0b11100000);
    ASSERT_EQ(spi_bits[21], 0b11100000);
    ASSERT_EQ(spi_bits[22], 0b11111110);
    ASSERT_EQ(spi_bits[23], 0b11111110);


    // [1]

    // g/3
    ASSERT_EQ(spi_bits[24], 0b11100000);
    ASSERT_EQ(spi_bits[25], 0b11100000);
    ASSERT_EQ(spi_bits[26], 0b11100000);
    ASSERT_EQ(spi_bits[27], 0b11100000);
    ASSERT_EQ(spi_bits[28], 0b11100000);
    ASSERT_EQ(spi_bits[29], 0b11100000);
    ASSERT_EQ(spi_bits[30], 0b11111110);
    ASSERT_EQ(spi_bits[31], 0b11111110);

    // r/4
    ASSERT_EQ(spi_bits[32], 0b11100000);
    ASSERT_EQ(spi_bits[33], 0b11100000);
    ASSERT_EQ(spi_bits[34], 0b11100000);
    ASSERT_EQ(spi_bits[35], 0b11100000);
    ASSERT_EQ(spi_bits[36], 0b11100000);
    ASSERT_EQ(spi_bits[37], 0b11111110);
    ASSERT_EQ(spi_bits[38], 0b11100000);
    ASSERT_EQ(spi_bits[39], 0b11100000);

    // b/5
    ASSERT_EQ(spi_bits[40], 0b11100000);
    ASSERT_EQ(spi_bits[41], 0b11100000);
    ASSERT_EQ(spi_bits[42], 0b11100000);
    ASSERT_EQ(spi_bits[43], 0b11100000);
    ASSERT_EQ(spi_bits[44], 0b11100000);
    ASSERT_EQ(spi_bits[45], 0b11111110);
    ASSERT_EQ(spi_bits[46], 0b11100000);
    ASSERT_EQ(spi_bits[47], 0b11111110);

    // termination ("reset", as in datasheet)
    ASSERT_EQ(spi_bits[48], 0b00000000);
    ASSERT_EQ(spi_bits[49], 0b00000000);
    ASSERT_EQ(spi_bits[50], 0b00000000);
    ASSERT_EQ(spi_bits[51], 0b00000000);
    ASSERT_EQ(spi_bits[52], 0b00000000);
    ASSERT_EQ(spi_bits[53], 0b00000000);
    ASSERT_EQ(spi_bits[54], 0b00000000);
    ASSERT_EQ(spi_bits[55], 0b00000000);
    ASSERT_EQ(spi_bits[56], 0b00000000);
    ASSERT_EQ(spi_bits[57], 0b00000000);
    ASSERT_EQ(spi_bits[58], 0b00000000);
    ASSERT_EQ(spi_bits[59], 0b00000000);
    ASSERT_EQ(spi_bits[60], 0b00000000);
    ASSERT_EQ(spi_bits[61], 0b00000000);
    ASSERT_EQ(spi_bits[62], 0b00000000);
    ASSERT_EQ(spi_bits[63], 0b00000000);
    ASSERT_EQ(spi_bits[64], 0b00000000);
    ASSERT_EQ(spi_bits[65], 0b00000000);
    ASSERT_EQ(spi_bits[66], 0b00000000);
    ASSERT_EQ(spi_bits[67], 0b00000000);
}

TEST(ws2812_strip, bitstream_builtin_raspberry)
{
    WS2812Strip led_strip(2, WS2812Strip::RASPBERRY);

    ASSERT_EQ(led_strip.mem().size(), 2/*n LEDS*/ * 3/*GRB/LED*/ * 8  + 20/*0-bytes for reset*/);
    ASSERT_EQ(led_strip[0], GRB(0,0,0));
    ASSERT_EQ(led_strip[1], GRB(0,0,0));

    led_strip[0] = GRB(1, 2, 3);
    led_strip[1] = GRB(3, 4, 5);

    // [0]

    // g/1
    ASSERT_EQ(led_strip.mem()[ 0], 0b11100000);
    ASSERT_EQ(led_strip.mem()[ 1], 0b11100000);
    ASSERT_EQ(led_strip.mem()[ 2], 0b11100000);
    ASSERT_EQ(led_strip.mem()[ 3], 0b11100000);
    ASSERT_EQ(led_strip.mem()[ 4], 0b11100000);
    ASSERT_EQ(led_strip.mem()[ 5], 0b11100000);
    ASSERT_EQ(led_strip.mem()[ 6], 0b11100000);
    ASSERT_EQ(led_strip.mem()[ 7], 0b11111110);

    // r/2
    ASSERT_EQ(led_strip.mem()[ 8], 0b11100000);
    ASSERT_EQ(led_strip.mem()[ 9], 0b11100000);
    ASSERT_EQ(led_strip.mem()[10], 0b11100000);
    ASSERT_EQ(led_strip.mem()[11], 0b11100000);
    ASSERT_EQ(led_strip.mem()[12], 0b11100000);
    ASSERT_EQ(led_strip.mem()[13], 0b11100000);
    ASSERT_EQ(led_strip.mem()[14], 0b11111110);
    ASSERT_EQ(led_strip.mem()[15], 0b11100000);

    // b/3
    ASSERT_EQ(led_strip.mem()[16], 0b11100000);
    ASSERT_EQ(led_strip.mem()[17], 0b11100000);
    ASSERT_EQ(led_strip.mem()[18], 0b11100000);
    ASSERT_EQ(led_strip.mem()[19], 0b11100000);
    ASSERT_EQ(led_strip.mem()[20], 0b11100000);
    ASSERT_EQ(led_strip.mem()[21], 0b11100000);
    ASSERT_EQ(led_strip.mem()[22], 0b11111110);
    ASSERT_EQ(led_strip.mem()[23], 0b11111110);


    // [1]

    // g/3
    ASSERT_EQ(led_strip.mem()[24], 0b11100000);
    ASSERT_EQ(led_strip.mem()[25], 0b11100000);
    ASSERT_EQ(led_strip.mem()[26], 0b11100000);
    ASSERT_EQ(led_strip.mem()[27], 0b11100000);
    ASSERT_EQ(led_strip.mem()[28], 0b11100000);
    ASSERT_EQ(led_strip.mem()[29], 0b11100000);
    ASSERT_EQ(led_strip.mem()[30], 0b11111110);
    ASSERT_EQ(led_strip.mem()[31], 0b11111110);

    // r/4
    ASSERT_EQ(led_strip.mem()[32], 0b11100000);
    ASSERT_EQ(led_strip.mem()[33], 0b11100000);
    ASSERT_EQ(led_strip.mem()[34], 0b11100000);
    ASSERT_EQ(led_strip.mem()[35], 0b11100000);
    ASSERT_EQ(led_strip.mem()[36], 0b11100000);
    ASSERT_EQ(led_strip.mem()[37], 0b11111110);
    ASSERT_EQ(led_strip.mem()[38], 0b11100000);
    ASSERT_EQ(led_strip.mem()[39], 0b11100000);

    // b/5
    ASSERT_EQ(led_strip.mem()[40], 0b11100000);
    ASSERT_EQ(led_strip.mem()[41], 0b11100000);
    ASSERT_EQ(led_strip.mem()[42], 0b11100000);
    ASSERT_EQ(led_strip.mem()[43], 0b11100000);
    ASSERT_EQ(led_strip.mem()[44], 0b11100000);
    ASSERT_EQ(led_strip.mem()[45], 0b11111110);
    ASSERT_EQ(led_strip.mem()[46], 0b11100000);
    ASSERT_EQ(led_strip.mem()[47], 0b11111110);

    // termination ("reset", as in datasheet)
    ASSERT_EQ(led_strip.mem()[48], 0b00000000);
    ASSERT_EQ(led_strip.mem()[49], 0b00000000);
    ASSERT_EQ(led_strip.mem()[50], 0b00000000);
    ASSERT_EQ(led_strip.mem()[51], 0b00000000);
    ASSERT_EQ(led_strip.mem()[52], 0b00000000);
    ASSERT_EQ(led_strip.mem()[53], 0b00000000);
    ASSERT_EQ(led_strip.mem()[54], 0b00000000);
    ASSERT_EQ(led_strip.mem()[55], 0b00000000);
    ASSERT_EQ(led_strip.mem()[56], 0b00000000);
    ASSERT_EQ(led_strip.mem()[57], 0b00000000);
    ASSERT_EQ(led_strip.mem()[58], 0b00000000);
    ASSERT_EQ(led_strip.mem()[59], 0b00000000);
    ASSERT_EQ(led_strip.mem()[60], 0b00000000);
    ASSERT_EQ(led_strip.mem()[61], 0b00000000);
    ASSERT_EQ(led_strip.mem()[62], 0b00000000);
    ASSERT_EQ(led_strip.mem()[63], 0b00000000);
    ASSERT_EQ(led_strip.mem()[64], 0b00000000);
    ASSERT_EQ(led_strip.mem()[65], 0b00000000);
    ASSERT_EQ(led_strip.mem()[66], 0b00000000);
    ASSERT_EQ(led_strip.mem()[67], 0b00000000);
}

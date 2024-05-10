#include <ledstrip.h>

#include <gtest/gtest.h>
#include <bitset>


TEST(ledstrip_suite, default_value)
{
    const LEDStrip led_strip(2);

    ASSERT_EQ(led_strip[0], GRB());
    ASSERT_EQ(led_strip[1], GRB());

    ASSERT_EQ(led_strip[0].bits(), std::bitset<24>());
    ASSERT_EQ(led_strip[1].bits(), std::bitset<24>());
}

TEST(ledstrip_suite, set_values)
{
    LEDStrip led_strip(2);
    led_strip[0] = GRB(1, 2, 3);
    ASSERT_EQ(led_strip[0], GRB(1, 2, 3));

    led_strip[1] = GRB(3, 4, 5);
    ASSERT_EQ(led_strip[1], GRB(3, 4, 5));
}

TEST(ledstrip_suite, create_logical_bitstream)
{
    LEDStrip led_strip(2);
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

TEST(ledstrip_suite, bitstream)
{
    LEDStrip led_strip(2);
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

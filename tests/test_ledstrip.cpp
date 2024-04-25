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

TEST(ledstrip_suite, create_spi_bits)
{
    LEDStrip led_strip(2);
    led_strip[0] = GRB(1, 2, 3);
    led_strip[1] = GRB(3, 4, 5);

    std::vector<SPIBit> spi_bits;
    led_strip.create_spi_bits(spi_bits);

    // [0]

    // g/1
    ASSERT_EQ(spi_bits[ 0], SPI_B0);
    ASSERT_EQ(spi_bits[ 1], SPI_B0);
    ASSERT_EQ(spi_bits[ 2], SPI_B0);
    ASSERT_EQ(spi_bits[ 3], SPI_B0);
    ASSERT_EQ(spi_bits[ 4], SPI_B0);
    ASSERT_EQ(spi_bits[ 5], SPI_B0);
    ASSERT_EQ(spi_bits[ 6], SPI_B0);
    ASSERT_EQ(spi_bits[ 7], SPI_B1);

    // r/2
    ASSERT_EQ(spi_bits[ 8], SPI_B0);
    ASSERT_EQ(spi_bits[ 9], SPI_B0);
    ASSERT_EQ(spi_bits[10], SPI_B0);
    ASSERT_EQ(spi_bits[11], SPI_B0);
    ASSERT_EQ(spi_bits[12], SPI_B0);
    ASSERT_EQ(spi_bits[13], SPI_B0);
    ASSERT_EQ(spi_bits[14], SPI_B1);
    ASSERT_EQ(spi_bits[15], SPI_B0);

    // b/3
    ASSERT_EQ(spi_bits[16], SPI_B0);
    ASSERT_EQ(spi_bits[17], SPI_B0);
    ASSERT_EQ(spi_bits[18], SPI_B0);
    ASSERT_EQ(spi_bits[19], SPI_B0);
    ASSERT_EQ(spi_bits[20], SPI_B0);
    ASSERT_EQ(spi_bits[21], SPI_B0);
    ASSERT_EQ(spi_bits[22], SPI_B1);
    ASSERT_EQ(spi_bits[23], SPI_B1);


    // [1]

    // g/3
    ASSERT_EQ(spi_bits[24], SPI_B0);
    ASSERT_EQ(spi_bits[25], SPI_B0);
    ASSERT_EQ(spi_bits[26], SPI_B0);
    ASSERT_EQ(spi_bits[27], SPI_B0);
    ASSERT_EQ(spi_bits[28], SPI_B0);
    ASSERT_EQ(spi_bits[29], SPI_B0);
    ASSERT_EQ(spi_bits[30], SPI_B1);
    ASSERT_EQ(spi_bits[31], SPI_B1);

    // r/4
    ASSERT_EQ(spi_bits[32], SPI_B0);
    ASSERT_EQ(spi_bits[33], SPI_B0);
    ASSERT_EQ(spi_bits[34], SPI_B0);
    ASSERT_EQ(spi_bits[35], SPI_B0);
    ASSERT_EQ(spi_bits[36], SPI_B0);
    ASSERT_EQ(spi_bits[37], SPI_B1);
    ASSERT_EQ(spi_bits[38], SPI_B0);
    ASSERT_EQ(spi_bits[39], SPI_B0);

    // b/5
    ASSERT_EQ(spi_bits[40], SPI_B0);
    ASSERT_EQ(spi_bits[41], SPI_B0);
    ASSERT_EQ(spi_bits[42], SPI_B0);
    ASSERT_EQ(spi_bits[43], SPI_B0);
    ASSERT_EQ(spi_bits[44], SPI_B0);
    ASSERT_EQ(spi_bits[45], SPI_B1);
    ASSERT_EQ(spi_bits[46], SPI_B0);
    ASSERT_EQ(spi_bits[47], SPI_B1);
}

TEST(ledstrip_suite, bitstream)
{
    LEDStrip led_strip(2);
    led_strip[0] = GRB(1, 2, 3);
    led_strip[1] = GRB(3, 4, 5);

    std::vector<SPIBit> spi_bits;
    led_strip.create_spi_bits(spi_bits);

    std::vector<uint8_t> bitstream = spibits_to_bitstream(spi_bits);

    ASSERT_EQ(bitstream[ 0], 0b11000110);
    // ------------------------0
    // -----------------------------1
    ASSERT_EQ(bitstream[ 1], 0b00110001);
    // --------------------------2
    // -------------------------------3
    ASSERT_EQ(bitstream[ 2], 0b10001100);
    // ----------------------------4
    ASSERT_EQ(bitstream[ 3], 0b01100011);
    // -------------------------5
    // ------------------------------6
    ASSERT_EQ(bitstream[ 4], 0b00011100);
    // ---------------------------7
    ASSERT_EQ(bitstream[ 5], 0b11000110);
    // ------------------------8
    // -----------------------------9
    ASSERT_EQ(bitstream[ 6], 0b00110001);
    // --------------------------10
    // -------------------------------11
    ASSERT_EQ(bitstream[ 7], 0b10001100);
    // ----------------------------12
    ASSERT_EQ(bitstream[ 8], 0b01100011);
    // -------------------------13
    // ------------------------------14
    ASSERT_EQ(bitstream[ 9], 0b10011000);
    // ---------------------------15
    ASSERT_EQ(bitstream[10], 0b11000110);
    // ------------------------16
    // -----------------------------17
    ASSERT_EQ(bitstream[11], 0b00110001);
    // --------------------------18
    // -------------------------------19
    ASSERT_EQ(bitstream[12], 0b10001100);
    // ----------------------------20
    ASSERT_EQ(bitstream[13], 0b01100011);
    // -------------------------21
    // ------------------------------22
    ASSERT_EQ(bitstream[14], 0b10011100);
    // ---------------------------23
    ASSERT_EQ(bitstream[15], 0b11000110);
    // ------------------------24
    // -----------------------------25
    ASSERT_EQ(bitstream[16], 0b00110001);
    // ---------------------------26
    // -------------------------------27
    ASSERT_EQ(bitstream[17], 0b10001100);
    // ----------------------------28
    ASSERT_EQ(bitstream[18], 0b01100011);
    // -------------------------29
    // ------------------------------30
    ASSERT_EQ(bitstream[19], 0b10011100);
    // ---------------------------31
    ASSERT_EQ(bitstream[20], 0b11000110);
    // ------------------------32
    // -----------------------------33
    ASSERT_EQ(bitstream[21], 0b00110001);
    // --------------------------34
    // -------------------------------35
    ASSERT_EQ(bitstream[22], 0b10001100);
    // ----------------------------36
    ASSERT_EQ(bitstream[23], 0b01110011);
    // -------------------------37
    // ------------------------------38
    ASSERT_EQ(bitstream[24], 0b00011000);
    // ---------------------------39
    ASSERT_EQ(bitstream[25], 0b11000110);
    // ------------------------40
    // -----------------------------41
    ASSERT_EQ(bitstream[26], 0b00110001);
    // --------------------------42
    // -------------------------------43
    ASSERT_EQ(bitstream[27], 0b10001100);
    // ----------------------------44
    ASSERT_EQ(bitstream[28], 0b01110011);
    // -------------------------45
    // ------------------------------46
    ASSERT_EQ(bitstream[29], 0b00011100);
    // ---------------------------47

    // termination ("reset", as in datasheet)
    ASSERT_EQ(bitstream[30], 0b00000000);
}

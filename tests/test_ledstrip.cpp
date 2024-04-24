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

TEST(ledstrip_suite, show)
{
    LEDStrip led_strip(2);
    led_strip[0] = GRB(1, 2, 3);
    led_strip[1] = GRB(3, 4, 5);

    std::vector<SPIBit> spi_line;
    led_strip.show(spi_line);

    ASSERT_EQ(spi_line[ 0], SPI_B0);
    ASSERT_EQ(spi_line[ 1], SPI_B0);
    ASSERT_EQ(spi_line[ 2], SPI_B0);
    ASSERT_EQ(spi_line[ 3], SPI_B0);
    ASSERT_EQ(spi_line[ 4], SPI_B0);
    ASSERT_EQ(spi_line[ 5], SPI_B0);
    ASSERT_EQ(spi_line[ 6], SPI_B0);
    ASSERT_EQ(spi_line[ 7], SPI_B1);

    ASSERT_EQ(spi_line[ 8], SPI_B0);
    ASSERT_EQ(spi_line[ 9], SPI_B0);
    ASSERT_EQ(spi_line[10], SPI_B0);
    ASSERT_EQ(spi_line[11], SPI_B0);
    ASSERT_EQ(spi_line[12], SPI_B0);
    ASSERT_EQ(spi_line[13], SPI_B0);
    ASSERT_EQ(spi_line[14], SPI_B1);
    ASSERT_EQ(spi_line[15], SPI_B0);

    ASSERT_EQ(spi_line[16], SPI_B0);
    ASSERT_EQ(spi_line[17], SPI_B0);
    ASSERT_EQ(spi_line[18], SPI_B0);
    ASSERT_EQ(spi_line[19], SPI_B0);
    ASSERT_EQ(spi_line[20], SPI_B0);
    ASSERT_EQ(spi_line[21], SPI_B0);
    ASSERT_EQ(spi_line[22], SPI_B1);
    ASSERT_EQ(spi_line[23], SPI_B1);


    ASSERT_EQ(spi_line[24], SPI_B0);
    ASSERT_EQ(spi_line[25], SPI_B0);
    ASSERT_EQ(spi_line[26], SPI_B0);
    ASSERT_EQ(spi_line[27], SPI_B0);
    ASSERT_EQ(spi_line[28], SPI_B0);
    ASSERT_EQ(spi_line[29], SPI_B0);
    ASSERT_EQ(spi_line[30], SPI_B1);
    ASSERT_EQ(spi_line[31], SPI_B1);

    ASSERT_EQ(spi_line[32], SPI_B0);
    ASSERT_EQ(spi_line[33], SPI_B0);
    ASSERT_EQ(spi_line[34], SPI_B0);
    ASSERT_EQ(spi_line[35], SPI_B0);
    ASSERT_EQ(spi_line[36], SPI_B0);
    ASSERT_EQ(spi_line[37], SPI_B1);
    ASSERT_EQ(spi_line[38], SPI_B0);
    ASSERT_EQ(spi_line[39], SPI_B0);

    ASSERT_EQ(spi_line[40], SPI_B0);
    ASSERT_EQ(spi_line[41], SPI_B0);
    ASSERT_EQ(spi_line[42], SPI_B0);
    ASSERT_EQ(spi_line[43], SPI_B0);
    ASSERT_EQ(spi_line[44], SPI_B0);
    ASSERT_EQ(spi_line[45], SPI_B1);
    ASSERT_EQ(spi_line[46], SPI_B0);
    ASSERT_EQ(spi_line[47], SPI_B1);
}

#include <ws2812_strip.h>

#include <gtest/gtest.h>
#include <bitset>


TEST(ws2812_strip, get_set)
{
    WS2812Strip led_strip(1, WS2812Strip::RASPBERRY);
    led_strip.set(0, GRB(1,2,3));
    ASSERT_EQ(led_strip.get(0), GRB(1,2,3));
}

TEST(ws2812_strip, mem_representation_for_spi)
{
    WS2812Strip led_strip(1, WS2812Strip::RASPBERRY);
    led_strip.set(0, GRB(1, 2, 3));

    ASSERT_GE(led_strip.mem().size(), 24);

    ASSERT_EQ(led_strip.mem()[ 0], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[ 1], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[ 2], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[ 3], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[ 4], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[ 5], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[ 6], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[ 7], WS2812Strip::RASPBERRY.ONE);

    ASSERT_EQ(led_strip.mem()[ 8], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[ 9], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[10], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[11], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[12], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[13], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[14], WS2812Strip::RASPBERRY.ONE);
    ASSERT_EQ(led_strip.mem()[15], WS2812Strip::RASPBERRY.ZERO);

    ASSERT_EQ(led_strip.mem()[16], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[17], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[18], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[19], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[20], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[21], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[22], WS2812Strip::RASPBERRY.ONE);
    ASSERT_EQ(led_strip.mem()[23], WS2812Strip::RASPBERRY.ONE);
}

TEST(ws2812_strip, default_value)
{
    const WS2812Strip led_strip(2, WS2812Strip::RASPBERRY);

    ASSERT_EQ(led_strip.get(0), GRB());
    ASSERT_EQ(led_strip.get(1), GRB());

    ASSERT_EQ(led_strip.mem().size(), 48 + WS2812Strip::RASPBERRY.n_zero_bytes);
    for (size_t i=0; i<48; i++)
        ASSERT_EQ(led_strip.mem()[i], WS2812Strip::RASPBERRY.ZERO) << i;

    for (size_t i=48; i<48+WS2812Strip::RASPBERRY.n_zero_bytes; i++)
        ASSERT_EQ(led_strip.mem()[i], 0) << i;
}

TEST(ws2812_strip, mem_representation_for_spi_two_leds)
{
    WS2812Strip led_strip(2, WS2812Strip::RASPBERRY);

    ASSERT_EQ(led_strip.mem().size(), 2/*n LEDS*/ * 3/*GRB/LED*/ * 8  + WS2812Strip::RASPBERRY.n_zero_bytes);

    ASSERT_EQ(led_strip.get(0), GRB(0,0,0)); // default value
    ASSERT_EQ(led_strip.get(1), GRB(0,0,0)); // default value

    led_strip.set(0, GRB(1, 2, 3));
    led_strip.set(1, GRB(3, 4, 5));

    // [0]

    // g/1
    ASSERT_EQ(led_strip.mem()[ 0], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[ 1], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[ 2], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[ 3], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[ 4], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[ 5], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[ 6], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[ 7], WS2812Strip::RASPBERRY.ONE);

    // r/2
    ASSERT_EQ(led_strip.mem()[ 8], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[ 9], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[10], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[11], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[12], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[13], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[14], WS2812Strip::RASPBERRY.ONE);
    ASSERT_EQ(led_strip.mem()[15], WS2812Strip::RASPBERRY.ZERO);

    // b/3
    ASSERT_EQ(led_strip.mem()[16], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[17], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[18], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[19], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[20], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[21], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[22], WS2812Strip::RASPBERRY.ONE);
    ASSERT_EQ(led_strip.mem()[23], WS2812Strip::RASPBERRY.ONE);


    // [1]

    // g/3
    ASSERT_EQ(led_strip.mem()[24], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[25], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[26], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[27], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[28], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[29], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[30], WS2812Strip::RASPBERRY.ONE);
    ASSERT_EQ(led_strip.mem()[31], WS2812Strip::RASPBERRY.ONE);

    // r/4
    ASSERT_EQ(led_strip.mem()[32], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[33], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[34], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[35], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[36], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[37], WS2812Strip::RASPBERRY.ONE);
    ASSERT_EQ(led_strip.mem()[38], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[39], WS2812Strip::RASPBERRY.ZERO);

    // b/5
    ASSERT_EQ(led_strip.mem()[40], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[41], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[42], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[43], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[44], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[45], WS2812Strip::RASPBERRY.ONE);
    ASSERT_EQ(led_strip.mem()[46], WS2812Strip::RASPBERRY.ZERO);
    ASSERT_EQ(led_strip.mem()[47], WS2812Strip::RASPBERRY.ONE);

    // termination ("reset", as in datasheet)
    for (size_t i=48; i<48+WS2812Strip::RASPBERRY.n_zero_bytes; i++)
        ASSERT_EQ(led_strip.mem()[i], 0) << i;
}

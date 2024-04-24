#include <gtest/gtest.h>

#include <bitset>


TEST(bit_suite, byte_layout)
{
    ASSERT_EQ(100, 0b01100100);
}

TEST(bit_suite, basic)
{
    std::bitset<8> bits = 42;
    ASSERT_EQ(bits[7], 0);
    ASSERT_EQ(bits[6], 0);
    ASSERT_EQ(bits[5], 1);
    ASSERT_EQ(bits[4], 0);
    ASSERT_EQ(bits[3], 1);
    ASSERT_EQ(bits[2], 0);
    ASSERT_EQ(bits[1], 1);
    ASSERT_EQ(bits[0], 0);
}

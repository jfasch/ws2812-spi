#include <grb.h>

#include <gtest/gtest.h>


TEST(grb_suite, basic1)
{
    GRB grb(150, 244, 100);

    std::bitset<24> bits = grb.bits();

    ASSERT_EQ(bits[ 0], 1);
    ASSERT_EQ(bits[ 1], 0);
    ASSERT_EQ(bits[ 2], 0);
    ASSERT_EQ(bits[ 3], 1);
    ASSERT_EQ(bits[ 4], 0);
    ASSERT_EQ(bits[ 5], 1);
    ASSERT_EQ(bits[ 6], 1);
    ASSERT_EQ(bits[ 7], 0);
    ASSERT_EQ(bits[ 8], 1);
    ASSERT_EQ(bits[ 9], 1);
    ASSERT_EQ(bits[10], 1);
    ASSERT_EQ(bits[11], 1);
    ASSERT_EQ(bits[12], 0);
    ASSERT_EQ(bits[13], 1);
    ASSERT_EQ(bits[14], 0);
    ASSERT_EQ(bits[15], 0);
    ASSERT_EQ(bits[16], 0);
    ASSERT_EQ(bits[17], 1);
    ASSERT_EQ(bits[18], 1);
    ASSERT_EQ(bits[19], 0);
    ASSERT_EQ(bits[20], 0);
    ASSERT_EQ(bits[21], 1);
    ASSERT_EQ(bits[22], 0);
    ASSERT_EQ(bits[23], 0);
}

TEST(grb_suite, basic2)
{
    GRB grb(1, 2, 3);

    std::bitset<24> bits = grb.bits();

    ASSERT_EQ(bits[ 0], 0);
    ASSERT_EQ(bits[ 1], 0);
    ASSERT_EQ(bits[ 2], 0);
    ASSERT_EQ(bits[ 3], 0);
    ASSERT_EQ(bits[ 4], 0);
    ASSERT_EQ(bits[ 5], 0);
    ASSERT_EQ(bits[ 6], 0);
    ASSERT_EQ(bits[ 7], 1);
    ASSERT_EQ(bits[ 8], 0);
    ASSERT_EQ(bits[ 9], 0);
    ASSERT_EQ(bits[10], 0);
    ASSERT_EQ(bits[11], 0);
    ASSERT_EQ(bits[12], 0);
    ASSERT_EQ(bits[13], 0);
    ASSERT_EQ(bits[14], 1);
    ASSERT_EQ(bits[15], 0);
    ASSERT_EQ(bits[16], 0);
    ASSERT_EQ(bits[17], 0);
    ASSERT_EQ(bits[18], 0);
    ASSERT_EQ(bits[19], 0);
    ASSERT_EQ(bits[20], 0);
    ASSERT_EQ(bits[21], 0);
    ASSERT_EQ(bits[22], 1);
    ASSERT_EQ(bits[23], 1);
}

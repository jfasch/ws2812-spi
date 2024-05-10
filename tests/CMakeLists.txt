ADD_EXECUTABLE(
  ws2812-spi-suite

  test_grb.cpp
  test_ledstrip.cpp

  test_bitset_comprehension.cpp
)

TARGET_LINK_LIBRARIES(
  ws2812-spi-suite

  ws2812
  gtest_main 
)

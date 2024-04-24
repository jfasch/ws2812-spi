ADD_EXECUTABLE(
  ws2812-spi-suite

  test_bits.cpp
  test_grb.cpp
  test_ledstrip.cpp
)

TARGET_LINK_LIBRARIES(
  ws2812-spi-suite

  ws2812
  gtest_main 
)

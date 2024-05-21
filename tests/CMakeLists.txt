ADD_EXECUTABLE(
  ws2812-spi-suite

  test_ws2812_strip.cpp
)

TARGET_LINK_LIBRARIES(
  ws2812-spi-suite

  ws2812
  gtest_main 
)

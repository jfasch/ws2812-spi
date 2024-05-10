ADD_LIBRARY(
  ws2812

  grb.h
  grb.cpp
  ws2812_strip.h
  ws2812_strip.cpp
  spi.h
  spi.cpp
)

TARGET_INCLUDE_DIRECTORIES(
  ws2812

  PUBLIC
  .
)

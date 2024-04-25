ADD_LIBRARY(
  ws2812

  grb.h
  grb.cpp
  ledstrip.h
  ledstrip.cpp
  spi.h
  spi.cpp
)

TARGET_INCLUDE_DIRECTORIES(
  ws2812

  PUBLIC
  .
)

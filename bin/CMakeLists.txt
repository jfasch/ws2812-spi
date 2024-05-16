ADD_EXECUTABLE(blink-12 blink-12.cpp)
TARGET_LINK_LIBRARIES(blink-12 ws2812)

ADD_EXECUTABLE(kitt kitt.cpp)
TARGET_LINK_LIBRARIES(kitt ws2812)

ADD_EXECUTABLE(spi-loopback spi-loopback.cpp)



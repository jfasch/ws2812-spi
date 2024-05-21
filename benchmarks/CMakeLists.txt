ADD_EXECUTABLE(ws2812-benchmark main.cpp)

TARGET_LINK_LIBRARIES(ws2812-benchmark
  
  ws2812
  benchmark::benchmark
)

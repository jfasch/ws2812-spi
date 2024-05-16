#include "spi.h"

#include <algorithm>
#include <cstdio>
#include <cassert>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>


SPIDevice::SPIDevice(const std::string& path)
{
    _fd = open(path.c_str(), O_RDWR);
    if (_fd == -1) {
        perror("open");
        assert(false);
    }
}

SPIDevice::~SPIDevice()
{
    close(_fd);
}

void SPIDevice::write(const WS2812Strip& s)
{
    const uint8_t* xfer_bytes = &s.mem()[0];
    size_t remaining_bytes = s.mem().size();

    while (remaining_bytes) {
        size_t xfer_size = std::min(remaining_bytes, 4096UL);
        remaining_bytes -= xfer_size;

        struct spi_ioc_transfer tr = {
            .tx_buf = (unsigned long)xfer_bytes,
            .len = (uint32_t)xfer_size,
            .speed_hz = s.profile().frequency_hz,
        };

        int ret = ioctl(_fd, SPI_IOC_MESSAGE(1), &tr);

        if (ret == -1) {
            perror("ioctl(SPI_IOC_MESSAGE(1))");
            assert(false);
        }
    }    
}

#include "spi.h"

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
    struct spi_ioc_transfer tr = {
        .tx_buf = (unsigned long)&s.mem()[0],
        .len = (uint32_t)s.mem().size(),
        .speed_hz = s.profile().frequency_hz,
    };

    int ret = ioctl(_fd, SPI_IOC_MESSAGE(1), &tr);

    if (ret == -1) {
        perror("ioctl(SPI_IOC_MESSAGE(1))");
        assert(false);
    }    
}

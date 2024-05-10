#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

#include <iostream>

using namespace std;

void terminate_if_error(int code, const char* msg)
{
    if (code == -1) {
        perror(msg);
        exit(1);
    }
}

uint32_t get_mode(int fd)
{
    uint32_t mode;
	int ret = ioctl(fd, SPI_IOC_RD_MODE32, &mode);
    terminate_if_error(ret, "ioctl(SPI_IOC_RD_MODE32)");
    return mode;
}

void set_mode(int fd, uint32_t mode)
{
	int ret = ioctl(fd, SPI_IOC_WR_MODE32, &mode);
    terminate_if_error(ret, "ioctl(SPI_IOC_WR_MODE32)");
}

void print_mode(uint32_t mode)
{
    cout << "Mode:" << endl;
    cout << "  SPI_CPHA: " << (mode & SPI_CPHA) << endl;
    cout << "  SPI_CPOL: " << (mode & SPI_CPOL) << endl;
    cout << "  SPI_MODE_0: " << (mode & SPI_MODE_0) << endl;
    cout << "  SPI_MODE_1: " << (mode & SPI_MODE_1) << endl;
    cout << "  SPI_MODE_2: " << (mode & SPI_MODE_2) << endl;
    cout << "  SPI_MODE_3: " << (mode & SPI_MODE_3) << endl;
    cout << "  SPI_MODE_X_MASK: " << (mode & SPI_MODE_X_MASK) << endl;
    cout << "  SPI_CS_HIGH: " << (mode & SPI_CS_HIGH) << endl;
    cout << "  SPI_LSB_FIRST: " << (mode & SPI_LSB_FIRST) << endl;
    cout << "  SPI_3WIRE: " << (mode & SPI_3WIRE) << endl;
    cout << "  SPI_LOOP: " << (mode & SPI_LOOP) << endl;
    cout << "  SPI_NO_CS: " << (mode & SPI_NO_CS) << endl;
    cout << "  SPI_READY: " << (mode & SPI_READY) << endl;
    cout << "  SPI_TX_DUAL: " << (mode & SPI_TX_DUAL) << endl;
    cout << "  SPI_TX_QUAD: " << (mode & SPI_TX_QUAD) << endl;
    cout << "  SPI_RX_DUAL: " << (mode & SPI_RX_DUAL) << endl;
    cout << "  SPI_RX_QUAD: " << (mode & SPI_RX_QUAD) << endl;
    cout << "  SPI_CS_WORD: " << (mode & SPI_CS_WORD) << endl;
    cout << "  SPI_TX_OCTAL: " << (mode & SPI_TX_OCTAL) << endl;
    cout << "  SPI_RX_OCTAL: " << (mode & SPI_RX_OCTAL) << endl;
    cout << "  SPI_3WIRE_HIZ: " << (mode & SPI_3WIRE_HIZ) << endl;
    cout << "  SPI_RX_CPHA_FLIP: " << (mode & SPI_RX_CPHA_FLIP) << endl;
    cout << "  SPI_MOSI_IDLE_LOW: " << (mode & SPI_MOSI_IDLE_LOW) << endl;
}

uint8_t get_bits_per_word(int fd)
{
    uint8_t bits;
    int ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
    terminate_if_error(ret, "ioctl(SPI_IOC_RD_BITS_PER_WORD)");
    return bits;
}




int main(int argc, char** argv)
{
    const char* filename = argv[1];

    int fd = open(filename, O_RDWR);
    terminate_if_error(fd, "open");

    uint32_t mode = get_mode(fd);
    print_mode(mode);

    // mode |= SPI_LSB_FIRST;
    // set_mode(fd, mode);
    // print_mode(get_mode(fd));

    uint8_t bits = get_bits_per_word(fd);
    cout << "SPI_IOC_RD_BITS_PER_WORD: " << (int)bits << endl;

    uint8_t outbuf[] = {'a', 'b', 'c', 'd'};
    uint8_t inbuf[sizeof(outbuf)];

    uint8_t* outp = outbuf;
    uint8_t* inp = inbuf;

	struct spi_ioc_transfer tr = {
		.tx_buf = (unsigned long)outp,
        .rx_buf = (unsigned long)inp,
		.len = sizeof(outbuf),
		.speed_hz = 4000000,
		.bits_per_word = 8,
	};

    cout << "Transferring: " << outbuf[0] << outbuf[1] << outbuf[2] << outbuf[3] << endl;
    
    int ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
    terminate_if_error(ret, "ioctl(SPI_IOC_MESSAGE(1))");

    cout << "Read back: " << inbuf[0] << inbuf[1] << inbuf[2] << inbuf[3] << endl;

    return 0;
}

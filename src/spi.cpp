#include "spi.h"

SPI::SPI(const char *device) {
  this->device = device;
  this->port = port;
  this->bits = 8;
}
SPI::SPI() {}

int SPI::Setup() {
  fd = open(device, O_RDWR);
  return fd;
}

int SPI::Setup(const char *device) {
  this->device = device;
  this->port = port;
  fd = open(device, O_RDWR);
  return fd;
}

int SPI::setMode(int mode) {
  if (ioctl(fd, SPI_IOC_WR_MODE, &mode) < 0)
    return -1;
  return ioctl(fd, SPI_IOC_RD_MODE, &mode);
}

int SPI::setClock(unsigned int freq) {
  this->freq = freq;
  if (ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &freq) < 0)
    return -1;
  return ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &freq);
}

int SPI::setBitOrder(int order) {
  if (order == 0) {
    if (ioctl(fd, SPI_IOC_WR_LSB_FIRST, SPI_LSB_FIRST) < 0)
      return -1;
    return ioctl(fd, SPI_IOC_RD_LSB_FIRST, SPI_LSB_FIRST);
  }
  return 0;
}

void SPI::setDelay(unsigned short usecs) {
  this->usecs = usecs;
}

int SPI::Write(void *tx_data, int length) {
  return write(fd, tx_data, length);
}

int SPI::Read(void *rx_data) {
  return read(fd, rx_data, rx_size);
}

int SPI::transfer(void *tx_data, void *rx_data, unsigned int len) {
  struct spi_ioc_transfer spi;

  // Mentioned in spidev.h but not used in the original kernel documentation
  //	test program )-:

  memset(&spi, 0, sizeof(spi));

  spi.tx_buf = (unsigned long)tx_data;
  spi.rx_buf = (unsigned long)rx_data;
  spi.len = len;
  spi.delay_usecs = usecs;
  spi.speed_hz = freq;
  spi.tx_nbits = tx_size;
  spi.rx_nbits = rx_size;

  return ioctl(fd, SPI_IOC_MESSAGE(1), &spi);
}

int SPI::Close(void) {
  return close(fd);
}

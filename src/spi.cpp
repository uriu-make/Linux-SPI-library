#include "spi.h"

SPI::SPI(const char *device, int mode, unsigned int freq) {
  this->device = device;
  this->bits = 8;
  this->mode = mode;
  this->freq = freq;
  this->usecs = 0;
}

int SPI::Setup() {
  fd = open(device, O_RDWR);
  this->setMode(mode);
  this->setClock(freq);
  this->setDelay(usecs);
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

int SPI::Read(void *rx_data, int length) {
  return read(fd, rx_data, length);
}

int SPI::transfer(void *tx_data, void *rx_data, unsigned int len) {
  struct spi_ioc_transfer spi;
  memset(&spi, 0, sizeof(spi));
  spi.tx_buf = (unsigned long)tx_data;
  spi.rx_buf = (unsigned long)rx_data;
  spi.len = len;
  spi.delay_usecs = usecs;
  spi.speed_hz = freq;
  spi.bits_per_word = bits;

  return ioctl(fd, SPI_IOC_MESSAGE(1), &spi);
}

int SPI::Close(void) {
  return close(fd);
}

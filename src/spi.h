#ifndef SPI_H_INCLUDE
#define SPI_H_INCLUDE
#include <fcntl.h>
#include <linux/spi/spidev.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <asm/ioctl.h>
#include <string.h>

#define SPI0_0 "/dev/spidev0.0"
#define SPI0_1 "/dev/spidev0.1"
#define MODE_0 0
#define MODE_1 1
#define MODE_2 2
#define MODE_3 3
#define LSBFIRST 0
#define MSBFIRST 1

class SPI {
 public:
  SPI(const char *device, int mode, unsigned int freq);
  int Setup(void);
  int setMode(int mode);
  int setClock(unsigned int freq);
  int setBitOrder(int order);
  void setDelay(unsigned short usecs);
  int Write(void *tx_data, int length);
  int Read(void *rx_data, int length);
  int transfer(void *tx_data, void *rx_data, size_t length);
  int Close(void);

 private:
  int fd, mode;
  unsigned int freq;
  unsigned short usecs;
  const char *device;
  unsigned char bits;
};
#endif
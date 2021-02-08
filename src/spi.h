#ifndef SPI_H_INCLUDE
#define SPI_H_INCLUDE
#include <fcntl.h>
#include <linux/spi/spidev.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <asm/ioctl.h>
#include <string.h>
#include <string>

#define SPI0 "/dev/spidev0.0"
#define SPI1 "/dev/spidev0.1"
#define MODE_0 0
#define MODE_1 1
#define MODE_2 2
#define MODE_3 3
#define LSBFIRST 0
#define MSBFIRST 1

using namespace std;

class SPI {
 public:
  SPI(const char *device);
  SPI();
  int Setup(void);
  int Setup(const char *device);
  int setMode(int mode);
  int setClock(unsigned int freq);
  int setBitOrder(int order);
  void setDelay(unsigned short usecs);
  int Write(void *tx_data, int length);
  int Read(void *rx_data);
  int transfer(void *tx_data, void *rx_data, size_t length);
  int Close(void);

 private:
  int fd, port;
  unsigned int freq;
  unsigned short usecs;
  const char *device;
  unsigned char bits;
  size_t tx_size, rx_size;
};
#endif
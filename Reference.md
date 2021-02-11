# Reference
```
SPI::SPI(const char *device, int mode, unsigned int freq)
```
**device Name of the SPI to be used (example "/dev/spidev0.0").\
**mode SPI mode (MODE_0,MODE_1,MODE_2,MODE_3).
**freq SPI speed(Hz).\
```
int SPI::Setup(void);
```
Setup SPI device.
```
int SPI::setMode(int mode);
```
```
int SPI::setClock(unsigned int freq);
```
```
int SPI::setBitOrder(int order);
```
```
void SPI::setDelay(unsigned short usecs);
```
```
int SPI::Write(void *tx_data, int length);
```
```
int SPI::Read(void *rx_data, int length);
```
```
int SPI::transfer(void *tx_data, void *rx_data, size_t length);
```
```
int SPI::Close(void);
```
#include <spi.h>
#include <string>
#include <math.h>
#define VOLTAGE 3.3
using namespace std;
SPI MCP3208(SPI0);
int adc_pin = 0;
int single = 1;
int main() {
  unsigned char buff[2] = {0};
  unsigned char data[3] = {0};
  buff[0] = 0b00000100 | (adc_pin >> 2) | single << 1;
  buff[1] = adc_pin << 6;
  MCP3208.Setup();
  MCP3208.setMode(MODE_0);
  MCP3208.setClock(100000);
  MCP3208.setDelay(0);
  MCP3208.transfer(buff, data, 3);
  int d = data[2] | (data[1] & 0b1111) << 8;
  printf("%d\n", d);
  printf("%lf\n", VOLTAGE * d / pow(2, 12));
  return 0;
}
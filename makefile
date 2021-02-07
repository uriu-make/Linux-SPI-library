install:
	gcc -shared -fPIC src/spi.cpp -o src/libspi.so
	sudo cp src/spi.h /usr/include/spi.h
	sudo cp src/libspi.so /usr/lib/libspi.so

test:
	g++ src/t.cpp -o src/t.o -lspi
# st7032:
# 	gcc example/st7032.cpp -o example/st7032.o -li2c

# bme280:
# 	gcc example/bme280.cpp -o example/bme280.o -li2c

# all: install st7032 bme280
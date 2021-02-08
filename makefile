install:
	gcc -shared -fPIC src/spi.cpp -o src/libspi.so
	sudo cp src/spi.h /usr/include/spi.h
	sudo cp src/libspi.so /usr/lib/libspi.so

MCP3208:
	g++ example/MCP3208.cpp -o example/MCP3208.o -lspi
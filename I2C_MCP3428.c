// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// MCP3428
// This code is designed to work with the MCP3428_I2CADC I2C 

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

void main() 
{
	// Create I2C bus
	int file;
	char *bus = "/dev/i2c-0";
	if((file = open(bus, O_RDWR)) < 0) 
	{
		printf("Failed to open the bus. \n");
		exit(1);
	}
	// Get I2C device, MCP3428 I2C address is 0x68(104)
	ioctl(file, I2C_SLAVE, 0x68);

	// Select configuration command(0x10)
	// Continuous conversion mode, Channel-1, 12-bit resolution
	char config[1] = {0};
	config[0] = 0x10;
	write(file, config, 1);
	sleep(1);

	// Read 2 bytes of data from register(0x00)
	// raw_adc msb, raw_adc lsb
	char reg[1] = {0x00};
	write(file, reg, 1);
	char data[2] = {0};
	if(read(file, data, 2) != 2)
	{
		printf("Error : Input/Output error \n");
	}
	else
	{
		// Convert the data to 12-bits
		int raw_adc = ((data[0] & 0x0F) * 256 + data[1]);
		if(raw_adc > 2047)
		{
			raw_adc -= 4095;
		}

		// Output data to screen
		printf("Digital value of Analog Input : %d \n", raw_adc);
	}
}

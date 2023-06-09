//Compilation Steps
//g++ LED_Code.cpp -o LED_code.o
//./LED_code.o
// Copyright (C) 2014-2017 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include "led_conf.h"

#define IN  0
#define OUT 1

#define LOW  0
#define HIGH 1

#define PIN  24 /* P1-18 */
#define PIN_1  23 /* P1-18 */
#define PIN_2 18

#define POUT 4  /* P1-07 */
#define POUT_1 17  /* P1-07 */
#define POUT_2 3

	int repeat = 10;
	int value = 0;
	int value1 = 0;
	
int set_gpio(char pin, char led_stat);
int gpio_init();


static int
GPIOExport(int pin)
{
#define BUFFER_MAX 3
	char buffer[BUFFER_MAX];
	ssize_t bytes_written;
	int fd;

	fd = open("/sys/class/gpio/export", O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open export for writing!\n");
		return(-1);
	}

	bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
	write(fd, buffer, bytes_written);
	close(fd);
	return(0);
}

static int GPIOUnexport(int pin)
{
	char buffer[BUFFER_MAX];
	ssize_t bytes_written;
	int fd;

	fd = open("/sys/class/gpio/unexport", O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open unexport for writing!\n");
		return(-1);
	}

	bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
	write(fd, buffer, bytes_written);
	close(fd);
	return(0);
}

static int
GPIODirection(int pin, int dir)
{
	static const char s_directions_str[]  = "in\0out";

#define DIRECTION_MAX 35
	char path[DIRECTION_MAX];
	int fd;

	snprintf(path, DIRECTION_MAX, "/sys/class/gpio/gpio%d/direction", pin);
	fd = open(path, O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open gpio direction for writing!\n");
		return(-1);
	}

	if (-1 == write(fd, &s_directions_str[IN == dir ? 0 : 3], IN == dir ? 2 : 3)) {
		fprintf(stderr, "Failed to set direction!\n");
		return(-1);
	}

	close(fd);
	return(0);
}

static int
GPIORead(int pin)
{
#define VALUE_MAX 30
	char path[VALUE_MAX];
	char value_str[3];
	int fd;

	snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);
	fd = open(path, O_RDONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open gpio value for reading!\n");
		return(-1);
	}

	if (-1 == read(fd, value_str, 3)) {
		fprintf(stderr, "Failed to read value!\n");
		return(-1);
	}

	close(fd);

	return(atoi(value_str));
}

static int
GPIOWrite(int pin, int value)
{
	static const char s_values_str[] = "01";

	char path[VALUE_MAX];
	int fd;

	snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);
	fd = open(path, O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open gpio value for writing!\n");
		return(-1);
	}

	if (1 != write(fd, &s_values_str[LOW == value ? 0 : 1], 1)) {
		fprintf(stderr, "Failed to write value!\n");
		return(-1);
	}

	close(fd);
	return(0);
}


//int main(void) {
int gpio_init()
{
    	/*
	 * Enable GPIO pins
	 */
	//if (-1 == GPIOExport(POUT) || -1 == GPIOExport(PIN))
	//	std::cout<<"gpio_init_error1"<<std::endl;
		//return(1);
	//if (-1 == GPIOExport(POUT_1) || -1 == GPIOExport(PIN_1))
	//	std::cout<<"gpio_init_error2"<<std::endl;
	
	if (-1 == GPIOExport(POUT_2) || -1 == GPIOExport(PIN_2))
		std::cout<<"gpio_init_error3"<<std::endl;	

//		return(1);
	/*
	 * Set GPIO directions
	 */
	//if (-1 == GPIODirection(POUT, OUT) || -1 == GPIODirection(PIN, IN))
		//std::cout<<"gpio_init_error3"<<std::endl;

	//	return(2);

	//if (-1 == GPIODirection(POUT_1, OUT) || -1 == GPIODirection(PIN_1, IN))
		//std::cout<<"gpio_init_error4"<<std::endl;
	
	//return(2);
	
	if (-1 == GPIODirection(POUT_2, OUT) || -1 == GPIODirection(PIN_2, IN))
		std::cout<<"gpio_init_error4"<<std::endl;	

		//return(2);
		
	//GPIOWrite(POUT, 1);
	//GPIOWrite(POUT_1, 1);
	GPIOWrite(POUT_2, 1);
	std::cout<<"GPIO_INIT"<< std::endl;
	//sleep(2);
}

int set_gpio(char pin, char led_stat)
{
	//if(pin==1)
	//{
	//	GPIOWrite(POUT, led_stat);
	//}
	//if(pin==2)
	//{
	//	GPIOWrite(POUT_1, led_stat);
	//}
	if(pin==3)
	{
		GPIOWrite(POUT_2, led_stat);
	}
	return 0;
}
/*
int main()
{
	 gpio_init();
	 while(1)
	 {
	 	set_gpio(1,1);
	 	set_gpio(2,0);
	 	sleep(1);
	 	set_gpio(1,0);
	 	set_gpio(2,1);
	 	sleep(1);
	 }
	
}*/

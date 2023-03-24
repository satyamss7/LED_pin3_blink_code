//Compilation Steps
//g++ LED_Code.cpp -o LED_code.o
//./LED_code.o

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "led_conf.h"

int main()
{
	 gpio_init();
	 while(1)
	 {
	 	set_gpio(3,0);
	 	sleep(1);
	 	set_gpio(3,1);
	 	sleep(1);
	 }
	
}

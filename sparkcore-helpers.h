#ifndef __SPCH__
#define __SPCH__

#define DEFAULT_LED_FLASH_TIME 100

#define COLOR_RED 			   0
#define COLOR_GREEN 		   1
#define COLOR_BLUE			   2

#include "TCPLogger.h"

void flash( int );
void vomit_rainbows();
/* squirt text into socket, then close it, don't care if succeeds */
void squirt(char* server, int port, char * text);

#endif
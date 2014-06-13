#include "sparkcore-helpers.h"

// top level of library code here

void flash(int color) {
	/* take control if we haven't got it */
	if ( !RGB.controlled() ) RGB.control( true );

		 if (color == COLOR_RED  ) RGB.color( 255, 0 , 0 );
	else if (color == COLOR_GREEN) RGB.color( 0  ,255, 0 );
	else if (color == COLOR_BLUE ) RGB.color( 0  , 0 ,255);
	delay(DEFAULT_LED_FLASH_TIME);

	/* release control */
	RGB.control(false);
}

void vomit_rainbows() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j<3; j++) {
			flash(j);
		}
	}
}

void squirt(char* server, int port, char * text) {
	TCPClient c;
	c.connect(server, port);
	if ( c.connected() ) c.print(text);
	c.stop();
}

#include "application.h"
#include "sparkcore-helpers/sparkcore-helpers.h"
#include "sparkcore-helpers/TCPLogger.h"



TCPLogger logger("devrecord.com",6000);

void setup() {
	delay(100);
	logger.log("well?");
	/* I like a distinctive start */
	vomit_rainbows();
	delay(100);
}

void loop() {
	
}
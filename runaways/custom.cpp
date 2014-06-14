
#include "application.h"
#include "sparkcore-helpers/sparkcore-helpers.h"
#include "sparkcore-helpers/TCPLogger.h"



TCPLogger logger("devrecord.com",6000);
int i = 0;

void setup() {
	/* I like a distinctive start */
	logger.log("vomiting rainbows");
	vomit_rainbows();
	logger.log("finished");
}

void loop() {
	static char countBuf[32] = { '\0' };
	sprintf(countBuf, "counted: %d", i);
	if (i % 100 == 0 ) logger.log( countBuf );
	if (i > 1000 ) i = 0;
	memset( countBuf, 0, 32 );
	i++;
}
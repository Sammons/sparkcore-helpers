sparkcore-helpers
=================

helper classes and code for sparkcore development

Latest and greatest: 6/13/2014 - TCPLogger
---

Usage:

TCPLogger logger("host.com",6000);// connect to host.com:6000

//or

TCPLogger logger(IPAddress(0,0,0,0), 6000);// connect to 0.0.0.0:6000

setup() {}

int i = 0;

loop() {
	i++;
	char[32] buf = {'\0'};
	if ( i % 10 == 0 ) {
		sprintf(buf, "counted: %d", i);
		logger.log(buf);
		i = 0;
	}
}

-	Notes
TCPLogger will do it's best to not forget things by queueing them up
to a default max of 128 chars or so. It will automatically reconnect to
the server if log is called and it is disconnected (it also does not connect until
the first call of log)
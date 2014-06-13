#ifndef __TCPLogger__
#define __TCPLogger__

#include "spark_wiring_ipaddress.h"
#include "spark_wiring_tcpclient.h"
#define DEFAULT_PORT 						6000
#define MAX_RECONNECT_ATTEMPTS 				5
#define DELAY_BETWEEN_RECONNECT_ATTEMPTS 	10

/* debug mode true */
#define __TCP_LOGGER_DEBUG_MODE__ 

/* debug flashes for logger */
#ifdef __TCP_LOGGER_DEBUG_MODE__
#define TCP_LOGGER_DEBUG_FLASH_BAD  flash(COLOR_RED)
#define TCP_LOGGER_DEBUG_FLASH_GOOD flash(COLOR_GREEN)
#else
#define TCP_LOGGER_DEBUG_FLASH_BAD
#define TCP_LOGGER_DEBUG_FLASH_GOOD
#endif

class TCPLogger
{	
public:
	TCPLogger();
	TCPLogger( const char* host, int port );
	TCPLogger( const char* host );
	TCPLogger( IPAddress server, int port );	
	TCPLogger( IPAddress server	);

	void log( char* );
	void log( char  );

	~TCPLogger();

private:
	const char*	host;
	int 		port;
	IPAddress 	server;
	TCPClient 	socket;
	
	void init( const char* host, IPAddress server, int port );

	/* tries many times */
	bool connect();

};

#endif
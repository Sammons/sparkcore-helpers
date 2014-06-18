#ifndef __TCPLogger__
#define __TCPLogger__

#include <vector>
#include "spark_wiring_string.h"
#include "spark_wiring_ipaddress.h"
#include "spark_wiring_tcpclient.h"

#define DEFAULT_PORT 						6000
#define MAX_RECONNECT_ATTEMPTS 				1
#define TCP_LOGGER_DELAY_BETWEEN_RECONNECT_ATTEMPTS 	0
#define TCP_LOGGER_MAX_CACHE_SIZE			( sizeof( char ) * 128 )

/* debug mode true */
// #define __TCP_LOGGER_RGB_DEBUG_MODE__ 

/* debug flashes for logger */
#ifdef __TCP_LOGGER_RGB_DEBUG_MODE__
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

	void log( char*  );
	void log( String );

	~TCPLogger();

private:
	const char*	 host;
	int 		 port;
	int 		 store_size;
	IPAddress 	 server;
	TCPClient 	 socket;

	// only for messages which fail
	std::vector<String> messageQ;
	
	void init( const char* host, IPAddress server, int port );

	/* tries many times */
	bool connect();

};

#endif
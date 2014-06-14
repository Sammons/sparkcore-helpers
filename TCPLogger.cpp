#pragma once

#include "sparkcore-helpers.h"
#include "TCPLogger.h"


TCPLogger::TCPLogger( const char* host, int port ) {
	init( host, IPAddress(0,0,0,0), port );
}
TCPLogger::TCPLogger( const char* host ) {
	init( host, IPAddress(0,0,0,0), DEFAULT_PORT );
}
TCPLogger::TCPLogger( IPAddress server, int port ) {
	init( NULL, server, port);
}
TCPLogger::TCPLogger( IPAddress server) {
	init( NULL, server, port);
}
void TCPLogger::init( const char* host, IPAddress server, int port) {
	this->host = host;
	this->server = server;
	this->port = port;
	this->store_size = 0;
}
void TCPLogger::log( String logText ) {
	log( logText.c_str() );
}
void TCPLogger::log( char* logText ) {
	if ( socket.connected() ) { socket.print( logText ); }
	else if ( connect() )     { socket.print( logText ); }
	else {
		int len = strlen(logText);
		// The logger refuses to eat all of the sparkcore's memory
		if (store_size + len < TCP_LOGGER_MAX_CACHE_SIZE) {
			messageQ.push_back(String(logText));
			store_size += len;
		}
	}
}

bool TCPLogger::connect() {
	int number_of_attempts = MAX_RECONNECT_ATTEMPTS;
	bool succeeded = false;
	while ( number_of_attempts > 0 ) {
		if  (  ( host != NULL && socket.connect( host, port   ) )
		    || ( host == NULL && socket.connect( server, port ) ) ) {

			TCP_LOGGER_DEBUG_FLASH_GOOD;

			log("TCPLogger connected\n");
			for (std::vector<String>::iterator i = messageQ.begin(); i != messageQ.end(); ++i)
			{
				socket.print( ( *i ).c_str() );
			}
			messageQ.erase(messageQ.begin(), messageQ.end());
			store_size = 0;
			succeeded = true;
			break;
		} else TCP_LOGGER_DEBUG_FLASH_BAD;
		delay(TCP_LOGGER_DELAY_BETWEEN_RECONNECT_ATTEMPTS);
		number_of_attempts--;
	}
	return succeeded;
}

TCPLogger::~TCPLogger() {
	log("\nDebugger disconnected\n");
	socket.stop();
}
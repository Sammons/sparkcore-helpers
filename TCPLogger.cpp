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
	if (connect()) log("Debugger connected");
}
void TCPLogger::log( char* logText ) {
	if ( socket.connected() ) socket.print( logText );
	else if ( connect() ) socket.print( logText );
}
void TCPLogger::log( char logChar ) {
	if ( socket.connected() ) socket.print( logChar );
	else if ( connect() ) socket.print( logChar );
}
bool TCPLogger::connect() {
	int number_of_attempts = MAX_RECONNECT_ATTEMPTS;
	while ( number_of_attempts > 0 ) {
		if (host != NULL) {
			if (socket.connect(host, port)) {
				TCP_LOGGER_DEBUG_FLASH_GOOD;
				return true;
			}
		}
		else {
			if(socket.connect(server, port)) {
				TCP_LOGGER_DEBUG_FLASH_GOOD;
				return true;
			}
		}
		delay(DELAY_BETWEEN_RECONNECT_ATTEMPTS);
		number_of_attempts--;
	}
	/* failed to connect */
	TCP_LOGGER_DEBUG_FLASH_BAD;
	return false;
}

TCPLogger::~TCPLogger() {
	log("Debugger disconnected");
	socket.stop();
}
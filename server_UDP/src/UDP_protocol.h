/*
 * UDP_protocol.h
 *
 *  Created on: 11 dic 2024
 *      Author: Linda Germinario
 */

#ifndef UDP_PROTOCOL_H_INCLUDED
#define UDP_PROTOCOL_H_INCLUDED

#if defined WIN32
#include <winsock.h>
#else
#include <sys/socket.h>
#include <arps/inet.h>
#include <unistd.h>
#include <netdb.h>
#endif

#define PORT 48000		// server port
#define BUFFER_SIZE 255

void ErrorHandler(char *error);
void ClearWinSock();

#endif /* UDP_PROTOCOL_H_INCLUDED */

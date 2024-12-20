/*
 * UDP_protocol.h
 *
 *  Created on: 17 dic 2024
 *      Author: Ennio Lo Buono
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

#define PORT 48000
#define BUFFER_SIZE 255
#define INPUT_SIZE 64
#define PROTO_IP "passwdgen.uniba.it"	// IP to convert into "127.0.0.1"

void ErrorHandler(char *error);
void ClearWinSock();

#endif // UDP_PROTOCOL_H_INCLUDED

/*
 * main.c
 *
 *  Created on: 11 dic 2024
 *      Author: Linda Germinario
 */

#include "UDP_PROTOCOL.h"
#include "password_generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

int main() {
	// basic API startup for winsock if the OS is Windows
	#if defined WIN32
		WSADATA wsaData;

		int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);

		if(iResult != 0) {
			printf("WSAStartup failed\n");
			return -1;
		}
	#endif

	int my_socket;
	struct sockaddr_in serverAddress; // structure containing the address to this machine
	char serverMessage[BUFFER_SIZE]; // buffer containing the string RECEIVED by the server
	int serverMessageSize;

	struct sockaddr_in clientAddress; // structure containing the address to the client machine connected to the server
	int cliAddrLen;

	char clientMessage[BUFFER_SIZE]; // buffer containing the string TO SEND to the client
	int clientMessageSize;

	if((my_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
		ErrorHandler("socket creation failed");
		ClearWinSock();
		return -1;
	}

	// define the server address to pass information and connect to clients
	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(PORT);
	serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

	if((bind(my_socket, (struct sockaddr*)&serverAddress, sizeof(serverAddress))) < 0) {
		ErrorHandler("Bind() failed");
		closesocket(my_socket);
		ClearWinSock();
		return -1;
	}

	fprintf(stdout, "waiting for a client to connect...\n");
	int len;
	char sign;

	// server loop NEVER STOPS
	while(true) {
		// cleanup of the buffer, happening after every interaction with a client
		memset(serverMessage, '\0', BUFFER_SIZE);
		memset(clientMessage, '\0', BUFFER_SIZE);

		cliAddrLen = sizeof(clientAddress);

		// receive a message from the client, trough the clientAddress and stored into the serverMessage
		serverMessageSize = recvfrom(my_socket, serverMessage, BUFFER_SIZE, 0, (struct sockaddr*)&clientAddress, &cliAddrLen);

		if(serverMessageSize < 0) {
			ErrorHandler("recvfrom() failed");
			continue;
		}

		// echo the client information to stdout, as well as the received message
		printf("New request from %s:%d\n", inet_ntoa(clientAddress.sin_addr), ntohs(clientAddress.sin_port));
		printf("received: %s\n", serverMessage);

		// parse the received message into the expected "sign(char)" and "len(int)"
		set_generation(&sign, &len, serverMessage);

		// the clientMessage (to send to the client) is changed based off of the generation of the password
		password_generation(clientMessage, sign, len);

		// null terminate the generated password
		clientMessage[strcspn(clientMessage, "\n")] = '\0';

		// echo the message that's about to be sent
		printf("generated: %s\n", clientMessage);

		clientMessageSize = strlen(clientMessage);

		// send the clientMessage to the client
		if(sendto(my_socket, clientMessage, clientMessageSize, 0, (struct sockaddr*)&clientAddress, sizeof(clientAddress)) != clientMessageSize) {
			ErrorHandler("Sent a different number of bytes than expected");
		}
	}

	printf("end server life\n");
	return 0;
}

void ErrorHandler(char *error) {
	printf("%s\n", error);
}

void ClearWinSock() {
	#if defined WIN32
		WSACleanup();
	#endif
}


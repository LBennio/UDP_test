/*
 * main.c
 *
 *  Created on: 17 dic 2024
 *      Author: Ennio Lo Buono
 */

#include "UDP_protocol.h"
#include "checks.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void get_help();

void ErrorHandler(char *error) {
	printf("%s\n", error);
}

void ClearWinSock() {
	#if defined WIN32
		WSACleanup();
 	#endif // defined
}

int main(int argc, char** argv) {

	// basic API startup for winsock if the OS is Windows
	#if defined WIN32
		WSADATA wsaData;
		int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);

		if(iResult != 0) {
			printf("error at startup()\n");
			return -1;
		}
	#endif

	int clientSocket;
	struct sockaddr_in serverAddress; // structure containing information about the server's address
	struct sockaddr_in clientAddress; // structure containing information about this address

	int serverAddressSize;
	int clientAddressSize;

	char message[BUFFER_SIZE]; // buffer for the message to be received from the server
	int messageSize;

	struct hostent* host;

	host = gethostbyname(PROTO_IP); // conversion from a name to a host structure

	if(host == NULL) {
		printf("ip %s resulted in an empty address\n", PROTO_IP);
		ClearWinSock();
		return -1;
	}

	char input[INPUT_SIZE]; // string for the user input to send to the server

	// creation of the socket
	if((clientSocket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
		ErrorHandler("socket creation failed");
		ClearWinSock();
		return -1;
	}

	// while loop continuing until the letter 'q' is pressed from the user
	do{
		// cleanup of the buffer, happening after every interaction with the server
		memset(input, '\0', INPUT_SIZE);
		memset(message, '\0', BUFFER_SIZE);

		printf("insert an input format 'format[SPACE]length': ");
		gets(input);
		input[strcspn(input, "\n")] = '\0';

		// loop to check the user input is of correct format
		while(!string_check(input)) {
			printf("invalid input %s\n", input);
			printf("insert an input format 'format[SPACE]length': ");
			gets(input);
		}

		// command to print on stdout the help menu
		if(strcmp(input, "h") == 0) {
			get_help();
			continue;
		}

		// quits the application, exiting the loop
		if(strcmp(input, "q") == 0) {
			continue;
		}

		// echo of user input
		printf("input: %s\n", input);

		// definition of the server address to send information to
		memset(&serverAddress, 0, sizeof(serverAddress));
		serverAddress.sin_family = AF_INET;
		serverAddress.sin_port = htons(PORT);
		serverAddress.sin_addr = *((struct in_addr*)host->h_addr_list[0]); // host->h_addr_list contains a list of available addresses

		serverAddressSize = sizeof(serverAddress);

		// echo of the server address we're about to send datagrams to
		printf("server address found: %s\n", inet_ntoa(serverAddress.sin_addr));

		// send the input to the server address, repeat the loop for a new input if the operation didn't go as expected
		if(sendto(clientSocket, input, sizeof(input), 0, (struct sockaddr*)&serverAddress, serverAddressSize) != sizeof(input)) {
			ErrorHandler("sendto() sent a different number o bytes than expected");
			continue;
		}

		clientAddressSize = sizeof(clientAddress);

		// receive the response from the server
		messageSize = recvfrom(clientSocket, message, BUFFER_SIZE, 0, (struct sockaddr*)&clientAddress, &clientAddressSize);

		if(messageSize == -1) {
			ErrorHandler("recvfrom(failed)");
			continue;
		}

		printf("received: %s\n", message);
	} while(strcmp(input, "q") != 0);

	return 0;
}

void get_help() {
	printf("Password Generator Help Menu\n");
	printf("Commands:\n");
	printf(" h        : show this help menu\n");
    printf(" n LENGTH : generate numeric password (digits only)\n");
    printf(" a LENGTH : generate alphabetic password (lowercase letters)\n");
	printf(" m LENGTH : generate mixed password (lowercase letters and numbers)\n");
    printf(" s LENGTH : generate secure password (uppercase, lowercase, numbers, symbols)\n");
    printf(" u LENGTH : generate unambiguous secure password (no similar-looking characters)\n");
    printf(" q        : quit application\n\n");
    printf(" LENGTH must be between 6 and 32 characters\n\n");
    printf(" Ambiguous characters excluded in 'u' option:\n");
    printf(" 0 O o (zero and letters O)\n");
    printf(" 1 l I i (one and letters l, I)\n");
    printf(" 2 Z z (two and letter Z)\n");
    printf(" 5 S s (five and letter S)\n");
    printf(" 8 B (eight and letter B)\n");
}

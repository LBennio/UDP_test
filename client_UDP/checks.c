/*
 * checks.c
 *
 *  Created on: 17 dic 2024
 *      Author: Ennio Lo Buono
 */


#include "checks.h"

bool type_check(char *str) {
	// check that the token is among the allowed options (n, m, a, s, u)
	if(strcmp(str, "n") == 0 ||
	   strcmp(str, "m") == 0 ||
	   strcmp(str, "a") == 0 ||
	   strcmp(str, "s") == 0 ||
	   strcmp(str, "u") == 0) {

		return true; // return true if it is allowed
	}

	return false; // return false if it is not allowed
}

bool is_number(const char *str) {
	while(*str) { // go trough every character part of the number

		if(!isdigit(*str)) { // if ANY of the character is not a digit, return false
			return false;
		}

		str++;
	}

	return true;  // if all characters are a digit, return true;
}

bool num_check(char *str) {
	if(!is_number(str)) { // if the token is NOT a string of digits (so a number), return false
		return false;
	}

	int num = atoi(str); // convert to a number

	return (num >= MIN_INT && num <= MAX_INT);  // return true if the integer taken from the string is between the allowed options (6 - 32)
}

bool string_check(const char *str) {
	char temp_str[MAX_STR];
	strcpy(temp_str, str); // copy the content of the string input in a temporary string

	// if the string is q or H, both being valid characters, return true
	if(strcmp(temp_str, "q") == 0 || strcmp(temp_str, "h") == 0) {
		return true;
	}

	// get the first part of the string, supposedly a character
	char *token = strtok(temp_str, " ");

	if(token == NULL) {
		return false;
	}

	unsigned int i = 1;

	while((i <= 2) && (token != NULL)) { // check tokens, for which they have to be two and present
		switch(i) {
			case 1:			// control for the first token, supposedly a 	character
				if(!type_check(token)) {	// if the type is not allowed, return false
					printf("invalid type %s\n", token);
					return false;
				}

				token = strtok(NULL, "");	// get the second part of the input, supposedly a number

				if(token == NULL) {
					return false;
				}
				break;

			case 2:
				if(!num_check(token)) {		// if the token is not a number or not withing limits, return false
					printf("invalid length %s\n", token);
					return false;
				}
				break;
		}

		i++;
	}

	return true;
}



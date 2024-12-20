/*
 * password_generator.h
 *
 *  Created on: 11 dic 2024
 *      Author: Linda Germinario
 */

#ifndef PASSWORD_GENERATOR_H_
#define PASSWORD_GENERATOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void set_generation(char *type, int *len, char *str_in); // Function to parse input string and extract the password type and length
void password_generation(char *pass, char type, int length); // funtion to select the option derived from the type extracted with the function "set_generation"
void generate_numeric(char *pass, int length); // Function to generate a numeric-only password
void generate_alpha(char *pass, int length);  // Function to generate an alphabetic-only password (lowercase letters only)
void generate_mixed(char *pass, int length); // Function to generate a mixed alphanumeric password
void generate_secure(char *pass, int length); // Function to generate a secure password with uppercase, lowercase, digits, and symbols
void generate_unambiguous(char *pass, int length); // function to generate a password with no ambiguous characters: 0, O ,o | 1, i, l, I | 5, S, s | 8, B

#endif /* PASSWORD_GENERATOR_H_ */

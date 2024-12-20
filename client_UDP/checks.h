/*
 * checks.h
 *
 *  Created on: 17 dic 2024
 *      Author: Ennio Lo Buono
 */

#ifndef CHECKS_H_
#define CHECKS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX_INT 32
#define MIN_INT 6

#define MAX_STR 30
#define MIN_STR 3

bool string_check(const char *str); // function that checks if a string is correct by program criteria
bool type_check(char *str); // function that checks if str is among the allowed strings

#endif /* CHECKS_H_ */

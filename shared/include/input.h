/*
 * Various functions using read and stdio for handling reads and buffers 
 * Written by: James Ross
 */

#ifndef _INPUT_H_
#define _INPUT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#define RESET_BFPL 1
#define KEEP_BFPL  0

ssize_t read_input(int fd, char *buff, int nbyte);

int parse_buff(int fd, char *buff, int reset_flag, char delim);

void clear_stdin();

char* fgets_input(size_t nbyte, FILE *fp);
#endif

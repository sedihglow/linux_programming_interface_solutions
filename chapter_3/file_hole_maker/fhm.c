/*
 * Filename: fhm.c
 *
 * Written by: James Ross
 */

#include "fhm.h"

#define BSIZE 512

void handle_input(int fd)
{
    char buff[BSIZE] = {'\0'};
    int rbytes;
    int len;

    do {
        rbytes = read_input(STDIN_FILENO, buff, BSIZE);
        if (rbytes == FAILURE)
            errExit("Failure to read stdin");

        len = strlen(buff);

        write(fd, buff, len);
    } while(rbytes != 0);
}

void create_hole(int fd, int hsize)
{
    lseek(fd, hsize, SEEK_END);
}

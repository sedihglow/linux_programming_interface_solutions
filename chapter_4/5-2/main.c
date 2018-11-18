/*
 * Read readme.
 * filename: main.c
 */

#include "sedhead.h"
#include "err_handle.h"

#define MSG "NewText"

int main(int argc, char *argv[])
{
    int fd;
    if (argc != 2)
        errnumExit(EINVAL, "Invalid commands. $cmd path");


    fd = open(argv[1], O_APPEND | O_WRONLY);
    if (fd == FAILURE)
        errExit("Failed to open the file");

    lseek(fd, 0, SEEK_SET);
    if (errno)
        errExit("seek failure");

    write(fd, MSG, sizeof(MSG)-1);
    if (errno)
        errExit("Write failure");

    exit(EXIT_SUCCESS);
}

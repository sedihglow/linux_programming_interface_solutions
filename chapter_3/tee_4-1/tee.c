/*
 *
 * Written by: James Ross
 */

#include "tee.h"

#define IN_SIZE 512

int parse_open(int argc, char *argv[]) 
{
    int opt;
    int fd;

    if (argc > 3)
        errnumExit(EINVAL, "Too many arguments");

    if (argc == 2) {
        printf("in write\n");
        fd = open(argv[1], W_FLAGS, MODES); 
    } else if (argc == 1) { /* no file provided */
        printf("in stdout\n");
        fd = STDOUT_FILENO;
    }

    while((opt = getopt(argc, argv, "a:")) != -1) {
        switch(opt) {
            case 'a':
                printf("in append\n");
                fd = open(optarg, APPEND_FLAGS, MODES);
                break;
            default:
                errnumExit(EINVAL,"invalid use of arguments. $cmd -a [file]");
        }
    }

    return fd;
}


void my_tee(int fd)
{
    char buff[IN_SIZE] = {'\0'};
    size_t len;
    int rbytes;
    
    do {
        /* Reads IN_SIZE-1 and adds null to the end */
        rbytes = read_input(STDIN_FILENO, buff, IN_SIZE);
        if (rbytes == FAILURE)
            errExit("my_tee: Failure to read.");

        len = strlen(buff);
       
        write(fd, buff, len);

        if (fd != STDOUT_FILENO)
            write(STDOUT_FILENO, buff, len);
    } while(rbytes != 0);

}

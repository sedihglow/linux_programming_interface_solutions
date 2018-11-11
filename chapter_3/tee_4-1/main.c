#include "tee.h"

int main(int argc, char *argv[])
{
    int fd;

    fd = parse_open(argc, argv);
    if (fd == FAILURE)
        errExit("Failed to open file");

    my_tee(fd);

    exit(EXIT_SUCCESS);
}

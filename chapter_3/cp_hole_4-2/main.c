/*
 * cp that copies file holes
 *
 * Written by: James Ross
 */
#include "sedhead.h"
#include "err_handle.h"

#define MODES   S_IRUSR | S_IWUSR 
#define IN_BUFF 100

static void copy_file(int src_fd, int dest_fd)
{
    ssize_t rbytes;
    char buff[IN_BUFF];
    do
    {
        rbytes = read(src_fd, buff, IN_BUFF);
        if (rbytes == FAILURE)
            errExit("Failure to read src");

        write(dest_fd, buff, rbytes);
        if (errno)
            errExit("Failure to write");
    } while (rbytes != 0);
}


int main(int argc, char *argv[])
{
    int src_fd;
    int dest_fd;

    if (argc > 3)
        errnumExit(EINVAL, "too many arguments");

    if (argc < 3)
        errnumExit(EINVAL, "too few arguments");

    src_fd = open(argv[1], O_RDONLY);
    if (src_fd == FAILURE)
        errExit("Failed to open file source");

    dest_fd = open(argv[2], O_WRONLY | O_CREAT, MODES);
    if (dest_fd == FAILURE)
        errExit("Failed to open file destination");

    copy_file(src_fd, dest_fd);

    close(src_fd);
    close(dest_fd);
    exit(EXIT_SUCCESS);
}

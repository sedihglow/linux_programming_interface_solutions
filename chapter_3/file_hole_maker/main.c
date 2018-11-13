/*
 *
 * Creates a file with file holes
 *
 */
    
#include "fhm.h"

/* $cmd -s [hole size] -p [file path] */
int main(int argc, char *argv[])
{
    int opt;
    int hsize = DFLT_HSIZE; /* hole size */
    int fd;

    if (argc > 5)
        errnumExit(EINVAL,"Too many arguments");

    if (argc < 3)
        errnumExit(EINVAL,"Too few arguments");

    while ((opt = getopt(argc, argv, "s:p:")) != -1) {
        switch(opt) {
        case 's':
            hsize = conv_int(optarg, 0, "hsize");
            break;
        case 'p':
            fd = open(optarg, W_FLAGS, MODES);
            if (fd == -1)
                errExit("Failure to open file");
            break;
        default:
            errnumExit(EINVAL,"$cmd -s [hole size] -p [file path] ");
        }
    }
    
    printf("Input text for new file\n");
    handle_input(fd);
    create_hole(fd, hsize);
    printf("\nInput text for after the hole\n");
    handle_input(fd);
    
    printf("File with %d size hole has been created\n", hsize);

    exit(EXIT_SUCCESS);
}

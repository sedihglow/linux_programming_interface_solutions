#include "tee.h"

int main(int argc, char *argv[])
{
    int opt;
    int fd;
    int flag;

    if (argc > 3)
        errnumExit(EINVAL, "Too many arguments");
   
    while((opt = getopt(argc, argv, "a:")) != -1) {
        switch(opt) {
            case 'a':
                flag = APPEND;
                fd = open(optarg, APPEND_FLAGS, MODES);
                break;
            default:
                errnumExit(EINVAL,"invalid use of arguments. $cmd -a [file]");
        }
    }

    if (argc == 2) {
        flag = TRUNC_W;
        fd = open(argv[1], W_FLAGS, MODES); 
    } else { /* no file provided */
        flag = TO_STDOUT;
        fd = STDOUT_FILENO;
    }

    my_tee(fd, flag);

    exit(EXIT_SUCCESS);
}

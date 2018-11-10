/*
 * Various functions using read and stdio for handling reads and buffers 
 * Written by: James Ross
 */

#include "input.h"

/*
 * Uses the read() system call to read from the given file descriptor.
 * Result of the read is placed in the provided buffer.
 * nbyte is the size of the buffer.
 *
 * Reads nbyte-1 and places a '\0' value at end of the buffer
 *
 * Returns -1 on error, errno is set by the read system call
 */
ssize_t read_input(int fd, char *buff, int nbyte)
{
    ssize_t bytes_read;

    --nbyte;
    bytes_read = read(fd, buff, nbyte);

    if (bytes_read < nbyte)
        buff[bytes_read] = '\0';
    else
        buff[nbyte] = '\0';

    return bytes_read;
}

/* clears the input buffer using variable char ch; and getchar ().*/
void clear_stdin()
{
    char CH;
    while((CH = getchar()) != '\n' && CH != EOF);
} /* end CLEAR_STDIN */

char* fgets_input(size_t nbyte, FILE *fp)
{
    size_t len;
    char *input;
    char *res;

    assert(fp);

    input = calloc(nbyte, sizeof(char));
    if (!input)
        return NULL;

    res = fgets(input, nbyte, fp); 
    if (!res) { /* fgets returned nothing read */
        free(input);
        return NULL;
    }
    
    /* replace newline with '\0', clearing STDIN if required */
    len = strlen(input) - 1;
    if(input[len] == '\n')
        input[len] = '\0';
    else
        clear_stdin();

    /* allocate res to smallest ammount required for string */
    len = strlen(input) + 1; 
    res = calloc(len, sizeof(char));
    if (!res) {
        free(input);
        return NULL;
    }
    
    /* copy contents of input into result */
    strncpy(res, input, len);
    free(input);

    return res;
} /* end lineInput */

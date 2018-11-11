/*
 * 
 *
 * Written by: James ross
 */

#include "../../shared/include/sedhead.h"
#include "../../shared/include/err_handle.h"
#include "../../shared/include/input.h"

#define W_FLAGS O_CREAT | O_WRONLY | O_TRUNC
#define MODES   S_IRUSR | S_IWUSR 

#define APPEND_FLAGS O_CREAT | O_APPEND | O_WRONLY

void my_tee(int fd);
int parse_open(int argc, char *argv[]);

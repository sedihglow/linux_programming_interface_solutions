/*
 * Filename: fhm.h
 *
 * Written by: James Ross
 */

#include "../../shared/include/sedhead.h"
#include "../../shared/include/err_handle.h"
#include "../../shared/include/input.h"
#include "../../shared/include/convNum.h"

#define DFLT_HSIZE 100
#define W_FLAGS O_CREAT | O_WRONLY | O_TRUNC
#define MODES   S_IRUSR | S_IWUSR 

void handle_input(int fd);
void create_hole(int fd, int hsize);

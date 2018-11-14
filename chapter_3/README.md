**Exercise 4-1**
The tee command reads its standard input until EOF, writing a copy of the input 
to standard output and to the file named in its  command line argument.
Implement tee using system calls. By default, tee overwrites any existing file 
with the given name. Implement the -a command line option which causes tee to
append text to theend of a file if it already exists.

**Exercise 4-1**
Write a program like cp that, when used to copy a regular file that contains
holes, aslo creates corresponding holes in the target file.

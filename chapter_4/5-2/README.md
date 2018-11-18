*** Exercise 5-2 ***

wirte a program that opens an existing file for writing with O+APPEND flag, and
then seeks to the begining of the file befor writing some data.
Where does the data appear in the file? Why?


The data appears in the file at the end of the file since the file descriptor
was opened with O_APPEND causing the write system call to ignore the file offset.

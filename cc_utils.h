#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

void do_input_flush();
char *fget_string(char *str, int n);
void read_char(const char *filename, char *message);

// I got this code from : https://github.com/libressl-portable/openbsd/blob/master/src/lib/string/
size_t strlcpy(char * __restrict dst, const char *__restrict src, size_t dsize);

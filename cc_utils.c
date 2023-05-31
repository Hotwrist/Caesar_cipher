#include "cc_utils.h"

// The do_input_flush() function
// It takes no parameter and helps to flush or clear the remaining unwanted inputs in the buffer
void do_input_flush() 
{    
    while ((getchar()) != '\n') continue;
}

/* The fget_string() function
 
	NOTE: It's a string input handling function that makes use of fgets(). I got the function from 
	'Stephen Prata' book: C PRIMER PLUS, 6th Edition, Chapter 11, line 461. With my own modification.
	
	It takes in 2 params:
	@str and @n
	 
	@str: This is the variable where the users' input will be written into.
	@n: this is the length of @str. ie. the required length of input needed from the user.
	
	It reads users' input and returns a string of type 'char*'.
*/
char *fget_string(char *str, int n)
{
	char *ret_val;
	int i = 0;
	
	ret_val = fgets(str, n, stdin);
	
	if(ret_val) // i.e ret_val != NULL
	{
		while(str[i] != '\n' && str[i] != '\0') i++;
		
		// if new line, discard it and add a null terminator there.
		if(str[i] == '\n')
			str[i] = '\0';
			
		else // flush the remaining input in buffer.
			do_input_flush();
	}
	
	return ret_val;
}

// Read the encrypted or decrypted message from the file character by character
// into @message.
void read_char(const char* filename, char *message) 
{
    // We need to open the file for reading.
    FILE *fp = fopen(filename, "r");
    
    if(fp == NULL)
    {
		fprintf(stderr, "\033[1;31m\nERROR: The filename \'(%s)\' does not exist for reading\033[0m", filename);
		exit(EXIT_FAILURE);
	}
    
    int ch, index = 0;
    
    while((ch = getc(fp)) != EOF)
    {
			message[index] = ch;
			++index;
	}
	
	// Subtracting 1 from the current position to remove EOF inserted there.
	message[index - 1] = '\0';
	
	if(fclose(fp) != 0)
	{
		fprintf(stderr, "Error in closing file\n");
		exit(EXIT_FAILURE);
	}
}

/*
 * Copy string src to buffer dst of size dsize. At most dsize-1
 * chars will be copied. Always NUL terminates (unless dsize == 0).
 * Returns strlen(src); if retval >= dsize, truncation occured.
 */
size_t strlcpy(char * __restrict dst, const char *__restrict src, size_t dsize)
{
	const char *osrc = src;
	size_t nleft = dsize;
	
	/* Copy as many bytes as will fit. */
	if(nleft != 0)
	{
		while(--nleft != 0)
		{
			if((*dst++ = *src++) == '\0')
				break;
		}
	}
	
	/* Not enough room in dst, add NUL and traverse rest of src. */
	if(nleft == 0)
	{
		if(dsize != 0)
			*dst = '\0';
		while(*src++)
			;
	}
	
	return(src - osrc - 1); /* count does not include NUL */
}

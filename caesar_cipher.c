/* Copyright(c) 2023 Odey John Ebinyi
*  All Rights Reserved
* 
*  Description: This program's goal is to encrypt/decrypt Caesar Ciphers
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "cc_utils.h"
#include <stdlib.h> // for exit() function
#include <unistd.h> // for sleep() function

// Length of message
#define MSG_BUFF 800

// Length of filename
#define FILENAME_LENGTH 30

// This function encrypts each character in the message using 
// the key parametre.
char encryptor(char ch, unsigned int *key)
{			
	// Check for valid characters
	if(isalnum(ch))
	{
		// Lowercase letters
		if(islower(ch)) ch = (ch - 'a' + *key) % 26 + 'a';
		
		// Uppercase letters
		if(isupper(ch)) ch = (ch - 'A' + *key) % 26 + 'A';
		
		// Numbers
		if(isdigit(ch)) ch = (ch - '0' + *key) % 10 + '0';
	}
	
	// Invalid characters
	else
	{
		fprintf(stderr, "Invalid Character!");
		exit(EXIT_FAILURE);
	}
	
	return ch;
}

// This function decrypts each character in the message using 
// the key parametre.
char decryptor(char ch, unsigned int *key)
{
	// Check for valid characters
	if(isalnum(ch))
	{
		// Lowercase letters
		if(islower(ch)) ch = (ch - 'a' - *key + 26) % 26 + 'a';
		
		// Uppercase letters
		if(isupper(ch)) ch = (ch - 'A' - *key + 26) % 26 + 'A';
		
		// Numbers
		if(isdigit(ch)) ch = (ch - '0' - *key + 10) % 10 + '0';	
	}
	// Invalid characters
	else
	{
		fprintf(stderr, "Invalid Encrypted Message!");
		exit(EXIT_FAILURE);
	}	
	
	return ch;
}

// This function is responsible for encrypting the message.
// It works in two ways. A user can either supply a file
// containing the message to be encrypted OR enter the message
// from the command line.
void encrypt_message(int argc, const char *filename)
{
	unsigned int key;
	
	// User wants to enter the message manually from the command line.
	if(argc <= 1)
	{
		char message[MSG_BUFF];
		char ch;
		
		printf("Enter a message to encrypt (Limit: %d Characters): ", MSG_BUFF);
		fget_string(message, MSG_BUFF);
		
		printf("Enter the Key: ");
		scanf("%i", &key);
		
		do_input_flush();
		
		// Iterate through all the characters
		for(int i = 0; message[i] != '\0'; ++i)
		{
			ch = message[i];
			
			// Space characters: ' ', \t, \n, \f, \r
			if(isspace(ch)) 
			{
				++i;
				ch = message[i];
			}
			
			message[i] = encryptor(ch, &key);	// Adding returned encoded character
		}
		
		printf("Encrypted Message: %s\n", message);
	}
	
	// User has the file containing the message to be encrypted.
	else
	{
		char message[MSG_BUFF], ch;
	
		printf("Enter the Key: ");
		scanf("%i", &key);

		do_input_flush();
		
		read_char(filename, message);
		
		for(int i=0; message[i] != '\0'; ++i)
		{
			ch = message[i];

			// Space characters: ' ', \t, \n, \f, \r
			if(isspace(ch)) 
			{
				++i;
				ch = message[i];
			}
			
			message[i] = encryptor(ch, &key);	// Adding returned encoded character
		}
		printf("Encrypted Message: %s\n", message);
	}
}


// This function is responsible for decrypting the message.
// It works in two ways. A user can either supply a file
// containing the message to be decrypted OR enter the message
// from the command line.
void decrypt_message(int argc, const char *filename)
{
	unsigned int key;
			
	// User wants to enter the message manually from the command line.
	if(argc <= 1)
	{
		char encrypted_message[MSG_BUFF];
		char ch;
		
		printf("Enter a message to decrypt (Limit: %d Characters): ", MSG_BUFF);
		fget_string(encrypted_message, MSG_BUFF);
		
		printf("Enter the Key: ");
		scanf("%i", &key);

		do_input_flush();
		
		// Iterate through all the characters
		for(int i = 0; encrypted_message[i] != '\0'; ++i)
		{
			ch = encrypted_message[i];	
			
			// Space characters: ' ', \t, \n, \f, \r
			if(isspace(ch)) 
			{
				++i;
				ch = encrypted_message[i];
			}	
			
			encrypted_message[i] = decryptor(ch, &key); 	// Adding returned decoded character
		}
		
		printf("Decrypted Message: %s\n", encrypted_message);
	}
	
	// User has a file containing the encrypted message.
	else
	{
		char message[MSG_BUFF], ch;
	
		printf("Enter the Key: ");
		scanf("%i", &key);

		do_input_flush();
		
		read_char(filename, message);
		
		for(int i=0; message[i] != '\0'; ++i)
		{
			ch = message[i];

			// Space characters: ' ', \t, \n, \f, \r
			if(isspace(ch)) 
			{
				++i;
				ch = message[i];
			}
			
			message[i] = decryptor(ch, &key);	// Adding returned encoded character

		}
		
		printf("Decrypted Message: %s\n", message);
	}
}

int main(int argc, char **argv)
{
	system("clear");
	printf("\033[1;32m\n\t\t\tCAESAR CIPHER\033[0m\n");
	
	const char *filename = argv[1];
	char reply;
	
	while(true)
	{
		printf("Would you like to encrypt or decrypt a message ? (e/d): ");
		reply = getchar();

		if(reply != 'e' && reply != 'd')
		{
			fprintf(stderr, "ERROR: Incorrect reply!!\n");
			do_input_flush();
			continue;
		}
	
		// Clear the remaining input in the buffer.
		do_input_flush();
		
		break;
    }
    
    switch(reply)
    {
        // User wants to encrypt a message using Caesar Cipher
        case 'e':
		encrypt_message(argc, filename);
            break;
            
        // User wants to decrypt a message using Caesar Cipher
        case 'd':
          	decrypt_message(argc, filename);
            break;
    }
}

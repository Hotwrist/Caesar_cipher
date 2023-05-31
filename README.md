# Caesar_cipher
A program that encrypt/decrypts a message using Caesar cipher.
You can give it a plain text file for it to encrypt and an encrypted file for it to decrypt.

# Program Compilation
gcc caesar_cipher.c cc_utils.c -o caesar_cipher.o

# Program Execution
The program runs in 2 mode:
(1) User supplies the plain text/encrypted message using the command line: ./caesar_cipher.o
(2) User gives the program a file containing a plain text/encrypted message.  ./caesar_cipher test.txt

# NOTE: 
Currently, the program does not support fullstops and other punctuation marks in the English Language like, comma, semi-colon, etc.


//xor.c
//Drake Wheeler
//10-11-2024
//This program encrpyts/decrypts files redricted into it buy xoring the data with the default key or a key string entered as a command line option argument.
//Then it writes out the encrypted/decrytped data. 

#include <unistd.h> //for read(), write(), getopt(), etc..
#include <stdio.h> //for input output functions
#include <stdlib.h> //for general functions like exit()
#include <string.h> //for string operations

#define OPTIONS "k:" //comand lines option

#ifndef FALSE
# define FALSE 0
#endif // FALSE
#ifndef TRUE
# define TRUE 1
#endif // TRUE
#define BUF_SIZE 50000

//used to print helpful debug statements
#ifdef NOISY_DEBUG
# define NOISY_DEBUG_PRINT fprintf(stderr, "%s %s %d\n", __FILE__, __func__, __LINE__)
#else // NOISY_DEBUG
# define NOISY_DEBUG_PRINT
#endif // NOISY_DEBUG
									 

int main(int argc, char* argv[])
{
	char* key = "Xerographic"; //defualt key
	char* users_text; //to hold user input
	char buffer[BUF_SIZE]; //buffer to hold data file
	ssize_t bytes_read; //to hold the number of bytes in user input
	size_t key_len; //to hold the number of characters in the key string


	{
		int opt = 0; //to hold command line option characters

		NOISY_DEBUG_PRINT;
		//parse the command line for option k
		while ((opt = getopt(argc, argv, OPTIONS)) != -1)
		{
			switch (opt)
			{
				case 'k':
					if (key == NULL || optarg[0] == '\0')
					{
						fprintf(stderr, "Error: -k option requires a key\n");
						exit(EXIT_FAILURE);
					}

					key = optarg; //set key with user's input
					break;
				default:
					break;
			}
		}
	}

	key_len = strlen(key); //set length of key


	//stores input text file in buffer and the number of bytes read in bytes_read
	bytes_read = read(STDIN_FILENO, buffer, BUF_SIZE); 

	//check for successful read
	if (bytes_read == -1)
	{
		fprintf(stderr, "Error reading input\n");
		exit(EXIT_FAILURE);
	}

	//dynamically allocate memory for users_text
	users_text = (char*)malloc((bytes_read + 1) * sizeof(char));

	//check for succesful memory allocation
	if (users_text == NULL)
	{
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	
	//copy data from buffer to users_text
	memcpy(users_text, buffer, bytes_read);

	//add null terminator to the string
	users_text[bytes_read] = '\0';

	//xor encrypt/decrypt  each text byte with corresponding key byte/element
	for (ssize_t i = 0; i < bytes_read; ++i) 
		users_text[i] ^= key[i % key_len];


	//output the encrypted/decrypted result
	write(STDOUT_FILENO, users_text, bytes_read);

	//free memory
	free(users_text);
	users_text = NULL;
	
	return 0;
}

















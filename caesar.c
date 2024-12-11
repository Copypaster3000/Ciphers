//caesar.c
//Drake Wheeler
//CS333
//Lab 2
//10-10-2024
//This program implements a caesar cipher, which encrypts or decrypts text by shifting characters. 
//It reads from standard input and outputs the modified text to standard output. The shift value 
//must be between 0 and 95, affecting all printable ASCII characters. By default, it encrypts with 
//a shift of 3. Users can specify a shift value and choose to either encrypt or decrypt the text 
//using command-line options. If neither encryption nor decryption is specified, the program defaults to encryption.

#include <stdio.h> //for input output functions
#include <stdlib.h> //for general functions like exit()
#include <string.h> //for string operations
#include <unistd.h> //for Unix-based system calls and functions like getopt() to parse the command line
#include <ctype.h>
					
#define OPTIONS "eds:" //defines the command line options

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

void encrypt(char* text, int shift); //encrypts user input by shift value
void decrypt(char* text, int shift); //decrypts user input by shift value
char* read_data(void); //reads the text file redirected to the program with stdout
									 

int main(int argc, char* argv[])
{
	int shift = 3; //set shift to default 
	int encrypt_flag = 1; //set encrypt to default
	char* text = NULL; //holds users input to be encrypted or decrypted

	{
		int opt = 0; //to hold command line option characters

		NOISY_DEBUG_PRINT;
		while ((opt = getopt(argc, argv, OPTIONS)) != -1)
		{
			switch (opt)
			{
				case 'e':
					encrypt_flag = 1; //set to encrypt
					NOISY_DEBUG_PRINT;
					break;
				case 'd':
					encrypt_flag = 0; //set to decrypt
					NOISY_DEBUG_PRINT;
					break;
				case 's':
					char* endptr;
					//converts to base-10 int, if successuful endptr will point to '\0', 
					//else it will point to first non-numeric character
					shift = strtol(optarg, &endptr, 10);

					//check if optarg is valid number
					if (*endptr != '\0')
					{
						fprintf(stderr, "Error: Shift value %s is not a valid number\n", optarg);
						exit(EXIT_FAILURE);
					}

					//check if shift value is in valid range
					if (shift < 0 || shift > 95)
					{
						fprintf(stderr, "Error: Shift value %s is not in the valid range of 0-95\n", optarg);
						exit(EXIT_FAILURE);
					}
					NOISY_DEBUG_PRINT;
					break;
				default:
					break;
			}
		}
	}

	//read data
	text = read_data();

	if (text == NULL)
	{
		fprintf(stderr, "Error: No input read\n");
		exit(EXIT_FAILURE);
	}

	//encrypts/decryptes text based on flag
	if(encrypt_flag) encrypt(text, shift); 
	else decrypt(text, shift);

	//outputs decrytped/encrytped data
	fprintf(stdout, "%s", text);

	//free alloacted memory
	free(text);
	text = NULL;


	NOISY_DEBUG_PRINT;

	return 0;	
}


//reads data file and returns it as a char*
char* read_data(void)
{
	char buffer[BUF_SIZE]; //temp buffer to hold each line
	char* text = NULL; //will point to the final result
	char* new_text = NULL; //to hold
	size_t total_size = 0; //tracks total size of string
	size_t buffer_len = 0; //holds length of current line

	NOISY_DEBUG_PRINT;

	//loop untile the end of the file
	while (fgets(buffer, BUF_SIZE, stdin) != NULL)
	{
		buffer_len = strlen(buffer); //gets length of current line

		//reallocare memory to hold the new line plus existing text
		new_text = realloc(text, total_size + buffer_len + 1);//+1 for null terminator

		if (new_text == NULL)
		{
			fprintf(stderr, "Error allocating memory");
			exit(EXIT_FAILURE);
		}

		//update the pointer with the additional memory needed for the new line
		text = new_text;
		strcpy(text + total_size, buffer); //add the new line test to the point where the presvious line ended

		total_size += buffer_len;
	}

	//null terminate string
	if (text != NULL) text[total_size] = '\0';

	return text;
}


//encrypts user's input by the shift value
void encrypt(char* input, int shift)
{
	int shifted_value = 0;
	NOISY_DEBUG_PRINT;

	
	//loop until the end of the string is reached
	for (int i = 0; input[i] != '\0'; ++i)
	{
		//only encrypt printable characters
		if (isprint(input[i]))
		{
			shifted_value = input[i] - 32 + shift;

			if (shifted_value < 0) shifted_value += 95; //adjust if negative

			input[i] = (shifted_value % 95) + 32; //shifts the current char positively within the prinitable ascii range

		}
	}
}


//decrypts user's input by the shift value
void decrypt(char* input, int shift)
{
	int shifted_value = 0;
	NOISY_DEBUG_PRINT;


	//loop until the end of the string is reached
	for (int i = 0; input[i] != '\0'; ++i)
	{

		//only encrypt printable characters
		if (isprint(input[i]))
		{
			shifted_value = input[i] - 32 - shift;

			if (shifted_value < 0) shifted_value += 95;

			input[i] = (shifted_value % 95) + 32; //shifts the current char negatively within the printable ascii range
		}
	}
}

	












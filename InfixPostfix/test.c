/* Infix/Postfix Calculator Program
** CS 343 -- Structure of Programming Languages
** Modified files: test.c, postfix.c, postfix.h (added a define)
** By Kevin Welsh and James Donley
** Released into public domain under the terms of CC0
**/

#include <stdio.h>
#include <stdlib.h>
#include "postfix.h"

// bufSize is defined in postfix.h as 50

int main()
{
	int choice = '0';
	char buffer[bufSize];
	// query choice
	puts("(1) Convert Infix to Postfix Expression");
	puts("(2) Evaluate Postfix Expression");
	puts("(3) Quit");
	while (choice != '3')
	{
		while (choice != '1' && choice != '2' && choice != '3')
		{
			printf("Enter Selection (1, 2, 3): ");
			choice = getc(stdin);
		}
		
		char * ptr;
		switch(choice)
		{
			case '1':
				// choice 1
				printf("Enter Infix Expression: ");
				// we have to repeat this twice for no apparent reason
				fgets(buffer, bufSize, stdin);
				fgets(buffer, bufSize, stdin);
				ptr = infixToPostfix(buffer);
				printf("Postfix: %s\n", ptr);
				printf("Value: %i\n", evaluatePostfix(ptr));
				free(ptr);
				break;
			case '2':
				// choice 2
				printf("Enter Postfix Expression: ");
				// we have to repeat this twice for no apparent reason
				fgets(buffer, bufSize, stdin);
				fgets(buffer, bufSize, stdin);
				printf("Value: %i\n", evaluatePostfix(buffer));
				break;
		}
		
		if (choice != '3')
		{
			choice = '0';
		}
	}
	
	return 0;
}

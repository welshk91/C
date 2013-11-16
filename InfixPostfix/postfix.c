#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "postfix.h"
#include "stack.h"

// bufSize is defined in postfix.h as 50

/* function to convert an infix to postfix */
char *infixToPostfix(char *infixStr)
{
	char * curTok;
	char copy[bufSize];
	char * answer = (char*) calloc (bufSize,sizeof(char));
	strcpy(copy, infixStr);
	*(strchr(copy, '\n')) = '\0';
	curTok = strtok(copy, " ");
	if (curTok != NULL)
	{
		strcat(answer, curTok);
		strcat(answer, " ");
		
		stack ifs;
		stackInit(&ifs);
		
		curTok = strtok(NULL, " ");
		
		while (curTok != NULL)
		{
			if (isOperand(curTok))
			{
				strcat(answer, curTok);
				strcat(answer, " ");
			}
			else if (isLeftParen(curTok))
			{
				stackPush(&ifs, curTok);
			}
			else if (isOperator(curTok))
			{
				// pop operator if top element's stack prec > input prec of curTok
				while (!stackIsEmpty(&ifs) && \
					stackPrecedence(stackPeek(&ifs)) >= inputPrecedence(curTok))
				{
					strcat(answer, stackPop(&ifs));
					strcat(answer, " ");
				}
				stackPush(&ifs, curTok);
			}
			else if (isRightParen(curTok))
			{
				while (!isLeftParen(stackPeek(&ifs)))
				{
					strcat(answer, stackPop(&ifs));
					strcat(answer, " ");
				}
				stackPop(&ifs);
			}
			
			curTok = strtok(NULL, " ");
		}
		
		while (!stackIsEmpty(&ifs))
		{
			strcat(answer, stackPop(&ifs));
			strcat(answer, " ");
		}
		
		stackDestroy(&ifs);
		return answer;
	}
	
	fputs("Error in evaluation: reached end (null string received)", stderr);
	exit(-1);
}

/* function that returns true if the string is an operator */
bool isOperator(char *str)
{
	if (*str == '+' || *str == '-' || *str == '*' || *str == '/' || \
		*str == '^' || *str == '%')
	{
		return true;
	}
	return false;
}

/* function that returns true if the string is an operand/integer */
bool isOperand(char *str)
{
	if (isdigit(*str))
	{
		return true;
	}
	return false;
}

/* function that returns true if the string is a left parenthesis */
bool isLeftParen(char *str)
{
	if (*str == '(')
	{
		return true;
	}
	return false;
}

/* function that returns true if the string is a right parenthesis */
bool isRightParen(char *str)
{
	if (*str == ')')
	{
		return true;
	}
	return false;
}

/* function that returns the stack precedence of given operator */
int stackPrecedence(char *str)
{
	switch (*str)
	{
		case '+':
			return 1;
			break;
		case '-':
			return 1;
			break;
		case '*':
			return 2;
			break;
		case '/':
			return 2;
			break;
		case '^':
			return 3;
			break;
		case '%':
			return 2;
			break;
		case '(':
			return -1;
			break;
		default:
			return -10;
	}
}

/* function that returns the input precedence of given operator */
int inputPrecedence(char *str)
{
	switch (*str)
	{
		case '+':
			return 1;
			break;
		case '-':
			return 1;
			break;
		case '*':
			return 2;
			break;
		case '/':
			return 2;
			break;
		case '^':
			return 4;
			break;
		case '%':
			return 2;
			break;
		case '(':
			return 5;
			break;
		default:
			return -10;
	}
}

/* function that evaluates a postfix expression and returns the result */
int evaluatePostfix(char *postfixStr)
{
	char * curTok;
	char copy[bufSize];
	strcpy(copy, postfixStr);
	curTok = strtok(copy, " ");
	if (curTok != NULL)
	{
		stack pfs;
		stackInit(&pfs);
		
		stackPush(&pfs, curTok);
		
		curTok = strtok(NULL, " ");
		while (curTok != NULL)
		{
			if (isOperand(curTok))
			{
				stackPush(&pfs, curTok);
			}
			else if (isOperator(curTok))
			{
				int x = atoi(stackPop(&pfs));
				int y = atoi(stackPop(&pfs));
				
				char result[10];
				sprintf (result, "%d", applyOperator(y, x, curTok));
				
				stackPush(&pfs, result);
			}
			
			curTok = strtok(NULL, " ");
		}
		
		char * temp = stackPop(&pfs);
		stackDestroy(&pfs);
		return atoi(temp);
	}
	
	fputs("Error in evaluation: reached end (null string received)", stderr);
	exit(-1);
}

/* function that performs num1 opr num2 and returns the result */
int applyOperator(int num1, int num2, char *opr)
{
	switch (*opr)
	{
		case '+':
			return num1 + num2;
			break;
		case '-':
			return num1 - num2;
			break;
		case '*':
			return num1 * num2;
			break;
		case '/':
			return num1 / num2;
			break;
		case '^':
			return pow(num1, num2);
			break;
		case '%':
			return num1 % num2;
			break;
	}
	return 0;
}

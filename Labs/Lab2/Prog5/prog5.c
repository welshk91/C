#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>

#define MAX 200

int main(void) 
{ 
	/*Variables*/
	char * cmd = NULL;
	char buffer[MAX];
	char * parsedBuff[MAX];
	int i = 0;
	pid_t pid, child;
	

	/*Grab input*/
	printf("Enter a command: \n");	
	fgets(buffer,MAX, stdin);

	/*Parse input*/
	cmd = strtok (buffer, " ,.-;");		
	while(cmd !=NULL){
		printf("%s \n", cmd);
		parsedBuff[i] = cmd;
		cmd = strtok (NULL, " ,.-;");
		i = i + 1;
	}	

	printf("Parsed Input: %s \n", parsedBuff);

    return 0; 
}

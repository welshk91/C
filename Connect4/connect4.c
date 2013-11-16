/*
Author:	Kevin Welsh
Class:	Programming Languages Section 2
Date:	February 7, 2011
Project:Program One, Connect Four
*/

/*
Instructions
Open terminal
cd into right directory
run:gcc -std=c99 connect4.c
run:./a.out size connects
example of a game:./a.out 5 3
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*methods to handle board play*/
void createBoard(int s, int b[s][s]);			//creates empty board
void printBoard(int s, int b[s][s]);			//prints board
int enterValue(int col, int p, int s, int b[s][s]);	//inserts chip

/*methods to handle winning conditions recursively*/
int hWin(int s, int b[s][s], int row, int col, int c);	//checks for horizontal win
int vWin(int s, int b[s][s], int row, int col, int c);	//checks for vertical win
int dWin1(int s, int b[s][s], int row, int col, int c);	//checks for diagnol win positive slope
int dWin2(int s, int b[s][s], int row, int col, int c);	//checks for diagnol win negative slope
int draw(int s, int b[s][s]);				//checks to see if board is full

/*variables used*/
int size;		//size of board, given by user
int connects;		//connects needed to win, given by user	
int player = 1;		//used to decided who's turn it is
int gameOver = 0;	//used to determine Game Over
int colPicked;		//used to determine column picked


int main(int argc,char *argv[])
{
	//Number of parameters is wrong
	if (argc != 3) {
		printf("Usage: Incorrect Number of Parameters\n");
		exit(1);
	}

	//handles input
	size = atoi(argv[1]);	 //size of board
	connects = atoi(argv[2]);//number of connects needed to win
	int board[size][size];	 //array used to act as the board
	
	printf("***Start Game*** \n");
	printf("Size input: %d \n", size);
	printf("Connect input: %d \n", connects);
	
	createBoard(size, board);
	printBoard(size, board);

	while(!gameOver){
		char userInput[80];
		
		printf("Player %d's turn. Choose column \n", player);
		scanf("%s",userInput);
		colPicked = atoi(userInput);
		
		/*
		checks to see if input is a valid number
		works, but decimal numbers are cut-offed
		*/
		while(!isdigit(userInput[0]) || colPicked>size || colPicked<1){
			
			printf("%s is not a valid number. Pick again \n", userInput);
			scanf("%s", userInput);
			colPicked = atoi(userInput);
		}
		
		//Flush buffer, not sure if needed but good practice when using scanf
		fflush(stdout);
		
		//Insert chip into board	
		enterValue(colPicked, player, size, board);

		printf("\n");		
		printBoard(size, board);
		
		//check for horizontal wins here
		for(int i=0; i<size; i++){
			for(int j=0; j<(size-(connects-1)); j++){	
				if(hWin(size, board, i,j,1)>=connects){
					printf("\n***Player %d wins horizontally!***\n",player);
					gameOver=1;

				}
			}
		}
		
		//check for vertical wins here
		for(int i=0; i<(size-(connects-1)); i++){
			for(int j=0; j<size; j++){	
				if(vWin(size, board, i,j,1)>=connects){
					printf("\n***Player %d wins vertically!***\n",player);
					gameOver=1;
				}
			}
		}

		//check for diagnol wins (positive slope) here
		for(int i=size; i>(size-(connects+1)); i--){
			for(int j=0; j<(size-(connects-1)); j++){	
				if(dWin1(size, board, i,j,1)>=connects){
					printf("\n***Player %d wins diagnolly!***\n",player);
					gameOver=1;
				}
			}
		}
		
		//check for diagnol wins (negative slope) here
		for(int i=0; i<(size-(connects-1)); i++){
			for(int j=0; j<(size-(connects-1)); j++){	
				if(dWin2(size, board, i,j,1)>=connects){
					printf("\n***Player %d wins diagnolly!***\n",player);
					gameOver=1;
				}
			}
		}

		//check for draw here
		if(draw(size,board)==1){
			printf("\n***DRAW***\n");
			gameOver=1;
		}		

		//Ask for rematch
		if(gameOver==1){
			printf("\n	Want to play again? (y/n)\n");
			char rematch;
			scanf("%s", &rematch);
			if(rematch=='y'||rematch=='Y'){
				printf("\n\n----------------------------\n\n");
				createBoard(size, board);
				printBoard(size, board);
				player=2;				
				gameOver=0;
			}
			else{
				gameOver=1;
			}		
	
		}
		
		//handles the players' turns
		if(player==1){
			player=2;
		}
		else if(player==2){
			player=1;
		}
		else{
			printf("!!!Something is Wrong with turns!!!");
			exit(1);
		}

	}//end of while(!gameOver)

	printf("***Game Over***\n");
	return 0;

}//end of main

/*
Function creates an empty board of size s
*/
void createBoard(int s, int b[s][s]){

	for (int i = 0; i < s; i++) {
		for (int j = 0; j < s; j++) {
			b[i][j]=0;
		}
	}

}//end of createBoard

/*
Function prints the board given
*/
void printBoard(int s, int b[s][s]){
	
	//used to display column's number
	printf("\n");
	for(int i=0;i<s;i++){
		printf("%d ",i+1);
	}
	printf("\n");

	//used to seperate column's number and the board 
	for(int i=0;i<s;i++){
		printf("--");
	}	
	printf("\n");

	for (int i = 0; i < s; i++) {
		for (int j = 0; j < s; j++) {
			printf("%d ", b[i][j]);
		}
		printf("\n");
	}

}//end of printBoard 

/*
Function takes value and looks for a spot to insert it
*/
int enterValue(int value, int p, int s, int b[s][s]){
	int count = -1;
	
	//Finds spot to insert chip
	for(int i=0;i<s;i++){
		if(b[i][value-1]==0){
			count++;
		}
	}

	//Inserts chip or says column is full
	if(count!=-1){
		printf("Inserting %d into %d,%d \n", p,count+1,value);
		b[count][value-1]=p;
		return 1;
	}

	else{ //column is full
		printf("Column is Full. Pick Again \n");
		scanf("%d", &value);
		enterValue(value, p, s, b);		
		return 0;
	}

}//end of enterValue

/*
Function recursively looks to see how many connects horizontally and returns the number of connects 
*/
int hWin(int s, int b[s][s], int row, int col, int count){
	
	if((b[row][col]!=0)&&(b[row][col]==b[row][col+1])){
		count++;
		hWin(s,b,row,col+1,count);
	}
	else{
		return count;
	}

}//end of hWin
	
/*
Function recursively looks to see how many connects vertically and returns the number of connects 
*/
int vWin(int s, int b[s][s], int row, int col, int count){

	if((b[row][col]!=0)&&(b[row][col]==b[row+1][col])){
		count++;
		vWin(s,b,row+1,col,count);
	}	
	else{
		return count;
	}
}//end of vWin

/*
Function recursively looks to see how many connects diagnolly and returns the number of connects 
*/
int dWin1(int s, int b[s][s], int row, int col, int count){

	if((b[row][col]!=0)&&(b[row][col]==b[row-1][col+1])){
		count++;
		dWin1(s,b,row-1,col+1,count);
	}	
	else{
		return count;
	}
}//end of dWin1

/*
Function recursively looks to see how many connects diagnolly and returns the number of connects 
*/
int dWin2(int s, int b[s][s], int row, int col, int count){

	if((b[row][col]!=0)&&(b[row][col]==b[row+1][col+1])){
		count++;
		dWin2(s,b,row+1,col+1,count);
	}	
	else{
		return count;
	}
}//end of dWin2

/*
Function looks to see if the board is full
*/
int draw(int s, int b[s][s]){
	int count = -1;
	
	//Looks for open spot
	for(int i=0; i<s; i++){
		for(int j=0;j<s;j++){
			if(b[i][j]==0){
				count++;
			}
		}
	}

	//count shouldn't be -1 if it found an open spot
	if(count==-1){
		//draw occured
		return 1;
	}
	else{
		//still an open slot
		return 0;	
	}
}//end of draw
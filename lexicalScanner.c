/*
 *	Authors: Tyler Stigliano, Austin Macdade
 *	Implementation of a Lexical Scanner for the language described in class
 *	Class: COP3402: System Software
 *	Professor: Dr. Euripides Montagne
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "lexicalScanner.h"

int main(){
	
	char filename[CMAX];
	printf("PL/O Lexical analyser");
	printf("Enter filename: ");

	scanf("%s", filename);
	ifp = fopen(filename, "r");
	ofp = fopen("output.txt", "w");

	if(!ifp){
		printf("Invalid file name. Program exiting");
		return;
	}

	initialize();
	
	while(currChar != EOF){
		// reads through the file until it gets to the end
	}


}


// Initializes the error array and initializes the counters
void initalize(){
	int i;

	for( i = 0; i < ERRMAX; i ++){
		errors[i] = FALSE;
	}
 
	charCount = 0; 
	lineCount = 0;
	line[0] = '\0';
}


// The idea I had for this function was to read in an line at a time and
// then trace through that line tokenizing the appropritate words
void nextCharacter(){
	
	
}



// This function will read through white space and comments
// when encountered
void skip(){
	
}
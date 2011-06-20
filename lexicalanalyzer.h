/*
 *      Authors: Tyler Stigliano, Austin Macdade
 *      Implementation of a Lexical Scanner for the language described in class
 *      Class: COP3402: System Software
 *      Professor: Dr. Euripides Montagne
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef LEXICALANALYZER_H_
#define LEXICALANALYZER_H_

// Constants
#define CMAX 12         // Maximum number of character length
#define DMAX 5          // Maximum number of digit length
#define LMAX 101        // Maximum line length
#define ERRMAX 4        // Maximum error number
#define TRUE 1
#define FALSE 0

// Token types
typedef enum    {nulsym = 1, identsym, numbersym, plussym, minussym, 
                 multsym, slashsym, oddsym, eqlsym, neqsym, lessym, leqsym, 
                 gtrsym, geqsym, lparentsym, rparentsym, commasym, 
                 semicolonsym, periodsym, becomessym, 
				 } token_type;

typedef enum { beginsym = 21, endsym, ifsym, thensym, whilesym, dosym, 
			   callsym, constsym, intsym, procsym, outsym, insym, 
			   elsesym} special_token;



struct token{
        int kind;                               // token type
        char name[CMAX+1];						// name 
		int value;								//
		int hasValue;
};

// Reserved words


char* reservedWords [] ={ "begin", "end", "if", "then", "while", "do", "call", "const",
						  "int", "proc", "out", "in", "else"};

int numReservWords = sizeof(reservedWords) / sizeof(char *);               // number of keywords

// Name of Special Symboles
char * sSymbolesName[] = {"plus", "minus", "times", "slash", "comma", "rparetn",
                          "lparent", "rbracket", "lbracket", "equal", "comman", "period",
                           "lss", "grt", "leq", "geq", "semicolon", "colon"};

int numSpecials = sizeof(sSymbolesName)/ sizeof(char *);                // number of special characters

//int numTotalSymboles = numSpecials + numKeyWords;                               // number of special characters and keywords

// Global Variables
char currChar;                  // Current character
char line[LMAX];                // Current line
int charCount;                  // Character counter
int lineCount;                  // line counter
int errors[ERRMAX];
struct token nameRec[500];
int h;

FILE* ifp, *ofp; 


// Functions
void errorFound(int type);              // Mark an error
void initialize();                              // Initialize variables
void nextCharacter();                   // Description in source file. 
void skip();                                    // Skips whitespace and comments
void getToken();								// Gets the token
void printLexemeTable();


#endif /* LEXICALANALYZER_H_ */
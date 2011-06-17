/*
 *	Authors: Tyler Stigliano, Austin Macdade
 *	Implementation of a Lexical Scanner for the language described in class
 *	Class: COP3402: System Software
 *	Professor: Dr. Euripides Montagne
 */
 
 // Constants
#define CMAX 11		// Maximum number of character length
#define DMAX 5		// Maximum number of digit length
#define LMAX 100	// Ma
#define ERRMAX 4	// Maximum error number

// Token types
typedef enum	{nulsym = 1, identsym, numbersym, plussym, minussym, 
				 multsym, slashsym, oddsym, eqsym, neqsym, lessym, leqsym, 
				 gtrsym, geqsym, lparentsym, rparentsym, commasym, 
				 semicolonsym, periodsym, becomessym, beginsym, endsym, 
				 ifsym, thensym, whilesym, dosym, callsym, constsym, intsym, 
				 procsym, outsym, insym, elsesym} token_type;

struct token{
	int kind;				// const = 1, var = 2, proc = 3
	char name[CMAX];		// name 
	int val;				// ASCII value
	int level;				// L level
	int adr;				// M address
} namerecord; 

// Reserved words
char* reservedWords [] = { "call", "begin", "end", "if", "then", 
						   "else", "while", "do", "in", "out"};

int numKeyWords = sizeof(reservedWords) / sizeof(char *);		// number of keywords

// Name of Special Symboles
char * sSymbolesName[] = {"plus", "minus", "times", "slash", "comma", "rparetn",
						 "lparent", "rbracket", "lbracket", "equal", "comman", "period",
						 " lss", "grt", "leq", "geq", "semicolon", "colon"};

int numSpecials = sizeof(sSymbolesName)/ sizeof(char *);		// number of special characters

int numTotalSymboles = numSpecials + numKeyWords;				// number of special characters and keywords

// Global Variables
char currChar;			// Current character


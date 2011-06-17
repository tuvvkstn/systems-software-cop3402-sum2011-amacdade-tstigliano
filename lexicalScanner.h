// Constants
#define CMAX 11		// Maximum number of character length
#define DMAX 5		// Maximum number of digit length
#define LMAX 100	// Maximum line length
#define ERRMAX 4	// Maximum error number
#define TRUE 1
#define FALSE 0

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
char line[LMAX];		// Current line
int charCount;			// Character counter
int lineCount;			// line counter
int errors[ERRMAX];
FILE* ifp, *ofp; 


// Functions
void errorFound(int type);		// Mark an error
void initialize();				// Initialize variables
void nextCharacter();			// Description in source file. 
void skip();					// Skips whitespace and comments



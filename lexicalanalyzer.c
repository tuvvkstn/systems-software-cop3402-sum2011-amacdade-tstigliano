/*
 * lexicalanalyzer.c
 *
 *  Created on: Jun 19, 2011
 *      Author: Austin
 */

#include "lexicalanalyzer.h"

FILE* inputFile = NULL;
FILE* outputFile = NULL;

enum STATE {
	DEFAULT_STATE,
	COMMENT_STATE,
	IDENTIFIER_STATE,
	NUMBER_STATE
};

int setInputFile(char* filename) {
	inputFile = fopen(filename, "r");
	if (inputFile)
		return NO_ERROR;
	else
		return ERROR_INVALID_FILE;
}

int setOutputFile(char* filename, char* mode) {	// TODO error checking needs to be done here to make sure that the mode selected is a writable mode
	inputFile = fopen(filename, mode);
	if (inputFile)
		return NO_ERROR;
	else
		return ERROR_INVALID_FILE;
}

int main(int argc, char** argv) {

	char* filename;

	if (argc>1) {
		filename = argv[1];
	} else {
		printf("Enter program file name:\n");
		scanf("%s", filename);
	}

	int lexemeList[500];
	
	return generateTokenList(lexemeList);
}

int generateTokenList(int* list) { //TODO push values onto list as they are found
		// setting up pointers to handle strings
	char* beginToken;
	char* currentPosition;
	char* currentString;
	
	// setting state to default state
	int state = DEFAULT_STATE;
	
	int list_size = sizeof(list)/sizeof(int);
	int list_index = 0;
	
	if (inputFile) {	//this would be so much easier if there were a standard c library for regex
		//TODO print contents of Source Program here
		printf("Lexeme Table:\nlexeme\ttoken type");
		while (fscanf(inputFile, "%s", currentString)!=EOF) {
			beginToken = currentString;
			currentPosition = currentString;
			while (*currentPosition != '\0') {
				if (list_index >= list_size)
					return ERROR_ARRAY_INDEX_OUT_OF_BOUNDS;
				switch (state) {
					case DEFAULT_STATE:
						switch (*currentPosition) {
							case ' ':
							case '\t':
							case '\r':
							case '\n':
								currentPosition++;
								break;
							case ':':
								if (*(currentPosition+1)=='=') {
									list[list_index] = BECOMES_SYM;
									list_index++;
									printf(":=\t%d\n", BECOMES_SYM);
									currentPosition += 2;
									break;
								} else {
									return ERROR_INVALID_SYMBOL;
								}
							case ';':
								list[list_index] = SEMICOLON_SYM;
								list_index++;
								printf(";\t%d\n", SEMICOLON_SYM);
								currentPosition++;
								break;
							case '<':
								switch (*(currentPosition +1)) {
									case '>':
										list[list_index] = NOT_EQUAL_SYM;
										list_index++;
										printf("<>\t%d\n", NOT_EQUAL_SYM);
										currentPosition+=2;
										break;
									case '=':
										list[list_index] = LESS_THAN_OR_EQUAL_SYM;
										list_index++;
										printf("<=\t%d\n", LESS_THAN_OR_EQUAL_SYM);
										currentPosition+=2;
										break;
									default:
										list[list_index] = LESS_THAN_SYM;
										list_index++;
										printf("<\t%d\n", LESS_THAN_SYM);
										currentPosition++;
										break;
									}
								break;
							case '>':
								if (*(currentPosition+1)=='=') {
									list[list_index] = GREATER_TH_OR_EQUAL_SYM;
									list_index++;
									printf(">=\t%d\n", GREATER_TH_OR_EQUAL_SYM);
									currentPosition += 2;
								} else {
									list[list_index] = GREATER_THAN_SYM;
									list_index++;
									printf(">\t%d\n", GREATER_THAN_SYM);
									currentPosition++;
								}
								break;
							case '=':
								list[list_index] = EQUAL_SYM;
								list_index++;
								printf("=\t%d\n", EQUAL_SYM);
								currentPosition++;
								break;
							case '/':
								if (*(currentPosition+1)=='*') {
									state = COMMENT_STATE;
									currentPosition += 2;
								} else {
									list[list_index] = FORWARD_SLASH_SYM;
									list_index++;
									printf("/\t%d\n", FORWARD_SLASH_SYM);
									currentPosition++;
								}
								break;
							default: // these values are too numerous to count out, so easier to check if the value is in the right range, check here and set to ID or INT appropriately
								if (*currentPosition >= '(' && *currentPosition <= '.') {	// if the symbol table is altered, these symbols must be redone
									int symbol = *currentPosition - '(' + LEFT_PARENTHESIS_SYM;
									list[list_index] = symbol;
									list_index++;
									printf("%c\t%d\n", *currentPosition, symbol);
									currentPosition++;
								} else if (*currentPosition >= '0' && *currentPosition <= '9') {
									beginToken = currentPosition;
									state = NUMBER_STATE;
									currentPosition++;
								} else if ((*currentPosition >= 'a' && *currentPosition <= 'z') || (*currentPosition >= 'A' && *currentPosition <= 'Z')) {
									switch (*currentPosition) {	//TODO to clean up this section of code, I recommend writing a function that will take in the string, current position, and what not and return a value (lots of repeated code here, just was lazy by the time it was finished)
										case 'b':
											if (*(currentPosition+1) == 'e' && *(currentPosition+2) == 'g' && *(currentPosition+3) == 'i' && *(currentPosition+4) == 'n')
												if (!((*(currentPosition+5) >= 'a' && *(currentPosition+5) <= 'z') || (*(currentPosition+5) >= 'A' && *(currentPosition+5) <= 'Z') || (*(currentPosition+5) >= '0' && *(currentPosition+5) <= '9'))) {
													list[list_index] = BEGIN_SYM;
													list_index++;
													printf("begin\t%d\n", BEGIN_SYM);
													currentPosition += 5;
													break;
												}
										case 'c':
											if (*(currentPosition+1) == 'a' && *(currentPosition+2) == 'l' && *(currentPosition+3) == 'l')
												if (!((*(currentPosition+4) >= 'a' && *(currentPosition+4) <= 'z') || (*(currentPosition+4) >= 'A' && *(currentPosition+4) <= 'Z') || (*(currentPosition+4) >= '0' && *(currentPosition+4) <= '9'))) {
													list[list_index] = CALL_SYM;
													list_index++;
													printf("call\t%d\n", CALL_SYM);
													currentPosition += 4;
													break;
												}
										case 'd':
											if (*(currentPosition+1) == 'o')
												if (!((*(currentPosition+2) >= 'a' && *(currentPosition+2) <= 'z') || (*(currentPosition+2) >= 'A' && *(currentPosition+2) <= 'Z') || (*(currentPosition+2) >= '0' && *(currentPosition+2) <= '9'))) {
													list[list_index] = DO_SYM;
													list_index++;
													printf("do\t%d\n", DO_SYM);
													currentPosition += 2;
													break;
												}
										case 'e':
											if (*(currentPosition+1) == 'l' && *(currentPosition+2) == 's' && *(currentPosition+3) == 'e') {
												if (!((*(currentPosition+4) >= 'a' && *(currentPosition+4) <= 'z') || (*(currentPosition+4) >= 'A' && *(currentPosition+4) <= 'Z') || (*(currentPosition+4) >= '0' && *(currentPosition+4) <= '9'))) {
													list[list_index] = ELSE_SYM;
													list_index++;
													printf("else\t%d\n", ELSE_SYM);
													currentPosition += 4;
													break;
												}
											} else if (*(currentPosition+1) == 'n' && *(currentPosition+2) == 'd')
												if (!((*(currentPosition+3) >= 'a' && *(currentPosition+3) <= 'z') || (*(currentPosition+3) >= 'A' && *(currentPosition+3) <= 'Z') || (*(currentPosition+3) >= '0' && *(currentPosition+3) <= '9'))) {
													list[list_index] = END_SYM;
													list_index++;
													printf("end\t%d\n", END_SYM);
													currentPosition += 3;
													break;
												}
										case 'i':
											if (*(currentPosition+1) == 'f') {
												if (!((*(currentPosition+2) >= 'a' && *(currentPosition+2) <= 'z') || (*(currentPosition+2) >= 'A' && *(currentPosition+2) <= 'Z') || (*(currentPosition+2) >= '0' && *(currentPosition+2) <= '9'))) {
													list[list_index] = IF_SYM;
													list_index++;
													printf("if\t%d\n", IF_SYM);
													currentPosition += 2;
													break;
												}
											} if (*(currentPosition+1) == 'n')
												if (!((*(currentPosition+2) >= 'a' && *(currentPosition+2) <= 'z') || (*(currentPosition+2) >= 'A' && *(currentPosition+2) <= 'Z') || (*(currentPosition+2) >= '0' && *(currentPosition+2) <= '9'))) {
													list[list_index] = IN_SYM;
													list_index++;
													printf("in\t%d\n", IN_SYM);
													currentPosition += 2;
													break;
												}
										case 'o':
											if (*(currentPosition+1) == 'u' && *(currentPosition+2) == 't')
												if (!((*(currentPosition+3) >= 'a' && *(currentPosition+3) <= 'z') || (*(currentPosition+3) >= 'A' && *(currentPosition+3) <= 'Z') || (*(currentPosition+3) >= '0' && *(currentPosition+3) <= '9'))) {
													list[list_index] = OUT_SYM;
													list_index++;
													printf("out\t%d\n", OUT_SYM);
													currentPosition += 3;
													break;
												}
										case 't':
											if (*(currentPosition+1) == 'h' && *(currentPosition+2) == 'e' && *(currentPosition+3) == 'n')
												if (!((*(currentPosition+4) >= 'a' && *(currentPosition+4) <= 'z') || (*(currentPosition+4) >= 'A' && *(currentPosition+4) <= 'Z') || (*(currentPosition+4) >= '0' && *(currentPosition+4) <= '9'))) {
													list[list_index] = THEN_SYM;
													list_index++;
													printf("then\t%d\n", THEN_SYM);
													currentPosition += 4;
													break;
												}
										case 'w':
											if (*(currentPosition+1) == 'h' && *(currentPosition+2) == 'i' && *(currentPosition+3) == 'l' && *(currentPosition+4) == 'e')
												if (!((*(currentPosition+5) >= 'a' && *(currentPosition+5) <= 'z') || (*(currentPosition+5) >= 'A' && *(currentPosition+5) <= 'Z') || (*(currentPosition+5) >= '0' && *(currentPosition+5) <= '9'))) {
													list[list_index] = WHILE_SYM;
													list_index++;
													printf("while\t%d\n", WHILE_SYM);
													currentPosition += 5;
													break;
												}
										default:
											beginToken = currentPosition;
											state = IDENTIFIER_STATE;
											currentPosition++;
									}
								} else {
									return ERROR_INVALID_SYMBOL;
								}
						}
						break;
					case COMMENT_STATE:	// comment state has been entered, so looking for exit
						if (*currentPosition == '*' && *(currentPosition+1) == '/') {
							beginToken = currentPosition + 2;
							currentPosition = beginToken;
							state = DEFAULT_STATE;
						}
						break;
					case IDENTIFIER_STATE:
						if ((*currentPosition >= 'a' && *currentPosition <= 'z') || (*currentPosition >= 'A' && *currentPosition <= 'Z') || (*currentPosition >= '0' && *currentPosition <= '9')) {
							currentPosition++;
						} else {
							list[list_index] = ID_SYM;
							list_index++;
							if (list_index >= list_size)
								return ERROR_ARRAY_INDEX_OUT_OF_BOUNDS;
							char* i;
							for (i = beginToken; i < currentPosition; i++) {
								printf("%c", *i);
								list[list_index] = *i;
								list_index++;
								if (list_index >= list_size)
									return ERROR_ARRAY_INDEX_OUT_OF_BOUNDS;
							}
							printf("\t%d\n", ID_SYM);
							state = DEFAULT_STATE;
						}
						break;
					case NUMBER_STATE:
						if (*currentPosition >= '0' && *currentPosition <= '9') {
							currentPosition++;
						} else {
							list[list_index] = NUMBER_SYM;
							list_index++;
							if (list_index >= list_size)
								return ERROR_ARRAY_INDEX_OUT_OF_BOUNDS;
							char* i;
							for (i = beginToken; i < currentPosition; i++) {
								printf("%c", *i);
								list[list_index] = *i;
								list_index++;
								if (list_index >= list_size)
									return ERROR_ARRAY_INDEX_OUT_OF_BOUNDS;
							}
							printf("\t%d\n", NUMBER_SYM);
							state = DEFAULT_STATE;
						}
						break;
					default:
						printf("This should never happen!!!");
						return ERROR_INVALID_STATE;	//this should never happen!!!!
				}
			}
		}
		printf("Lexeme list\n");
		int j;
		for (j = 0; j < list_index; j++) {	// TODO the way this is set up now, the last element will have a trailing |, don't know if this will matter
			printf("%d|", list[j]);
			if (list[j] == ID_SYM || list[j] == NUMBER_SYM) {
				j++;
				while (j < list_index && list[j] != '\0') {
					printf("%c|", (char)(list[j]));
					j++;
				}
			}	
		}
	} else {
		return ERROR_INVALID_FILE;
	}
	return NO_ERROR;
}
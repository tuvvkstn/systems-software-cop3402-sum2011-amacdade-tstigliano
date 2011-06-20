/*
 * lexicalanalyzer.h
 *
 *  Created on: Jun 19, 2011
 *      Author: Austin
 */
#include <stdio.h>
#include <stdlib.h>

#ifndef LEXICALANALYZER_H_
#define LEXICALANALYZER_H_

enum LEXICAL_ERRORS {
	NO_ERROR,
	ERROR_INVALID_SYMBOL,
	ERROR_INVALID_IDENTIFIER,
	ERROR_INVALID_FILE,
	ERROR_INVALID_STATE,
	ERROR_ARRAY_INDEX_OUT_OF_BOUNDS
};

enum LEXICAL_SYMBOLS {	// symbol table is a modified version of the one in the assignment so that some of the values can be entered as a mathematically derived value of their ascii value
	NULL_SYM,
	ID_SYM,
	NUMBER_SYM,
	ODD_SYM,
	BECOMES_SYM,
	BEGIN_SYM,
	END_SYM,
	IF_SYM,
	THEN_SYM,
	WHILE_SYM,
	DO_SYM,
	CALL_SYM,
	CONST_SYM,
	INT_SYM,
	PROCEDURE_SYM,
	OUT_SYM,
	IN_SYM,
	ELSE_SYM,
	LEFT_PARENTHESIS_SYM,
	RIGHT_PARENTHESIS_SYM,
	MULTIPLY_SYM,
	PLUS_SYM,
	COMMA_SYM,
	MINUS_SYM,
	PERIOD_SYM,
	FORWARD_SLASH_SYM,
	SEMICOLON_SYM,
	LESS_THAN_SYM,
	EQUAL_SYM,
	GREATER_THAN_SYM,
	NOT_EQUAL_SYM,
	LESS_THAN_OR_EQUAL_SYM,
	GREATER_TH_OR_EQUAL_SYM
};

int setInputFile(char* filename);
int setOutputFile(char* filename, char* mode); // mode included so that users can choose between write and append
int generateTokenList(int* list);

#endif /* LEXICALANALYZER_H_ */

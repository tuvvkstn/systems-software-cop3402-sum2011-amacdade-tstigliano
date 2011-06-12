/*
 *	Authors: Tyler Stigliano, Austin Macdade
 *	Homework #1: Implementation of a PM/0 p-machine virtual machine
 *	Class: COP3402: System Software
 *	Professor: Dr. Euripides Montagne
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG

// Constants;
#define MAX_STRING_LENGTH 256	//increased to a value not likely to be reached, what if the user inputs a fully qualified path?
#define MAX_STACK_HEIGHT 2000
#define MAX_CODE_LENGTH 500
#define MAX_LEXI_LEVELS 3
//TODO figure out how to implement MAX_LEXI_LEVELS? this isn't present in the rest of the code...
//Does this mean that at most you can search 3 levels deep, or that the program should only be allowed to run 3 levels deep?
//Professor says that this means that there should be at most MAX_LEXI_LEVELS static linkages deep for a given call.
//There is currently no bookkeeping done for how deep a stack goes, so this may not end up getting implemented machine side, or at all.

#define ERROR_INVALID_OPCODE 1
#define ERROR_INVALID_STACK_OPERATION 2
#define ERROR_INVALID_FILENAME 3
#define ERROR_PC_TOO_HIGH 4
#define ERROR_PROG_TOO_LONG 5
#define ERROR_SP_OUT_OF_BOUNDS 6
#define ERROR_INVALID_IO_OPERATION 7

//String arrays that match the opcodes and operation values in index values
const char* OPCODE_STRINGS[] = {"FCH", "LIT", "OPR", "LOD", "STO", "CAL", "INC", "JMP", "JPC", "SIO"};
const char* STACK_OPERATION_STRINGS[] = {"RET", "NEG", "ADD", "SUB", "MUL", "DIV", "ODD", "MOD", "EQL", "NEQ", "LSS", "LEQ", "GTR", "GEQ"};
const char* SIO_OPERATION_STRINGS[] = {"", "SOT", "SIN"};

// Funcations;
int base (int l, int base);
void printCodeList();
void printCodeLine(int line);
void printStack();
void executeNextInstruction();
void operateOnStack();
void standardIOOperation();
void loadProgramFromFile(char filename[]);
void runProgram();

// Enumerations
enum OPCODE {FCH, LIT, OPR, LOD, STO, CAL, INC, JMP, JNC, SIO};
enum STACK_OPERATION {RET, NEG, ADD, SUB, MUL, DIV, ODD, MOD, EQL, NEQ, LSS, LEQ, GTR, GEQ};
enum SIO_OPERATION {SOT = 1, SIN}; //only 1 and 2 have been defined in the specification for the machine

// Structures;
struct instructions{
	int OP;
	int l;
	int m;
};

// Global Arrays;
int stack[MAX_STACK_HEIGHT];
struct instructions code[MAX_CODE_LENGTH];


// Registers
int BP = 1;
int SP = 0;
int PC = 0;
struct instructions IR;

// other global variables
int code_size = 0;
#ifdef DEBUG
FILE *debugFile;
#endif

int main(){
	
	char filename[MAX_STRING_LENGTH];

	// Stack initialization
	stack[1] = 0;
	stack[2] = 0;
	stack[3] = 0;
	//command line style file input method, not using for now, may reimplement later for ease of use (it's easier to include the files in the command line when using a smart shell)
	/*if (argc>1) {	// if multiple arguments were entered in the command line, then assume the second argument is the input file, else default to input.txt
		filename = argv[1];
		}
	else
		filename = "input.txt";*/
	
	FILE *programFile;
	programFile = fopen(filename, "r");
	
	printf("Enter program file name:\n");
	scanf("%s", filename);
	
	 else {
		printf("ERROR: File %s does not exist\n", filename);
		exit(ERROR_INVALID_FILENAME);
	}
	
	loadProgramFromFile(filename);
	
#ifdef DEBUG
	char debugLogName[MAX_STRING_LENGTH];

	printf("Enter debug log file name:\n");
	scanf("%s", debugLogName);
	fopen(debugFile, "w");
	
	while(debugFile == NULL) {
		printf("Error opening file, please specify a different file:\n");
		scanf("%s", debugLogName);
		fopen(debugFile, "w");
	}
	printCodeList();
	
#endif

	runProgram();

	

	return 0;
}

void printStack() {
	//form an array of all base pointers in the stack
	int numBasePointers = 1;
	int basePointers[700];
	int currentBP = BP;
	int i;
	
	while(currentBP > 1) {
		basePointers[700 - numBasePointers] = currentBP;
		currentBP = stack[currentBP+1];
		numBasePointers++;
	}
	
	numBasePointers--;

	for(i = 1; i <= SP; i++) {
		if (basePointers[700-numBasePointers]==i) {
			printf("| ");
			numBasePointers--;
		}
		printf("%d ", stack[i]);
	}
}

void printCodeList() {
	int i;
	printf("Line  OP  L   M\n");
	for(i = 0; i < code_size; i++){
		printCodeLine(i);
		printf("\n");
	}
}

void printCodeLine(int line) {
	printf("%3d %s %2d %3d", line, OPCODE_STRINGS[code[line].OP], code[line].l, code[line].m);
}

void runProgram() {
	// Prints initial values
#ifdef DEBUG
	fprintf(debugFile, "\t\tPC BP  SP  Stack\n");
	fprintf(debugFile, "Initial values  %2d %2d %3d ", PC, BP, SP);
	printStack();
	fprintf(debugFile, "\n");
#endif
	while(BP > 0) {	// If BP is 0, then the program has executed an OPR.RET from the base program, time to halt.
		if (PC < code_size) {
#ifdef DEBUG
			printCodeLine(PC);
#else
			printCodeLine(PC);
#endif
			executeNextInstruction();
#ifdef DEBUG
			fprintf(debugFile, "\t%2d %2d %3d  ", PC, BP, SP);	// print registers
			printStack();
			fprintf(debugFile, "\n");
#endif
		} else if (PC<MAX_CODE_LENGTH){
			printf("WARNING: Program counter has exceeded program lentgh.\n\tPress CTRL+C to terminate, or press ENTER to continue.\n");
			while ( getchar() != '\n');
		} else {
			printf("ERROR: Program counter has exceeded MAX_CODE_LENGTH.\n");
			exit(ERROR_PC_TOO_HIGH);
		}
	}
}

int base(int l, int base) {	//find base L levels down
	int b1;
	b1 = base;
	while(l > 0){
		b1 = stack[b1];
		l--;
	}
	return b1;
}

void executeNextInstruction() {	// fetch code at PC and execute
	// Fecth Cycle
	IR = code[PC];
	PC++;

	// Execution Cycle
	switch (IR.OP) {
		case FCH:	//treated as NOOP, (fetch already executed, TODO there may be a better way to do this, but the FETCH opcode isn't in the design (traditionally a hidden opcode))
			break;
		case LIT:	//push literal IR.m onto stack
			SP++;
			stack[SP] = IR.m;
			break;
		case OPR:	//operate on stack, depending on literal in instruction register, for operations, see operateOnStack()
			operateOnStack();
			break;
		case LOD:	//push value at offset IR.m from IR.l lexicographical levels down onto stack
			SP++;
			stack[SP] = stack[base(IR.l, BP) + IR.m];
			break;
		case STO:	//pop value off stack and store at offset IR.m from IR.l lexicographical levels down
			stack[base(IR.l, BP) + IR.m] = stack[SP];
			SP--;
			break;
		case CAL:	//call procedure at code index IR.m (assuming in this case that the stack pointer will be properly incremented after this call is made to allocate local variables?)
			stack[SP + 1] = base(IR.l, BP);	//static link
			stack[SP + 2] = BP;				//dynamic link
			stack[SP + 3] = PC;				//return address
			BP = SP + 1;
			PC = IR.m;
			break;
		case INC:	//increment stack pointer by IR.m
			SP += IR.m;
			break;
		case JMP:	//jump to instruction IR.m
			PC = IR.m;
			break;
		case JNC:	//jump to instruction IR.m IF top stack element == 0
			if(stack[SP] == 0){
				PC = IR.m;
				SP--;
			}
			break;
		case SIO:	//perform standard IO operation, depending on literal in instruction register, for operations, see standardIOOperation()
			//standardIOOperation();	//suppressing this function for now
			break;
		case 10: break;	//suppressed, not technically a valid operation based on conversation with instructor
		default:
			printf("ERROR: Invalid OPCODE %d! Line: %d\n", IR.OP, PC);
			exit(ERROR_INVALID_OPCODE);
	}
}

void operateOnStack() {	// do operation IR.m on stack
	switch (IR.m) {
		case RET:
			SP = BP - 1;
			PC = stack[SP + 3];
			BP = stack[SP + 2];
			break;
		case NEG:
			stack[SP] *= -1;
			break;
		case ADD:
			SP--;
			stack [SP] = stack[SP] + stack[SP + 1];
			break;
		case SUB:
			SP--;
			stack[SP] = stack[SP] - stack[SP + 1];
			break;
		case MUL:
			SP--;
			stack[SP] = stack[SP] * stack[SP + 1];
			break;
		case DIV:
			SP--;
			stack[SP] = stack[SP] / stack[SP + 1];
			break;
		case ODD:
			stack[SP] %= 2;
			break;
		case MOD:
			SP--;
			stack[SP] %= stack[SP + 1];
			break;
		case EQL:
			SP--;
			stack[SP] = stack[SP] == stack[SP+1];
			break;
		case NEQ:
			SP--;
			stack[SP] = stack[SP] != stack[SP + 1];
			break;
		case LSS:
			SP--;
			stack[SP] = stack[SP] < stack[SP + 1];
			break;
		case LEQ:
			SP--;
			stack[SP] = stack[SP] <= stack[SP + 1];
			break;
		case GTR:
			SP--;
			stack[SP] = stack[SP] > stack[SP + 1];
			break;
		case GEQ:
			SP--;
			stack[SP] = stack[SP] >= stack[SP + 1];
			break;
		default:
			printf("ERROR: Invalid STACK_OPERATION on line %d: %d cannot be resolved to an operation.\n", PC, IR.m);
			printStack();
			printf("\n");
			exit(ERROR_INVALID_STACK_OPERATION);
	}
}

void standardIOOperation() {
	switch (IR.m) {
		case 0:	//for the purposes of testing the factorial code, which was based on a slightly different instruction set, this instruction will do the same as SOT
		case SOT:	// pop the top element of the stack off and display it to standard out
			printf("%d\n", stack[SP]);
			SP--;
			break;
		case SIN:	// push the first integer to be entered from standard input onto the stack, keep retrying till good data is gotten
			SP++;
			int i;
			while (!scanf("%d", &i));
			stack[SP] = i;
			break;
		default:
			printf("ERROR: Invalid SIO_OPERATION on line %d: %d cannot be resolved to a standard IO operation.\n", PC, IR.m);
			printStack();
			printf("\n");
			exit(ERROR_INVALID_IO_OPERATION);
	}
}

void loadProgramFromFile(char filename[]) {	// load program in file filename into code, only supports loading one program, may support loading more than one in the future.
	if(programFile){	// If file exists
		// Reads in information from file and stores in CODE array, assumes that the input file is properly formatted, TODO: no error checking ATM here
		int opcode, L_code, M_code;	// Holds OPcode, L, and M when reading in from file
		int i = 0;					// Counter
		while (fscanf(programFile, "%d", &opcode) != EOF){
			if (i>MAX_CODE_LENGTH) {
				printf("ERROR: Program is longer MAX_CODE_LENGTH.\n\tDecrease lines of code in program or increase MAX_CODE_LENGTH.\n");
				exit(ERROR_PROG_TOO_LONG);
			}
			fscanf(programFile, "%d", &L_code);
			fscanf(programFile, "%d", &M_code);

			code[i].OP = opcode;
			code[i].l = L_code;
			code[i].m = M_code;
			i++;
		}
		code_size = i;
	}
}

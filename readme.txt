Authors: Tyler Stigliano, Austin Macdade
Homework #1: Implementation of a PM/0 p-machine virtual machine
Class: COP3402: System Software
Professor: Dr. Euripides Montagne


	To compile and run the Virtual Machine the user is first prompt to enter a file name 
less than 30 characters long that contains the sequence code. If an incorrect file name is input 
the program will terminated, otherwise the information is read in. When reading in the information 
from the input file, if the code length becomes greater than the maximum allowed code length the 
program will terminate. Next the program will begin to analyze the sequence code. If the problem 
counter is less than the code size the code executes normally. If the problem counter exceeds the 
input code size then an error message prints out advising to terminate the program. Finally if the 
problem counter exceeds the Maximum Code Length the program terminates. 


Valid OPcode instructions for this Virtual Machine are:
FCH: this is treated as No OPcode
LIT: Push constant value M onto stack
OPR: 
     NEG: -stack[sp]
     ADD: sp <- sp – 1 and stack[sp] <- stack[sp] + stack[sp + 1
     SUB: sp <- sp – 1 and stack[sp] <- stack[sp] - stack[sp + 1]
     MUL: sp <- sp – 1 and stack[sp] <- stack[sp] - stack[sp + 1]
     DIV: sp <- sp – 1 and stack[sp] <- stack[sp] div stack[sp + 1]
     ODD: stack[sp] <- stack mod 2) or ord(odd(stack[sp]))
     MOD: sp <- sp – 1 and  stack[sp] <- stack[sp] mod stack[sp + 1

     If statement is true 1 is store in stack[sp], other wise 0 is stored in stack[sp]
     EQL: sp <- sp – 1 and  stack[sp] <- stack[sp] = =stack[sp + 1]
     NEQ: sp <- sp – 1 and  stack[sp] <- stack[sp] != stack[sp + 1]
     LSS: sp <- sp – 1 and  stack[sp] <- stack[sp]  <  stack[sp + 1]
     LEQ: sp <- sp – 1 and  stack[sp] <- stack[sp] <=  stack[sp + 1]
     GTR: sp <- sp – 1 and  stack[sp] <- stack[sp] >  stack[sp + 1]
     GEQ: sp <- sp – 1 and  stack[sp] <- stack[sp] >= stack[sp + 1]	
LOD: Push from location at offset M in frame L levels down
STO: Store in location at ofset M in frame L levels down
CAL: Call procedure at M
INC: Allocate M locations, first three are SL, DL, RA
JMP: Sets PC = M
JMC: Jump to M if top of stack element is 0 and decrement SP by one
SIO: Preform standard IO operation, depending on L in instruction register
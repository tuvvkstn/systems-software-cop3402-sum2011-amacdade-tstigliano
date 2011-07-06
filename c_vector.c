/*	'c_vector.h'
	Austin Macdade
	7/6/11
*/

#include "c_vector.h"
//PRIVATE FUNCTIONS:

//PUBLIC FUNCTIONS:
//constructors
c_vector newVector() {
	return newVector(DEFAULT_C_VECTOR_DATA_SIZE, DEFAULT_C_VECTOR_LENGTH, DEFAULT_C_VECTOR_POINTER_LIST_LENGTH)
}

c_vector newVector(int dataSize) {
	return newVector(dataSize, DEFAULT_C_VECTOR_LENGTH, DEFAULT_C_VECTOR_POINTER_LIST_LENGTH)
}

c_vector newVector(int dataSize, int initialLength) {
	return newVector(dataSize, initialLength, DEFAULT_C_VECTOR_POINTER_LIST_LENGTH)
}

c_vector newVector(int dataSize, int initialLength, int pointerListLength) {
//TODO
	
}

//copy constructor
c_vector copyVector(c_vector vector) {
//TODO
	
}

//copy mutate constructors
c_vector copyVector(c_vector vector, int initialLength) {
//TODO
	
}

c_vector copyVector(c_vector vector, int initialLength, int pointerListLength) {
//TODO
	
}


//destructor
int destroyVector(c_vector vector) {
//TODO
	
	return C_VECTOR_ERROR_NO_ERROR;
}


//accessors
int getElement(c_vector vector, void* element, int elementIndex) {
//TODO
	
	return C_VECTOR_ERROR_NO_ERROR;
}

int getElements(c_vector vector, void* returnArray, int startIndex, int endIndex) {
//TODO
	
	return C_VECTOR_ERROR_NO_ERROR;
}

//this next accessor will write all values from vector into returnArray until breakValue
//is reached or the array runs out of space.
int getElements(c_vector vector, void* returnArray, int startIndex, void* breakElement) {
//TODO
	
	return C_VECTOR_ERROR_NO_ERROR;
}

int getElementSize(c_vector vector) {
//TODO
	
	return C_VECTOR_ERROR_NO_ERROR;
}

int getVectorLength(c_vector vector) {
//TODO
	
	return C_VECTOR_ERROR_NO_ERROR;
}


//search functions
int findElement(c_vector vector, void* element, void (*compareFunction)(void*, void*)) {
//TODO
	
	return C_VECTOR_ERROR_NO_ERROR;
}

int findNextElementAfterIndex(c_vector vector, void* element, int startIndex, void (*compareFunction)(void*, void*)) {
//TODO
	
	return C_VECTOR_ERROR_NO_ERROR;
}


//mutators
int setElement(c_vector vector, void* element, int elementIndex) {
//TODO
	
	return C_VECTOR_ERROR_NO_ERROR;
}

int setElements(c_vector vector, void* sourceArray, int sourceBeginIndex, int sourceEndIndex, int vectorBeginIndex, int vectorEndIndex) {
//TODO
	
	return C_VECTOR_ERROR_NO_ERROR;
}

int pushElements(c_vector vector, void* sourceArray, int sourceBeginIndex, int sourceEndIndex) {
//TODO
	
	return C_VECTOR_ERROR_NO_ERROR;
}

int pushElements(c_vector vector, void* sourceArray, int sourceBeginIndex, void* breakElement) {
//TODO
	
	return C_VECTOR_ERROR_NO_ERROR;
}

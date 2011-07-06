/*	'c_vector.h'
	Austin Macdade
	7/6/11
	This is a data structure that acts as an extendible array, using pointer
	arrays to keep track of where the arrays are in memory, with a pointer to
	the next pointer array at the end of the pointer array. This does not mimic
	a c++ vector in that it does not allocate and copy a larger array every
	time it needs more space, and c doesn't support operator overload, so the
	data can only be accessed by calling one of the funtions in this file. This
	data structure does not lay in one continuous block and will allocate
	memory from the heap in a fragmented fashion. It was designed that way so
	that it can exist even when a large continuous block is not available to be
	allocated and so that it does not bottleneck at costly memcpy functions of
	large arrays.
*/

#ifndef C_VECTOR_H
#define C_VECTOR_H

//typedef to make things less hairy looking
typedef void* c_vector;

//default values, char may be different sizes on different systems
#define DEFAULT_C_VECTOR_LENGTH 100
#define DEFAULT_C_VECTOR_POINTER_LIST_LENGTH 10
#define DEFAULT_C_VECTOR_DATA_SIZE (sizeof(char))

//TODO: return errors
#define C_VECTOR_ERROR_NO_ERROR 0
#define C_VECTOR_ERROR_ARRAY_INDEX_OUT_OF_BOUNDS 1
#define C_VECTOR_ERROR_ELEMENT_DOES_NOT_EXIST
#define C_VECTOR_ERROR_CANNOT_DESTROY_NON_VECTOR

//constructors
c_vector newVector();
c_vector newVector(int dataSize);
c_vector newVector(int dataSize, int initialLength);
c_vector newVector(int dataSize, int initialLength, int pointerListLength);
//copy constructor
c_vector copyVector(c_vector vector);
//copy mutate constructors
c_vector copyVector(c_vector vector, int initialLength);
c_vector copyVector(c_vector vector, int initialLength, int pointerListLength);

//destructor
int destroyVector(c_vector vector);

//accessors
int getElement(c_vector vector, void* element, int elementIndex);
int getElements(c_vector vector, void* returnArray, int startIndex, int endIndex);
//this next accessor will write all values from vector into returnArray until
//breakValue is reached or the array runs out of space.
int getElements(c_vector vector, void* returnArray, int startIndex, void* breakElement);
int getElementSize(c_vector vector);
int getVectorLength(c_vector vector);

//search functions
int findElement(c_vector vector, void* element, void (*compareFunction)(void*, void*));
int findNextElementAfterIndex(c_vector vector, void* element, int startIndex, void (*compareFunction)(void*, void*));

//mutators
int setElement(c_vector vector, void* element, int elementIndex);
int setElements(c_vector vector, void* sourceArray, int sourceBeginIndex, int sourceEndIndex, int vectorBeginIndex, int vectorEndIndex);
int pushElements(c_vector vector, void* sourceArray, int sourceBeginIndex, int sourceEndIndex);
int pushElements(c_vector vector, void* sourceArray, int sourceBeginIndex, void* breakElement);

#endif
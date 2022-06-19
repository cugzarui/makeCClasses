#ifndef _MORE_DATA_TYPES_H_
#define _MORE_DATA_TYPES_H_

#include "makeClasses.h"



// some classes


// the 'Nicht' macro (similar to 'None' in python or 'undefined' in js)
#define Nicht ((Defined){ .class=NULL, .instanceData=NULL })
#define isNicht(x) (x.class == NULL)
#define isntNicht(x) (x.class != NULL)


// the String class (header part)

defineInstance(String,
	char *s;
	int len;
)

#define __String_new_RET_TYPE Defined
#define __String_new_ARGS(s) (char *s)

#define __String_unmake_RET_TYPE void
#define __String_unmake_ARGS(a) (Defined a)

#define __String_len_RET_TYPE int
#define __String_len_ARGS(a) (Defined a)

#define __String_getS_RET_TYPE char *
#define __String_getS_ARGS(a) (Defined a)

#define method(name) _method(PTR, String, name)

typedef struct {
	method(new);
	method(unmake);
	method(len);
	method(getS);
} __String;

#undef method

extern __String * String;

// end of string class (header part)



// must be called for classes to be usable
void createAllClasses();

// must be called at the end of the program to free up resources used to make the class definitions
void unmakeAllClasses();



#include "makeClassesCleanup.h"

#endif
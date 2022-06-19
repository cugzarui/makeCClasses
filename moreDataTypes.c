#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "moreDataTypes.h"
#include "makeClasses.h"

// the String class (code part)

__String *String;

#define method(name,...) _method(DEF, String, name, __VA_ARGS__)
#define fromInstanceGet _fromInstanceGet(String, instance)

/**
 * constructor for the string class
 *
 * @param s<char *> - the string that the class would be initialized to. the class points to this string after initialization.
 * 
 * @return <Defined> a Defined object containing a new initialized String class object instance
*/
method(new, s)
{
	__String_instanceData *instanceData = (__String_instanceData *)malloc(sizeof(__String_instanceData));
	if (instanceData == NULL)
		return Nicht;
	
	instanceData->len = strlen(s);
	
	instanceData->s = (char *)malloc(sizeof(char) * (instanceData->len + 1));
	if (instanceData->s == NULL) {
		free(instanceData);
		return Nicht;
	}
	strcpy(instanceData->s, s);
	
	return (Defined){ .class=String, .instanceData=instanceData };
}



/**
 * deconstruct a String class object instance (free alocated resources)
 *
 * @param instance<Defined> - the instance to deconstruct
*/
method(unmake, instance)
{
	free( fromInstanceGet s );
	free(instance.instanceData);
}

/**
 * return the length of a String instance
 *
 * @param instance<Defined> - the instance
 *
 * @return <int> the length
*/
method(len, instance)
{
	if (instance.class == String)
		return fromInstanceGet len;
	return -1;
}

/**
 * get the string from a String class instance
 *
 * @param instance<Defined> - the instance
 *
 * @return <char *> the string
*/
method(getS, instance)
{
	return fromInstanceGet s;
}

#undef fromInstanceGet
#undef method


void createStringClass() {
	String = (__String *)malloc(sizeof(__String));
	*String = (__String){
		.new = &__String_new,
		.unmake = &__String_unmake,
		.len = &__String_len,
		.getS = &__String_getS
	};
}

void unmakeStringClass()
{
	free(String);
}

// end of string class (code part)




void createAllClasses()
{
	createStringClass();
}

void unmakeAllClasses()
{
	unmakeStringClass();
}




#include "makeClassesCleanup.h"
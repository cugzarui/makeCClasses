#include <stdio.h>
#include "moreDataTypes.h"

int main()
{
	Defined s;
	#define s(x) ((*(String->x))(s))
	
	createAllClasses();
	
	s = String->new("Hello world!\n");
	
	printf(s(getS));
	
	s(unmake);
	
	unmakeAllClasses();
	
	return 0;
}
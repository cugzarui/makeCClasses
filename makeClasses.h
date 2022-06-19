/**
 * how to make and use classes:
 * there are some examples in the moreDataTypes library.
 *
 * @HOW TO MAKE CLASSES PART -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *
 * step zero: create a .c and .h files for the class/classes.
 *
 * first, include this file (makeClasses.h, in both .c and .h files), and remember to include makeClassesCleanup.h at the end of your class definitions in both the header and code files.
 * nothing bad will happen if you dont, but it cleans up some of the stuff used to make classes, so that stuff wont bother you when using the classes in other files.
 *
 * next, go to the header file and use two comment lines to show where the definition of a specific class starts and ends (do this for the .c file too).
 * between them (in header) typedef a struct to the classes name, but prepend the name with two underscores (e.g. __String), or make it different and hard to accidently type some other way.
 * you dont gotta fill it in yet, but do define an extern pointer to an object of that structs type right under it (e.g. extern __String * String), and make sure to give it the class name.
 * this pointer IS the class definition as far as any code relying on it is concerned. when you wana access the class methods or variables, you do it through THAT pointer, and there is only ONE of it.
 *
 * next, youl want to copy and fill in the macros commented out in this file (bellow this comment, above the headers code, as well as at the bottom of the file), placing them in the right places.
 * 
 * next, in the header file above the definition of the 'method' macro, define the instance data storage type by using the 'defineInstance' macro like so:
 *
 * defineInstance(class name,
 * 	define instance variables here like you would in a struct
 * )
 *
 * next, in the .c file, write the documentation for the methods, along with:
 *
 * method(method name, parameter names)
 * {
 *		...
 *		...
 *		...
 * }
 *
 * this will help you get an idea for how to write the rest of the code before you get confused.
 * in particular, deciding on and documenting the parameter types, purposes, and the return type and nature of the return value.
 * dont fill in the code for the methods yet unless you realy want to.
 *
 * next, create macros that define the methods return types and parameters. do this in the header file between the place you used the 'defineInstance' macro and where you defined the struct that the class will point to.
 * create the macros like so:
 *
 * #define two underscores + class name + underscore + method name + _RET_TYPE method's return type
 * #define two underscores + class name + underscore + method name + _ARGS(list of as many macro parameters as method params) (list of param types in order inside this pair of parentheses)
 *
 * example (for the method 'new' in class 'String'):
 * #define __String_new_RET_TYPE Defined
 * #define __String_new_ARGS(s) (char *s)
 *
 * please note that you can use these macros wherever youd like after defining them, and might want to use them sometimes when you use the class methods.
 *
 * now would be a good time to write the methods maybe but you can also do that later.
 *
 * next, in the .c file, at the top of the class definition, declare the pointer that will be the class, but dont initialize it yet (maybe set it to NULL or something).
 * at the bottom of the class definition, create a function that initializes it. remember: its a pointer to a specific struct of a specific type, that you defined in the header,
 * whos fields will be populated by the methods and class variables. an example of how the function is written (in the 'String' class):
 *
 * void createStringClass() {
 *	String = (__String *)malloc(sizeof(__String));
 *	*String = (__String){
 *		.unmake = &__String_unmake,
 *		.len = &__String_len,
 *		.getS = &__String_getS
 *	};
 * }
 *
 * in this example we first allocate memory for the class definition (it would get currupted otherwise). then, we populate it.
 *
 * remember to also create an 'unmake' function for the class thatl de-allocate the class definition.
 *
 * were not done yet. to keep things organized, it is good to create a single function that calls all the functions that create classes (all the functions serving a similar purpose to 'createStringClass').
 * this function will be prototyped in some header file, while the ones it calls will not. you will call this 'createAllClasses' function in 'main' or someplace similarly central, so that the classes are created and usable, without needing to call a shitton of functions.
 *
 * do the same thing for the 'unmakeClass' functions.
 *
 * @HOW TO USE CLASSES PART-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *
 * to declare a class instance, simply declare a 'Defined' variable (it can be initialized later. for now, initialize it to { 0 } if you must).
 * to initialize an instance of a class, assign it to the classes 'new' method (or another constructor if it exists). remeber to access the methods through the class definition (e.g. Class->method() ).
 * to be able to use classes at all, call 'getAllClasses' (but only call it once or you could get some serious bugs).
 * remember to 'unmake' every class instance when youre done with it ('unmake' is a 'deconstructor' that frees resources taken up by the class. its a method of the class).
 * remember to unmake the class definitions at the end with 'unmakeAllClasses'.
 * using a class instance or the class itself can be tedious, so you might want to assign some local variable to a commonly used expression that relies on the class,
 * or make a macro that expands to a more complex expression. here is an example of a 'hello world' program written using classes:
 *
 * #include <stdio.h>
 * #include "moreDataTypes.h"
 *
 * int main()
 * {
 * 	Defined s;
 * 	#define s(x) (String->x(s))
 * 	
 * 	createAllClasses();
 * 	
 * 	s = String->new("Hello world!\n");
 * 	
 * 	printf(s(getS));
 * 	
 * 	s(unmake);
 *	
 *	unmakeAllClasses();
 * 	
 * 	return 0;
 * }
 *
 * at the bottom of this file youl find a 'second header' that defines tools that make class usage possible and easier. the tools include:
 * - fromInstanceGet - which allows you to more easily access instance variables (read instructions on usage bellow)
 * 
 * @COMMON BUG FIXES -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *
 * if your code doesnt compile try to:
 * - change the types that are related to classes in any way whatsoever (specifically, change them from pointers to non-pointers, or vice versa)
 * - add parentheses
 * - make sure every line that needs a semicolon has one
 * - make sure everything has the right number of arguments
 * - make sure all the names are correct
 * - from periods (.) and arrows (->), or vice versa, in code that accesses class methods/attributes
 * - compile the problem file with option -E and search through the mountain of precompiled text for the issue (usually your code will be near the bottom so dont worry)
 * - literaly rewrite the problem code and other parts of the code for no reason
 * - pray to god
 * - take a break and come back later
 * - use a different library, or language (why are you even using c if you want classes??)
*/

// copy this one above the class methods for a specific class in the .c file. #undef it after the method definitions of that class
//#define method(name,...) _method(DEF, <class name>, name, __VA_ARGS__)

// copy this one above the struct that the class points to an instance of in the header file. #undef it after the struct definition.
//#define method(name,...) _method(PTR, <class name>, name)

// copy this one next to the 'method' macro and undefine it at the next to the 'method' macros undefinition. fill in the blank. maybe change the name.
// you now have the a macro for the type of the instance data
//#define instanceDataType __<class name>_instanceData

#ifndef _MAKE_CLASSES_H_
#define _MAKE_CLASSES_H_

// macros to make defining methods easier. just remember to #undef them or #include "makeClassesCleanup.h" when youre done
// you have to define the return type and argument macros yourself, and their names must be of the format: class name + method name + _RET_TYPE or _ARGS
// the name is preceded by two underscores and the class and method names are seperated by an underscore and written as they are to be used through the class interface in the code.
// the function names will become the class name followed by the method name, seperated by an underscore, and preceded by two underscores. e.g. __String_len
// the arguments macro will expand into a list of the arguments to the method, seperated by commas: (type1 optional name, type2 optional name, type3 optional name...)
// note: these do not end in semicolons and you might wana use semicolons with them
#define DEF(class, name,...) __##class##_##name##_RET_TYPE __##class##_##name __##class##_##name##_ARGS(__VA_ARGS__)
#define PTR(class, name,...)__##class##_##name##_RET_TYPE (* name) __##class##_##name##_ARGS()
// this macro should not be used directly and instead you should create a new macro 'method' that expands to _method. #undef 'method' at the end of a classes code (both in c and h files).
// the 'method' macro just expands to _method and outo fills some of the params.
// you can find the skeleton of the 'method' macro at the top of the file. copy/paste it to your code in the right place and fill in the blanks.
#define _method(expression, class, name,...) expression(class, name,__VA_ARGS__)


// a macro for defining the instance variables.
// the name of the data type used for storing the instance variables is the class name + _instanceData (the name is also preceded by two underscores).
// if you want to use the data type in its own definition, use this name but preceed it with 'struct' as is only typedef'ed after the definition.
#define defineInstance(class,...) typedef struct __##class##_instanceData {\
__VA_ARGS__\
} __##class##_instanceData;

#endif


#ifndef _USE_CLASSES_
#define _USE_CLASSES_

// a type to emulate the class system in higher level languages.
// 'instance' points to the data relating to a particular variable of a given type.
// 'class' points to some 'description' of the data type. likely complete with methods and constructors and whatnot.
typedef struct {
	void *instanceData;
	void *class;
} Defined;


// copy the commented out macro to where youre using classes and replace 'class' and\or 'instance with the name of the class youre using and the name of the instance (change the macro name if you use multiple class types)
// itl be easier and more readable to access instance variables
#define _fromInstanceGet(class, instance) ((__##class##_instanceData *)(instance.instanceData))->
//#define fromInstanceGet _fromInstanceGet(class, instance)
//#define fromInstanceGet(instance) _fromInstanceGet(class, instance)
//#define fromInstanceGet(class) _fromInstanceGet(class, instance)

#endif
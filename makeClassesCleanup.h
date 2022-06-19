/**
 * include this header AT THE END of whatever file you have that uses makeClasses.h and itll undefine the macros and do other cleanups of the tools used to make classes (tho not the tools for using them)
*/
#ifdef _MAKE_CLASSES_H_

#undef _MAKE_CLASSES_H_
#undef DEF
#undef PTR
#undef _method

#endif
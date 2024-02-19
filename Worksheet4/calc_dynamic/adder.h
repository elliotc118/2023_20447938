//begin adder.h dynamic version

//the following two lines prevent adder.h from being included more than once in any source file

#ifndef MATHSLIB_ADDER_H
#define MATHSLIB_ADDER_H



//we need to prefix our function  names with additional keyword which is different depending on the operating system we are using

//and whther we are using or creating the library

//the variable "maths_EXPORTS" must be defined at build time if we are building the library but not if we are using it



#if defined (WIN32)|defined(_WIN32)
#ifdef maths_STATIC

//dont add any keywords if building a static library

#define MATHSLIB_API
#else
#ifdef maths_EXPORTS
#define MATHSLIB_API __declspec( dllexport )
#else
#define MATHSLIB_API __declspec( dllimport )
#endif
#endif
#else
//MATHSLIB_API is defined as nothing is were not on Windows
#define MATHSLIB_API
#endif
//the above will include one of:
//__declspec (dllexport)
//__declspec(dllimport)
//before declarations This is Microsoft specific
//extension to C/C++
//prototype for the function including additional keyword
MATHSLIB_API int add(int a, int b);
#endif



//end adder.h dynamic version
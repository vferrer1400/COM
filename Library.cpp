#include "Library.h"
#include <stdio.h>

// To compile as a library in dev command line
// cl /W4 /LD Library.cpp Library.def
void __stdcall HenCluck()
{
	printf("C-style cluck!\n");
}
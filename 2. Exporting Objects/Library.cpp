#include "Library.h"
//#include <stdio.h>

// To compile as a library in dev command line
// cl /W4 /LD Library.cpp Library.def

// void __stdcall HenCluck()
// {
	// printf("C-style cluck!\n");
// }

#include <windows.h>

#define TRACE OutputDebugString

struct Hen : IHen
{
	unsigned m_count;
	Hen()
	{
		TRACE("Cheep!\n");
	}

	~Hen()
	{
		TRACE("Chicken soup!\n");
	}

	void __stdcall Cluck()
	{
		TRACE("Cluck\n");
	}

	void __stdcall Roost()
	{
		TRACE("Zzzzzz!\n");
	}

	void __stdcall AddRef()
	{
		++m_count;
	}

	void __stdcall Release()
	{
		if (0 == --m_count)
		{
			delete this;
		}
	}
};

IHen* __stdcall CreateHen()
{
	IHen* result = new Hen;
	result->AddRef();
	return result;
}
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

struct Hen : IHen2, IOfflineChicken
{
	unsigned m_count;
	Hen(): m_count(0)
	{
		TRACE("Cheep!\n");
	}

	~Hen()
	{
		TRACE("Chicken soup!\n");
	}

	//
	// IObject
	//

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

	void* __stdcall As(char const* type)
	{
		// Cannot simply static_cast every single interface since
		// they will necessary be a hierarchy of interfacesand that
		// would be ambiguous to the compiler. Simply match the 
		// appropriate interfaces and then cast to the most derived interface
		if (0 == strcmp(type, "IHen2") ||
			0 == strcmp(type, "IHen") ||
			0 == strcmp(type, "IObject"))
		{
			// It is duplicating the interface pointer
			// then increasing count
			AddRef();
			return static_cast<IHen2*>(this);
		}
		else if (0 == strcmp(type, "IOfflineChicken"))
		{
			AddRef();
			return static_cast<IOfflineChicken*>(this);
		}
		else
		{
			return nullptr;
		}
	}

	//
	// IHen
	//

	void __stdcall Cluck()
	{
		TRACE("Cluck\n");
	}

	void __stdcall Roost()
	{
		TRACE("Zzzzzz!\n");
	}

	//
	// IHen2
	//

	void __stdcall Forage()
	{
		TRACE("Forage!\n");
	}

	//
	// IOfflineChicken
	//

	void __stdcall Load(char const* /*file*/)
	{

	}

	void __stdcall Save(char const* /*file*/)
	{

	}
};

IHen* __stdcall CreateHen()
{
	IHen* result = new Hen;
	result->AddRef();
	return result;
}
#pragma once

/* The __stdcall calling convention is used to call Win32 API functions. The callee cleans the stack,
 * so the compiler makes vararg functions __cdecl. Functions that use this calling convention require
 * a function prototype.
 *
 * __stdcall is the standard and produces smaller code. */

 //void __stdcall HenCluck();



 // What the designers of COM discovered was that virtually all of the C++ compilers
 // on the windows platform happen to implement virtual functions in the same way. This 
 // was a key discovery. They then decided to take this coincidence as a blessing and
 // use it as the basis for COM's interface inheritance which enables polymorphism and
 // COM's version of OOP.

 // COM also expects methods to implement the standard calling convention. This too
 // is something that isn't standarized across compilers, but fortunately it's widely
 // supported thanks to the fact that the Windows API relies on it.


 // This is a demonstration how to export an object from a DLL. Although you can use
 // COM exclusively from within your application, it makes the most sense at the component
 // boundaries and the DLL represents the most common component boundary.
//struct IObject
//{
//	virtual void __stdcall AddRef() = 0;
//	virtual void __stdcall Release() = 0;
//
//	// There is no way that clients know about new features by extension.
//	// This is a similar mechanism to dynamic_cast for runtime discoverability.
//	virtual void* __stdcall  As(char const* type ) = 0;
//};

#include <unknwn.h>

// Use uuidgen | clip in command line to generate a GUID and copy it
// to clipboard


struct __declspec(uuid("10712e79-ef71-4e76-99c2-cefe92a1f910"))
IHen :  IUnknown
{
	// We need to keep the binary as simple as possible, not using C++ features that
	// might not be portable, and that excludes exporting the implementation class itself.
	virtual void __stdcall Cluck() = 0;
	virtual void __stdcall Roost() = 0;

	//virtual void __stdcall AddRef() = 0;
	//virtual void __stdcall Release() = 0;
};


struct __declspec(uuid("f7582a90-9a58-44fe-b054-bb2e75ea3f31"))
IHen2 : IHen
{
	virtual void __stdcall Forage() = 0;
};

struct __declspec(uuid("44422fc2-b7ea-4951-9e5d-d984458ea1de"))
IOfflineChicken : IUnknown
{
	virtual void __stdcall Load(char const* file) = 0;
	virtual void __stdcall Save(char const* file) = 0;
};

// A portable option then is to simply export a function for creating hens.

// Using the COM approach of returning an interface pointer as an outer 
// parameter. You give it an address of a pointer and it will copy the
// value of the pointer to that location
HRESULT __stdcall CreateHen(IHen** hen);
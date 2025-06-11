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
struct IObject
{
	virtual void __stdcall AddRef() = 0;
	virtual void __stdcall Release() = 0;

	// There is no way that clients know about new features by extension.
	// This is a similar mechanism to dynamic_cast for runtime discoverability.
	virtual void* __stdcall  As(char const* type ) = 0;
};

struct IHen :  IObject
{
	// We need to keep the binary as simple as possible, not using C++ features that
	// might not be portable, and that excludes exporting the implementation class itself.
	virtual void __stdcall Cluck() = 0;
	virtual void __stdcall Roost() = 0;

	//virtual void __stdcall AddRef() = 0;
	//virtual void __stdcall Release() = 0;
};

struct IHen2 : IHen
{
	virtual void __stdcall Forage() = 0;
};

struct IOfflineChicken : IObject
{
	virtual void __stdcall Load(char const* file) = 0;
	virtual void __stdcall Save(char const* file) = 0;
};

// A portable option then is to simply export a function for creating hens.
IHen* __stdcall CreateHen();
// using System.Runtime.InteropServices;

// // Run echo %processo_architecture% to check against which architecture we should compile
// //
// // Nex step is to check what processor de C++ compiler is targeting. Do this by 
// // running cl
// //
// // Run "csc /platform:x86 managed.cs" to compile against the same architecture as C++ compiler.
// // It might be possible that C++ compiler is targeting x64. 
// class Application
// {
	// static void Main()
	// {
		// HenCluck();
	// }
	
	
	// // DllImport attribute allows the compiler to know how to resolve the function.
	// // It is the equivalent of the linker's in Command Line option to tell the
	// // C# compiler how the function should be resolved
	// [DllImport("Library.dll")]
	// static extern void HenCluck();
// }


/**************************************************************************
/******************       IUnknown and modern C++       *******************
/**************************************************************************/

// This demonstrates dynamic linking of a C++ DLL from a C# app.
//
// The c++ app was able to simply include the library header file to get hold of
// the interface definitions. Unfortunately, C# has very little in common with C++,
// so the interfaces are redifined here.
//
using System.Runtime.InteropServices;

// The CLR is different to COM. CLR is not the evolution of COM. In order for COM
// and the CLR to interoperate, you need to do a bit work. Fortunately, COM defines
// this binary standard, and the CLR does a lot of work to implement that standard
// as needed, but it is not the way that the CLR's type system works naturally.
// There is some work to bridge the gap. The CLR supports COM, but not transparently.
// The IHen interface derives from IUnknown but the CLR hides the use of IUnknown's
// memebers, the reference counting and the extensibility via QueryInterface. It hides
// this functionality completely so that it can manage this inside the runtime on
// behalve of programmer.

// Instead of deriving from IUnknown, it is just necessary to indicate the CLR that
// this is an IUnknown based COM interface through an attribute
[InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
//The CLR also needs to know the UUID to query the interface
[Guid("10712e79-ef71-4e76-99c2-cefe92a1f910")]
interface IHen
{
	// In this case the CLR sees void and assumes a HRESULT. We can make the CLR to treat
	// the definition literally by using the [PreserveSig] attribute.
	[PreserveSig] void Cluck();
	[PreserveSig] void Roost();
}

// CLR implements virtual functions differently. In C# you must treat each interface as
// inheriting from IUnknown and build up the inheritance hierarchy manually to provide
// compatible v-tables.
[InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
[Guid("f7582a90-9a58-44fe-b054-bb2e75ea3f31")]
interface IHen2
{
	// IHen	
	[PreserveSig] void Cluck();
	[PreserveSig] void Roost();
	
	// IHen2
	[PreserveSig] void Forage();
}

[InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
[Guid("44422fc2-b7ea-4951-9e5d-d984458ea1de")]
interface IOfflineChicken
{
	[PreserveSig] void Load();
	[PreserveSig] void Save();
}

class Application
{
	static void Main()
	{
		IHen hen = CreateHen();
		hen.Cluck();
		hen.Roost();
		
		IHen2 hen2 = (IHen2)hen;
		hen2.Forage();
	}
	
	// This exported function really does return an HRESULT and it would be perfectly
	// acceptable for the CLR to convert this into an exception as needed. However, in
	// this case the CLR chooses to treat the signature literally by default and not assume
	// that it might return an HRESULT.
	[DllImport("Library.dll", PreserveSig = false)]
	static extern IHen CreateHen();
}
	
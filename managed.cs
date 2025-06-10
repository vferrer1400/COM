using System.Runtime.InteropServices;

// Run echo %processo_architecture% to check against which architecture we should compile
//
// Nex step is to check what processor de C++ compiler is targeting. Do this by 
// running cl
//
// Run "csc /platform:x86 managed.cs" to compile against the same architecture as C++ compiler.
// It might be possible that C++ compiler is targeting x64. 
class Application
{
	static void Main()
	{
		HenCluck();
	}
	
	
	// DllImport attribute allows the compiler to know how to resolve the function.
	// It is the equivalent of the linker's in Command Line option to tell the
	// C# compiler how the function should be resolved
	[DllImport("Library.dll")]
	static extern void HenCluck();
}

#include "Library.h"

// To compile the application in dev command line
// cl /W4 Application.cpp Library.def

// Dependency Walker a useful app to review linking problems
// int main()
// {
	// HenCluck();
	// return 0;
// }

int main()
{
	IHen* hen = CreateHen();
	hen->Cluck();
	hen->Roost();

	/* In order for this to work, the IHen interface needs a virtual destructor.
	 * As it stands, it has no destructor at all. Adding a virtual destructor simply
	 * introduces a new problem. Calling "delete" is compiler specific. Using 
	 * "delete" for an object that wasn't created using new operator might yield
	 * to unpredictable results.*/

	// delete hen;

	hen->Release();
}
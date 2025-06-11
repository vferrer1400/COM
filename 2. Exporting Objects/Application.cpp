#include "Library.h"

// To compile the application in dev command line
// cl /W4 Application.cpp Library.def

// Dependency Walker a useful app to review linking problems
// int main()
// {
	// HenCluck();
	// return 0;
// }

struct A
{
	int val = 5;
};

struct B : A
{
	int val2 = 6;
};

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

	IHen2* hen2 = static_cast<IHen2*>(hen->As("IHen2"));
	if (hen2)
	{
		hen2->Forage();
		hen2->Release();
		hen2 = nullptr;
	}

	IOfflineChicken* offline = static_cast<IOfflineChicken*>(hen->As("IOfflineChicken"));
	if (offline)
	{
		offline->Save("filename");
		offline->Release();
		offline = nullptr;
	}
	hen->Release();
	hen = nullptr;
}
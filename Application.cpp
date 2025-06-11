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
	IHen * hen = CreateHen();
	hen->Cluck();
	hen->Roost();

	delete hen;
}
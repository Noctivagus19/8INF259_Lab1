//
// D�velopp� par:
// Jean-Michel Plourde PLOJ07029207
// Jean-Pilippe Lapointe LAPJ16078607
//

#include "Dossier.h"
#include <iostream>
using namespace std;

int main()
{
	char FP[] = "FP.txt";
	char FT[] = "FT.txt";
	DossierProfesseur * docProf = new DossierProfesseur(FP);

	docProf->executerCommandes(FP, FT);

	system("PAUSE");
	return 0;
}
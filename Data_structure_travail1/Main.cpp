//#include "stdafx.h"
#include "Dossier.h"
#include <iostream>
using namespace std;

int main()
{
	char FP[] = "C:/FP.txt";
	DossierProfesseur * docProf = new DossierProfesseur(FP);

	docProf->afficherListe();

	system("PAUSE");
	return 0;
}
//#include "stdafx.h"
#include "Dossier.h"
#include <iostream>
using namespace std;

int main()
{
	char FP[] = "C:/FP.txt";
	DossierProfesseur * docProf = new DossierProfesseur(FP);

	docProf->afficherListe();

	docProf->afficherleprofplusetudiants();
	docProf->affichercoursplusdemande();
	system("PAUSE");
	return 0;
}
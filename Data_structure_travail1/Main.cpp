//#include "stdafx.h"
#include "Dossier.h"
#include <iostream>
using namespace std;

int main()
{
	char FP[] = "C:/FP.txt";
	DossierProfesseur * docProf = new DossierProfesseur(FP);

	docProf->afficherListe();
	docProf->executerCommandes();
	docProf->afficherListe();
	docProf->afficherCoursPlusDemande();
	system("PAUSE");
	return 0;
}
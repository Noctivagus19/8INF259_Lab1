//#include "stdafx.h"
#include "Dossier.h"
#include <iostream>
using namespace std;

int main()
{
	char FP[] = "C:/FP.txt";
	DossierProfesseur * docProf = new DossierProfesseur(FP);

	docProf->afficherLeProfPlusEtudiants();
	docProf->supprimerProf("Professeur 1");
	std::cout << "//////////////////////////////////////////////\n";
	docProf->afficherLeProfPlusEtudiants();
	docProf->supprimerProf("Professeur 3");
	std::cout << "//////////////////////////////////////////////\n";
	docProf->afficherLeProfPlusEtudiants();
	docProf->supprimerProf("Professeur 2");
	std::cout << "//////////////////////////////////////////////\n";
	docProf->afficherLeProfPlusEtudiants();

	system("PAUSE");
	return 0;
}
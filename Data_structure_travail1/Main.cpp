//#include "stdafx.h"
#include "Dossier.h"
#include <iostream>
using namespace std;

int main()
{
	char FP[] = "C:/docprof/FP.txt";
	DossierProfesseur * docProf = new DossierProfesseur(FP);

	docProf->executerCommandes(FP);
	docProf->afficherListe();
	
	//std::cout << "Professeur ayant le plus d'etudiants : " << *docProf->afficherLeProfPlusEtudiants() << endl;

	//std::cout << "Le cours le plus demande est: " << *docProf->afficherCoursPlusDemande() << endl;

	//string coursDonne = "GEI103";
	//cout << "Le nombre de professeurs pour le cours " << coursDonne << " est : " << docProf->afficherNbreProfPourUnCours(&coursDonne) << endl;

	//docProf->recopier(FP);

	system("PAUSE");
	return 0;
}
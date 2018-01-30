//#include "stdafx.h"
#include "Dossier.h"
#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
using namespace std;

#define NOMPROF 0
#define ANCIENETE 1
#define COURS 2
#define ETUDIANTS 3


DossierProfesseur::DossierProfesseur(char* FP)
{
	Professeur *courantProf;
	DossierProfesseur * docProf = (DossierProfesseur*)malloc(sizeof(DossierProfesseur));
	tete = (Professeur*)malloc(sizeof(Professeur));
	courantProf = tete;

	Cours* courantCours = (Cours*)malloc(sizeof(Cours));
	tete->listeCours = courantCours;

	Etudiant* courantEtudiant = (Etudiant*)malloc(sizeof(Etudiant));
	tete->listeEtudiants = courantEtudiant;


	ifstream dataSource(FP);
	if (dataSource)
	{
		string ligne;
		int curseur = 0; 

		while (getline(dataSource, ligne))
		{
			switch (curseur)
			{
			case NOMPROF:
				{	
				courantProf->nom = new string;
				*courantProf->nom = ligne;
				curseur++;
				}
				break;

			case ANCIENETE:
				{
				courantProf->ancien = new int;
				*courantProf->ancien = atoi(ligne.c_str());
				curseur++;
				}
				break;

			case COURS:
				{
				if (ligne[0] == '&')
				{
					curseur++;
					goto labelFin;
				}
				Cours *nouveauCours = (Cours*)malloc(sizeof(Cours));
				courantCours->sigle = new string;
				*courantCours->sigle = ligne;
				courantCours->suivant = nouveauCours;
				courantCours = courantCours->suivant;
				}
				labelFin:
				break;

			case ETUDIANTS:
			{
				if (ligne[0] == '&')
				{
					curseur++;
					goto labelFin2;
				}
				Etudiant *nouvelEtudiant = (Etudiant*)malloc(sizeof(Etudiant));
				courantEtudiant->nom = new string;
				*courantEtudiant->nom = ligne;
				courantEtudiant->apres = nouvelEtudiant;
				courantEtudiant = courantEtudiant->apres;
				break;
				labelFin2:
				curseur = 0;
				Professeur *nouveauProf = (Professeur*)malloc(sizeof(Professeur));
				courantProf->suivant = nouveauProf;
				courantProf = courantProf->suivant;
				courantCours = (Cours*)malloc(sizeof(Cours));
				courantProf->listeCours = courantCours;
				courantEtudiant = (Etudiant*)malloc(sizeof(Etudiant));
				courantProf->listeEtudiants = courantEtudiant;
				}
				break;
			}
		}
		dataSource.close();
	}
}


DossierProfesseur::~DossierProfesseur()
{

}

void DossierProfesseur::Afficher()
{
	Professeur * courantProfesseur = tete;
	Cours * courantCours = tete->listeCours;
	Etudiant * courantEtudiant = tete->listeEtudiants;

	/*try {
		while (courantProfesseur != NULL)
		{
			cout << *courantProfesseur->nom << endl;
			courantProfesseur = courantProfesseur->suivant;
		}
	}
	catch (exception e){}*/

	for (int i = 0; i < 3; i++)
	{
		cout << *courantProfesseur->nom << endl << *courantProfesseur->ancien << endl << *courantProfesseur->listeCours->sigle << endl
			<< *courantProfesseur->listeCours->suivant->sigle << endl << *courantProfesseur->listeCours->suivant->suivant->sigle
			<< endl << *courantProfesseur->listeEtudiants->nom << endl << *courantProfesseur->listeEtudiants->apres->nom << endl <<
			*courantProfesseur->listeEtudiants->apres->apres->nom << endl;
		courantProfesseur = courantProfesseur->suivant;
	}
	
}

void DossierProfesseur::executerCommandes()
{
	ifstream ftFile("C:/FT.txt");
	if (ftFile.is_open())
	{
		std::vector<string> linesVector;

		copy(istream_iterator<string>(ftFile),
			istream_iterator<string>(),
			back_inserter(linesVector));

		for (std::vector<string>::const_iterator i = linesVector.begin(); i != linesVector.end(); ++i)
		{
			std::cout << i->at(0) << "\n"; /* Isolation de l'opérateur */
			//string lineParam = i->substr(1, i->size() - 1);
		}
	}
}
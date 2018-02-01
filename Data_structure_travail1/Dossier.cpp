//#include "stdafx.h"
#include "Dossier.h"
#include <iostream>
#include <string>
#include <fstream>
#include <string>
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
					courantCours->sigle = NULL;
					courantCours = NULL;
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
					courantEtudiant->nom = NULL;
					courantEtudiant = NULL;
					//delete courantEtudiant;
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
		courantProf->nom = NULL;
		courantProf = NULL;


		dataSource.close();
	}
}


DossierProfesseur::~DossierProfesseur()
{

}

void DossierProfesseur::Afficher()
{
	Professeur * courantProfesseur = tete;
	Cours * courantCours = courantProfesseur->listeCours;
	Etudiant * courantEtudiant = courantProfesseur->listeEtudiants;

	try {
		while (courantProfesseur->nom)
		{
			cout << *courantProfesseur->nom << endl;
			cout << *courantProfesseur->ancien << endl;

			while (courantCours->sigle)
			{
				cout << *courantCours->sigle << endl;
				courantCours = courantCours->suivant;
			}

			while (courantEtudiant->nom)
			{
				cout << *courantEtudiant->nom << endl;
				courantEtudiant = courantEtudiant->apres;
			}
			courantProfesseur = courantProfesseur->suivant;
			courantCours = courantProfesseur->listeCours;
			courantEtudiant = courantProfesseur->listeEtudiants;
		}
	}
	catch (exception e) {}

	/*for (int i = 0; i < 3; i++)
	{
	cout << *courantProfesseur->nom << endl << *courantProfesseur->ancien << endl << *courantProfesseur->listeCours->sigle << endl
	<< *courantProfesseur->listeCours->suivant->sigle << endl << *courantProfesseur->listeCours->suivant->suivant->sigle
	<< endl << *courantProfesseur->listeEtudiants->nom << endl << *courantProfesseur->listeEtudiants->apres->nom << endl <<
	*courantProfesseur->listeEtudiants->apres->apres->nom << endl;
	courantProfesseur = courantProfesseur->suivant;
	}*/

}

void DossierProfesseur::executerCommandes()
{
	ifstream dataSource("C:/FT.txt");
	if (dataSource.is_open())
	{
		string line;
		string cmdOperator;
		string cmdParam;
		string startDelim = "[";
		string stopDelim = "]";
		unsigned firstDelimPos;
		unsigned endPosDelim;
		unsigned lastDelimPos;

		while (getline(dataSource, line))
		{
			/* Operator extraction */
			cmdOperator = line.substr(0, 1);
			
			/* Operator parameter extraction*/
			firstDelimPos = line.find(startDelim);
			endPosDelim = firstDelimPos + startDelim.length();
			lastDelimPos = line.find(stopDelim);
			cmdParam = line.substr(endPosDelim, lastDelimPos - endPosDelim);

			std::cout << "Operator: " << cmdOperator << " Parameter: ";
			if (!cmdParam.empty())
			{
				std::cout << cmdParam;
			}
			else
			{
				std::cout << "N/A";
			}
			std::cout << "\n";			
		}
	}
}
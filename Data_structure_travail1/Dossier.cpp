#include "Dossier.h"
#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#define NOMPROF 0
#define ANCIENETE 1
#define COURS 2
#define ETUDIANTS 3

DossierProfesseur::DossierProfesseur(char* FP)
{
	/*  Variables Cours */
	teteCours = NULL;

	/* Variables Etudiant */
	teteEtudiant = NULL;

	/*  Variables Professeur*/
	teteProf = NULL;
	string nomProf;
	int ancienProf = 0;

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
				nomProf = ligne;
				curseur++;
				break;
			}

			case ANCIENETE:
			{
				ancienProf = atoi(ligne.c_str());
				curseur++;
				break;
			}

			case COURS:
			{
				if (ligne[0] == '&')
				{
					curseur++;
					goto labelFin;
				}
				Cours *c = new Cours();
				c->sigle = new string();
				*c->sigle = ligne;

				c->suivant = teteCours;
				teteCours = c;
			labelFin:
				break;
			}

			case ETUDIANTS:
			{
				if (ligne[0] == '&')
				{
					curseur++;
					goto labelFin2;
				}
				Etudiant *e = new Etudiant();
				e->nom = new string();
				*e->nom = ligne;

				e->suivant = teteEtudiant;
				teteEtudiant = e;
				break;
			labelFin2:
				curseur = 0;
				Professeur *p = new Professeur();
				p->nom = new string();
				*p->nom = nomProf;
				p->ancien = new int();
				*p->ancien = ancienProf;
				p->listeCours = teteCours;
				p->listeEtudiants = teteEtudiant;

				p->suivant = teteProf;
				teteProf = p;
				teteCours = NULL;
				teteEtudiant = NULL;
				break;
			}
			}
		}

		dataSource.close();
	}
}

DossierProfesseur::~DossierProfesseur()
{
	Professeur *next = teteProf;

	while (next)
	{
		Cours *c = next->listeCours;
		while (c)
		{
			Cours *deleteMe = c;
			c = c->suivant;
			delete deleteMe;
		}
		Etudiant *e = next->listeEtudiants;
		while (e)
		{
			Etudiant *deleteMe = e;
			e = e->suivant;
			delete deleteMe;
		}
		Professeur *deleteMe = next;
		next = next->suivant;
		delete deleteMe;
	}
}

void DossierProfesseur::popValue()
{
	if (teteProf != NULL)
	{
		Professeur *p = teteProf;
		std::cout << p->nom << "\n";
		std::cout << "Anciennete: " << p->ancien << "\n";

		teteProf = teteProf->suivant;
		delete p;
	}
	else
	{
		std::cout << "La liste est vide\n";
	}
}

void DossierProfesseur::afficherListe()
{
	Professeur *p = teteProf;

	if (p)
	{
		while (p)
		{
			Cours *c = p->listeCours;
			Etudiant *e = p->listeEtudiants;
			std::cout << *p->nom << "\n";
			std::cout << "Anciennete: " << *p->ancien << "\nCours enseignes: ";
			if (c != NULL)
			{
				std::cout << "\n";
				while (c)
				{
					std::cout << *c->sigle << "\n";
					c = c->suivant;
				}
			}
			else
			{
				std::cout << "Ce professeur n'a aucun cours!\n";
			}
			std::cout << "Etudiants: ";
			if (e != NULL) {
				std::cout << "\n";
				while (e != NULL)
				{
					std::cout << *e->nom << "\n";
					e = e->suivant;
				}
			}
			else
			{
				std::cout << "Ce professeur n'a aucun etudiant!\n";
			}
			std::cout << "\n";
			p = p->suivant;
		}
	}
	else
	{
		std::cout << "Il n'y a aucun professeur a afficher!\n";
	}
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
			cmdParam = line.substr(line.find(' ') + 1 );

			if (cmdOperator == "-")
			{
				supprimerProf(cmdParam);
			}
			else if (cmdOperator == "#")
			{
				afficherLeProfPlusEtudiants();
			}
			else if (cmdOperator == "*")
			{
				afficherCoursPlusDemande();
			}
			else if (cmdOperator == "%")
			{
				std::cout << "Display numbr of prof wanting to teach " << cmdParam << "\n";
			}
			else if (cmdOperator == "$")
			{
				std::cout << "Save list in memory to FP.txt\n";
			}
			std::cout << "\n";
		}
	}
}

void DossierProfesseur::afficherLeProfPlusEtudiants()
{
	Professeur * courantProf = teteProf;
	Etudiant * courantEtudiant;
	Professeur * profPlusEtudiants = teteProf;
	int cptEtudiants = 0, lePlusEtudiants = 0;

	while (courantProf != NULL)
	{
		courantEtudiant = courantProf->listeEtudiants;
		cptEtudiants = 0;

		while (courantEtudiant)
		{
			cptEtudiants++;
			courantEtudiant = courantEtudiant->suivant;
		}

		if (cptEtudiants > lePlusEtudiants)
		{
			lePlusEtudiants = cptEtudiants;
			profPlusEtudiants = courantProf;
		}

		courantProf = courantProf->suivant;
		
	}

	if (profPlusEtudiants != NULL)
	{
		std::cout << "Professeur ayant le plus d'etudiants : " << *profPlusEtudiants->nom << "\nNombre d'etudiants: " << lePlusEtudiants << endl;
	}
	else
	{
		std::cout << "Le dossier ne contient aucun professeur!\n";
	}

}

void DossierProfesseur::afficherCoursPlusDemande()
{
	Professeur * courantProf = teteProf;
	Professeur * profCoursPlusDemande = courantProf;
	Cours * courantCours = NULL;
	Cours * coursPlusDemande = NULL;

	vector<Cours*> vecteurCours(0);
	vector<int> vecteurNbCours(0);
	vector<Professeur*> vecteurProfs(0);

	vector<int> lesPlusDemandes(0);

	int a = 0 , b = 0, nombrePlusDemande=0;

	while (courantProf != NULL)
	{
		courantCours = courantProf->listeCours;
		bool trouve = false;

		while (courantCours != NULL)
		{
			for (a = 0; a < vecteurCours.size(); a++)
			{
				bool trouve = false;
				if (*vecteurCours[a]->sigle == *courantCours->sigle)
				{
					vecteurNbCours[a] = vecteurNbCours[a] + 1;
					bool trouve = true;
				}
			}

			if (trouve == false)
			{
				vecteurCours.push_back(courantCours);
				vecteurProfs.push_back(courantProf);
				vecteurNbCours.push_back(1);
			}
			courantCours = courantCours->suivant;
		}

		courantProf = courantProf->suivant;
		

	}

	for (a = 0; a < vecteurNbCours.size(); a++)
	{
		if (vecteurNbCours[a] > nombrePlusDemande)
		{
			nombrePlusDemande = vecteurNbCours[a];
		}
	}

	for (a = 0; a < vecteurNbCours.size(); a++) 
	{
		if (vecteurNbCours[a] == nombrePlusDemande)
		{
			lesPlusDemandes.push_back(a);
		}
	}

	if (lesPlusDemandes.size() > 1)
	{
		int lePlusAncien = 0;
		Professeur * profLePlusAncien = NULL;
		for (a = 0; a < lesPlusDemandes.size(); a++)
		{
			if (*vecteurProfs[lesPlusDemandes[a]]->ancien > lePlusAncien)
			{
				lePlusAncien = *vecteurProfs[lesPlusDemandes[a]]->ancien;
				profLePlusAncien = vecteurProfs[lesPlusDemandes[a]];
				
			}
		}

		for (a = 0; a < lesPlusDemandes.size(); a++)
		{
			if (*vecteurProfs[lesPlusDemandes[a]]->nom == *profLePlusAncien->nom)
			{
				std::cout << "Le cours le plus demande est: " << *vecteurCours[lesPlusDemandes[a]]->sigle << "\nCe cours est enseigne " << vecteurNbCours[lesPlusDemandes[a]]
					<< " fois ce semestre\n" << "Professeur responsable du cours: " << *vecteurProfs[lesPlusDemandes[a]]->nom << endl;
				break;
			}
		}
		

	}
	else if (lesPlusDemandes.size() < 1)
	{
		std::cout << "Le dossier ne contient aucun professeur!\n";
	}
	else
	{
		std::cout << "Le cours le plus demande est: " << *vecteurCours[lesPlusDemandes[0]]->sigle << "\nCe cours est enseigne " << vecteurNbCours[lesPlusDemandes[0]]
			<< " fois ce semestre\n" << "Professeur responsable du cours: " << *vecteurProfs[lesPlusDemandes[0]]->nom << endl;
	}

}

void DossierProfesseur::supprimerProf(string nomProf)
{
	Professeur *profCourant = teteProf;
	Professeur *lastProf = NULL;
	Professeur *deleteMe;
	int deleteCount = 0;

	while (profCourant)
	{
		if (nomProf == *profCourant->nom)
		{
			deleteMe = profCourant;
			if (lastProf == NULL) // Suppression de l'�l�ment de t�te
			{
				lastProf = profCourant->suivant;
				teteProf = lastProf;
			}
			else // Suppression d'un �l�ment � une position n > 2
			{
				lastProf->suivant = profCourant->suivant;
			}
			profCourant = profCourant->suivant;
			std::cout << "Le professeur " << *deleteMe->nom << " a ete supprime!\n";
			delete deleteMe;
			++deleteCount;
		} 
		else
		{
			lastProf = profCourant;
			profCourant = profCourant->suivant;
		}
	}
}
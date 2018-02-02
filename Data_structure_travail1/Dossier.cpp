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
				c->sigle = ligne;

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
				e->nom = ligne;

				e->suivant = teteEtudiant;
				teteEtudiant = e;
				break;
			labelFin2:
				curseur = 0;
				Professeur *p = new Professeur();
				p->nom = nomProf;
				p->ancien = ancienProf;
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
			std::cout << p->nom << "\n";
			std::cout << "Anciennete: " << p->ancien << "\n" << "Cours enseignes: ";
			if (c != NULL)
			{
				std::cout << "\n";
				while (c)
				{
					std::cout << c->sigle << "\n";
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
					std::cout << e->nom << "\n";
					e = e->suivant;
				}
			}
			else
			{
				std::cout << "Ce professeur n'a aucun etudiants!\n";
			}
			std::cout << "\n";
			p = p->suivant;
		}
	}
	else
	{
		std::cout << "Il n'y a aucun professeurs a afficher!\n";
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
				cout << "Delete prof " << cmdParam << "\n";
			}
			else if (cmdOperator == "#")
			{
				cout << "Display prof with most students\n";
			}
			else if (cmdOperator == "*")
			{
				cout << "Display most wanted course\n";
			}
			else if (cmdOperator == "%")
			{
				cout << "Display numbr of prof wanting to teach " << cmdParam << "\n";
			}
			else if (cmdOperator == "$")
			{
				cout << "Save list in memory to FP.txt\n";
			}
		}
	}
}
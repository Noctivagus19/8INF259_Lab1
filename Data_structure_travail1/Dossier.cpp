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


//Constructeur
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
			switch (curseur) //Structure de séparation des données pour la création des structures
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


//Cette fonction parcours toutes les structures de Professeurs, compte les étudiants et affiche le prof qui en a le plus
string* DossierProfesseur::afficherLeProfPlusEtudiants()
{
	Professeur * courantProf = teteProf;
	Etudiant * courantEtudiant;
	Professeur * profPlusEtudiants = teteProf;
	int cptEtudiants = 0, lePlusEtudiants = 0;

	while (courantProf != NULL)		//Parcourir les structures
	{
		courantEtudiant = courantProf->listeEtudiants;
		cptEtudiants = 0;

		while (courantEtudiant)	//Compteur d'étudiants
		{
			cptEtudiants++;
			courantEtudiant = courantEtudiant->suivant;
		}

		if (cptEtudiants > lePlusEtudiants)	//Sauvegarde le nombre d'étudiants le plus élevé et le Professeur associé
		{
			lePlusEtudiants = cptEtudiants;
			profPlusEtudiants = courantProf;
		}

		courantProf = courantProf->suivant;
		
	}

	if (profPlusEtudiants != NULL) // Affiche le professeur ayant le plus d'étudiants
	{
		return profPlusEtudiants->nom;
	}
	else
	{
		std::cout << "Le dossier ne contient aucun professeur!\n";
	}

}


//Cette fonction va parcourir toutes les structures et va charger tous les cours demandés dans un vecteur.
//2 autres vecteurs vont contenir le professeur associé et le nombre de demandes.
//Finalement le cours le plus demandé (priorité à l'ancienneté du Professeur, premier rencontré) est affiché.

string* DossierProfesseur::afficherCoursPlusDemande()
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

	while (courantProf != NULL) //Lecture de tous les Professeurs
	{
		courantCours = courantProf->listeCours;
		bool trouve = false;

		while (courantCours != NULL) //Lecture de tous les Cours
		{
			for (a = 0; a < vecteurCours.size(); a++)	//Parcourir le vecteur de cours
			{
				bool trouve = false;
				if (*vecteurCours[a]->sigle == *courantCours->sigle)	//Si le vecteur existe deja
				{
					vecteurNbCours[a] = vecteurNbCours[a] + 1;			//Incrementer le nombre de demande dans le vecteur nombre cours
					bool trouve = true;

					if (courantProf->ancien > vecteurProfs[a]->ancien)		//Assure que le professeur associé au cours est bien celui qui a le plus d'ancienneté
					{
						vecteurProfs[a] = courantProf;
					}
				}
			}

			if (trouve == false)	//Si le cours n'existe pas dans le vecteur
			{
				vecteurCours.push_back(courantCours);		//Ajouter le cours au vecteur
				vecteurProfs.push_back(courantProf);		//Ajouter le prof au vecteur
				vecteurNbCours.push_back(1);				//Ajouter le nombre de cours au vecteur
			}
			courantCours = courantCours->suivant;
		}

		courantProf = courantProf->suivant;
		

	}

	for (a = 0; a < vecteurNbCours.size(); a++)	//Parcourir le vecteur à la recherche du nombre de demandes le plus élevé
	{
		if (vecteurNbCours[a] > nombrePlusDemande)
		{
			nombrePlusDemande = vecteurNbCours[a];
		}
	}

	for (a = 0; a < vecteurNbCours.size(); a++) //Parcourir le vecteur à la recherche du ou des cours les plus demandés
	{
		if (vecteurNbCours[a] == nombrePlusDemande)
		{
			lesPlusDemandes.push_back(a);		//Charger le ou les plus demandés dans un vecteur
		}
	}

	if (lesPlusDemandes.size() > 1)	//Si il y a plus d'un cours dans les plus demandés
	{
		int lePlusAncien = 0;
		Professeur * profLePlusAncien = NULL;
		for (a = 0; a < lesPlusDemandes.size(); a++)	//Parcourir le vecteur des plus demandés
		{
			if (*vecteurProfs[lesPlusDemandes[a]]->ancien > lePlusAncien)	//Verifie l'ancienneté des professeurs et charge la première valeur d'ancienneté la plus élevée
			{
				lePlusAncien = *vecteurProfs[lesPlusDemandes[a]]->ancien;
				profLePlusAncien = vecteurProfs[lesPlusDemandes[a]];
				
			}
		}

		for (a = 0; a < lesPlusDemandes.size(); a++)	//Parcours le vecteur des cours les plus demandés à la recherche du Prof ayant le plus d'ancienneté
		{
			if (*vecteurProfs[lesPlusDemandes[a]]->nom == *profLePlusAncien->nom)	//Si le prof est trouvé, afficher le cours
			{
				return vecteurCours[lesPlusDemandes[a]]->sigle;
			}
		}
		

	}
	else if (lesPlusDemandes.size() < 1)	//Si seulement un cours se trouve dans le vecteur des plus demandés, alors afficher
	{
		std::cout << "Le dossier ne contient aucun professeur!\n";
	}
	else
	{
		return vecteurCours[lesPlusDemandes[0]]->sigle;
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
			if (lastProf == NULL) // Suppression de l'élément de tête
			{
				lastProf = profCourant->suivant;
				teteProf = lastProf;
			}
			else // Suppression d'un élément à une position n > 2
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


//Cette fonction compte le nombre de professeurs qui donnent un cours spécifique
int DossierProfesseur::afficherNbreProfPourUnCours(string* coursDonne)
{
	Professeur * courantProf = teteProf;
	Cours * courantCours = NULL;
	int nombreProfs = 0;

	while (courantProf != NULL) //Lecture de tous les Professeurs
	{
		courantCours = courantProf->listeCours;

		while (courantCours != NULL)
		{
			if (*courantCours->sigle == *coursDonne) //si le cours courant est celui qu'on cherche
			{
				nombreProfs++;	//Incrementer le compteur de profs
				courantCours = NULL;
				break;
			}
			else
			{
				courantCours = courantCours->suivant;
			}
		}
		courantProf = courantProf->suivant;
	}
	return nombreProfs;
}
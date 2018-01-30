#include <string>
using namespace std;

struct Cours
{
	string *sigle;
	Cours *suivant;
};

struct Etudiant
{
	string *nom;
	Etudiant* apres;
};

struct Professeur
{
	string *nom;
	int* ancien;
	Cours* listeCours;
	Etudiant* listeEtudiants;
	Professeur* suivant;
};

class DossierProfesseur
{
private:
	Professeur* tete; /* D�but de la liste cha�n�e */

public:
	DossierProfesseur(char* FP); /* Constructuer � partir du fichier FP*/

	~DossierProfesseur(); /* Destructeur */

	void supprimer(string* name); /* Supprimer de la liste le prof sp�cifi� */

	char* afficherProfAvecPlusEtudiants(); /* Afficher prof avec plus d'�tudiants */

	char* afficherCoursPlusDemande(); /* Afficher cours le plus demand�. En cas d'�galit�, choisit le plus ancien */

	int afficherNbreProfPourUnCours(string* coursdonne); /* Afficher nb de profs pour un cours */

	void sauvegarderListe(string *FP); /* Recopie liste cha�n�e dans fichier FP */

	void Afficher(); // Pour faire des tests

	void executerCommandes();
};



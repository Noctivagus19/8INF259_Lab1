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
	Professeur* tete; /* Début de la liste chaînée */

public:
	DossierProfesseur(char* FP); /* Constructuer à partir du fichier FP*/

	~DossierProfesseur(); /* Destructeur */

	void supprimer(string* name); /* Supprimer de la liste le prof spécifié */

	char* afficherProfAvecPlusEtudiants(); /* Afficher prof avec plus d'étudiants */

	char* afficherCoursPlusDemande(); /* Afficher cours le plus demandé. En cas d'égalité, choisit le plus ancien */

	int afficherNbreProfPourUnCours(string* coursdonne); /* Afficher nb de profs pour un cours */

	void sauvegarderListe(string *FP); /* Recopie liste chaînée dans fichier FP */

	void Afficher(); // Pour faire des tests
};



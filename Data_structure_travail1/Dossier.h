#include <string>
using namespace std;

class DossierProfesseur
{
	struct Cours
	{
		string *sigle;

		Cours *suivant;
	};

	struct Etudiant
	{
		string *nom;

		Etudiant *suivant;
	};

	struct Professeur
	{
		string *nom;
		int *ancien;

		Cours *listeCours;
		Etudiant *listeEtudiants;
		Professeur *suivant;
	};

private:
	Cours *teteCours;
	Etudiant *teteEtudiant;
	Professeur *teteProf;

public:
	// constructor
	DossierProfesseur(char *FP);

	// destructor
	~DossierProfesseur();

	void addProf(string nomParam, int ancienParam);
	void popValue();
	void DossierProfesseur::afficherListe();
	void DossierProfesseur::executerCommandes(char* FP);
	void DossierProfesseur::supprimerProf(string nomProf);
	string* DossierProfesseur::afficherLeProfPlusEtudiants();
	string* DossierProfesseur::afficherCoursPlusDemande();
	int DossierProfesseur::afficherNbreProfPourUnCours(string* coursDonne);
	void DossierProfesseur::recopier(char*FP);
	
};

struct Cours
{
	char *sigle;
	Cours *suivant;
};

struct Etudiant
{
	char* nom;
	Etudiant* apres;
};

struct Professeur
{
	char* nom;
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

		void supprimer(char* name); /* Supprimer de la liste le prof sp�cifi� */

		char* afficherleprofplusetudiant() const; /* Afficher prof avec plus d'�tudiants */
		
		char* affichercoursplusdemande() const; /* Afficher cours le plus demand�. En cas d'�galit�, choisit le plus ancien */

		int affichernbreprofpouruncours(char* coursdonne) const; /* Afficher nb de profs pour un cours */

		void recopier(char *FP); /* Recopie liste cha�n�e dans fichier FP */
};
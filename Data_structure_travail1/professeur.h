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
		Professeur* tete; /* Début de la liste chaînée */

	public:
		DossierProfesseur(char* FP); /* Constructuer à partir du fichier FP*/
		~DossierProfesseur(); /* Destructeur */

		void supprimer(char* name); /* Supprimer de la liste le prof spécifié */

		char* afficherleprofplusetudiant() const; /* Afficher prof avec plus d'étudiants */
		
		char* affichercoursplusdemande() const; /* Afficher cours le plus demandé. En cas d'égalité, choisit le plus ancien */

		int affichernbreprofpouruncours(char* coursdonne) const; /* Afficher nb de profs pour un cours */

		void recopier(char *FP); /* Recopie liste chaînée dans fichier FP */
};
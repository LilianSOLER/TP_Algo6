

/* structure noeud presentee en cours */


typedef struct n {
  
  int      t         ; /* t type de noeud 0, 2, 3 ou 4 */
  int      cles  [3] ;
  struct n *fils [4] ;
  
} noeud234, *pnoeud234 ;

/* type Arbre, pointeur vers un noeud */

typedef pnoeud234 Arbre234 ;

Arbre234 lire_arbre (char *nom_fichier) ;

void afficher_arbre (Arbre234 a, int niveau) ;

void ajouter_cle (Arbre234 *a, int cle, int niveau, Arbre234 pere) ;

/* Prototypes des fonctions implémentées durant le TP */
/* Les fonctions prototypées ici sont celles qui sont opérationnelles */

int hauteur (Arbre234 a);

int NombreCles (Arbre234 a);

int CleMax (Arbre234 a);

int CleMin (Arbre234 a);

Arbre234 RechercherCle (Arbre234 a, int cle);

void AnalyseStructureArbre (Arbre234 a, int *feuilles, int *noeud2, int *noeud3, int *noeud4);

int sommeNoeud(Arbre234 a);

Arbre234 noeud_max (Arbre234 a);

void Afficher_Cles_Largeur (Arbre234 a);

void Affichage_Cles_Triees_Recursive (Arbre234 a);


typedef struct a *parc_t;

/*
  definition des types sommet et pointeur de sommet
  un graphe est constitué d'une liste de sommets
*/

typedef struct s
{
  int label;                // label du sommet
  parc_t liste_arcs;        // arcs sortants du sommet
  struct s *sommet_suivant; // sommet suivant dans le graphe
  int couleur;              // couleur du sommet
  int explore;
  // Vaut 0 si le sommet n'est pas encore exploré (utilisé dans parcours en profondeur)
  // Vaut 1 si le sommet n'est pas encore TOTALEMENT exploité
  // Vaut 2 si le sommet est totalement exploité
} sommet_t, *psommet_t;

/*
  definition des types arc et pointeur d'arc
  Les arcs sortants d'un sommet sont chainés
  Pour chaque arc, il y a un poids qui peut par exemple correspondre a une distance
*/

typedef struct a
{

  int poids;             // poids de l arc
  psommet_t dest;        // pointeur sommet destinataire
  struct a *arc_suivant; // arc suivant

} arc_t, *parc_t;

/*
  pgraphe_t: pointeur vers le premier sommet d'un graphe
*/
typedef psommet_t pgraphe_t;

typedef struct c
{
  psommet_t start;
  parc_t arc;
  struct c *suivant;
} chemin_t, *pchemin_t;
typedef psommet_t pgraphe_t;

psommet_t chercher_sommet(pgraphe_t g, int label);

void ajouter_arc(psommet_t o, psommet_t d, int distance);

int nombre_arcs(pgraphe_t g);

int nombre_sommets(pgraphe_t g);

void lire_graphe(char *file_name, pgraphe_t *g);

void ecrire_graphe(psommet_t p);

void ecrire_graphe_colorie(psommet_t p);

int colorier_graphe(pgraphe_t g);

void afficher_graphe_profondeur(pgraphe_t g, int r);

void afficher_graphe_largeur(pgraphe_t g, int r);

void algo_dijkstra(pgraphe_t g, int r);

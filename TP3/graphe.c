/*
  Structures de type graphe
  Structures de donnees de type liste
  (Pas de contrainte sur le nombre de noeuds des  graphes)
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "graphe.h"
#include "pile.h"
#include "file.h"

int appartient_tableau(parc_t *tableau, parc_t p, pgraphe_t g)
{
  int i = 0;
  while (tableau[i] != NULL && i < nombre_arcs(g))
  {
    if (tableau[i] == p)
    {
      return 1;
    }
    i++;
  }
  return 0;
}
int appartient_tableau_arc(psommet_t *tableau, psommet_t p, pgraphe_t g)
{
  int i = 0;
  while (tableau[i] != NULL && i < nombre_sommets(g))
  {
    if (tableau[i] == p)
    {
      return 1;
    }
    i++;
  }
  return 0;
}

psommet_t chercher_sommet(pgraphe_t g, int label)
{
  psommet_t s;

  s = g;

  while ((s != NULL) && (s->label != label))
  {
    s = s->sommet_suivant;
  }
  return s;
}

parc_t existence_arc(parc_t l, psommet_t s)
{
  parc_t p = l;

  while (p != NULL)
  {
    if (p->dest == s)
      return p;
    p = p->arc_suivant;
  }
  return p;
}

void ajouter_arc(psommet_t o, psommet_t d, int distance)
{
  parc_t parc;

  parc = (parc_t)malloc(sizeof(arc_t));

  if (existence_arc(o->liste_arcs, d) != NULL)
  {
    fprintf(stderr, "ajout d'un arc deja existant\n");
    exit(-1);
  }

  parc->poids = distance;
  parc->dest = d;
  parc->arc_suivant = o->liste_arcs;
  o->liste_arcs = parc;
  return;
}

// ===================================================================

int nombre_sommets(pgraphe_t g)
{
  psommet_t p = g;
  int nb = 0;

  while (p != NULL)
  {
    nb = nb + 1;
    p = p->sommet_suivant;
  }

  return nb;
}

int nombre_arcs(pgraphe_t g)
{

  psommet_t p = g;
  int nb_arcs = 0;

  while (p != NULL)
  {
    parc_t l = p->liste_arcs;

    while (l != NULL)
    {
      nb_arcs = nb_arcs + 1;
      l = l->arc_suivant;
    }

    p = p->sommet_suivant;
  }
  return nb_arcs;
}

void init_couleur_sommet(pgraphe_t g)
{
  psommet_t p = g;

  while (p != NULL)
  {
    p->couleur = 0;        // couleur indefinie
    p = p->sommet_suivant; // passer au sommet suivant dans le graphe
  }

  return;
}

int colorier_graphe(pgraphe_t g)
{
  /*
    coloriage du graphe g

    datasets
    graphe data/gr_planning
    graphe data/gr_sched1
    graphe data/gr_sched2
  */

  psommet_t p = g;
  parc_t a;
  int couleur;
  int max_couleur = INT_MIN; // -INFINI

  int change;

  init_couleur_sommet(g);

  while (p != NULL)
  {
    couleur = 1; // 1 est la premiere couleur

    // Pour chaque sommet, on essaie de lui affecter la plus petite couleur

    // Choix de la couleur pour le sommet p

    do
    {
      a = p->liste_arcs;
      change = 0;

      while (a != NULL)
      {
        if (a->dest->couleur == couleur)
        {
          couleur = couleur + 1;
          change = 1;
        }
        a = a->arc_suivant;
      }

    } while (change == 1);

    // couleur du sommet est differente des couleurs de tous les voisins

    p->couleur = couleur;
    if (couleur > max_couleur)
      max_couleur = couleur;

    p = p->sommet_suivant;
  }

  return max_couleur;
}

void afficher_graphe_largeur(pgraphe_t g, int r)
{
  psommet_t p = g;
  while (p != NULL && p->label != r)
  {
    p = p->sommet_suivant;
  }

  if (p == NULL)
  {
    printf("Le sommet demandé n'est pas dans le graphe.\n");
    return;
  }

  pfile_t file = creer_file();
  psommet_t sommetsvisites[nombre_sommets(g)];
  sommetsvisites[0] = p;
  int j = 1;
  parc_t a;
  int nbvisites = 1;
  int size = nombre_sommets(g);

  enfiler(file, p);

  while (nbvisites <= size)
  {
    if (file_vide(file) == 0)
    {
      p = defiler(file);
      nbvisites++;

      printf("%d ", p->label);

      a = p->liste_arcs;

      while (a != NULL)
      {
        if (appartient_tableau(sommetsvisites, a->dest, g) == 0)
        {
          enfiler(file, a->dest);
          sommetsvisites[j] = a->dest;
          j++;
        }
        a = a->arc_suivant;
      }
    }
    else
    {
      p = g;
      while (appartient_tableau(sommetsvisites, p, g) == 1)
      {
        p = p->sommet_suivant;
      }
      enfiler(file, p);
      sommetsvisites[j] = p;
      j++;
    }
  }

  printf("\n");

  return;
}

void afficher_graphe_profondeur(pgraphe_t g, int r)
{

  // Existance de r dans le graphe g
  psommet_t p = g;
  while (p != NULL && p->label != r)
  {
    p = p->sommet_suivant;
  }

  if (p == NULL)
  {
    printf("r n'est pas dans le graphe, insèrez un label correct \n");
    return;
  }
  // Partie "descendente"

  ppile_t pile = creer_pile();
  psommet_t sommetsvisites[nombre_sommets(g)];
  sommetsvisites[0] = p;
  int j = 1;
  int k = j;
  parc_t a;
  int nbvisites = 1;
  int size = nombre_sommets(g);

  empiler(pile, p);

  while (nbvisites <= size)
  {
    if (pile_vide(pile) == 0)
    {
      p = depiler(pile);
      nbvisites++;

      printf("%d ", p->label);

      a = p->liste_arcs;
      k = j;

      while (a != NULL)
      {
        if (appartient_tableau(sommetsvisites, a->dest, g) == 0)
        {
          sommetsvisites[j] = a->dest;
          j++;
        }
        a = a->arc_suivant;
      }

      for (int i = j - 1; i > k - 1; i--)
      {
        empiler(pile, sommetsvisites[i]);
      }
    }
    else
    {
      p = g;
      while (appartient_tableau(sommetsvisites, p, g) == 1)
      {
        p = p->sommet_suivant;
      }
      empiler(pile, p);
      sommetsvisites[j] = p;
      j++;
    }
  }

  printf("\n");

  return;
}

void algo_dijkstra(pgraphe_t g, int r)
{
  /*
    algorithme de dijkstra
    des variables ou des chanmps doivent etre ajoutees dans les structures.
  */

  return;
}

// ======================================================================

int degre_sortant_sommet(pgraphe_t g, psommet_t s)
{
  /*
    Cette fonction retourne le nombre d'arcs sortants
    du sommet n dans le graphe g
  */
  if (g != NULL)
  {

    psommet_t p = g;
    while (p != s)
    {
      p = p->sommet_suivant;
    }

    if (p == NULL)
    {
      printf("Le sommet demandé  pas dans le graphe.\n");
      return 0;
    }

    int dss = 0;
    parc_t arc = s->liste_arcs;
    while (arc != NULL)
    {
      dss++;
      arc = arc->arc_suivant;
    }
    return dss;
  }
  return 0;
}

int degre_entrant_sommet(pgraphe_t g, psommet_t s)
{
  /*
    Cette fonction retourne le nombre d'arcs entrants
    dans le noeud n dans le graphe g
  */
  psommet_t p = g;
  int cpt = 0;
  while (p)
  {
    parc_t a = p->liste_arcs;
    while (a)
    {
      if (a->dest->label == s->label)
      {
        cpt++;
      }
      a = a->arc_suivant;
    }
    p = p->sommet_suivant;
  }
  return cpt;
}

int degre_maximal_graphe(pgraphe_t g)
{
  /*
    Max des degres des sommets du graphe g
  */

  int max = 0;
  psommet_t p = g;
  while (p)
  {
    if (degre_entrant_sommet(g, p) + degre_sortant_sommet(g, p) > max)
    {
      max = degre_entrant_sommet(g, p) + degre_sortant_sommet(g, p);
    }
    p = p->sommet_suivant;
  }
  return max;
}

int degre_minimal_graphe(pgraphe_t g)
{
  /*
    Min des degres des sommets du graphe g
  */
  int min = nombre_sommets(g);
  psommet_t p = g;
  while (p)
  {
    if (degre_entrant_sommet(g, p) + degre_sortant_sommet(g, p) < min)
    {
      min = degre_entrant_sommet(g, p) + degre_sortant_sommet(g, p);
    }
    p = p->sommet_suivant;
  }

  return min;
}
int elementaire(pgraphe_t g, pchemin_t c)
{
  if (g != NULL && c != NULL)
  {
    psommet_t *sommetstrouves = malloc(sizeof(psommet_t) * nombre_sommets(g));

    sommetstrouves[0] = c->start;
    int j = 1;
    while (c != NULL)
    {
      if (appartient_tableau(sommetstrouves, c->arc->dest, g) == 1)
      {
        return 0;
      }
      sommetstrouves[j] = c->arc->dest;
      j++;
      c = c->suivant;
    }
    return 1;
  }
  return 1;
}

int simple(pgraphe_t g, pchemin_t c)
{
  if (g != NULL && c != NULL)
  {
    parc_t *arcstrouves = malloc(sizeof(parc_t) * nombre_arcs(g));

    arcstrouves[0] = c->arc;
    int j = 1;
    c = c->suivant;
    while (c != NULL)
    {
      if (appartient_tableau_arc(arcstrouves, c->arc, g) == 1)
      {
        return 0;
      }
      arcstrouves[j] = c->arc;
      j++;
      c = c->suivant;
    }
    return 1;
  }
  return 1;
}

int eulerien(pgraphe_t g, pchemin_t c)
{
  if (g != NULL && c != NULL)
  {
    parc_t *arcstrouves = malloc(sizeof(parc_t) * nombre_arcs(g));
    arcstrouves[0] = c->arc;
    int j = 1;
    c = c->suivant;
    while (c != NULL)
    {
      if (appartient_tableau_arc(arcstrouves, c->arc, g) == 0)
      {
        arcstrouves[j] = c->arc;
        j++;
      }
      c = c->suivant;
    }
    if (j != nombre_arcs(g))
    {
      return 0;
    }
    return 1;
  }
  return 0;
}
int independant(pgraphe_t g)
{
  /* Les aretes du graphe n'ont pas de sommet en commun */

  return 0;
}

int complet(pgraphe_t g)
{
  /* Toutes les paires de sommet du graphe sont jointes par un arc */

  return 0;
}

int regulier(pgraphe_t g)
{
  /*
     graphe regulier: tous les sommets ont le meme degre
     g est le ponteur vers le premier sommet du graphe
     renvoie 1 si le graphe est régulier, 0 sinon
  */

  return 0;
}

/*
  placer les fonctions de l'examen 2017 juste apres
*/

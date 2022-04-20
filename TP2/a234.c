#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "a234.h"

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

int hauteur(Arbre234 a)
{
  int h0, h1, h2, h3;

  if (a == NULL)
    return 0;

  if (a->t == 0)
    return 0;

  h0 = hauteur(a->fils[0]);
  h1 = hauteur(a->fils[1]);
  h2 = hauteur(a->fils[2]);
  h3 = hauteur(a->fils[3]);

  return 1 + max(max(h0, h1), max(h2, h3));
}

int NombreCles(Arbre234 a)
{
  if (a == NULL)
    return 0;

  if (a->t == 0)
    return 0;

  return NombreCles(a->fils[0]) + NombreCles(a->fils[1]) + NombreCles(a->fils[2]) + NombreCles(a->fils[3]) + a->t - 1;
}

int CleMax(Arbre234 a)
{
  if (a == NULL)
  {
    return -1;
  }
  if (a->t == 0)
  {
    return -1;
  }
  else if (a->t == 2 || a->t == 3)
  {
    return max(CleMax(a->fils[2]), a->cles[1]);
  }
  else
  {
    return max(CleMax(a->fils[3]), a->cles[2]);
  }
  return 0;
}

int CleMin(Arbre234 a)
{
  /*
  Retourne plus petite cle de l'arbre a
  */
  int ind_min;
  if (a != NULL && a->t != 0)
  {
    switch (a->t)
    {
    case 2:
      ind_min = 1;
      break;
    default:
      ind_min = 0;
      break;
    }
    return CleMin(a->fils[ind_min]) == -1 ? a->cles[ind_min] : CleMin(a->fils[ind_min]);
  }
  else
  {
    return -1;
  }
}

Arbre234 RechercherCle(Arbre234 a, int cle)
{
  /*
     rechercher si la cle a est presente dans
     l'arbre a. Si oui, retourne le noeud ou se trouve la cle.
  */
  if (a != NULL)
  {
    switch (a->t)
    {
    case 0:
      return NULL;
    case 2:
      return cle == a->cles[1] ? a : cle < a->cles[1] ? RechercherCle(a->fils[1], cle)
                                                      : RechercherCle(a->fils[2], cle);
    case 3:
      return (cle == a->cles[1] || cle == a->cles[2]) ? a : cle < a->cles[0]                     ? RechercherCle(a->fils[0], cle)
                                                        : (cle > a->cles[0] && cle < a->cles[1]) ? RechercherCle(a->fils[1], cle)
                                                                                                 : RechercherCle(a->fils[2], cle);
    case 4:
      return (cle == a->cles[0] || cle == a->cles[1] || cle == a->cles[2]) ? a : (cle < a->cles[0])                   ? RechercherCle(a->fils[0], cle)
                                                                             : (cle > a->cles[0] && cle < a->cles[1]) ? RechercherCle(a->fils[1], cle)
                                                                             : (cle > a->cles[1] && cle < a->cles[2]) ? RechercherCle(a->fils[2], cle)
                                                                                                                      : RechercherCle(a->fils[3], cle);

    default:
      return NULL;
    }
  }
  else
  {
    return NULL;
  }
}

void AnalyseStructureArbre(Arbre234 a, int *feuilles, int *noeud2, int *noeud3, int *noeud4)
{
  /*
     calculer le nombre de feuilles, de 2-noeuds, 3-noeuds,et 4-noeuds
  */
}

Arbre234 noeud_max(Arbre234 a)
{
  /*
    Retourne le noeud avec la somme maximale des cles internes
  */

  return NULL;
}

void Afficher_Cles_Largeur(Arbre234 a)
{
  /*
    Afficher le cles de l'arbre a avec
    un parcours en largeur
  */

  return;
}

void Affichage_Cles_Triees_Recursive(Arbre234 a)
{
  /*
     Afficher les cles en ordre croissant
     Cette fonction sera recursive
  */
}

void Affichage_Cles_Triees_NonRecursive(Arbre234 a)
{
  /*
   Afficher les cles en ordre croissant
   Cette fonction ne sera pas recursive
   Utiliser une pile
*/
}

void Detruire_Cle(Arbre234 *a, int cle)
{
  /*
    retirer la cle de l'arbre a
  */

  return;
}

void basicMain(Arbre234 a)
{
  afficher_arbre(a, 0);

  printf("\n");
}

void test_nb_cle(Arbre234 a)
{
  printf("Nombre-de-cles : %d\n", NombreCles(a));
}

void test_cle_min(Arbre234 a)
{
  printf("Cle-min : %d\n", CleMin(a));
}

void test_cle_max(Arbre234 a)
{
  printf("Clé-max : %d\n", CleMax(a));
}

void test_recherche_cle(Arbre234 a, int cle)
{
  printf("Recherche-de-la-cle-%d : %d\n", cle, RechercherCle(a, cle) != NULL);
}

int main(int argc, char **argv)
{
  Arbre234 a = NULL;
  if (argc < 3)
  {
    fprintf(stderr, "il manque le parametre nom de fichier\n");
    exit(-1);
  }

  a = lire_arbre(argv[1]);

  if (strcmp(argv[2], "display") == 0)
  {
    basicMain(a);
  }
  else if (strcmp(argv[2], "nb_cles") == 0)
  {
    test_nb_cle(a);
  }
  else if (strcmp(argv[2], "cle_min") == 0)
  {
    test_cle_min(a);
  }
  else if (strcmp(argv[2], "cle_max") == 0)
  {
    test_cle_max(a);
  } else if (strcmp(argv[2], "recherche_cle") == 0)
  {
    if(argc < 4)
    {
      fprintf(stderr, "il manque le parametre cle\n");
      exit(-1);
    }
    test_recherche_cle(a, atoi(argv[3]));
  }
  else
  {
    fprintf(stderr, "parametre inconnu\n");
    exit(-1);
  }
}

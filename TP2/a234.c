#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "a234.h"

#define max(a, b) ((a) > (b) ? (a) : (b))

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

  return  NombreCles(a->fils[0]) + NombreCles(a->fils[1]) + NombreCles(a->fils[2]) + NombreCles(a->fils[3]) + a->t - 1;
}

int CleMax(Arbre234 a)
{
  /*
  Retourne plus grande cle de l'arbre a
  */
  return 0;
}

int CleMin(Arbre234 a)
{
  /*
  Retourne plus petite cle de l'arbre a
  */
  return 0;
}

Arbre234 RechercherCle(Arbre234 a, int cle)
{
  /*
     rechercher si la cle a est presente dans
     l'arbre a. Si oui, retourne le noeud ou se trouve la cle.
  */
  return 0;
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

Arbre234 read_arbre_in_arg(int argc, char *argv[])
{
  Arbre234 a = NULL;
  if (argc != 2)
  {
    fprintf(stderr, "il manque le parametre nom de fichier\n");
    exit(-1);
  }
  a = lire_arbre(argv[1]);
  return a;
}

void basicMain(Arbre234 a)
{
  printf("==== Afficher arbre ====\n");

  afficher_arbre(a, 0);

  printf("\n");
}

void test_nb_cle(Arbre234 a)
{
  printf("==== Test nombre cles ====\n");
  int nb_cle = NombreCles(a);
  printf("Nombre de cles : %d\n", nb_cle);
}

void test_cle_min(Arbre234 a)
{
  printf("==== Test cle min ====\n");
  int cle_min = CleMin(a);
  if (cle_min != 1)
  {
    printf("Erreur CleMin\n");
  }
  printf("Cle min : %d\n", cle_min);
}

void test_cle_max(Arbre234 a)
{
  printf("==== Test cle max ====\n");
  int cle_max = CleMax(a);
  if (cle_max != 50)
  {
    printf("Erreur CleMax\n");
  }
  printf("Cle max : %d\n", cle_max);
}

int main(int argc, char **argv)
{
  Arbre234 a = read_arbre_in_arg(argc, argv);
  basicMain(a);
  test_nb_cle(a);
}

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
  if (a != NULL && a->t != 0)
  {
    return NombreCles(a->fils[0]) + NombreCles(a->fils[1]) + NombreCles(a->fils[2]) + NombreCles(a->fils[3]) + a->t - 1;
  }
  else
  {
    return 0;
  }
}

int CleMax(Arbre234 a)
{
  if (a != NULL && a->t != 0)
  {
    if (a->t == 2 || a->t == 3)
    {
      return max(CleMax(a->fils[2]), a->cles[1]);
    }
    else
    {
      return max(CleMax(a->fils[3]), a->cles[2]);
    }
  }

  return -1;
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

/* Here is the explanation for the code above:
 1. If the tree is empty, return NULL.
 2. If the tree is not empty, check if the key is in the root.
 3. If the key is in the root, return the root.
 4. If the key is not in the root, check if the key is in the left or right subtree.
 5. If the key is in the left subtree, recursively call the function with the left subtree.
 6. If the key is in the right subtree, recursively call the function with the right subtree. */
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
      return (cle == a->cles[0] || cle == a->cles[1]) ? a : cle < a->cles[0]                     ? RechercherCle(a->fils[0], cle)
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
  if (a != NULL)
  {
    switch (a->t)
    {
    case 0:
      *feuilles += 1;
      break;
    case 2:
      *noeud2 += 1;
      break;
    case 3:
      *noeud3 += 1;
      break;
    case 4:
      *noeud4 += 1;
      break;
    default:
      break;
    }
    for (int i = 0; i <= 4; i++)
    {
      if (a->fils[i] != NULL)
      {
        AnalyseStructureArbre(a->fils[i], feuilles, noeud2, noeud3, noeud4);
      }
    }
  }
}

int noeud_sum(Arbre234 a)
{
  return (a == NULL || a->t == 0) ? 0 : a->cles[0] + a->cles[1] + a->cles[2];
}

/* Here is the explanation for the code above:
1. We allocate an array of the size of the tree to store the child nodes.
2. We iterate through the tree and store each child node in the array.
3. We then iterate through the array to find the node with the maximum value of the sum.
4. We return the node that has the maximum value of the sum. */
Arbre234 noeud_max(Arbre234 a)
{
  /*
    Retourne le noeud avec la somme maximale des cles internes
  */
  if (a != NULL && a->t != 0)
  {
    Arbre234 *fils = malloc(sizeof(Arbre234) * 4);
    for (int i = 0; i < 4; i++)
    {

      fils[i] = noeud_max(a->fils[i]);
    }

    int max = noeud_sum(a);
    int j = 4;
    for (int i = 0; i < 4; i++)
    {
      if (max < noeud_sum(fils[i]))
      {
        max = noeud_sum(fils[i]);
        j = i;
      }
    }

    Arbre234 tmp = fils[j];
    free(fils);
    return j == 4 ? a : tmp;
  }
  else
  {
    return NULL;
  }
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
  //On distingue les cas avec 2,3 ou 4 fils et on fait le nombre d'appels recursifs necessaires
  if (a!=NULL) {
    if (a->t == 2) {
      Affichage_Cles_Triees_Recursive(a->fils[1]);
      printf("%d ", a->cles[1]);
      Affichage_Cles_Triees_Recursive(a->fils[2]);
    }
    if (a->t == 3) {
      Affichage_Cles_Triees_Recursive(a->fils[0]);
      printf("%d ", a->cles[0]);
      Affichage_Cles_Triees_Recursive(a->fils[1]);
      printf("%d ", a->cles[1]);
      Affichage_Cles_Triees_Recursive(a->fils[2]);
    }
    if (a->t == 4) {
      Affichage_Cles_Triees_Recursive(a->fils[0]);
      printf("%d ", a->cles[0]);
      Affichage_Cles_Triees_Recursive(a->fils[1]);
      printf("%d ", a->cles[1]);
      Affichage_Cles_Triees_Recursive(a->fils[2]);
      printf("%d ", a->cles[2]);
      Affichage_Cles_Triees_Recursive(a->fils[3]);
    }
  }
     
}

void Affichage_Cles_Triees_NonRecursive(Arbre234 a)
{
  /*
   Afficher les cles en ordre croissant
   Cette fonction ne sera pas recursive
   Utiliser une pile
  */
}


/*
void Detruire_Cle(Arbre234 *a, int cle) // Tout juste commencée mais on souhaite annoter nos idées en se basant sur les diapositives de cours
{
  Arbre234 tmp = (RechercheCle(*a,cle));
  //On verifie si la clé est présente dans l'arbre
  if (tmp != NULL){
    //Si la clé est dans une feuille et qu'il y a au moins 2 clés dans la feuille (cas le plus simple)
    //On supprime la feuille sans se soucier du reste
    if (tmp->t > 2){
      for (int i = 0; i < tmp->t; i++){
        if(tmp->cles[i] == cle){
          free((tmp->cles[i]));
      }
      tmp->t --;
    }
    //Cas où la clé est dans un noeud feuille avec une seule clé
    //On devra alors remonter une clé d'un noeud frère "arrangeant" vers le noeud père PUIS le faire redescendre dans le noeud qui nous interesse
    //On se retrouve alors dans le cas dejà traité avec au moins 2 clés
    if(tmp->t == 1){
      //NYI
    }
    //Cas où la clé est dans un noeud feuille avec une seule clé
    //MAIS le noeud frère dispose aussi d'une seule clé ! -> ?
  }
  return;
}
*/

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

void test_analyse_struct(Arbre234 a)
{
  int feuilles = 0, noeud2 = 0, noeud3 = 0, noeud4 = 0;
  AnalyseStructureArbre(a, &feuilles, &noeud2, &noeud3, &noeud4);
  printf("Feuilles : %d \n", feuilles);
  printf("Noeud2 : %d \n", noeud2);
  printf("Noeud3 : %d \n", noeud3);
  printf("Noeud4 : %d \n", noeud4);
}

void test_noeud_max(Arbre234 a)
{
  printf("Noeud-max : %d\n", noeud_sum(noeud_max(a)));
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
  }
  else if (strcmp(argv[2], "recherche_cle") == 0)
  {
    if (argc < 4)
    {
      fprintf(stderr, "il manque le parametre cle\n");
      exit(-1);
    }
    test_recherche_cle(a, atoi(argv[3]));
  }
  else if (strcmp(argv[2], "analyse_struct") == 0)
  {
    test_analyse_struct(a);
  }
  else if (strcmp(argv[2], "noeud_max") == 0)
  {
    test_noeud_max(a);
  }
  else
  {
    fprintf(stderr, "parametre inconnu\n");
    exit(-1);
  }
}

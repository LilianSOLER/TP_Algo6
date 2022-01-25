#include <stdlib.h>
#include <stdio.h>
#include "pile.c"

int main (int argc, char**argv)
{
//test des fonctions de pile
  ppile_t p = creer_pile();
  int estVide = pile_vide(p);
  printf("pile vide: %d\n", estVide);
  int depileVide  = (NULL == depiler(p));
  printf("depiler: %d\n", depileVide);
  return 0;
}

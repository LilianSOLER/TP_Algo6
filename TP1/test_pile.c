#include <stdlib.h>
#include <stdio.h>
#include "abr.h"
#include "pile.h"

int main (int argc, char**argv)
{
//test des fonctions de pile
  ppile_t p = creer_pile();
  int estVide = pile_vide(p);
  printf("pile vide: %d\n", estVide);
  int depileVide  = (NULL == depiler(p));
  printf("depiler: %d\n", depileVide);

  for(int i = 0; i < MAX_PILE_SIZE; i++)
  {
    pnoeud_t tmp = malloc(sizeof(pnoeud_t));
    tmp->cle = i;
    empiler(p, tmp);
  }
  int estPleine = pile_pleine(p);
  printf("pile pleine: %d\n", estPleine);
  
  pnoeud_t tmp = malloc(sizeof(pnoeud_t));
  tmp->cle = 33;
  // int empile_max = empiler(p, tmp);
  // printf("empiler_max: %d\n", empile_max);
  // free(tmp);
  
  int i = 0;
  while(i < p->sommet)
  {
    printf("%d\n", p->Tab[i]->cle);
  }
    
  for(int j = 0; j < MAX_PILE_SIZE; j++)
  {
    printf("depiler: %d\n", depiler(p)->cle);
  }
  int estVide2 = pile_vide(p);
  printf("pile vide: %d\n", estVide2);
  
  depileVide  = (NULL == depiler(p));
  printf("depiler: %d\n", depileVide);




  return 0;
}

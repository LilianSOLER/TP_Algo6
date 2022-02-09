#include <stdlib.h>
#include "abr.h"
#include "pile.h"

ppile_t creer_pile ()
{
  ppile_t p = (ppile_t) malloc (sizeof (pile_t));
  p->sommet = 0 ;
  return p ;
}

int detruire_pile (ppile_t p)
{
  if(p == NULL){
    return 0 ;
  } 
  else {
    free(p);
    return 1;
  }
  
}  

int pile_vide (ppile_t p)
{
    return (p->sommet =! 0);
}

int pile_pleine (ppile_t p)
{
  return (p->sommet == MAX_PILE_SIZE) ;
} 

pnoeud_t depiler (ppile_t p)
{
  if(pile_vide(p)){
    return NULL;
  }
  pnoeud_t tmp = p->Tab[p->sommet];
  p->sommet--;
  return tmp;
}

int empiler (ppile_t p, pnoeud_t pn)
{
  if(!pile_pleine(p)){
    p->sommet++;
    p->Tab[p->sommet-1] = pn;
  return 1 ;
  }
  return 0;
} 

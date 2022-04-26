#include <stdlib.h>

#include "a234.h"
#include "pile.h"

//On réutilise les fonctions associées à la manipulation de pile utilisées dans des cours précédents

ppile_t creer_pile () {
  ppile_t pile = malloc(sizeof(pile_t));
  pile->sommet = 0;
  return pile;
}

int detruire_pile (ppile_t p) {
  free(p);
  return 1;
}  

int pile_vide (ppile_t p) {
  if (p->sommet == 0) {
    return 1;
  }
  return 0;
}

int pile_pleine (ppile_t p) {
  if (p->sommet == MAX_PILE_SIZE) {
    return 1;
  }
  return 0;
} 

pnoeud234 depiler (ppile_t p)
{
  if (pile_vide(p) == 1) {
    return NULL;
  }
  pnoeud234 retour = p->Tab[p->sommet];
  p->sommet = p->sommet-1;
  return retour;
}

int empiler (ppile_t p, pnoeud234 pn) {
  if (pile_pleine(p) != 1) {
    p->sommet += 1;
    p->Tab[p->sommet] = pn; 
    return p->sommet;
  }
  return 0;
}
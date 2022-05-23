#include <stdlib.h>

#include "graphe.h"
#include "pile.h"

ppile_t creer_pile()
{
  ppile_t pile = malloc(sizeof(pile_t));
  pile->sommet = 0;
  return pile;
}

int detruire_pile(ppile_t p)
{
  free(p);
  return 1;
}

int pile_vide(ppile_t p)
{
  if (p->sommet == 0)
  {
    return 1;
  }
  return 0;
}

int pile_pleine(ppile_t p)
{
  if (p->sommet == MAX_PILE_SIZE)
  {
    return 1;
  }
  return 0;
}

psommet_t depiler(ppile_t p)
{
  if (pile_vide(p) == 1)
  {
    return NULL;
  }
  psommet_t retour = p->Tab[p->sommet];
  p->sommet = p->sommet - 1;
  return retour;
}

int empiler(ppile_t p, psommet_t pn)
{
  if (pile_pleine(p) != 1)
  {
    p->sommet += 1;
    p->Tab[p->sommet] = pn;
    return p->sommet;
  }
  return 0;
}
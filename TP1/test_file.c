#include <stdlib.h>
#include <stdio.h>

#include "file.c"

int main (int argc, char**argv)
{
  //test des fonctions de file
  pfile_t p = creer_file();
  int estVide = file_vide(p);
  printf("file vide: %d\n", estVide);
  int estPleine = file_pleine(p);
  printf("file pleine: %d\n", estPleine);
  int estDetruite =  detruire_file(p);
  printf("file detruite: %d\n", estDetruite);

  pfile_t p2 = creer_file();
  int emfileWork = emfiler(p2, (pnoeud_t) {1, NULL, NULL});
  printf("emfiler: %d\n", emfileWork);
  int emfileWork = emfiler(p2, (pnoeud_t) {2, NULL, NULL});
  int estVide2 = file_vide(p2);
  printf("file vide: %d\n", estVide2);
  int estPleine2 = file_pleine(p2);
  printf("file pleine: %d\n", estPleine2);
  pnoeud_t defile = defiler(p2);
  int elmdefiler = defile->cle;
  printf("defiler: %d\n", elmdefiler);
  int estDetruite2 =  detruire_file(p2);
  printf("file detruite: %d\n", estDetruite2);
  return 0;
}

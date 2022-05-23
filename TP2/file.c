#include <stdlib.h>

#include "a234.h"
#include "file.h"

pfile_t creer_file ()
{
  pfile_t file = malloc(sizeof(file_t));
  file->tete = 0;
  file->queue = 0;
  return file;
}

int detruire_file (pfile_t f)
{
  free(f);
  return 1;
}

int file_vide (pfile_t f)
{
  if (f->tete == f->queue) {
    return 1;
  }
  return 0;
}

int file_pleine (pfile_t f)
  {
  if (f->queue - f->tete == MAX_FILE_SIZE) {
    return 1;
  }
  return 0;
}

pnoeud234 defiler (pfile_t f)
  {
  if (file_vide(f) == 1) {
    return NULL;
  }
  f->tete = f->tete+1; 
  pnoeud234 retour = f->Tab[(f->tete)%(MAX_FILE_SIZE)];
  return retour;
}

int enfiler (pfile_t f, pnoeud234 p)
{
  if (file_pleine(f) != 1) {
    f->queue += 1; 
    f->Tab[(f->queue)%(MAX_FILE_SIZE)] = p; 
    return f->queue;
  }
  return 0;
}
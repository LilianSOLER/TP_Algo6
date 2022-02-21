#include <stdlib.h>

#include "abr.h"
#include "file.h"

pfile_t creer_file ()
{
  pfile_t f = (pfile_t) malloc (sizeof (file_t));
  f->tete = 0;
  f->queue = 0;
  f->nb_elem = 0;
  return f;
}

int detruire_file (pfile_t f)
{
  if(f == NULL){
    return 0 ;
  } 
  else {
    free(f);
    return 1;
  }
}


int file_vide (pfile_t f)
{
  return (f->nb_elem == 0);
}

int file_pleine (pfile_t f)
{
  return (f->nb_elem == MAX_FILE_SIZE);
}

pnoeud_t defiler (pfile_t f)
{
  if(file_vide(f)){
    return NULL;
  }
  f->nb_elem--;
  f->tete = (f->tete + 1) % MAX_FILE_SIZE;
  return f->Tab[f->tete];
}

int enfiler (pfile_t f, pnoeud_t p)
{
  if(!file_pleine(f)){
    f->nb_elem++;
    f->queue = (f->queue + 1) % MAX_FILE_SIZE;
    f->Tab[f->queue] = p;
    return 1 ;
  }
  else{
    return 0;
  }
}

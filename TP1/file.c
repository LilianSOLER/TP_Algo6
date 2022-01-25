#include <stdlib.h>

#include "abr.h"
#include "file.h"

pfile_t creer_file ()
{
  pfile_t f = (pfile_t) malloc (sizeof (file_t));
  f->tete = 0;
  f->queue = 0;
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
  return (f->queue == f->tete) && (f->Tab[f->tete] == NULL);
}

int file_pleine (pfile_t f)
{
  return ((f->queue - f->tete == 1) || (f->tete - f->queue  == MAX_FILE_SIZE - 1));
}

pnoeud_t defiler (pfile_t f)
{
  if(file_vide(f)){
    return NULL;
  }
  pnoeud_t res = f->Tab[f->tete--];
  f->Tab[f->tete] = NULL;
  return res;
}

int enfiler (pfile_t f, pnoeud_t p)
{
  if(!file_pleine(f)){
    if(f->queue == 0){
      f->queue = MAX_FILE_SIZE - 1;
    }
    else{
      f->queue--;
    }
    f->Tab[f->queue] = p;
    return 1;
  }
  else{
    return 0;
  }
}

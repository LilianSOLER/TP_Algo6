#include <stdio.h>
#include <stdlib.h>

#include "a234.h"

static void decalage (int niveau)
{
  int i ;

  for (i = 0; i < niveau; i++)
    printf ("\t\t") ;
  return ;
}

void afficher_arbre (Arbre234 a, int niveau)
{
  /*
    affichage de l'arbre a
    on l'affiche en le penchant sur sa gauche
    la partie droite (haute) se retrouve en l'air
  */
  
  if (a != NULL)
      {
	if (a->t == 0)
	  return ;

	if (a->t == 2)
	  {
	    afficher_arbre (a->fils[2],niveau+1) ;

	    decalage (niveau) ;	    
	    printf (" %d (%d)\n", a->cles[1], niveau) ;

	    afficher_arbre (a->fils[1],niveau+1) ;
	    return ;
	  }

	if (a->t == 3)
	  {
	    afficher_arbre (a->fils [2], niveau+1) ;
		
	    decalage (niveau) ;
	    printf (" %d %d (%d)\n", a->cles [0], a->cles [1], niveau) ;

	    afficher_arbre (a->fils [1], niveau+1) ;

	    printf ("\n") ;
	    
	    afficher_arbre (a->fils [0], niveau+1) ;
		
	    return ;
	  }

	if (a->t == 4)
	  {
	    afficher_arbre (a->fils[3],niveau+1) ;	    

	    printf ("\n") ;
	    
	    afficher_arbre (a->fils[2],niveau+1) ;

	    decalage (niveau) ;
	    printf (" %d %d %d (%d)\n", a->cles[0], a->cles [1], a->cles [2], niveau) ;

	    afficher_arbre (a->fils[1],niveau+1) ;

	    
	    afficher_arbre (a->fils[0],niveau+1) ;

	    return ;
	  }
      }
  return ;
}

Arbre234 lire_arbre (char *nom_fichier)
{
  FILE *f ;
  int cle;
  Arbre234 a = NULL;
  
  f = fopen (nom_fichier, "r") ;
  
  if (f == NULL)
    {
      fprintf (stderr, "le fichier %s n existe pas\n", nom_fichier) ;
      exit (0) ;
    }
  
  while (fscanf (f, "%d", &cle) != EOF)
    {
      ajouter_cle (&a, cle, 0, NULL) ;

      /* 
	 printf ("================== affiichage arbre avec la cle %d ==================\n", cle) ;
	 afficher_arbre (a, 0) ;
      */
      
    }
  
  fclose (f) ;

  return a ;
}

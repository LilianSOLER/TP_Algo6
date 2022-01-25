#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "a234.h"

pnoeud234 allouer_noeud ()
{
  pnoeud234 p  = (pnoeud234) malloc (sizeof(noeud234)) ;

  p->t = 0 ;
  p->fils[0] = NULL ;
  p->fils[1] = NULL ;
  p->fils[2] = NULL ;
  p->fils[3] = NULL ;
  
  return p ; 
}


void eclater_4noeud_racine (Arbre234 *a, int cle)
{
  Arbre234 a1, a2 ;
  Arbre234 c = *a ;

  c->t = 2 ;
 
  a1 = allouer_noeud () ;
  a1->t = 2 ;
  a1->cles [1] = c->cles [0] ;
  a1->fils [1] = c->fils [0] ;
  a1->fils [2] = c->fils [1] ;
  a1->fils [0] = NULL ;
  a1->fils [3] = NULL ;  
  
  a2 = allouer_noeud () ;
  a2->t = 2 ;
  a2->cles [1] = c->cles [2] ;
  a2->fils [1] = c->fils [2] ;
  a2->fils [2] = c->fils [3] ;
  a2->fils [0] = NULL ;
  a2->fils [3] = NULL ;  

  c->fils [0] = NULL ;
  c->fils [1] = a1 ;
  c->fils [2] = a2 ;
  c->fils [3] = NULL ;

  ajouter_cle (a, cle, 0, NULL) ;
  
  return ;
}

void eclater_4noeud_interne (Arbre234 *a, Arbre234 pere, int cle, int niveau)
{
  pnoeud234 eclat = allouer_noeud () ;
  pnoeud234 c = *a;
  
  if (pere->t == 2)
    {
      if (c->cles[1] < pere->cles [1])
	{
	  
	  pere->t = 3 ;	
	  pere->cles [0] = c->cles [1] ;

	  pere->fils [0] = c ;
	  pere->fils [1] = eclat ;

	  eclat->t = 2 ;
	  eclat->cles [1] = c->cles [2] ;
	  eclat->fils [0] = NULL  ;
	  eclat->fils [1] = c->fils [2] ;
	  eclat->fils [2] = c->fils[3] ;
	  eclat->fils [3] = NULL ;
      
	  c->t = 2 ;
	  c->cles [1] = c->cles [0] ;
	  
	  c->fils [2] = c->fils [1] ;
	  c->fils [1] = c->fils [0] ;
	  c->fils [0] = NULL ;
	  c->fils [3] = NULL ;
	}
      else
	{
	  pere->t = 3 ;
	  pere->cles [0] = pere->cles [1] ;
	  pere->cles [1] = c->cles [1] ;


	  pere->fils [0] = pere->fils [1] ;
	  pere->fils [1] = c ;
	  pere->fils [2] = eclat ;
	  pere->fils [3] = allouer_noeud () ;
	  	 
	  eclat->t = 2 ;
	  eclat->cles [1] = c->cles [2] ;

	  eclat->fils [1] = c->fils[2] ;
	  eclat->fils [2] = c->fils[3] ;
	  eclat->fils [0] = allouer_noeud () ;
	  eclat->fils [3] = allouer_noeud () ;
	  
	  c->t = 2 ;
	  c->cles [1] = c->cles [0] ;
	  c->cles [0] = 0 ;
	  c->cles [2] = 0 ;

	  c->fils [2] = c->fils [1] ;
	  c->fils [1] = c->fils [0] ;

	}
             
      if (cle > pere->cles [1])
	{
	  ajouter_cle (&(pere->fils[2]), cle, niveau, pere) ;
	}
      else
	{
	  if (cle > pere->cles [0])
	    {
	      ajouter_cle (&(pere->fils [1]), cle, niveau, pere) ;
	    }
	  else
	    {
	      ajouter_cle (&(pere->fils [0]), cle, niveau, pere) ;
	    }
	}
      return;
    }



  // pere-t == 2

  
    if (pere->t == 3) 
      {
	/* 3 cas possibles */ 

	if (c == pere->fils [0])
	  {
	    /* cas 1*/

	    eclat->t = 2 ;
	    eclat->cles [1] = c->cles [2] ;
	    eclat->fils [1] = c->fils[2] ;
	    eclat->fils [2] = c->fils [3] ;
	    
	    pere->t = 4 ;
	    pere->cles [2] = pere->cles [1] ;
	    pere->cles [1] = pere->cles [0] ; 
	    pere->cles [0] = c->cles [1] ;

	    pere->fils [3] = pere->fils [2] ;
	    pere->fils [2] = pere->fils [1] ;
	    pere->fils [0] = c ;
	    pere->fils [1] = eclat ;

	    c->t = 2 ;
	    c->cles [1] = c->cles [0] ;
	    c->fils [2] = c->fils [1] ;
	    c->fils [1] = c->fils [0] ;

	  }
	else
	  {
	    if (c == pere->fils [1])
	      {
		/* cas 2 */

		eclat->t = 2 ;
		eclat->cles [1] = c->cles[2] ;
		eclat->fils [1] = c->fils [2] ;
		eclat->fils [2] = c->fils [3] ;
		
		pere->t = 4 ;
		pere->cles [2] = pere->cles [1] ;
                pere->cles [1] = c->cles [1] ;

		pere->fils [3] = pere->fils [2] ;
		pere->fils [2] = eclat ;

		c->t = 2 ;
		c->cles [1] = c->cles [0] ;
		c->fils [2] = c->fils [1] ;
                c->fils [1] = c->fils [0] ;
	      }
	    else
	      {
		/* cas 3 */
		eclat->t = 2 ;
		eclat->cles [1] = c->cles [2] ;
		
		eclat->fils [1] = c->fils [2] ;
		eclat->fils [2] = c->fils [3] ;

		pere->t = 4 ;
                pere->cles [2] = c->cles [1] ;

		pere->fils [3] = eclat ;
		pere->fils [2] = c ;

		c->t = 2 ;
		c->cles [1] = c->cles [0] ;
		c->fils [2] = c->fils [1] ;
		c->fils [1] = c->fils [0] ;
		
	      }
	  }

	if (cle > pere->cles [2])
	  {
	    ajouter_cle (&(pere->fils [3]), cle, niveau, pere) ;
	  }
	else
	  {
	    if (cle > pere->cles [1])
	      {
		ajouter_cle (&(pere->fils [2]), cle, niveau, pere) ;
	      }
	    else
	      {
		if (cle > pere->cles [0])
		  {
		    ajouter_cle (&(pere->fils [1]), cle, niveau, pere) ;
		  }
		else
		  {
		    ajouter_cle (&(pere->fils [0]), cle, niveau, pere) ;
		  }
	      }
	  }	
      } // pere->t == 3
    return ;
}

void ajouter_cle (Arbre234 *a, int cle, int niveau, Arbre234 pere)
{
  pnoeud234 p;
  pnoeud234 c = *a ;
  
  if (c == NULL)
    {
      p = allouer_noeud () ;
      p->t = 2 ;
      p->cles [1] = cle ;

      p->fils [0] = allouer_noeud () ;
      p->fils [3] = allouer_noeud () ;
      
      p->fils [1] = allouer_noeud () ;
      p->fils [2] = allouer_noeud () ;

      *a = p ;
      return ;
    }

  if (c->t == 0)
    {
      // Le noeud c est vide
      // creation d'un 2-noeud

      c->cles [1] = cle ;
      c->t = 2 ;
      
      c->fils [0] = allouer_noeud () ;
      c->fils [3] = allouer_noeud () ;
      c->fils [1] = allouer_noeud () ;
      c->fils [2] = allouer_noeud () ;

      return ;
    } // c->t == 0

  
  if (c->t == 2)
    {
      // Une seule cle dans le  noeud

      if (cle > c->cles[1])
	{
	  if (c->fils[2]->t == 0)
	    {
	      c->t = 3 ;
	      c->cles [0] = c->cles [1] ;
	      c->cles [1] = cle ;
		  
	      c->fils [0] = c->fils [1] ;
	      c->fils [1] = c->fils [2] ;
	      c->fils [2] = allouer_noeud () ;
	    }
	  else
	    {
	      ajouter_cle (&(*a)->fils [2], cle, niveau+1, c) ;
	    }
	  return ;
	}      
      
      if (cle < c->cles[1])
	{
	  if (c->fils[1]->t == 0)
	    {
	      c->cles[0] = cle ;
	      c->t = 3 ;
	      c->fils[0] = allouer_noeud () ;
	    }
	  else
	    {
	      ajouter_cle (&(*a)->fils [1], cle, niveau+1, c) ;
	    }
	}

      return ;
    } // (*a)->t == 2

  
  if (c->t == 3)
    {
      // deux cles dans le noeud
      
      if (cle > c->cles [1])
	{
	  if (c->fils[2]->t == 0)
	    {
	      c->cles[2] = cle ;
	      c->t = 4 ;
	      c->fils [3] = allouer_noeud () ;
	    }
	  else
	    {
	      ajouter_cle (&((*a)->fils[2]), cle, niveau+1, c) ;
	    }
	}
      else
	{
	  if (cle > c->cles [0])
	    {
	      if (c->fils[1]->t == 0)
		{
		  c->cles [2] = c->cles [1] ;
		  c->cles [1] = cle ;
		  c->t = 4 ;
		  c->fils [3] = c->fils [2] ;
		  c->fils [2] = allouer_noeud () ;
		}
	      else
		{
		  ajouter_cle (&(*a)->fils [1], cle, niveau+1, c) ;
		}
	    }
	  else
	    {
	      if (c->fils[0]->t == 0)
		{
		  c->cles [2] = c->cles [1] ;
		  c->cles [1] = c->cles [0] ;
		  c->cles [0] = cle ;
		  c->t = 4 ;

		  c->fils[3] = c->fils[2] ;
		  c->fils[2] = c->fils[1] ;
		  c->fils[1] = c->fils[0] ;
		  c->fils[0] = allouer_noeud () ;
		  
		} 
	      else
		{
		  ajouter_cle (&(*a)->fils [0], cle, niveau+1, c) ;
		}	      
	    }
	}

      return ;
    } // c->t == 3

  
  // trois cles dans le noeud courant
  // Le noeud doit etre eclate
  // c->t == 4

  if (niveau == 0) // noeud racine
    {
      eclater_4noeud_racine (a, cle) ;
    }
  
  else   
    {
      eclater_4noeud_interne (a, pere, cle, niveau) ;
    }
 
  return ;
}

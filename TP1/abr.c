#include <stdio.h>
#include <stdlib.h>

#include "abr.h"
#include "pile.h"
#include "file.h"


#define max(a,b) ((a)>(b)?(a):(b))


int feuille (Arbre_t a)
{
  if (a == NULL)
    return 0 ;
  else
    {
      if ((a->fgauche == NULL) && (a->fdroite == NULL))
	return 1 ;
      else
	return 0 ;
    }
}

Arbre_t ajouter_noeud (Arbre_t a, Arbre_t n)
{
  /* ajouter le noeud n dans l'arbre a */
  
  if (a == NULL)
    return n ;
  else if (n->cle < a->cle)
	a->fgauche = ajouter_noeud (a->fgauche, n) ;
  else
	a->fdroite = ajouter_noeud (a->fdroite, n) ;
  return a ;
  
}  

Arbre_t rechercher_cle_arbre (Arbre_t a, int valeur)
{
  if (a == NULL)
    return NULL ;
  else
    {
      if (a->cle == valeur)
	return a ;
      else
	{
	  if (a->cle < valeur)
	    return rechercher_cle_arbre (a->fdroite, valeur) ;
	  else
	    return rechercher_cle_arbre (a->fgauche, valeur) ;
	}
    }
}

Arbre_t ajouter_cle (Arbre_t a, int cle)
{
  Arbre_t n ;
  Arbre_t ptrouve ;
  
  /* 
     ajout de la clé. Creation du noeud n qu'on insere 
    dans l'arbre a
  */

  ptrouve = rechercher_cle_arbre (a, cle) ;

  if (ptrouve == NULL)
    {
      n = (Arbre_t) malloc (sizeof(noeud_t)) ;
      n->cle = cle;
      n->fgauche = NULL ;
      n->fdroite = NULL ;

      a = ajouter_noeud (a, n) ;
      return a ;
    }
  else
    return a ;
}


Arbre_t lire_arbre (char *nom_fichier)
{
  FILE *f ;
  int cle;
  Arbre_t a = NULL;
  
  f = fopen (nom_fichier, "r") ;

  while (fscanf (f, "%d", &cle) != EOF)
    {
      a = ajouter_cle (a, cle) ;
    }
    
  fclose (f) ;

  return a ;
}

void afficher_arbre (Arbre_t a, int niveau)
{
  /*
    affichage de l'arbre a
    on l'affiche en le penchant sur sa gauche
    la partie droite (haute) se retrouve en l'air
  */
  
  int i ;
  
  if (a != NULL)
      {
	afficher_arbre (a->fdroite,niveau+1) ;
	
	for (i = 0; i < niveau; i++)
	  printf ("\t") ;
	printf (" %d (%d)\n\n", a->cle, niveau) ;

	afficher_arbre (a->fgauche, niveau+1) ;
      }
  return ;
}


int hauteur_arbre_r (Arbre_t a)
{
  /*
    a completer
  */
  if(a == NULL){
    return 1;
  }
  else{
    return max(hauteur_arbre_r(a->fgauche), hauteur_arbre_r(a->fdroite)) + 1;
  }
}

int hauteur_arbre_nr (Arbre_t a)
{
  /*
    a completer
  */
  ppile_t p = creer_pile();
  ppile_t h = creer_pile();
  empiler(p, a);
  empiler(h, (Arbre_t)1);
  while(!est_vide_pile(p)){
    a = depiler(p);
    int h = depiler(h);
    if(a->fgauche != NULL){
      empiler(p, a->fgauche);
      empiler(h, h+1);
    }
    if(a->fdroite != NULL){
      empiler(p, a->fdroite);
      empiler(h, h+1);
    }
  }
  return h;
}


void parcourir_arbre_largeur (Arbre_t a)
{
  /*
    a completer
    Utiliser une file, voir cours
  */

  pfile_t f = creer_file();
  if(a != NULL){
    enfiler(f, a);
  }

  while(!file_vide(f)){
    a = defiler(f);
    printf("%d\n", a->cle);
    if(a->fgauche != NULL){
      enfiler(f, a->fgauche);
    }
    if(a->fdroite != NULL){
      enfiler(f, a->fdroite);
    }
  }
}

void afficher_nombre_noeuds_par_niveau (Arbre_t a)
{
  /*
    a completer
  */
  //calcul number of nodes by level
  int h = hauteur_arbre_r(a);
  int i;
  int nb_nodes[h];
  for(i = 0; i < h; i++){
    nb_nodes[i] = 0;
  }
  pfile_t f = creer_file();
  enfiler(f, a);
  while(!file_vide(f)){
    a = defiler(f);
    nb_nodes[a->cle]++;
    if(a->fgauche != NULL){
      enfiler(f, a->fgauche);
    }
    if(a->fdroite != NULL){
      enfiler(f, a->fdroite);
    }
  }

  //print number of nodes by level
  for(i = 0; i < h; i++){
    printf("%d\n", nb_nodes[i]);
  }

}


int nombre_cles_arbre_r (Arbre_t a)
{
  /*
    a completer
  */
  if(a == NULL){
    return 0;
  }
  else{
    return nombre_cles_arbre_r(a->fgauche) + nombre_cles_arbre_r(a->fdroite) + 1;
  }
}

int nombre_cles_arbre_nr (Arbre_t a)
{
  /*
    a completer
  */
  pfile_t f = creer_file();
  int nb_nodes = 0;
  if(a != NULL){
    enfiler(f, a);
  }
  while(!file_vide(f)){
    a = defiler(f);
    nb_nodes++;
    if(a->fgauche != NULL){
      enfiler(f, a->fgauche);
    }
    if(a->fdroite != NULL){
      enfiler(f, a->fdroite);
    }
  }
  return nb_nodes;
}

int trouver_cle_min (Arbre_t a)
{
  /*
    a completer
  */
  if(a->fgauche == NULL){
    return a->cle;
  }
  else{
    return trouver_cle_min(a->fgauche);
  } 
}

void imprimer_liste_cle_triee_r (Arbre_t a)
{
  /*
    a completer
  */
  if(a != NULL){
    imprimer_liste_cle_triee_r(a->fgauche);
    printf("%d\n", a->cle);
    imprimer_liste_cle_triee_r(a->fdroite);
  }
  return;
}

void imprimer_liste_cle_triee_nr (Arbre_t a)
{
  /*
    a completer
  */  
  return ;
}


int arbre_plein (Arbre_t a)
{
  /*
    a completer
  */
  if(a == NULL){
    return 0;
  }else if(a->fgauche == NULL && a->fdroite == NULL){
    return 1;
  }else{
    return arbre_plein(a->fgauche) && arbre_plein(a->fdroite);
  }
}

int arbre_parfait (Arbre_t a)
{
  /*
    a completer
  */
  if(a == NULL){
    return 0;
  }else if(a->fgauche == NULL && a->fdroite == NULL){
    return 1;
  }else if(a->fgauche != NULL && a->fdroite != NULL){
    return arbre_parfait(a->fgauche) && arbre_parfait(a->fdroite);
  }else{
    return 0;
  }
}




Arbre_t rechercher_cle_sup_arbre (Arbre_t a, int valeur)
{
  /*
    a completer
  */
  if(a == NULL){
    return NULL;
  }else if(a->cle > valeur){
    Arbre_t a_sup = rechercher_cle_sup_arbre(a->fdroite, valeur);
    if(a->cle > valeur && a_sup == NULL){
      return a;
    }else{
      return a_sup;
    }
  }else{
    return NULL;
  }
}

Arbre_t rechercher_cle_inf_arbre (Arbre_t a, int valeur)
{
  /*
    a completer
  */
  if(a == NULL){
    return NULL;
  }else if(a->cle > valeur){
    Arbre_t a_sup = rechercher_cle_sup_arbre(a->fgauche, valeur);
    if(a->cle > valeur && a_sup == NULL){
      return a;
    }else{
      return a_sup;
    }  
  }else{
    return NULL;
  }
}


Arbre_t detruire_cle_arbre (Arbre_t a, int cle)
{
  /*
    a completer
  */
  if(a == NULL){
    return NULL;
  }else if(a->cle == cle){
    if(a->fgauche == NULL && a->fdroite == NULL){
      free(a);
      return NULL;
    }else if(a->fgauche == NULL){
      Arbre_t a_sup = a->fdroite;
      free(a);
      return a_sup;
    }else if(a->fdroite == NULL){
      Arbre_t a_sup = a->fgauche;
      free(a);
      return a_sup;
    }else{
      Arbre_t a_sup = rechercher_cle_sup_arbre(a->fdroite, cle);
      a->cle = a_sup->cle;
      a->fdroite = detruire_cle_arbre(a->fdroite, a_sup->cle);
    }
  }
}



Arbre_t intersection_deux_arbres (Arbre_t a1, Arbre_t a2)
{
  /*
    a completer
  */
  if(a1 == NULL || a2 == NULL){
    return NULL;
  }else{
    Arbre_t a_inter = NULL;
    if(a1->cle == a2->cle){
      a_inter = creer_arbre(a1->cle);
      a_inter->fgauche = intersection_deux_arbres(a1->fgauche, a2->fgauche);
      a_inter->fdroite = intersection_deux_arbres(a1->fdroite, a2->fdroite);
    }else if(a1->cle < a2->cle){
      a_inter = intersection_deux_arbres(a1->fdroite, a2);
    }else{
      a_inter = intersection_deux_arbres(a1, a2->fdroite);
    }
    return a_inter;
  }

  return NULL ;
  
}

Arbre_t union_deux_arbres (Arbre_t a1, Arbre_t a2)
{
  /*
    a completer
  */
  if(a1 == NULL){
    return a2;
  }else if(a2 == NULL){
    return a1;
  }else{
    Arbre_t a_union = NULL;
    if(a1->cle == a2->cle){
      a_union = creer_arbre(a1->cle);
      a_union->fgauche = union_deux_arbres(a1->fgauche, a2->fgauche);
      a_union->fdroite = union_deux_arbres(a1->fdroite, a2->fdroite);
    }else if(a1->cle < a2->cle){
      a_union = creer_arbre(a1->cle);
      a_union->fgauche = a1->fgauche;
      a_union->fdroite = union_deux_arbres(a1->fdroite, a2);
    }else{
      a_union = creer_arbre(a2->cle);
      a_union->fgauche = union_deux_arbres(a1, a2->fgauche);
      a_union->fdroite = a2->fdroite;
    }
    return a_union;
  }
}


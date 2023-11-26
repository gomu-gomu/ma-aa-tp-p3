#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "noeud.h"

Noeud *creerNoeud(char mot[])
{
  Noeud *nouveauNoeud = (Noeud *)malloc(sizeof(Noeud));
  if (nouveauNoeud != NULL)
  {
    strcpy(nouveauNoeud->mot, mot);
    nouveauNoeud->gauche = NULL;
    nouveauNoeud->droite = NULL;
  }
  return nouveauNoeud;
}

Noeud *ajouterMot(Noeud *racine, char mot[])
{
  if (racine == NULL)
  {
    return creerNoeud(mot);
  }

  int comparaison = strcmp(mot, racine->mot);

  if (comparaison < 0)
  {
    racine->gauche = ajouterMot(racine->gauche, mot);
  }
  else if (comparaison > 0)
  {
    racine->droite = ajouterMot(racine->droite, mot);
  }

  return racine;
}

Noeud *rechercherMot(Noeud *racine, char mot[])
{
  if (racine == NULL || strcmp(mot, racine->mot) == 0)
  {
    return racine;
  }

  if (strcmp(mot, racine->mot) < 0)
  {
    return rechercherMot(racine->gauche, mot);
  }

  return rechercherMot(racine->droite, mot);
}

Noeud *trouverMinimum(Noeud *racine)
{
  while (racine->gauche != NULL)
  {
    racine = racine->gauche;
  }
  return racine;
}

Noeud *supprimerMot(Noeud *racine, char mot[])
{
  if (racine == NULL)
  {
    return racine;
  }

  int comparaison = strcmp(mot, racine->mot);

  if (comparaison < 0)
  {
    racine->gauche = supprimerMot(racine->gauche, mot);
  }
  else if (comparaison > 0)
  {
    racine->droite = supprimerMot(racine->droite, mot);
  }
  else
  {
    if (racine->gauche == NULL)
    {
      Noeud *temp = racine->droite;
      free(racine);
      return temp;
    }
    else if (racine->droite == NULL)
    {
      Noeud *temp = racine->gauche;
      free(racine);
      return temp;
    }

    Noeud *temp = trouverMinimum(racine->droite);

    strcpy(racine->mot, temp->mot);

    racine->droite = supprimerMot(racine->droite, temp->mot);
  }

  return racine;
}

void afficherEnOrdre(Noeud *racine)
{
  if (racine != NULL)
  {
    afficherEnOrdre(racine->gauche);
    printf("%s\n", racine->mot);
    afficherEnOrdre(racine->droite);
  }
}

int hauteurArbre(Noeud *racine)
{
  if (racine == NULL)
  {
    return 0;
  }

  int hauteurGauche = hauteurArbre(racine->gauche);
  int hauteurDroite = hauteurArbre(racine->droite);

  return 1 + (hauteurGauche > hauteurDroite ? hauteurGauche : hauteurDroite);
}

int nombreMots(Noeud *racine)
{
  if (racine == NULL)
  {
    return 0;
  }

  return 1 + nombreMots(racine->gauche) + nombreMots(racine->droite);
}

void libererArbre(Noeud *racine)
{
  if (racine != NULL)
  {
    libererArbre(racine->gauche);
    libererArbre(racine->droite);
    free(racine);
  }
}
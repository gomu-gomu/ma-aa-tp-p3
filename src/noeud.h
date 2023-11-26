#ifndef NOEUD_H
#define NOEUD_H

typedef struct Noeud
{
  char mot[50];
  struct Noeud *gauche;
  struct Noeud *droite;
} Noeud;

Noeud *creerNoeud(char mot[]);

Noeud *ajouterMot(Noeud *racine, char mot[]);

Noeud *rechercherMot(Noeud *racine, char mot[]);

Noeud *trouverMinimum(Noeud *racine);

Noeud *supprimerMot(Noeud *racine, char mot[]);

void afficherEnOrdre(Noeud *racine);

int hauteurArbre(Noeud *racine);

int nombreMots(Noeud *racine);

void libererArbre(Noeud *racine);

#endif
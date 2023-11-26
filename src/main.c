#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "noeud.h"

Noeud *chargerArbreDepuisFichier(const char *nomFichier)
{
  FILE *fichier = fopen(nomFichier, "r");

  if (fichier == NULL)
  {
    perror("Erreur lors de l'ouverture du fichier");
    return NULL;
  }

  Noeud *racine = NULL;
  char mot[50];

  while (fgets(mot, sizeof(mot), fichier) != NULL)
  {
    size_t longueurMot = strlen(mot);

    if (longueurMot > 0 && mot[longueurMot - 1] == '\n')
    {
      mot[longueurMot - 1] = '\0';
    }

    racine = ajouterMot(racine, mot);
  }

  fclose(fichier);
  return racine;
}

void afficherMenu()
{
  printf("\n---------[Menu]---------\n");
  printf("1. Afficher l'arbre\n");
  printf("2. Rechercher un mot\n");
  printf("3. Ajouter un mot\n");
  printf("4. Supprimer un mot\n");
  printf("5. Afficher la hauteur de l'arbre\n");
  printf("6. Afficher le nombre de mots dans l'arbre\n");
  printf("0. Quitter\n");
  printf("> Choisissez une option : ");
}

int main()
{
  int choix = -1;
  Noeud *racine = chargerArbreDepuisFichier("fmots.txt");

  while (choix != 0)
  {
    afficherMenu();
    scanf("%d", &choix);

    switch (choix)
    {
    case 1:
      printf("\nArbre :\n");
      afficherEnOrdre(racine);
      break;

    case 2:
    {
      char motRecherche[50];
      printf("\nEntrez le mot à rechercher : ");
      scanf("%s", motRecherche);

      printf("\nRecherche du mot '%s' : %s\n", motRecherche, (rechercherMot(racine, motRecherche) != NULL) ? "trouvé" : "non trouvé");
      break;
    }

    case 3:
    {
      char motAjout[50];
      printf("\nEntrez le mot à ajouter : ");
      scanf("%s", motAjout);

      racine = ajouterMot(racine, motAjout);
      printf("\nLe mot '%s' a été ajouté à l'arbre.\n", motAjout);
      break;
    }

    case 4:
    {
      char motSuppression[50];
      printf("\nEntrez le mot à supprimer : ");
      scanf("%s", motSuppression);

      racine = supprimerMot(racine, motSuppression);
      printf("\nLe mot '%s' a été supprimé de l'arbre.\n", motSuppression);
      break;
    }

    case 5:
      printf("\nHauteur de l'arbre : %d\n", hauteurArbre(racine));
      break;

    case 6:
      printf("\nNombre de mots dans l'arbre : %d\n", nombreMots(racine));
      break;

    case 0:
      printf("\nProgramme terminé.\n");
      break;

    default:
      printf("\nOption invalide. Veuillez entrer une option valide.\n");
      break;
    }
  }

  libererArbre(racine);
  return EXIT_SUCCESS;
}
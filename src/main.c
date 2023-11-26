#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "noeud.h"

int main()
{
  Noeud *racine = NULL;
  char mot[50];

  // Charger les mots à partir du fichier fmots.txt
  FILE *fichier = fopen("fmots.txt", "r");
  if (fichier == NULL)
  {
    perror("Erreur lors de l'ouverture du fichier");
    return 1;
  }

  while (fgets(mot, sizeof(mot), fichier) != NULL)
  {
    // Supprimer le saut de ligne à la fin du mot
    size_t longueurMot = strlen(mot);
    if (longueurMot > 0 && mot[longueurMot - 1] == '\n')
    {
      mot[longueurMot - 1] = '\0';
    }

    racine = ajouterMot(racine, mot);
  }

  fclose(fichier);

  // Exemple d'utilisation des opérations
  printf("Arbre avant suppression :\n");
  afficherEnOrdre(racine);

  printf("\nRecherche du mot 'exemple' : %s\n", (rechercherMot(racine, "exemple") != NULL) ? "trouvé" : "non trouvé");

  printf("\nSuppression du mot 'exemple'\n");
  racine = supprimerMot(racine, "exemple");

  printf("\nArbre après suppression :\n");
  afficherEnOrdre(racine);

  printf("\nHauteur de l'arbre : %d\n", hauteurArbre(racine));

  printf("\nNombre de mots dans l'arbre : %d\n", nombreMots(racine));

  // Libérer la mémoire occupée par l'arbre
  libererArbre(racine);

  return EXIT_SUCCESS;
}
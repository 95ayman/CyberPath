#ifndef GRILLE_H
#define GRILLE_H

#define MAX_HAUTEUR 23
#define MAX_LARGEUR 23

// Vérifier si une position est valide pour placer des cibles
int positionValide(char grille[][MAX_LARGEUR], int hauteur, int largeur, int x, int y);

// Créer la grille de jeu
void creationGrille(char grille[][MAX_LARGEUR], int *hauteur, int *largeur);

// Afficher la grille
void afficherGrille(char grille[][MAX_LARGEUR], int hauteur, int largeur);

#endif // GRILLE_H

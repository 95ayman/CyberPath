#include "grille.h"
#include <stdio.h>
#include <stdlib.h>

// Vérifier si une position est valide pour placer des cibles
int positionValide(char grille[][MAX_LARGEUR], int hauteur, int largeur, int x, int y) {
    if (x < 0 || x >= hauteur || y < 0 || y >= largeur) return 0;
    if (grille[x][y] != '-') return 0;

    for (int i = -2; i <= 2; i++) {
        for (int j = -2; j <= 2; j++) {
            int nx = x + i;
            int ny = y + j;
            if (nx >= 0 && ny >= 0 && nx < hauteur && ny < largeur && grille[nx][ny] != '-') {
                return 0;
            }
        }
    }
    return 1;
}

// Créer la grille de jeu
void creationGrille(char grille[][MAX_LARGEUR], int *hauteur, int *largeur) {
    *largeur = rand() % 6 + 17;
    *hauteur = rand() % 6 + 17;

    for (int i = 0; i < *hauteur; i++) {
        for (int j = 0; j < *largeur; j++) {
            grille[i][j] = '-';
        }
    }

    // Définir les limites de la grille
    for (int i = 0; i < *largeur; i++) {
        grille[0][i] = '0';
        grille[*hauteur - 1][i] = '0';
    }

    for (int i = 0; i < *hauteur; i++) {
        grille[i][0] = '0';
        grille[i][*largeur - 1] = '0';
    }

    // Ajouter des obstacles internes
    for (int i = 0; i < 2; i++) {
        int random1;

        random1 = rand() % (*hauteur - 2) + 1;
        grille[random1][1] = '0';

        random1 = rand() % (*hauteur - 2) + 1;
        grille[random1][*largeur - 2] = '0';

        random1 = rand() % (*largeur - 2) + 1;
        grille[1][random1] = '0';

        random1 = rand() % (*largeur - 2) + 1;
        grille[*hauteur - 2][random1] = '0';
    }

    // Placer les cibles
    int ciblesPlacees = 0;
    while (ciblesPlacees < 10) {
        int random1 = rand() % (*hauteur - 2) + 1;
        int random2 = rand() % (*largeur - 2) + 1;
        if (positionValide(grille, *hauteur, *largeur, random1, random2)) {
            grille[random1][random2] = '1';
            ciblesPlacees++;
        }
    }

    // Placer les robots
    char robots[] = {'A', 'B', 'C', 'D'};
    for (int i = 0; i < 4; i++) {
        int random1, random2;
        do {
            random1 = rand() % (*hauteur - 2) + 1;
            random2 = rand() % (*largeur - 2) + 1;
        } while (grille[random1][random2] != '-');

        grille[random1][random2] = robots[i];
    }
}

// Afficher la grille
void afficherGrille(char grille[][MAX_LARGEUR], int hauteur, int largeur) {
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            printf("%c ", grille[i][j]);
        }
        printf("\n");
    }
}

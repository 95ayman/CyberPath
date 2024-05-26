#include "robot.h"
#include <stdio.h>

// Déplacer le robot selon l'entrée de l'utilisateur
int deplacerRobot(char grille[][MAX_LARGEUR], int hauteur, int largeur, int startX, int startY, int maxDeplacements) {
    int deplacements = 0;
    int x = startX;
    int y = startY;
    char robot = grille[x][y];
    char direction;

    while (deplacements < maxDeplacements) {
        printf("Il vous reste %d mouvements.\n", maxDeplacements - deplacements);
        printf("Entrez la direction (z=haut, s=bas, q=gauche, d=droite) : ");
        scanf(" %c", &direction);

        // Assurer une entrée valide
        if (direction != 'z' && direction != 's' && direction != 'q' && direction != 'd') {
            printf("Direction invalide ! Veuillez entrer z, s, q ou d.\n");
            continue;
        }

        // Incrémenter le compte des déplacements
        deplacements++;

        switch (direction) {
            case 'z': // Déplacer vers le haut
                while (x > 0 && grille[x-1][y] != '0' && grille[x-1][y] != 'A' && grille[x-1][y] != 'B' && grille[x-1][y] != 'C' && grille[x-1][y] != 'D') {
                    grille[x][y] = '-';
                    x--;
                    if (grille[x][y] == '1') {
                        grille[x][y] = robot;
                        // Afficher la grille après chaque déplacement
                        afficherGrille(grille, hauteur, largeur);
                        return deplacements;
                    }
                    grille[x][y] = robot;
                }
                break;
            case 's': // Déplacer vers le bas
                while (x < hauteur - 1 && grille[x+1][y] != '0' && grille[x+1][y] != 'A' && grille[x+1][y] != 'B' && grille[x+1][y] != 'C' && grille[x+1][y] != 'D') {
                    grille[x][y] = '-';
                    x++;
                    if (grille[x][y] == '1') {
                        grille[x][y] = robot;
                        // Afficher la grille après chaque déplacement
                        afficherGrille(grille, hauteur, largeur);
                        return deplacements;
                    }
                    grille[x][y] = robot;
                }
                break;
            case 'q': // Déplacer vers la gauche
                while (y > 0 && grille[x][y-1] != '0' && grille[x][y-1] != 'A' && grille[x][y-1] != 'B' && grille[x][y-1] != 'C' && grille[x][y-1] != 'D') {
                    grille[x][y] = '-';
                    y--;
                    if (grille[x][y] == '1') {
                        grille[x][y] = robot;
                        // Afficher la grille après chaque déplacement
                        afficherGrille(grille, hauteur, largeur);
                        return deplacements;
                    }
                    grille[x][y] = robot;
                }
                break;
            case 'd': // Déplacer vers la droite
                while (y < largeur - 1 && grille[x][y+1] != '0' && grille[x][y+1] != 'A' && grille[x][y+1] != 'B' && grille[x][y+1] != 'C' && grille[x][y+1] != 'D') {
                    grille[x][y] = '-';
                    y++;
                    if (grille[x][y] == '1') {
                        grille[x][y] = robot;
                        // Afficher la grille après chaque déplacement
                        afficherGrille(grille, hauteur, largeur);
                        return deplacements;
                    }
                    grille[x][y] = robot;
                }
                break;
        }

        // Afficher la grille après chaque déplacement
        afficherGrille(grille, hauteur, largeur);
    }

    return deplacements;
}

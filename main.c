#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "grille.h"
#include "robot.h"

// Effacer l'écran
void effacerEcran() {
    printf("\033[H\033[J");
}

int main() {
    srand(time(NULL)); // Initialiser le générateur de nombres aléatoires

    int hauteur, largeur;
    char grille[MAX_HAUTEUR][MAX_LARGEUR];
    char robots[] = {'A', 'B', 'C', 'D'};

    // Choisir le niveau de difficulté
    int difficulte;
    printf("Choisissez le niveau de difficulté (1 : Facile, 2 : Normal, 3 : Difficile) : ");
    scanf("%d", &difficulte);

    // Définir le temps d'affichage en fonction du niveau de difficulté
    int tempsAffichage;
    switch (difficulte) {
        case 1: tempsAffichage = 35; break;
        case 2: tempsAffichage = 25; break;
        case 3: tempsAffichage = 15; break;
        default: printf("Choix invalide ! Niveau de difficulté par défaut : Normal.\n");
                 tempsAffichage = 25; break;
    }

    // Variables de jeu
    int nombreJoueurs;
    printf("Entrez le nombre de joueurs : ");
    scanf("%d", &nombreJoueurs);

    if (nombreJoueurs <= 0) {
        printf("Nombre de joueurs invalide.\n");
        return 1;
    }

    int scoresJoueurs[nombreJoueurs];
    for (int i = 0; i < nombreJoueurs; i++) {
        scoresJoueurs[i] = 0;
    }

    int nombreRounds;
    printf("Entrez le nombre de rounds : ");
    scanf("%d", &nombreRounds);

    if (nombreRounds <= 0) {
        printf("Nombre de rounds invalide.\n");
        return 1;
    }

    // Créer une grille unique pour tous les rounds
    creationGrille(grille, &hauteur, &largeur);

    for (int round = 1; round <= nombreRounds; round++) {
        printf("Round %d/%d\n", round, nombreRounds);

        // Choisir un robot au hasard pour chaque round
        int indiceRobot = rand() % 4;
        char robotChoisi = robots[indiceRobot];
        int startX = -1, startY = -1;

        // Trouver la position initiale du robot choisi
        for (int i = 0; i < hauteur; i++) {
            for (int j = 0; j < largeur; j++) {
                if (grille[i][j] == robotChoisi) {
                    startX = i;
                    startY = j;
                    break;
                }
            }
            if (startX != -1) break;
        }

        if (startX == -1 || startY == -1) {
            printf("Aucun robot trouvé sur la grille.\n");
            continue;
        }

        // Afficher quel robot nous utilisons pour le round
        printf("Nous jouons avec le robot %c\n", robotChoisi);

        // Afficher la grille pendant le temps spécifié
        afficherGrille(grille, hauteur, largeur);
        sleep(tempsAffichage); // Pause pendant le temps spécifié

        // Effacer l'écran
        effacerEcran();

        // Chaque joueur estime le nombre de déplacements
        int estimationsJoueurs[nombreJoueurs];
        for (int i = 0; i < nombreJoueurs; i++) {
            printf("Joueur %d, entrez le nombre de déplacements que vous pensez faire : ", i + 1);
            scanf("%d", &estimationsJoueurs[i]);
            if (estimationsJoueurs[i] <= 0) {
                printf("Impossible, donnez un nombre positif.\n");
                i--;
            }
        }

        // Déterminer le joueur avec l'estimation la plus basse
        int estimationMin = estimationsJoueurs[0];
        int joueurEstimationMin = 0;
        for (int i = 1; i < nombreJoueurs; i++) {
            if (estimationsJoueurs[i] < estimationMin) {
                estimationMin = estimationsJoueurs[i];
                joueurEstimationMin = i;
            }
        }

        printf("Joueur %d estime faire %d déplacements et va jouer.\n", joueurEstimationMin + 1, estimationMin);

        // Réafficher la grille pour le joueur qui fait les déplacements
        effacerEcran();
        printf("Nous jouons avec le robot %c\n", robotChoisi);
        afficherGrille(grille, hauteur, largeur);

        // Déplacer le robot selon l'entrée du joueur et compter les déplacements
        int deplacementsReels = deplacerRobot(grille, hauteur, largeur, startX, startY, estimationMin);

        // Affichage de débogage pour comprendre le nombre de déplacements
        printf("Joueur %d a utilisé %d déplacements.\n", joueurEstimationMin + 1, deplacementsReels);

        // Vérifier si le robot a atteint une cible (est sur une case '1')
        int cibleAtteinte = 0;
        if (grille[startX][startY] == '1') {
            cibleAtteinte = 1;
        }

        // Mettre à jour les scores selon le nouveau système de points
        if (cibleAtteinte) {
            if (deplacementsReels == estimationMin) {
                scoresJoueurs[joueurEstimationMin] += 2; // Atteindre la cible exactement dans les déplacements estimés
            } else if (deplacementsReels < estimationMin) {
                scoresJoueurs[joueurEstimationMin] -= 1; // Atteindre la cible avec moins de déplacements que l'estimation
                if (scoresJoueurs[joueurEstimationMin] < 0) {
                    scoresJoueurs[joueurEstimationMin] = 0; // Le score ne peut pas être inférieur à 0
                }
            }
        } else {
            // Si le joueur n'a pas atteint la cible, les autres joueurs gagnent 1 point
            for (int i = 0; i < nombreJoueurs; i++) {
                if (i != joueurEstimationMin) {
                    scoresJoueurs[i]++; // Les autres joueurs gagnent 1 point si le joueur échoue à atteindre la cible
                }
            }
        }

        // Afficher les scores actuels
        printf("Scores actuels :\n");
        for (int i = 0; i < nombreJoueurs; i++) {
            printf("Joueur %d : %d\n", i + 1, scoresJoueurs[i]);
        }
    }

    // Déterminer le(s) gagnant(s)
    int scoreMax = scoresJoueurs[0];
    for (int i = 1; i < nombreJoueurs; i++) {
        if (scoresJoueurs[i] > scoreMax) {
            scoreMax = scoresJoueurs[i];
        }
    }

    printf("Le(s) gagnant(s) :\n");
    for (int i = 0; i < nombreJoueurs; i++) {
        if (scoresJoueurs[i] == scoreMax) {
            printf("Joueur %d avec un score de %d !\n", i + 1, scoresJoueurs[i]);
        }
    }

    return 0;
}

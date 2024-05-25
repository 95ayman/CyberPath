#include "game.h"
#include "util.h"

int main() {
    srand(time(NULL)); // Initialize random number generator

    int hauteur, largeur;
    char grille[MAX_HAUTEUR][MAX_LARGEUR];
    char robots[] = {'A', 'B', 'C', 'D'};

    // Choose difficulty level
    int difficulte = choisirDifficulte();

    // Set display time based on difficulty level
    int tempsAffichage = obtenirTempsAffichage(difficulte);

    // Game variables
    int nombreJoueurs = obtenirNombreJoueurs();
    int scoresJoueurs[nombreJoueurs];
    initialiserScores(scoresJoueurs, nombreJoueurs);

    int nombreRounds = obtenirNombreRounds();

    // Create a unique grid for all rounds
    creationGrille(grille, &hauteur, &largeur);

    for (int round = 1; round <= nombreRounds; round++) {
        printf("Round %d/%d\n", round, nombreRounds);

        // Randomly choose a robot for each round
        int indiceRobot = rand() % 4;
        char robotChoisi = robots[indiceRobot];
        int startX = -1, startY = -1;

        // Find the initial position of the chosen robot
        trouverPositionInitiale(grille, hauteur, largeur, robotChoisi, &startX, &startY);

        if (startX == -1 || startY == -1) {
            printf("Aucun robot trouvé sur la grille.\n");
            continue;
        }

        // Display the robot we are using for the round
        printf("Nous jouons avec le robot %c\n", robotChoisi);

        // Display the grid for the specified time
        afficherGrille(grille, hauteur, largeur);
        attendre(tempsAffichage);

        // Clear the screen
        effacerEcran();

        // Each player estimates the number of moves
        int estimationsJoueurs[nombreJoueurs];
        obtenirEstimations(estimationsJoueurs, nombreJoueurs);

        // Determine the player with the lowest estimate
        int joueurEstimationMin = determinerJoueurEstimationMin(estimationsJoueurs, nombreJoueurs);

        printf("Joueur %d estime faire %d déplacements et va jouer.\n", joueurEstimationMin + 1, estimationsJoueurs[joueurEstimationMin]);

        // Redisplay the grid for the player making the moves
        effacerEcran();
        printf("Nous jouons avec le robot %c\n", robotChoisi);
        afficherGrille(grille, hauteur, largeur);

        // Move the robot according to the player's input and count the moves
        int deplacementsReels = deplacerRobot(grille, hauteur, largeur, startX, startY, estimationsJoueurs[joueurEstimationMin]);

        // Debug output to understand the number of moves
        printf("Joueur %d a utilisé %d déplacements.\n", joueurEstimationMin + 1, deplacementsReels);

        // Check if the robot reached a target (is on a '1' cell)
        int cibleAtteinte = verifierCibleAtteinte(grille, startX, startY);

        // Update scores according to the new point system
        mettreAJourScores(scoresJoueurs, nombreJoueurs, joueurEstimationMin, cibleAtteinte, deplacementsReels, estimationsJoueurs[joueurEstimationMin]);

        // Display current scores
        afficherScores(scoresJoueurs, nombreJoueurs);
    }

    // Determine the winner(s)
    afficherGagnants(scoresJoueurs, nombreJoueurs);

    return 0;
}


#ifndef ROBOT_H
#define ROBOT_H

#include "grille.h"

// Déplacer le robot selon l'entrée de l'utilisateur
int deplacerRobot(char grille[][MAX_LARGEUR], int hauteur, int largeur, int startX, int startY, int maxDeplacements);

#endif // ROBOT_H

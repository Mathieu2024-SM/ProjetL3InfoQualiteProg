#ifndef TERRAIN_H
#define TERRAIN_H

#include <vector>
#include <iostream>
#include <string>

/**
	Elements dans un terrain
		'X' = un mur --> le robot ne doit pas aller dessus
		'.' = une case vide --> le robot peut aller dessus
		'A' = case d'arriver --> case où le robot doit arriver
*/

class Terrain {
private:
    std::vector<std::vector<char>> d_grille; // Un tableau de caractère
    int d_hauteur, d_largeur; // Hauteur et largeur du terrain

public:
    Terrain(int hauteur, int largeur); // Constructeur
    Terrain(); // Constructeur par défaut

    int hauteur() const;
    int largeur() const;
    std::pair<int, int> positionAleatoireLibrePourRobot() const;

    void chargerTerrainDepuis(std::string chemin);
    void sauverTerrainSur(std::string cheminFichier) const;
    void afficherTerrain() const;
    bool Obstacle(int x, int y) const;

    void modifierElementGrille(int x, int y, char ch);
    char afficherElementGrille(int x, int y) const;
    void donnerElementGrille(int x, int y, char ch);
};

#endif

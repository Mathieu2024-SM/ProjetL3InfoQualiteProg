#ifndef TERRAIN_H
#define TERRAIN_H

#include <vector>
#include <iostream>
#include <string>

using std::string;

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

    void chargerTerrainDepuis(string chemin);
    bool Obstacle(int x, int y) const;

    void sauverTerrainSur(string cheminFichier) const;
    void sauverTerrainASCIISur(const string& chemin, const int& robotX, const int& robotY, const string& formeRobot) const;
    void sauverTerrainUnicodeSur(const string& chemin, const int& robotX, const int& robotY, const string& formeRobot) const;

    void modifierElementGrille(int x, int y, char ch);
    char afficherElementGrille(int x, int y) const;
    void donnerElementGrille(int x, int y, char ch);

    void afficherTerrainUnicode(const int &x, const int &y, const string& forme)const;
    void afficherTerrainASCII(const int &x, const int &y, const string& forme) const;
    void afficherTerrainSimple(const int &x, const int &y, const string& forme) const;
};

#endif

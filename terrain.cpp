#include "terrain.h"
#include <fstream>
#include <cstdlib> // Pour rand() et srand()
#include <ctime>   // Pour initialiser srand()

Terrain::Terrain(int hauteur, int largeur) : d_grille(hauteur, std::vector<char>(largeur, '.')), d_hauteur{hauteur}, d_largeur{largeur} {}

Terrain::Terrain() : d_grille{}, d_hauteur{0}, d_largeur{0} {}

int Terrain::hauteur() const {
    return d_hauteur;
}

int Terrain::largeur() const {
    return d_largeur;
}

std::pair<int, int> Terrain::positionAleatoireLibrePourRobot() const {
    int maxAttempts = 1000; // Limite pour éviter des boucles infinies
    int attempts = 0;

    while (attempts < maxAttempts) {
        int x = rand() % d_largeur; // Génère un x aléatoire
        int y = rand() % d_hauteur; // Génère un y aléatoire

        if (d_grille[y][x] != 'X') { // Vérifie que la case n'est pas un mur
            return {x, y};
        }

        attempts++;
    }

    std::cerr << "Erreur : Impossible de trouver une position libre pour le robot !" << std::endl;
    return {0, 0}; // Retourne une position par défaut en cas d'échec
}


void Terrain::chargerTerrainDepuis(std::string chemin) {
    std::ifstream fichierterrain(chemin);

    if (!fichierterrain) {
        std::cerr << "Erreur de lecture" << std::endl;
        return;
    }

    d_grille.clear();
    std::string ligne;
    while (std::getline(fichierterrain, ligne)) {
        d_grille.emplace_back(ligne.begin(), ligne.end());
    }
    d_hauteur = d_grille.size();
    d_largeur = d_hauteur > 0 ? d_grille[0].size() : 0;
}

void Terrain::sauverTerrainSur(std::string chemin) const {
    std::ofstream fichierterrain(chemin);

    if (!fichierterrain) {
        std::cerr << "Erreur de lecture" << std::endl;
        return;
    }
    for (const auto& ligne : d_grille) {
        for (char colonne : ligne) {
            fichierterrain << colonne;
        }
        fichierterrain << "\n";
    }
}

void Terrain::afficherTerrain() const {
    for (const auto& ligne : d_grille) {
        for (char colonne : ligne) {
            std::cout << colonne << ' ';
        }
        std::cout << std::endl;
    }
}

bool Terrain::Obstacle(int x, int y) const {
    if (x < 0 || y < 0 || x >= d_hauteur || y >= d_largeur) {
        return true; // Considérer hors-limites comme obstacle
    }
    return d_grille[x][y] == 'X';
}

void Terrain::modifierElementGrille(int x, int y, char ch) {
    if (x >= 0 && x < d_largeur && y >= 0 && y < d_hauteur) {
        d_grille[y][x] = ch; // Mise à jour de l'élément de la grille
    } else {
        std::cerr << "Erreur : Coordonnées (" << x << ", " << y << ") hors limites !" << std::endl;
    }
}

char Terrain::afficherElementGrille(int x, int y) const {
    if (x >= 0 && y >= 0 && x < d_hauteur && y < d_largeur) {
        return d_grille[x][y];
    }
    return 'X'; // Retourne un mur pour les coordonnées invalides
}

void Terrain::donnerElementGrille(int x, int y, char ch) {
    if (x >= 0 && y >= 0 && x < d_hauteur && y < d_largeur) {
        d_grille[x][y] = ch;
    }
}

#include "terrain.h"
#include <fstream>
#include <cstdlib> // Pour rand() et srand()
#include <ctime>   // Pour initialiser srand()
#include <vector>
#include <thread>  // Pour std::this_thread::sleep_for
#include <chrono>  // Pour std::chrono::seconds, std::chrono::milliseconds

using std::cout;
using std::endl;

Terrain::Terrain(int hauteur, int largeur)
    : d_grille(hauteur, std::vector<char>(largeur, '.')), d_hauteur{hauteur}, d_largeur{largeur} {}

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

        char element = afficherElementGrille(x, y);
        if (element != 'X' && element != '+' && element != '-' && element != '|') {
            return {x, y};
        }

        attempts++;
    }
    return {-1, -1}; // Retourne une position d'erreur
}

void Terrain::chargerTerrainDepuis(string chemin) {
    std::ifstream fichierterrain(chemin);

    if (!fichierterrain) {
        std::cerr << "Erreur de lecture" << std::endl;
        return;
    }

    d_grille.clear();
    string ligne;
    while (std::getline(fichierterrain, ligne)) {
        d_grille.emplace_back(ligne.begin(), ligne.end());
    }
    d_hauteur = d_grille.size();
    d_largeur = d_hauteur > 0 ? d_grille[0].size() : 0;
}

void Terrain::sauverTerrainSur(string chemin) const {
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

bool Terrain::Obstacle(int x, int y) const {
    if (x < 0 || y < 0 || x >= d_hauteur || y >= d_largeur) {
        return true; // Considérer hors-limites comme obstacle
    }
    char element = d_grille[x][y];
    return (element == 'X' || element == '+' || element == '-' || element == '|');
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

void Terrain::afficherTerrainUnicode(const int &x, const int &y, const string& forme) const {
    system("chcp 65001 > nul"); // Change l'encodage de la console pour UTF-8
    cout << "\033[H\033[J";    // Code ANSI pour nettoyer la console

    for (int i = 0; i < d_grille.size(); ++i) {
        for (int j = 0; j < d_grille[i].size(); ++j) {
            // Afficher le robot à sa position
            if (i == x && j == y) {
                if (forme == ">") cout << "\u25B7";  // Flèche droite
                else if (forme == "<") cout << "\u25C1";  // Flèche gauche
                else if (forme == "^") cout << "\u25B3";  // Flèche haut
                else cout << "\u25BD";  // Flèche bas
            } else if (d_grille[i][j] == 'X') {
                // Coins réels
                if (i == 0 && j == 0) cout << "┏";  // Coin supérieur gauche
                else if (i == 0 && j == d_grille[i].size() - 1) cout << "┓";  // Coin supérieur droit
                else if (i == d_grille.size() - 1 && j == 0) cout << "┗";  // Coin inférieur gauche
                else if (i == d_grille.size() - 1 && j == d_grille[i].size() - 1) cout << "┛";  // Coin inférieur droit
                // Murs
                else if (i == 0 || i == d_grille.size() - 1) cout << "━";  // Mur horizontal
                else if (j == 0 || j == d_grille[i].size() - 1) cout << "┃";  // Mur vertical
                else cout << "━";  // Espaces ou autres éléments non spécifiques
            } else if (d_grille[i][j] == 'A') {
                cout << "▄";  // Objectif
            } else {
                cout << d_grille[i][j];  // Chemins ou autres éléments
            }
        }
        cout << '\n';  // Nouvelle ligne après chaque ligne du terrain
    }
}


void Terrain::afficherTerrainASCII(const int &x, const int &y, const string& forme) const {
    cout << "\033[H\033[J"; // Code ANSI pour nettoyer la console

    for (int i = 0; i < d_grille.size(); ++i) {
        for (int j = 0; j < d_grille[i].size(); ++j) {
            // Afficher le robot à sa position
            if (i == x && j == y) {
                cout << forme;
            } else if (d_grille[i][j] == 'X') {
                // Gestion des caractères ASCII pour les murs
                bool murHaut = i > 0 && d_grille[i - 1][j] == 'X';
                bool murBas = i < d_grille.size() - 1 && d_grille[i + 1][j] == 'X';
                bool murGauche = j > 0 && d_grille[i][j - 1] == 'X';
                bool murDroit = j < d_grille[i].size() - 1 && d_grille[i][j + 1] == 'X';

                if (murHaut && murBas && murGauche && murDroit) cout << "+";
                else if (murHaut && murBas) cout << "|";
                else if (murGauche && murDroit) cout << "-";
                else cout << "+";
            } else if (d_grille[i][j] == 'A') {
                cout << "O";  // Objectif
            } else {
                cout << d_grille[i][j];
            }
        }
        cout << '\n';
    }
}

void Terrain::afficherTerrainSimple(const int &x, const int &y, const string& forme) const
{
    for (auto i = 0; i < d_grille.size(); i++) {
        for (auto j = 0; j < d_grille[0].size(); j++) {
            if (i == x && j == y) {
                std::cout << forme << ' ';
            } else {
                std::cout << d_grille[i][j] << ' ';
            }
        }
        std::cout << std::endl;
    }
}

void Terrain::sauverTerrainASCIISur(const string& chemin, const int& x, const int& y, const string& forme) const {

    std::ofstream fichierterrain(chemin);

    if (!fichierterrain) {
        std::cerr << "Erreur d'écriture du fichier en ASCII" << std::endl;
        return;
    }

    for (int i = 0; i < d_grille.size(); ++i) {
        for (int j = 0; j < d_grille[i].size(); ++j) {
            // Afficher le robot à sa position
            if (i == x && j == y) {
                fichierterrain << forme;
            } else if (d_grille[i][j] == 'X') {
                // Gestion des caractères ASCII pour les murs
                bool murHaut = i > 0 && d_grille[i - 1][j] == 'X';
                bool murBas = i < d_grille.size() - 1 && d_grille[i + 1][j] == 'X';
                bool murGauche = j > 0 && d_grille[i][j - 1] == 'X';
                bool murDroit = j < d_grille[i].size() - 1 && d_grille[i][j + 1] == 'X';

                if (murHaut && murBas && murGauche && murDroit) fichierterrain << "+";
                else if (murHaut && murBas) fichierterrain << "|";
                else if (murGauche && murDroit) fichierterrain << "-";
                else fichierterrain<< "+";
            } else if (d_grille[i][j] == 'A') {
                fichierterrain << "O";  // Objectif
            } else {
                fichierterrain << d_grille[i][j];
            }
        }
        fichierterrain << '\n';
    }

    fichierterrain.close();
}

void Terrain::sauverTerrainUnicodeSur(const string& chemin, const int& x, const int& y, const string& forme) const {
    system("chcp 65001 > nul"); // Change l'encodage de la console pour UTF-8
    cout << "\033[H\033[J";    // Code ANSI pour nettoyer la console

    std::ofstream fichierterrain(chemin);

    if (!fichierterrain) {
        std::cerr << "Erreur d'écriture du fichier en Unicode" << std::endl;
        return;
    }

    for (int i = 0; i < d_grille.size(); ++i) {
        for (int j = 0; j < d_grille[i].size(); ++j) {
            // Afficher le robot à sa position
            if (i == x && j == y) {
                if (forme == ">") fichierterrain << "\u25B7";  // Flèche droite
                else if (forme == "<") fichierterrain << "\u25C1";  // Flèche gauche
                else if (forme == "^") fichierterrain << "\u25B3";  // Flèche haut
                else fichierterrain<< L"\u25BD";  // Flèche bas

            } else if (d_grille[i][j] == 'X') {
                // Coin
                if (i == 0 && j == 0) fichierterrain << "┏";  // Coin supérieur gauche
                else if (i == 0 && j == d_grille[i].size() - 1) fichierterrain << "┓";  // Coin supérieur droit
                else if (i == d_grille.size() - 1 && j == 0) fichierterrain << "┗";  // Coin inférieur gauche
                else if (i == d_grille.size() - 1 && j == d_grille[i].size() - 1) fichierterrain << "┛";  // Coin inférieur droit
                // Murs
                else if (i == 0 || i == d_grille.size() - 1) fichierterrain << "━";  // Mur horizontal
                else if (j == 0 || j == d_grille[i].size() - 1) fichierterrain << "┃";  // Mur vertical
                else fichierterrain << "━";  // Espaces ou autres éléments non spécifiques
            } else if (d_grille[i][j] == 'A') {
                fichierterrain << "▄";  // Objectif
            } else {
                fichierterrain << d_grille[i][j];  // Chemins ou autres éléments
            }
        }
        fichierterrain << '\n';  // Nouvelle ligne après chaque ligne du terrain
    }

    fichierterrain.close();
}










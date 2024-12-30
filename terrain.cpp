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
    system("chcp 65001 > nul");  // Change l'encodage de la console pour UTF-8
     cout << "\033[H\033[J";  // Code ANSI pour nettoyer la console
    for (int i = 0; i < d_grille.size(); ++i) {
        for (int j = 0; j < d_grille[i].size(); ++j) {
            // Afficher le robot à sa position
            if (i == x && j == y) {
                //cout << forme;  // Affiche le robot sans espace
                if(forme == ">")
                    cout << "\u25B7"; //code unicode pour la fleche droite

                else if (forme == "<")
                    cout << "\u25C1";

                else if (forme == "^")
                    cout << "\u25B3";

                else
                    cout << "\u25BD";
            }
            else {
                switch (d_grille[i][j]) {
                    case '-':
                        cout << "━";  // Mur horizontal
                        break;
                    case '.':
                        cout << ".";  // Chemin libre, espace vide
                        break;
                    case 'A':
                        cout << "▄";  // Objectif
                        break;
                    case '|':
                        cout << "┃";  // Mur vertical
                        break;
                    case '+':
                        // ┏ ┓ ┛ ┗ ┻ ┻ +
                        // Gestion des coins : les tests sont organisés par direction
                        if (i > 0 && j > 0 && d_grille[i-1][j] == '|' && d_grille[i][j-1] == '-') {
                            cout << "┛";  // Coin supérieur gauche
                        } else if (i > 0 && j < d_grille[i].size()-1 && d_grille[i-1][j] == '|' && d_grille[i][j+1] == '-') {
                            cout << "┗";  // Coin supérieur droit
                        } else if (i < d_grille.size()-1 && j > 0 && d_grille[i+1][j] == '|' && d_grille[i][j-1] == '-') {
                            cout << "┓";  // Coin inférieur gauche
                        } else if (i < d_grille.size()-1 && j < d_grille[i].size()-1 && d_grille[i+1][j] == '|' && d_grille[i][j+1] == '-') {
                            cout << "┏";  // Coin inférieur droit
                        }
                        // Si c'est un coin bas-droit, vérifier la jonction horizontale et verticale
                        else if (i < d_grille.size() - 1 && j < d_grille[i].size() - 1 &&
                                 d_grille[i+1][j] == '|' && d_grille[i][j+1] == '-') {
                            cout << "┏";  // Coin inférieur droit (vérification spécifique)
                        }
                        else {
                            cout << "+";  // Intersection ou autre cas
                        }
                        break;
                    default:
                        cout << d_grille[i][j];  // Affiche d'autres éléments
                        break;
                }
            }
        }
        std::cout << '\n';  // Nouvelle ligne après chaque ligne du terrain
    }
}
void Terrain::afficherTerrainASCII(const int &x, const int &y, const string& forme) const {
    cout << "\033[H\033[J";  // Code ANSI pour nettoyer la console
    for (int i = 0; i < d_grille.size(); ++i) {
        for (int j = 0; j < d_grille[i].size(); ++j) {
            // Afficher le robot à sa position
            if (i == x && j == y) {
                cout << forme;  // Affiche le robot sans espace
            } else {
                switch (d_grille[i][j]) {
                    case '-':
                        cout << "-";  // Mur horizontal
                        break;
                    case '.':
                        cout << ".";  // Chemin libre, espace vide
                        break;
                    case 'A':
                        cout << "O";  // Objectif
                        break;
                    case '|':
                        cout << "|";  // Mur vertical
                        break;
                    case '+':
                        cout << "+";  // Intersection ou autre cas
                        break;
                    default:
                        cout << d_grille[i][j];  // Affiche d'autres éléments
                        break;
                }
            }
        }
        std::cout << '\n';  // Nouvelle ligne après chaque ligne du terrain
    }
}


void Terrain::afficherTerrainSimple(const int &x, const int &y, const string& forme) const {
    // Vérifie si la grille est vide
    if (d_grille.empty() || d_grille[0].empty()) {
        std::cout << "La grille est vide !\n";
        return;
    }

    for (int i = 0; i < d_grille.size(); ++i) {
        for (int j = 0; j < d_grille[i].size(); ++j) {
            // Afficher le robot à sa position
            if (i == x && j == y) {
                cout << forme;  // Affiche le robot sans espace
            } else {
                // Afficher les éléments du terrain
                switch (d_grille[i][j]) {
                    case '-':
                        cout << "X";  // Mur horizontal
                        break;
                    case '.':
                        cout << ".";  // Chemin libre, espace vide
                        break;
                    case 'A':
                        cout << "O";  // Objectif
                        break;
                    case '|':
                        cout << "X";  // Mur vertical
                        break;
                    case '+':
                        cout << "X";  // Intersection ou autre cas
                        break;
                    default:
                        cout << d_grille[i][j];  // Affiche d'autres éléments
                        break;
                }
            }
        }
        cout << '\n';  // Nouvelle ligne après chaque ligne du terrain
    }
}















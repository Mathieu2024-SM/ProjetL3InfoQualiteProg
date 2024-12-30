#include "interface.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>  // Pour std::this_thread::sleep_for
#include <chrono>  // Pour std::chrono::seconds, std::chrono::milliseconds
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

Interface::Interface() : d_algo{nullptr}
{}

int Interface::choisirAlgo() {
    int choix;
    cout << "\nChoisissez un algorithme :\n";
    cout << "1. Algorithme de la Main Droite\n";
    cout << "2. Algorithme de Pledge\n";
    cout << "Votre choix : ";
    cin >> choix;

    if (choix == 1) {
        d_algo = new AlgoMainDroite(d_robot);
    } else if (choix == 2) {
        d_algo = new AlgoPledge(d_robot);
    } else {
        cout << "Choix invalide. Aucun algorithme sélectionne.\n";
        return -1;
    }

    return choix;
}

void Interface::choisirAffichage() {
    int choix;
    cout << "Choisissez le type d'affichage du terrain :\n";
    cout << "0. Affichage Unicode\n";
    cout << "1. Affichage ASCII\n";
    cout << "2. Affichage Simple\n";
    cout << "Votre choix : ";
    cin >> choix;

    switch (choix) {
        case TYPEUNICODE:
            d_typeAffichage = TYPEUNICODE;
            break;
        case TYPEASCII:
            d_typeAffichage = TYPEASCII;
            break;
        case TYPESIMPLE:
            d_typeAffichage = TYPESIMPLE;
            break;
        default:
            cout << "Choix invalide. Affichage par défaut ASCII sélectionné.\n";
            break;
    }
}

void Interface::sauvegarderTerrain() const {
    char choix;
    cout << "\nSouhaitez-vous sauvegarder le terrain dans un fichier ? (o/n) : ";
    cin >> choix;

    if (choix == 'o' || choix == 'O') {
        string chemin;
        cout << "Entrez le nom du fichier de sauvegarde : ";
        cin >> chemin;

        d_terrain.sauverTerrainSur(chemin);
        cout << "Terrain sauvegarde avec succes dans " << chemin << ".\n";
    }
}
void Interface::afficherObservations() const
{

    char choix;
    cout << "\nSouhaitez-vous afficher les déplacements du robot ? (o/n) : ";
    cin >> choix;

    if (choix == 'o' || choix == 'O') {
        cout << "\n===== Deplacements du robot =====\n";
        for (const auto& obs : d_robot.getObservateurs()) {
            obs->afficheObservation();
        }
        cout << "=================================\n";

    }

}

void Interface::chargerTerrain() {
    string nomFichier;
    cout << "Entrez le nom du fichier de terrain : ";
    cin >> nomFichier;

    // Chargement d'un fichier ASCII
    d_terrain.chargerTerrainDepuis(nomFichier);
    cout << "Terrain charge avec succes depuis le fichier : " << nomFichier << ".\n";
}

void Interface::afficherTerrain() {
    d_robot.positionnerAleatoirementSur(d_terrain);

    switch (d_typeAffichage) {
        case TYPEUNICODE:
            d_terrain.afficherTerrainUnicode(d_robot.getX(), d_robot.getY(),(d_robot.formeRobot()) );
            break;
        case TYPEASCII:
            d_terrain.afficherTerrainASCII(d_robot.getX(), d_robot.getY(),(d_robot.formeRobot()) );
            break;
        case TYPESIMPLE:
            d_terrain.afficherTerrainSimple(d_robot.getX(), d_robot.getY(),(d_robot.formeRobot()) );
            break;
        default:
            d_terrain.afficherTerrainASCII(d_robot.getX(), d_robot.getY(),(d_robot.formeRobot()) );
            break;
    }
}

void Interface::exectuerAlgo()
{
    if (d_terrain.hauteur() == 0 || d_terrain.largeur() == 0) {
        std::cout << "Veuillez d'abord charger un terrain.\n";
    }
    else {
        int algoChoix = choisirAlgo();
        if (algoChoix == 1) {
            AlgoMainDroite algo(d_robot);
            algo.typeAlgo(d_terrain, d_typeAffichage);
        }
        else if (algoChoix == 2) {
            AlgoPledge algo(d_robot);
            algo.typeAlgo(d_terrain, d_typeAffichage);
        }
        afficherObservations();
        sauvegarderTerrain();
    }
}

void Interface::supprimerAlgo()
{
    delete d_algo;
    d_algo = nullptr;
}

void Interface::run() {
    int choix;
    do {
        cout << "\n===== Menu Principal =====\n";
        cout << "1. Charger un terrain et choisir le type d'affichage \n";
        cout << "2. Afficher le terrain\n";
        cout << "3. Lancer un algorithme\n";
        cout << "4. Quitter\n";
        cout << "Votre choix : ";
        cin >> choix;

        switch (choix) {
            case 1:
                chargerTerrain();
                choisirAffichage(); // Choisir le type d'affichage
                break;

            case 2:
                if (d_terrain.hauteur() == 0 || d_terrain.largeur() == 0) {
                    std::cout << "Veuillez d'abord charger un terrain.\n";
                }
                else {
                    afficherTerrain();
                }
                break;

            case 3:
                exectuerAlgo();
                break;

            case 4:
                std::cout << "Fin des tests !\n";
                break;

            default:
                std::cout << "Choix invalide. Réessayez.\n";
                break;
        }
    }while (choix != 4);

    supprimerAlgo();
}




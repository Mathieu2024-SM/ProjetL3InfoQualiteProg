#include "interface.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>  // Pour std::this_thread::sleep_for
#include <chrono>  // Pour std::chrono::seconds, std::chrono::milliseconds
#include <string>
#include <limits>

using std::cout;
using std::cin;
using std::endl;
using std::string;

Interface::Interface() : d_algo{nullptr}
{}

bool Interface::AffichageErreurPasDeTerrainCharger() const
{
    return d_terrain.hauteur() == 0 || d_terrain.largeur() == 0;
}

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
    if (AffichageErreurPasDeTerrainCharger() == true) {
        std::cout << "Veuillez d'abord charger un terrain.\n";
    }
    else{
        int choix;
        cout << "Choisissez le type d'affichage du terrain :\n";
        cout << "0. Affichage Unicode\n";
        cout << "1. Affichage ASCII\n";
        cout << "Votre choix : ";
        cin >> choix;

        switch (choix) {
            case TYPEUNICODE:
                d_typeAffichage = TYPEUNICODE;
                break;
            case TYPEASCII:
                d_typeAffichage = TYPEASCII;
                break;
            default:
                cout << "Choix invalide. Affichage par défaut Simple sélectionné.\n";
                break;
        }
    }
}

void Interface::sauvegarderTerrain() const {
    if (AffichageErreurPasDeTerrainCharger() == true) {
        std::cout << "Veuillez d'abord charger un terrain.\n";
    }

    else
    {
        string chemin;
        cout << "Entrez le nom du fichier de sauvegarde : ";
        cin >> chemin;

        auto [x,y] = d_terrain.positionAleatoireLibrePourRobot();
        int positionRobotX = x, positionRobotY = y;

        if(d_typeAffichage == TYPEUNICODE){
            d_terrain.sauverTerrainUnicodeSur(chemin,positionRobotX,positionRobotY,d_robot.formeRobot());
        }
        else if(d_typeAffichage == TYPEASCII){
            d_terrain.sauverTerrainASCIISur(chemin,positionRobotX,positionRobotY,d_robot.formeRobot());
        }
        else{
            d_terrain.sauverTerrainSur(chemin);
        }
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
            d_terrain.afficherTerrainSimple(d_robot.getX(), d_robot.getY(),(d_robot.formeRobot()) );
            break;
    }
}

void Interface::exectuerAlgo()
{
    if (AffichageErreurPasDeTerrainCharger() == true) {
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
        cout << "Retour au menu, vous pouvez continuer les tests avec le meme terrain ou le changer \n";
    }
}

void Interface::supprimerAlgo()
{
    delete d_algo;
    d_algo = nullptr;
}

bool Interface::lecture_Choix(int& choix)
{
    auto testChoix = choix;
    std::cout << "Votre choix : " ;
    while ( ! ( std::cin >> testChoix ) || testChoix < 1 || testChoix > 6 )
    {
        if ( std::cin.eof() )
        {
            // ^D  (^Z sous windows); Fin du flux d'entree !
            return false;
        }
        else if ( std::cin.fail() )
        {
            std::cout << "Saisie incorrecte, recommencez : ";
            std::cin.clear();
            std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
        }
        else
        {
            std::cout << "Le chiffre n'est pas entre 1 et 6, recommencez : ";
        }
    }
    choix = testChoix;
    return true; // succès
}

void Interface::run() {
    int choix ;
    do {
        cout << "\n===== Menu Principal =====\n";
        cout << "1. Charger un terrain (format simple)\n";
        cout << "2. Choisir le type d'affichage \n";
        cout << "3. Afficher le terrain\n";
        cout << "4. Lancer un algorithme\n";
        cout << "5. Sauvegarder le terrain \n";
        cout << "6. Quitter\n";

        if(lecture_Choix(choix))
        {
                switch (choix) {
                case 1:
                    chargerTerrain();
                    break;

                case 2:
                    choisirAffichage();
                    break;

                case 3:
                    afficherTerrain();
                    break;

                case 4:
                    exectuerAlgo();
                    break;

                case 5:
                    sauvegarderTerrain();
                    break;

                case 6:
                    supprimerAlgo();
                    std::cout << "Fin des tests !\n";
                    break;

                default:
                    std::cout << "Choix invalide. Reessayez.\n";
                    break;
            }
        }

    }while (choix != 6);
}

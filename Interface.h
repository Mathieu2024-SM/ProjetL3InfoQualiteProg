#ifndef INTERFACE_H
#define INTERFACE_H

#include "robot.h"
#include "terrain.h"
#include "algorithme.h"



class Interface {
private:
    bool AffichageErreurPasDeTerrainCharger() const;
    void afficherTerrain(); // Méthode d'affichage spécifique
    void chargerTerrain();
    int choisirAlgo();
    void sauvegarderTerrain() const ;
    void afficherObservations() const;
    void choisirAffichage();
    void exectuerAlgo();
    void supprimerAlgo();
    bool lecture_Choix(int & choix);

    Terrain d_terrain;
    Robot d_robot;
    Algorithme* d_algo = nullptr;
    int d_typeAffichage = TYPESIMPLE;

    static constexpr int TYPEUNICODE = 0;
    static constexpr int TYPEASCII = 1;
    static constexpr int TYPESIMPLE = 2;


public:
    Interface();
    void run();
};

#endif

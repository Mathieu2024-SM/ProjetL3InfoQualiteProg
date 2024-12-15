#include "terrain.h"
#include <fstream>

Terrain::Terrain(int hauteur , int largeur) : d_grille{}, d_hauteur{hauteur}, d_largeur{largeur}
{}
Terrain::Terrain() : d_grille{}, d_hauteur{0}, d_largeur{0}
{}

int Terrain::hauteur()const{
    return d_hauteur;
}
int Terrain::largeur()const{
    return d_largeur;
}

void Terrain::chargerTerrainDepuis(std::string chemin){

    std::ifstream fichierterrain(chemin);
    
    if (!fichierterrain){
        std::cerr<<"erreur de lecture"<<std::endl;
        return;
    }

    d_grille.clear();
    std::string ligne;
    while(std::getline(fichierterrain,ligne)){
        d_grille.push_back(std::vector<char>(ligne.begin(),ligne.end()));
    }
    d_hauteur=d_grille.size();
    d_largeur=d_grille[0].size();
}

void Terrain::sauverTerrainSur(std::string chemin)const{
    std::ofstream fichierterrain(chemin);
    
    if (!fichierterrain){
        std::cerr<<"erreur de lecture"<<std::endl;
        return;
    }
    for(auto& ligne:d_grille){
        for (char colonne:ligne){
            fichierterrain<<colonne;  
        }
        fichierterrain<<"\n";
        
    }        

}

void Terrain::afficherTerrain()const{
    for(auto& ligne:d_grille){
        for (auto& colonne:ligne){
            std::cout<<colonne<<' ';
        }
        std::cout<<std::endl;
    }
}


void Terrain::donnerElementGrille(int x , int y, char ch){
    d_grille[x][y]=ch;
}

char Terrain::afficherElementGrille(int x, int y){
    return d_grille[x][y];
}

bool Terrain::Obstacle(int x,int y){
    if (d_grille[x][y] == 'X' ){
        return true;
    }else{
        return false;
    }
}



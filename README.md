MEMBRES DU GROUPE

SCHELLENBAUM Mathieu - chef de projet - L3 Informatique

FANGER Cantin - développeur - L3 Informatique

ZEROUAL Samy - développeur - L3 Informatique

BENTRANTI Kenza - développeuse - L3 Informatique

BUTS ET OBJECTIFS DU PROJET

Le projet porte sur la gestion des déplacements d'un robot dans un labyrinthe et de valider le tout sous la forme de test.
Voici les principaux objectifs et fonctionnalités à mettre en œuvre :

1.Représentation et sauvegarde du terrain :

Le terrain est un tableau contenant des cases vides, des murs, une case départ et une case arrivée.
Le terrain doit pouvoir être sauvegardé et chargé depuis un fichier.

2.Déplacements et suivi du robot :

Le robot se déplace sur le terrain en détectant les obstacles devant lui, à gauche et à droite.
Il peut avancer d'une case ou pivoter de 90° (gauche ou droite).
Chaque déplacement doit être notifié aux observateurs via un modèle de conception de type observateur, incluant les coordonnées et la direction du robot.

3.Algorithmes de sortie de labyrinthe :

Main droite : Le robot suit un mur à droite (ou tout droit si aucun mur n'est présent au départ).

Algorithme de Pledge : Le robot avance tout droit, contourne les murs en comptant les changements de direction, et reprend son chemin quand le compteur revient à zéro.

4.Programme interactif en mode texte :

L'utilisateur peut charger un labyrinthe depuis un fichier, choisir un algorithme, suivre les déplacements du robot, et visualiser le nombre de cases parcourues.
Le programme doit proposer plusieurs niveaux d'affichage textuel (simple ou amélioré avec des caractères ASCII ou Unicode).

5.Tests unitaires avec DOCTEST :

Écrire des tests pour valider les différentes fonctionnalités du programme, notamment :

- La création et manipulation du labyrinthe.
  
- Les déplacements et comportements du robot.
  
- La correcte exécution des algorithmes de sortie.

  
Ce projet demande enfin une bonne structuration du code pour garantir la qualité, la clarté et l'évolutivité du programme.

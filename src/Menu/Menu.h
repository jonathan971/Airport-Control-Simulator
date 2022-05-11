#ifndef CONTROLEAERIEN_GROUPE_1_B_MENU_H
#define CONTROLEAERIEN_GROUPE_1_B_MENU_H

#include <iostream>
#include "../Plane/Plane.h"
#include "../Airport_network/Aiport_network.h"
#include "../Flight/Flight.h"
#include "../Airport/Airport.h"
#include "../Map/Map.h"



#define LARGEUR_FENETRE 1300
#define HAUTEUR_FENETRE 700
class Plane;
class Aiport_network;

void Game_Menu(unsigned int &choix);
void airplane_information(unsigned int &choix, Plane &p);
void airport_information(unsigned int &choix, Aiport_network &a);

#endif //CONTROLEAERIEN_GROUPE_1_B_MENU_H

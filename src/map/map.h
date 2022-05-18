//
// Created by mathi on 08/05/2022.
//

#ifndef CONTROLEAERIEN_GROUPE_1_B_MAP_H
#define CONTROLEAERIEN_GROUPE_1_B_MAP_H

#include "../Case/Case.h"
#include "../Airport_network/Aiport_network.h"
#include "../Plane/Plane.h"

#define COLUMNS 88
#define ROWS 48
#define SIZE 48*88

class Airplane;
class Case;
class Aiport_network;

class Map {
private :

    //Case **my_map;
    std::vector<std::vector<Case>> my_map;

public:
    Map();

    void modelize_map(Aiport_network &a);
    std::vector<Case*> Astar_turbulence (Airplane* plane, Case* arrival);


};

float calcul_distance(float x, float y,float x2, float y2);





#endif //CONTROLEAERIEN_GROUPE_1_B_MAP_H

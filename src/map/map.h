//
// Created by mathi on 08/05/2022.
//

#ifndef CONTROLEAERIEN_GROUPE_1_B_MAP_H
#define CONTROLEAERIEN_GROUPE_1_B_MAP_H

#include "../Case/Case.h"
#include "../Menu/Menu.h"
#include "../Plane/Plane.h"
class Airplane;
class Case;

class map {
private :
    float m_x, m_y;
    /*enum m_State{
        Map_case_open = 0,
        Map_case_close = 1,
        Map_turbulence = 2,
    };*/
    Case** my_map;

public:
    map(Case** board);
    void modelize_map();
    std::vector<Case*> Astar_turbulence (Airplane* plane, Case* arrival);
};

float calcul_distance(float x, float y,float x2, float y2);





#endif //CONTROLEAERIEN_GROUPE_1_B_MAP_H

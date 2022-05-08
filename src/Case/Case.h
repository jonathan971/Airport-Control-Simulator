//
// Created by mathi on 08/05/2022.
//

#ifndef CONTROLEAERIEN_GROUPE_1_B_CASE_H
#define CONTROLEAERIEN_GROUPE_1_B_CASE_H

#include <iostream>
#include "../Menu/Menu.h"


class Case {
private :
    float m_x, m_y ;
    int m_state,  m_id;
    std::vector<std::pair<Case *const, float>> m_successeurs;

    //std::pair<int, int> m_pos;

public :
    Case();
    void set_X(float x);
    void set_Y(float y);
    void set_state(int state);
    void set_id(int id);
    int get_state();
    float get_X();
    float get_Y();
    int get_id();
    void addSuccesseur(Case *successeur, float poids);
    const std::vector<std::pair<Case *const, float>> &getSuccesseurs() const;


};


#endif //CONTROLEAERIEN_GROUPE_1_B_CASE_H

//
// Created by mathi on 08/05/2022.
//

#ifndef CONTROLEAERIEN_GROUPE_1_B_CASE_H
#define CONTROLEAERIEN_GROUPE_1_B_CASE_H

#include <iostream>
//#include <SFML/Graphics.hpp>
#include <vector>



class Case {
private :
    int m_state,  m_id;
    float m_x, m_y;
    std::vector<std::pair<Case *const, float>> m_successeurs;

    //std::pair<float, float> m_pos;//x,y

public :
    Case();

    void set_X(float x);

    void set_Y(float y);

    void set_state(int state);

    void set_id(int id);

    int get_state() const;

    float get_X() const;

    float get_Y() const;

    int get_id() const;

    void addSuccesseur(Case *successeur, float poids);

    const std::vector<std::pair<Case *const, float>> &getSuccesseurs() const;

    void afficher() const;

};


#endif //CONTROLEAERIEN_GROUPE_1_B_CASE_H

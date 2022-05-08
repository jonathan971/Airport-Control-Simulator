//
// Created by mathi on 08/05/2022.
//

#include "Case.h"

Case::Case() : m_state{0} {

}

void Case::set_X(float x) {
    m_x = x;
}

void Case::set_Y(float y) {
    m_y = y;
}

void Case::set_state(int state) {

    switch (state) {
        case 1 :
            m_state = 1;//free
            // state = 0;
            break;
        case 2:
            m_state=2;//aiport
            break;
        case 3:
            m_state=3;//obstacle
            // state = 0;
            break;
        default:
            break;
    }

}

int Case::get_state() {
    return m_state;
}

void Case::set_id(int id) {

    m_id = id;

}

float Case::get_X() {
    return m_x;
}

float Case::get_Y() {
    return m_y;
}

int Case::get_id() {
    return m_id;
}

const std::vector<std::pair<Case *const, float>> &Case::getSuccesseurs() const {
    return m_successeurs;
}

void Case::addSuccesseur(Case *successeur, float poids) {
        m_successeurs.emplace_back(successeur,poids);
}






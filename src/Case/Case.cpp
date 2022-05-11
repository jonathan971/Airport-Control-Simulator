//
// Created by mathi on 08/05/2022.
//

#include "Case.h"

Case::Case()  {
    //m_y = 0.0f;
   // m_pos.first = 0.0f;
    //m_pos.second = 0.0f;
}

void Case::set_id(int id) {
    m_id = id;
}

void Case::set_X(float x) {
    //m_pos.first = x;
    m_x = x;
}

/*void Case::set_Y(float y) {
    //m_pos.second = y;
    m_y = y;
}*/

void Case::set_state(int state) {

    m_state = state;
    //description state ; 1->...., 2->Airport, 3->turbulence,

}

int Case::get_state() const {
    return m_state;
}

float Case::get_X() const {
    //return m_pos.first;
    return m_x;
}

float Case::get_Y() const {

   // return m_pos.second;
   return m_y;
}

int Case::get_id() const {
    return m_id;
}

const std::vector<std::pair<Case *const, float>> &Case::getSuccesseurs() const {
    return m_successeurs;
}

void Case::addSuccesseur(Case *successeur, float poids) {
        m_successeurs.emplace_back(successeur,poids);
}

void Case::afficher() const {
    std::cout << "   Case " << m_id <<"  "<< m_state << " : " << std::endl;
    for (auto addrSommet : m_successeurs) {
        std::cout << "      " << m_id << "---" << "(" << addrSommet.second << ")" << "--->" << addrSommet.first->get_id()
                  << std::endl;
    }
}






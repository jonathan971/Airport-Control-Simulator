//
// Created by mathi on 08/05/2022.
//

#include "Case.h"

Case::Case( int id, float x) : m_state{0}, m_id{id} {
    m_pos.first = x;
}


void Case::set_id(int id) {
    m_id = id;
}

void Case::set_X(float x) {
    m_pos.first = x;

}

void Case::set_Y(float y) {
    m_pos.second = y;

}

void Case::set_state(int state) {

    m_state = state;
    //description state ; 0->nothing, 2->Airport, 3->turbulence, 4-> OPEN LIST, 5-> CLOSED LIST

}

int Case::get_state() const {
    return m_state;
}

float Case::get_X() const {
    return m_pos.first;
    //return x;
}

float Case::get_Y() const {

    return m_pos.second;
  // return y;
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

Case::~Case() {

}






#include "Connexion.h"

Connexion::Connexion(Airport *premier, Airport *deuxieme, int poids) : m_premier(premier), m_deuxieme(deuxieme),
                                                         m_poids(poids) {}

Airport *Connexion::getPremier() const {
    return m_premier;
}

Airport *Connexion::getDeuxieme() const {
    return m_deuxieme;
}

void Connexion::setPremier(Airport *premier) {
    m_premier = premier;
}

void Connexion::setDeuxieme(Airport *deuxieme) {
    m_deuxieme = deuxieme;
}

int Connexion::getPoids() const {
    return m_poids;
}

void Connexion::setPoids(int poids) {
    m_poids = poids;
}

void Connexion::afficher() {
    std::cout << m_premier->get_AirportName() << " -- (" << m_poids << ") -- " << m_deuxieme->get_AirportName();
}
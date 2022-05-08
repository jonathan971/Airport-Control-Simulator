#ifndef CONTROLEAERIEN_GROUPE_1_B_CONNEXION_H
#define CONTROLEAERIEN_GROUPE_1_B_CONNEXION_H
#include "../Airport/Airport.h"
class Airport;

class Connexion {
private:
    Airport* m_premier;
    Airport* m_deuxieme;
    int m_poids;

public:
    Connexion(Airport *premier, Airport *deuxieme, int poids);

    Airport *getDeuxieme() const;

    Airport *getPremier() const;

    void setPremier(Airport *premier);

    void setDeuxieme(Airport *deuxieme);

    int getPoids() const;

    void setPoids(int poids);

    void afficher();

};


#endif //CONTROLEAERIEN_GROUPE_1_B_CONNEXION_H

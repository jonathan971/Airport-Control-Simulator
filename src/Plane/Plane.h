#ifndef CONTROLEAERIEN_GROUPE_1_B_PLANE_H
#define CONTROLEAERIEN_GROUPE_1_B_PLANE_H
#include "../Plane/Airplane.h"
#include <fstream>
#include <queue>
#include <sstream>
#define MAX_PLANE 10
class Airplane;

class Plane {
private:
    std::vector<Airplane*> m_airplane;
public:
    Plane(std::string FichierPlane);

    ~Plane();

    std::vector<Airplane*> getListPlane() const;

    void afficher() const;

    void supElement_ListPlane(int b);

    void addElement_ListPlane(Airplane *b);
};


#endif //CONTROLEAERIEN_GROUPE_1_B_PLANE_H

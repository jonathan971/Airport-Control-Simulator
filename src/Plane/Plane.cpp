#include "Plane.h"

Plane::Plane(std::string FichierPlane) {

    int num(0);
    bool ok;
    std::ifstream ifs{FichierPlane};
    if (!ifs) {
        throw std::runtime_error("Impossible d'ouvrir " + FichierPlane);
    }
    std::string ligne;
    while (std::getline(ifs, ligne)) {
        int number = rand() % MAX_PLANE + 1;
        std::stringstream ss;
        size_t posit = ligne.find(" ");
        std::string nmodel = ligne.substr(0, posit);
        ss << ligne.substr(posit);
        std::string ntype;
        bool nstate;
        double ncomsuption, nspeed, nlanding_speed, ntakeoff_speed, nfuel_capacity;
        ss >> ntype >> nstate >> ncomsuption >> nspeed >> nlanding_speed >> ntakeoff_speed >> nfuel_capacity;
        for (int i = 0; i < number; ++i) {
            ok=false;
            do {
                num = rand() % 9999 + 1000;
                    if (i!=0) {
                        for (int j(0); j < i; j++) {
                            if (num == m_airplane[j]->get_id()) {
                                ok = false;
                            } else if (num != m_airplane[j]->get_id() && (num<10000 && num>999)) {
                                ok = true;
                                j=i;
                            }
                        }
                    }
                    else if(num < 10000 && num > 999) {
                        ok = true;
                    }
            } while (!ok);
            sf::Texture *ATR;
            sf::Texture *Boeing;
            sf::Texture *Airbus;

            ATR=new sf::Texture;
            Boeing=new sf::Texture;
            Airbus=new sf::Texture;

            ATR->loadFromFile("Graphic_Content/Planes/ATR.png");
            Boeing->loadFromFile("Graphic_Content/Planes/Boeing.png");
            Airbus->loadFromFile("Graphic_Content/Planes/Airbus.png");

            if (nmodel == "ATR72-600") {
                sf::Sprite Sprite_ATR(*ATR);
                m_airplane.push_back(
                        new Airplane(nmodel, num, ntype, nstate, ncomsuption, nspeed, nlanding_speed, ntakeoff_speed,
                                     nfuel_capacity,Sprite_ATR));
            } else if (nmodel == "BOEING-777") {
                sf::Sprite Sprite_Boeing(*Boeing);
                m_airplane.push_back(
                        new Airplane(nmodel, num, ntype, nstate, ncomsuption, nspeed, nlanding_speed, ntakeoff_speed,
                                     nfuel_capacity,Sprite_Boeing));
            } else if (nmodel == "AIRBUS-A380") {
                sf::Sprite Sprite_Airbus(*Airbus);
                m_airplane.push_back(
                        new Airplane(nmodel, num, ntype, nstate, ncomsuption, nspeed, nlanding_speed, ntakeoff_speed,
                                     nfuel_capacity,Sprite_Airbus));
            }
        }
    }
}

Plane::~Plane() {
    for (auto addrPlane: m_airplane) {
        delete addrPlane;
    }
}

void Plane::afficher() const {
    for (int i = 0; i < 20; ++i) {
        std::cout << "*";
    }
    std::cout << " AIRPLANE INFORMATION ";
    for (int i = 0; i < 25; ++i) {
        std::cout << "*";
    }
    std::cout << "\n";
    for (auto count_airplaine: m_airplane) {
        count_airplaine->afficher();
    }
    for (int j = 0; j < 67; ++j) {
        std::cout << "*";
    }
    std::cout << "\n";
}

std::vector<Airplane *> Plane::getListPlane() const {
    return m_airplane;
}

void Plane::supElement_ListPlane(int b){
    m_airplane.erase(m_airplane.begin()+b);
}

void Plane::addElement_ListPlane(Airplane *b){
    m_airplane.push_back(b);
}



















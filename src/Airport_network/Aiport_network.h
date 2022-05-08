#ifndef CONTROLEAERIEN_GROUPE_1_B_AIPORT_NETWORK_H
#define CONTROLEAERIEN_GROUPE_1_B_AIPORT_NETWORK_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "../Airport/Airport.h"
#include "../Airport_Connexion/Connexion.h"
#include "../Flight/Flight.h"

class Connexion;
class Airport;
class Flight;
class Plane;

class Aiport_network {
private:
    std::vector<Airport*> m_airport;
    std::vector<Connexion*> m_connect;
public:
    Aiport_network(std::string FichieraiportNetwork);

    ~Aiport_network();

    void afficher() const;

    std::vector<Airport*> getListAirport() const;

    void show_network_airport_line_on_screen(sf::Event event, sf::RenderWindow &window, sf::Sprite &Sprite, sf::Font &font) ;

    void draw_line(sf::RenderWindow &window, const double &airport1_x_center, const double &airport1_y_center,
                   const double &airport2_x_center, const double &airport2_y_center, sf::Font &font, int i);

    void addVol(int &num1, int &num2, int &poids);

    void init_flight(std::vector<Flight *> &ALl_flight, size_t i, sf::Vector2f &(Airport1),
                     sf::Vector2f &(Airport2), std::vector<std::vector<int>> &flight_plan, int &j,
                     bool &ok);

    void Plane_Movement(sf::RenderWindow &window, sf::Sprite &Sprite, bool &enter_manual, std::vector<Flight *> &ALl_flight, Plane p, Aiport_network a);

};

sf::Vector2f (Interpolate(const sf::Vector2f (&pointA), const sf::Vector2f (&pointB), float factor));

double angle(float airport1X, float airport1Y, float airport2X, float airport2Y);

#endif //CONTROLEAERIEN_GROUPE_1_B_AIPORT_NETWORK_H

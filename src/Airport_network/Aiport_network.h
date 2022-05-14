#ifndef CONTROLEAERIEN_GROUPE_1_B_AIPORT_NETWORK_H
#define CONTROLEAERIEN_GROUPE_1_B_AIPORT_NETWORK_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "../Airport/Airport.h"
#include "../Airport_Connexion/Connexion.h"
#include "../Flight/Flight.h"
#define LEFT_X 200
#define RIGHT_X 1080
#define SIZE 26
#define MAX_OLD_F 5
#define MAX_WAITING_TIME_TO_CREATE 20
#define TIME_MAX_TO_CREATE_PERTUBATION 60

class Connexion;

class Airport;

class Flight;

class Plane;

class Aiport_network {
private:
    std::vector<Airport *> m_airport;
    std::vector<Connexion *> m_connect;
public:
    Aiport_network(std::string FichieraiportNetwork);

    ~Aiport_network();

    void afficher() const;

    std::vector<Airport *> getListAirport() const;

    void
    show_network_airport_line_on_screen(sf::Event event, sf::RenderWindow &window, sf::Sprite &Sprite, sf::Font &font);

    void draw_line(sf::RenderWindow &window, const double &airport1_x_center, const double &airport1_y_center,
                   const double &airport2_x_center, const double &airport2_y_center, sf::Font &font, int i);

    void addVol(int &num1, int &num2, int &poids);

    void init_flight(std::vector<Flight *> &ALl_flight, size_t i, sf::Vector2f &(Airport1),
                     sf::Vector2f &(Airport2), std::vector<std::vector<int>> &flight_plan, int &j,
                     bool &ok);

    void Plane_Movement(sf::RenderWindow &window, sf::Sprite &Sprite, bool &enter_manual, std::vector<Flight *> &ALl_flight,
                   Plane p, Aiport_network a, sf::Font &font2, sf::Font &font1);

    void manage_pertubation(sf::RenderWindow &window, int &num, int &number, int &number_of_pertubation,
                            std::vector<int> &num_connect, std::vector<sf::Sprite> &animSprites, sf::Texture &animTexture,
                            std::vector<std::vector<sf::Sprite>> &vec_Sprites);

};

sf::Vector2f (Interpolate(const sf::Vector2f (&pointA), const sf::Vector2f (&pointB), float factor));

double angle(float airport1X, float airport1Y, float airport2X, float airport2Y);

void init_text(sf::Font &font1, sf::Font &font2, sf::Text &text1, sf::Text &text2, sf::Text &text3, sf::Text &text4, sf::Text &text5,
               sf::Text &text6, sf::Text &text7, sf::Text &text8, sf::Text &text9, sf::Text &text10);

void draw_text(sf::RenderWindow &window, sf::Text &text1, sf::Text &text2, sf::Text &text3, sf::Text &text4, sf::Text &text5,
          sf::Text &text6, sf::Text &text7, sf::Text &text8, sf::Text &text9);

void alea_intemp(sf::RenderWindow &window, const double &airport1_x_center, const double &airport1_y_center,
                 const double &airport2_x_center, const double &airport2_y_center, int number,  std::vector<sf::Sprite> &animSprites, sf::Texture &animTexture);
#endif //CONTROLEAERIEN_GROUPE_1_B_AIPORT_NETWORK_H

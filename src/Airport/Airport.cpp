#include "Airport.h"


Airport::Airport(int &id, std::string &AirportName, int &Xmin, int &Xmax, int &Xcentre, int &Ymin, int &Ymax,
                 int &Ycentre, int &NbrRunways, int &Ground_seats, double &Ground_waiting_time,
                 double &acces_runway_time, double &anticollision_time, double &landing_time, double &takeoff_time,
                 double &in_flight_loop) :
        m_id{id}, m_AirportName{AirportName}, m_Xmin{Xmin}, m_Xmax{Xmax}, m_Xcentre{Xcentre}, m_Ymin{Ymin},
        m_Ymax{Ymax}, m_Ycentre{Ycentre}, m_NbrRunways{NbrRunways}, m_Ground_seats{Ground_seats},
        m_Ground_waiting_time{Ground_waiting_time}, m_acces_runway_time{acces_runway_time},
        m_anticollision_time{anticollision_time}, m_landing_time{landing_time},
        m_takeoff_time{takeoff_time}, m_in_flight_loop{in_flight_loop} {
    std::vector<bool> management_NbrRunways(m_NbrRunways, false);
    std::vector<bool> management_Ground_seats(m_Ground_seats, true);// ça c est true et pas false
    m_management_nbrRunways = management_NbrRunways;
    m_management_Ground_seats = management_Ground_seats;

    m_management_nbrRunways[2] = true;
    m_management_nbrRunways[3] = true;

    m_management_Ground_seats[2] = false;
    m_management_Ground_seats[3] = false;


}

void Airport::addSuccesseur(Airport *successeur, int poids) {
    m_successeurs.emplace_back(successeur, poids);
}

void Airport::afficher() const {
    std::cout << "                   Id : " << m_id << std::endl
              << "                   Name : " << m_AirportName << std::endl
              << "                   Number of Runways : " << m_NbrRunways << std::endl
              << "                   Number of Ground Seats : " << m_Ground_seats << std::endl
              << "                   Ground Waiting Time : " << m_Ground_waiting_time << std::endl
              << "                   Acces Runway Time : " << m_acces_runway_time << std::endl
              << "                   Anticollision Time : " << m_anticollision_time << std::endl
              << "                   Landing Time : " << m_landing_time << std::endl
              << "                   Takeoff Time : " << m_takeoff_time << std::endl
              << "                   In Flight Loop Time : " << m_in_flight_loop << "\n" << std::endl;
}

int Airport::getXmin() const {
    return m_Xmin;
}

int Airport::getXmax() const {
    return m_Xmax;
}

int Airport::getXcentre() const {
    return m_Xcentre;
}

int Airport::getYmin() const {
    return m_Ymin;
}

int Airport::getYmax() const {
    return m_Ymax;
}

int Airport::getYcentre() const {
    return m_Ycentre;
}

std::string Airport::get_AirportName() const {
    return m_AirportName;
}

int Airport::getId() const {
    return m_id;
}

const std::vector<std::pair<Airport *const, int>> &Airport::getSuccesseurs() const {
    return m_successeurs;
}

void Airport::management_Landing(Airplane *airplane_which_landing) {
    for (size_t i(0); i < m_management_nbrRunways.size(); ++i) {
        if (!m_management_nbrRunways[i] && m_acces_runway_time < m_anticollision_time) {
            m_management_nbrRunways[i] = true;

            m_management_Ground_seats[i] = false;
            airplane_which_landing->put_state(true);
        } else {
            m_waiting_airplane.push_back(airplane_which_landing);
            //ajouter à la boucle d'attente décollage
        }
    }
}

void Airport::management_takeoff(Airplane *airplane_which_takeoff) {

    for (size_t i(0); i < m_management_nbrRunways.size(); ++i) {
        if (!m_management_nbrRunways[i] &&
            /*!m_management_Ground_seats[i]*/  m_acces_runway_time < m_anticollision_time) {
            m_management_nbrRunways[i] = true; //pendant 2ut
            airplane_which_takeoff->takeoff_or_not(true);

            m_management_Ground_seats[i] = true;
            airplane_which_takeoff->put_state(
                    false);// plus en vol mais ce sera apres 2ut faudra reflechir a ca pareil pr ground seats pariel pour decollage
        } else {
            m_waiting_airplane.push_back(airplane_which_takeoff);
        }
    }

}

int Airport::getGround_seats_free() const{
    int compt(0);
    for(auto && m_management_Ground_seat : m_management_Ground_seats){
        if(m_management_Ground_seat){
            compt++;
        }
    }
    return compt;
}

int Airport::getGround_seats_occuped() const{
    int compt(0);
    for(auto && m_management_Ground_seat : m_management_Ground_seats){
        if(!m_management_Ground_seat){
            compt++;
        }
    }
    return compt;
}

void Airport::loop_management() {
    //TRIE DES AVIONS EN ATTENTES
    std::sort(m_waiting_airplane.begin(), m_waiting_airplane.end(), [](Airplane *s1, Airplane *s2) {
        return s1->get_fuel_capacity() > s2->get_fuel_capacity();
    });

    Airplane *a_transition;


    do {
        //priorité attérissage
        for (size_t i(0); i < m_waiting_airplane.size(); ++i) {
            if (m_waiting_airplane[i]->get_if_takeoff()) {
                management_takeoff(m_waiting_airplane[i]);
                m_waiting_airplane[(int) m_waiting_airplane.size()] = a_transition;
                m_waiting_airplane[(int) m_waiting_airplane.size()] = m_waiting_airplane[i];
                m_waiting_airplane[i] = a_transition;
                m_waiting_airplane.pop_back();
            }
        }
        //jsp si on peut simplifier ça en mode tous faire dans une boucle for
        for (size_t i(0); i < m_waiting_airplane.size(); ++i) {
            if (!m_waiting_airplane[i]->get_if_takeoff()) {
                management_Landing(m_waiting_airplane[i]);
                m_waiting_airplane[(int) m_waiting_airplane.size()] = a_transition;
                m_waiting_airplane[(int) m_waiting_airplane.size()] = m_waiting_airplane[i];
                m_waiting_airplane[i] = a_transition;
                m_waiting_airplane.pop_back();
            }
        }
    } while (!m_waiting_airplane.empty());
}

bool Airport::condition_landing() {
    int landing_compteur(0);
    bool landing_viability(false);

    for (size_t i(0); i < m_management_nbrRunways.size(); ++i) {
        if (!m_management_nbrRunways[i] && m_acces_runway_time < m_anticollision_time) {
            landing_compteur++;
        }
    }
    if (landing_compteur > 0) {
        landing_viability = true;
    } else { landing_viability = false; }

    return landing_viability;
}

bool Airport::condition_takeoff() {
    int runways_available(0);
    int groundseats_available(0);
    bool takeoff_viability(false);

    for (size_t i(0); i < m_management_nbrRunways.size(); ++i) {
        if (m_acces_runway_time < m_anticollision_time && !m_management_nbrRunways[i]) {
            runways_available++;
        }
    }

    for (size_t i(0); i < m_management_Ground_seats.size(); ++i) {
        if (m_acces_runway_time < m_anticollision_time && !m_management_Ground_seats[i]) {
            groundseats_available++;
        } else {}
    }


    if (runways_available > 0 && groundseats_available > 0) {
        takeoff_viability = true;
    } else {
        takeoff_viability = false;
    }

    return takeoff_viability;

}


void show_airport_on_screen(sf::Event event, sf::RenderWindow &window, sf::Sprite &Sprite, Aiport_network &a, sf::Font &font,
                            sf::Font &font2, std::vector<Flight *> &ALl_flight, bool &enter_manual, Plane &p) {
    bool ok(false);

    sf::Texture Sydney;
    sf::Texture Pekin;
    sf::Texture Moscou;
    sf::Texture Dubai;
    sf::Texture Londres;
    sf::Texture Pretoria;
    sf::Texture Algeria;
    sf::Texture Los_Angeles;
    sf::Texture New_York;
    sf::Texture Rio_De_Janeiro;
    sf::Texture Martinique;

    sf::Texture Sydney_airport;
    sf::Texture Pekin_airport;
    sf::Texture Moscou_airport;
    sf::Texture Dubai_airport;
    sf::Texture Londres_airport;
    sf::Texture Pretoria_airport;
    sf::Texture Algeria_airport;
    sf::Texture Los_Angeles_airport;
    sf::Texture New_York_airport;
    sf::Texture Rio_De_Janeiro_airport;
    sf::Texture Martinique_airport;


    Sydney.loadFromFile("../Graphic_Content/Map/Sydney.png");
    Pekin.loadFromFile("../Graphic_Content/Map/Sydney.png");
    Moscou.loadFromFile("../Graphic_Content/Map/Sydney.png");
    Dubai.loadFromFile("../Graphic_Content/Map/Sydney.png");
    Londres.loadFromFile("../Graphic_Content/Map/Sydney.png");
    Pretoria.loadFromFile("../Graphic_Content/Map/Sydney.png");
    Algeria.loadFromFile("../Graphic_Content/Map/Sydney.png");
    Los_Angeles.loadFromFile("../Graphic_Content/Map/Sydney.png");
    New_York.loadFromFile("../Graphic_Content/Map/Sydney.png");
    Rio_De_Janeiro.loadFromFile("../Graphic_Content/Map/Sydney.png");
    Martinique.loadFromFile("../Graphic_Content/Map/Sydney.png");

    Sydney_airport.loadFromFile("../Graphic_Content/Map/Info/Sydney_info_airport.png");
    Pekin_airport.loadFromFile("../Graphic_Content/Map/Info/Pekin_info_airport.png");
    Moscou_airport.loadFromFile("../Graphic_Content/Map/Info/Moscou_info_airport.png");
    Dubai_airport.loadFromFile("../Graphic_Content/Map/Info/Dubai_info_airport.png");
    Londres_airport.loadFromFile("../Graphic_Content/Map/Info/Londres_info_airport.png");
    Pretoria_airport.loadFromFile("../Graphic_Content/Map/Info/Pretoria_info_airport.png");
    Algeria_airport.loadFromFile("../Graphic_Content/Map/Info/Algerie_info_airport.png");
    Los_Angeles_airport.loadFromFile("../Graphic_Content/Map/Info/LosAngeles_info_airport.png");
    New_York_airport.loadFromFile("../Graphic_Content/Map/Info/NewYork_info_airport.png");
    Rio_De_Janeiro_airport.loadFromFile("../Graphic_Content/Map/Info/RiodeJaneiro_info_airport.png");
    Martinique_airport.loadFromFile("../Graphic_Content/Map/Info/Martinique_info_airport.png");

    sf::Sprite Sprite_Sydney(Sydney);
    sf::Sprite Sprite_Pekin(Pekin);
    sf::Sprite Sprite_Moscou(Moscou);
    sf::Sprite Sprite_Dubai(Dubai);
    sf::Sprite Sprite_Londres(Londres);
    sf::Sprite Sprite_Pretoria(Pretoria);
    sf::Sprite Sprite_Algeria(Algeria);
    sf::Sprite Sprite_Los_Angeles(Los_Angeles);
    sf::Sprite Sprite_New_York(New_York);
    sf::Sprite Sprite_Rio_De_Janeiro(Rio_De_Janeiro);
    sf::Sprite Sprite_Martinique(Martinique);

    sf::Sprite Sprite_Sydney_info_airport(Sydney_airport);
    sf::Sprite Sprite_Pekin_info_airport(Pekin_airport);
    sf::Sprite Sprite_Moscou_info_airport(Moscou_airport);
    sf::Sprite Sprite_Dubai_info_airport(Dubai_airport);
    sf::Sprite Sprite_Londres_info_airport(Londres_airport);
    sf::Sprite Sprite_Pretoria_info_airport(Pretoria_airport);
    sf::Sprite Sprite_Algeria_info_airport(Algeria_airport);
    sf::Sprite Sprite_Los_Angeles_info_airport(Los_Angeles_airport);
    sf::Sprite Sprite_New_York_info_airport(New_York_airport);
    sf::Sprite Sprite_Rio_De_Janeiro_info_airport(Rio_De_Janeiro_airport);
    sf::Sprite Sprite_Martinique_info_airport(Martinique_airport);

    Sprite_Sydney.setPosition(sf::Vector2f(POS_X, POS_Y));
    Sprite_Pekin.setPosition(sf::Vector2f(POS_X, POS_Y));
    Sprite_Moscou.setPosition(sf::Vector2f(POS_X, POS_Y));
    Sprite_Dubai.setPosition(sf::Vector2f(POS_X, POS_Y));
    Sprite_Londres.setPosition(sf::Vector2f(POS_X, POS_Y));
    Sprite_Pretoria.setPosition(sf::Vector2f(POS_X, POS_Y));
    Sprite_Algeria.setPosition(sf::Vector2f(POS_X, POS_Y));
    Sprite_Los_Angeles.setPosition(sf::Vector2f(POS_X, POS_Y));
    Sprite_New_York.setPosition(sf::Vector2f(POS_X, POS_Y));
    Sprite_Rio_De_Janeiro.setPosition(sf::Vector2f(POS_X, POS_Y));
    Sprite_Martinique.setPosition(sf::Vector2f(POS_X, POS_Y));

    Sprite_Sydney_info_airport.setPosition(sf::Vector2f(POS_INFO_X, 0));
    Sprite_Pekin_info_airport.setPosition(sf::Vector2f(POS_INFO_X, 0));
    Sprite_Moscou_info_airport.setPosition(sf::Vector2f(POS_INFO_X, 0));
    Sprite_Dubai_info_airport.setPosition(sf::Vector2f(POS_INFO_X, 0));
    Sprite_Londres_info_airport.setPosition(sf::Vector2f(POS_INFO_X, 0));
    Sprite_Pretoria_info_airport.setPosition(sf::Vector2f(POS_INFO_X, 0));
    Sprite_Algeria_info_airport.setPosition(sf::Vector2f(POS_INFO_X, 0));
    Sprite_Los_Angeles_info_airport.setPosition(sf::Vector2f(POS_INFO_X, 0));
    Sprite_New_York_info_airport.setPosition(sf::Vector2f(POS_INFO_X, 0));
    Sprite_Rio_De_Janeiro_info_airport.setPosition(sf::Vector2f(POS_INFO_X, 0));
    Sprite_Martinique_info_airport.setPosition(sf::Vector2f(POS_INFO_X, 0));

    sf::Text text;
    sf::Text text2;
    text.setFont(font2);
    text.setCharacterSize(22);
    text.setColor(sf::Color::Yellow);
    text.setPosition(850, 12);
    std::string myString;

    text2.setFont(font2);
    text2.setCharacterSize(22);
    text2.setColor(sf::Color::White);
    text2.setPosition(850, 33);
    std::string myString2;

    window.clear(sf::Color::Transparent);
    window.draw(Sprite);
    window.display();

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::I) {
                    window.clear();
                    window.draw(Sprite);
                    a.show_network_airport_line_on_screen(event, window, Sprite, font);
                    ok=true;
                }
                if (event.key.code == sf::Keyboard::O) {
                    window.clear();
                    window.draw(Sprite);
                    ok=false;
                }
            } else {
                window.clear();
                window.draw(Sprite);
                if(ok){
                    a.show_network_airport_line_on_screen(event, window, Sprite, font);
                    //Plane_Movement(window, Sprite, enter_manual, ALl_flight,  p,  a);
                }
            }

            for (int i(0); i < a.getListAirport().size(); i++) {
                if (sf::Mouse::getPosition(window).x >= a.getListAirport()[i]->getXmin() &&
                    sf::Mouse::getPosition(window).x <= a.getListAirport()[i]->getXmax() &&
                    sf::Mouse::getPosition(window).y >= a.getListAirport()[i]->getYmin() &&
                    sf::Mouse::getPosition(window).y <= a.getListAirport()[i]->getYmax()) {

                    if (i == 0) {
                        window.draw(Sprite_Sydney);
                        window.draw(Sprite_Sydney_info_airport);
                        myString+=std::to_string(a.getListAirport()[i]->getGround_seats_occuped());
                        myString2+=std::to_string(a.getListAirport()[i]->getGround_seats_free());

                    } else if (i == 1) {
                        window.draw(Sprite_Pekin);
                        window.draw(Sprite_Pekin_info_airport);
                        myString+=std::to_string(a.getListAirport()[i]->getGround_seats_occuped());
                        myString2+=std::to_string(a.getListAirport()[i]->getGround_seats_free());
                    } else if (i == 2) {
                        window.draw(Sprite_Moscou);
                        window.draw(Sprite_Moscou_info_airport);
                        myString+=std::to_string(a.getListAirport()[i]->getGround_seats_occuped());
                        myString2+=std::to_string(a.getListAirport()[i]->getGround_seats_free());
                    } else if (i == 3) {
                        window.draw(Sprite_Dubai);
                        window.draw(Sprite_Dubai_info_airport);
                        myString+=std::to_string(a.getListAirport()[i]->getGround_seats_occuped());
                        myString2+=std::to_string(a.getListAirport()[i]->getGround_seats_free());
                    } else if (i == 4) {
                        window.draw(Sprite_Londres);
                        window.draw(Sprite_Londres_info_airport);
                        myString+=std::to_string(a.getListAirport()[i]->getGround_seats_occuped());
                        myString2+=std::to_string(a.getListAirport()[i]->getGround_seats_free());
                    } else if (i == 5) {
                        window.draw(Sprite_Pretoria);
                        window.draw(Sprite_Pretoria_info_airport);
                        myString+=std::to_string(a.getListAirport()[i]->getGround_seats_occuped());
                        myString2+=std::to_string(a.getListAirport()[i]->getGround_seats_free());
                    } else if (i == 6) {
                        window.draw(Sprite_Algeria);
                        window.draw(Sprite_Algeria_info_airport);
                        myString+=std::to_string(a.getListAirport()[i]->getGround_seats_occuped());
                        myString2+=std::to_string(a.getListAirport()[i]->getGround_seats_free());
                    } else if (i == 7) {
                        window.draw(Sprite_Los_Angeles);
                        window.draw(Sprite_Los_Angeles_info_airport);
                        myString+=std::to_string(a.getListAirport()[i]->getGround_seats_occuped());
                        myString2+=std::to_string(a.getListAirport()[i]->getGround_seats_free());
                    } else if (i == 8) {
                        window.draw(Sprite_New_York);
                        window.draw(Sprite_New_York_info_airport);
                        myString+=std::to_string(a.getListAirport()[i]->getGround_seats_occuped());
                        myString2+=std::to_string(a.getListAirport()[i]->getGround_seats_free());
                    } else if (i == 9) {
                        window.draw(Sprite_Rio_De_Janeiro);
                        window.draw(Sprite_Rio_De_Janeiro_info_airport);
                        myString+=std::to_string(a.getListAirport()[i]->getGround_seats_occuped());
                        myString2+=std::to_string(a.getListAirport()[i]->getGround_seats_free());
                    } else if (i == 10) {
                        window.draw(Sprite_Martinique);
                        window.draw(Sprite_Martinique_info_airport);
                        myString+=std::to_string(a.getListAirport()[i]->getGround_seats_occuped());
                        myString2+=std::to_string(a.getListAirport()[i]->getGround_seats_free());
                    }
                }
            }
            text.setString(myString);
            text2.setString(myString2);
            window.draw(text);
            window.draw(text2);
            window.display();
            myString.clear();
            myString2.clear();
        }
    }

}




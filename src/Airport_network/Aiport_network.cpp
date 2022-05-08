#include "Aiport_network.h"


Aiport_network::Aiport_network(std::string FichieraiportNetwork) {

    std::ifstream ifs{FichieraiportNetwork};
    if (!ifs) {
        throw std::runtime_error("Impossible d'ouvrir " + FichieraiportNetwork);
    }
    //Airport
    int nbrAirport;
    ifs >> nbrAirport;
    if (ifs.fail()) {
        throw std::runtime_error("Probleme de lecture du nombre d'aeroport.");
    }

    std::string AirportName;
    int Xmin, Xmax, Xcentre, Ymin, Ymax, Ycentre;
    int NbrRunways, Ground_seats;
    double Ground_waiting_time, acces_runway_time, anticollision_time, landing_time, takeoff_time, in_flight_loop;

    for (int i = 0; i < nbrAirport; ++i) {
        ifs >> AirportName >> Xmin >> Xmax >> Xcentre >> Ymin >> Ymax >> Ycentre >> NbrRunways >> Ground_seats
            >> Ground_waiting_time >> acces_runway_time >> anticollision_time >> landing_time >> takeoff_time
            >> in_flight_loop;
        if (ifs.fail()) {
            throw std::runtime_error("Probleme de lecture des donnees d'un aeroport.");
        }

        m_airport.push_back(
                new Airport(i, AirportName, Xmin, Xmax, Xcentre, Ymin, Ymax, Ycentre,
                            NbrRunways, Ground_seats, Ground_waiting_time, acces_runway_time,
                            anticollision_time, landing_time, takeoff_time, in_flight_loop));

    }
    int taille;
    ifs >> taille;
    if (ifs.fail()) {
        throw std::runtime_error("Probleme de lecture de la taille du graphe.");
    }

    std::string airport1, airport2;
    int poids;
    for (int i = 0; i < taille; ++i) {
        ifs >> airport1 >> airport2 >> poids;
        if (ifs.fail()) {
            throw std::runtime_error("Probleme de lecture d'un.e arc/arete.");
        }
        //addConnexion(airport1, airport2, poids);
        int num1(0), num2(0);
        for (int j(0); j < m_airport.size(); j++) {
            if (airport1 == m_airport[j]->get_AirportName()) {
                num1 = j;
            }
            if (airport2 == m_airport[j]->get_AirportName()) {
                num2 = j;
            }
        }
        m_airport[num1]->addSuccesseur(m_airport[num2], poids);
        m_airport[num2]->addSuccesseur(m_airport[num1], poids);//non orienté
        addVol(num1, num2, poids);
    }

}

void Aiport_network::addVol(int &num1, int &num2, int &poids) {
    Connexion *connect = new Connexion(m_airport[num1], m_airport[num2], poids);
    m_connect.push_back(connect);

}


void Aiport_network::afficher() const {

    for (int i = 0; i < 20; ++i) {
        std::cout << "*";
    }
    std::cout << " AIRPLANE INFORMATION ";
    for (int i = 0; i < 25; ++i) {
        std::cout << "*";
    }
    std::cout << "\n";
    for (auto addrAirport: m_airport) {
        addrAirport->afficher();
    }

    for (int j = 0; j < 67; ++j) {
        std::cout << "*";
    }
    std::cout << "\n";

    /*std::cout << std::endl << "Liste d'arcs : " << std::endl;
    for(auto addrFlight : m_flight){
        addrFlight->afficher();// classe flight
        std::cout << std::endl;
*/
    // rien vu qu'on affiche en graphique juste histoire de voir si ça lie bien le fichier txt

}

Aiport_network::~Aiport_network() {
    for (auto addrAirport_network: m_airport) {
        delete addrAirport_network;
    }
}

std::vector<Airport *> Aiport_network::getListAirport() const {
    return m_airport;
}

void Aiport_network::show_network_airport_line_on_screen(sf::Event event, sf::RenderWindow &window, sf::Sprite &Sprite,
                                                         sf::Font &font) {
    int counter(0);
    for (auto &i: m_connect) {
        draw_line(window, i->getPremier()->getXcentre(), i->getPremier()->getYcentre(),
                  i->getDeuxieme()->getXcentre(), i->getDeuxieme()->getYcentre(), font, counter);
    }
}

void
Aiport_network::draw_line(sf::RenderWindow &window, const double &airport1_x_center, const double &airport1_y_center,
                          const double &airport2_x_center, const double &airport2_y_center, sf::Font &font, int i) {

    sf::Text text;
    text.setFont(font);
    std::string poids;
    poids += std::to_string(m_connect[i]->getPoids());
    text.setString(poids);
    text.setCharacterSize(9);
    text.setColor(sf::Color::Yellow);
    sf::Vector2f mid = sf::Vector2f((float) (airport1_x_center + airport2_x_center) / 2,
                                    (float) (airport1_y_center + airport2_y_center) / 2);
    sf::Vertex line[] =
            {
                    sf::Vertex(sf::Vector2f((float) airport1_x_center, (float) airport1_y_center)),
                    sf::Vertex(sf::Vector2f((float) airport2_x_center, (float) airport2_y_center))
            };

    window.draw(line, 2, sf::Lines);
    text.setPosition(mid.x, mid.y);
    window.draw(text);
}


void Aiport_network::init_flight(std::vector<Flight *> &ALl_flight, size_t i, sf::Vector2f &(Airport1),
                                 sf::Vector2f &(Airport2), std::vector<std::vector<int>> &flight_plan, int &j,
                                 bool &ok) {
    if (ok) {
        if (i == 3) {
            std::cout << "oui\n";
        }
        flight_plan.emplace_back(std::vector<int>());
        flight_plan[i] = ALl_flight[i]->PCC();
        flight_plan[i].push_back(j);
    }

    if (j < flight_plan[i].size() - 2) {


        ALl_flight[i]->get_airplane()->set_plane_x(
                m_airport[flight_plan[i][j]]->getXcentre());
        ALl_flight[i]->get_airplane()->set_plane_y(
                m_airport[flight_plan[i][j]]->getYcentre());
        ALl_flight[i]->get_airplane()->set_Coord_plane((float) ALl_flight[i]->get_airplane()->get_plane_x(),
                                                       ALl_flight[i]->get_airplane()->get_plane_y());

        for (size_t y(0); y < ALl_flight.size(); y++) {
            std::cout << "Avion" << y << ":" << m_airport[flight_plan[y][j]]->getXcentre()
                      << ","
                      << m_airport[flight_plan[y][j]]->getYcentre() << "/"
                      << ALl_flight[y]->get_airplane()->get_plane_x() << ","
                      << ALl_flight[y]->get_airplane()->get_plane_y() << std::endl;
        }

        Airport1.x = (float) m_airport[flight_plan[i][j]]->getXcentre();
        Airport1.y = (float) m_airport[flight_plan[i][j]]->getYcentre();

        Airport2.x = (float) m_airport[flight_plan[i][j + 1]]->getXcentre();
        Airport2.y = (float) m_airport[flight_plan[i][j + 1]]->getYcentre();

    }

}

void
Aiport_network::Plane_Movement(sf::RenderWindow &window, sf::Sprite &Sprite, bool &enter_manual,
                               std::vector<Flight *> &ALl_flight,
                               Plane p, Aiport_network a) {
    window.setFramerateLimit(60);
    bool arrive(false), end(false), ok(true);
    sf::Vector2f (Airport1), (Airport2);
    std::vector<std::vector<sf::Vector2f>> (my_Airport);
    std::vector<std::vector<int>> flight_plan;
    int j(0);

    //Get Flight plan vector
    Flight m{p.getListPlane(), a.getListAirport(), enter_manual};
    ALl_flight.push_back(&m);
    init_flight(ALl_flight, 0,
                Airport1, Airport2, flight_plan, j, ok);
    ok = false;
    my_Airport.push_back(std::vector<sf::Vector2f>());

    my_Airport[0].push_back(Airport1);
    my_Airport[0].push_back(Airport2);

    bool fin(false);
    float vitesse = 0.08f;
    std::vector<float> progression;
    float time(0.0f);

    sf::Clock clock;
    sf::Clock clock2;

    progression.push_back(0.0f);
    do {

        for (size_t f(0); f < ALl_flight.size(); f++) {
            progression[f]+=clock.getElapsedTime().asSeconds() * vitesse;
            clock.restart();
            ALl_flight[f]->get_airplane()->set_plane_x(
                    Interpolate(my_Airport[f][0], my_Airport[f][1], progression[f]).x);
            ALl_flight[f]->get_airplane()->set_plane_y(
                    Interpolate(my_Airport[f][0], my_Airport[f][1], progression[f]).y);
            ALl_flight[f]->get_airplane()->set_Coord_plane(ALl_flight[f]->get_airplane()->get_plane_x(),
                                                           ALl_flight[f]->get_airplane()->get_plane_y());

            if ((ALl_flight[f]->get_airplane()->get_plane_x() ==
                 (float) my_Airport[f][1].x &&
                 ALl_flight[f]->get_airplane()->get_plane_y() ==
                 (float) my_Airport[f][1].y) || progression [f]> 1) {
                //window.clear();
                //window.draw(Sprite);
                flight_plan[f][flight_plan.size() - 1]++;
                if (flight_plan[f][flight_plan[f].size() - 1] < flight_plan[f].size() - 2) {
                    init_flight(ALl_flight, f,
                                Airport1, Airport2, flight_plan, flight_plan[f][flight_plan.size() - 1], ok);

                    std::cout << flight_plan[f][flight_plan[f].size() - 1] << ";" << flight_plan[f].size() - 2
                              << std::endl;

                    flight_plan[f][flight_plan.size() - 1]++;

                    std::cout << flight_plan[f][flight_plan.size() - 2] << std::endl;

                }
                fin = true;
                arrive = false;
                if (flight_plan[f][flight_plan[f].size() - 1] == flight_plan[f].size() - 2) {
                    std::cout << "Arivée\n";
                    arrive = true;
                    ALl_flight.erase(ALl_flight.begin() + (int) f);
                    my_Airport.erase(my_Airport.begin() + (int) f);
                    flight_plan.erase(flight_plan.begin() + (int) f);
                }
            } else {
                if (my_Airport[f][flight_plan.size() - 1].x >
                    my_Airport[f][flight_plan.size()].x) {
                    ALl_flight[f]->get_airplane()->set_Angle(
                            (float) angle(my_Airport[f][0].x, my_Airport[f][0].y, my_Airport[f][1].x,
                                          my_Airport[f][1].y) + 180.0f);
                } else {
                    ALl_flight[f]->get_airplane()->set_Angle(
                            (float) angle(my_Airport[f][0].x, my_Airport[f][0].y, my_Airport[f][1].x,
                                          my_Airport[f][1].y) + 180.0f);
                }
                window.clear();
                window.draw(Sprite);
                fin = false;
                arrive = false;
            }
            time = clock2.getElapsedTime().asSeconds();
            if (time >= 3) {
                ok = true;
                j = 0;
                auto *l = new Flight{p.getListPlane(), a.getListAirport(), enter_manual};
                ALl_flight.push_back(l);

                init_flight(ALl_flight, ALl_flight.size() - 1,
                            Airport1, Airport2, flight_plan, j, ok);
                ok = false;
                my_Airport.push_back(std::vector<sf::Vector2f>());
                my_Airport[ALl_flight.size() - 1].push_back(Airport1);
                my_Airport[ALl_flight.size() - 1].push_back(Airport2);
                progression.push_back(0.0f);
                clock2.restart();

            }
            window.clear();
            window.draw(Sprite);
            for (auto &z: ALl_flight) {
                window.draw(z->get_airplane()->get_Sprite());
            }
            window.display();
        }

    } while (!fin || !arrive);
}


sf::Vector2f (Interpolate(const sf::Vector2f (&pointA), const sf::Vector2f (&pointB), float factor)) {
    if (factor > 1.f) {
        factor = 1.f;
    } else if (factor < 0.f) {
        factor = 0.f;
    }
    return pointA + (pointB - pointA) * factor;
}

double angle(float airport1X, float airport1Y, float airport2X, float airport2Y) {

    float oposite_long = std::abs(airport2X) - std::abs(airport1X);
    float hypo = std::abs(airport1Y) - std::abs(airport2Y);

    if (airport2Y > airport1Y) {
        return (std::atan(oposite_long / hypo) * 180.0) / PI;
    } else {
        return (std::atan(oposite_long / hypo) * 180.0) / PI + 180.0;
    }
}



//VERIFICATION DE LA VIABILITE DE L'AEROPORT QUI SE TROUVE A UNE DISTANCE MINIMALE
/*   if (s == f->get_arrival()->getId()) {
       couleurs[s] = 1;
       nbMarques = int(m_airport.size());
   } else if (rapport_consommation_carburant <= distances[s]poids de l'aeroport d'id s par rapport a laeroport init ) {//gestions arrivé gesiton depart sur s
       couleurs[s] = 1;
       nbMarques++;

   } else {
       //refaire le calcul de distance mini sans s donc remettre la distance de s à l'infini pour que l'aeroport d'id s ne soit  plus prit en compte
       distances[s] = std::numeric_limits<int>::max();
   }

    rapport_consommation_carburant = f->get_airplane()->get_plane_comsuption()/double(distances[s]);

     // INITIALISATION
    int nbMarques = 0;
    std::vector<int> couleurs(m_airport.size(), 0); // tous les aéroports sont non marqués
    std::vector<int> distances(m_airport.size(), std::numeric_limits<int>::max());
    distances[f->get_departure()->getId()] = 0; // departure est à une distance de 0 de lui même.
    std::vector<int> predecesseurs(m_airport.size(), -1); // nous ne connaissons pas encore les prédécesseurs
    predecesseurs[f->get_departure()->getId()] = 0; // on pourrait laisser -1, departure n'a pas vraiment de prédécesseur car il s'agit de l'aeroport initial


   */
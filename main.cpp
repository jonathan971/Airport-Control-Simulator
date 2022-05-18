#include "src/Menu/Menu.h"
#include <thread>

int main() {

    unsigned int choix(0);
    bool fin(false), back_menu(true), end_flight(false), enter_manual(false), end_choose_manual(false), end_choice(false);
    float time(0.0f);
    sf::Font font;
    sf::Font font2;
    font.loadFromFile("Font/Pixeled.ttf");
    font2.loadFromFile("Font/calendar note tfb.ttf");
    //Initialisation Menu
    sf::Texture Menu;
    Menu.loadFromFile("Graphic_Content/Menu/cover.png");
    sf::Sprite Sprite_Menu(Menu);
    sf::Texture Rect1, Rect2;
    Rect1.loadFromFile("Graphic_Content/Menu/Rectangle.png");
    sf::Sprite Sprite_Rect1(Rect1);
    Sprite_Rect1.setPosition(20, 560);
    sf::Sprite Sprite_Rect2(Rect1);
    Sprite_Rect2.setPosition(400, 560);

    sf::Text text, text2, text3, text4;
    text.setFont(font2);
    text.setCharacterSize(46);
    text.setColor(sf::Color (178, 184, 185));
    text.setPosition(50, 572);
    text2.setFont(font2);
    text2.setCharacterSize(46);
    text2.setColor(sf::Color (178, 184, 185));
    text2.setPosition(460, 572);
    text3.setFont(font2);
    text3.setCharacterSize(28);
    text3.setColor(sf::Color (178, 184, 185));
    text3.setPosition(100, 567);
    text4.setFont(font2);
    text4.setCharacterSize(28);
    text4.setColor(sf::Color (178, 184, 185));
    text4.setPosition(490, 567);
    //Initialisation Carte Map
    sf::Texture Menu_principal;

    Menu_principal.loadFromFile("../Graphic_Content/Map/Sim_Map.png");

    sf::Sprite Sprite(Menu_principal);

    sf::Vector2f targetSize(LARGEUR_FENETRE, HAUTEUR_FENETRE);
    std::vector<Flight *> ALl_flight;

    Plane p{"../Text_files/Airplane"};
    Aiport_network a{"../Text_files/Airport_network"};
//Initialisation  Fenetre
    sf::RenderWindow window(sf::VideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE), "AIRPORT CONTROL SIMULATOR");
    window.setPosition(sf::Vector2i(0, 10));
    sf::Event event{};
    Sprite.setScale(
            targetSize.x / Sprite.getLocalBounds().width,
            targetSize.y / Sprite.getLocalBounds().height);

    window.clear(sf::Color::Transparent);

    window.draw(Sprite_Menu);
    window.draw(Sprite_Rect1);
    window.draw(Sprite_Rect2);
    text.setString("SEMI-MANUAL");
    text2.setString("AUTOMATIC");
    window.draw(text);
    window.draw(text2);
    window.display();

        do {
            end_choose_manual=false;
            while (window.pollEvent(event)) {
                if (sf::Mouse::getPosition(window).x >= 22 &&
                    sf::Mouse::getPosition(window).x <= 381 &&
                    sf::Mouse::getPosition(window).y >= 558 &&
                    sf::Mouse::getPosition(window).y <= 635) {
                    Sprite_Rect1.setColor(sf::Color(250, 240, 125));
                    Sprite_Rect2.setColor(sf::Color(255, 255, 255));
                    text2.setColor(sf::Color(178, 184, 185));
                    text.setColor(sf::Color(255, 255, 255));
                    //window.display();
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        if (sf::Mouse::getPosition(window).x >= 22 &&
                            sf::Mouse::getPosition(window).x <= 381 &&
                            sf::Mouse::getPosition(window).y >= 558 &&
                            sf::Mouse::getPosition(window).y <= 635) {
                            enter_manual = false;
                            end_choose_manual=true;
                        }
                    }
                }
                else if (sf::Mouse::getPosition(window).x >= 400 &&
                    sf::Mouse::getPosition(window).x <= 760 &&
                    sf::Mouse::getPosition(window).y >= 558 &&
                    sf::Mouse::getPosition(window).y <= 635) {
                    Sprite_Rect2.setColor(sf::Color(250, 240, 125));
                    Sprite_Rect1.setColor(sf::Color(255, 255, 255));
                    text.setColor(sf::Color(178, 184, 185));
                    text2.setColor(sf::Color(255, 255, 255));

                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        if (sf::Mouse::getPosition(window).x >= 400 &&
                            sf::Mouse::getPosition(window).x <= 760 &&
                            sf::Mouse::getPosition(window).y >= 558 &&
                            sf::Mouse::getPosition(window).y <= 635) {
                            enter_manual = true;
                            end_choose_manual=true;
                        }
                    }
                }
                else {//Pas cliqué bouton 2
                    text2.setColor(sf::Color(178, 184, 185));
                    text.setColor(sf::Color(178, 184, 185));
                    Sprite_Rect1.setColor(sf::Color(255, 255, 255));
                    Sprite_Rect2.setColor(sf::Color(255, 255, 255));
                }
                window.draw(Sprite_Menu);
                window.draw(Sprite_Rect1);
                window.draw(Sprite_Rect2);
                text.setString("SEMI-MANUAL");
                text2.setString("AUTOMATIC");
                window.draw(text);
                window.draw(text2);
                window.display();
            }
            if(end_choose_manual) {
                Game_Menu(choix);
                end_choose_manual= true;
            }
            if(end_choose_manual) {
                switch (choix) {
                    case 1 :
                        window.draw(Sprite_Menu);
                        window.draw(Sprite_Rect1);
                        window.draw(Sprite_Rect2);
                        text3.setString("SHOW AIRPORT \n \t NETWORK");
                        text4.setString("\t\tSTART \n SIMULATION");
                        window.draw(text3);
                        window.draw(text4);
                        window.display();
                        while (!fin) {

                            while (window.pollEvent(event)) {
                                if (sf::Mouse::getPosition(window).x >= 22 &&
                                    sf::Mouse::getPosition(window).x <= 381 &&
                                    sf::Mouse::getPosition(window).y >= 558 &&
                                    sf::Mouse::getPosition(window).y <= 635) {
                                    Sprite_Rect1.setColor(sf::Color(250, 240, 125));
                                    Sprite_Rect2.setColor(sf::Color(255, 255, 255));
                                    text4.setColor(sf::Color(178, 184, 185));
                                    text3.setColor(sf::Color(255, 255, 255));

                                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                                        if (sf::Mouse::getPosition(window).x >= 22 &&
                                            sf::Mouse::getPosition(window).x <= 381 &&
                                            sf::Mouse::getPosition(window).y >= 558 &&
                                            sf::Mouse::getPosition(window).y <= 635) {
                                            show_airport_on_screen(event, window, Sprite, a, font, font2,
                                                                   ALl_flight,
                                                                   enter_manual,
                                                                   p);

                                            fin = false;
                                        }
                                    }
                                } else if (sf::Mouse::getPosition(window).x >= 400 &&
                                           sf::Mouse::getPosition(window).x <= 760 &&
                                           sf::Mouse::getPosition(window).y >= 558 &&
                                           sf::Mouse::getPosition(window).y <= 635) {
                                    Sprite_Rect2.setColor(sf::Color(250, 240, 125));
                                    Sprite_Rect1.setColor(sf::Color(255, 255, 255));
                                    text3.setColor(sf::Color(178, 184, 185));
                                    text4.setColor(sf::Color(255, 255, 255));
                                    //window.display();
                                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                                        if (sf::Mouse::getPosition(window).x >= 400 &&
                                            sf::Mouse::getPosition(window).x <= 760 &&
                                            sf::Mouse::getPosition(window).y >= 558 &&
                                            sf::Mouse::getPosition(window).y <= 635) {
                                            a.Plane_Movement(window, Sprite, enter_manual, ALl_flight, p, a, font2,
                                                             font);
                                            fin = false;
                                        }
                                    }
                                } else {//Pas cliqué bouton 2
                                    text4.setColor(sf::Color(178, 184, 185));
                                    text3.setColor(sf::Color(178, 184, 185));
                                    Sprite_Rect1.setColor(sf::Color(255, 255, 255));
                                    Sprite_Rect2.setColor(sf::Color(255, 255, 255));
                                }
                                window.draw(Sprite_Menu);
                                window.draw(Sprite_Rect1);
                                window.draw(Sprite_Rect2);
                                text3.setString("SHOW AIRPORT \n \t NETWORK");
                                text4.setString("\t\tSTART \n SIMULATION");
                                window.draw(text3);
                                window.draw(text4);
                                window.display();

                                if (event.type == sf::Event::Closed ||
                                    (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                                    fin = true;
                                    window.close();
                                    choix = 0;
                                }
                            }
                        }
                        fin = false;

                        break;
                    case 2 :
                        //affichage info aeroport
                        airport_information(choix, a);
                        choix = 0;
                        break;
                    case 3:
                        //affichage info avion
                        airplane_information(choix, p);
                        choix = 0;
                        break;
                    case 4 :
                        back_menu = false;
                        //Credits
                        std::cout << "Credit";
                        break;
                    case 5 :
                        std::cout << "Good bye HAVE A NICE DAY";
                        break;
                    default:
                        std::cout << "UNKNOWN CHOICE\n"
                                     "PLEASE RE-TYPE\n";
                        choix = 0;
                        break;
                }
            }

}while (choix < 5 && back_menu);

return 0;
}



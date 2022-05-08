#include "Menu.h"

//Affichage du Menu avec le style d'affichage
void Game_Menu(unsigned int &choix) {
    std::cout << "\n";
    for (int i = 0; i < 20; ++i) {
        std::cout << "*";
    }
    std::cout << " AIRPORT CONTROL SIMULATOR ";
    for (int i = 0; i < 20; ++i) {
        std::cout << "*";
    }
    std::cout << "\n";
    std::cout << "                   1. START A SIMULATION \n";
    std::cout << "                   2. INFORMATIONS ABOUT AIRPORTS \n";
    std::cout << "                   3. INFORMATIONS ABOUT AIRPLANES \n";
    std::cout << "                   4. CREDITS \n";
    std::cout << "                   5. QUIT \n";
    for (int i = 0; i < 67; ++i) {
        std::cout << "*";
    }
    std::cout << "\n"
                 "ENTER YOUR CHOICE : ";
    std::cin >> choix;
}

void airplane_information(unsigned int &choix, Plane &p) {
    do {
        std::cout << "\n";
        for (int i = 0; i < 20; ++i) {
            std::cout << "*";
        }
        std::cout << " AIRPLANE INFORMATION ";
        for (int i = 0; i < 25; ++i) {
            std::cout << "*";
        }
        std::cout << "\n";
        std::cout << "                   1. SHOW PLANES \n"
                     "                   2. BACK TO PRINCIPAL MENU \n";
        for (int i = 0; i < 67; ++i) {
            std::cout << "*";
        }
        std::cout << "\n"
                     "ENTER YOUR CHOICE : ";
        std::cin >> choix;

        switch (choix) {
            case 1 :
                p.afficher();
                choix = 0;
                break;
            case 2:
                break;
            default:
                std::cout << "UNKNOWN CHOICE\n"
                             "PLEASE RE-TYPE\n";
                choix = 0;
                break;
        }
    } while (choix != 2);
}

void airport_information(unsigned int &choix, Aiport_network &a) {
    do {
        std::cout << "\n";
        for (int i = 0; i < 21; ++i) {
            std::cout << "*";
        }
        std::cout << " AIRPORT INFORMATION ";
        for (int i = 0; i < 25; ++i) {
            std::cout << "*";
        }
        std::cout << "\n";
        std::cout << "                   1. SHOW AIRPORTS \n"
                     "                   2. BACK TO PRINCIPAL MENU \n";
        for (int i = 0; i < 67; ++i) {
            std::cout << "*";
        }
        std::cout << "\n"
                     "ENTER YOUR CHOICE : ";
        std::cin >> choix;

        switch (choix) {
            case 1 :
                a.afficher();
                choix = 0;
                break;
            case 2:
                break;
            default:
                std::cout << "UNKNOWN CHOICE\n"
                             "PLEASE RE-TYPE\n";
                choix = 0;
                break;
        }
    } while (choix != 2);
}


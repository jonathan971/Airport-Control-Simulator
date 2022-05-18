//
// Created by mathi on 08/05/2022.
//

#include "Map.h"

#include <cmath>


Map::Map() {
}

void Map::modelize_map(Aiport_network &a)  {

    int id_auto_increment(0);
    int rien(0);
    std::string nom;
    for (int i(0); i < COLUMNS; ++i) {
        my_map.emplace_back(std::vector<Case>());
        for (int j(0); j < ROWS; ++j) {
           if(i==0){
               my_map[0].push_back(Case( id_auto_increment, 0.0f));

               if(j==0) {
                   my_map[0][my_map[0].size() - 1].set_Y(0.0f);
               }else{
                   my_map[0][j].set_Y(my_map[0][j - 1].get_Y() + 15.0f);
               }
           }else {
               if(j!=0) {
                   my_map[i].push_back(Case( id_auto_increment, my_map[i - 1][j].get_X()+15.0f));
                   my_map[i][j].set_Y(my_map[i][j - 1].get_Y() + 15.0f);
               }else{
                   my_map[i].push_back(Case( id_auto_increment, my_map[i-1][j].get_X()+15.0f));
               my_map[i][j].set_X(my_map[i-1][j].get_X() + 15.0f);
                   }
           }
            ++id_auto_increment;

            for(size_t k(0); k < a.getListAirport().size();++k ) {

                if ((int)my_map[i][j].get_X() >= a.getListAirport()[k]->getXmin() &&
                        (int) my_map[i][j].get_X() <= a.getListAirport()[k]->getXmax() &&
                        (int)my_map[i][j].get_Y() >= a.getListAirport()[k]->getYmin() &&
                        (int)my_map[i][j].get_Y() <= a.getListAirport()[k]->getYmax()){

                    my_map[i][j].set_state(2);

                }
                /*else if(case_pixel >= coordsTurbulence &&
                        case_pixel <= coordsTurbulence &&
                        case_pixel >= coordsTurbulence &&
                        case_pixel <= coordsTurbulence){my_map[i][j].set_state(3);}*/
                //else{my_map[i][j].set_state(1);}
            }
        }
    }


    for (int i(0); i < COLUMNS; ++i) {
        for (int j(0); j < ROWS; ++j) {

             if(i > 0) {
                my_map[i][j].addSuccesseur(&my_map[i - 1][j],
                                           calcul_distance(my_map[i][j].get_X(), my_map[i][j].get_Y(),
                                                           my_map[i - 1][j].get_X(), my_map[i - 1][j].get_Y()));
            }
            if(j>0) {
                my_map[i][j].addSuccesseur(&my_map[i][j - 1],
                                           calcul_distance(my_map[i][j].get_X(), my_map[i][j].get_Y(),
                                                           my_map[i][j - 1].get_X(), my_map[i][j - 1].get_Y()));
            }

            if(j>0 && i > 0) {
                my_map[i][j].addSuccesseur(&my_map[i - 1][j - 1],
                                           calcul_distance(my_map[i][j].get_X(), my_map[i][j].get_Y(),
                                                           my_map[i - 1][j - 1].get_X(), my_map[i - 1][j - 1].get_Y()));
            }

            if(j<ROWS) {
                my_map[i][j].addSuccesseur(&my_map[i][j + 1],
                                           calcul_distance(my_map[i][j].get_X(), my_map[i][j].get_Y(),
                                                           my_map[i][j + 1].get_X(), my_map[i][j + 1].get_Y()));
            }


            if(i>0 && j<ROWS ){
                my_map[i][j].addSuccesseur(&my_map[i - 1][j + 1],
                                           calcul_distance(my_map[i][j].get_X(), my_map[i][j].get_Y(),
                                                           my_map[i - 1][j + 1].get_X(), my_map[i - 1][j + 1].get_Y()));

            }
           if(i<COLUMNS-1) {

               my_map[i][j].addSuccesseur(&my_map[i+1][j],
                                          calcul_distance(my_map[i][j].get_X(), my_map[i][j].get_Y(),
                                                          my_map[i+1][j].get_X(), my_map[i+1][j].get_Y()));
           }
           if(i<COLUMNS-1 && j<ROWS ) {
                my_map[i][j].addSuccesseur(&my_map[i + 1][j + 1],
                                           calcul_distance(my_map[i][j].get_X(), my_map[i][j].get_Y(),
                                                           my_map[i + 1][j + 1].get_X(), my_map[i + 1][j + 1].get_Y()));
           }


           if(j>0 && i<COLUMNS-1){
                my_map[i][j].addSuccesseur(&my_map[i + 1][j - 1],
                                           calcul_distance(my_map[i][j].get_X(), my_map[i][j].get_Y(),
                                                           my_map[i + 1][j - 1].get_X(), my_map[i + 1][j - 1].get_Y()));
           }

        }
    }

}




std::vector<Case*> Map::Astar_turbulence(Airplane* plane, Case* arrival ) {


    std::vector<int> couleurs(SIZE, 0);
    std::vector<float> distances(SIZE, std::numeric_limits<float>::max());// 200 pour le nbre de case quon pense utilisé pour la redirection
    std::vector<float> f(SIZE, std::numeric_limits<float>::max());//distance + heuristique
    double rapport_consommation_carburant(0);// si on définit par exemple 300L/km et 500/km dans la turbulence
    std::vector<Case*> predecesseurs;
    std::vector<Case*> parcour_case(SIZE, nullptr);


    for (int i(0); i < COLUMNS; ++i) {
        for (int j(0); j < ROWS; ++j) {
            parcour_case[i*ROWS+j] = &my_map[i][j];
        }
    }


    std::vector<Case*> deviation;
    bool arrive;
    Case* avion_case;
    for (int i(0); i < SIZE; ++i) {
            if (parcour_case[i]->get_X() + 15.0f >= plane->get_plane_x() &&
                    parcour_case[i]->get_X() <= plane->get_plane_x() &&
                    parcour_case[i]->get_Y() + 15.0f >= plane->get_plane_y() &&
                    parcour_case[i]->get_Y() <= plane->get_plane_y()){

                avion_case = parcour_case[i];//case ou il y a l'avion
            }
    }
    distances[avion_case->get_id()] = 0;
    f[avion_case->get_id()] = 0;

    //  rapport_consommation_carburant = f->get_airplane()->get_plane_comsuption() / 300); la on obtient le nbre d'ut que l'on peut faire avec le carburant de l'avion


    do {

        float distanceMini = std::numeric_limits<float>::max();
        float f_Mini = std::numeric_limits<float>::max();
        bool choix(false);
        do {

            for (size_t i = 0; i < f.size(); i++) {

                if (couleurs[i] == 0 && f[i] < f_Mini) {
                    f_Mini = f[i];//distances[i] + calcul_distance(plane->get_plane_x(),plane->get_plane_y(),avion_case->get_X(),avion_case->get_Y());
                    avion_case = parcour_case[i];


                }
                //  rapport_consommation_carburant = f->get_airplane()->get_plane_comsuption() / 300); la on obtient le nbre d'ut que l'on peut faire avec le carburant de l'avion
            }


            //VERIFICATION DE LA VIABILITE DE LA CASE
            if (plane->get_plane_x() == arrival->get_X() &&  plane->get_plane_y() == arrival->get_Y()) {
                couleurs[avion_case->get_id()] = 1;
                arrive = true;
                //choix=true;
                deviation.push_back(avion_case);// push back dans le vecteur du chemin
            } else if (avion_case->get_state()!=3 && avion_case->get_state()!=1 ) {// on vérifie si la case n'est pas un obstacle
                couleurs[avion_case->get_id()] = 1;
                choix = true;
                deviation.push_back(avion_case);// push back dans le vecteur du chemin

            } else {
                //refaire le calcul de f mini sans la case en question donc remettre le f de la case à l'infini
                f[avion_case->get_id()] = std::numeric_limits<float>::max();
            }
        } while (!choix);




        for (auto successeur: avion_case->getSuccesseurs()) {
            if (couleurs[successeur.first->get_id()] == 0) {

                if (distances[avion_case->get_id()] + successeur.second < distances[successeur.first->get_id()]) {
                   distances[successeur.first->get_id()] = distances[avion_case->get_id()] + successeur.second;
                    f[successeur.first->get_id()] = distances[successeur.first->get_id()] + calcul_distance(successeur.first->get_X(),successeur.first->get_Y(),arrival->get_X(),arrival->get_Y());
                    predecesseurs[successeur.first->get_id()] = avion_case;
                }
            }
        }


    } while (arrive);



    return deviation;
}



float calcul_distance(float x, float y,float x2, float y2) {
    return std::sqrt( (x - x2) * (x - x2) + (y - y2) * (y - y2)  ) ;
}

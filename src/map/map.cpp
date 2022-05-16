//
// Created by mathi on 08/05/2022.
//

#include "Map.h"

#include <cmath>


Map::Map() {
    /*my_map  = new Case [COLUMNS]();

    for (int i = 0; i < COLUMNS; i++) {
        my_map[i]= new Case[ROWS];
    }*/
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
            if(my_map[i][j].get_state() == 2){
                ++rien;

                //std::cout << "couilles\n";
                //std::cout << i << "/" << j << "\n";

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




void Map::Astar_turbulence(Airplane* plane, Case* arrival ) {

    std::vector<Case> open_list;
    std::vector<Case> closed_list;



    std::vector<int> couleurs(my_map.size(), 0);
    std::vector<float> distances(my_map.size(), std::numeric_limits<float>::max());// 200 pour le nbre de case quon pense utilisé pour la redirection
    std::vector<float> heuristiques(my_map.size(), std::numeric_limits<float>::max());// 200 pour le nbre de case quon pense utilisé pour la redirection
    std::vector<Case*> predecesseurs;
    //std::vector<Case*> deviation;
    bool arrive;



    Case* avion_case;//case ou il y a l'avion
    for (int i(0); i < COLUMNS; ++i) {
        for (int j(0); j < ROWS; ++j) {

            if (my_map[i][j].get_X() + 15.0f >= plane->get_plane_x() &&
                my_map[i][j].get_X() <= plane->get_plane_x() &&
                my_map[i][j].get_Y() + 15.0f >= plane->get_plane_y() &&
                my_map[i][j].get_Y() <= plane->get_plane_y()){

                avion_case = &my_map[i][j];
            }
        }
    }

    do {

        float distanceMini = std::numeric_limits<float>::max();
        bool choix(false);
        do {

            for (size_t i = 0; i < distances.size(); i++) {
                if (couleurs[i] == 0 && distances[i] < distanceMini) {
                    distanceMini = distances[i] + calcul_distance(plane->get_plane_x(),plane->get_plane_y(),avion_case->get_X(),avion_case->get_Y());
                    avion_case->set_id((int) i) ;
                }
                //  rapport_consommation_carburant = f->get_airplane()->get_plane_comsuption() / 300); la on obtient le nbre d'ut que l'on peut faire avec le carburant de l'avion
            }
            //std::cout << std::endl << std::endl;

            //VERIFICATION DE LA VIABILITE DE LA CASE
            if (plane->get_plane_x() == arrival->get_X() &&  plane->get_plane_y() == arrival->get_Y()) {
                //couleurs[avion_case->get_id()] = 1;
                arrive = true;
                choix=true;
                //deviation.push_back(s);// push back dans le vecteur du chemin
            } else if (avion_case->get_state()!=3) {// on vérifie si la case n'est pas un obstacle
                //couleurs[avion_case->get_id()] = 1;
                choix = true;
                //deviation.push_back(s);// push back dans le vecteur du chemin

            } else {
                //refaire le calcul de distance mini sans s donc remettre la distance de s à l'infini pour que l'aeroport d'id s ne soit  plus prit en compte
                distances[avion_case->get_id()] = std::numeric_limits<float>::max();
            }
        } while (!choix);

        //recup position de la case choisi










        for (auto successeur: avion_case->getSuccesseurs()) {
            //tchek si succsseur dans la closed list
            //stocke la distance wsv la distance du precdent + la nouvelle
            //gerer lheuristique qui est la distance de la pos ou on est jusqua larrivé en vol doiseau
            //et on fait la resultante des 2 pour choisir le prochain sommet
            //on stocke le pred
            if (couleurs[successeur.first->get_id()] == 0) {
                if (distances[avion_case->get_id()] + successeur.second < distances[successeur.first->get_id()]) {
                   distances[successeur.first->get_id()] = distances[avion_case->get_id()] + successeur.second +
                            calcul_distance(plane->get_plane_x(),plane->get_plane_y(),avion_case->get_X(),avion_case->get_Y());
                    predecesseurs[successeur.first->get_id()] = avion_case;
                }
            }
        }


    } while (arrive);






    //return deviation;
}

bool Map::already_in_list(Case s, std::vector<Case> list) {
    int already;

    for(size_t i(0); i<list.size(); ++i){
        if(s.get_id() == list[i].get_id()){
            ++already;
        }
    }
    if(already>0){
        return true;
    }
    else{ return false;}

}


float calcul_distance(float x, float y,float x2, float y2) {
    return std::sqrt( (x - x2) * (x - x2) + (y - y2) * (y - y2)  ) ;
}

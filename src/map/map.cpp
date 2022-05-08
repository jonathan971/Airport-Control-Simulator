//
// Created by mathi on 08/05/2022.
//

#include "map.h"


map::map(Case** board) {
    board  = new Case *[COLUMNS]();

    for (int i = 0; i < COLUMNS; i++) {
        board[i]= new Case[ROWS];
    }

    my_map = board;
}

void map::modelize_map() {
    int case_pixel(0);
    int id_auto_increment(0);
    for (int j(0); j < COLUMNS; j++) {
        for (int i(0); i < ROWS; ++i) {

            my_map[i][j].set_X(case_pixel);
            my_map[i][j].set_Y(case_pixel);
            my_map[i][j].set_id(id_auto_increment);
            ++id_auto_increment;
            case_pixel += 15;
        }
    }
    for (int j(0); j < COLUMNS; j++) {
        for (int i(0); i < ROWS; ++i) {


            my_map[i][j].addSuccesseur(&my_map[i-1][j], calcul_distance(my_map[i][j].get_X(),my_map[i][j].get_Y(),my_map[i-1][j].get_X(),my_map[i-1][j].get_Y()));
            my_map[i][j].addSuccesseur(&my_map[i][j-1], calcul_distance(my_map[i][j].get_X(),my_map[i][j].get_Y(),my_map[i][j-1].get_X(),my_map[i][j-1].get_Y()));
            my_map[i][j].addSuccesseur(&my_map[i-1][j-1], calcul_distance(my_map[i][j].get_X(),my_map[i][j].get_Y(),my_map[i-1][j-1].get_X(),my_map[i-1][j-1].get_Y()));

            my_map[i][j].addSuccesseur(&my_map[i+1][j], calcul_distance(my_map[i][j].get_X(),my_map[i][j].get_Y(),my_map[i+1][j].get_X(),my_map[i+1][j].get_Y()));
            my_map[i][j].addSuccesseur(&my_map[i][j+1], calcul_distance(my_map[i][j].get_X(),my_map[i][j].get_Y(),my_map[i][j+1].get_X(),my_map[i][j+1].get_Y()));
            my_map[i][j].addSuccesseur(&my_map[i+1][j+1], calcul_distance(my_map[i][j].get_X(),my_map[i][j].get_Y(),my_map[i+1][j+1].get_X(),my_map[i+1][j+1].get_Y()));




        }
    }

}



std::vector<Case*> map::Astar_turbulence(Airplane* plane, Case* arrival ) {


    std::vector<int> couleurs(200, 0);
    std::vector<int> distances(200, std::numeric_limits<int>::max());// 200 pour le nbre de case quon pense utilisé pour la redirection
    std::vector<int> heuristiques(200, std::numeric_limits<int>::max());// 200 pour le nbre de case quon pense utilisé pour la redirection
    std::vector<int> predecesseurs;
    std::vector<Case*> deviation;
    bool arrive;
    //Case* depart;



    Case* s;

    do {

        int distanceMini = std::numeric_limits<int>::max();
        bool choix(false);
        do {
            for (int j(0); j < COLUMNS; j++) {
                for (int i(0); i < ROWS; ++i) {

                    if(my_map[i][j].get_X()==plane->get_plane_x() && my_map[i][j].get_Y()==plane->get_plane_y() ){
                        s = &my_map[i][j];
                    }
                }
            }
            for (size_t i = 0; i < distances.size(); i++) {
                if (couleurs[i] == 0 && distances[i] < distanceMini) {
                    distanceMini = distances[i] + calcul_distance(plane->get_plane_x(),plane->get_plane_y(),s->get_X(),s->get_Y());
                    s->set_id((int) i) ;
                }
                //  rapport_consommation_carburant = f->get_airplane()->get_plane_comsuption() / 300); la on obtient le nbre d'ut que l'on peut faire avec le carburant de l'avion
            }
            //std::cout << std::endl << std::endl;

            //VERIFICATION DE LA VIABILITE DE LA CASE
            if (plane->get_plane_x() == arrival->get_X() &&  plane->get_plane_y() == arrival->get_Y()) {
                couleurs[s->get_id()] = 1;
                arrive = true;
                choix=true;
                deviation.push_back(s);// push back dans le vecteur du chemin
            } else if (s->get_state()!=3) {// on vérifie si la case n'est pas un obstacle
                couleurs[s->get_id()] = 1;
                choix = true;
                deviation.push_back(s);// push back dans le vecteur du chemin

            } else {
                //refaire le calcul de distance mini sans s donc remettre la distance de s à l'infini pour que l'aeroport d'id s ne soit  plus prit en compte
                distances[s->get_id()] = std::numeric_limits<int>::max();
            }
        } while (!choix);

        /*couleurs[s] = 1;
        nbMarques++;*/

        for (auto successeur: s->getSuccesseurs()) {
            if (couleurs[successeur.first->get_id()] == 0) {
                if (distances[s->get_id()] + successeur.second < distances[successeur.first->get_id()]) {
                    distances[successeur.first->get_id()] = distances[s->get_id()] + successeur.second +
                            calcul_distance(plane->get_plane_x(),plane->get_plane_y(),s->get_X(),s->get_Y());
                    predecesseurs[successeur.first->get_id()] = s->get_id();
                }
            }
        }
    } while (arrive);






    return deviation;
}


float calcul_distance(float x, float y,float x2, float y2) {
    return sqrt( (x - x2) * (x - x2) + (y - y2) * (y - y2)  ) ;
}

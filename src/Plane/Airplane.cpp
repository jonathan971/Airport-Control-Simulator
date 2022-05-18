#include "Airplane.h"

Airplane::Airplane(std::string &airplane_model, int &airplane_id, std::string &airplane_type, bool &airplane_state,
                   double &airplane_comsuption,
                   double &airplane_speed, double &airplane_landing_speed, double &airplane_takeoff_speed,
                   double &airplane_fuel_capacity, sf::Sprite &pic) :
        model{airplane_model}, id{airplane_id}, type{airplane_type}, state{airplane_state},
        comsuption{airplane_comsuption},
        speed{airplane_speed}, landing_speed{airplane_landing_speed}, takeoff_speed{airplane_takeoff_speed},
        fuel_capacity{airplane_fuel_capacity}, takeoff{false}, x{0}, y{0}, airplane_pic{pic} {

}

std::string Airplane::get_model() const {
    return model;
}

int Airplane::get_id() const {
    return id;
}

std::string Airplane::get_type() const {
    return type;
}

bool Airplane::get_state() const {
    return state;
}

bool Airplane::get_if_takeoff() const {
    return takeoff;
}

double Airplane::get_plane_comsuption() const {
    return comsuption;
}

double Airplane::get_speed() const {
    return speed;
}

double Airplane::get_landing_speed() const {
    return landing_speed;
}

double Airplane::get_takeoff_speed() const {
    return takeoff_speed;
}

double Airplane::get_fuel_capacity() const {
    return fuel_capacity;
}

void Airplane::afficher() const {
    std::cout << "                   Model : " << model << std::endl
              << "                   Id : " << id << std::endl
              << "                   Type : " << type << std::endl;
    if (!state) {
        std::cout << "                   State : Off flight " << std::endl;
    } else {
        std::cout << "                   State : On flight " << std::endl;
    }
    std::cout << "                   Speed : " << speed << std::endl
              << "                   Landing Speed : " << landing_speed << std::endl
              << "                   Take off Speed : " << takeoff_speed << std::endl
              << "                   Fuel Capacity : " << speed << "\n" << std::endl;
}

void Airplane::put_state(bool plane_state) {
    state = plane_state;
}

void Airplane::takeoff_or_not(bool if_takeoff) {
    takeoff = if_takeoff;
}

float Airplane::get_plane_x() const {
    return x;
}

float Airplane::get_plane_y() const {
    return y;
}

void Airplane::set_plane_x(float plane_x) {
    x = (float)plane_x;
}

void Airplane::set_plane_y(float plane_y) {
    y = (float)plane_y;
}

sf::Sprite Airplane::get_Sprite() const {
    return airplane_pic;
}

void Airplane::set_Angle(float angle){
        airplane_pic.setRotation(angle+5);
}

void Airplane::set_Coord_plane(float plane_x, float plane_y) {
    airplane_pic.setPosition(plane_x, plane_y);
}






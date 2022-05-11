cmake_minimum_required(VERSION 3.17)
project(Projet_S2_ING2)

IF(APPLE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp src/Menu/Menu.cpp src/Menu/Menu.h src/Airport/Airport.cpp src/Airport/Airport.h src/Plane/Plane.cpp src/Plane/Plane.h src/Airport_network/Aiport_network.cpp src/Airport_network/Aiport_network.h src/Flight/Flight.cpp src/Flight/Flight.h src/Flying_time/Flying_time.cpp src/Flying_time/Flying_time.h src/Plane/Airplane.cpp src/Plane/Airplane.h src/Airport_Connexion/Connexion.cpp src/Airport_Connexion/Connexion.h src/Case/Case.cpp src/Case/Case.h src/map/map.cpp src/map/map.h)
add_executable(Projet_S2_ING2 ${SOURCE_FILES} main.cpp src/Menu/Menu.cpp src/Menu/Menu.h src/Airport/Airport.cpp src/Airport/Airport.h src/Plane/Plane.cpp src/Plane/Plane.h src/Airport_network/Aiport_network.cpp src/Airport_network/Aiport_network.h src/Flight/Flight.cpp src/Flight/Flight.h src/Flying_time/Flying_time.cpp src/Flying_time/Flying_time.h src/Plane/Airplane.cpp src/Plane/Airplane.h src/Airport_Connexion/Connexion.cpp src/Airport_Connexion/Connexion.h)
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(Projet_S2_ING2 sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
ENDIF(APPLE)

IF(WIN32)
    set(CMAKE_CXX_STANDARD 14)

    add_executable(Projet_S2_ING2 main.cpp src/Menu/Menu.cpp src/Menu/Menu.h src/Airport/Airport.cpp src/Airport/Airport.h src/Plane/Plane.cpp src/Plane/Plane.h src/Airport_network/Aiport_network.cpp src/Airport_network/Aiport_network.h src/Flight/Flight.cpp src/Flight/Flight.h src/Flying_time/Flying_time.cpp src/Flying_time/Flying_time.h src/Plane/Airplane.cpp src/Plane/Airplane.h src/Airport_Connexion/Connexion.cpp src/Airport_Connexion/Connexion.h src/Case/Case.cpp src/Case/Case.h src/map/map.cpp src/map/map.h)
    set  (SFML_STATIC_LIBRARIES TRUE)
    set  (SFML_DIR C:/SFML/lib/cmake/SFML)
    find_package ( SFML COMPONENTS system window graphics audio network REQUIRED)

    include_directories (C:/SFML/include)
    target_link_libraries(Projet_S2_ING2  sfml-system sfml-window sfml-graphics sfml-audio sfml-network )
ENDIF(WIN32)

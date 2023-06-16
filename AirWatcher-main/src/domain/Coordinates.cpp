/*************************************************************************
                           Coordinates  -  longitude + latitude
                             -------------------
    beginning            : 09/05/2023
    copyright            : (C) 2023 by Q41 : Adrien Morin, Isaline Foissey, Marie Roulier, Célia Djouadi et Nour ElJadiri
*************************************************************************/

//---------- Réalisation de la classe <Coordinates> (fichier Coordinates.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <cmath>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Coordinates.h"

//------------------------------------------------------------- Constantes
#define RAD_EARTH 6372.79756085

//----------------------------------------------------- Méthodes publiques

double Coordinates::Distance (const Coordinates& point) const {

    double lat1  = (this->latitude  * M_PI)/180.0;
    double lat2 = (point.latitude * M_PI)/180.0;
    double long1  = (this->longitude  * M_PI)/180.0;
    double long2  = (point.longitude * M_PI)/180.0;

    double dLat = lat2 - lat1;
    double dLong = long2 - long1;

    double a = sin(dLat / 2.0) * sin(dLat / 2.0) +
               cos(lat1) * cos(lat2) *
               sin(dLong / 2.0) * sin(dLong / 2.0);

    double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));

    return c * RAD_EARTH;
}

//-------------------------------------------- Constructeurs - destructeur

Coordinates::Coordinates() {
    longitude = .0;
    latitude = .0;
}

Coordinates::Coordinates (double latInput, double longInput)
{
    longitude = longInput;
    latitude = latInput;
} //----- Fin de Coordinates (constructeur par defaut)

Coordinates::Coordinates ( const Coordinates & coord )
{
    longitude = coord.longitude;
    latitude= coord.latitude;
} //----- Fin de Sensor (constructeur de copie)

Coordinates::~Coordinates( ) = default;

//---------------------------------------------------------------- Getters

double Coordinates::getLongitude() const {
    return longitude;
}

double Coordinates::getLatitude() const {
    return latitude;
}

//---------------------------------------------------------------- Setters

void Coordinates::setLongitude(double aLongitude) {
    longitude = aLongitude;
}

void Coordinates::setLatitude(double aLatitude) {
    latitude = aLatitude;
}


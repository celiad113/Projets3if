/*************************************************************************
                           Sensor  -  object of a sensor
                             -------------------
    beginning            : 09/05/2023
    copyright            : (C) 2023 by Q41 : Adrien Morin, Isaline Foissey, Marie Roulier, Célia Djouadi et Nour ElJadiri
*************************************************************************/

//---------- Réalisation de la classe <Sensor> (fichier Sensor.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <string>
#include <utility>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Sensor.h"

//----------------------------------------------------- Méthodes publiques

//---------------------------------------------------------------- Getters

const string &Sensor::getId() const {
    return id;
}

const Coordinates &Sensor::getCoord() const {
    return coord;
}

bool Sensor::isReliable() const {
    return reliable;
}

//---------------------------------------------------------------- Setters

void Sensor::setId(const string &id) {
    this->id = id;
}

void Sensor::setCoord(const Coordinates & coord) {
    this->coord = coord;
}

void Sensor::setReliable(bool reliable) {
    this->reliable = reliable;
}

const string &Sensor::getPrivIndivId() const {
    return privIndivId;
}

void Sensor::setPrivIndivId(const string & privIndivId) {
    this->privIndivId = privIndivId;
}

//-------------------------------------------- Constructeurs - destructeur
Sensor::Sensor ( const Sensor & aSensor )
{
    id = aSensor.id;
    coord = aSensor.coord;
    reliable = aSensor.reliable;
    privIndivId = aSensor.privIndivId;
}

Sensor::Sensor(string aId, const Coordinates& someCoord)
{
    id = std::move(aId);
    coord = someCoord;
    reliable = true;
    privIndivId = "";
}

Sensor::Sensor(string aId, const Coordinates& someCoord, bool isReliable)
{
    id = std::move(aId);
    coord = someCoord;
    reliable = isReliable;
    privIndivId = "";
}

Sensor::Sensor()
= default;

Sensor :: ~Sensor()
= default;



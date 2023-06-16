/*************************************************************************
                           PrivIndiv  -  user of type private individual
                             -------------------
    beginning            : 09/05/2023
    copyright            : (C) 2023 by Q41 : Adrien Morin, Isaline Foissey, Marie Roulier, Célia Djouadi et Nour ElJadiri
*************************************************************************/

//---------- Réalisation de la classe <PrivIndiv> (fichier PrivIndiv.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <string>
#include <utility>
using namespace std;

//------------------------------------------------------ Include personnel
#include "PrivIndiv.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void PrivIndiv::printProvidedSensors() const {
    for(const auto& sensor : providedSensors){
        cout << " -" << sensor.getId() << endl;
    }
}

//---------------------------------------------------------------- Getters

vector<Sensor> & PrivIndiv::getProvidedSensors(){
    return this->providedSensors;
}

int & PrivIndiv::getPoints(){
    return this->points;
}

//---------------------------------------------------------------- Setters

void PrivIndiv::setProvidedSensors(vector<Sensor> provSens){
    this->providedSensors = std::move(provSens);
}

void PrivIndiv::setPoints(int aPoint){
    this->points = aPoint;
    FileManager f = FileManager();
    f.UpdatePoints(id,aPoint);
}

//-------------------------------------------- Constructeurs - destructeur
PrivIndiv::PrivIndiv ( const PrivIndiv & aPrivIndiv )
{
    id = aPrivIndiv.id;
    providedSensors = aPrivIndiv.providedSensors;
    points = aPrivIndiv.points;
}

PrivIndiv::PrivIndiv ( const string &id, vector<Sensor> provSens )
{
    this->id = id;
    this->providedSensors = std::move(provSens);
    points = 0;
}

PrivIndiv::PrivIndiv ( const string &id, vector<Sensor> provSens, int points )
{
    this->id = id;
    this->providedSensors = std::move(provSens);
    this->points = points;
}

PrivIndiv::~PrivIndiv( )= default;

PrivIndiv::PrivIndiv() = default;

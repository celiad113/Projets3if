/*************************************************************************
                           Measure  -  a measurement of a pollutant
                             -------------------
    beginning            : 09/05/2023
    copyright            : (C) 2023 by Q41 : Adrien Morin, Isaline Foissey, Marie Roulier, Célia Djouadi et Nour ElJadiri
*************************************************************************/

//---------- Réalisation de la classe <Measure> (fichier Measure.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <utility>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Measure.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

//---------------------------------------------------------------- Getters

const string & Measure::getSensorId() const{
    return this->sensorId;
}

const time_t & Measure::getDateMeas() const{
    return this->dateMeas;
}

const string & Measure::getAttributeValue() const{
    return this->attributeType;
}

double & Measure::getValue(){
    return this->value;
}

//---------------------------------------------------------------- Setters

void Measure::setSensorId(string anId){
    this->sensorId = std::move(anId);
}

void Measure::setDateMeas(time_t aDate){
    this->dateMeas = aDate;
}

void Measure::setAttributeType(string aType){
    this->attributeType = std::move(aType);
}

void Measure::setValue(double aValue){
    this->value = aValue;
}

//-------------------------------------------- Constructeurs - destructeur

Measure::Measure ( )
= default;

Measure::Measure (string  sensorIdInput, const time_t& dateMeasInput, string  attributeTypeInput, const double& valueInput)
: sensorId(std::move(sensorIdInput)), dateMeas(dateMeasInput), attributeType(std::move(attributeTypeInput)), value(valueInput)
{
}

Measure::~Measure( )
= default;


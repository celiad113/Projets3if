/*************************************************************************
                           Attribute  -  type of pollutant
                             -------------------
    beginning            : 09/05/2023
    copyright            : (C) 2023 by Q41 : Adrien Morin, Isaline Foissey, Marie Roulier, Célia Djouadi et Nour ElJadiri
*************************************************************************/

//---------- Réalisation de la classe <Attribute> (fichier Attribute.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <utility>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Attribute.h"

//----------------------------------------------------- Méthodes publiques

//---------------------------------------------------------------- Getters
string Attribute::getType()
{
    return type;
}

string Attribute::getUnit()
{
    return unit;
}

string Attribute::getDescription()
{
    return description;
}

//---------------------------------------------------------------- Setters

void Attribute::setType( string id)
{
    type = std::move(id);
}

void Attribute::setUnit(string unite)
{
    unit = std::move(unite);
}

void Attribute::setDescription( string aDescription)
{
    description = std::move(aDescription);
}

//-------------------------------------------- Constructeurs - destructeur
Attribute::Attribute ( const Attribute & anAttribute )
{
    unit = anAttribute.unit;
    type = anAttribute.type;
    description = anAttribute.description;
}

Attribute::Attribute( string unit, string type, string description )
{
    this->type = std::move(type);
    this->unit = std::move(unit);
    this->description = std::move(description);
}

Attribute::Attribute() = default;

Attribute::~Attribute ( ) = default;

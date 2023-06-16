/*************************************************************************
                           Provider  -  user of type provider
                             -------------------
    beginning            : 09/05/2023
    copyright            : (C) 2023 by Q41 : Adrien Morin, Isaline Foissey, Marie Roulier, Célia Djouadi et Nour ElJadiri
*************************************************************************/

//---------- Réalisation de la classe <Provider> (fichier Provider.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <utility>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Provider.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void Provider::printAirCleaners() const {
    for(const auto & aircleaner : providedAC){
        cout << aircleaner.getAirCleanerID() << endl;
    }
}

//---------------------------------------------------------------- Getters

const string &Provider::getProviderId() const {
    return providerID;
}

const vector<AirCleaner> &Provider::getProvidedAc() const {
    return providedAC;
}


//---------------------------------------------------------------- Setters
void Provider::setProviderId(const string &providerId) {
    providerID = providerId;
}

void Provider::setProvidedAc(const vector<AirCleaner> &providedAc) {
    providedAC = providedAc;
}

//-------------------------------------------- Constructeurs - destructeur

Provider::Provider() = default;

Provider::Provider(string providerIDInput) : providerID(std::move(providerIDInput)) {}

Provider::Provider( const string & providerID, const vector<AirCleaner> & airCleaners )
{
    this->providerID = providerID;
    providedAC = airCleaners;
}

Provider::~Provider()= default;

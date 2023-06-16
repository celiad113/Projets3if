/*************************************************************************
                           AirCleaner  -  object of an Air Cleaner
                             -------------------
    beginning            : 09/05/2023
    copyright            : (C) 2023 by Q41 : Adrien Morin, Isaline Foissey, Marie Roulier, Célia Djouadi et Nour ElJadiri
*************************************************************************/

//---------- Réalisation de la classe <AirCleaner> (fichier AirCleaner.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <utility>
using namespace std;

//------------------------------------------------------ Include personnel
#include "AirCleaner.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

//Getters et Setters

const string & AirCleaner::getAirCleanerID() const {
      return id;
}

void AirCleaner::setAirCleanerID(string anID){
      id = std::move(anID);
}

const Coordinates &AirCleaner::getCoord() const {
    return coord;
}

void AirCleaner::setCoord(const Coordinates& coordinates){
  coord = coordinates;
}

const time_t & AirCleaner::getDateStart() const{
  return dateStart;
}

void AirCleaner::setDateStart(const time_t aStart){
  dateStart = aStart;
}

const time_t & AirCleaner::getDateStop() const{
return dateStop;
}

void AirCleaner::setDateStop(const time_t aStop){
  dateStop = aStop;
}


//-------------------------------------------- Constructeurs - destructeur

AirCleaner :: AirCleaner ( string idInput, const Coordinates& coordInput, time_t dateStartInput, time_t dateStopInput)
{
  id = std::move(idInput);
  coord = coordInput;
  dateStart = dateStartInput;
  dateStop= dateStopInput;
} //----- Fin de AirCleaner



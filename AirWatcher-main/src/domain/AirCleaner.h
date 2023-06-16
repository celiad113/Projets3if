/*************************************************************************
                           AirCleaner  -  object of an Air Cleaner
                             -------------------
    beginning            : 09/05/2023
    copyright            : (C) 2023 by Q41 : Adrien Morin, Isaline Foissey, Marie Roulier, Célia Djouadi et Nour ElJadiri
*************************************************************************/

//---------- Interface de la classe <AirCleaner> (fichier AirCleaner.h) ----------------
#if ! defined ( AIRCLEANER_H )
#define AIRCLEANER_H

//--------------------------------------------------- Interfaces utilisées
#include <cstring>
#include <map>
#include <ctime>
#include "Coordinates.h"

class AirCleaner
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    const std::string & getAirCleanerID() const;

    void setAirCleanerID(std::string anID);

    const Coordinates &getCoord() const;

    void setCoord(const Coordinates& coord);

    const time_t & getDateStart() const;

    void setDateStart(time_t aStart);

    const time_t & getDateStop() const;

    void setDateStop(time_t aStop);

//-------------------------------------------- Constructeurs - destructeur

    AirCleaner() = default;

    AirCleaner (std::string idInput, const Coordinates& coordInput, time_t dateStartInput, time_t dateStopInput);

    virtual ~AirCleaner ( ) = default;

//------------------------------------------------------------------ PRIVE
private:
    std::string id;
    Coordinates coord;
    time_t dateStart{};
    time_t dateStop{};
};


//-------------------------------- Autres définitions dépendantes de <AirCleaner>

#endif // AIRCLEANER_H
/*************************************************************************
                           Sensor  -  object of a sensor
                             -------------------
    beginning            : 09/05/2023
    copyright            : (C) 2023 by Q41 : Adrien Morin, Isaline Foissey, Marie Roulier, Célia Djouadi et Nour ElJadiri
*************************************************************************/

//---------- Interface de la classe <Sensor> (fichier Sensor.h) ----------------
#if ! defined ( SENSOR_H)
#define SENSOR_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <map>
#include <vector>

//------------------------------------------------------ Include personnel
#include "Coordinates.h"
#include "Measure.h"

//------------------------------------------------------------------------
// Rôle de la classe <Sensor>
//
//
//------------------------------------------------------------------------

class Sensor 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    const std::string &getId() const;

    const Coordinates &getCoord() const;

    bool isReliable() const;

    void setCoord(const Coordinates &coord);

    void setId(const std::string &id);

    void setReliable(bool reliable);

    const std::string &getPrivIndivId() const;

    void setPrivIndivId(const std::string &privIndivId);

    const std::vector<Measure> &getMeasure() const;

//-------------------------------------------- Constructeurs - destructeur
  Sensor ( const Sensor & aSensor );

  Sensor ( );

  Sensor(std::string id, const Coordinates& coord);

  Sensor(std::string aId, const Coordinates& someCoord, bool isReliable);

  virtual ~Sensor ( );

//------------------------------------------------------------------ PRIVE

protected:

    //----------------------------------------------------- Attributs protégés
    std::string id;

    Coordinates coord = Coordinates(.0, .0);

    std::string privIndivId;

    bool reliable{};

};

#endif // SENSOR_H

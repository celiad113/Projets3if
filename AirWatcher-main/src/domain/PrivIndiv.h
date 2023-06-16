/*************************************************************************
                           PrivIndiv  -  description
                             -------------------
    début                : 09/05/2023
    copyright            : (C) 2023 par Q41 : Adrien Morin, Isaline Foissey, Marie Roulier, Célia Djouadi et Nour ElJadiri
*************************************************************************/

//---------- Interface de la classe <PrivIndiv> (fichier PrivIndiv.h) ----------------
#if ! defined ( PRIVINDIV_H )
#define PRIVINDIV_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <map>
#include <vector>

//------------------------------------------------------ Include personnel
#include "Sensor.h"
#include "User.h"
#include "../data/FileManager.h"


//------------------------------------------------------------------------
// Rôle de la classe <PrivIndiv>
//
//
//
//------------------------------------------------------------------------

class PrivIndiv : public User
{
//----------------------------------------------------------------- PUBLIC

public:

//----------------------------------------------------- Méthodes publiques

    void printProvidedSensors() const;

    std::vector<Sensor> & getProvidedSensors();

    int & getPoints();

    void setProvidedSensors(std::vector<Sensor> provSens);

    void setPoints(int aPoint);

//-------------------------------------------- Constructeurs - destructeur
    PrivIndiv ( const PrivIndiv & aPrivIndiv );

    PrivIndiv();

    PrivIndiv ( const std::string &id, std::vector<Sensor> provSens );

    PrivIndiv ( const std::string &id, std::vector<Sensor> provSens, int points );

    virtual ~PrivIndiv ( );

//------------------------------------------------------------------ PRIVE

protected:

    //----------------------------------------------------- Attributs protégés
    std::vector<Sensor> providedSensors;

    int points{};

};

#endif // PRIVINDIV_H
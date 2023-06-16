/*************************************************************************
                           Provider  -  user of type provider
                             -------------------
    beginning            : 09/05/2023
    copyright            : (C) 2023 by Q41 : Adrien Morin, Isaline Foissey, Marie Roulier, Célia Djouadi et Nour ElJadiri
*************************************************************************/

//---------- Interface de la classe <Provider> (fichier Provider.h) ----------------
#if ! defined ( PROVIDER_H )
#define PROVIDER_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <map>
#include <vector>

//------------------------------------------------------ Include personnel
#include "AirCleaner.h"
#include "SuperUser.h"

class Provider : public SuperUser
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    void printAirCleaners() const;

    const std::string &getProviderId() const;

    void setProviderId(const std::string &providerId);

    const std::vector<AirCleaner> &getProvidedAc() const;

    void setProvidedAc(const std::vector<AirCleaner> &providedAc);

//-------------------------------------------- Constructeurs - destructeur
    Provider();

    explicit Provider(std::string providerID);

    Provider (const std::string & providerID, const std::vector<AirCleaner> & airCleaners);

    virtual ~Provider ( );

//------------------------------------------------------------------ PRIVE

protected:

    //----------------------------------------------------- Attributs protégés
    std::string providerID;

    std::vector<AirCleaner> providedAC;

};

#endif // PROVIDER_H
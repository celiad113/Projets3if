/*************************************************************************
                           Attribute  -  type of pollutant
                             -------------------
    beginning            : 09/05/2023
    copyright            : (C) 2023 by Q41 : Adrien Morin, Isaline Foissey, Marie Roulier, Célia Djouadi et Nour ElJadiri
*************************************************************************/

//---------- Interface de la classe <Attribute> (fichier Attribute.h) ----------------
#if ! defined ( Attribute_H )
#define Attribute_H

//--------------------------------------------------- Interfaces utilisées
#include <string>

class Attribute {
    //----------------------------------------------------------------- PUBLIC

public:
    //----------------------------------------------------- Méthodes publiques

    std::string getType();

    std::string getUnit();

    std::string getDescription();

    void setType(std::string id);

    void setUnit(std::string unite);

    void setDescription( std::string aDescription);

//-------------------------------------------- Constructeurs - destructeur

    Attribute ( const Attribute & anAttribute );

    Attribute ( );

    Attribute ( std::string unit, std::string type, std::string description );

    virtual ~Attribute ( );


//------------------------------------------------------------------ PRIVE

private:

//----------------------------------------------------- Attribut privés
    std::string type;

    std::string unit;

    std::string description;
};


#endif //ATTRIBUTE_H

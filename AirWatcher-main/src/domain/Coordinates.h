/*************************************************************************
                           Coordinates  -  longitude + latitude
                             -------------------
    beginning            : 09/05/2023
    copyright            : (C) 2023 by Q41 : Adrien Morin, Isaline Foissey, Marie Roulier, Célia Djouadi et Nour ElJadiri
*************************************************************************/

//---------- Interface de la classe <Coordinates> (fichier Coordinates.h) ----------------
#if ! defined ( COORDINATES_H )
#define COORDINATES_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <map>

class Coordinates
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    double Distance(const Coordinates& point) const;

    double getLongitude() const;

    void setLongitude(double longitude);

    double getLatitude() const;

    void setLatitude(double latitude);

//-------------------------------------------- Constructeurs - destructeur

    Coordinates();

    Coordinates(double latInput, double longInput);

    Coordinates (const Coordinates & coord);

    virtual ~Coordinates ( );

//------------------------------------------------------------------ PRIVE
private:

    double longitude;

    double latitude;

};

#endif // COORDINATES_H
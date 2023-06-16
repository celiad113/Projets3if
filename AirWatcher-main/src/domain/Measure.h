/*************************************************************************
                           Measure  -  a measurement of a pollutant
                             -------------------
    beginning            : 09/05/2023
    copyright            : (C) 2023 by Q41 : Adrien Morin, Isaline Foissey, Marie Roulier, Célia Djouadi et Nour ElJadiri
*************************************************************************/

//---------- Interface de la classe <Measure> (fichier Measure.h) ----------------
#if ! defined ( MEASURE_H )
#define MEASURE_H

//--------------------------------------------------- Interfaces utilisées
#include <cstring>
#include <map>
#include <ctime>


class Measure
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    const std::string & getSensorId() const;

    const time_t & getDateMeas() const;

    const std::string & getAttributeValue() const;

    double & getValue();

    void setSensorId(std::string anId);

    void setDateMeas(time_t aDate);

    void setAttributeType(std::string aType);

    void setValue(double aValue);

    friend struct MeasureComparator;
//-------------------------------------------- Constructeurs - destructeur

    Measure ( );

    Measure ( std::string  sensorIdInput, const time_t& dateMeasInput, std::string  attributeTypeInput, const double& valueInput);

    virtual ~Measure ( );

//------------------------------------------------------------------ PRIVE

protected:

    //----------------------------------------------------- Attributs protégés
    std::string sensorId;

    time_t dateMeas{};

    std::string attributeType;

    double value{};
};

struct MeasureComparator {
    bool operator()(const Measure& lhs, const Measure& rhs) const {
        return lhs.dateMeas < rhs.dateMeas;
    }
};


#endif // MEASURE_H
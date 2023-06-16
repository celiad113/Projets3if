/*************************************************************************
                           AppService  -  computations
                             -------------------
    beginning            : 09/05/2023
    copyright            : (C) 2023 by Q41 : Adrien Morin, Isaline Foissey, Marie Roulier, Célia Djouadi et Nour ElJadiri
*************************************************************************/

//---------- Interface de la classe <AppService> (fichier AppService.h) ----------------
#if ! defined ( APPSERVICE_H )
#define APPSERVICE_H

//--------------------------------------------------- Interfaces utilisées
#include <vector>
#include <string>
#include <utility>

#include "../domain/DataSet.h"
#include "../domain/Coordinates.h"
#include "../domain/Measure.h"
#include "../domain/Sensor.h"

//------------------------------------------------------------------------
// Rôle de la classe <AppService>
//
//
//
//------------------------------------------------------------------------


class AppService
{
    //----------------------------------------------------------------- PUBLIC

public:

    //----------------------------------------------------- Méthodes publiques

    double produceStatsMoment(time_t day, const Coordinates& coord, double radius, const std::vector<Measure>& measure = {});

    double computeMeanATMOIdx(std::vector<Measure> listMeasures);

    std::unordered_map<std::string, Sensor> getSensorsAround(const Coordinates& coord, double radius, const std::unordered_map<std::string, Sensor>& sensorMap = {} );

    std::vector<Measure> getMeasuresAtMoment(const std::unordered_map<std::string, Sensor>& sensorMap, time_t date);

    int getATMOIdx(double value, const std::vector<std::pair<int, int>>& breakpoints);

    std::pair<int, std::vector<double>> obsImpactLvlImprov(const std::string& AirCleanId, double radius, const std::vector<Measure>& measBefore = {}, const std::vector<Measure>& measAfter = {});

    std::string convertTimeToString(const time_t& time);

    //-------------------------------------------- Constructeurs - destructeur

    explicit AppService(DataSet& data);

    explicit AppService();

    virtual ~AppService();


    //------------------------------------------------------------------ PRIVE

private:

    DataSet * data{};
};

#endif // APPSERVICE_H

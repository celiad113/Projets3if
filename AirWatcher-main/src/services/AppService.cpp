/*************************************************************************
                           AppService  -  computations
                             -------------------
    beginning            : 09/05/2023
    copyright            : (C) 2023 by Q41 : Adrien Morin, Isaline Foissey, Marie Roulier, Célia Djouadi et Nour ElJadiri
*************************************************************************/

//---------- Réalisation de la classe <AppService> (fichier AppService.cpp) ----------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <string>
#include <map>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <set>
#include <chrono>

using namespace std;

//------------------------------------------------------ Include personnel
#include "AppService.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
double AppService::produceStatsMoment(time_t day, const Coordinates& coord, double radius, const vector<Measure>& measure)
{
    // Début de la mesure du temps
    auto startChrono = chrono::high_resolution_clock::now();

    // get all the reliable sensor around the circle of center coord and radius radius
    unordered_map<string, Sensor> sensors = getSensorsAround(coord, radius);
    if(sensors.empty()) return -1;

    // get all the measurements corresponding to the previous sensors
    vector<Measure> measures = (measure.empty()) ? getMeasuresAtMoment(sensors, day) : measure;
    if(measures.empty()) return -2;

    // compute the mean of the ATMO indices of the measurements above
    double res = computeMeanATMOIdx(measures);

    // Fin de la mesure du temps
    auto endChrono = chrono::high_resolution_clock::now();

    // Calcul de la durée écoulée
    auto duration = chrono::duration_cast<chrono::milliseconds>(endChrono - startChrono);

    // Affichage de la durée
    cout << "Execution time of produceStatsMoment : " << duration.count() << " milliseconds" << endl;

    return res;
}

double AppService::computeMeanATMOIdx(vector<Measure> listMeasures)
{
    if (listMeasures.empty())
    {
        return 0; // Return 0 if the list of measures is empty
    }

    // get the sensors list of the data set to check if the ones who took measurements belong to private individuals
    unordered_map<string, Sensor> allSensors = data->getSensorsList();
    // get the list of private individuals
    unordered_map<string, PrivIndiv>& allPrivIndiv = data->getUserList();

    // Define the breakpoints for each pollutant
    vector<pair<int, int>> OzoneBreakpoints = {{0, 29}, {30, 54}, {55, 79}, {80, 104}, {105, 129}, {130, 149}, {150, 179}, {180, 209}, {210, 239}, {240, INT_MAX}};
    vector<pair<int, int>> SO2Breakpoints = {{0, 39}, {40, 79}, {80, 119}, {120, 159}, {160, 199}, {200, 249}, {250, 299}, {300, 399}, {400, 499}, {500, INT_MAX}};
    vector<pair<int, int>> NO2Breakpoints = {{0, 29}, {30, 54}, {55, 84}, {85, 109}, {110, 134}, {135, 164}, {165, 199}, {200, 274}, {275, 399}, {400, INT_MAX}};
    vector<pair<int, int>> PM10Breakpoints = {{0, 6}, {7, 13}, {14, 20}, {21, 27}, {28, 34}, {35, 41}, {42, 49}, {50, 64}, {65, 79}, {80, INT_MAX}};
    double sumATMOIdx = 0;

    map<string, int> maxATMOSubIdxBySensorDay; // Store the maximum ATMOSubIdx for each sensor and day

    for (Measure& measure : listMeasures)
    {
        int ATMOSubIdx = 10;
        string sensorId = measure.getSensorId();

        string PrivIndivId = allSensors[sensorId].getPrivIndivId();
        if (!PrivIndivId.empty()) {
            allPrivIndiv[PrivIndivId].setPoints(allPrivIndiv[PrivIndivId].getPoints()+1);
        }

        string date;

        // Get the attribute type and value of the measure
        string attributeType = measure.getAttributeValue();
        double attributeValue = measure.getValue();

        // Calculate ATMO subindex based on the attribute value
        if (attributeType == "O3")
        {
            ATMOSubIdx = getATMOIdx(attributeValue, OzoneBreakpoints);
        }
        else if (attributeType == "SO2")
        {
            ATMOSubIdx = getATMOIdx(attributeValue, SO2Breakpoints);
        }
        else if (attributeType == "NO2")
        {
            ATMOSubIdx = getATMOIdx(attributeValue, NO2Breakpoints);
        }
        else if (attributeType == "PM10")
        {
            ATMOSubIdx = getATMOIdx(attributeValue, PM10Breakpoints);
        }

        date = convertTimeToString(measure.getDateMeas());

        // create unique key for sensor and day
        string sensorDayKey = sensorId;
        sensorDayKey += "_";
        sensorDayKey += date;

        if (maxATMOSubIdxBySensorDay.find(sensorDayKey) == maxATMOSubIdxBySensorDay.end())
        {
            // If the sensor and day combination is not present in the map, initialize it with the current ATMOSubIdx
            maxATMOSubIdxBySensorDay[sensorDayKey] = ATMOSubIdx;
        }
        else
        {
            // If the sensor and day combination is already present, update the value with the maximum ATMOSubIdx
            maxATMOSubIdxBySensorDay[sensorDayKey] = max(maxATMOSubIdxBySensorDay[sensorDayKey], ATMOSubIdx);
        }
    }

    // computing the mean of the ATMO indices
    for (const auto& entry : maxATMOSubIdxBySensorDay)
    {
        sumATMOIdx += entry.second; // Add the maximum ATMOSubIdx for each sensor and day to the sum
    }

    return sumATMOIdx / maxATMOSubIdxBySensorDay.size(); // Divide by the number of unique sensor and day combinations
}


int AppService::getATMOIdx(double value, const vector<pair<int, int>>& breakpoints)
{
    int i=1;
    for (const auto& range : breakpoints)
    {
        if (value >= range.first && value <= range.second)
        {
            return i;
        }
        i++;
    }

    return 10; // Invalid range so worst atmo sub index
}


unordered_map<string, Sensor> AppService::getSensorsAround(const Coordinates& coord, double radius, const unordered_map<string, Sensor>& sensorMap)
{
    const unordered_map<string, Sensor>& sensors = (sensorMap.empty()) ? data->getSensorsList() : sensorMap;

    unordered_map<string, Sensor> sensorsAround;

    for (const auto& pair : sensors)
    {
        const Sensor & sensor = pair.second; // Access the sensor object from the pair
        if (sensor.getCoord().Distance(coord) <= radius && sensor.isReliable())
        {
            sensorsAround[pair.first] = sensor;
        }
    }

    return sensorsAround;
}


vector<Measure> AppService::getMeasuresAtMoment(const unordered_map<string, Sensor>& sensorMap, time_t date)
{
    unordered_multimap<pair<string, time_t>, Measure, PairHash, PairEqual> measures = data->getMeasureList();

    vector<Measure> measuresAtMom;

    for( const auto & pair : sensorMap ){
        const auto & sensorId = pair.first;

        // On construit la combinaison capteur - date qu'on veut extraire
        auto desiredKey = make_pair(sensorId, date);

        // On définit la range d'extraction (possibilité d'avoir plusieurs mesures pour la même clé)
        auto range = measures.equal_range(desiredKey);

        for(auto it = range.first; it != range.second; ++it){
            Measure desiredMeasure = it->second;

            measuresAtMom.push_back(desiredMeasure);
        }
    }
    return measuresAtMom;
}

pair<int, vector<double>> AppService::obsImpactLvlImprov(const string& AirCleanId, double radius, const vector<Measure>& measBeforeParam, const vector<Measure>& measAfterParam)
{
    // Début de la mesure du temps
    auto startChrono = chrono::high_resolution_clock::now();

    unordered_map<string, AirCleaner> airCleanerIds = data->getAirCleanerList();
    AirCleaner airCl;

    auto it = airCleanerIds.find(AirCleanId);
    if (it != airCleanerIds.end()) {
        // air cleaner found
        airCl = it->second;
        vector<double> results;

        unordered_map<string, Sensor> listSensors = getSensorsAround(airCl.getCoord(), radius);
        if (listSensors.empty()) {
            // Fin de la mesure du temps
            auto endChrono = chrono::high_resolution_clock::now();

            // Calcul de la durée écoulée
            auto duration = chrono::duration_cast<chrono::milliseconds>(endChrono - startChrono);

            // Affichage de la durée
            cout << "Execution time of obsImpactLvlImprov : " << duration.count() << " milliseconds" << endl;
            return make_pair(-2, vector<double>()); // Return error code -2 and empty vector
        }

        // if passed as parameters, we keep them as they are, else we populate them
        // measurements the day just before the starting day of the air cleaner (thus -86400 seconds)
        vector<Measure> measBefore = (measBeforeParam.empty()) ? getMeasuresAtMoment(listSensors, airCl.getDateStart()-86400) : measBeforeParam;
        // measurements the day it finished its action (thus +43200 since dateStop are at midnight)
        vector<Measure> measAfter = (measAfterParam.empty()) ? getMeasuresAtMoment(listSensors, airCl.getDateStop()+43200) : measAfterParam;

        if (measAfter.empty() || measBefore.empty()){
            // Fin de la mesure du temps
            auto endChrono = chrono::high_resolution_clock::now();

            // Calcul de la durée écoulée
            auto duration = chrono::duration_cast<chrono::milliseconds>(endChrono - startChrono);

            // Affichage de la durée
            cout << "Execution time of obsImpactLvlImprov : " << duration.count() << " milliseconds" << endl;
            return make_pair(-3, vector<double>()); // Return error code -3 and empty vector
        }

        double meanATMObefore = computeMeanATMOIdx(measBefore);
        double meanATMOafter = computeMeanATMOIdx(measAfter);

        double diffATMO = meanATMOafter - meanATMObefore;

        // Add relevant values to the results vector
        results.push_back(meanATMObefore);
        results.push_back(meanATMOafter);
        results.push_back(diffATMO);

        // Fin de la mesure du temps
        auto endChrono = chrono::high_resolution_clock::now();

        // Calcul de la durée écoulée
        auto duration = chrono::duration_cast<chrono::milliseconds>(endChrono - startChrono);

        // Affichage de la durée
        cout << "Execution time of obsImpactLvlImprov : " << duration.count() << " milliseconds" << endl;

        return make_pair(0, results); // Return success code 0 and the results vector

    } else {
        // No air cleaner found with the given AirCleanId

        // Fin de la mesure du temps
        auto endChrono = chrono::high_resolution_clock::now();

        // Calcul de la durée écoulée
        auto duration = chrono::duration_cast<chrono::milliseconds>(endChrono - startChrono);

        // Affichage de la durée
        cout << "Execution time of obsImpactLvlImprov : " << duration.count() << " milliseconds" << endl;
        return make_pair(-1, vector<double>()); // Return error code -1 and empty vector
    }
}

string AppService::convertTimeToString(const time_t& time)
{
    tm* tmPtr = localtime(&time);
    stringstream ss;
    ss << put_time(tmPtr, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

//-------------------------------------------- Constructeurs - destructeur
AppService::AppService(DataSet& dataInput)
{
    data = &dataInput;
}

AppService::AppService() = default;

AppService::~AppService() = default;





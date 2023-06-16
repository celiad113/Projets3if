/*************************************************************************
                           DataSet  -  the data base
                             -------------------
    beginning            : 09/05/2023
    copyright            : (C) 2023 by Q41 : Adrien Morin, Isaline Foissey, Marie Roulier, Célia Djouadi et Nour ElJadiri
*************************************************************************/

//---------- Interface de la classe <DataSet> (fichier DataSet.h) ----------------
#if ! defined ( DATASET_H )
#define DATASET_H

//--------------------------------------------------- Interfaces utilisées
#include <cstring>
#include <map>
#include <vector>
#include <unordered_map>
#include <set>

#include "Sensor.h"
#include "Measure.h"
#include "AirCleaner.h"
#include "User.h"
#include "Provider.h"
#include "../data/FileManager.h"
#include "PrivIndiv.h"


class DataSet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void initSensorList();

    void initUserList();

    void initProviderList();

    void initMeasureList();

    void initAirCleanerList();

    const std::unordered_map<std::string, Sensor> &getSensorsList() const;

    const std::unordered_map<std::string, AirCleaner> &getAirCleanerList() const;

    void setSensorsList(const std::unordered_map<std::string, Sensor> &list);

    std::unordered_map<std::string, PrivIndiv> &getUserList();

    void setUserList(const std::unordered_map<std::string, PrivIndiv> &list);

    const std::unordered_map<std::string, Provider> &getProviderList() const;

    void setProviderList(const std::unordered_map<std::string, Provider> &list);

    const std::unordered_multimap<std::pair<std::string, time_t>, Measure, PairHash, PairEqual> &getMeasureList() const;

    void setMeasureList(const std::unordered_multimap<std::pair<std::string, time_t>, Measure, PairHash, PairEqual> &list);

    const FileManager &getFileManager() const;

    void setFileManager(const FileManager &manager);

//-------------------------------------------- Constructeurs - destructeur

    DataSet ( );

    DataSet( const std::string & path );

    virtual ~DataSet ( );

//------------------------------------------------------------------ PRIVE

private:
    FileManager fileManager;

    std::unordered_map<std::string, Sensor> sensorsList;

    std::unordered_map<std::string, PrivIndiv> userList;

    std::unordered_map<std::string, Provider> providerList;

    std::unordered_map<std::string, AirCleaner> airCleanerList;

    std::unordered_multimap<std::pair<std::string, time_t>, Measure, PairHash, PairEqual> measureList;
};

#endif // DATASET_H
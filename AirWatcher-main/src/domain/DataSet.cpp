/*************************************************************************
                           DataSet  -  the data base
                             -------------------
    beginning            : 09/05/2023
    copyright            : (C) 2023 by Q41 : Adrien Morin, Isaline Foissey, Marie Roulier, Célia Djouadi et Nour ElJadiri
*************************************************************************/

//---------- Réalisation de la classe <DataSet> (fichier DataSet.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//------------------------------------------------------ Include personnel
#include "DataSet.h"

using namespace std;

//----------------------------------------------------- Méthodes publiques

void DataSet::initSensorList() {
    sensorsList = fileManager.ParseSensorList();
}

void DataSet::initMeasureList() {
    measureList = fileManager.ParseMeasureList();
}

void DataSet::initAirCleanerList() {
    airCleanerList = fileManager.ParseAirCleanerList();
}

void DataSet::initUserList() {
    unordered_map<string, vector<string>> usersSensors = fileManager.ParseUserList();

    // For each user in the user-sensor list
    for (const auto &pair: usersSensors) {
        auto userId = pair.first;
        auto sensorsIds = pair.second;

        // Create a vector of Sensors
        vector<Sensor> userSensorList{};
        userSensorList.reserve(sensorsIds.size());

        // And use the sensorList to get all the sensors of a specific user
        for (const auto &sensor: sensorsIds) {
            sensorsList[sensor].setPrivIndivId(userId);
            userSensorList.push_back(sensorsList[sensor]);
        }

        // Call ParsePointsFile to get the points map
        map<string, int> pointsMap = fileManager.ParsePointsFile();

        int points;

        // Check if the ID exists in the points map
        if (pointsMap.count(userId) > 0) {
            // ID found, store the points value
            points = pointsMap[userId];
        } else {
            // ID not found, store 0
            points = 0;
        }

        PrivIndiv pindiv(userId, userSensorList, points);

        userList[userId] = pindiv;
    }
}

void DataSet::initProviderList() {
    unordered_map<string, vector<string>> providersAirCleaners = fileManager.ParseProviderList();

    for (const auto &pair: providersAirCleaners) {
        auto key = pair.first;
        auto airCleanersIds = pair.second;

        // We create the vector of aircleaners
        vector<AirCleaner> airCleanersList{};
        airCleanersList.reserve(airCleanersIds.size());

        // And then we get all the airCleanersIds provided by the same provider
        for (const auto &airCleanerId: airCleanersIds) {
            airCleanersList.push_back(airCleanerList[airCleanerId]);
        }

        Provider provider(key, airCleanersList);

        providerList[key] = provider;
    }
}

//---------------------------------------------------------------- Getters

const unordered_map<string, Sensor> &DataSet::getSensorsList() const {
    return sensorsList;
}

const unordered_map<string, AirCleaner> &DataSet::getAirCleanerList() const {
    return airCleanerList;
}

unordered_map<string, PrivIndiv> &DataSet::getUserList() {
    return userList;
}

const unordered_map<string, Provider> &DataSet::getProviderList() const {
    return providerList;
}

const unordered_multimap<std::pair<string, time_t>, Measure, PairHash, PairEqual> & DataSet::getMeasureList() const {
    return measureList;
}

const FileManager &DataSet::getFileManager() const {
    return fileManager;
}

//---------------------------------------------------------------- Setters

void DataSet::setSensorsList(const unordered_map<string, Sensor> &list) {
    sensorsList = list;
}

void DataSet::setUserList(const unordered_map<string, PrivIndiv> &list) {
    userList = list;
}

void DataSet::setProviderList(const unordered_map<string, Provider> &list) {
    providerList = list;
}

void DataSet::setMeasureList(const unordered_multimap<std::pair<string, time_t>, Measure, PairHash, PairEqual> & list) {
    measureList = list;
}

void DataSet::setFileManager(const FileManager &manager) {
    fileManager = manager;
}

//-------------------------------------------- Constructeurs - destructeur

DataSet::DataSet() {
    initSensorList();
    initUserList();
    initMeasureList();
    initAirCleanerList();
    initProviderList();
}

DataSet::DataSet(const string &path) {
    fileManager = FileManager(path);
    initSensorList();
    initUserList();
    initMeasureList();
    initAirCleanerList();
    initProviderList();
}

DataSet::~DataSet() = default;


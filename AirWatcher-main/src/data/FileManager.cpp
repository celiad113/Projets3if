/*************************************************************************
                           FileManager  -  parsing through files
                             -------------------
    beginning            : 09/05/2023
    copyright            : (C) 2023 by Q41 : Adrien Morin, Isaline Foissey, Marie Roulier, Célia Djouadi et Nour ElJadiri
*************************************************************************/

//---------- Réalisation de la classe <FileManager> (fichier FileManager.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <string>

using namespace std;

//------------------------------------------------------ Include personnel
#include "FileManager.h"

//----------------------------------------------------- Méthodes publiques

unordered_map<string, Sensor> FileManager::ParseSensorList()
{
    const string filePath = basePath + "sensors.csv";
    ifstream file(filePath);

    if (!file.is_open())
    {
        cerr << "Error when opening file " << filePath << endl;
        return {};
    }

    unordered_map<string, Sensor> sensors;

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string sensorId;
        double latitude, longitude;

        if (getline(ss, sensorId, ';') &&
            ss >> latitude &&
            ss.ignore() &&
            ss >> longitude)
        {
            Coordinates coord(latitude, longitude);
            Sensor sensor(sensorId, coord);
            sensors[sensorId] = sensor;
        }
        else
        {
            cout << "Error in format of the CSV file" << endl;
        }
    }

    file.close();

    return sensors;
}

unordered_multimap<std::pair<string, time_t>, Measure, PairHash, PairEqual> FileManager::ParseMeasureList()
{
    // Utilisation de fonction de hashage propres à l'objet
    unordered_multimap<std::pair<string,time_t>, Measure, PairHash, PairEqual> measureMap;

    const string filePath = basePath + "measurements.csv";
    ifstream file(filePath);

    if (!file)
    {
        cerr << "Error when opening file " << filePath << endl;
        return measureMap; // empty list
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string cell;

        string dateStr;
        string sensorId;
        string attributeType;
        string valueStr;

        // Utilisation de getline avec le délimiteur ';' pour extraire les valeurs de chaque cellule
        if (getline(ss, dateStr, ';') && getline(ss, sensorId, ';') &&
            getline(ss, attributeType, ';') && getline(ss, valueStr, ';'))
        {
            // Conversion des valeurs au format approprié
            time_t dateMeas = convertToTimeT(dateStr); // Conversion de la chaîne de caractères en time_t
            double value = stod(valueStr); // Conversion de la chaîne de caractères en un double

            // Création de l'objet Measure et ajout à la liste
            Measure measure(sensorId, dateMeas, attributeType, value);

            std::pair<string, time_t> key = std::make_pair(sensorId, dateMeas);

            measureMap.insert(std::make_pair(key, measure));
        }
        else
        {
            cout << "Error when reading a line of the file." << endl;
        }
    }

    file.close();

    return measureMap;
}


unordered_map<string, vector<string>> FileManager::ParseUserList()
{
    const string filePath = basePath + "users.csv";
    ifstream file(filePath);

    if (!file.is_open())
    {
        cerr << "Error when opening file " << filePath << endl;
        return {};
    }
    unordered_map<string, vector<string>> userList;

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);
        string cell;

        string userId;
        string sensor;

        while (getline(ss, cell, ';'))
        {
            if (userId.empty())
            {
                userId = cell;
            }
            else
            {
                sensor = cell;
            }
        }

        if (!userId.empty())
        {
            userList[userId].push_back(sensor); // Ajoute l'objet temporaire à la map
        }
    }

    file.close();

    return userList;
}

unordered_map<string, AirCleaner> FileManager::ParseAirCleanerList()
{
    unordered_map<string, AirCleaner> airCleanersMap{};
    const string filePath = basePath + "cleaners.csv";
    ifstream file(filePath);

    if (!file.is_open()) {
        cerr << "Error when opening file " << filePath << endl;
        return {};
    }

    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string cell;
        string id;
        double latitude, longitude;
        tm dateStart{}, dateStop{};

        if (getline(ss, id, ';') && getline(ss, cell, ';') && (latitude = stod(cell), true) &&
                getline(ss, cell, ';') && (longitude = stod(cell), true) &&
                getline(ss, cell, ';') && (istringstream(cell) >> get_time(&dateStart, "%Y-%m-%d %H:%M:%S"), true) &&
                getline(ss, cell, ';') && (istringstream(cell) >> get_time(&dateStop, "%Y-%m-%d %H:%M:%S"), true)) {

            Coordinates coord{latitude, longitude};
            time_t start = mktime(&dateStart);
            time_t stop = mktime(&dateStop);

            airCleanersMap[id] = AirCleaner(id, coord, start, stop);
        }
    }

    file.close();
    return airCleanersMap;
}


unordered_map<string, vector<string>> FileManager::ParseProviderList()
{
    unordered_map<string, vector<string>> providers;
    const string filePath = basePath + "providers.csv";

    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error when opening file " << filePath << endl;
        return providers;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string providerId, cleanerId;

        if (getline(ss, providerId, ';') && getline(ss, cleanerId, ';')) {
            // Vérifier si le providerID existe déjà dans l'unordered_map
            auto it = providers.find(providerId);
            if (it != providers.end()) {
                // Le provider existe déjà, ajouter le cleaner à son vecteur de cleanerIds
                it->second.push_back(cleanerId);
            } else {
                // Le provider n'existe pas encore, créer un nouveau vecteur avec le cleanerId
                vector<string> cleanerIds{ cleanerId };
                providers[providerId] = cleanerIds;
            }
        }
    }

    file.close();

    if(providers.empty()){
        cout << "Warning : the file "<< filePath << " is empty" << endl;
    }
    return providers;
}

time_t FileManager::convertToTimeT(const string& dateStr)
{
    struct tm tm = {};
    istringstream ss(dateStr);
    ss >> get_time(&tm, "%Y-%m-%d %H:%M:%S");

    if (!ss.fail())
    {
        time_t time = mktime(&tm);
        return time;
    }

    return 0; // Return 0 if the conversion fails
}

map<string, int> FileManager::ParsePointsFile() {
    map<string, int> pointsMap;

    const string fileName = basePath + "points.csv";
    ifstream file(fileName);

    if(!file.is_open()){
        return pointsMap;
    }
    string line;

    while (getline(file, line)) {
        istringstream iss(line);
        string id;
        string pointsStr;

        if (getline(iss, id, ';') && getline(iss, pointsStr, ';')) {
            try {
                int points = stoi(pointsStr);
                pointsMap[id] = points;
            } catch (const exception& e) {
                cerr << "Error parsing points for ID: " << id << endl;
            }
        }
    }

    file.close();
    return pointsMap;
}

void FileManager::UpdatePoints(const string& id, int points) {
    const string filename = basePath + "points.csv";

    //cout << "Call to UpdatePoints (id : " << id << " ; points : " << points << ")" << endl;

    // Read the existing file
    ifstream inputFile(filename);
    if (!inputFile) {
        //cerr << "Failed to open file: " << filename << endl;
        return;
    }

    // Create a temporary file for writing
    const string tempFileName = basePath + "points_temp.csv";
    ofstream tempFile(tempFileName);
    if (!tempFile) {
        //cerr << "Failed to create temporary file." << endl;
        inputFile.close();
        return;
    }

    bool idFound = false;
    string line;

    // Process each line in the input file
    while (getline(inputFile, line)) {
        istringstream iss(line);
        string currentId;
        string currentPoints;

        if (getline(iss, currentId, ';') && getline(iss, currentPoints, ';')) {
            //cout << "line: " << currentId << ";" << currentPoints << endl;
            if (currentId == id) {
                //cout << "correspondence found" << endl;
                // Update the points for the matching ID
                tempFile << id << ';' << points << ';' << endl;
                idFound = true;
            } else {
                // Copy the line as it is to the temporary file
                tempFile << line << endl;
            }
        }
    }

    // If the ID was not found, add a new line
    if (!idFound) {
        tempFile << id << ';' << points << ';' << endl;
    }

    // Close the file handles
    inputFile.close();
    tempFile.close();

    // Attempt to delete the file
    if (remove(filename.c_str()) != 0) {
        // Deletion failed
        //perror("Error deleting file");
    } else {
        // Deletion successful
        //printf("File deleted successfully\n");
    }

    // Rename the temporary file to the original filename
    if (rename( tempFileName.c_str() , filename.c_str()) != 0) {
        //cerr << "Failed to rename the temporary file." << endl;
    }
}

//-------------------------------------------- Constructeurs - destructeur

FileManager::FileManager() {
    basePath = "../src/data/csv/";
}

FileManager::FileManager ( const string & path ){
    basePath = path;
}

FileManager::~FileManager( ) = default;


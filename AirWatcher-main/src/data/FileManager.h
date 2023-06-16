/*************************************************************************
                           FileManager  -  description
                             -------------------
    début                : 09/05/2023
    copyright            : (C) 2023 par Q41 : Adrien Morin, Isaline Foissey, Marie Roulier, Célia Djouadi et Nour ElJadiri
*************************************************************************/

//---------- Interface de la classe <FileManager> (fichier FileManager.h) ----------------
#if ! defined ( FILEMANAGER_H )
#define FILEMANAGER_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <map>
#include <vector>
#include <unordered_map>
#include <set>
#include "../domain/Sensor.h"
#include "../domain/Coordinates.h"
#include "../domain/Measure.h"
#include "../domain/User.h"
#include "../domain/AirCleaner.h"
#include "../domain/Provider.h"


//------------------------------------------------------------- Constantes

// We define custom hash functions for pair <string, time_t> in order to use them for random access
struct PairHash {
    std::size_t operator()(const std::pair<std::string, std::time_t>& p) const {
        std::hash<std::string> stringHash;
        std::hash<std::time_t> timeHash;

        // Custom hash function for hashing pairs
        std::size_t hash = 17;
        hash = hash * 31 + stringHash(p.first);
        hash = hash * 31 + timeHash(p.second);
        return hash;
    }
};

// Define custom equality operator
struct PairEqual {
    template <typename T1, typename T2>
    bool operator()(const std::pair<T1, T2>& lhs, const std::pair<T1, T2>& rhs) const {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }
};

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <FileManager>
//
//
//
//------------------------------------------------------------------------

class FileManager
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    std::unordered_map<std::string, Sensor> ParseSensorList();

    std::unordered_map<std::string, std::vector<std::string>> ParseUserList();

    std::unordered_map<std::string, AirCleaner> ParseAirCleanerList();

    std::unordered_map<std::string, std::vector<std::string>> ParseProviderList();

    std::map<std::string, int> ParsePointsFile();

    std::unordered_multimap<std::pair<std::string, time_t>, Measure, PairHash, PairEqual> ParseMeasureList();

    void UpdatePoints(const std::string& id, int points);

    time_t convertToTimeT(const std::string& dateString);

//-------------------------------------------- Constructeurs - destructeur

    FileManager();

    explicit FileManager ( const std::string & path );

    virtual ~FileManager ( );

private:

    std::string basePath;

};



#endif // FILEMANAGER_H


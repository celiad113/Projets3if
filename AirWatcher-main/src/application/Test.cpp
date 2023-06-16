/*************************************************************************
                           Test  -  class for tests
                             -------------------
    beginning            : 09/05/2023
    copyright            : (C) 2023 by Q41 : Adrien Morin, Isaline Foissey, Marie Roulier, Célia Djouadi et Nour ElJadiri
*************************************************************************/

//---------- Réalisation du module <Test> (fichier Test.cpp) ------------

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cassert>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Test.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void Test::testGetATMOIdx(DataSet* dataSet){
    auto *app = new AppService(*dataSet);
    // Define the breakpoints for each pollutant
    vector<pair<int, int>> OzoneBreakpoints = {{0, 29}, {30, 54}, {55, 79}, {80, 104}, {105, 129}, {130, 149}, {150, 179}, {180, 209}, {210, 239}, {240, INT_MAX}};
    vector<pair<int, int>> SO2Breakpoints = {{0, 39}, {40, 79}, {80, 119}, {120, 159}, {160, 199}, {200, 249}, {250, 299}, {300, 399}, {400, 499}, {500, INT_MAX}};
    vector<pair<int, int>> NO2Breakpoints = {{0, 29}, {30, 54}, {55, 84}, {85, 109}, {110, 134}, {135, 164}, {165, 199}, {200, 274}, {275, 399}, {400, INT_MAX}};
    vector<pair<int, int>> PM10Breakpoints = {{0, 6}, {7, 13}, {14, 20}, {21, 27}, {28, 34}, {35, 41}, {42, 49}, {50, 64}, {65, 79}, {80, INT_MAX}};

    // O3
    assert(app->getATMOIdx(23.2, OzoneBreakpoints) == 1);
    cout << endl << "** Test 1 for getATMOIdx() passed **" << endl << endl;

    // SO2
    assert(app->getATMOIdx(123.2, SO2Breakpoints) == 4);
    cout << endl << "** Test 2 for getATMOIdx() passed **" << endl << endl;

    // NO2
    assert(app->getATMOIdx(138.7, NO2Breakpoints) == 6);
    cout << endl << "** Test 3 for getATMOIdx() passed **" << endl << endl;

    // PM10
    assert(app->getATMOIdx(67.8, PM10Breakpoints) == 9);
    cout << endl << "** Test 4 for getATMOIdx() passed **" << endl << endl;
}


void Test::testComputeMeanATMOIdx(DataSet* dataSet)
{
    auto *app = new AppService(*dataSet);

    vector<Measure> measures;

    // empty measure list so should print a message saying that the list is empty
    double atmo = app->computeMeanATMOIdx(measures);
    assert(atmo == 0);
    cout << endl << "** Test 1 for computeMeanATMOIdx() passed **" << endl << endl;

    string dateTimeString = "2019-01-01 12:00:00";
    time_t time = convertToTimeT(dateTimeString);

    Measure measure1("Sensor0", time, "O3", 50.25);
    Measure measure2("Sensor0", time, "NO2", 74.5);
    Measure measure3("Sensor0", time, "SO2", 41.5);
    Measure measure4("Sensor0", time, "PM10",44.75);
    // this gives an atmo index = 7

    Measure measure5("Sensor1", time, "O3", 180.25);
    Measure measure6("Sensor1", time, "NO2", 4.5);
    Measure measure7("Sensor1", time, "SO2", 151.5);
    Measure measure8("Sensor1", time, "PM10",44.75);
    // this gives an atmo index = 8

    measures.push_back(measure1);
    measures.push_back(measure2);
    measures.push_back(measure3);
    measures.push_back(measure4);
    measures.push_back(measure5);
    measures.push_back(measure6);
    measures.push_back(measure7);
    measures.push_back(measure8);

    atmo = app->computeMeanATMOIdx(measures);
    cout << "Mean ATMO index is: " << atmo << endl;
    // thus the mean ATMO index is equal to (7+8)/2 = 7.5
    assert(atmo == 7.5);
    cout << endl << "** Test 2 for computeMeanATMOIdx() passed **" << endl << endl;

    delete app;
}

void Test::testAddPointsToPrivIndiv(DataSet* dataSet){
    auto *app = new AppService(*dataSet);

    unordered_map<string, PrivIndiv> allPrivIndiv = dataSet->getUserList();

    int nbPoints1Avant = allPrivIndiv["User0"].getPoints();
    int nbPoints2Avant = allPrivIndiv["User1"].getPoints();

    vector<Measure> measures;

    string dateTimeString = "2019-01-01 12:00:00";
    time_t time = convertToTimeT(dateTimeString);

    Measure measure1("Sensor36", time, "O3", 50.25);
    Measure measure2("Sensor36", time, "NO2", 74.5);
    Measure measure3("Sensor36", time, "SO2", 41.5);
    Measure measure4("Sensor36", time, "PM10",44.75);
    // this gives an atmo index = 7

    Measure measure5("Sensor70", time, "O3", 180.25);
    Measure measure6("Sensor70", time, "NO2", 4.5);
    Measure measure7("Sensor70", time, "SO2", 151.5);
    Measure measure8("Sensor70", time, "PM10",44.75);
    // this gives an atmo index = 8

    measures.push_back(measure1);
    measures.push_back(measure2);
    measures.push_back(measure3);
    measures.push_back(measure4);
    measures.push_back(measure5);
    measures.push_back(measure6);
    measures.push_back(measure7);
    measures.push_back(measure8);

    double atmo = app->computeMeanATMOIdx(measures);
    cout << "Mean ATMO index is: " << atmo << endl;
    // thus the mean ATMO index is equal to (7+8)/2 = 7.5
    assert(atmo == 7.5);

    allPrivIndiv = dataSet->getUserList();

    string privIndivId1 = allPrivIndiv["User0"].getId();
    int nbPoints1 = allPrivIndiv["User0"].getPoints();
    string privIndivId2 = allPrivIndiv["User1"].getId();
    int nbPoints2 = allPrivIndiv["User1"].getPoints();

    cout << "After this query, the user who installed Sensor36, " << privIndivId1 << ", has now " << nbPoints1 << " points." << endl;
    cout << "After this query, the user who installed Sensor70, " << privIndivId2 << ", has now " << nbPoints2 << " points." << endl;

    assert(nbPoints1 == (nbPoints1Avant+4) && nbPoints2 == (nbPoints2Avant+4));
    cout << endl << "** Test 1 for adding points to private indiviudal passed **" << endl << endl;

    delete app;
}

void Test::testGetSensorsAround(DataSet* dataSet)
// on the 10 sensors, only sensors 2 and 3 are within a 150km radius from point(44,1)
{
    auto *app = new AppService(*dataSet);
    // list of sensors
    unordered_map<string, Sensor> sensors;

    sensors["Sensor0"] = Sensor("Sensor0", Coordinates(44, -1));
    sensors["Sensor1"] = Sensor("Sensor1", Coordinates(45, -0.3));
    sensors["Sensor2"] = Sensor("Sensor2", Coordinates(44, 0.5));
    sensors["Sensor3"] = Sensor("Sensor3", Coordinates(44, 1));
    sensors["Sensor4"] = Sensor("Sensor4", Coordinates(49, 1.8));
    sensors["Sensor5"] = Sensor("Sensor5", Coordinates(44, -2.5));
    sensors["Sensor6"] = Sensor("Sensor6", Coordinates(44, 3.2));
    sensors["Sensor7"] = Sensor("Sensor7", Coordinates(41, 3.9));
    sensors["Sensor8"] = Sensor("Sensor8", Coordinates(44, -4.6));
    sensors["Sensor9"] = Sensor("Sensor9", Coordinates(44, 5.3));


    // Call the getSensorsAround method with the made-up list
    Coordinates center(44, 1);
    double radius = 150.0;

    unordered_map<string, Sensor> sensorsAround = app->getSensorsAround(center, radius, sensors);

    if (sensorsAround.empty()) cout << "No sensors around for the specified area." << endl;
    else
    {
        // Print the sensors found within the radius
        cout << "Sensors within the radius:" << endl;
        for (const auto & pair : sensorsAround)
        {
            const auto & sensor = pair.second;
            cout << "Sensor ID: " << sensor.getId() << endl;
            cout << "Sensor Coordinates: (" << sensor.getCoord().getLongitude() << ", " << sensor.getCoord().getLatitude() << ")" << endl;
        }
    }

    assert(sensorsAround.size() == 2);
    cout << endl << "** Test 1 for getSensorsAround() passed **" << endl << endl;


    // Call the getSensorsAround method with the other made-up list
    sensors.clear();
    sensors["Sensor0"] = Sensor("Sensor0", Coordinates(44, -1));
    sensors["Sensor1"] = Sensor("Sensor1", Coordinates(45, -0.3));

    sensorsAround = app->getSensorsAround(center, radius, sensors);
    cout << "No matching sensors for the given area." << endl;

    assert(sensorsAround.empty());
    cout << endl << "** Test 2 for getSensorsAround() passed **" << endl << endl;

    // Call the getSensorsAround method with one unreliable sensor, and one reliable
    sensors.clear();
    sensors["Sensor0"] = Sensor("Sensor0", Coordinates(44, 0.5));
    sensors["Sensor1"] = Sensor("Sensor1", Coordinates(45, 1), false);

    sensorsAround = app->getSensorsAround(center, radius, sensors);

    assert(sensorsAround.size() == 1 && sensorsAround["Sensor0"].isReliable() == true);
    cout << endl << "** Test 3 for getSensorsAround() passed **" << endl << endl;

    // Call the getSensorsAround method with the entire list of sensors
    sensorsAround = app->getSensorsAround(center, radius);

    if(sensorsAround.empty()) cout << "No sensors around for the specified area." << endl;
    else
    {
        // Print the sensors found within the radius
        cout << "Sensors within the radius:" << endl;
        for (const auto & pair : sensorsAround)
        {
            const auto & sensor = pair.second;
            cout << "Sensor ID: " << sensor.getId() << endl;
            cout << "Sensor Coordinates: (" << sensor.getCoord().getLongitude() << ", " << sensor.getCoord().getLatitude() << ")" << endl;
        }
    }

    assert(sensorsAround.size() == 18);
    cout << endl << "** Test 4 for getSensorsAround() passed **" << endl << endl;

    delete app;

}

void Test::testGetMeasuresAtMoment(DataSet* dataSet)
{
    auto *app = new AppService(*dataSet);

    unordered_map<string, Sensor> sensors;

    sensors.emplace("Sensor0", Sensor("Sensor0",Coordinates(10,20)));

    string dateTimeString = "2019-01-01 12:00:00";
    time_t time = convertToTimeT(dateTimeString);

    vector<Measure> meas = app->getMeasuresAtMoment(sensors, time);

    cout << "measures :" << endl;
    for (Measure& measure : meas)
    {
        cout << "Sensor ID: " << measure.getSensorId() << endl;
        cout << "measure : " << convertTimeToString(measure.getDateMeas()) << ", " << measure.getAttributeValue() << ";" << measure.getValue()<< endl;
    }
    assert(meas.size() == 4 && meas[0].getDateMeas() == time);
    cout << endl << "** Test 1 for getMeasuresAtMoment() passed **" << endl << endl;

    dateTimeString = "2023-01-01 12:00:00";
    time = convertToTimeT(dateTimeString);
    meas = app->getMeasuresAtMoment(sensors, time);
    cout << "No reliable measurements related to this date." << endl;
    assert(meas.empty());
    cout << endl << "** Test 2 for getMeasuresAtMoment() passed **" << endl << endl;
}

void Test::testObsImpactLvlImprov(DataSet* dataSet){
    auto *app = new AppService(*dataSet);
    string AirCleanerId = "Cleaner5";
    double radius = 5.;

    pair<int,vector<double>> stats = app->obsImpactLvlImprov(AirCleanerId, radius);
    cout << "The AirCleaner " << AirCleanerId << " is not registered in our database." << endl;
    assert(stats.first == -1);
    cout << endl << "** Test 1 for obsImpactLvlImprov() passed **" << endl << endl;

    AirCleanerId = "Cleaner1";
    stats = app->obsImpactLvlImprov(AirCleanerId, radius);
    cout << "No matching sensors for the given area." << endl;
    assert(stats.first == -2);
    cout << endl << "** Test 2 for obsImpactLvlImprov() passed **" << endl << endl;

    radius = 100;
    vector<Measure> measBefore;
    vector<Measure> measAfter;
    string dateTimeString = "2019-02-01 12:00:00";
    time_t time = convertToTimeT(dateTimeString);

    Measure measure1("Sensor0", time, "O3", 50.25);
    Measure measure2("Sensor0", time, "NO2", 74.5);
    Measure measure3("Sensor0", time, "SO2", 41.5);
    Measure measure4("Sensor0", time, "PM10",44.75);
    // this gives an atmo index = 7

    dateTimeString = "2019-03-01 12:00:00";
    time = convertToTimeT(dateTimeString);

    Measure measure5("Sensor0", time, "O3", 13.25);
    Measure measure6("Sensor0", time, "NO2", 23.5);
    Measure measure7("Sensor0", time, "SO2", 18.5);
    Measure measure8("Sensor0", time, "PM10",29.75);
    // this gives an atmo index = 5

    measBefore.push_back(measure1);
    measBefore.push_back(measure2);
    measBefore.push_back(measure3);
    measBefore.push_back(measure4);
    measAfter.push_back(measure5);
    measAfter.push_back(measure6);
    measAfter.push_back(measure7);
    measAfter.push_back(measure8);

    stats = app->obsImpactLvlImprov(AirCleanerId, radius, measBefore, measAfter);

    double improvement = stats.second[2];
    // affichage
    cout << "Impact Level (ATMO index difference) of the AirCleaner " << AirCleanerId << " on a " << radius << " km radius:" << endl;
    cout << "-> ATMO index before action of AirCleaner = " << stats.second[0] << endl;
    cout << "-> ATMO index after action of AirCleaner = " << stats.second[1] << endl;
    cout << "-> ATMO level of improvement: " << (improvement > 0 ? "+" : "") << improvement << endl;

    assert(stats.first == 0);
    assert(stats.second[2] == -2);
    cout << endl << "** Test 3 for obsImpactLvlImprov() passed **" << endl << endl;
}

void Test::testProduceStatsMoment(DataSet *dataSet) {
    auto *app = new AppService(*dataSet);

    time_t day = convertToTimeT("2023-06-02");
    double longitude = 52;
    double latitude = 20;
    double radius = 0;

    double stats = app->produceStatsMoment(day, Coordinates(latitude, longitude), radius);
    cout << "No matching sensors for the given area." << endl;
    assert(stats == - 1);
    cout << endl << "** Test 1 for produceStatsMoment() passed **" << endl << endl;

    longitude = 1;
    latitude = 44;
    radius = 100;
    stats = app->produceStatsMoment(day, Coordinates(latitude, longitude), radius);
    cout << "No reliable measurements related to this date." << endl;
    assert(stats == -2);
    cout << endl << "** Test 2 for produceStatsMoment() passed **" << endl << endl;



    vector<Measure> measures;
    string dateTimeString = "2023-06-02 12:00:00";
    time_t time = convertToTimeT(dateTimeString);

    Measure measure1("Sensor0", time, "O3", 80.25);
    Measure measure2("Sensor0", time, "NO2", 74.5);
    Measure measure3("Sensor0", time, "SO2", 41.5);
    Measure measure4("Sensor0", time, "PM10",7.75);
    // this gives an atmo index = 4
    Measure measure5("Sensor1", time, "O3", 50.25);
    Measure measure6("Sensor1", time, "NO2", 74.5);
    Measure measure7("Sensor1", time, "SO2", 41.5);
    Measure measure8("Sensor1", time, "PM10",32.75);
    // this gives an atmo index = 5

    measures.push_back(measure1);
    measures.push_back(measure2);
    measures.push_back(measure3);
    measures.push_back(measure4);
    measures.push_back(measure5);
    measures.push_back(measure6);
    measures.push_back(measure7);
    measures.push_back(measure8);

    stats = app->produceStatsMoment(day, Coordinates(latitude, longitude), radius, measures);

    // affichage
    cout << "Mean of ATMO indexes computed with the sensors around:" << endl;
    cout << "\tCenter = (" << longitude << ", " << latitude << ")" << endl;
    cout << "\tRadius = " << radius << " km" << endl;
    cout << "\t-> Mean ATMO index = " << stats << endl;
    assert(stats == 4.5);
    cout << endl << "** Test 3 for produceStatsMoment() passed **" << endl << endl;
}


time_t Test::convertToTimeT(const string& dateStr)
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

string Test::convertTimeToString(const time_t& time)
{
    tm* tmPtr = localtime(&time);
    stringstream ss;
    ss << put_time(tmPtr, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

void Test::testUpdatePoints() {
    FileManager f = FileManager();
    f.UpdatePoints("User0", 1);
    f.UpdatePoints("User100", 10); // Doit rajouter une ligne dans le fichier
}

void Test::testParseProviders() {

    string path = "../src/data/test_data/";
    string fullPath = path + "providers.csv";
    stringstream buffer;

    // On redirige le flux de sortie vers un buffer custom
    streambuf* oldBuffer = cout.rdbuf(buffer.rdbuf());
    DataSet dataSet = DataSet(path);

    // Puis on restore l'ancien flux de sortie
    cout.rdbuf(oldBuffer);

    string output = buffer.str();

    string expected = "Warning : the file ../src/data/test_data/providers.csv is empty\n";

    cout << output;
    assert(output == expected);

    cout << "** Test 1 for ParseProvidersList() passed **" << endl << endl;

    string newFullPath = path + "unreachable_providers.csv";
    rename(fullPath.c_str(), newFullPath.c_str());

    stringstream buffer2;
    streambuf * oldBuffer2 = cerr.rdbuf(buffer2.rdbuf());
    dataSet.initProviderList();

    cerr.rdbuf(oldBuffer2);

    output = buffer2.str();

    expected = "Error when opening file ../src/data/test_data/providers.csv\n";

    cout << output;
    assert(output == expected);
    cout << "** Test 2 for ParseProvidersList() passed **" << endl << endl;
    rename(newFullPath.c_str(), fullPath.c_str());
}


//-------------------------------------------- Constructeurs - destructeur
Test::Test ( ) = default;

Test::~Test ( ) = default;


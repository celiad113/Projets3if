/*************************************************************************
                           IHM  -  lauching and console
                             -------------------
    beginning            : 09/05/2023
    copyright            : (C) 2023 by Q41 : Adrien Morin, Isaline Foissey, Marie Roulier, Célia Djouadi et Nour ElJadiri
*************************************************************************/

//---------- Réalisation du module <Main> (fichier Main.cpp) ------------

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <iostream>
#include <utility>
#include <regex>
#include <limits>
#include <iomanip>
#include <sstream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "IHM.h"

// initialisation du dataSet (mise en mémoire des données)
DataSet* dataSet = new DataSet();

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
int main()
{
    /// PLEASE REMOVE THIS BLOCK COMMENT TO RUN THE UNIT TESTS
    /*
    Test *test = new Test();
    test->testGetMeasuresAtMoment(dataSet);
    test->testAddPointsToPrivIndiv(dataSet);
    test->testProduceStatsMoment(dataSet);
    test->testObsImpactLvlImprov(dataSet);
    test->testGetATMOIdx(dataSet);
    test->testComputeMeanATMOIdx(dataSet);
    test->testGetSensorsAround(dataSet);
    test->testGetMeasuresAtMoment(dataSet);
    //test->testUpdatePoints();
    test->testParseProviders();
     */

    // get type user
    int typeOk = 0, userType;

    while (typeOk == 0){
        cout << "Enter the number corresponding to your user type: \n\t1. Member of Government Agency \n\t2. Private individual \n\t3. Provider \n\t4. Admin \n\t5. Exit" << endl;
        if (!(cin >> userType)) {
            cout << endl << "Please enter numbers only." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (userType)
        {
            case 1:
                handleGovernmentAgencyFunctionalities();
                break;

            case 2:
                handlePrivateIndividualFunctionalities();
                break;

            case 3:
                handleProviderFunctionalities();
                break;

            case 4:
                handleAdminFunctionalities();
                break;

            case 5:
                typeOk = 1;
                cout << "Exiting...";
                break;

            default:
                cout << endl << "Invalid user type. Choose a number between 1 and 4." << endl;
                break;
        }
    }

    return 0;
}

// fonctionnalités spécifiques à l'admin
void handleAdminFunctionalities()
{
    int choiceOk = 0, choice;

    while (choiceOk == 0){
        cout << endl << "Choose the corresponding number to what you which to do: \n\t1. Produce statistics (mean of air quality) in a specified circular area \n\t2. Exit" << endl;
        if (!(cin >> choice)) {
            cout << endl << "Please enter numbers only." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice)
        {
            case 1:
                produceStatistics();
                break;

            case 2:
                choiceOk = 1;
                cout << endl << "Going back to main menu..." << endl;
                break;

            default:
                cout << endl << "Invalid choice. Choose a number between 1 and 2." << endl;
                break;
        }
    }
}

// fonctionnalités spécifiques aux PrivIndiv
void handlePrivateIndividualFunctionalities()
{
    int choiceOk = 0, choice;

    while (choiceOk == 0){
        cout << endl << "Choose the corresponding number to what you which to do: \n\t1. Produce statistics (mean of air quality) in a specified circular area \n\t2. Exit" << endl;
        if (!(cin >> choice)) {
            cout << endl << "Please enter numbers only." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice)
        {
            case 1:
                produceStatistics();
                break;

            case 2:
                choiceOk = 1;
                cout << endl << "Going back to main menu..." << endl;
                break;

            default:
                cout << endl << "Invalid choice. Choose a number between 1 and 2." << endl;
                break;
        }
    }
}

// fonctionnalités spécifiques aux membres de Government Agency
void handleGovernmentAgencyFunctionalities()
{
    int choiceOk = 0, choice;

    while (choiceOk == 0){
        cout << endl << "Choose the corresponding number to what you which to do: \n\t1. Produce statistics (mean of air quality) in a specified circular area \n\t2. Observe the impact of an Air Cleaner \n\t3. Exit" << endl;
        if (!(cin >> choice)) {
            cout << endl << "Please enter numbers only." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice)
        {
            case 1:
                produceStatistics();
                break;

            case 2:
                observeImpact();
                break;

            case 3:
                choiceOk = 1;
                cout << endl << "Going back to main menu..." << endl;
                break;

            default:
                cout << endl << "Invalid choice. Choose a number between 1 and 3." << endl;
                break;
        }
    }
}

// fonctionnalités spécifiques aux fournisseurs
void handleProviderFunctionalities()
{
    int choiceOk = 0, choice;

    while (choiceOk == 0){
        cout << endl << "Choose the corresponding number to what you which to do: \n\t1. Produce statistics (mean of air quality) in a specified circular area \n\t2. Observe the impact of an Air Cleaner \n\t3. Exit" << endl;
        if (!(cin >> choice)) {
            cout << endl << "Please enter numbers only." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice)
        {
            case 1:
                produceStatistics();
                break;

            case 2:
                observeImpact();
                break;

            case 3:
                choiceOk = 1;
                cout << endl << "Going back to main menu..." << endl;
                break;

            default:
                cout << endl << "Invalid choice. Choose a number between 1 and 3." << endl;
                break;
        }
    }
}

void produceStatistics()
{
    int choiceOk = 0, choice;

    while (choiceOk == 0){
        cout << endl << "You chose to produce statistics (get the mean of air quality) in a specified circular area." << endl;
        cout << "Choose the corresponding number to what you which to do: \n\t1. Compute the mean of air quality in a specified circular area at a given MOMENT \n\t2. Compute the mean of air quality in a specified circular area at a given PERIOD OF TIME (not implemented) \n\t3. Exit" << endl;
        if (!(cin >> choice)) {
            cout << endl << "Please enter numbers only." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice)
        {
            case 1:
                cout << endl << "You chose to compute the mean of air quality at a given moment." << endl;
                produceStatsMoment();
                break;

            case 2:
                cout << endl << "You chose to compute the mean of air quality at a specified period of time." << endl;
                cout << "Not implemented yet" << endl;
                break;

            case 3:
                choiceOk = 1;
                cout << endl << "Going back to user menu..." << endl;
                break;

            default:
                cout << endl << "Invalid choice. Choose a number between 1 and 3." << endl;
                break;
        }
    }
}

void produceStatsMoment()
{
    time_t day;
    string dayStr;

    // choix du moment
    while (true) {
        cout << endl << "Enter the day (YYYY-MM-DD): ";
        cin >> dayStr;

        if (!isValidDateFormat(dayStr))
        {
            cout << endl << "Error: The date format YYYY-MM-DD must be respected" << endl;
            continue;
        }

        if (isDateAfterToday(dayStr))
        {
            cout << endl << "Error: Please enter a valid day." << endl;
            continue;
        }

        day = convertToTimeT(dayStr+" 12:00:00");

        // valid input, on sort de la loop
        break;
    }

    // choix des coordonnées
    double longitude;
    while (true) {
        cout << "Enter the longitude (it must be between -180 and 180): ";
        if (!(cin >> longitude)) {
            cout << endl << "Please enter numbers only." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (longitude < -180 || longitude > 180) {
            cout << endl << "Longitude is outside the valid range. \nLongitude: -180 to +180" << endl;
            continue;
        }

        // valid input, on sort de la loop
        break;
    }

    double latitude;
    while (true) {
        cout << "Enter the latitude (it must be between -90 and 90): ";
        if (!(cin >> latitude)) {
            cout << endl << "Please enter numbers only." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (latitude < -90 || latitude > 90) {
            cout << endl << "Latitude is outside the valid range. \nLatitude: -90 to +90" << endl;
            continue;
        }

        // valid input, on sort de la loop
        break;
    }

    // choix du rayon
    double radius;
    while (true) {
        cout << "Enter the radius in km (it must be between 0 and 20 000): ";
        if (!(cin >> radius)) {
            cout << endl << "Please enter numbers only." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (radius < 0 || radius > 20000) {
            cout << endl << "Radius is outside the valid range. \nRadius: 0 to 20 000" << endl;
            continue;
        }

        // valid input, on sort de la loop
        break;
    }


    auto* appServ = new AppService(*dataSet);

    double stats = appServ->produceStatsMoment(day, Coordinates(latitude, longitude), radius);
    if (stats == - 1) cout << endl << "No matching sensors for the given area." << endl;
    else if (stats == -2) cout << endl << "No reliable measurements related to this date." << endl;
    else {
        // display
        cout << endl << endl << "Mean of ATMO indexes computed with the sensors around:" << endl;
        cout << "\tCenter = (" << longitude << ", " << latitude << ")" << endl;
        cout << "\tRadius = " << radius << " km" << endl;
        cout << "\t-> Mean ATMO index = " << stats << endl;
    }
}


void observeImpact()
{
    int choiceOk = 0, choice;
    string choiceStr;

    while (choiceOk == 0){
        cout << endl << "You chose to observe the impact of an Air Cleaner." << endl;
        cout << "Choose the corresponding number to what you which to do: \n\t1. Get the radius of the cleaned zone (not implemented) \n\t2. Get the level of improvement in air quality \n\t3. Exit" << endl;
        // Read input as string
        cin >> choiceStr;

        // Check if input is digits only
        bool isNumber = true;
        for (char c : choiceStr) {
            if (!isdigit(c)) {
                isNumber = false;
                break;
            }
        }
        if (!isNumber) {
            cout << "Invalid user type. Choose a number between 1 and 3." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        // Convert input string into int
        choice = stoi(choiceStr);

        switch (choice)
        {
            case 1:
                cout << endl << "You chose to observe the impact of an Air Cleaner by getting the radius of the zone it cleaned." << endl;
                cout << "Not implemented yet" << endl;
                break;

            case 2:
                cout << endl << "You chose to observe the impact of an Air Cleaner by getting the level of improvement of air quality around it." << endl;
                obsImpactLvlImprov();
                break;

            case 3:
                choiceOk = 1;
                cout << endl << "Going back to user menu..." << endl;
                break;

            default:
                cout << endl << "Invalid choice. Choose a number between 1 and 3." << endl;
                break;
        }
    }
}

void obsImpactLvlImprov ()
{
    // choix du Air Cleaner
    string idAC;
    while (true) {
        cout << endl << "Enter the ID ('CleanerX', with X the number of the AirCleaner) of the AirCleaner around which you wish to observe the level of improvement: ";
        cin >> idAC;

        // Regular expression pattern pour vérifier qu'on a bien 'Cleaner' followed by one or more digits
        regex pattern("^Cleaner\\d+$");

        if (!regex_match(idAC, pattern)) {
            cout << endl << "Invalid ID. Please enter an ID in the format 'CleanerX', where X is the number of the AirCleaner." << endl;
            continue;
        }

        // valid input, on sort de la loop
        break;
    }

    // choix du rayon
    double radius;
    while (true) {
        cout << "Enter the radius in km (it must be between 0 and 20 000): ";
        if (!(cin >> radius)) {
            cout << endl << "Please enter numbers only." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (radius < 0 || radius > 20000) {
            cout << endl << "Radius is outside the valid range. \nRadius: 0 to 20 000" << endl;
            continue;
        }

        // valid input, on sort de la loop
        break;
    }

    auto* appServ = new AppService(*dataSet);
    pair<int,vector<double>> stats = appServ->obsImpactLvlImprov(idAC, radius);

    if (stats.first == -1)
        cout << endl << "The AirCleaner " << idAC << " is not registered in our database." << endl;
    else if (stats.first == -2)
        cout << endl << "No matching sensors for the given area." << endl;
    else if (stats.first == -3)
        cout << endl << "No reliable measurements related to this date." << endl;
    else {
        double improvement = stats.second[2];
        // affichage
        cout << endl << "Impact Level (ATMO index difference) of the AirCleaner " << idAC << " on a " << radius << " km radius:" << endl;
        cout << "-> ATMO index before action of AirCleaner = " << stats.second[0] << endl;
        cout << "-> ATMO index after action of AirCleaner = " << stats.second[1] << endl;
        cout << "-> ATMO level of improvement: " << (improvement > 0 ? "+" : "") << improvement << endl;    }
}


// fonction pour vérifier si la date est après aujourd'hui
bool isDateAfterToday(const string& date)
{
    time_t currentTime = time(nullptr);
    tm* now = localtime(&currentTime);

    int currentYear = now->tm_year + 1900;
    int currentMonth = now->tm_mon + 1;
    int currentDay = now->tm_mday;

    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));

    if (year > currentYear)
        return true;
    else if (year == currentYear && month > currentMonth)
        return true;
    else if (year == currentYear && month == currentMonth && day > currentDay)
        return true;

    return false;
}

// fonction pour vérifier que le format de la date est conforme
bool isValidDateFormat(const string& date)
{
    if (date.length() != 10)
        return false;

    if (date[4] != '-' || date[7] != '-')
        return false;

    // Check if the year, month, and day components are valid integers
    try {
        stoi(date.substr(0, 4));
        int month = stoi(date.substr(5, 2));
        if (month == 0 || month > 12)
            return false;
        int day = stoi(date.substr(8, 2));
        if (day == 0 || day > 31)
            return false;
    } catch (const exception& e) {
        return false;
    }

    return true;
}

time_t convertToTimeT(const string& dateStr)
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


/*************************************************************************
                           IHM  -  lauching and console
                             -------------------
    beginning            : 09/05/2023
    copyright            : (C) 2023 by Q41 : Adrien Morin, Isaline Foissey, Marie Roulier, Célia Djouadi et Nour ElJadiri
*************************************************************************/

//---------- Interface du module <IHM> (fichier IHM.h) -------------------
#if ! defined ( IHM_H )
#define IHM_H

//--------------------------------------------------- Interfaces utilisées
#include "../data/FileManager.h"
#include "../domain/DataSet.h"
#include "../services/AppService.h"
#include "Test.h"

//---------------------------------------------------- Fonctions publiques

int main ( );

void handleAdminFunctionalities ( );

void handlePrivateIndividualFunctionalities ( );

void handleGovernmentAgencyFunctionalities ( );

void handleProviderFunctionalities ( );

void observeImpact ( );

void produceStatistics ( );

void produceStatsMoment ( );

void obsImpactLvlImprov ( );

bool isDateAfterToday( const std::string& date );

bool isValidDateFormat( const std::string& date );

time_t convertToTimeT( const std::string& dateStr );

#endif // IHM_H
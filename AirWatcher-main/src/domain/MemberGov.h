/*************************************************************************
                           MemberGov  -  user of type member of a government agency
                             -------------------
    beginning            : 09/05/2023
    copyright            : (C) 2023 by Q41 : Adrien Morin, Isaline Foissey, Marie Roulier, Célia Djouadi et Nour ElJadiri
*************************************************************************/

//---------- Interface de la classe <MemberGov> (fichier MemberGov.h) ----------------
#ifndef MEMBERGOV_H
#define MEMBERGOV_H

//--------------------------------------------------- Interfaces utilisées
#include <cstring>

//------------------------------------------------------ Include personnel
#include "SuperUser.h"

class MemberGov : public SuperUser
{
//----------------------------------------------------------------- PUBLIC

public:

//-------------------------------------------- Constructeurs - destructeur

    MemberGov ();

    virtual ~MemberGov( );
};

//-------------------------------- Autres définitions dépendantes de <MemberGov>



#endif //MEMBERGOV_H

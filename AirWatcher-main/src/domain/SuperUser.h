/*************************************************************************
                           SuperUser  -  type of User
                             -------------------
    beginning            : 09/05/2023
    copyright            : (C) 2023 by Q41 : Adrien Morin, Isaline Foissey, Marie Roulier, Célia Djouadi et Nour ElJadiri
*************************************************************************/

//---------- Interface de la classe <SuperUser> (fichier SuperUser.h) ----------------
#if ! defined ( SUPERUSER_H )
#define SUPERUSER_H

//------------------------------------------------------ Include personnel
#include "User.h"

class SuperUser : public User
{
//----------------------------------------------------------------- PUBLIC

public:

//-------------------------------------------- Constructeurs - destructeur

    SuperUser ( );

    virtual ~SuperUser ( );

};

#endif // SUPERUSER_H
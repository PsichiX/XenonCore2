/*
	Name:			XenoN Core 2
	Version:		2.0.0.0 Frozen Eye
	Update:			2011-06-04
	Copyright:		Copyright © 2007-2011 XenoN Core by PsichiX. All rights reserved.
	Author:			PsichiX
	Website:		http://www.xenon.psichix.com
	Description:	XenoN Core 4D World Engine
*/

/*
	== EN ==
	This file is part of Xenon Core Engine.
	You may distribute it further, but you can not modify it.
	Please do not use in modified form.
	The principles of XenoN Core License available in the file LICENSE_CORE_EN.TXT or visit: http://www.xenon.psichix.com.

	== PL ==
	Ten plik jest czescia XenoN Core Engine.
	Mozesz go rozpowszechniac dalej, jednak nie mozesz go modyfikowac.
	Nalezy uzytkowac w nie zmodyfikowanej formie.
	Nalezy przestrzegac zasad Licencji XenoN Core dostepnej w pliku LICENSE_CORE_PL.TXT oraz na stronie: http://www.xenon.psichix.com.
*/

#ifndef _XE_TIME_H_
#define _XE_TIME_H_

#include "../XenonCore2.h"


//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{

/*--- XeTime ---*/
/*! Klasa operacji na czasie. Singleton. */
class XeTime
{
private:
XeTime();
XeTime(const XeTime&);
LARGE_INTEGER Freq;
bool UseQPC;
public:
//! Zwraca referencje na instancje.
static XeTime& Use();
/*! Zwraca aktualny czas systemu (sekundy od uruchomienia systemu).
\return Sekundy.
*/
static float GetSecs();
/*! Zwraca aktualny czas systemu o podwojnej czulosci (sekundy od uruchomienia systemu).
\return Sekundy.
*/
static double GetSecsSens();
/*! Zwraca aktualny czas systemu (milisekundy od uruchomienia systemu).
\return Milisekundy.
*/
static LONGLONG GetMilisecs();
};

} // XeCore


#endif // _XE_TIME_H_

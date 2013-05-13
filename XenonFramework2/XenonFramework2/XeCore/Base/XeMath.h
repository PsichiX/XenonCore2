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

#ifndef _XE_MATH_H_
#define _XE_MATH_H_

#include "../XenonCore2.h"

#define MATH_LENGTH(x,y,z)				(sqrt((x*x)+(y*y)+(z*z)))
#define MATH_LENGTHDIR_X(length,dir)	(length*cos(XeMath::DegToRad(dir)))
#define MATH_LENGTHDIR_Y(length,dir)	(length*sin(XeMath::DegToRad(dir)))
#define MATH_DIRECTION_2D(x,y)			(XeMath::RadToDeg(atan2(y,x)))
#define MATH_DIRECTION_ALPHA(x,y,z)		(MATH_DIRECTION_2D(x,y))
#define MATH_DIRECTION_BETA(x,y,z)		(MATH_DIRECTION_2D(MATH_LENGTH(x,y,0),z));

//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{

/*--- XeMath ---*/
/*! Klasa podstawowych operacji matematycznych. */
class XeMath
{
public:
/*! Zamienia stopnie na radiany.
\param deg Stopnie.
\return Radiany.
*/
static double DegToRad(double deg);
static float DegToRad(float deg);
/*! Zamienia radiany na stopnie.
\param rad Radiany.
\return Stopnie.
*/
static double RadToDeg(double rad);
static float RadToDeg(float rad);
/*! Wylicza pseudolosowa wartosc.
\param range Zakres wartosci liczony od 0.
\return Wartosc pseudolosowa.
*/
static double Random(double range=0);
/*! Resetuje ziarno losowania pseudolosowych liczb. */
static void RandomReset();
/*! Oblicza wartosc pomiedzy dwoma podanymi wartosciami, wzgledem wagi liczb (np. 0: pierwsza; 1: druga; 0.5: pomiedzy).
\param v1 Pierwsza wartosc.
\param v2 Druga wartosc.
\param amount Waga liczb.
\return Wyliczona wartosc.
*/
static double Amount(double v1,double v2,double amount);
/*! Umieszcza bit na danej pozycji.
\param data Wskaznik na dane.
\param bit Pozycja bitu.
*/
static void BitInclude(void* data,unsigned int bit);
/*! Zabiera bit z danej pozycji.
\param data Wskaznik na dane.
\param bit Pozycja bitu.
*/
static void BitExclude(void* data,unsigned int bit);
/*! Sprawdza bit na danej pozycji.
\param data Wskaznik na dane.
\param bit Pozycja bitu.
\return Wartosc bitu.
*/
static bool BitCheck(void* data,unsigned int bit);
};

} // XeCore


#endif // _XE_MATH_H_

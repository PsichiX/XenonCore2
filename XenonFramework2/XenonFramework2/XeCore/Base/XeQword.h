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

#ifndef _XE_QWORD_H_
#define _XE_QWORD_H_

#include "../XenonCore2.h"


//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{

/*! Klasa typu QWORD (64bit). */
class XeQword
{
public:
/*! Wartosc nizsza (32bit). */
unsigned int Low;
/*! Wartosc wyzsza (32bit). */
unsigned int High;
/*! Konstruktor kopiujacy.
\param h Wartosc wyzsza (32bit).
\param l Wartosc nizsza (32bit).
*/
XeQword(XeDword h=0,XeDword l=0);
/*! Operator porownania.
Sprawdza czy oba QWORD sa rowne.
\param value Wartosc do porownania.
\return true jesli oba QWORD sa rowne.
*/
bool operator== (XeQword& value);
/*! Operator porownania.
Sprawdza czy oba QWORD sa rozne.
\param value Wartosc do porownania.
\return true jesli oba QWORD sa rozne.
*/
bool operator!= (XeQword& value);
/*! Operator porownania.
Sprawdza czy QWORD jest wiekszy badz rowny niz drugi.
\param value Wartosc do porownania.
\return true jesli pierwszy QWORD jest wiekszy badz rowny niz drugi.
*/
bool operator>= (XeQword& value);
/*! Operator porownania.
Sprawdza czy QWORD jest mniejszy badz rowny niz drugi.
\param value Wartosc do porownania.
\return true jesli pierwszy QWORD jest mniejszy badz rowny niz drugi.
*/
bool operator<= (XeQword& value);
/*! Operator porownania.
Sprawdza czy QWORD jest wiekszy niz drugi.
\param value Wartosc do porownania.
\return true jesli pierwszy QWORD jest wiekszy niz drugi.
*/
bool operator> (XeQword& value);
/*! Operator porownania.
Sprawdza czy QWORD jest mniejszy niz drugi.
\param value Wartosc do porownania.
\return true jesli pierwszy QWORD jest mniejszy niz drugi.
*/
bool operator< (XeQword& value);
/*! Operator bitowy.
Wykonuje sume bitowa na obu QWORD.
\param value Wartosc.
\return QWORD wynikowy.
*/
XeQword operator| (XeQword value);
/*! Operator bitowy.
Wykonuje iloczyn bitowy na obu QWORD.
\param value Wartosc.
\return QWORD wynikowy.
*/
XeQword operator& (XeQword value);
/*! Operator bitowy.
Wykonuje roznice bitowa na obu QWORD.
\param value Wartosc.
\return QWORD wynikowy.
*/
XeQword operator^ (XeQword value);
/*! Operator bitowy przypisania.
Wykonuje przypisanie sumy bitowej obu QWORD.
\param value Wartosc.
\return QWORD wynikowy.
*/
XeQword operator|= (XeQword& value);
/*! Operator bitowy przypisania.
Wykonuje przypisanie iloczynu bitowego obu QWORD.
\param value Wartosc.
\return QWORD wynikowy.
*/
XeQword operator&= (XeQword& value);
/*! Operator bitowy przypisania.
Wykonuje przypisanie roznicy bitowej obu QWORD.
\param value Wartosc.
\return QWORD wynikowy.
*/
XeQword operator^= (XeQword& value);
};

} // XeCore

#endif // _XE_QWORD_H_
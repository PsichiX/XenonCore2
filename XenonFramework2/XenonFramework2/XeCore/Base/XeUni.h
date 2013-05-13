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

#ifndef _XE_UNI_H_
#define _XE_UNI_H_

#include "../XenonCore2.h"
#include "XeNumber.h"
#include "XeString.h"
#include "XeAssoc.h"


//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{

/*--- XeUni ---*/
/*! Klasa wartosci uniwersalnej (tekstowo-liczbowa). */
class XeUni
{
private:
void* Data;
unsigned char Type; // 0: undefined; 1: number; 2: string; 3: assoc;
public:
typedef XeAssoc< XeUni, XeUni > Assoc;
/*! Ustala czy pamiec bufora jest statyczna (jesli true to podczas niszczenia unii nie zostaje zwalniana pamiec bufora). */
bool Static;
/*! Konstruktor domyslny. */
XeUni();
/*! Konstruktor kopiujacy. */
XeUni(const XeUni& value);
/*! Konstruktor wypelniajacy. */
XeUni(XeNumber value);
/*! Konstruktor wypelniajacy. */
XeUni(XeString& value);
/*! Konstruktor wypelniajacy. */
XeUni(double value);
/*! Konstruktor wypelniajacy. */
XeUni(char* value);
/*! Konstruktor wypelniajacy. */
XeUni(Assoc& value);
/*! Destruktor. */
~XeUni();
/*! Pobiera wartosc liczbowa.
\return Wartosc liczbowa.
*/
XeNumber GetNumber();
/*! Pobiera wartosc tekstowa.
\return Wartosc tekstowa.
*/
XeString GetString();
/*! Pobiera wartosc liczbowa (double).
\return Wartosc liczbowa.
*/
double GetPureNumber();
/*! Pobiera wartosc tekstowa (cstring).
\return Wartosc tekstowa.
*/
char* GetPureString();
/*! Pobiera zawartosc tablicy asocjacyjnej.
\param result Referencja na docelowa tablice asocjacyjna.
*/
void GetAssoc(Assoc& result);
/*! Pobiera wskaznik na tablice asocjacyjna.
\return Wskaznik na tablice asocjacyjna.
*/
Assoc* GetPureAssoc();
/*! Zwraca typ przechowywanej wartosci.
\return Typ wartosci. Dostepne wartosci:<br>
'n': Liczbowy.<br>
's': Tekstowy.<br>
'a': Asocjacyjny.
*/
unsigned char GetType();
/*! Sprawdza czy ma typ niezdefiniowany.
\return true jesli typ niezdefiniowany.
*/
bool IsUndefined();
/*! Sprawdza czy ma typ liczbowy.
\return true jesli typ liczbowy.
*/
bool IsNumber();
/*! Sprawdza czy ma typ tekstowy.
\return true jesli typ tekstowy.
*/
bool IsString();
/*! Sprawdza czy ma typ asocjacyjny.
\return true jesli typ asocjacyjny.
*/
bool IsAssoc();
/*! Ustala wartosc liczbowa.
\param value Referencja na wartosc liczbowa.
*/
void SetNumber(XeNumber& value);
/*! Ustala wartosc tekstowa.
\param value Referencja na wartosc tekstowa.
*/
void SetString(XeString& value);
/*! Ustala zawartosc tablicy asocjacyjnej.
\param value Referencja na tablice asocjacyjna.
*/
void SetAssoc(Assoc& value);
/*! Kasuje wartosc. */
void Unset();
/*! Porownuje z inna wartoscia. */
bool Compare(XeUni& value);
/*! Operator przypisania.
\param value Wartosc uniwersalna.
*/
void operator= (const XeUni& value);
/*! Operator przypisania.
\param value Referencja na wartosc liczbowa.
*/
void operator= (XeNumber& value);
/*! Operator przypisania.
\param value Referencja na wartosc tekstowa.
*/
void operator= (XeString& value);
/*! Operator przypisania.
\param value Referencja na tablice asocjacyjna.
*/
void operator= (Assoc& value);
/*! Operator przypisania.
\param value Wartosc double.
*/
void operator= (double value);
/*! Operator przypisania.
\param value Wartosc cstring.
*/
void operator= (char* value);
/*! Operator rzutowania. */
operator XeNumber() const;
/*! Operator rzutowania. */
operator XeString() const;
/*! Operator rzutowania. */
operator double() const;
/*! Operator rzutowania. */
operator char*() const;
/*! Operator porownania.
\param value Wartosc uniwersalna.
*/
bool operator== (XeUni& value);
/*! Operator porownania.
\param value Wartosc uniwersalna.
*/
bool operator!= (XeUni& value);
/*! Operator dostepu do pola tablicy asocjacyjnej.
\param key Referencja na klucz.
\return Referencja na wartosc.
*/
XeUni& operator[] (XeUni& key);
};

} // XeCore

#endif // _XE_UNI_H_
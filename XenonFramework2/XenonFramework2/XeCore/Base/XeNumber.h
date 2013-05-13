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

#ifndef _XE_NUMBER_H_
#define _XE_NUMBER_H_

#include "../XenonCore2.h"


//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{

/*--- XeNumber ---*/
/*! Klasa liczby.
Bufor wartoœci liczbowej.
*/
class XeNumber
{
private:
double Value;
public:
/*! Konstruktor domyœlny. */
XeNumber();
/*! Konstruktor wypelniajacy. */
XeNumber(double val);
/*! Konstruktor wypelniajacy. */
XeNumber(int val);
/*! Zwraca double. */
double Get();
/*! Ustala wartoœæ. */
void Set(double val);
//! operator dodawania
XeNumber operator+ (XeNumber& n);
//! operator odejmowania
XeNumber operator- (XeNumber& n);
//! operator mnozenia
XeNumber operator* (XeNumber& n);
//! operator dzielenia
XeNumber operator/ (XeNumber& n);
//! operator dodawania
XeNumber& operator+= (XeNumber& n);
//! operator odejmowania
XeNumber& operator-= (XeNumber& n);
//! operator mnozenia
XeNumber& operator*= (XeNumber& n);
//! operator dzielenia
XeNumber& operator/= (XeNumber& n);
/*! Operator przypisania.
Ustala nowa wartosc.
\param val Wartosc double.
*/
double& operator= (double& val);
/*! Operator przypisania.
Ustala nowa wartosc.
\param val Wartosc float.
*/
float& operator= (float& val);
/*! Operator przypisania.
Ustala nowa wartosc.
\param val Wartosc int.
*/
int& operator= (int& val);
/*! Operator przypisania.
Ustala nowa wartosc.
\param val Wartosc unsigned int.
*/
unsigned int& operator= (unsigned int& val);
/*! Operator przypisania.
Ustala nowa wartosc.
\param val Wartosc short.
*/
short& operator= (short& val);
/*! Operator przypisania.
Ustala nowa wartosc.
\param val Wartosc unsigned short.
*/
unsigned int& operator= (unsigned short& val);
/*! Operator przypisania.
Ustala nowa wartosc.
\param val Wartosc byte (char).
*/
char& operator= (char& val);
/*! Operator przypisania.
Ustala nowa wartosc.
\param val Wartosc unsigned byte (char).
*/
unsigned char& operator= (unsigned char& val);
/*! Operator przypisania.
Ustala nowa wartosc.
\param val Wartosc bool.
*/
bool& operator= (bool& val);
/*! Operator porownania.
Sprawdza czy wartosci sa rowne.
\param val Wartosc liczbowa.
\return true jesli wartosci sa rowne.
*/
bool operator== (XeNumber& val);
/*! Operator porownania.
Sprawdza czy wartosci sa rowne.
\param val Wartosc double.
\return true jesli wartosci sa rowne.
*/
bool operator== (double& val);
/*! Operator porownania.
Sprawdza czy wartosci sa rowne.
\param val Wartosc float.
\return true jesli wartosci sa rowne.
*/
bool operator== (float& val);
/*! Operator porownania.
Sprawdza czy wartosci sa rowne.
\param val Wartosc int.
\return true jesli wartosci sa rowne.
*/
bool operator== (int& val);
/*! Operator porownania.
Sprawdza czy wartosci sa rowne.
\param val Wartosc unsigned int.
\return true jesli wartosci sa rowne.
*/
bool operator== (unsigned int& val);
/*! Operator porownania.
Sprawdza czy wartosci sa rowne.
\param val Wartosc short.
\return true jesli wartosci sa rowne.
*/
bool operator== (short& val);
/*! Operator porownania.
Sprawdza czy wartosci sa rowne.
\param val Wartosc unsigned short.
\return true jesli wartosci sa rowne.
*/
bool operator== (unsigned short& val);
/*! Operator porownania.
Sprawdza czy wartosci sa rowne.
\param val Wartosc byte (char).
\return true jesli wartosci sa rowne.
*/
bool operator== (char& val);
/*! Operator porownania.
Sprawdza czy wartosci sa rowne.
\param val Wartosc unsigned byte (char).
\return true jesli wartosci sa rowne.
*/
bool operator== (unsigned char& val);
/*! Operator porownania.
Sprawdza czy wartosci sa rowne.
\param val Wartosc bool.
\return true jesli wartosci sa rowne.
*/
bool operator== (bool& val);
/*! Operator porownania.
Sprawdza czy wartosci sa rozne.
\param val Wartosc liczbowa.
\return true jesli wartosci sa rowne.
*/
bool operator!= (XeNumber& val);
/*! Operator porownania.
Sprawdza czy wartosci sa rozne.
\param val Wartosc double.
\return true jesli wartosci sa rowne.
*/
bool operator!= (double& val);
/*! Operator porownania.
Sprawdza czy wartosci sa rozne.
\param val Wartosc float.
\return true jesli wartosci sa rowne.
*/
bool operator!= (float& val);
/*! Operator porownania.
Sprawdza czy wartosci sa rozne.
\param val Wartosc int.
\return true jesli wartosci sa rowne.
*/
bool operator!= (int& val);
/*! Operator porownania.
Sprawdza czy wartosci sa rozne.
\param val Wartosc unsigned int.
\return true jesli wartosci sa rowne.
*/
bool operator!= (unsigned int& val);
/*! Operator porownania.
Sprawdza czy wartosci sa rozne.
\param val Wartosc short.
\return true jesli wartosci sa rowne.
*/
bool operator!= (short& val);
/*! Operator porownania.
Sprawdza czy wartosci sa rozne.
\param val Wartosc unsigned short.
\return true jesli wartosci sa rowne.
*/
bool operator!= (unsigned short& val);
/*! Operator porownania.
Sprawdza czy wartosci sa rozne.
\param val Wartosc byte (char).
\return true jesli wartosci sa rowne.
*/
bool operator!= (char& val);
/*! Operator porownania.
Sprawdza czy wartosci sa rozne.
\param val Wartosc unsigned byte (char).
\return true jesli wartosci sa rowne.
*/
bool operator!= (unsigned char& val);
/*! Operator porownania.
Sprawdza czy wartosci sa rozne.
\param val Wartosc bool.
\return true jesli wartosci sa rowne.
*/
bool operator!= (bool& val);
/*! Operator konwersji.
Rzutuje wartosc na double.
*/
operator double() const;
/*! Operator konwersji.
Rzutuje wartosc na float.
*/
operator float() const;
/*! Operator konwersji.
Rzutuje wartosc na int.
*/
operator int() const;
/*! Operator konwersji.
Rzutuje wartosc na unsigned int.
*/
operator unsigned int() const;
/*! Operator konwersji.
Rzutuje wartosc na short.
*/
operator short() const;
/*! Operator konwersji.
Rzutuje wartosc na unsigned short.
*/
operator unsigned short() const;
/*! Operator konwersji.
Rzutuje wartosc na byte (char).
*/
operator char() const;
/*! Operator konwersji.
Rzutuje wartosc na unsigned byte (char).
*/
operator unsigned char() const;
/*! Operator konwersji.
Rzutuje wartosc na bool.
*/
operator bool() const;
};

} // XeCore

#endif // _XE_NUMBER_H_

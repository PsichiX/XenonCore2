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

#ifndef _XE_VECTOR_TEMPLATE_H_
#define _XE_VECTOR_TEMPLATE_H_

#include "../XenonCore2.h"
#include "XeNumber.h"

template<typename T>
class XeAngleVectorTemplate;

//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{

/*--- XeVectorTemplate ---*/
//! Klasa szablonu wektora
template<typename T>
class XeVectorTemplate
{
public:
//! Wspolrzedna X
T X;
//! Wspolrzedna Y
T Y;
//! Wspolrzedna Z
T Z;
//! Wspolczedna W
T W;
//! Konstruktor przypisujacy poczatkowe wartosci
XeVectorTemplate(T x=0,T y=0,T z=0,T w=1);
//! Przypisanie wartosci
void Set(T x=0,T y=0,T z=0,T w=1);
//! Zwraca dlugosc wektora
T Length();
//! Zwraca znormalizowana wartosc wektora
XeVectorTemplate<T> Normalize();
//! Zwraca minimum
XeVectorTemplate<T> Min(XeVectorTemplate<T>& v);
//! Zwraca maksimum
XeVectorTemplate<T> Max(XeVectorTemplate<T>& v);
//! Zwraca wektor ze zresetowanymi wybranymi komponentami
XeVectorTemplate<T> Without(unsigned int flags);
//! Zwraca wektor pomiedzy dwoma danymi, uwzgledniajac ich wagi.
XeVectorTemplate<T> Amount(XeVectorTemplate<T>& v,T amount);
//! Rzutuje wektory.
XeVectorTemplate<T> Project(XeVectorTemplate<T>& v);
//! Rzutuje na wektor sferyczny.
void ToAngle(T& alpha, T& beta);
//! Operator dodawania
XeVectorTemplate<T> operator+ (XeVectorTemplate<T>& v);
//! Operator dodawania
XeVectorTemplate<T> operator+ (XeNumber& n);
//! Operator odejmowania
XeVectorTemplate<T> operator- (XeVectorTemplate<T>& v);
//! Operator odejmowania
XeVectorTemplate<T> operator- (XeNumber& n);
//! Operator mnozenia
XeVectorTemplate<T> operator* (XeVectorTemplate<T>& v);
//! Operator mnozenia
XeVectorTemplate<T> operator* (XeNumber& n);
//! Operator dzielenia
XeVectorTemplate<T> operator/ (XeVectorTemplate<T>& v);
//! Operator dzielenia
XeVectorTemplate<T> operator/ (XeNumber& n);
//! Operator iloczynu wektorowego
XeVectorTemplate<T> operator^ (XeVectorTemplate<T>& v);
//! Operator iloczynu skalarnego
T operator% (XeVectorTemplate<T>& v);
//! Operator dodawania
XeVectorTemplate<T>& operator+= (XeVectorTemplate<T>& v);
//! Operator dodawania
XeVectorTemplate<T>& operator+= (XeNumber& n);
//! Operator odejmowania
XeVectorTemplate<T>& operator-= (XeVectorTemplate<T>& v);
//! Operator odejmowania
XeVectorTemplate<T>& operator-= (XeNumber& n);
//! Operator mnozenia
XeVectorTemplate<T>& operator*= (XeVectorTemplate<T>& v);
//! Operator mnozenia
XeVectorTemplate<T>& operator*= (XeNumber& n);
//! Operator dzielenia
XeVectorTemplate<T>& operator/= (XeVectorTemplate<T>& v);
//! Operator dzielenia
XeVectorTemplate<T>& operator/= (XeNumber& n);
//! Operator iloczynu wektorowego
XeVectorTemplate<T>& operator^= (XeVectorTemplate<T>& v);
//! Operator zmiany znaku
XeVectorTemplate<T>& operator- ();
//! Operator rownosci
bool operator== (XeVectorTemplate<T>& v);
//! Operator roznosci
bool operator!= (XeVectorTemplate<T>& v);
};

typedef XeVectorTemplate<double> XeVector;
typedef XeVectorTemplate<float> XeHalfVector;

#define XE_HALFTOVEC(val) XeVector((double)(val).X,(double)(val).Y,(double)(val).Z,(double)(val).W)
#define XE_VECTOHALF(val) XeHalfVector((float)(val).X,(float)(val).Y,(float)(val).Z,(float)(val).W)
#define XE_FORLINE(begin,end,as,size,offset,whennomove)	for(XeVector __d_i_r__=((end)-(begin)).Normalize(),__d_i_s__=XeVector(offset),__l_e_n__=XeVector(((end)-(begin)).Length()),as=(begin)+__d_i_r__*XeNumber(offset);(whennomove)?(__d_i_s__.X<=__l_e_n__.X):(__d_i_s__.X<__l_e_n__.X);__d_i_s__.X+=size,as+=__d_i_r__*XeNumber(size))
#define XE_FORLINEHALF(begin,end,as,size,offset,whennomove)	for(XeHalfVector __d_i_r__=((end)-(begin)).Normalize(),__d_i_s__=XeHalfVector(offset),__l_e_n__=XeHalfVector(((end)-(begin)).Length()),as=(begin)+__d_i_r__*XeNumber(offset);(whennomove)?(__d_i_s__.X<=__l_e_n__.X):(__d_i_s__.X<__l_e_n__.X);__d_i_s__.X+=size,as+=__d_i_r__*XeNumber(size))

/*--- XePerVertex ---*/
//! Struktura danych wierzcholka
struct XePerVertex
{
//! Koordynaty tekstury
XeHalfVector Coord;
//! Kolor
XeHalfVector Color;
//! Normalna (X)
float NormalX;
//! Normalna (Y)
float NormalY;
//! Normalna (Z)
float NormalZ;
//! Pozycja wierzcholka
XeHalfVector Vertex;
};

} // XeCore

#include "XeVectorTemplate.inl"

#endif // _XE_VECTOR_TEMPLATE_H_
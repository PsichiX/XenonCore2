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

#ifndef _XE_ANGLEVECTOR_TEMPLATE_H_
#define _XE_ANGLEVECTOR_TEMPLATE_H_

#include "../XenonCore2.h"

template<typename T>
class XeVectorTemplate;

//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{

/*--- XeAngleVectorTemplate ---*/
//! Klasa szablonu wektora sferycznego
template<typename T>
class XeAngleVectorTemplate
{
public:
//! Kat Alpha (os Z)
T Alpha;
//! Kat Beta (os Y)
T Beta;
//! Kat Gamma (os X)
T Gamma;
//! Dlugosc
T Length;
//! Konstruktor przypisujacy poczatkowe wartosci
XeAngleVectorTemplate(T alpha=0,T beta=0,T gamma=0,T length=0);
//! Przypisanie wartosci
void Set(T alpha=0,T beta=0,T gamma=0,T length=0);
//! Moduluje wartosci wzgledem innego wektora sferycznego.
void Mod(XeAngleVectorTemplate& angle);
//! Rzutuje na wektor.
void ToVector(T& x, T& y, T& z);
//! Operator dodawania
XeAngleVectorTemplate<T> operator+ (XeAngleVectorTemplate<T>& v);
//! Operator odejmowania
XeAngleVectorTemplate<T> operator- (XeAngleVectorTemplate<T>& v);
//! Operator mnozenia
XeAngleVectorTemplate<T> operator* (XeAngleVectorTemplate<T>& v);
//! Operator dzielenia
XeAngleVectorTemplate<T> operator/ (XeAngleVectorTemplate<T>& v);
//! Operator dodawania
XeAngleVectorTemplate<T>& operator+= (XeAngleVectorTemplate<T>& v);
//! Operator odejmowania
XeAngleVectorTemplate<T>& operator-= (XeAngleVectorTemplate<T>& v);
//! Operator mnozenia
XeAngleVectorTemplate<T>& operator*= (XeAngleVectorTemplate<T>& v);
//! Operator dzielenia
XeAngleVectorTemplate<T>& operator/= (XeAngleVectorTemplate<T>& v);
//! Operator zmiany znaku
XeAngleVectorTemplate<T>& operator- ();
//! Operator rownosci
bool operator== (XeAngleVectorTemplate<T>& v);
//! Operator roznosci
bool operator!= (XeAngleVectorTemplate<T>& v);
};

typedef XeAngleVectorTemplate<double> XeAngleVector;
typedef XeAngleVectorTemplate<float> XeAngleHalfVector;

} // XeCore

#include "XeAngleVectorTemplate.inl"

#endif // _XE_ANGLEVECTOR_TEMPLATE_H_
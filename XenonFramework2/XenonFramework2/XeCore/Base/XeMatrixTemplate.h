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

#ifndef _XE_MATRIX_TEMPLATE_H_
#define _XE_MATRIX_TEMPLATE_H_

#include "../XenonCore2.h"
#include "XeVectorTemplate.h"
#include "XeMath.h"


//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{

/*--- XeMatrixTemplate ---*/
//! Klasa szablonu macierzy 4x4.
template<typename T>
class XeMatrixTemplate
{
public:
//! Komorki macierzy.
T Cell[16];
//! Konstruktor domyslny.
XeMatrixTemplate();
/*! Ustala maciez jednostkowa. */
void Identity();
/*! Dodanie macierzy.
\param mat Macierz.
\return Macierz wynikowa.
*/
XeMatrixTemplate<T> Add(XeMatrixTemplate<T>& mat);
/*! Odejmmowanie macierzy.
\param mat Macierz.
\return Macierz wynikowa.
*/
XeMatrixTemplate<T> Substract(XeMatrixTemplate<T>& mat);
/*! Mnozenie macierzy przez skalar.
\param value Wartosc.
\return Macierz wynikowa.
*/
XeMatrixTemplate<T> ScalarMultiply(T value);
/*! Transpozycja macierzy.
\return Macierz wynikowa.
*/
XeMatrixTemplate<T> Transpose();
/*! Mnozenie macierzy przez macierz.
\param mat Macierz.
\return Macierz wynikowa.
*/
XeMatrixTemplate<T> Multiply(XeMatrixTemplate<T>& mat);
/*! Mnozenie macierzy przez vector.
\param vec Vector.
\return Vector wynikowy.
*/
XeVectorTemplate<T> Multiply(XeVectorTemplate<T>& vec);
/*! Mnozenie macierzy przez macierz.
\param mat Macierz.
\param ret Macierz wynikowa.
*/
void Multiply(XeMatrixTemplate<T>& mat,XeMatrixTemplate<T>& ret);
/*! Mnozenie macierzy przez vector.
\param vec Vector.
\param ret Vector wynikowy.
*/
void Multiply(XeVectorTemplate<T>& vec,XeVectorTemplate<T>& ret);
/*! Oblicza wyznacznik macierzy.
\return Wyznacznik.
*/
T Determinant();
/*! Oblicza odwrotnosc macierzy.
\return Macierz odwrotna.
*/
XeMatrixTemplate<T> Inverse();
/*! Przesuniecie.
\param x Wartosc X.
\param y Wartosc Y.
\param z Wartosc Z.
\return Macierz wynikowa.
*/
XeMatrixTemplate<T> Translate(T x,T y,T z);
/*! Skalowanie.
\param x Wartosc X.
\param y Wartosc Y.
\param z Wartosc Z.
\return Macierz wynikowa.
*/
XeMatrixTemplate<T> Scale(T x,T y,T z);
/*! Obrot w osi X.
\param angle Wartosc obrotu.
\return Macierz wynikowa.
*/
XeMatrixTemplate<T> RotateX(T angle);
/*! Obrot w osi Y.
\param angle Wartosc obrotu.
\return Macierz wynikowa.
*/
XeMatrixTemplate<T> RotateY(T angle);
/*! Obrot w osi Z.
\param angle Wartosc obrotu.
\return Macierz wynikowa.
*/
XeMatrixTemplate<T> RotateZ(T angle);
/*! Obrot w osiach XYZ.
\param alpha Wartosc obrotu w osi Z.
\param beta Wartosc obrotu w osi Y.
\param gamma Wartosc obrotu w osi X.
\return Macierz wynikowa.
*/
XeMatrixTemplate<T> Rotate(T alpha,T beta,T gamma);
/*! Przesuniecie.
\param x Wartosc X.
\param y Wartosc Y.
\param z Wartosc Z.
\param ret Macierz wynikowa.
*/
void Translate(T x,T y,T z,XeMatrixTemplate<T>& ret);
/*! Skalowanie.
\param x Wartosc X.
\param y Wartosc Y.
\param z Wartosc Z.
\param ret Macierz wynikowa.
*/
void Scale(T x,T y,T z,XeMatrixTemplate<T>& ret);
/*! Obrot w osi X.
\param angle Wartosc obrotu.
\param ret Macierz wynikowa.
*/
void RotateX(T angle,XeMatrixTemplate<T>& ret);
/*! Obrot w osi Y.
\param angle Wartosc obrotu.
\param ret Macierz wynikowa.
*/
void RotateY(T angle,XeMatrixTemplate<T>& ret);
/*! Obrot w osi Z.
\param angle Wartosc obrotu.
\param ret Macierz wynikowa.
*/
void RotateZ(T angle,XeMatrixTemplate<T>& ret);
/*! Obrot w osiach XYZ.
\param alpha Wartosc obrotu w osi Z.
\param beta Wartosc obrotu w osi Y.
\param gamma Wartosc obrotu w osi X.
\param ret Macierz wynikowa.
*/
void Rotate(T alpha,T beta,T gamma,XeMatrixTemplate<T>& ret);
/*! Operator dodawania. */
XeMatrixTemplate<T> operator+ (XeMatrixTemplate<T>& mat);
/*! Operator odejmowania. */
XeMatrixTemplate<T> operator- (XeMatrixTemplate<T>& mat);
/*! Operator mnozenia przez skalar. */
XeMatrixTemplate<T> operator* (T value);
/*! Operator mnozenia. */
XeMatrixTemplate<T> operator* (XeMatrixTemplate<T>& mat);
/*! Operator mnozenia przez Vektor. */
XeVectorTemplate<T> operator* (XeVectorTemplate<T>& vec);
};

typedef XeMatrixTemplate<double> XeMatrix;
typedef XeMatrixTemplate<float> XeHalfMatrix;

} // XeCore

#include "XeMatrixTemplate.inl"

#endif // _XE_MATRIX_TEMPLATE_H_
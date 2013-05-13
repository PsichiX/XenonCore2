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

#ifndef _XE_ASSOC_H_
#define _XE_ASSOC_H_

#include "../XenonCore2.h"
#include "XeElements.h"


//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{

/*--- XePair ---*/
//! Klasa pary klucz-wartosc.
template <typename TK,typename TV>
class XePair
{
public:
TK Key;
TV Value;
};

/*--- XeAssoc ---*/
//! Klasa tablicy asocjacyjnej.
template <typename TK,typename TV>
class XeAssoc
{
private:
XeElements< XePair<TK,TV> > Array;
public:
/*! Zwraca pierwszy element tablicy.
\return Element pola tablicy.
*/
XeElementPointer< XePair<TK,TV> > FirstPointer();
/*! Czysci zawartosc tablicy. */
void Clear();
/*! Kasuje element tablicy.
\param key Klucz.
\return true jesli operacja powiodla sie.
*/
bool Erase(TK key);
/*! Zmienia klucz danej pary.
\param oldkey Stary klucz.
\param newkey Nowy klucz.
\return true jesli operacja powiodla sie.
*/
bool Change(TK oldkey,TK newkey);
/*! Zwraca ilosc elementow w tablicy.
\return Ilosc elementow.
*/
unsigned int Size();
/*! Operator wy³uskania wartoœci po kluczu.
\param key Klucz.
*/
TV& operator[] (TK key);
/*! Sprawdza, czy istnieje element o danym kluczu.
\param key Klucz.
*/
bool Exists(TK key);
};

} // XeCore

#include "XeAssoc.inl"

#endif // _XE_ASSOC_H_
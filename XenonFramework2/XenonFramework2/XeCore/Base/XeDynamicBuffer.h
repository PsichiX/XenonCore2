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

#ifndef _XE_DYNAMIC_BUFFER_H_
#define _XE_DYNAMIC_BUFFER_H_

#include "../XenonCore2.h"
#include "XeAssoc.h"


//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{

/*--- XeDynamicBuffer ---*/
//! Klasa dynamicznych buforow
template<typename T>
class XeDynamicBuffer
{
private:
XeElements<XePair<T*,unsigned int> > Buffers;
public:
//! Defenicja typu iteratora.
typedef XeElementPointer<XePair<T*,unsigned int> > Iterator;
/*! Konstruktor domyslny. */
XeDynamicBuffer();
/*! Destruktor. */
~XeDynamicBuffer();
/*! Dodanie bufora.
\param source Wskaznik na tablice danych.
\param count Ilosc elementow do pobrania.
\return Element iteratora bufora.
*/
Iterator Add(T* source,unsigned int count);
/*! Zamiana bufora.
\param elm Element iteratora bufora.
\param source Wskaznik na tablice danych.
\param count Ilosc elementow do pobrania.
\return true jesli operacja powiodla sie.
*/
bool Replace(Iterator elm,T* source,unsigned int count);
/*! Usuniecie bufora.
\param elm Element iteratora bufora.
*/
void Erase(Iterator elm);
/*! Zwraca liczbe buforow.
\return Ilosc buforow.
*/
unsigned int Count();
/*! Zwraca wielkosc bufora, sumujac rozmiary wszystkich buforow.
\return Suma rozmiaru buforow.
*/
unsigned int Size();
/*! Zwraca wielkosc bufora w bajtach, sumujac rozmiary wszystkich buforow.
\return Suma rozmiaru buforow w bajtach.
*/
unsigned int Bytesize();
/*! Buduje jeden bufor laczac wszystkie i zwraca jego wskaznik lub wartosc NULL jesli nie utworzy bufora.
\param extra Ilosc dodatkowego miejsca dla elementow (liczba elementow).
\param offset Liczba bajtow przesuniecia (mniejsza badz rowna ilosci dodatkowego miejsca w bajtach).
\return Wskaznik na utworzony bufor.
*/
T* Build(unsigned int extra=0,unsigned int offset=0);
/*! Zwraca iterator pierwszego bufora.
\return Iterator pierwszego bufora.
*/
Iterator First();
/*! Zwraca iterator ostatniego bufora.
\return Iterator ostatniego bufora.
*/
Iterator Last();
/*! Usuwa wszystkie bufory. */
void Clear();
};

} // XeCore

#include "XeDynamicBuffer.inl"

#endif _XE_DYNAMIC_BUFFER_H_
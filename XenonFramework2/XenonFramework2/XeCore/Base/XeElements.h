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

#ifndef _XE_ELEMENTS_H_
#define _XE_ELEMENTS_H_

#include "../XenonCore2.h"


//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{

/*--- XeElements & XeElementBase & XeElementPointer ---*/
template<typename T> class XeElementBase;
template<typename T> class XeElementPointer;
template<typename T> class XeElements;

#define XE_FOREACH(type,container,as)	for(XeElementPointer< type > as=container.FirstPointer();!as.IsEmpty();as.Next())if(!as.IsEmpty())

/*-- XeElementBase --*/
template<typename T>
class XeElementBase
{
friend class XeElementPointer<T>;
friend class XeElements<T>;
private:
T data;
bool empty;
bool original;
XeElementBase<T> *parent;
XeElementBase<T> *prev;
XeElementBase<T> *next;
XeElements<T> *container;
public:
XeElementBase();
~XeElementBase();
};

/*-- XeElementPointer --*/
/*! Klasa wskaznika elementu kontenera elementow.
Przechowuje wskaznik elementu kontenera elementow.
*/
template<typename T>
class XeElementPointer
{
friend class XeElementBase<T>;
friend class XeElements<T>;
private:
bool empty;
bool original;
XeElementBase<T> *parent;
public:
/*! Konstruktor domyslny. */
XeElementPointer();
/*! Zwraca posredni klon elementu (przechowywany w kontenerze).
\return Klon obiektu.
*/
T iClone();
/*! Zwraca posredni wskaznik na element (przechowywany w kontenerze).
\return Wskaznik na obiekt.
*/
T* iPointer();
/*! Inkrementuje element (o pozycje w przod).
Jesli natrafi za koncowy element kontenera, to przyjmuje wartosc pustego elementu, lub pierwszego w liscie.
\param cycle Ustala, czy iteracja ma zataczac cykl.
*/
void Next(bool cycle=false);
/*! Dekrementuje element (o pozycje wstecz).
Jesli natrafi przed poczatkowy element kontenera, to przyjmuje wartosc pustego elementu, lub ostatniego w liscie.
\param cycle Ustala, czy iteracja ma zataczac cykl.
*/
void Prev(bool cycle=false);
/*! Sprawdza czy element jest pusty.
\return true jesli element jest pusty.
*/
bool IsEmpty();
/*! Dowiazuje sie do obiektu danego wskaznika elementu.
\param elm Referencja na wskaznik elementu.
*/
void RefPointer(XeElementPointer<T>& elm);
/*! Odwiazuje sie od kontenera. */
void Unref();
/*! Operator wyluskania.
Zwraca posredni wskaznik na obiekt (przechowywany w kontenerze).
\return Wskaznik na obiekt.
*/
T* operator-> ();
/*! Operator wyluskania.
Zwraca referencje na obiekt (przechowywany w kontenerze).
\return Referencja na obiekt.
*/
T& operator() ();
/*! Operator porownania.
Sprawdza czy oba wskazniki elementow sa rowne.
\param elm Wskaznik elementu.
\return true jesli wskazniki elementow sa rowne.
*/
bool operator== (XeElementPointer<T>& elm);
/*! Operator porownania.
Sprawdza czy oba wskazniki elementow sa rozne.
\param elm Wskaznik elementu.
\return true jesli wskazniki elementow sa rozne.
*/
bool operator!= (XeElementPointer<T>& elm);
/*! Operator preinkrementacji.
Inkrementuje element (o pozycje w przód).
\return Element.
*/
XeElementPointer<T> operator++ ();
/*! Operator predekrementacji.
Dekrementuje element (o pozycje w przód).
\return Element.
*/
XeElementPointer<T> operator-- ();
/*! Operator postinkrementacji.
Inkrementuje element (o pozycje w przód).
\return Element.
*/
XeElementPointer<T> operator++ (int);
/*! Operator postdekrementacji.
Dekrementuje element (o pozycje w przód).
\return Element.
*/
XeElementPointer<T> operator-- (int);
};

/*-- XeElements --*/
/*! Klasa kontenera elementow.
Przechowuje obiekty, do ktorych dostep daja klony oraz wskazniki elementow.
*/
template<typename T>
class XeElements
{
private:
XeElementBase<T>* first;
XeElementBase<T>* last;
unsigned int size;
public:
/*! Ustala czy pamiec kontenera jest statyczna (jesli true to podczas niszczenia kontenera nie zostaje zwalniana jego pamiec). */
bool Static;
/*! Ustala czy elementy maja byc dodawane poprzez klonowanie pamieci obiektu, a nie samego obiektu. (nie zaleca sie stosowac) */
bool AddingByCloning;
/*! Konstruktor domyslny. */
XeElements();
/*! Destruktor. */
~XeElements();
/*! Zwraca rozmiar kontenera.
\return Ilosc elementow w kontenerze.
*/
unsigned int Size();
/*! Czysci kontener. */
void Clear();
/*! Sortuje kontener funkcja foo.
\param foo Wskaznik na funkcje porownujaca 2 elementy (wartosc wieksza niz 0 oznacza wlasciwa kolejnosc, 0 oznacza identyczne wartosci, a mniej niz 0 oznacza niewlasciwa kolejnosc i koniecznosc zamiany miejsc).
*/
void Sort(int(*foo)(T*,T*));
/*! Zamienia elementy miejscami.
\param elm1 Pierwszy element.
\param elm2 Drugi element.
\return true jesli operacja powiodla sie.
*/
bool Swap(XeElementPointer<T> elm1,XeElementPointer<T> elm2);
/*! Przechwytuje element z innego kontenera (wskazniki na dane nie traca waznosci).
\param elm element do przechwycenia.
\return true jesli operacja powiodla sie.
*/
bool Capture(XeElementPointer<T> elm);
/*! Zwraca wskaznik pierwszego elementu kontenera.
\return Wskaznik elementu.
*/
XeElementPointer<T> FirstPointer();
/*! Zwraca wskaznik ostatniego elementu kontenera.
\return Wskaznik elementu.
*/
XeElementPointer<T> LastPointer();
/*! Dodaje obiekt do kontenera i zwraca jego wskaznik elementu.
\param value Obiekt.
\return Wskaznik elementu.
*/
XeElementPointer<T> AddPointer(const T& value);
/*! Dodaje obiekt do kontenera, tuz za okreslonym elementem i zwraca jego wskaznik elementu.
\param value Obiekt.
\param elm Wskaznik elementu.
\return Wskaznik elementu.
*/
XeElementPointer<T> InsertPointer(const T& value,XeElementPointer<T> elm);
/*! Usuwa obiekt z kontenera wskazywany przez wskaznik elementu.
\param elm Referencja na wskaznik elementu.
*/
void ErasePointer(XeElementPointer<T>& elm);
};

} // XeCore

#include "XeElements.inl"

#endif // _XE_ELEMENTS_H_
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

#ifndef _XE_SMART_H_
#define _XE_SMART_H_

#include "../XenonCore2.h"


//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{

/*--- XeSmart ---*/
template<typename T> class XeSmart;

/*! Klasa inteligentnego wskaznika.
Obiekt tego typu przechowuje wskaznik na dane tworzone dynamicznie i zwalnia zajmowana pamiec gdy zaden inny obiekt z niego nie korzysta.
*/
template<typename T>
class XeSmart
{
private:
bool Empty;
unsigned int* Counter;
T* Data;
public:
/*! Ustala czy pamiec obiektu jest statyczna (jesli true to podczas niszczenia wskaznika nie zostaje zwalniana pamiec obiektu) */
bool Static;
/*! Konstruktor domyslny. */
XeSmart();
/*! Konstruktor powiazujacy.
Powiazuje ze soba dany obiekt wskazywany przez wskaznik.
\param _pointer Wskaznik na obiekt.
*/
XeSmart(T* _pointer);
/*! Konstruktor klonujacy.
Klonuje dany obiekt i powiazuje go ze soba.
\param _clone Obiekt.
*/
XeSmart(const T _clone);
/*! Konstruktor powiazujacy.
Powiazuje ze soba obiekt innego inteligentnego wskaznika.
\param _smart Referencja na wskaznik inteligentny.
*/
XeSmart(const XeSmart<T>& _smart);
/*! Konstruktor powiazujacy.
Powiazuje ze soba obiekt innego inteligentnego wskaznika, poprzez wskaznik na niego.
\param _smartp Wskaznik na wskaznik inteligentny.
*/
XeSmart(XeSmart<T>* _smartp);
/*! Destruktor. */
~XeSmart();
/*! Powiazuje ze soba dany obiekt wskazywany przez wskaznik.
\param _pointer Wskaznik na obiekt.
\return true jesli operacja powiodla sie.
*/
bool RefPointer(T* _pointer);
/*! Klonuje dany obiekt i powiazuje go ze soba.
\param _clone Obiekt.
\return true jesli operacja powiodla sie.
*/
bool RefClone(const T _clone);
/*! Powiazuje ze soba obiekt innego inteligentnego wskaznika.
\param _smart Referencja na wskaznik inteligentny.
\return true jesli operacja powiodla sie.
*/
bool RefSmart(const XeSmart<T>& _smart);
/*! Powiazuje ze soba obiekt innego inteligentnego wskaznika, poprzez wskaznik na niego.
\param _smartp Wskaznik na wskaznik inteligentny.
\return true jesli operacja powiodla sie.
*/
bool RefSmartP(XeSmart<T>* _smartp);
/*! Odwiazuje siebie od obiektu. */
void Unref();
/*! Abstrakcyjne powiazanie (nie powiazuje z zadnym fizycznym obiektem, jednak zwieksza licznik powiazan).
\return true jesli operacja powiodla sie.
*/
bool AbstractRef();
/*! Abstrakcyjne odwiazanie (nie odwiazuje od siebie fizycznego obiektu, jednak zmniejsza licznik powiazan). */
void AbstractUnref();
/*! Zwraca wskaznik na obiekt powiazany. */
T* Pointer();
/*! Zwraca klona obiektu powiazanego. */
T Clone();
/*! Sprawdza czy inteligentny wskaznik jest pusty (czyli nie jest powiazany z zadnym obiektem).
\return true jesli wskaznik jest pusty.
*/
bool IsEmpty();
/*! Zwraca liczbe powiazan.
\return Liczba powiazan inteligentnego wskaznika.
*/
unsigned int Count();
/*! Operator powiazujacy.
Powiazuje ze soba dany obiekt wskazywany przez wskaznik.
\param _pointer Wskaznik na obiekt.
*/
void operator= (T* _pointer);
/*! Operator klonujacy.
Klonuje dany obiekt i powiazuje go ze soba.
\param _clone Obiekt.
*/
void operator= (const T _clone);
/*! Operator powiazujacy.
Powiazuje ze soba obiekt innego inteligentnego wskaznika.
\param _smart Referencja na wskaznik inteligentny.
*/
void operator= (const XeSmart<T>& _smart);
/*! Operator powiazujacy.
Powiazuje ze soba obiekt innego inteligentnego wskaznika, poprzez wskaznik na niego.
\param _smartp Wskaznik na wskaznik inteligentny.
*/
void operator= (XeSmart<T>* _smartp);
/*! Operator wyluskania.
Zwraca wskaznik na obiekt powiazany.
\return Wskaznik na obiekt powiazany.
*/
T* operator-> ();
};

} // XeCore

#include "XeSmart.inl"


#endif // _XE_SMART_H_

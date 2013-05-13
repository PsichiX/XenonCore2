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

#ifndef _XE_ARRAY_H_
#define _XE_ARRAY_H_

#include "../XenonCore2.h"


//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{

/*--- XeArray ---*/
/*! Klasa kontenera tablicy. */
template<typename T>
class XeArray
{
public:
enum SeekType
{
SET,
END,
CUR,
RET,
OFF
};
private:
unsigned int size;
T* data;
T* position;
T temporary;
public:
//! Ustala czy przy zniszczeniu obiektu ma nie zwalniac tablicy z pamieci.
bool Static;
/*! Konstruktor domyslny. */
XeArray();
/*! Konstruktor.
\param count Ilosc elementow do zarezerwowania.
*/
XeArray(unsigned int count);
/*! Destruktor. */
~XeArray();
/*! Sprawdza czy kontener jest pusty.
\return true jesli kontener jest pusty, false jesli nie jest.
*/
bool IsEmpty();
/*! Zwraca rozmiar kontenera.
\return Ilosc elementow zdolnych do przechowania.
*/
unsigned int Size();
/*! Zwraca rozmiar kontenera w bajtach.
\return Wielkosc danych zdolnych do przechowania.
*/
unsigned int SizeBytes();
/*! Usuwa pola tablicy i rezerwuje nowa ilosc pol.
\param count Ilosc pol do rezerwacji.
*/
void Reserve(unsigned int count);
/*! Zmienia rozmiar tablicy, kopiujac jej elementy.
\param count Ilosc pol.
\param offset Indeks pola od ktorego zaczyna kopiowac.
*/
void Resize(unsigned int count,unsigned int offset=0);
/*! Usuwa wszystkie pola tablicy. */
void Free();
/*! Zwraca wskaznik na tablice danych.
\param current Ustala czy ma zwrocic wskaznik na bierzaca pozycje kursora w tablicy.
\return Wskaznik na dane tablicy.
*/
T* Get(bool current=false);
/*! Zwraca aktualna pozycje kursora.
\return Pozycja w bajtach.
*/
unsigned int Current();
/*! Sprawdza czy kursor znajduje sie na koncu tablicy.
\return true jesli kursor znajduje sie na koncu tablicy.
*/
bool EndOf();
/*! Podlacza zewnetrzny bufor pod tablice.
\param buffer Wskaznik na bufor danych do podlaczenia.
\param count Liczba elementow bufora do podlaczenia.
*/
void Link(T* buffer,unsigned int count);
/*! Odlacza zewnetrzny bufor od tablicy i rezerwuje nowe pola.
\param count Liczba pol do zarezerwowania.
*/
void Unlink(unsigned int count=0);
/*! Ustala pozycje kursora w buforze tablicy.
\param pos Pozycja.
\param type Typ pozycji. Dostepne wartosci:<br>
SeekType::SET: Indeks pola wzgledem poczatku tablicy.<br>
SeekType::END: Indeks pola wzgledem konca tablicy.<br>
SeekType::CUR: Indeks pola wzgledem aktualnej pozycji kursora.<br>
SeekType::RET: Indeks pola wzgledem aktualnej pozycji kursora, przemieszczany wstecz.<br>
SeekType::OFF: Pozycja w bajtach wzgledem poczatku bufora tablicy.
*/
void Seek(unsigned int pos,SeekType type=SET);
/*! Odczytuje pola tablicy wzgledem aktualnej pozycji kursora.
\param dest Wskaznik na docelowa tablice danych.
\param count Ilosc pol do odczytania.
\return Ilosc odczytanych bajtow.
*/
unsigned int Read(T* dest,unsigned int count=1);
/*! Wczytuje pola tablicy wzgledem aktualnej pozycji kursora.
\param src Wskaznik na zrodlowa tablice danych.
\param count Ilosc pol do wczytania.
\return Ilosc wczytanych bajtow.
*/
unsigned int Write(T* src,unsigned int count=1);
/*! Odczytuje dane tablicy wzgledem aktualnej pozycji kursora.
\param dest Wskaznik na docelowy bufor danych.
\param sizebyte Ilosc bajtow do odczytania.
\return Ilosc odczytanych bajtow.
*/
unsigned int ReadBytes(void* dest,unsigned int sizebyte);
/*! Wczytuje dane tablicy wzgledem aktualnej pozycji kursora.
\param src Wskaznik na zrodlowy bufor danych.
\param sizebyte Ilosc bajtow do wczytania.
\return Ilosc wczytanych bajtow.
*/
unsigned int WriteBytes(void* src,unsigned int sizebyte);
/*! Operator dostepu do pola tablicy. */
T& operator[] (unsigned int index);
};

typedef XeArray<char> XeBuffer;

} // XeCore

#include "XeArray.inl"

#endif // _XE_ARRAY_H_
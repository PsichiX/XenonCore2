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

#ifndef _XE_FILE_H_
#define _XE_FILE_H_

#include "../XenonCore2.h"
#include "XeString.h"
#include "XeArray.h"


//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{

/*--- XeFile ---*/
//! Klasa bufora pliku.
class XeFile
{
private:
XeBuffer Buffer;
unsigned int CurrentSize;
public:
//! Ilosc bajtow rozszerzajacych bufor przy jego powiekszaniu.
unsigned int ReallocBytes;
/*! Konstruktor domyslny. */
XeFile();
/*! Laduje dane z pliku.
\param fname Sciezka do pliku.
\param offset Przesuniecie kursora w pliku.
\param size Ilosc bajtow do zaladowania.
\return true jesli operacja powiodla sie.
*/
bool Load(char* fname,unsigned int offset=0,unsigned int size=0);
/*! Zapisuje dane do pliku.
\param fname Sciezka do pliku.
\param offset Przesuniecie kursora w pliku.
\param size Ilosc bajtow do zaladowania.
\return true jesli operacja powiodla sie.
*/
bool Save(char* fname,unsigned int offset=0,unsigned int size=0);
/*! Dopisuje dane na koncu pliku.
\param fname Sciezka do pliku.
\return true jesli operacja powiodla sie.
*/
bool Append(char* fname);
/*! Wpisuje dane do bufora pliku.
\param buff Wskaznik na dane do wczytania.
\param size Rozmiar danych do wczytania.
\return Rozmiar wczytanych danych.
*/
unsigned int Write(void* buff,unsigned int size=1);
/*! Wpisuje cstring do bufora pliku.
\param str Wskaznik na cstring do wczytania.
\param nullterm Ustala czy wpisywany string ma byc zakonczony wartoscia NULL.
\return Rozmiar wczytanych danych.
*/
unsigned int WriteString(char* str,bool nullterm=false);
/*! Odczytuje dane z bufora pliku.
\param buff Wskaznik na bufor docelowy.
\param size Rozmiar danych do odczytania.
\return Rozmiar odczytanych danych.
*/
unsigned int Read(void* buff,unsigned int size=1);
/*! Odczytuje string z bufora pliku.
\param str Referencja na string docelowy.
\param nullterm Ustala czy odczytywany string jest zakonczony wartoscia NULL.
\return Dlugosc odczytanego stringu.
*/
unsigned int ReadString(XeString& str,bool nullterm=false);
/*! Ustawia kursor w buforze pliku.
\param offset Przesuniecie (w bajtach).
\param relative Ustala czy przesuniecie ma byc wzgledne.
\param reverse Ustala czy przesuniecie ma byc wsteczne.
*/
void Seek(unsigned int offset,bool relative=false,bool reverse=false);
/*! Sprawdza czy kursor w pliku osiagna koniec pliku.
\return true jesli kursor znajduje sie na koncu pliku.
*/
bool Eof();
/*! Zwraca rozmiar pliku lub rozmiar bufora pliku, jesli nie podano sciezki do pliku.
\param fname Sciezka do pliku.
\return Rozmiar (w bajtach).
*/
unsigned int Size(char* fname=0);
/*! Zwraca pozycje kursora w buforze pliku.
\return Pozycja (w bajtach).
*/
unsigned int Position();
/*! Zwraca wskaznik na dane bufora pliku.
\return Wskaznik na dane.
*/
void* Data();
/*! Zwalnia bufor pliku z pamieci. */
void Free();
/*! Zwraca wskaznik na bufor pliku.
\return Wskaznik na bufor pliku.
*/
XeBuffer* GetBuffer();
/*! Aktualizuje status bufora pliku. */
void Update();
};

} // XeCore

#endif // _XE_FILE_H_
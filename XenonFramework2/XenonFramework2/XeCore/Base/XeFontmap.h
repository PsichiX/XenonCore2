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

#ifndef _XE_FONTMAP_H_
#define _XE_FONTMAP_H_

#include "../XenonCore2.h"


//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{

/*--- XeFontmap ---*/
/*! Klasa mapy czcionki. */
class XeFontmap
{
public:
//! Klasa opisu znaku.
class Char
{
public:
//! Szerokosc.
float Width;
//! Wysokosc.
float Height;
//! Przesuniecie poziome.
float Xoffset;
//! Przesuniecie pionowe.
float Yoffset;
//! Przesuniecie pozycji po wypisaniu znaku.
float Advance;
//! Poczatkowy koordynat X.
float Xbegin;
//! Poczatkowy koordynat Y.
float Ybegin;
//! Koncowy koordynat X.
float Xend;
//! Koncowy koordynat Y.
float Yend;
/*! Konstruktor domyslny. */
Char();
};
//! Pozioma separacja.
float Xsep;
//! Pionowa separacja.
float Ysep;
//! Znak nowej linii;
char NewLine;
//! Rozmiar czcionki.
float Size;
//! Opis wszystkich znakow.
Char Desc[256];
/*! Konstruktor domyslny. */
XeFontmap();
/*! Kompiluje tekstowy opis mapy z pliku.
\param fname Sciezka do pliku.
\return true jesli operacja powiodla sie.
*/
bool Compile(char* fname);
/*! Kompiluje tekstowy opis mapy z pamieci.
\param buff Wskaznik na bufor danych tekstowe opisu.
\param size Rozmiar bufora (w bajtach).
\return true jesli operacja powiodla sie.
*/
bool CompileFromMemory(void* buff,unsigned int size);
};

} // XeCore

#endif // _XE_FONTMAP_H_
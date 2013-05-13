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

#ifndef _XE_WSTRING_H_
#define _XE_WSTRING_H_

#include "../XenonCore2.h"


//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{

/*--- XeWstring ---*/
/*! Klasa wide-stringa.
Bufor wartosci tekstowych.
*/
class XeWstring
{
private:
wchar_t* Text;
public:
/*! Ustala czy pamiec bufora jest statyczna (jesli true to podczas niszczenia stringa nie zostaje zwalniana pamiec bufora). */
bool Static;
/*! Konstruktor domyslny. */
XeWstring();
/*! Konstruktor wypelniajacy. */
XeWstring(const XeWstring& str);
/*! Konstruktor wypelniajacy. */
XeWstring(wchar_t* str);
/*! Konstruktor wypelniajacy. */
XeWstring(char* str);
/*! Destruktor. */
~XeWstring();
/*! Zwraca znak w buforze tekstu.
\param index Pozycja w buforze tekstu.
\param invert Okresla czy indeks zaczyna sie od konca tekstu.
\return Cstring zawartoœci bufora tekstu.
*/
wchar_t Index(unsigned int index,bool invert=false);
/*! Zwraca wcstring.
\param index Pozycja w buforze tekstu.
\param invert Okresla czy indeks zaczyna sie od konca tekstu.
\return Cstring zawartoœci bufora tekstu.
*/
wchar_t* Get(unsigned int index=0,bool invert=false);
/*! Zwraca wcstring.
\param result Wskaznik na docelowy bufor Wcstring.
\param buffsize Rozmiar bufora w bajtach.
\return true jesli operacja powiodla sie.
*/
bool GetAnsi(char* result,unsigned int buffsize);
/*! Kopiuje lancuch znakow do bufora tekstu.
\param str Wskaznik na wcstring.
*/
void Set(wchar_t* str);
/*! Kopiuje lancuch znakow do bufora tekstu.
\param str Wskaznik na wcstring.
*/
void Set(char* str);
/*! Kopiuje bufor znakow do bufora tekstu.
\param src Zrodlowy bufor znakow.
\param size Rozmiar bufora znakow (w bajtach).
*/
void Copy(wchar_t* src,unsigned int size);
/*! Ustala zawartosc bufora tekstu formatowanego.
\param str Wskaznik na wcstring formatu.
\param ... Kolejne wartosci.
*/
void Format(wchar_t* str,...);
/*! Rozdziela zawartosc bufora tekstu w miejscu znakow sep i wysyla je do tablicy dynamicznej buforow tekstu. Wazne aby po uzyciu zwolnic tablice z pamieci uzywajac operatora: delete[].
\param sep Wskaznik na wcstring ze znakami rozdzielajacymi.
\param count Referencja na wynik operacji (liczba elementow utworzonej tablicy).
\param block Wskaznikna wcstring ze znakami oznaczajacymi blok tekstu bez rozdzielania.
\return Wskaznik na tablice dynamiczna buforow tekstu jelsi operacja powiodla sie, lub wartosc 0 jesli nie.
*/
XeWstring* Explode(wchar_t* sep,unsigned int& count,wchar_t* block=0);
/*! Rozdziela zawartosc bufora w miejscu znakow sep i wysyla je do tablicy dynamicznej buforow tekstu. Wazne aby po uzyciu zwolnic tablice z pamieci uzywajac operatora: delete[].
\param buff Wskaznik na bufor.
\param size Rozmiar bufora w bajtach.
\param sep Wskaznik na wcstring ze znakami rozdzielajacymi.
\param count Referencja na wynik operacji (liczba elementow utworzonej tablicy).
\param block Wskaznikna wcstring ze znakami oznaczajacymi blok tekstu bez rozdzielania.
\return Wskaznik na tablice dynamiczna buforow tekstu jelsi operacja powiodla sie, lub wartosc 0 jesli nie.
*/
static XeWstring* ExplodeBuff(wchar_t* buff,unsigned int size,wchar_t* sep,unsigned int& count,wchar_t* block=0);
/*! Konwertuje liczbe w postaci tekstu na liczbe numeryczna.
\param out Wskaznik na zmienna do ktorej zostanie zapisany wynik.
\param deftype Jesli rozne od 0, ustala jakiego typu ma byc liczba bez symbolu.
\return true jesli operacja powiodla sie,
*/
bool Convert(void* out,int deftype=0);
/*! Zwraca typ liczby.
\return Typ (rozszerzenie) liczby.
*/
int ConvertType();
/*! Zwraca rozmiar liczby.
\return Rozmiar liczby w bajtach.
*/
unsigned int ConvertSize();
/*! Zamienia slowa formatowalne ("\") na odpowiednie znaki. */
void EscapeSeq();
/*! Zwraca dlugosc tekstu.
\return Rozmiar bufora tekstu.
*/
unsigned int Length();
/*! Zwraca dlugosc tekstu dla konwersji unicode.
\param extrachars Liczba dodatkowych znakow.
\return Rozmiar bufora tekstu unicode.
*/
unsigned int LengthUnicode(unsigned int extrachars=0);
/*! Szuka dany ciag znakow w stringu i zwraca jego pozycje.
\param offset Poczatkowa pozycja odczytu.
\param substr Szukany ciag znakow.
\param position Wskaznik na zwracana pozycje w stringu (jesli rozny od 0).
\return true jesli operacja powiodla sie.
*/
bool Find(unsigned int offset,wchar_t* substr,unsigned int* position=0);
/*! Szuka i pobiera ciag znakow pomiedzy poczatkiem a pierwszym znalezionym ciagiem znakow rozdzielajacych.
\param result Referencja na wynikowy string.
\param delim Ciag znakow rozdzielajacych.
\param offset Poczatkowa pozycja odczytu.
\return Pozycja na ktorej zakonczyl odczyt, od ktorej powinien szukac dalej, lub 0 jesli nie znaleziono ciagu, badz dalsze poszukiwania sa niemozliwe..
*/
unsigned int Search(XeWstring& result,wchar_t* delim,unsigned int offset=0);
/*! Zamienia wszystkie stare ciagi znakow na nowe.
\param result Referencja na wynikowy string.
\param oldstr Stary ciag znakow.
\param newstr Nowy ciag znakow.
\return Ilosc zamienionych ciagow znakow.
*/
unsigned int Replace(XeWstring& result,wchar_t* oldstr,wchar_t* newstr);
/*! Zamienia wszystkie stare znaki na nowe.
\param result Referencja na wynikowy string.
\param oldchar Stary znak.
\param newchar Nowy znak.
\return Ilosc zamienionych znakow.
*/
unsigned int ReplaceChars(XeWstring& result,wchar_t oldchar,wchar_t newchar);
/*! Czysci bufor tekstu. */
void Clear();
/*! Operator przypisania.
Ustala nowa zawartosc bufora tekstu.
\param str Referencja na string.
*/
void operator= (const XeWstring& str);
/*! Operator przypisania.
Ustala nowa zawartosc bufora tekstu.
\param str Wskaznik na wcstring.
*/
void operator= (wchar_t* str);
/*! Operator konwersji.
Rzutuje zawartosc bufora tekstu na wcstring.
*/
operator wchar_t*() const;
/*! Operator strumieniowania.
Konwertuje i dodaje wartosc double do bufora tekstu.
\param value Wartosc do dodania.
\return Referencja na string str.
*/
XeWstring& operator<< (wchar_t* value);
/*! Operator porownania.
Sprawdza czy oba stringi sa rowne.
\param str String do porownania.
\return true jesli oba stringi sa rowne.
*/
bool operator== (XeWstring& str);
/*! Operator porownania.
Sprawdza czy oba stringi sa rozne.
\param str String do porownania.
\return true jesli oba stringi sa rozne.
*/
bool operator!= (XeWstring& str);
/*! Operator porownania.
Sprawdza czy string i wcstring sa rowne.
\param str String do porownania.
\return true jesli string i wcstring sa rowne.
*/
bool operator== (wchar_t* str);
/*! Operator porownania.
Sprawdza czy string i wcstring sa rozne.
\param str String do porownania.
\return true jesli string i wcstring sa rozne.
*/
bool operator!= (wchar_t* str);
};

#define XeWendL L"\r\n"
#define XeWendS L"\0"

} // XeCore

#endif // _XE_WSTRING_H_
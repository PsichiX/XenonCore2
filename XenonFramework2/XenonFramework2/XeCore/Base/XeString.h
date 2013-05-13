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

#ifndef _XE_STRING_H_
#define _XE_STRING_H_

#include "../XenonCore2.h"


//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{

/*--- XeString ---*/
/*! Klasa stringa.
Bufor wartosci tekstowych.
*/
class XeString
{
private:
char* Text;
public:
/*! Ustala czy pamiec bufora jest statyczna (jesli true to podczas niszczenia stringa nie zostaje zwalniana pamiec bufora). */
bool Static;
/*! Konstruktor domyslny. */
XeString();
/*! Konstruktor wypelniajacy. */
XeString(const XeString& str);
/*! Konstruktor wypelniajacy. */
XeString(char* str);
/*! Konstruktor wypelniajacy. */
XeString(wchar_t* str);
/*! Destruktor. */
~XeString();
/*! Zwraca znak w buforze tekstu.
\param index Pozycja w buforze tekstu.
\param invert Okresla czy indeks zaczyna sie od konca tekstu.
\return Cstring zawartoœci bufora tekstu.
*/
char Index(unsigned int index,bool invert=false);
/*! Zwraca cstring.
\param index Pozycja w buforze tekstu.
\param invert Okresla czy indeks zaczyna sie od konca tekstu.
\return Cstring zawartoœci bufora tekstu.
*/
char* Get(unsigned int index=0,bool invert=false);
/*! Zwraca wcstring.
\param result Wskaznik na docelowy bufor Wcstring.
\param buffsize Rozmiar bufora w bajtach.
\return true jesli operacja powiodla sie.
*/
bool GetUnicode(wchar_t* result,unsigned int buffsize);
/*! Kopiuje lancuch znakow do bufora tekstu.
\param str Wskaznik na cstring.
*/
void Set(char* str);
/*! Kopiuje lancuch znakow do bufora tekstu.
\param str Wskaznik na wcstring.
*/
void Set(wchar_t* str);
/*! Kopiuje bufor znakow do bufora tekstu.
\param src Zrodlowy bufor znakow.
\param size Rozmiar bufora znakow (w bajtach).
*/
void Copy(char* src,unsigned int size);
/*! Ustala zawartosc bufora tekstu formatowanego.
\param str Wskaznik na cstring formatu.
\param ... Kolejne wartosci.
*/
void Format(char* str,...);
/*! Rozdziela zawartosc bufora tekstu w miejscu znakow sep i wysyla je do tablicy dynamicznej buforow tekstu. Wazne aby po uzyciu zwolnic tablice z pamieci uzywajac operatora: delete[].
\param sep Wskaznik na cstring ze znakami rozdzielajacymi.
\param count Referencja na wynik operacji (liczba elementow utworzonej tablicy).
\param block Wskaznikna cstring ze znakami oznaczajacymi blok tekstu bez rozdzielania.
\return Wskaznik na tablice dynamiczna buforow tekstu jelsi operacja powiodla sie, lub wartosc 0 jesli nie.
*/
XeString* Explode(char* sep,unsigned int& count,char* block=0);
/*! Rozdziela zawartosc bufora w miejscu znakow sep i wysyla je do tablicy dynamicznej buforow tekstu. Wazne aby po uzyciu zwolnic tablice z pamieci uzywajac operatora: delete[].
\param buff Wskaznik na bufor.
\param size Rozmiar bufora w bajtach.
\param sep Wskaznik na cstring ze znakami rozdzielajacymi.
\param count Referencja na wynik operacji (liczba elementow utworzonej tablicy).
\param block Wskaznikna cstring ze znakami oznaczajacymi blok tekstu bez rozdzielania.
\return Wskaznik na tablice dynamiczna buforow tekstu jelsi operacja powiodla sie, lub wartosc 0 jesli nie.
*/
static XeString* ExplodeBuff(char* buff,unsigned int size,char* sep,unsigned int& count,char* block=0);
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
bool Find(unsigned int offset,char* substr,unsigned int* position=0);
/*! Szuka i pobiera ciag znakow pomiedzy poczatkiem a pierwszym znalezionym ciagiem znakow rozdzielajacych.
\param result Referencja na wynikowy string.
\param delim Ciag znakow rozdzielajacych.
\param offset Poczatkowa pozycja odczytu.
\return Pozycja na ktorej zakonczyl odczyt, od ktorej powinien szukac dalej, lub 0 jesli nie znaleziono ciagu, badz dalsze poszukiwania sa niemozliwe..
*/
unsigned int Search(XeString& result,char* delim,unsigned int offset=0);
/*! Zamienia wszystkie stare ciagi znakow na nowe.
\param result Referencja na wynikowy string.
\param oldstr Stary ciag znakow.
\param newstr Nowy ciag znakow.
\return Ilosc zamienionych ciagow znakow.
*/
unsigned int Replace(XeString& result,char* oldstr,char* newstr);
/*! Zamienia wszystkie stare znaki na nowe.
\param result Referencja na wynikowy string.
\param oldchar Stary znak.
\param newchar Nowy znak.
\return Ilosc zamienionych znakow.
*/
unsigned int ReplaceChars(XeString& result,char oldchar,char newchar);
/*! Czysci bufor tekstu. */
void Clear();
/*! Operator przypisania.
Ustala nowa zawartosc bufora tekstu.
\param str Referencja na string.
*/
void operator= (const XeString& str);
/*! Operator przypisania.
Ustala nowa zawartosc bufora tekstu.
\param str Wskaznik na cstring.
*/
void operator= (char* str);
/*! Operator konwersji.
Rzutuje zawartosc bufora tekstu na cstring.
*/
operator char*() const;
/*! Operator strumieniowania.
Konwertuje i dodaje wartosc double do bufora tekstu.
\param value Wartosc do dodania.
\return Referencja na string str.
*/
XeString& operator<< (double value);
/*! Operator strumieniowania.
Konwertuje i dodaje wartosc int do bufora tekstu.
\param value Wartosc do dodania.
\return Referencja na string str.
*/
XeString& operator<< (int value);
/*! Operator strumieniowania.
Konwertuje i dodaje wartosc unsigned int do bufora tekstu.
\param value Wartosc do dodania.
\return Referencja na string str.
*/
XeString& operator<< (unsigned int value);
/*! Operator strumieniowania.
Dodaje cstring do bufora tekstu.
\param value Wskaznik na cstring.
\return Referencja na string str.
*/
XeString& operator<< (char* value);
/*! Operator porownania.
Sprawdza czy oba stringi sa rowne.
\param str String do porownania.
\return true jesli oba stringi sa rowne.
*/
bool operator== (XeString& str);
/*! Operator porownania.
Sprawdza czy oba stringi sa rozne.
\param str String do porownania.
\return true jesli oba stringi sa rozne.
*/
bool operator!= (XeString& str);
/*! Operator porownania.
Sprawdza czy string i cstring sa rowne.
\param str String do porownania.
\return true jesli string i cstring sa rowne.
*/
bool operator== (char* str);
/*! Operator porownania.
Sprawdza czy string i cstring sa rozne.
\param str String do porownania.
\return true jesli string i cstring sa rozne.
*/
bool operator!= (char* str);
};

#define XeEndL "\r\n"
#define XeEndS "\0"

} // XeCore

#endif // _XE_STRING_H_
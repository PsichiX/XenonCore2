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

#ifndef _XE_MARKUP_H_
#define _XE_MARKUP_H_

#include "../XenonCore2.h"
#include "XeNode.h"
#include "XeString.h"
#include "XeAssoc.h"
#include "XeArray.h"


//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{

/*--- XeMarkup ---*/
//! Klasa drzewa znacznikow.
class XeMarkup
{
public:
//! Typ wyliczeniowy.
enum Enum
{
CREATE,
DESTROY,
FIND
};
//! Klasa znacznika.
class Tag
{
public:
//! Nazwa.
XeString Name;
//! Tresc znacznika.
XeString Text;
//! Kontener atrybutow.
XeElements< XePair<XeString,XeString> > Attribs;
/*! Konstruktor domyslny. */
Tag();
};
//! Definicja typu elementu atrybutu.
typedef XeElementPointer< XePair<XeString,XeString> > Attrib;
//! Definicja typu elementu tagu.
typedef XeNode<Tag>::Node Etag;
//! Definicja typu wskaznika tagu.
typedef XeNode<Tag>* Ptag;
private:
void TagsToString(XeString& result,Ptag tag,int level);
public:
//! Drzewo znacznikow.
XeNode<Tag> Tags;
/*! Konstruktor domyslny. */
XeMarkup();
/*! Destruktor. */
~XeMarkup();
/*! Parsuje bufor.
\param buff Wskaznik na bufor danych.
\param size Rozmiar bufora.
\param prepost Znaki ignorowane na poczatku i koncu tresci znacznika.
\return true jesli operacja powiodla sie.
*/
bool Parse(char* buff,unsigned int size,char* prepost=0);
/*! Tworzy i wpisuje do bufora tekstowa tresc drzewa znacznikow.
\param buff Referencja na bufor docelowy.
\return true jesli operacja powiodla sie.
*/
bool Make(XeBuffer& buff);
/*! Zwalnia dane tagow z pamieci. */
void Free();
/*! Operator wyluskania.
\param path Sciezka do znacznika (tagi oddzielane znakiem: "/", opcjowane znakiem: "#". Dostepne opcje: new; last; id:0; next; prev ). Przyklad: "html/body/table#last#prev/td#id:2/tr#new". Tag "." oznacza ze operujemy na znaczniku z ragumentu tag, nie zas na jego dziecku. Tag ".." oznacza przejscie do znacznika nadrzednego.
\param action Typ akcji wykonywanej na tagu.
\param tag Wskaznik na znacznik w ktorym szukamy, badz wartosc NULL jesli szukamy w calym drzewie.
\return Element wezla znacznika.
*/
Etag operator() (char* path,Enum action=CREATE,Ptag tag=0);
/*! Operator wyluskania.
\param path Sciezka do znacznika (tagi oddzielane znakiem: "/", opcjowane znakiem: "#". Dostepne opcje: new; last; id:0; next; prev ). Przyklad: "html/body/table#last#prev/td#id:2/tr#new". Tag "." oznacza ze operujemy na znaczniku z ragumentu tag, nie zas na jego dziecku. Tag ".." oznacza przejscie do znacznika nadrzednego.
\param name Nazwa atrybutu.
\param action Typ akcji wykonywanej na tagu.
\param tag Wskaznik na znacznik w ktorym szukamy, badz wartosc NULL jesli szukamy w calym drzewie.
\return Element atrybutu znacznika.
*/
Attrib operator() (char* path,char* name,Enum action=CREATE,Ptag tag=0);
};

} // XeCore

#endif // _XE_MARKUP_H_
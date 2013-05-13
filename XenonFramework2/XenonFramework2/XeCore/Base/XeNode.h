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

#ifndef _XE_NODE_H_
#define _XE_NODE_H_

#include "../XenonCore2.h"
#include "XeElements.h"


//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{

/*--- XeNode ---*/
/*! Klasa wezla. */
template<typename T>
class XeNode
{
public:
typedef XeElementPointer<XeNode<T> > Node;
private:
T Data;
XeNode<T>* Parent;
XeElements<XeNode<T> > Childs;
public:
/*! Konstruktor domyslny. */
XeNode();
/*! Konstruktor wypelniajacy. */
XeNode(const T& val);
/*! Destruktor. */
~XeNode();
/*! Zwraca klon danych wezla.
\return Klon danych wezla.
*/
T Clone();
/*! Zwraca wskaznik na dane wezla.
\return Wskaznik na dane wezla.
*/
T* Pointer();
/*! Zwraca wskaznik na rodzica wezla.
\return Wskaznik na rodzica wezla.
*/
XeNode<T>* GetParent();
/*! Zwraca wezel do pierwszego dziecka.
\return Wezel.
*/
Node FirstChild();
/*! Zwraca wezel do ostatniego dziecka.
\return Wezel.
*/
Node LastChild();
/*! Dodaje dziecko i zwraca wezel do niego.
\param value Wartosc danych wezla.
\return Wezel dodanego dziecka.
*/
Node AddChild(const T& value);
/*! Usuwa dziecko.
\param child Element wezla dziecka.
*/
void RemoveChild(Node child);
/*! Usuwa dziecko o danym wskazniku na dane wezla.
\param child Wskaznik na dane wezla dziecka.
*/
void RemoveChildPtr(XeNode<T>* child);
/*! Usuwa siebie z wezlow rodzica. */
void RemoveSelf();
/*! Zwraca liczbe dzieci.
\return Ilosc wezlow dzieci.
*/
unsigned int Count();
/*! Usuwa wszystkie dzieci. */
void Free();
/*! Przechwytuje dziecko z innego wezla.
\param child Wezel dziecka do przechwycenia.
\return true jesli operacja powiodla sie.
*/
bool CaptureChild(Node child);
/*! Przechwytuje dziecko z innego wezla o danym wskazniku na dane wezla.
\param child Wskaznik na dane wezla dziecka.
\return true jesli operacja powiodla sie.
*/
bool CaptureChildPtr(XeNode<T>* child);
/*! Sortuje dzieci wedle funkcji foo przyjmujacej wskazniki na dwoje sasiednich dzieci i zwracajaca 1 jesli kolejnosc jest poprawna, 0 jesli kolejnosc jest ta sama i -1 jesli kolejnosc jest zla i trzeba ja zamienic.
\param foo Wskaznik na funkcje sortujaca: int foo(XeNode<T>* a,XeNode<T>* b).
*/
void SortChilds(int(*foo)(XeNode<T>*,XeNode<T>*));
/*! Operator wyluskania.
\return Wskaznik na dane wezla.
*/
T* operator-> ();
};

} // XeCore

#include "XeNode.inl"

#endif // _XE_NODE_H_

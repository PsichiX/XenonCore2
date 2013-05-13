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

#ifndef _XE_STACK_BUFFER_H_
#define _XE_STACK_BUFFER_H_

#include "../XenonCore2.h"


//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{

/*--- XeStackBuffer ---*/
//! Klasa bufora stosu.
template<typename T>
class XeStackBuffer
{
private:
T* stack;
int maxsize;
int count;
public:
/*! Konstruktor domyslny. */
XeStackBuffer();
/*! Konstruktor inicjujacy. */
XeStackBuffer(int size);
/*! Destruktor. */
~XeStackBuffer();
/*! Uklada obiekt na stosie. */
void Push(T val);
/*! Zdejmuje obiekt ze stosu. */
T Pop();
/*! Zwraca ilosc elementow na stosie. */
int Count();
/*! Zwraca rozmiar stosu. */
int MaxSize();
/*! Zwraca wskaznik na bufor stosu. */
T* Buffer();
/*! Czysci stos. */
void Clear();
/*! Odklada wiecej niz jeden obiekt na stosie. */
void PushMulti(int size,...);
/*! Czysci stos, nastepnie odklada wiecej niz jeden obiekt na stosie. */
void ClearPushMulti(int size,...);
};

} // XeCore

#include "XeStackBuffer.inl"

#endif // _XE_STACK_BUFFER_H_
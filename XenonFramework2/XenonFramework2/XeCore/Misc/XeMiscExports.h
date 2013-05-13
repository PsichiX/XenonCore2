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

#ifndef _XE_MISC_EXPORTS_H_
#define _XE_MISC_EXPORTS_H_

#include "../XenonCore2.h"
#ifdef XE_COMPILE_CORE_INTUICIO
#include "Intuicio.h"
#endif // XE_COMPILE_CORE_INTUICIO
#ifdef XE_COMPILE_CORE_VIRTUAL_FILE
#include "XVF.h"
#endif // XE_COMPILE_CORE_VIRTUAL_FILE
#include "../Base/XeAngleVectorTemplate.h"
#include "../Base/XeVectorTemplate.h"
#include "../Base/XeArray.h"

//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{

/*--- XeEngineHandle() ---*/
/*! Zwraca uchwyt modulu silnika.
\return Uchwyt modulu silnika.
*/
HMODULE XE_CALLTYPE XeEngineHandle();

#ifdef XE_COMPILE_CORE_VIRTUAL_FILE

/*--- XeVirtualFileMakeFile() ---*/
/*! Tworzy plik gotowy do zapisu do archiwum.
\param result Wskaznik na plik wynikowy.
\param name Nazwa pliku.
\param data Wskaznik na dane pliku.
\param size Rozmiar danych pliku (w bajtach).
*/
XE_IMPEX void XE_CALLTYPE XeVirtualFileMakeFile(XvfFile* result,char* name,void* data,unsigned int size);

/*--- XeVirtualFileSize() ---*/
/*! Zwraca wielkosc pliku.
\param file Wskaznik na plik.
\return Rozmiar danych pliku (w bajtach).
*/
XE_IMPEX unsigned int XE_CALLTYPE XeVirtualFileSize(XvfFile* file);

/*--- XeVirtualFileGetData() ---*/
/*! Pobiera dane pliku do bufora.
\param file Wskaznik na plik.
\param destbuff Wskaznik na bufor docelowy.
\param destsize Rozmiar bufora docelowego (w bajtach).
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeVirtualFileGetData(XvfFile* file,void* destbuff,unsigned int destsize);

/*--- XeVirtualFileFree() ---*/
/*! Zwalnia plik z pamieci (Wazne aby plik byl plikiem zaladowanym z archiwum!).
\param file Wskaznik na plik.
*/
XE_IMPEX void XE_CALLTYPE XeVirtualFileFree(XvfFile* file);

/*--- XeVirtualFileInfoOpen() ---*/
/*! Otwiera i zwraca informacje o plikach.
\param fname Sciezka do pliku archiwum.
\param infotab Wskaznik na docelowa tablice informacji o plikach.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeVirtualFileInfoOpen(char* fname,XeArray<XvfInfo>* infotab);

/*--- XeVirtualFileInfoClose() ---*/
/*! Zamyka i usuwa informacje o plikach.
\param infotab Wskaznik na tablice informacji o plikach.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeVirtualFileInfoClose(XeArray<XvfInfo>* infotab);

/*--- XeVirtualFileLoad() ---*/
/*! Laduje plik z archiwum.
\param resfile Wskaznik na plik.
\param fname Sciezka do pliku archiwum.
\param info Referencja na informacje o pliku.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeVirtualFileLoad(XvfFile* resfile,char* fname,XvfInfo& info);

/*--- XeVirtualFileLoadPart() ---*/
/*! Laduje czesc pliku z archiwum.
\param resfile Wskaznik na plik.
\param fname Sciezka do pliku archiwum.
\param info Referencja na informacje o pliku.
\param offset Przesuniecie (w bajtach).
\param size Rozmiar danych (w bajtach).
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeVirtualFileLoadPart(XvfFile* resfile,char* fname,XvfInfo& info,unsigned int offset, unsigned int size);

/*--- XeVirtualFileSave() ---*/
/*! Zapisuje pliki do archiwum.
\param fname Sciezka do pliku.
\param files Wskaznik na tablice plikow.
\param count Liczba plikow.
\param astemplate Ustala czy ma zapisac jako szablon archiwum.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeVirtualFileSave(char* fname,XvfFile* files,unsigned int count,bool astemplate=false);

/*--- XeVirtualFileMakeTemplate() ---*/
/*! Tworzy szablon archiwum.
\param fname Sciezka do pliku.
\param files Wskaznik na tablice informacji o plikach.
\param count Liczba plikow.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeVirtualFileMakeTemplate(char* fname,XvfInfo* files,unsigned int count);

/*--- XeVirtualFileComplete() ---*/
/*! Uzupelnia plik w archiwum.
\param fname Sciezka do pliku.
\param files Wskaznik na tablice plikow.
\param count Liczba plikow.
\param id Indeks pliku.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeVirtualFileComplete(char* fname,XvfFile* files,unsigned int count,unsigned int id);

/*--- XeVirtualFileReplace() ---*/
/*! Podmienia plik w archiwum.
\param fname Sciezka do pliku.
\param file Plik.
\param id Indeks pliku.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeVirtualFileReplace(char* fname,XvfFile file,unsigned int id);

#endif // XE_COMPILE_CORE_VIRTUAL_FILE

#ifdef XE_COMPILE_CORE_INTUICIO

/*--- XeIntuicioCompile ---*/
/*! Kompiluje skrypt Intuicio.
\param program Wskaznik na program Intuicio.
\param buffer Bufor tresci skryptu.
\param size Rozmiar bufora w bajtach.
\param deflist Uchwyt listy definicji externala.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeIntuicioCompile(XeIntuicioProgram* program,char* buffer,unsigned int size,XeHandle deflist=0);

/*--- XeIntuicioFree() ---*/
/*! Zwalnia program Intuicio z pamieci.
\param program Wskaznik na program Intuicio.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeIntuicioFree(XeIntuicioProgram* program);

/*--- XeIntuicioCompileToFile() ---*/
/*! Kompiluje skrypt Intuicio do pliku.
\param buffer Bufor tresci skryptu.
\param size Rozmiar bufora w bajtach.
\param fname Sciezka do pliku wynikowego.
\param deflist Uchwyt listy definicji externala.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeIntuicioCompileToFile(char* buffer,unsigned int size,char* fname,XeHandle deflist=0);

/*--- XeIntuicioCompileFile() ---*/
/*! Kompiluje skrypt Intuicio z pliku.
\param program Wskaznik na program Intuicio.
\param script Sciezka do pliku z trescia skryptu.
\param deflist Uchwyt listy definicji externala.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeIntuicioCompileFile(XeIntuicioProgram* program,char* script,XeHandle deflist=0);

/*--- XeIntuicioCompileFileToFile() ---*/
/*! Kompiluje skrypt Intuicio z pliku.
\param script Sciezka do pliku z trescia skryptu.
\param fname Sciezka do pliku wynikowego.
\param deflist Uchwyt listy definicji externala.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeIntuicioCompileFileToFile(char* script,char* fname,XeHandle deflist=0);

/*--- XeIntuicioExecute() ---*/
/*! Wykonuje program Intuicio.
\param program Wskaznik na program Intuicio.
\param params Wskaznik na bufor parametrow.
\param parsize Rozmiar bufora parametrow w bajtach.
\param deflist Uchwyt listy definicji externala.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeIntuicioExecute(XeIntuicioProgram* program,void* params=0,unsigned int parsize=0,XeHandle deflist=0);

/*--- XeIntuicioExecuteFile() ---*/
/*! Wykonuje program Intuicio.
\param fname Sciezka do pliku programu.
\param params Wskaznik na bufor parametrow.
\param parsize Rozmiar bufora parametrow w bajtach.
\param deflist Uchwyt listy definicji externala.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeIntuicioExecuteFile(char* fname,void* params=0,unsigned int parsize=0,XeHandle deflist=0);

/*--- XeIntuicioLinkDefinition() ---*/
/*! Linkuje skrypt definicji externali.
\param name Nazwa biblioteki externali.
\param data Wskaznik na tresc skryptu.
\param size Rozmiar skryptu w bajtach.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeIntuicioLinkDefinition(char* name,void* data,unsigned int size);

/*--- XeIntuicioLinkDefinitionFile() ---*/
/*! Linkuje skrypt definicji externali z pliku.
\param name Nazwa biblioteki externali.
\param fname Sciezka do pliku definicji externali.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeIntuicioLinkDefinitionFile(char* name,char* fname);

/*--- XeIntuicioUnlinkDefinitions() ---*/
/*! Odlinkowuje skrypty definicji externali. */
XE_IMPEX void XE_CALLTYPE XeIntuicioUnlinkDefinitions();

/*--- XeIntuicioAddDefinitionProc() ---*/
/*! Dodaje procedure definicji externala.
\param ext Nazwa externala.
\param def Nazwa definicji.
\param proc Procedura externala.
\return Jesli operacja powiodla sie zwraca wskaznik na procedure externala, jesli nie to zwraca wartosc NULL.
*/
XE_IMPEX XeIntuicioInterface* XE_CALLTYPE XeIntuicioAddDefinitionProc(char* ext,char* def,XeIntuicioInterface proc);

/*--- XeIntuicioClearDefinitionsProc() ---*/
/*! Czysci liste procedur definicji externali. */
XE_IMPEX void XE_CALLTYPE XeIntuicioClearDefinitionsProc();

/*--- XeIntuicioBuildDefinitionList() ---*/
/*! Generuje liste definicji externala z zalinkowanych skryptow i zwraca jej uchwyt.
\return Uchwyt listy definicji externala.
*/
XE_IMPEX XeHandle XE_CALLTYPE XeIntuicioBuildDefinitionList();

/*--- XeIntuicioFreeDefinitionList() ---*/
/*! Zwalnia liste definicji externala z pamieci.
\param deflist Uchwyt listy definicji externala.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeIntuicioFreeDefinitionList(XeHandle deflist);

#endif // XE_COMPILE_CORE_INTUICIO

/*--- XeStoreStates() ---*/
/*! Wrzuca zmienne stanu na stos.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeStoreStates();

/*--- XeRestoreStates() ---*/
/*! Zdejmuje zmienne stanu ze stosu.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeRestoreStates();

/*--- XeGetState() ---*/
/*! Pobiera wartosc zmiennej stanu silnika.
\param index Zmienna stanu.
\return Wskaznik nieokreslony, ktory nalezy rzutowac na wlasciwy danej zmiennej typ. Przyklad: XeEstate texturing=*(XeEstate*)XeGetState(XE_RENDER_TEXTURING_2D);
*/
XE_IMPEX void* XE_CALLTYPE XeGetState(XeEstate index);

/*--- XeSetState() ---*/
/*! Ustala wartosc zmiennej stanu silnika.
\param index Zmienna stanu.
\param ... Kolejne wartosci.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeSetState(XeEstate index,...);

/*--- XeLengthdir() ---*/
/*! Konwertuje kierunek i dlugosc na wektor.
\param a Kierunek i dlugosc.
\param result Wskaznik na wektor wynikowy.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeLengthdir(XeAngleVector a,XeVector* result);

/*--- XeDirection() ---*/
/*! Oblicza kierunek i odleglosc pomiedzy dwoma punktami.
\param b Pozycja poczatkowa.
\param e Pozycja koncowa.
\param result Wskaznik na kierunek i dlugosc.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeDirection(XeVector b,XeVector e,XeAngleVector* result);

/*--- XeInAngleField() ---*/
/*! Sprawdza czy punkt znajduje sie w polu widzenia kamery perspektywistycznej o danym kacie patrzenia.
\param p Pozycja punktu.
\param angle Kat pola widzenia.
\param cf Poczatkowa pozycja wektora kamery.
\param ct Koncowa pozycja wektora kamery.
\return true jesli punkt znajduje sie w polu widzenia.
*/
XE_IMPEX bool XE_CALLTYPE XeInAngleField(XeVector p,double angle,XeVector cf,XeVector ct);

/*--- XeAngleDifference() ---*/
/*! oblicza roznice pomiedzy dwoma katami.
\param angle1 Pierwszy kat.
\param angle2 Drugi kat.
\return Roznica katow.
*/
XE_IMPEX double XE_CALLTYPE XeAngleDifference(double angle1,double angle2);

/*--- XeInitiation() ---*/
/*! Inicjacja silnika.
\return true jesli operacja poziodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeInitiation();

/*--- XeClosure() ---*/
/*! Konczy prace silnika. */
XE_IMPEX void XE_CALLTYPE XeClosure();

/*--- XeCryptEncode() ---*/
/*! Szyfruje bufor.
\param buff_src Wskaznik na bufor zrodlowy.
\param buff_dst Wskaznik na bufor docelowy.
\param buff_size Rozmiar (w bajtach) bufora docelowego.
\param key_string Cstring klucza.
\param key_size Dlugosc cstringa klucza.
*/
XE_IMPEX void XE_CALLTYPE XeCryptEncode(void* buff_src,void* buff_dst,unsigned int buff_size,char* key_string,unsigned int key_size);

/*--- XeCryptDecode() ---*/
/*! Deszyfruje bufor.
\param buff_src Wskaznik na bufor zrodlowy.
\param buff_dst Wskaznik na bufor docelowy.
\param buff_size Rozmiar (w bajtach) bufora docelowego.
\param key_string Cstring klucza.
\param key_size Dlugosc cstringa klucza.
*/
XE_IMPEX void XE_CALLTYPE XeCryptDecode(void* buff_src,void* buff_dst,unsigned int buff_size,char* key_string,unsigned int key_size);

/*--- XeCurve() ---*/
/*--- XeCurveHalf() ---*/
/*! Oblicza wartosc krzywej na danej pozycji.
\param pos Pozycja na krzywej (zakres: <0;1>).
\param count Liczba punktow kontrolnych.
\param points Wskaznik na tablice punktow kontrolnych.
\param format Format punktow (ilosc punktow w strukturze).
\param offset Odstep od pierwszego punktu w strukturze.
\return Wartosc krzywej.
*/
XE_IMPEX double XE_CALLTYPE XeCurve(double pos,unsigned int count,double* points,unsigned int format,unsigned int offset);
XE_IMPEX float XE_CALLTYPE XeCurveHalf(float pos,unsigned int count,float* points,unsigned int format,unsigned int offset);

/*--- XeDataPack() ---*/
/*! Pakuje (kompresuje) dane do nowego buforu i zwraca wskaznik na niego.
\param data Wskaznik na bufor danych surowych.
\param sizeraw Wielkosc danych surowych.
\param sizecomp Referencja na wielkosc danych spakowanych.
\param password Cstring z haslem.
\param passsize Dlugosc hasla.
\return Wskaznik na utworzony bufor.
*/
XE_IMPEX void* XE_CALLTYPE XeDataPack(void* data,unsigned int sizeraw,unsigned int& sizecomp,char* password,unsigned int passsize);

/*--- XeDataUnpack() ---*/
/*! Pakuje (kompresuje) dane do nowego buforu i zwraca wskaznik na niego.
\param data Wskaznik na bufor danych surowych.
\param sizeraw Referencja na wielkosc danych surowych.
\param sizecomp Wielkosc danych spakowanych.
\param password Cstring z haslem.
\param passsize Dlugosc hasla.
\return Wskaznik na utworzony bufor.
*/
XE_IMPEX void* XE_CALLTYPE XeDataUnpack(void* data,unsigned int& sizeraw,unsigned int sizecomp,char* password,unsigned int passsize);

/*--- XeElementsCount() ---*/
/*! Zwraca ilosc elementow danego typu.
\param element Typ elementu.
\return Ilosc elementow.
*/
XE_IMPEX unsigned int XE_CALLTYPE XeElementsCount(XeEstate element);

/*--- XeElementsFirst() ---*/
/*! Pobiera pierwszy element danego typu.
\param type Typ elementu.
\param elm Wskaznik na element.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeElementsFirst(XeEstate type,void* elm);

/*--- XeElementsLast() ---*/
/*! Pobiera ostatni element danego typu.
\param type Typ elementu.
\param elm Wskaznik na element.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeElementsLast(XeEstate type,void* elm);

} // XeCore

#endif // _XE_MISC_EXPORTS_H_

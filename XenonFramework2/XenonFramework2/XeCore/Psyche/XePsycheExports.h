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

#ifndef _XE_PSYCHE_EXPORTS_H_
#define _XE_PSYCHE_EXPORTS_H_

#include "../XenonCore2.h"
#ifdef XE_COMPILE_PSYCHE
#include "../XePsyche.h"
#include "../Base/XeElmUniform.h"
#include "XenonCorePsyche.h"

//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{
//! \namespace XeCore::Psyche Przestrzen nazw modulu Psyche
namespace Psyche
{

/*--- XePsycheCreate() ---*/
/*! Tworzy umysl.
\param elm Wskaznik na element umyslu.
*/
XE_IMPEX void XE_CALLTYPE XePsycheCreate(XeElmPsyche* elm);

/*--- XePsycheProgress() ---*/
/*! Wykonuje postep umyslu.
\param index Element umyslu.
\param factor Wspolczynnik predkosci sygnalow.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XePsycheProgress(XeElmPsyche index,float factor);

/*--- XePsycheSave() ---*/
/*! Zapisuje umysl do pliku.
\param index Element umyslu.
\param fname Sciezka do pliku.
\param savesignals Ustala czy maja byc zapisane sygnaly.
\param savedetsignals Ustala czy maja byc zapisane sygnaly przechowywane w detektorach.
\param saveeffsignals Ustala czy maja byc zapisane sygnaly przechowywane w efektorach.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XePsycheSave(XeElmPsyche index,char* fname,bool savesignals=false,bool savedetsignals=false,bool saveeffsignals=false);

/*--- XePsycheLoad() ---*/
/*! Laduje umysl z pliku.
\param index Element umyslu.
\param fname Sciezka do pliku.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XePsycheLoad(XeElmPsyche index,char* fname);

/*--- XePsycheAdd() ---*/
/*! Dodaje komorke do umyslu.
\param index Element umyslu.
\param unit Wskaznik na uniwersalny element komorki.
\param type Typ komorki. Dostepne wartosci:<br>
XE_PSYCHE_NEURON: Neuron.<br>
XE_PSYCHE_DETECTOR: Detektor.<br>
XE_PSYCHE_EFFECTOR: Efektor.
\param value Wartosc poczatkowa (dla neuronu to wartosc bramy, dla detektora lub efektora to wartosc sygnalu).
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XePsycheAdd(XeElmPsyche index,XeElmUniform* unit,XeEstate type,XeDword value=0);

/*--- XePsycheRemove() ---*/
/*! Usuwa komorke z umyslu.
\param index Element umyslu.
\param unit Uniwersalny element komorki.
\param type Typ komorki. Dostepne wartosci:<br>
XE_PSYCHE_NEURON: Neuron.<br>
XE_PSYCHE_DETECTOR: Detektor.<br>
XE_PSYCHE_EFFECTOR: Efektor.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XePsycheRemove(XeElmPsyche index,XeElmUniform unit,XeEstate type);

/*--- XePsycheLink() ---*/
/*! Laczy komorke umyslu z inna komorka (tworzy synapse).
\param unit Uniwersalny element komorki ktorej dodamy synapse.
\param type Typ komorki do ktorej podlaczymy synapse. Dostepne wartosci:<br>
XE_PSYCHE_NEURON: Neuron.<br>
XE_PSYCHE_EFFECTOR: Efektor.
\param cell Uniwersalny element komorki do ktorego podlaczymy synapse.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XePsycheLink(XeElmUniform unit,XeEstate type,XeElmUniform cell);

/*--- XePsycheUnlink() ---*/
/*! Odlacza komorke umyslu od innej komorki (usuwa synapse).
\param unit Uniwersalny element komorki ktorej usuniemy synapse.
\param type Typ komorki od ktorej odlaczymy synapse. Dostepne wartosci:<br>
XE_PSYCHE_NEURON: Neuron.<br>
XE_PSYCHE_EFFECTOR: Efektor.
\param cell Uniwersalny element komorki od ktorej odlaczymy synapse.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XePsycheUnlink(XeElmUniform unit,XeEstate type,XeElmUniform cell);

/*--- XePsycheSet() ---*/
/*! Ustala wartosc stanu komorki umyslu.
\param unit Uniwersalny element komorki.
\param type Typ zmiennej stanu. Dostepne wartosci:<br>
XE_PSYCHE_NEURON_LENGTH: Dlugosc neuronu [float].<br>
XE_PSYCHE_NEURON_GATE: Brama neuronu [XeDword].<br>
XE_PSYCHE_NEURON_POSITION: Pozycja neuronu [XeHalfVector].<br>
XE_PSYCHE_DETECTOR_SIGNAL: Sygnal detektora [XeDword].<br>
XE_PSYCHE_DETECTOR_POSITION: Pozycja detektora [XeHalfVector].<br>
XE_PSYCHE_EFFECTOR_SIGNAL: Sygnal efektora [XeDword].<br>
XE_PSYCHE_EFFECTOR_POSITION: Pozycja efektora [XeHalfVector].<br>
XE_PSYCHE_SIGNAL_SIGNAL: Wartosc sygnalu [XeDword].
\param ... Wartosci do przeslania.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XePsycheSet(XeElmUniform unit,XeEstate type,...);

/*--- XePsycheGet() ---*/
/*! Pobiera wartosc stanu komorki umyslu.
\param unit Uniwersalny element komorki.
\param type Typ zmiennej stanu. Dostepne wartosci:<br>
XE_PSYCHE_NEURON_LENGTH: Dlugosc neuronu [float].<br>
XE_PSYCHE_NEURON_GATE: Brama neuronu [XeDword].<br>
XE_PSYCHE_NEURON_POSITION: Pozycja neuronu [XeHalfVector].<br>
XE_PSYCHE_DETECTOR_SIGNAL: Sygnal detektora [XeDword].<br>
XE_PSYCHE_DETECTOR_POSITION: Pozycja detektora [XeHalfVector].<br>
XE_PSYCHE_EFFECTOR_SIGNAL: Sygnal efektora [XeDword].<br>
XE_PSYCHE_EFFECTOR_POSITION: Pozycja efektora [XeHalfVector].<br>
XE_PSYCHE_SIGNAL_SIGNAL: Wartosc sygnalu [XeDword].<br>
XE_PSYCHE_SIGNAL_POSITION: Pozycja sygnalu <0;?> [float].<br>
XE_PSYCHE_SYNAPSIS_GATE: Brama komorki [XeDword].<br>
XE_PSYCHE_SYNAPSIS_POSITION: Pozycja komorki [XeHalfVector].
\return Wskaznik nieokreslony na zmienna stanu komorki. Nalezy rzutowac na konkretny typ danej zmiennej stanu.
*/
XE_IMPEX void* XE_CALLTYPE XePsycheGet(XeElmUniform unit,XeEstate type);

/*--- XePsycheSignalNeuronInfo() ---*/
/*! Pobiera opis neuronu w ktorym przebywa dany sygnal.
\param unit Uniwersalny element komorki sygnalu.
\param info Wskaznik na obiekt struktury opisu neuronu.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XePsycheSignalNeuronInfo(XeElmUniform unit,XePsycheSignalNeuronInfoStruct* info);

/*--- XePsycheElement() ---*/
/*! Dokonuje danej operacji na uniwerslanym elemencie komorki.
\param index Element umyslu.
\param unit Wskaznik na uniwersalny element komorki.
\param type Typ komorki i akcji. Dostepne wartosci:<br>
XE_PSYCHE_NEURON_FIRST: Pobiera pierwszy neuron.<br>
XE_PSYCHE_NEURON_LAST: Pobiera ostatni neuron.<br>
XE_PSYCHE_NEURON_NEXT: Inkrementuje neuron.<br>
XE_PSYCHE_NEURON_PREV: Dekrementuje neuron.<br>
XE_PSYCHE_DETECTOR_FIRST: Pobiera pierwszy detektor.<br>
XE_PSYCHE_DETECTOR_LAST: Pobiera ostatni detektor.<br>
XE_PSYCHE_DETECTOR_NEXT: Inkrementuje detektor.<br>
XE_PSYCHE_DETECTOR_PREV: Dekrementuje detektor.<br>
XE_PSYCHE_EFFECTOR_FIRST: Pobiera pierwszy efektor.<br>
XE_PSYCHE_EFFECTOR_LAST: Pobiera ostatni efektor.<br>
XE_PSYCHE_EFFECTOR_NEXT: Inkrementuje efektor.<br>
XE_PSYCHE_EFFECTOR_PREV: Dekrementuje efektor.<br>
XE_PSYCHE_SIGNAL_FIRST: Pobiera pierwszy sygnal.<br>
XE_PSYCHE_SIGNAL_LAST: Pobiera ostatni sygnal.<br>
XE_PSYCHE_SIGNAL_NEXT: Inkrementuje sygnal.<br>
XE_PSYCHE_SIGNAL_PREV: Dekrementuje sygnal.<br>
*/
XE_IMPEX bool XE_CALLTYPE XePsycheElement(XeElmPsyche index,XeElmUniform* unit,XeEstate type);

/*--- XePsycheSynapsis() ---*/
/*! Pobiera uniwersalny element komorki z danej synapsy.
\param unit Uniwersalny element komorki.
\param type Typ komorki z ktorej pobieramy element. Dostepne wartosci:<br>
XE_PSYCHE_NEURON_FIRST: Pierwszy neuron.<br>
XE_PSYCHE_NEURON_LAST: Ostatni neuron.<br>
XE_PSYCHE_DETECTOR_FIRST: Pierwszy detektor.<br>
XE_PSYCHE_DETECTOR_LAST: Ostatni detektor.<br>
XE_PSYCHE_SYNAPSIS_FIRST: Pierwszy neuron.<br>
XE_PSYCHE_SYNAPSIS_LAST: Ostatni neuron.<br>
XE_PSYCHE_SYNAPSIS_NEXT: Nastepna synapsa.<br>
XE_PSYCHE_SYNAPSIS_PREV: Poprzednia synapsa.
\param cell Wskaznik na uniwersalny element komorki do ktorego zapiszemy wynik.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XePsycheSynapsis(XeElmUniform unit,XeEstate type,XeElmUniform* cell);

/*--- XePsycheSynapsisCount() ---*/
/*! Zwraca ilosc synaps komorki umyslu danego typu.
\param unit Uniwersalny element komorki.
\param type Typ komorki z ktorej pobieramy element. Dostepne wartosci:<br>
XE_PSYCHE_NEURON: Neuron.<br>
XE_PSYCHE_DETECTOR: Detektor.<br>
XE_PSYCHE_SYNAPSIS: Synapsa.
\return Ilosc synaps.
*/
XE_IMPEX unsigned int XE_CALLTYPE XePsycheSynapsisCount(XeElmUniform unit,XeEstate type);

/*--- XePsycheCount() ---*/
/*! Zwraca ilosc komorek umyslu danego typu.
\param index Element umyslu.
\param type Typ komorki. Dostepne wartosci:<br>
XE_PSYCHE_NEURON: Neuron.<br>
XE_PSYCHE_DETECTOR: Detektor.<br>
XE_PSYCHE_EFFECTOR: Efektor.<br>
XE_PSYCHE_SIGNAL: Sygnal.<br>
XE_PSYCHE: Wszystkie.
\return Ilosc komorek.
*/
XE_IMPEX unsigned int XE_CALLTYPE XePsycheCount(XeElmPsyche index,XeEstate type);

/*--- XePsycheSend() ---*/
/*! Wysyla sygnal do detektora.
\param unit Uniwersalny element komorki.
\param signal Wartosc sygnalu.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XePsycheSend(XeElmUniform unit,XeDword signal);

/*--- XePsycheReceive() ---*/
/*! Odbiera sygnal od efektora.
\param unit Uniwersalny element komorki.
\return Wartosc sygnalu.
*/
XE_IMPEX XeDword XE_CALLTYPE XePsycheReceive(XeElmUniform unit);

/*--- XePsycheKillSignal() ---*/
/*! Zabija dany sygnal.
\param index Element umyslu.
\param unit Uniwersalny element komorki sygnalu.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XePsycheKillSignal(XeElmPsyche index,XeElmUniform unit);

/*--- XePsycheKillSignals() ---*/
/*! Zabija wszystkie sygnaly.
\param index Element umyslu.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XePsycheKillSignals(XeElmPsyche index);

/*--- XePsycheClear() ---*/
/*! Niszczy wszystkie komorki danego typu.
\param index Element umyslu.
\param type Typ komorki. Dostepne wartosci:<br>
XE_PSYCHE_NEURON: Neuron.<br>
XE_PSYCHE_DETECTOR: Detektor.<br>
XE_PSYCHE_EFFECTOR: Efektor.<br>
XE_PSYCHE_SIGNAL: Sygnal.<br>
XE_PSYCHE: Wszystkie.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XePsycheClear(XeElmPsyche index,XeEstate type);

/*--- XePsycheDestroy() ---*/
/*! Niszczy umysl.
\param index Element umyslu.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XePsycheDestroy(XeElmPsyche index);

} // Psyche
} // XeCore

#endif // XE_COMPILE_PSYCHE

#endif // _XE_PSYCHE_EXPORTS_H_

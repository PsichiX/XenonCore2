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

#ifndef _XE_CHAOS_EXPORTS_H_
#define _XE_CHAOS_EXPORTS_H_

#include "../XenonCore2.h"
#ifdef XE_COMPILE_CHAOS
#include "../XeChaos.h"
#ifdef XE_COMPILE_PHOTON
#include "../XePhoton.h"
#endif // XE_COMPILE_PHOTON
#include "../Base/XeVectorTemplate.h"
#include "../Base/XeAngleVectorTemplate.h"

//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{
//! \namespace XeCore::Chaos Przestrzen nazw modulu Chaos
namespace Chaos
{

/*--- XeShapeIsConvex2D() ---*/
/*! Sprawdza czy bryla jest wypukla.
\param vertices Wskaznik na tablice wierzcholkow.
\param count Ilosc wierzcholkow w tablicy.
\return true jesli bryla jest wypukla.
*/
XE_IMPEX bool XE_CALLTYPE XeShapeIsConvex2D(XeVector* vertices,unsigned int count);

/*--- XeShapeCollision2D() ---*/
/*! Sprawdza czy punkt koliduje z bryla wypukla.
\param point Punkt.
\param vertices Wskaznik na tablice wierzcholkow.
\param count Ilosc wierzcholkow w tablicy.
\param negfaces Zmienia kierunek scian na przeciwne.
\param onplane Ustala czy uznac punkt na plaszczyznie sciany jako kolizje.
\return true jesli nastapila kolizja.
*/
XE_IMPEX bool XE_CALLTYPE XeShapeCollision2D(XeVector point,XeVector* vertices,unsigned int count,bool negfaces=false,bool onplane=true);

/*--- XePolygonsCollision2D() ---*/
/*! Sprawdza czy dwa wielokaty wypukle koliduja ze soba.
\param shape1 Wskaznik na tablice wierzcholkow pierwszego wielokata.
\param count1 Ilosc wierzcholkow pierwszego wielokata.
\param shape2 Wskaznik na tablice wierzcholkow drugiego wielokata.
\param count2 Ilosc wierzcholkow drugiego wielokata.
\return true jesli nastapila kolizja.
*/
XE_IMPEX bool XE_CALLTYPE XePolygonsCollision2D(XeVector* shape1,unsigned int count1,XeVector* shape2,unsigned int count2);

/*--- XeShapeIsConvex2Dhalf() ---*/
/*! Sprawdza czy bryla jest wypukla.
\param vertices Wskaznik na tablice wierzcholkow.
\param count Ilosc wierzcholkow w tablicy.
\return true jesli bryla jest wypukla.
*/
XE_IMPEX bool XE_CALLTYPE XeShapeIsConvex2Dhalf(XeHalfVector* vertices,unsigned int count);

/*--- XeShapeCollision2Dhalf() ---*/
/*! Sprawdza czy punkt koliduje z bryla wypukla.
\param point Punkt.
\param vertices Wskaznik na tablice wierzcholkow.
\param count Ilosc wierzcholkow w tablicy.
\param negfaces Zmienia kierunek scian na przeciwne.
\param onplane Ustala czy uznac punkt na plaszczyznie sciany jako kolizje.
\return true jesli nastapila kolizja.
*/
XE_IMPEX bool XE_CALLTYPE XeShapeCollision2Dhalf(XeHalfVector point,XeHalfVector* vertices,unsigned int count,bool negfaces=false,bool onplane=true);

/*--- XePolygonsCollision2Dhalf() ---*/
/*! Sprawdza czy dwa wielokaty wypukle koliduja ze soba.
\param shape1 Wskaznik na tablice wierzcholkow pierwszego wielokata.
\param count1 Ilosc wierzcholkow pierwszego wielokata.
\param shape2 Wskaznik na tablice wierzcholkow drugiego wielokata.
\param count2 Ilosc wierzcholkow drugiego wielokata.
\return true jesli nastapila kolizja.
*/
XE_IMPEX bool XE_CALLTYPE XePolygonsCollision2Dhalf(XeHalfVector* shape1,unsigned int count1,XeHalfVector* shape2,unsigned int count2);

/*--- XePhysicsSetFactor() ---*/
/*! Ustala wspolczynnik fizyczny.
\param factor Wspolczynnik.
*/
XE_IMPEX void XE_CALLTYPE XePhysicsSetFactor(double factor);

/*--- XePhysicsGetFactor() ---*/
/*! Zwraca wspolczynnik fizyczny.
\return Wspolczynnik.
*/
XE_IMPEX double XE_CALLTYPE XePhysicsGetFactor();

/*--- XePhysicsUpdate() ---*/
/*! Aktualizuje fizyke. */
XE_IMPEX void XE_CALLTYPE XePhysicsUpdate();

/*--- XeSubstanceCreate() ---*/
/*! Tworzy substancje.
\param elm Wskaznik na element substancji. Zwraca do niego utworzony element jesli operacja powiodla sie.
*/
XE_IMPEX void XE_CALLTYPE XeSubstanceCreate(XeElmSubstance* elm);

/*--- XeSubstanceSetObject() ---*/
/*! Ustala obiekt.
\param index Element substancji.
\param object Obiekt.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeSubstanceSetObject(XeElmSubstance index,double object);

/*--- XeSubstanceSetPosition() ---*/
/*! Ustala pozycje.
\param index Element substancji.
\param p Pozycja.
\param notresetprev Sprawdza czy ma nie ustawiac (resetowac) stan poprzedniej pozycji na obecna (domyslnie: false).
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeSubstanceSetPosition(XeElmSubstance index,XeVector p,bool notresetprev=false);

/*--- XeSubstanceSetRange() ---*/
/*! Ustala promien.
\param index Element substancji.
\param range Promien.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeSubstanceSetRange(XeElmSubstance index,double range);

/*--- XeSubstanceSetMass() ---*/
/*! Ustala mase.
\param index Element substancji.
\param mass Masa.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeSubstanceSetMass(XeElmSubstance index,double mass);

/*--- XeSubstanceSetEnergy() ---*/
/*! Ustala energie.
\param index Element substancji.
\param energy Energia.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeSubstanceSetEnergy(XeElmSubstance index,double energy);

/*--- XeSubstanceSetSolid() ---*/
/*! Ustala czy obiekt jest trwaly.
\param index Element substancji.
\param solid Trwalosc. Dostepne wartosci:<br>
XE_FLAG_SUBSTANCE_SOLID_RANGE: Umozliwia kolidowanie promieniowe.<br>
XE_FLAG_SUBSTANCE_SOLID_SURFACE: Umozliwia kolidowanie powierzchniowe.<br>
Wartosci sa maskami bitowymi wiec mozna je laczyc operatorem "|".
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeSubstanceSetSolid(XeElmSubstance index,unsigned int solid);

/*--- XeSubstanceAddInertion() ---*/
/*! Dodaje bezwladnosc.
\param index Element substancji.
\param i Wektor bezwladnosci.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeSubstanceAddInertion(XeElmSubstance index,XeVector i);

/*--- XeSubstanceResetInertion() ---*/
/*! Zeruje bezwladnosc.
\param index Element substancji.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeSubstanceResetInertion(XeElmSubstance index);

/*--- XeSubstanceGet() ---*/
/*! Pobiera wartosc zmiennej stanu substancji.
\param index Element substancji.
\param type Zmienna stanu substancji. Dostepne wartosci:<br>
XE_SUBSTANCE_ID: Indeks substancji.<br>
XE_SUBSTANCE_OBJECT: Obiekt.<br>
XE_SUBSTANCE_POSITION: Pozycja.<br>
XE_SUBSTANCE_RANGE: Promien.<br>
XE_SUBSTANCE_MASS: Masa.<br>
XE_SUBSTANCE_ENERGY: Energia.<br>
XE_SUBSTANCE_SOLID: Trwalosc.<br>
XE_SUBSTANCE_INERTION: Wektor bezwladnosci.
XE_SUBSTANCE_LAST_POSITION: Pozycja z ostatniej aktualizacji.
\return Wskaznik nieokreslony na zmienna stanu substancji. Nalezy rzutowac na konkretny typ danej zmiennej stanu. 
*/
XE_IMPEX void* XE_CALLTYPE XeSubstanceGet(XeElmSubstance index,XeEstate type);

/*--- XeSubstanceDestroy() ---*/
/*! Niszczy substancje.
\param index Element substancji.
*/
XE_IMPEX bool XE_CALLTYPE XeSubstanceDestroy(XeElmSubstance index);

/*--- XeRayCreate() ---*/
/*! Tworzy wiazke (promien).
\param elm Wskaznik na element wiazki. Zwraca do niego utworzony obiekt jesli operacja powiodla sie.
*/
XE_IMPEX void XE_CALLTYPE XeRayCreate(XeElmRay* elm);

/*--- XeRaySetPosition() ---*/
/*! Ustala pozycje.
\param index Element wiazki.
\param p Pozycja.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeRaySetPosition(XeElmRay index,XeVector p);

/*--- XeRaySetDirection() ---*/
/*! Ustala kierunek.
\param index Element wiazki.
\param dir Kierunek.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeRaySetDirection(XeElmRay index,XeAngleVector dir);

/*--- XeRaySetAngle() ---*/
/*! Ustala kat zasiegu (rozproszenia).
\param index Element wiazki.
\param angle Kat angle.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeRaySetAngle(XeElmRay index,double angle);

/*--- XeRaySetEnergy() ---*/
/*! Ustala energie.
\param index Element wiazki.
\param energy Energia.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeRaySetEnergy(XeElmRay index,double energy);

/*--- XeRaySetFrequency() ---*/
/*! Ustala czestotliwosc.
\param index Element wiazki.
\param frequency Czestotliwosc.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeRaySetFrequency(XeElmRay index,double frequency);

/*--- XeRayGet() ---*/
/*! Pobiera wartosc zmiennej stanu wiazki.
\param index Element wiazki.
\param type Zmienna stanu wiazki. Dostepne wartosci:<br>
XE_RAY_ID: Indeks wiazki.<br>
XE_RAY_POSITION: Pozycja.<br>
XE_RAY_DIRECTION: Kierunek.<br>
XE_RAY_ANGLE: Zasieg (rozproszenie).<br>
XE_RAY_ENERGY: Energia.<br>
XE_RAY_FREQUENCY: Czestotliwosc.
\return Wskaznik nieokreslony na zmienna stanu wiazki. Nalezy rzutowac na konkretny typ danej zmiennej stanu.
*/
XE_IMPEX void* XE_CALLTYPE XeRayGet(XeElmRay index,XeEstate type);

/*--- XeRayDestroy() ---*/
/*! Niszczy wiazke.
\param index Element wiazki.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeRayDestroy(XeElmRay index);

/*--- XeCovalenceForceCreate() ---*/
/*! Tworzy sile kowalencyjna (miedzyczasteczkowa).
\param elm Wskaznik na element sily kowalencyjnej. Zwraca do niego utworzony element jesli operacja powiodla sie.
*/
XE_IMPEX void XE_CALLTYPE XeCovalenceForceCreate(XeElmCovalenceForce* elm);

/*--- XeCovalenceForceSetSubstance() ---*/
/*! Ustala substancje.
\param index Element sily kowalencyjnej.
\param type Typ substancji. Dostepne wartosci:<br>
XE_COVALENCE_FORCE_SUBSTANCE_1: Pierwsza substancja.<br>
XE_COVALENCE_FORCE_SUBSTANCE_2: Druga substancja.
\param substance Element substancji.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeCovalenceForceSetSubstance(XeElmCovalenceForce index,XeEstate type,XeElmSubstance substance);

/*--- XeCovalenceForceSetForce() ---*/
/*! Ustala sile.
\param index Element sily kowalencyjnej.
\param force Sila.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeCovalenceForceSetForce(XeElmCovalenceForce index,double force);

/*--- XeCovalenceForceSetForceFromDistance() ---*/
/*! Ustala sile biorac ja z odleglosci pomiedzy substancjami.
\param index Element sily kowalencyjnej.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeCovalenceForceSetForceFromDistance(XeElmCovalenceForce index);

/*--- XeCovalenceSetForceResilience() ---*/
/*! Ustala sprezystosc.
\param index Element sily kowalencyjnej.
\param resilience Sprezystosc.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeCovalenceForceSetResilience(XeElmCovalenceForce index,double resilience);

/*--- XeCovalenceForceSetRange() ---*/
/*! Ustala zasieg sily, po ktorego przekroczeniu nastepuje rozerwanie sily.
\param index Element sily kowalencyjnej.
\param range Zasieg.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeCovalenceForceSetRange(XeElmCovalenceForce index,double range);

/*--- XeCovalenceForceSetSolid() ---*/
/*! Ustala zasieg sily, po ktorego przekroczeniu nastepuje rozerwanie sily.
\param index Element sily kowalencyjnej.
\param solid Solidnosc; zachowanie sily po przekroczeniu zasiegu. Dostepne wartosci:<br>
XE_COVALENCE_FORCE_SOLID_ALWAYS: Utrzymuje sile zawsze.<br>
XE_COVALENCE_FORCE_SOLID_TEMPORARY: Tymczasowo nie utrzymuje sily, dopoki dystans pomiedzy substancjami nie bedzie w zasiegu sily.<br>
XE_COVALENCE_FORCE_SOLID_NEVER: Po przekroczeniu zasiegu zrywa polaczenie.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeCovalenceForceSetSolid(XeElmCovalenceForce index,XeEstate solid);

/*--- XeCovalenceForceGet() ---*/
/*! Pobiera wartosc zmiennej stanu sily kowalencyjnej.
\param index Element sily kowalencyjnej.
\param type Zmienna stanu sily kowalencyjnej. Dostepne wartosci:<br>
XE_COVALENCE_FORCE_ID: Indeks sily kowalencyjnej.<br>
XE_COVALENCE_FORCE_SUBSTANCE_1: Pierwsza substancja.<br>
XE_COVALENCE_FORCE_SUBSTANCE_2: Druga substancja.<br>
XE_COVALENCE_FORCE_FORCE: Sila.<br>
XE_COVALENCE_FORCE_RESILIENCE: Sprezystosc.<br>
XE_COVALENCE_FORCE_RANGE: Zasieg. Jesli odleglosc substancji bedzie wieksza niz zasieg i sila nie jest solidna to nastapi rozerwanie na stale badz na chwile.<br>
XE_COVALENCE_FORCE_SOLID: Solidnosc, utrzymywanie polaczenia po przekroczeniu zasiegu: zawsze, tymczasowo lub nigdy.
\return Wskaznik nieokreslony na zmienna stanu sily kowalencyjnej. Nalezy rzutowac na konkretny typ danej zmiennej stanu.
*/
XE_IMPEX void* XE_CALLTYPE XeCovalenceForceGet(XeElmCovalenceForce index,XeEstate type);

/*--- XeCovalenceForceDestroy() ---*/
/*! Niszczy sile kowalencyjna.
\param index Element sily kowalencyjnej.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeCovalenceForceDestroy(XeElmCovalenceForce index);

/*--- XeForceCreate() ---*/
/*! Tworzy sile.
\param elm Wskaznik na element sily. Zwraca do niego utworzony element jesli operacja powiodla sie.
*/
XE_IMPEX void XE_CALLTYPE XeForceCreate(XeElmForce* elm);

/*--- XeForceSetPosition() ---*/
/*! Ustala pozycje.
\param index Element sily.
\param p Pozycja.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeForceSetPosition(XeElmForce index,XeVector p);

/*--- XeForceSetDirection() ---*/
/*! Ustala kierunek.
\param index Element sily.
\param dir Kierunek.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeForceSetDirection(XeElmForce index,XeAngleVector dir);

/*--- XeForceSetDirectionToAnchor() ---*/
/*! Ustala kierunek do zakotwiczonej substancji kierunku.
\param index Element sily.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeForceSetDirectionToAnchor(XeElmForce index);

/*--- XeForceSetForce() ---*/
/*! Ustala sile.
\param index Element sily.
\param force Sila.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeForceSetForce(XeElmForce index,double force);

/*--- XeForceSetSpeed() ---*/
/*! Ustala predkosc.
\param index Element sily.
\param speed Predkosc.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeForceSetSpeed(XeElmForce index,double speed);

/*--- XeForceSetAnchor() ---*/
/*! Ustala kotwice (substancje z ktora jest polaczony).
\param index Element sily.
\param anchor Substancja.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeForceSetAnchor(XeElmForce index,XeElmSubstance anchor);

/*--- XeForceSetAnchorDirection() ---*/
/*! Ustala kotwice kierunku (substancje z ktora jest polaczony, ktora wskazuje kierunek sily).
\param index Element sily.
\param anchordir Substancja.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeForceSetAnchorDirection(XeElmForce index,XeElmSubstance anchordir);

/*--- XeForceSetRicochet() ---*/
/*! Ustala wspolczynnik sily odrzutu oddzialujaca na inne substancje gdy sila jest polaczana z jakas substancja.
\param index Element sily.
\param ricochet Wspolczynnik sily dla reszty substancji.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeForceSetRicochet(XeElmForce index,float ricochet);

/*--- XeForceSetRange() ---*/
/*! Ustala zasieg sily. Jesli rowny 0 to zasieg jest globalny.
\param index Element sily.
\param range Zasieg sily.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeForceSetRange(XeElmForce index,double range);

/*--- XeForceGet() ---*/
/*! Pobiera wartosc zmiennej stanu sily.
\param index Element sily.
\param type Zmienna stanu. Dostepne wartosci:<br>
XE_FORCE_ID: Indeks sily.<br>
XE_FORCE_POSITION: Pozycja.<br>
XE_FORCE_DIRECTION: Kierunek.<br>
XE_FORCE_FORCE: Sila.<br>
XE_FORCE_SPEED: Predkosc.<br>
XE_FORCE_ANCHOR: Kotwica (substancja z ktora jest polaczony).<br>
XE_FORCE_ANCHOR_DIRECTION: Kotwica kierunku (substancja z ktora jest polaczony, ktora wskazuje kierunek sily).<br>
XE_FORCE_RICOCHET: Wspolczynnik sily oddzialujacej na inne sily gdy dana sila ma ustalona kotwice.
\return Wskaznik nieokreslony na zmienna stanu sily. Nalezy rzutowac na konkretny typ danej zmiennej stanu.
*/
XE_IMPEX void* XE_CALLTYPE XeForceGet(XeElmForce index,XeEstate type);

/*--- XeForceDestroy() ---*/
/*! Niszczy sile.
\param index Element sily.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeForceDestroy(XeElmForce index);

#ifdef XE_COMPILE_PHOTON

/*--- XeSurfaceCreate() ---*/
/*! Tworzy powierzchnie.
\param elm Wskaznik na element powierzchni. Zwraca do niego utworzony element jesli operacja powiodla sie.
*/
XE_IMPEX void XE_CALLTYPE XeSurfaceCreate(XeElmSurface* elm);

/*--- XeSurfaceSetSubstance() ---*/
/*! Ustala substancje.
\param index Element powierzchni.
\param type Typ substancji. Dostepne wartosci:<br>
XE_SURFACE_SUBSTANCE_1: Pierwsza substancja.<br>
XE_SURFACE_SUBSTANCE_2: Druga substancja.<br>
XE_SURFACE_SUBSTANCE_3: Trzecia substancja.
\param substance Element substancji.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeSurfaceSetSubstance(XeElmSurface index,XeEstate type,XeElmSubstance substance);

/*--- XeSurfaceSetTexture() ---*/
/*! Ustala teksture.
\param index Element powierzchni.
\param texture Element tekstury.
\param type Typ tekstury. Musi byc: XE_2D.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeSurfaceSetTexture(XeElmSurface index,Photon::XeElmTexture texture,XeEstate type);

/*--- XeSurfaceSetCoord() ---*/
/*! Ustala koordynaty tekstury.
\param index Element powierzchni.
\param type Typ substancji tekstury. Dostepne wartosci:<br>
XE_SURFACE_COORD_SUBSTANCE_1: Pierwsza substancja tekstury.<br>
XE_SURFACE_COORD_SUBSTANCE_2: Druga substancja tekstury.<br>
XE_SURFACE_COORD_SUBSTANCE_3: Trzecia substancja tekstury.
\param c Koordynaty.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeSurfaceSetCoord(XeElmSurface index,XeEstate type,XeVector c);

/*--- XeSurfaceSetDensity() ---*/
/*! Ustala gestosc (grubosc) powierzchni (wazne przy wykrywaniu kolizji).
\param index Element powierzchni.
\param density Gestosc.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeSurfaceSetDensity(XeElmSurface index,double density);

/*--- XeSurfaceSetOrientation() ---*/
/*! Ustala orientacje.
\param index Element powierzchni.
\param orientation Orientacja (wartosci: -1;0;1).
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeSurfaceSetOrientation(XeElmSurface index,int orientation);

/*--- XeSurfaceSetOrder() ---*/
/*! Ustala kolejnosc dla kolejki rysowania.
\param index Element powierzchni.
\param order Kolejnosc.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeSurfaceSetOrder(XeElmSurface index,double order);

/*--- XeSurfaceGet() ---*/
/*! Pobiera wartosc zmiennej stanu powierzchni.
\param index Element powierzchni.
\param type Zmienna stanu. Dostepne wartosci:<br>
XE_SURFACE_ID: Indeks powierzchni.<br>
XE_SURFACE_SUBSTANCE_1: Pierwsza substancja.<br>
XE_SURFACE_SUBSTANCE_2: Druga substancja.<br>
XE_SURFACE_SUBSTANCE_3: Trzecia substancja.<br>
XE_SURFACE_TEXTURE: Element tekstury.<br>
XE_SURFACE_TEXTURE_TYPE: Typ tekstury.<br>
XE_SURFACE_ORDER: Kolejnosc dla kolejki rysowania.<br>
XE_SURFACE_COORD_SUBSTANCE_1: Koordynaty pierwszej tekstury.<br>
XE_SURFACE_COORD_SUBSTANCE_2: Koordynaty drugiej tekstury.<br>
XE_SURFACE_COORD_SUBSTANCE_3: Koordynaty trzeciej tekstury.<br>
XE_SURFACE_DIFFUSION: Rozproszenie swiatla.<br>
XE_SURFACE_MIRROR: Poziom odbicia swiatla.<br>
XE_SURFACE_ORIENTATION: Orientacja.
\return Wskaznik nieokreslony na zmienna stanu powierzchni. Nalezy rzutowac na konkretny typ danej zmiennej stanu.
*/
XE_IMPEX void* XE_CALLTYPE XeSurfaceGet(XeElmSurface index,XeEstate type);

/*--- XeSurfaceDestroy() ---*/
/*! Niszczy powierzchnie.
\param index Element powierzchni.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeSurfaceDestroy(XeElmSurface index);

/*--- XeSurfaceSort() ---*/
/*! Sortuje powierzchnie.
\param invert Sortowanie odwrotne.
*/
XE_IMPEX void XE_CALLTYPE XeSurfaceSort(bool invert);

/*--- XeParticleCreate() ---*/
/*! Tworzy czasteczke.
\param elm Wskaznik na element czasteczki. Zwraca do niego utworzony element jesli operacja powiodla sie.
*/
XE_IMPEX void XE_CALLTYPE XeParticleCreate(XeElmParticle* elm);

/*--- XeParticleSetSubstance() ---*/
/*! Ustala substancje.
\param index Element czasteczki.
\param substance Element substancji.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeParticleSetSubstance(XeElmParticle index,XeElmSubstance substance);

/*--- XeParticleSetSize() ---*/
/*! Ustala rozmiar.
\param index Element czasteczki.
\param size Rozmiar.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeParticleSetSize(XeElmParticle index,double size);

/*--- XeParticleSetTexture() ---*/
/*! Ustala teksture.
\param index Element czasteczki.
\param texture Element tekstury.
\param type Typ tekstury. Musi byc: XE_2D.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeParticleSetTexture(XeElmParticle index,Photon::XeElmTexture texture,XeEstate type);

/*--- XeParticleGet() ---*/
/*! Pobiera wartosc zmiennej stanu czasteczki.
\param index Element czasteczki.
\param type Zmienna stanu czasteczki. Dostepne wartosci:<br>
XE_PARTICLE_ID: Indeks czasteczki.<br>
XE_PARTICLE_WIDTH: Szerokosc.<br>
XE_PARTICLE_HEIGHT: Wysokosc.<br>
XE_PARTICLE_TEXTURE: Element tekstury.<br>
XE_PARTICLE_TEXTURE_TYPE: Typ tekstury.<br>
XE_PARTICLE_SUBSTANCE: Element substancji.
\return Wskaznik nieokreslony na zmienna stanu czasteczki. Nalezy rzutowac na konkretny typ danej zmiennej stanu.
*/
XE_IMPEX void* XE_CALLTYPE XeParticleGet(XeElmParticle index,XeEstate type);

/*--- XeParticleDestroy() ---*/
/*! Niszczy czasteczke.
\param index Element czasteczki.
*/
XE_IMPEX bool XE_CALLTYPE XeParticleDestroy(XeElmParticle index);

#endif // XE_COMPILE_PHOTON

/*--- XeGlobalForceCreate() ---*/
/*! Tworzy sile globalna.
\param elm Wskaznik na element sily globalnej. Zwraca do niego utworzony element jesli operacja powiodla sie.
*/
XE_IMPEX void XE_CALLTYPE XeGlobalForceCreate(XeElmGlobalForce* elm);

/*--- XeGlobalForceSetDirection() ---*/
/*! Ustala kierunek.
\param index Element sily globalnej.
\param dir Kierunek.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeGlobalForceSetDirection(XeElmGlobalForce index,XeAngleVector dir);

/*--- XeGlobalForceSetForce() ---*/
/*! Ustala sile.
\param index Element sily globalnej.
\param force Sila.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeGlobalForceSetForce(XeElmGlobalForce index,double force);

/*--- XeGlobalForceGet() ---*/
/*! Pobiera wartosc zmiennej stanu sily globalnej.
\param index Element sily globalnej.
\param type Zmienna stanu sily globalnej. Dostepne wartosci:<br>
XE_GLOBAL_FORCE_ID: Indeks sily globalnej.<br>
XE_GLOBAL_FORCE_DIRECTION: Kierunek.<br>
XE_GLOBAL_FORCE_FORCE: Sila.
\return Wskaznik nieokreslony na zmienna stanu sily globalnej. Nalezy rzutowac na konkretny typ danej zmiennej stanu.
*/
XE_IMPEX void* XE_CALLTYPE XeGlobalForceGet(XeElmGlobalForce index,XeEstate type);

/*--- XeGlobalForceDestroy() ---*/
/*! Niszczy sile globalna.
\param index Element sily globalnej.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeGlobalForceDestroy(XeElmGlobalForce index);

/*--- XeBlackHoleCreate() ---*/
/*! Tworzy czarna dziure.
\param elm Wskaznik na element czarnej dziury. Zwraca do niego utworzony element jesli operacja powiodla sie.
*/
XE_IMPEX void XE_CALLTYPE XeBlackHoleCreate(XeElmBlackHole* elm);

/*--- XeBlackHoleSetPosition() ---*/
/*! Ustala pozycje.
\param index Element czarnej dziury.
\param p Pozycja.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeBlackHoleSetPosition(XeElmBlackHole index,XeVector p);

/*--- XeBlackHoleSetForce() ---*/
/*! Ustala sile.
\param index Element czarnej dziury.
\param force Sila.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeBlackHoleSetForce(XeElmBlackHole index,double force);

/*--- XeBlackHoleSetRange() ---*/
/*! Ustala zasieg.
\param index Element czarnej dziury.
\param range Zasieg.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeBlackHoleSetRange(XeElmBlackHole index,double range);

/*--- XeBlackHoleSetAnchor() ---*/
/*! Ustala kotwice (czarna dziure z ktora jest polaczona).
\param index Element czarnej dziury.
\param anchor Element czarnej dziury.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeBlackHoleSetAnchor(XeElmBlackHole index,XeElmBlackHole anchor);

/*--- XeBlackHoleGet() ---*/
/*! Pobiera wartosc zmiennej stanu czarnej dziury.
\param index Element czarnej dziury.
\param type Zmienna stanu czarnej dziury. Dostepne wartosci:<br>
XE_BLACK_HOLE_ID: Indeks czarnej dziury.<br>
XE_BLACK_HOLE_POSITION: Pozycja.<br>
XE_BLACK_HOLE_FORCE: Sila.<br>
XE_BLACK_HOLE_RANGE: Zasieg.<br>
XE_BLACK_HOLE_ANCHOR: Element czarnej dziury.
\return Wskaznik nieokreslony na zmienna stanu czarnej dziury. Nalezy rzutowac na konkretny typ danej zmiennej stanu.
*/
XE_IMPEX void* XE_CALLTYPE XeBlackHoleGet(XeElmBlackHole index,XeEstate type);

/*--- XeBlackHoleDestroy() ---*/
/*! Niszczy czarna dziure.
\param index Element czarnej dziury.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeBlackHoleDestroy(XeElmBlackHole index);

/*--- XeWaveForceCreate() ---*/
/*! Tworzy sile falowa.
\param elm Wskaznik na element sily falowej. Zwraca do niego utworzony element jesli operacja powiodla sie.
*/
XE_IMPEX void XE_CALLTYPE XeWaveForceCreate(XeElmWaveForce* elm);

/*--- XeWaveForceSetPosition() ---*/
/*! Ustala pozycje.
\param index Element sily falowej.
\param p Pozycja.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeWaveForceSetPosition(XeElmWaveForce index,XeVector p);

/*--- XeWaveForceSetForce() ---*/
/*! Ustala sile.
\param index Element sily falowej.
\param force Sila.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeWaveForceSetForce(XeElmWaveForce index,double force);

/*--- XeWaveForceSetRange() ---*/
/*! Ustala zasieg.
\param index Element sily falowej.
\param range Zasieg.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeWaveForceSetRange(XeElmWaveForce index,double range);

/*--- XeWaveForceSetLength() ---*/
/*! Ustala dlugosc.
\param index Element sily falowej.
\param length Dlugosc.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeWaveForceSetLength(XeElmWaveForce index,double length);

/*--- XeWaveForceSetSpeed() ---*/
/*! Ustala predkosc.
\param index Element sily falowej.
\param speed Predkosc.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeWaveForceSetSpeed(XeElmWaveForce index,double speed);

/*--- XeWaveForceSetOrientation() ---*/
/*! Ustala sile.
\param index Element sily falowej.
\param orientation Orientacja. Dostepne wartosci:<br>
XE_WAVE_FORCE_ORIENTATION_IN: Sila dosrodkowa.<br>
XE_WAVE_FORCE_ORIENTATION_OUT: Sila odsrodkowa.<br>
XE_WAVE_FORCE_ORIENTATION_INNER: Sila dosrodkowa dla grzbietu fali.<br>
XE_WAVE_FORCE_ORIENTATION_OUTER: Sila odsrodkowa dla grzbietu fali.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeWaveForceSetOrientation(XeElmWaveForce index,XeEstate orientation);

/*--- XeWaveForceGet() ---*/
/*! Pobiera wartosc zmiennej stanu sily falowej.
\param index Element sily falowej.
\param type Zmienna stanu sily falowej. Dostepne wartosci:<br>
XE_WAVE_FORCE_ID: Indeks sily falowej.<br>
XE_WAVE_FORCE_POSITION: Pozycja.<br>
XE_WAVE_FORCE_FORCE: Sila.<br>
XE_WAVE_FORCE_RANGE: Zasieg.<br>
XE_WAVE_FORCE_LENGTH: Dlugosc.<br>
XE_WAVE_FORCE_SPEED: Predkosc.<br>
XE_WAVE_FORCE_ORIENTATION: Orientacja.
\return Wskaznik nieokreslony na zmienna stanu sily falowej. Nalezy rzutowac na konkretny typ danej zmiennej stanu.
*/
XE_IMPEX void* XE_CALLTYPE XeWaveForceGet(XeElmWaveForce index,XeEstate type);

/*--- XeWaveForceDestroy() ---*/
/*! Niszczy sile falowa.
\param index Element sily falowej.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeWaveForceDestroy(XeElmWaveForce index);

} // Chaos
} // XeCore

#endif // XE_COMPILE_CHAOS

#endif // _XE_CHAOS_EXPORTS_H_

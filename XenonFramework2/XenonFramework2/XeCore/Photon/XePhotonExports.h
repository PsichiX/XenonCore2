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

#ifndef _XE_PHOTON_EXPORTS_H_
#define _XE_PHOTON_EXPORTS_H_

#include "../XenonCore2.h"
#ifdef XE_COMPILE_PHOTON
#include "../XePhoton.h"
#ifdef XE_COMPILE_CHAOS
#include "../XeChaos.h"
#endif // XE_COMPILE_CHAOS
#include "../Base/XeMatrixTemplate.h"
#include "../Base/XeVectorTemplate.h"
#include "../Base/XeAngleVectorTemplate.h"
#include "../Base/XeFontmap.h"

//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{
//! \namespace XeCore::Photon Przestrzen nazw modulu Photon
namespace Photon
{

/*--- XeIsSupported() ---*/
/*! Sprawdza czy rozszerzenie jest obslugiwane.
\param extension Rozszerzenie.
\return true jesli rozszerzenie jest dostepne.
*/
XE_IMPEX bool XE_CALLTYPE XeIsSupported(XeEstate extension);

/*--- XeCameraOrtho() ---*/
/*! Uaktywnia projekcje prostopadla.
\param px Pozycja X na scenie.
\param py Pozycja Y na scenie.
\param width Szerokosc na scenie.
\param height Wysokosc na scenie.
\param angle Kat obrotu widoku.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeCameraOrtho(double px,double py,double width,double height,double angle);

/*--- XeCameraOrthoCustomBuild() ---*/
/*! Buduje macierz projekcji prostopadlej uzytkownika.
\param matrix Wskaznik na docelowa macierz.
\param px Pozycja X na scenie.
\param py Pozycja Y na scenie.
\param width Szerokosc na scenie.
\param height Wysokosc na scenie.
\param angle Kat obrotu widoku.
\param znear Najblizsza granica widocznosci.
\param zfar Najdalsza granica widocznosci.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeCameraOrthoCustomBuild(XeMatrix* matrix,double px,double py,double width,double height,double angle,double znear=-1.0,double zfar=1.0);

/*--- XeCameraOrthoCustomBuildHalf() ---*/
/*! Buduje macierz float projekcji prostopadlej uzytkownika.
\param matrix Wskaznik na docelowa macierz float.
\param px Pozycja X na scenie.
\param py Pozycja Y na scenie.
\param width Szerokosc na scenie.
\param height Wysokosc na scenie.
\param angle Kat obrotu widoku.
\param znear Najblizsza granica widocznosci.
\param zfar Najdalsza granica widocznosci.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeCameraOrthoCustomBuildHalf(XeHalfMatrix* matrix,float px,float py,float width,float height,float angle,float znear=-1.0f,float zfar=1.0f);

/*--- XeCameraOrthoBuild() ---*/
/*! Buduje macierz projekcji prostopadlej kamery.
\param matrix Wskaznik na docelowa macierz.
\param px Pozycja X na scenie.
\param py Pozycja Y na scenie.
\param width Szerokosc na scenie.
\param height Wysokosc na scenie.
\param angle Kat obrotu widoku.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeCameraOrthoBuild(XeMatrix* matrix,double px,double py,double width,double height,double angle=0.0);

/*--- XeCameraOrthoBuildHalf() ---*/
/*! Buduje macierz float projekcji prostopadlej kamery.
\param matrix Wskaznik na docelowa macierz float.
\param px Pozycja X na scenie.
\param py Pozycja Y na scenie.
\param width Szerokosc na scenie.
\param height Wysokosc na scenie.
\param angle Kat obrotu widoku.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeCameraOrthoBuildHalf(XeHalfMatrix* matrix,float px,float py,float width,float height,float angle=0.0f);

/*--- XeCameraPerspective() ---*/
/*! Uaktywnia projekcje perspektywistyczna.
\param a Kierunek oka kamery.
\param p Pozycja kamery.
\param projection Typ projekcji: false jesli oko patrzy z pozycji kamery; true jesli oko patrzy na pozycje kamery;
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeCameraPerspective(XeAngleVector a,XeVector p,bool projection=false);

/*--- XeCameraPerspectiveCustomBuild() ---*/
/*! Buduje macierz projekcji perspektywistycznej uzytkownika.
\param matrix Wskaznik na docelowa macierz.
\param a Kierunek oka kamery.
\param p Pozycja kamery.
\param projection Typ projekcji: false jesli oko patrzy z pozycji kamery; true jesli oko patrzy na pozycje kamery;
\param angle Kat stozka pola widzenia.
\param aspect Aspekt obrazu.
\param znear Najblizsza granica widocznosci.
\param zfar Najdalsza granica widocznosci.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeCameraPerspectiveCustomBuild(XeMatrix* matrix,XeAngleVector a,XeVector p,bool projection=false,double angle=45.0,double aspect=1.0,double znear=1.0,double zfar=10000.0);

/*--- XeCameraPerspectiveCustomBuildHalf() ---*/
/*! Buduje macierz float projekcji perspektywistycznej uzytkownika.
\param matrix Wskaznik na docelowa macierz.
\param a Kierunek oka kamery.
\param p Pozycja kamery.
\param projection Typ projekcji: false jesli oko patrzy z pozycji kamery; true jesli oko patrzy na pozycje kamery;
\param angle Kat stozka pola widzenia.
\param aspect Aspekt obrazu.
\param znear Najblizsza granica widocznosci.
\param zfar Najdalsza granica widocznosci.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeCameraPerspectiveCustomBuildHalf(XeHalfMatrix* matrix,XeAngleVector a,XeHalfVector p,bool projection=false,float angle=45.0f,float aspect=1.0f,float znear=1.0f,float zfar=10000.0f);

/*--- XeCameraPerspectiveBuild() ---*/
/*! Buduje macierz projekcji perspektywistycznej uzytkownika.
\param matrix Wskaznik na docelowa macierz.
\param a Kierunek oka kamery.
\param p Pozycja kamery.
\param projection Typ projekcji: false jesli oko patrzy z pozycji kamery; true jesli oko patrzy na pozycje kamery;
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeCameraPerspectiveBuild(XeMatrix* matrix,XeAngleVector a,XeVector p,bool projection=false);

/*--- XeCameraPerspectiveBuildHalf() ---*/
/*! Buduje macierz float projekcji perspektywistycznej uzytkownika.
\param matrix Wskaznik na docelowa macierz.
\param a Kierunek oka kamery.
\param p Pozycja kamery.
\param projection Typ projekcji: false jesli oko patrzy z pozycji kamery; true jesli oko patrzy na pozycje kamery;
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeCameraPerspectiveBuildHalf(XeHalfMatrix* matrix,XeAngleVector a,XeHalfVector p,bool projection=false);

/*--- XeCameraUpdate() ---*/
/*! Aktualizuje ostatnio ustawiona projekcje perspektywistyczna.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeCameraUpdate();

/*--- XeCameraFrom() ---*/
/*! Zwraca pozycje z ktorej patrzy kamera.
\return Pozycja kamery.
*/
XE_IMPEX bool XE_CALLTYPE XeCameraFrom(XeVector* v);

/*--- XeCameraTo() ---*/
/*! Zwraca pozycje na ktora patrzy kamera.
\return Pozycja oka kamery.
*/
XE_IMPEX bool XE_CALLTYPE XeCameraTo(XeVector* v);

/*--- XeCameraUp() ---*/
/*! Zwraca wartosc znormalizowanego wektora gory kamery.
\return Wektor gory kamery.
*/
XE_IMPEX bool XE_CALLTYPE XeCameraUp(XeVector* v);

/*--- XeExtensions() ---*/
/*! Inicjalizacja rozszerzen.
\param forced Ustala czy rozszerzenia maja byc zainicjowane mimo iz juz wczesniej byly zainicjowane.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeExtensions(bool forced=false);

/*--- XeRenderExecute() ---*/
/*! Wysyla do karty rozkaz wykonania wywolanych operacji rederingu.
\param mode Typ rozkazu. Dostepne wartosci:<br>
XE_FLUSH: Nakazuje wykonanie operacji najszybciej na ile pozwala na to karta.<br>
XE_FINISH: Nakazuje wykonanie operacji czekajac dopuki nie zostana wszystkie wykonane.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeRenderExecute(XeEstate mode);

/*--- XeRenderScene() ---*/
/*! Renderuje scene.
\param flag Flagi operacji. Dostepne wartosci:<br>
XE_FLAG_SWAP: Zamienia bufory ramki.<br>
XE_FLAG_COLORBUFF: Czysci bufor koloru.<br>
XE_FLAG_DEPTHBUFF: Czysci bufor glebi.<br>
XE_FLAG_ACCUMBUFF: Czysci bufor akumulacyjny.<br>
XE_FLAG_STENCILBUFF: Czysci bufor szablonowy.<br>
XE_FLAG_TRANSFORMIDENT: Resetuje transformacje (laduje macierz jednostkowa).
\return true jesli operacja powiodla sie
*/
XE_IMPEX bool XE_CALLTYPE XeRenderScene(unsigned int flag);

/*--- XeRenderGetData() ---*/
/*! Pobiera dane pixeli z bufora ramki.
\param x Pozycja X (zaczynajac od lewego dolnego rogu).
\param y Pozycja Y (zaczynajac od lewego dolnego rogu).
\param w Szerokosc.
\param h Wysokosc.
\param format Typ bufora. Dostepne wartosci:<br>
XE_RENDER_FORMAT_RGBA: Bufor koloru.<br>
XE_RENDER_FORMAT_STENCIL: Bufor szablonowy.<br>
XE_RENDER_FORMAT_DEPTH: Bufor glebi.
\param buffer Wskaznik na bufor do ktorego zapisze dane.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeRenderGetData(int x,int y,int w,int h,XeEstate format,void* buffer);

/*--- XeRenderDrawData() ---*/
/*! Wpisuje dane pixeli do bufora ramki.
\param x Pozycja X (zaczynajac od lewego dolnego rogu).
\param y Pozycja Y (zaczynajac od lewego dolnego rogu).
\param w Szerokosc.
\param h Wysokosc.
\param format Typ bufora. Dostepne wartosci:<br>
XE_RENDER_FORMAT_RGBA: Bufor koloru.<br>
XE_RENDER_FORMAT_STENCIL: Bufor szablonowy.<br>
XE_RENDER_FORMAT_DEPTH: Bufor glebi.
\param buffer Wskaznik na bufor z ktorego wczyta dane.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeRenderDrawData(int x,int y,int w,int h,XeEstate format,void* buffer);

/*--- XeRenderVsync() ---*/
/*! Wlacza badz wylacza pionowa synchronizacje obrazu.
\param mode XE_TRUE jesli ma wlaczyc, XE_FALSE jesli ma wylaczyc synchronizacje.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeRenderVsync(XeEstate mode);

/*--- XeRenderTargetCreate() ---*/
/*! Tworzy kontekst renderowania.
\param elm Wskaznik na element RenderTarget. Zwraca do niego utworzony element jesli operacja powiodla sie.
\param handle Uchwyt okna do ktorego podepniemy kontekst.
\param mode Tryb rysowania. Dostepne wartosci:<br>
XE_DRAW_TO_WINDOW: Rysowanie do okna.<br>
XE_DRAW_TO_LAYER: Rysowanie do warstwy (polprzezroczystego okna).
\param bits Ilosc bitow glebi koloru (8,16,24,32).
\param depthbits Ilosc bitow bufora glebi (8,16,24,32).
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeRenderTargetCreate(XeElmRenderTarget* elm,HANDLE handle,XeEstate mode,int bits,int depthbits);

/*--- XeRenderTargetDestroy() ---*/
/*! Niszczy kontekst renderowania.
\param index Element RenderTarget.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeRenderTargetDestroy(XeElmRenderTarget index);

/*--- XeRenderTargetChange() ---*/
/*! Zmienia tryb kontekstu renderowania.
\param index Element RenderTarget.
\param mode Tryb rysowania. Dostepne wartosci:<br>
XE_DRAW_TO_WINDOW: Rysowanie do okna.<br>
XE_DRAW_TO_LAYER: Rysowanie do warstwy (polprzezroczystego okna).
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeRenderTargetChange(XeElmRenderTarget index,XeEstate mode);

/*--- XeRenderTargetActivate) ---*/
/*! Aktywuje kontekst renderowania.
\param index Element RenderTarget.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeRenderTargetActivate(XeElmRenderTarget index);

/*--- XeRenderTargetRelease() ---*/
/*! Zwalnia aktywny kontekst renderowania. */
XE_IMPEX void XE_CALLTYPE XeRenderTargetRelease();

/*--- XeRenderTargetShare() ---*/
/*! Wspoldzieli zasoby graficzne z danym kontekstem.
\param index Element RenderTarget.
\param target Element RenderTarget z ktorym ma wspoldzielic zasoby.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeRenderTargetShare(XeElmRenderTarget index,XeElmRenderTarget target);

/*--- XeRenderTargetArea() ---*/
/*! Ustawia wlasciwosci pola viewportu.
\param index Element RenderTarget.
\param x Pozycja X w oknie.
\param y Pozycja Y w oknie.
\param width Szerokosc w oknie.
\param height Wysokosc w oknie.
\param angle Kat pola widzenia w perspektywie.
\param znear Najblizsza wartosc Z-bufora.
\param zfar Najdalsza wartosc Z-bufora.
\param aspect Aspekt obrazu.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeRenderTargetArea(XeElmRenderTarget index,int x,int y,int width,int height,double angle=45,double znear=-1,double zfar=1,double aspect=0);

/*--- XeRenderTargetGet() ---*/
/*! Pobiera wartosc zmiennej stanu kontekstu.
\param index Element RenderTarget.
\param type Zmienna stanu. Dostepne wartosci:<br>
XE_RENDERTARGET_WINDOW_HANDLE: Uchwyt okna.<br>
XE_RENDERTARGET_DISPLAY_CONTEXT: Kontekst wyswietlania.<br>
XE_RENDERTARGET_RENDER_CONTEXT: Kontenkst renderingu.<br>
XE_RENDERTARGET_X: Pozycja X.<br>
XE_RENDERTARGET_Y: Pozycja Y.<br>
XE_RENDERTARGET_WIDTH: Szerokosc.<br>
XE_RENDERTARGET_HEIGHT: Wysokosc.<br>
XE_RENDERTARGET_ANGLE: Kat pola widzenia w perspektywie.<br>
XE_RENDERTARGET_ZNEAR: Najblizsza wartosc Z-bufora.<br>
XE_RENDERTARGET_ZFAR: Najdalsza wartosc Z-bufora.<br>
XE_RENDERTARGET_ASPECT: Aspekt obrazu.
XE_RENDERTARGET_DRAW_MODE: Tryb rysowania na ekranie. Dostepne wartosci:<br>
XE_DRAW_TO_WINDOW: Rysowanie do okna.<br>
XE_DRAW_TO_LAYER: Rysowanie do warstwy (polprzezroczystego okna).
\return Wskaznik nieokreslony na zmienna stanu kontekstu. Nalezy rzutowac na konkretny typ danej zmiennej stanu.
*/
XE_IMPEX void* XE_CALLTYPE XeRenderTargetGet(XeElmRenderTarget index,XeEstate type);

/*--- XeFrameBufferCreate() ---*/
/*! Tworzy bufor ramki.
\param elm Wskaznik na element bufora ramki.
\param width Szerokosc.
\param height Wysokosc.
\param type Typ tekstury bufora ramki. Dostepne wartosci:<br>
XE_2D: Tekstura 2D.<br>
XE_DATA: Tekstura float.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeFrameBufferCreate(XeElmFrameBuffer* elm,int width,int height,XeEstate type=XE_2D);

/*--- XeFrameBufferCreateFromTexture() ---*/
/*! Tworzy bufor ramki.
\param elm Wskaznik na element bufora ramki.
\param tex Element tekstury.
\param forcednofbo Ustala czy bufor ramki ma bazowac wylacznie na teksturze, nawet gdy obsluguje FBO.
\return true jesli operacja powiodla sie.
*/
//XE_IMPEX bool XE_CALLTYPE XeFrameBufferCreateFromTexture(XeElmFrameBuffer* elm,XeElmTexture tex,bool forcednofbo=false);

/*--- XeFrameBufferDestroy() ---*/
/*! Niszczy bufor ramki.
\param index Element bufora ramki.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeFrameBufferDestroy(XeElmFrameBuffer index);

/*--- XeFrameBufferActivate() ---*/
/*! Aktywuje bufor ramki.
\param index Element bufora ramki.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeFrameBufferActivate(XeElmFrameBuffer index);

/*--- XeFrameBufferActivateTexture() ---*/
/*! Aktywuje bufor ramki jako teksture.
\param index Element bufora ramki.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeFrameBufferActivateTexture(XeElmFrameBuffer index);

/*--- XeFrameBufferUnactivateTexture() ---*/
/*! Dezaktywuje teksture bufora ramki.
\param index Element bufora ramki.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeFrameBufferUnactivateTexture(XeElmFrameBuffer index);

/*--- XeFrameBufferActivateTextureDepth() ---*/
/*! Aktywuje bufor ramki jako teksture glebi.
\param index Element bufora ramki.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeFrameBufferActivateTextureDepth(XeElmFrameBuffer index);

/*--- XeFrameBufferUnactivateTextureDepth() ---*/
/*! Dezaktywuje teksture glebi bufora ramki.
\param index Element bufora ramki.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeFrameBufferUnactivateTextureDepth(XeElmFrameBuffer index);

/*--- XeFrameBufferUnactivate() ---*/
/*! Dezaktywuje bufor ramki.
\param index Element bufora ramki.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeFrameBufferUnactivate(XeElmFrameBuffer index);

/*--- XeFrameBufferMipmap() ---*/
/*! Generuje mipmapy dla tekstury bufora ramki.
\param index Element bufora ramki.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeFrameBufferMipmap(XeElmFrameBuffer index);

/*--- XeFrameBufferSwapTexture() ---*/
/*! Podmienia zawartosc tekstury, tylko wtedy gdy maja te same wymiary.
\param index Element bufora ramki.
\param tex Element tekstury.
\return true jesli operacja powiodla sie.
*/
//XE_IMPEX bool XE_CALLTYPE XeFrameBufferSwapTexture(XeElmFrameBuffer index,XeElmTexture tex);

/*--- XeFrameBufferGet() ---*/
/*! Pobiera wartosc zmiennej stanu bufora ramki.
\param index Element bufora ramki.
\param type Zmienna stanu. Dostepne wartosci:<br>
XE_PIXELBUFFER_WIDTH: Szerokosc.<br>
XE_PIXELBUFFER_HEIGHT: Wysokosc.<br>
XE_PIXELBUFFER_TEXTURE: Tekstura.<br>
XE_PIXELBUFFER_TEXTURE_DEPTH: Tekstura glebi.<br>
\return Wskaznik nieokreslony na zmienna stanu bufora ramki. Nalezy rzutowac na konkretny typ danej zmiennej stanu.
*/
XE_IMPEX void* XE_CALLTYPE XeFrameBufferGet(XeElmFrameBuffer index,XeEstate type);

/*--- XeFrameBufferUseFBO() ---*/
/*! Sprawdza czy bufor ramki uzywa rozszerzenia FBO.
\param index Element bufora ramki.
\return true jesli uzywa rozszerzenia FBO.
*/
//XE_IMPEX bool XE_CALLTYPE XeFrameBufferUseFBO(XeElmFrameBuffer index);

/*--- XeVertexBufferInit() ---*/
/*! Inicjuje obsluge bufora wierzcholkow.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeVertexBufferInit();

/*--- XeVertexBufferCreate() ---*/
/*! Tworzy bufor wierzcholkow.
\param elm Wskaznik na element bufora wierzcholkow.
\param maxsize Maksymalny rozmiar bufora wierzcholkow w bajtach.
\param data Wskaznik na dane bufora wierzcholkow.
\param type Typ obslugi bufora wierzcholkow. Dostepne wartosci:<br>
XE_VERTEXBUFFER_DYNAMIC_COPY: Dane beda aktualizowane. Przeplyw danych GPU->GPU.<br>
XE_VERTEXBUFFER_DYNAMIC_DRAW: Dane beda aktualizowane. Przeplyw danych APP->GPU.<br>
XE_VERTEXBUFFER_DYNAMIC_READ: Dane beda aktualizowane. Przeplyw danych GPU->APP.<br>
XE_VERTEXBUFFER_STATIC_COPY: Dane nie beda aktualizowane. Przeplyw danych GPU->GPU.<br>
XE_VERTEXBUFFER_STATIC_DRAW: Dane nie beda aktualizowane. Przeplyw danych APP->GPU.<br>
XE_VERTEXBUFFER_STATIC_READ: Dane nie beda aktualizowane. Przeplyw danych GPU->APP.<br>
XE_VERTEXBUFFER_STREAM_COPY: Dane beda aktualizowane co klatke. Przeplyw danych GPU->GPU.<br>
XE_VERTEXBUFFER_STREAM_DRAW: Dane beda aktualizowane co klatke. Przeplyw danych APP->GPU.<br>
XE_VERTEXBUFFER_STREAM_READ: Dane beda aktualizowane co klatke. Przeplyw danych GPU->APP.
\param maxsizeindices Maksymalny rozmiar bufora indeksow w bajtach.
\param dataindices Wskaznik na dane bufora indeksow.
\param typeindices Typ obslugi bufora indeksow. Dostepne wartosci:<br>
XE_VERTEXBUFFER_DYNAMIC_COPY: Dane beda aktualizowane. Przeplyw danych GPU->GPU.<br>
XE_VERTEXBUFFER_DYNAMIC_DRAW: Dane beda aktualizowane. Przeplyw danych APP->GPU.<br>
XE_VERTEXBUFFER_DYNAMIC_READ: Dane beda aktualizowane. Przeplyw danych GPU->APP.<br>
XE_VERTEXBUFFER_STATIC_COPY: Dane nie beda aktualizowane. Przeplyw danych GPU->GPU.<br>
XE_VERTEXBUFFER_STATIC_DRAW: Dane nie beda aktualizowane. Przeplyw danych APP->GPU.<br>
XE_VERTEXBUFFER_STATIC_READ: Dane nie beda aktualizowane. Przeplyw danych GPU->APP.<br>
XE_VERTEXBUFFER_STREAM_COPY: Dane beda aktualizowane co klatke. Przeplyw danych GPU->GPU.<br>
XE_VERTEXBUFFER_STREAM_DRAW: Dane beda aktualizowane co klatke. Przeplyw danych APP->GPU.<br>
XE_VERTEXBUFFER_STREAM_READ: Dane beda aktualizowane co klatke. Przeplyw danych GPU->APP.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeVertexBufferCreate(XeElmVertexBuffer* elm,int maxsize,void* data,XeEstate type,int maxsizeindices,void* dataindices,XeEstate typeindices);

/*--- XeVertexBufferDestroy() ---*/
/*! Niszczy bufor wierzcholkow.
\param index Element bufora wierzcholkow.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeVertexBufferDestroy(XeElmVertexBuffer index);

/*--- XeVertexBufferActivate() ---*/
/*! Aktywuje bufor wierzcholkow.
\param index Element bufora wierzcholkow.
\param mode Tryb bufora wierzcholkow. Dostepne wartosci:<br>
XE_VERTEXBUFFER_ARRAY: Bufor wierzcholkow.<br>
XE_VERTEXBUFFER_ELEMENT: Bufor indeksow.
*/
XE_IMPEX void XE_CALLTYPE XeVertexBufferActivate(XeElmVertexBuffer index,XeEstate mode);

/*--- XeVertexBufferUnactivate() ---*/
/*! Dezaktywuje bufor wierzcholkow.
\param mode Tryb bufora wierzcholkow. Dostepne wartosci:<br>
XE_VERTEXBUFFER_ARRAY: Bufor wierzcholkow.<br>
XE_VERTEXBUFFER_ELEMENT: Bufor indeksow.
*/
XE_IMPEX void XE_CALLTYPE XeVertexBufferUnactivate(XeEstate mode);

/*--- XeVertexBufferSendData() ---*/
/*! Wysyla i podmienia dane w buforze wierzcholkow.
\param mode Tryb bufora wierzcholkow. Dostepne wartosci:<br>
XE_VERTEXBUFFER_ARRAY: Bufor wierzcholkow.<br>
XE_VERTEXBUFFER_ELEMENT: Bufor indeksow.
\param size Rozmiar danych w bajtach.
\param offset Przesuniecie danych w bajtach.
\param data Wskaznik na dane do przeslania.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeVertexBufferSendData(XeEstate mode,int size,int offset,void* data);

/*--- XeVertexBufferMap() ---*/
/*! Mapuje bufor wierzcholkow (pobiera wskaznik na niego i blokuje mozliwosc renderowania go).
\param mode Tryb bufora wierzcholkow. Dostepne wartosci:<br>
XE_VERTEXBUFFER_ARRAY: Bufor wierzcholkow.<br>
XE_VERTEXBUFFER_ELEMENT: Bufor indeksow.
\param type Typ dostepu do danych. Dostepne wartosci:<br>
XE_VERTEXBUFFER_READ: Tylko do odczytu.<br>
XE_VERTEXBUFFER_WRITE: Tylko do zapisu.<br>
XE_VERTEXBUFFER_READWRITE: Do zapisu i odczytu.
\return Wskaznik na bufor jesli operacja powiodla sie, lub wartosc NULL jesli nie.
*/
XE_IMPEX void* XE_CALLTYPE XeVertexBufferMap(XeEstate mode,XeEstate type);

/*--- XeVertexBufferUnmap() ---*/
/*! Odmapowuje bufor wierzcholkow (odblokowuje mozliwosc renderowania go).
\param mode Tryb bufora wierzcholkow. Dostepne wartosci:<br>
XE_VERTEXBUFFER_ARRAY: Bufor wierzcholkow.<br>
XE_VERTEXBUFFER_ELEMENT: Bufor indeksow.
*/
XE_IMPEX void XE_CALLTYPE XeVertexBufferUnmap(XeEstate mode);

/*--- XeVertexBufferHasBuffer() ---*/
/*! Sprawdza czy bufor posiada konkretny typ bufora wierzcholkow.
\param index Element bufora wierzcholkow.
\param mode Tryb bufora wierzcholkow. Dostepne wartosci:<br>
XE_VERTEXBUFFER_ARRAY: Bufor wierzcholkow.<br>
XE_VERTEXBUFFER_ELEMENT: Bufor indeksow.
\return true jesli posiada dany typ bufora wierzcholkow.
*/
XE_IMPEX bool XE_CALLTYPE XeVertexBufferHasBuffer(XeElmVertexBuffer index,XeEstate mode);

/*--- XeVertexBufferSize() ---*/
/*! Zwraca rozmiar danego bufora wierzcholkow w bajtach.
\param index Element bufora wierzcholkow.
\param mode Tryb bufora wierzcholkow. Dostepne wartosci:<br>
XE_VERTEXBUFFER_ARRAY: Bufor wierzcholkow.<br>
XE_VERTEXBUFFER_ELEMENT: Bufor indeksow.
\return Rozmiar bufora.
*/
XE_IMPEX int XE_CALLTYPE XeVertexBufferSize(XeElmVertexBuffer index,XeEstate mode);

/*--- XeShaderInit() ---*/
/*! Inicjuje obsluge shaderow.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeShaderInit();

/*--- XeShaderModel() ---*/
/*! Zwraca Shader Model obslugiwany przez silnik i karte graficzna.
\return obs³ugiwany Shader Model.
*/
XE_IMPEX int XE_CALLTYPE XeShaderModel();

/*--- XeShaderCreate() ---*/
/*! Tworzy shader.
\param elm Wskaznik na element shadera.
*/
XE_IMPEX void XE_CALLTYPE XeShaderCreate(XeElmShader* elm);

/*--- XeShaderDestroy() ---*/
/*! Niszczy shader.
\param index Element shadera.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeShaderDestroy(XeElmShader index);

/*--- XeShaderProfile() ---*/
/*! Zwraca profil shadera.
\param index Element shadera.
\return Profil shadera.
*/
XE_IMPEX XeEstate XE_CALLTYPE XeShaderProfile(XeElmShader index);

/*--- XeShaderLoad() ---*/
/*! Laduje shader z pliku.
\param index Element shadera.
\param mode Profil shadera.
\param filename Nazwa pliku.
\param prepend Dodatkowe dane na poczatku bufora (wartosc NULL jesli brak danych).
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeShaderLoad(XeElmShader index,XeEstate mode,char* filename,char* prepend);

/*--- XeShaderLoadFromMemory() ---*/
/*! Laduje shader z pamieci.
\param index Element shadera.
\param mode Profil shadera.
\param buff Bufor z zawartoscia shadera.
\param prepend Dodatkowe dane na poczatku bufora (wartosc NULL jesli brak danych).
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeShaderLoadFromMemory(XeElmShader index,XeEstate mode,char* buff,char* prepend);

/*--- XeShaderMakeProgram() ---*/
/*! Tworzy program cieniowania laczac poszczegolne shadery.
\param index Element shadera.
\param shaders Tablica shaderow do polaczenia.
\param count Liczba shaderow do polaczenia.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeShaderMakeProgram(XeElmShader index,XeElmShader* shaders,unsigned int count);

/*--- XeShaderLastLog() ---*/
/*! Zwraca wskaznik na cstring z trescia ostatniego logu akcji shadera.
\return Wskaznik na cstring logu.
*/
XE_IMPEX char* XE_CALLTYPE XeShaderLastLog();

/*--- XeShaderActivate() ---*/
/*! Aktywuje shader.
\param index Element shadera.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeShaderActivate(XeElmShader index);

/*--- XeShaderUnactivate() ---*/
/*! Deaktywuje shader danego typu.
\param type Profil shadera.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeShaderUnactivate(XeEstate type);

/*--- XeShaderLocalParam() ---*/
/*! Ustala wartosc zmiennej lokalnej.
\param mode Profil shadera.
\param index Indeks zmiennej lokalnej.
\param v Wektor wartosci.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeShaderLocalParam(XeEstate mode,int index,XeHalfVector v);

/*--- XeShaderEnvParam() ---*/
/*! Ustala wartosc zmiennej srodowiskowej.
\param mode Profil shadera.
\param index Indeks zmiennej srodowiskowej.
\param v Wektor wartosci.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeShaderEnvParam(XeEstate mode,int index,XeHalfVector v);

/*--- XeShaderUniformLocation() ---*/
/*! Zwraca indeks zmiennej (profil: XE_SHADER_PROGRAM_SL).
\param index Element shadera.
\param name Nazwa zmiennej.
\return Indeks zmiennej.
*/
XE_IMPEX int XE_CALLTYPE XeShaderUniformLocation(XeElmShader index,char* name);

/*--- XeShaderUniform() ---*/
/*! Ustala wartosc zmiennej (profil: XE_SHADER_PROGRAM_SL).
\param index Indeks zmiennej.
\param v Wektor wartosci.
\param subs Ilosc komponentow wysylanych do zmiennej.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeShaderUniform(int index,XeHalfVector v,int subs=4);

/*--- XeShaderUniformArray() ---*/
/*! Ustala wartosc zmiennej (profil: XE_SHADER_PROGRAM_SL).
\param index Indeks zmiennej.
\param v Wskaznik tablicy wartosci float.
\param count Ilosc elementow.
\param subs Ilosc komponentow wysylanych do zmiennej.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeShaderUniformArray(int index,float* v,int count,int subs=4);

/*--- XeShaderUniformInteger() ---*/
/*! Ustala wartosc zmiennej calkowitej (profil: XE_SHADER_PROGRAM_SL).
\param index Indeks zmiennej.
\param s Tablica 4 elementow wartosci.
\param subs Ilosc komponentow wysylanych do zmiennej.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeShaderUniformInteger(int index,int s[4],int subs=4);

/*--- XeShaderUniformArrayInteger() ---*/
/*! Ustala wartosc zmiennej calkowitej (profil: XE_SHADER_PROGRAM_SL).
\param index Indeks zmiennej.
\param s Wskaznik tablcy wartosci int.
\param count Ilosc elementow.
\param subs Ilosc komponentow wysylanych do zmiennej.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeShaderUniformArrayInteger(int index,int* s,int count,int subs=4);

/*--- XeShaderUniformMatrix() ---*/
/*! Ustala wartosc zmiennej - macierz (profil: XE_SHADER_PROGRAM_SL).
\param index Indeks zmiennej.
\param m Macierz wartosci.
\param transpose Ustala czy macierz ma byc transponowana.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeShaderUniformMatrix(int index,XeHalfMatrix* m,bool transpose=false);

/*--- XeShaderAttributeLocation() ---*/
/*! Zwraca indeks atrybutu (profil: XE_SHADER_PROGRAM_SL).
\param index Element shadera.
\param name Nazwa atrybutu.
\return Indeks atrybutu.
*/
XE_IMPEX int XE_CALLTYPE XeShaderAttributeLocation(XeElmShader index,char* name);

/*--- XeShaderAttribute() ---*/
/*! Ustala wartosc atrybutu (profil: XE_SHADER_PROGRAM_SL).
\param index Indeks atrybutu.
\param v Wektor wartosci.
\param subs Ilosc komponentow wysylanych do atrybutu.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeShaderAttribute(int index,XeHalfVector v,int subs=4);

/*--- XeTextureCreate() ---*/
/*! Tworzy teksture i automatycznie ja aktywuje.
\param elm Wskaznik na element tekstury. Zwraca do niego utworzony element jesli operacja powiodla sie.
*/
XE_IMPEX void XE_CALLTYPE XeTextureCreate(XeElmTexture* elm);

/*--- XeTextureDestroy() ---*/
/*! Niszczy teksture.
\param index Element tekstury.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeTextureDestroy(XeElmTexture index);

/*--- XeTextureLoad() ---*/
/*! Laduje teksture z pliku.
\param index Element tekstury.
\param filename Cstring z nazwa pliku.
\param achannel Jesli true to laduje z kanalem przezroczystosci.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeTextureLoad(XeElmTexture index,char* filename,bool achannel);

/*--- XeTextureLoadEmpty() ---*/
/*! Laduje pusta teksture 2D.
\param index Element tekstury.
\param width Szerokosc tekstury.
\param height Wysokosc tekstury.
\param achannel Jesli true to laduje z kanalem przezroczystosci.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeTextureLoadEmpty(XeElmTexture index,int width,int height,bool achannel);

/*--- XeTextureLoadFromMemory() ---*/
/*! Laduje teksture 2D z pamieci.
\param index Element tekstury.
\param buff Wskaznik na bufor w ktorym sa dane tekstury.
\param achannel Jesli true to laduje z kanalem przezroczystosci.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeTextureLoadFromMemory(XeElmTexture index,void* buff,bool achannel);

/*--- XeTextureLoadRGBA() ---*/
/*! Laduje teksture 2D RAW RGBA z pliku.
\param index Element tekstury.
\param filename Cstring z nazwa pliku.
\param width Szerokosc tekstury RAW RGBA.
\param height Wysokosc tekstury RAW RGBA.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeTextureLoadRGBA(XeElmTexture index,char* filename,int width,int height);

/*--- XeTextureLoadRGBAFromMemory() ---*/
/*! Laduje teksture 2D RAW RGBA z pamieci.
\param index Element tekstury.
\param buff Wskaznik na bufor w ktorym sa dane tekstury RAW RGBA.
\param width Szerokosc tekstury RAW RGBA.
\param height Wysokosc tekstury RAW RGBA.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeTextureLoadRGBAFromMemory(XeElmTexture index,void* buff,int width,int height);

/*--- XeTextureFromRender() ---*/
/*! Laduje teksture 2D z bufora kolorow aktywnego kontekstu renderujacego.
\param index  Element tekstury.
\param x Pozycja X w buforze.
\param y Pozycja Y w buforze.
\param width Szerokosc w buforze.
\param height Wysokosc w buforze.
\param asnew Tworzy nowa teksture jesli wartosc jest true, jesli zas false to zastepuje istniejace dane.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeTextureFromRender(XeElmTexture index,int x,int y,int width,int height,bool asnew);

/*--- XeTextureLoadEmptyData() ---*/
/*! Laduje pusta teksture float.
\param index Element tekstury.
\param width Szerokosc tekstury.
\param height Wysokosc tekstury.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeTextureLoadEmptyData(XeElmTexture index,int width,int height);

/*--- XeTextureLoadData() ---*/
/*! Laduje teksture float RAW RGBA z pamieci.
\param index Element tekstury.
\param buff Wskaznik na bufor w ktorym sa dane tekstury RAW RGBA.
\param width Szerokosc tekstury RAW RGBA.
\param height Wysokosc tekstury RAW RGBA.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeTextureLoadData(XeElmTexture index,void* buff,int width,int height);

/*--- XeTextureLoadEmptyDepth() ---*/
/*! Laduje pusta teksture glebi.
\param index Element tekstury.
\param width Szerokosc tekstury.
\param height Wysokosc tekstury.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeTextureLoadEmptyDepth(XeElmTexture index,int width,int height);

/*--- XeTextureLoadDepth() ---*/
/*! Laduje teksture glebi z pamieci.
\param index Element tekstury.
\param buff Wskaznik na bufor w ktorym sa dane tekstury.
\param width Szerokosc tekstury.
\param height Wysokosc tekstury.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeTextureLoadDepth(XeElmTexture index,void* buff,int width,int height);

/*--- XeTextureUpdate() ---*/
/*! Aktualizuje teksture pobierajac piksele z danego bufora.
\param index Element tekstury.
\param data Wskaznik na bufor danych pikseli.
\param x Pozycja X w buforze.
\param y Pozycja Y w buforze.
\param width Szerokosc w buforze.
\param height Wysokosc w buforze.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeTextureUpdate(XeElmTexture index,void* data,int x,int y,int width,int height);

/*--- XeTextureActivate() ---*/
/*! Aktywuje teksture.
\param index Element tekstury.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeTextureActivate(XeElmTexture index);

/*--- XeTextureUnactivate() ---*/
/*! Dezaktywuje teksture.
\param index Element tekstury.
*/
XE_IMPEX void XE_CALLTYPE XeTextureUnactivate(XeElmTexture index);

/*--- XeTextureLock() ---*/
/*! Blokuje piksele tekstury i umieszcza je w podrecznym buforze.
\param index Element tekstury.
\param lockasxet Ustala czy blokowane piksele maja byc kompilowane do formatu XET.
\return Wskaznik na bufor pikseli lub wartosc NULL jesli operacja nie powiodla sie.
*/
XE_IMPEX void* XE_CALLTYPE XeTextureLock(XeElmTexture index,bool lockasxet=false);

/*--- XeTextureUnlock() ---*/
/*! Odblokowuje piksele tekstury.
\param index Element tekstury.
\param update Ustala czy ma zaktualizowac piksele tekstury z bufora.
*/
XE_IMPEX void XE_CALLTYPE XeTextureUnlock(XeElmTexture index,bool update);

/*--- XeTextureIsLocked() ---*/
/*! Sprawdza czy piksele tekstury sa zablokowane.
\param index Element tekstury.
\return true jesli piksele sa zablokowane.
*/
XE_IMPEX bool XE_CALLTYPE XeTextureIsLocked(XeElmTexture index);

/*--- XeTextureParamater() ---*/
/*! Ustala parametr aktywnej tekstury.
\param type Typ parametru. Dostepne wartosci:<br>
XE_TEXTURE_PARAM_PRIORITY: Priorytet tekstury (zakres: <0;1>).<br>
XE_TEXTURE_PARAM_MIN_FILTER: Filtr pomniejszajacy.<br>
XE_TEXTURE_PARAM_MAG_FILTER: Filtr powiekszajacy.<br>
XE_TEXTURE_PARAM_WRAP_S: Poziome powtarzanie tekstury.<br>
XE_TEXTURE_PARAM_WRAP_T: Pionowe powtarzanie tekstury.
\param value Wartosc parametru.
*/
XE_IMPEX void XE_CALLTYPE XeTextureParameter(XeEstate type,float value);

/*--- XeTextureMode() ---*/
/*! Ustala tryb mieszania kolorow tekstur z kolorami wierzcholkow.
\param mode Tryb mieszania. Dostepne wartosci:<br>
XE_TEXTURE_MODE_ADD: Dodaje kolor tekstury do koloru wierzcholka.<br>
XE_TEXTURE_MODE_MODULATE: Moduluje kolor tekstury przez kolor wierzcholka.<br>
XE_TEXTURE_MODE_DECAL: Zastepuje kolor wierzcholka kolorem tekstury.<br>
XE_TEXTURE_MODE_BLEND: Miesza kolor wierzcholka z kolorem tekstury.<br>
XE_TEXTURE_MODE_REPLACE: Zastepuje kolor wierzcholka kolorem tekstury.<br>
XE_TEXTURE_MODE_COMBINE: Opcje mieszania dla multitekstur .[Obecnie wartosc nie uzywana]
*/
XE_IMPEX void XE_CALLTYPE XeTextureMode(XeEstate mode);

/*--- XeTextureMulti() ---*/
/*! Wlacza tryb multiteksturingu.
Pozwala to na mieszanie tekstur poprzez uzywanie wiecej niz jednej jednostki teksturujacej.
Dodatkowo umieszcza w zmiennej stanu XE_TEXTURE_UNIT_COUNT wartosc maxymalnej liczby jednostek teksturowania jaka dysponuje karta.
\return true jesli operacja powiodla sie; false jesli karta nie obsluguje wieloteksturowania.
*/
XE_IMPEX bool XE_CALLTYPE XeTextureMulti();

/*--- XeTextureUnit() ---*/
/*! Aktywuje jednostke teksturowania.
\param unit Numer jednostki teksturowania.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeTextureUnit(int unit);

/*--- XeTextureGet() ---*/
/*! Pobiera wartosc zmiennej stanu tekstury.
\param index Element tekstury.
\param type Zmienna stanu. Dostepne wartosci:<br>
XE_TEXTURE_WIDTH: Szerokosc tekstury.<br>
XE_TEXTURE_HEIGHT: Wysokosc tekstury.<br>
XE_TEXTURE_PIXEL_BUFFER: Wskaznik na bufor zablokowanych pikseli.<br>
XE_TEXTURE_PIXEL_SIZE: Rozmiar bufora zablokowanych pikseli.
\return Wskaznik nieokreslony na zmienna stanu tekstury. Nalezy rzutowac na konkretny typ danej zmiennej stanu.
*/
XE_IMPEX void* XE_CALLTYPE XeTextureGet(XeElmTexture index,XeEstate type);

/*--- XeTextureGetReal() ---*/
/*! Pobiera wartosc zmiennej stanu tekstury bezposrednio z GPU.
\param index Element tekstury.
\param type Zmienna stanu. Dostepne wartosci:<br>
XE_TEXTURE_WIDTH: Szerokosc tekstury.<br>
XE_TEXTURE_HEIGHT: Wysokosc tekstury.<br>
\return Wartoœæ zmiennej stanu.
*/
XE_IMPEX int XE_CALLTYPE XeTextureGetReal(XeElmTexture index,XeEstate type);

/*--- XeTextureType() ---*/
/*! Pobiera typ tekstury.
\param index Element tekstury.
\return Typ tekstury. Dostepne wartosci:<br>
XE_2D: Tekstura 2D.<br>
XE_DATA: Tekstura float.
*/
XE_IMPEX XeEstate XE_CALLTYPE XeTextureType(XeElmTexture index);

/*--- XeDisplaylistCreate() ---*/
/*! Tworzy liste wyswietlania.
Czyli liste polecen graficznych rysujacych scene. Polecenia sa kompilowane i zapamietywane, a podczas wywolywania listy polecenia sa przetwarzane szybko.
\param elm Wskaznik na element listy wyswietlania. Zwraca do niego utworzony element jesli operacja powiodla sie.
\param count Liczba sublist. Domyslnie rowna 1.
*/
XE_IMPEX void XE_CALLTYPE XeDisplaylistCreate(XeElmDisplayList* elm,unsigned int count=1);

/*--- XeDisplaylistDestroy() ---*/
/*! Niszczy liste wyswietlania.
\param index Element listy wyswietlania.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeDisplaylistDestroy(XeElmDisplayList index);

/*--- XeDisplaylistBegin() ---*/
/*! Rozpoczyna zapamietywanie polecen rysowania.
\param index Element listy wyswietlania.
\param id Indeks sublisty.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeDisplaylistBegin(XeElmDisplayList index,unsigned int id=0);

/*--- XeDisplaylistEnd() ---*/
/*! Konczy zapamietywanie polecen rysowania. */
XE_IMPEX void XE_CALLTYPE XeDisplaylistEnd();

/*--- XeDisplaylistCall() ---*/
/*! Wywoluje zapamietane polecenia z listy wyswietlania.
\param index Element listy wyswietlania.
\param id Indeks sublisty.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeDisplaylistCall(XeElmDisplayList index,unsigned int id=0);

/*--- XeRenderQueueActivate() ---*/
/*! Aktywuje kolejke renderowania (wlacza buforowanie danych grupujac je tak by wykonywaly mniejsza ilosc polecen rysowania). */
XE_IMPEX void XE_CALLTYPE XeRenderQueueActivate();

/*--- XeRenderQueueUnactivate() ---*/
/*! Dezaktywuje kolejke renderowania.*/
XE_IMPEX void XE_CALLTYPE XeRenderQueueUnactivate();

/*--- XeRenderQueueFlush() ---*/
/*! Nakazuje wyrenderowac buforowane dane.
\param leavebuffers Ustala czy ma zachowac dane w buforach po ich wyrenderowaniu.
*/
XE_IMPEX void XE_CALLTYPE XeRenderQueueFlush(bool leavebuffers=false);

/*--- XeRenderQueueClear() ---*/
/*! Czysci kolejke renderowania (zalecane po uzyciu XeRenderQueueFlush()). */
XE_IMPEX void XE_CALLTYPE XeRenderQueueClear();

/*--- XeRenderQueueTransformVertices() ---*/
/*! Wlacza/wylacza transformacje wierzcholkow.
\param mode Tryb. true: wlaczony; false: wylaczony.
*/
XE_IMPEX void XE_CALLTYPE XeRenderQueueTransformVertices(bool mode);

/*--- XeRenderQueueTransformCoords() ---*/
/*! Wlacza/wylacza transformacje koordynatow.
\param mode Tryb. true: wlaczony; false: wylaczony.
*/
XE_IMPEX void XE_CALLTYPE XeRenderQueueTransformCoords(bool mode);

/*--- XeRenderQueueReallocCount() ---*/
/*! Ustala liczbe elementow o jaka zwieksza sie pojemnosc maksymalna bufora po jej przekroczeniu.
\param count Liczba elementow.
*/
XE_IMPEX void XE_CALLTYPE XeRenderQueueReallocCount(unsigned int count);

/*--- XeRenderQueueGetModelviewMat() ---*/
/*! Pobiera bierzaca macierz widoku. */
XE_IMPEX void XE_CALLTYPE XeRenderQueueGetModelviewMat();

/*--- XeRenderQueueGetTextureMat() ---*/
/*! Pobiera bierzaca macierz tekstur. */
XE_IMPEX void XE_CALLTYPE XeRenderQueueGetTextureMat();

/*--- XeMatrixMode() ---*/
/*! Ustala aktywny tryb macierzy.
\param mode Tryb macierzy. Dostepne wartosci:<br>
XE_MATRIX_PROJECTION: Macierz projekcji.<br>
XE_MATRIX_MODELVIEW: Macierz widoku (domyslna).<br>
XE_MATRIX_TEXTURE: Macierz tekstury.
*/
XE_IMPEX void XE_CALLTYPE XeMatrixMode(XeEstate mode);

/*--- XeMatrixIdentity() ---*/
/*! Laduje macierz jednostkowa do aktywnej macierzy (zerujemy transformacje). */
XE_IMPEX void XE_CALLTYPE XeMatrixIdentity();

/*--- XeMatrixPush() ---*/
/*! Odklada bierzaca macierz na stos. */
XE_IMPEX void XE_CALLTYPE XeMatrixPush();

/*--- XeMatrixPop() ---*/
/*! Pobiera macierz ze stosu i oznaczamy jako bierzaca. */
XE_IMPEX void XE_CALLTYPE XeMatrixPop();

/*--- XeMatrixRotate() ---*/
/*! Obraca uklad wspolrzednych.
\param angle kat obrotu.
\param x Ilosc pelnych obrotow angle dla osi X.
\param y Ilosc pelnych obrotow angle dla osi Y.
\param z Ilosc pelnych obrotow angle dla osi Z.
*/
XE_IMPEX void XE_CALLTYPE XeMatrixRotate(double angle,double x,double y,double z);

/*--- XeMatrixScale() ---*/
/*! Skaluje uklad wspolrzednych.
\param x Skala osi X.
\param y Skala osi Y.
\param z Skala osi Z.
*/
XE_IMPEX void XE_CALLTYPE XeMatrixScale(double x,double y,double z);

/*--- XeMatrixTranslate() ---*/
/*! Przesuwamy uklad wspolrzednych.
\param x Wartosc przesuniecia osi X.
\param y Wartosc przesuniecia osi Y.
\param z Wartosc przesuniecia osi Z.
*/
XE_IMPEX void XE_CALLTYPE XeMatrixTranslate(double x,double y,double z);

/*--- XeMatrixLoad() ---*/
/*! Laduje macierz.
\param mat Wskaznik na macierz.
*/
XE_IMPEX void XE_CALLTYPE XeMatrixLoad(double* mat);

/*--- XeMatrixLoadHalf() ---*/
/*! Laduje macierz float.
\param mat Wskaznik na macierz float.
*/
XE_IMPEX void XE_CALLTYPE XeMatrixLoadHalf(float* mat);

/*--- XeMatrixSave() ---*/
/*! Zapisuje macierz do tablicy.
\param type Typ macierzy.
\param mat Wskaznik na macierz.
*/
XE_IMPEX void XE_CALLTYPE XeMatrixSave(XeEstate type,double* mat);

/*--- XeMatrixSaveHalf() ---*/
/*! Zapisuje macierz float do tablicy.
\param type Typ macierzy.
\param mat Wskaznik na macierz float.
*/
XE_IMPEX void XE_CALLTYPE XeMatrixSaveHalf(XeEstate type,float* mat);

/*--- XeDrawData() ---*/
/*! Rysuje prymitywy pobierajac ich dane z wielu buforow. Upakowanie danych: coord4;color4;normal3;vertex4;attrib?.
\param mode Typ prymitywow. Dostepne wartosci:<br>
XE_POINTS: Punkty.<br>
XE_LINES: Linie.<br>
XE_LINELOOP: Petla linii.<br>
XE_LINESTRIP: Tasma linii.<br>
XE_TRIANGLES: Trojkaty.<br>
XE_TRIANGLESTRIP: Tasma trojkatow.<br>
XE_TRIANGLEFAN: Wachlaz trojkatow.<br>
XE_QUADS: Czworokaty.<br>
XE_QUADSTRIP: Tasma czworokatow.<br>
XE_POLYGON: Wielokat.
\param first Indeks pierwszego elementu.
\param count Liczba elementow do narysowania.
\param vertex Wskaznik na bufor wierzcholkow (4).
\param color Wskaznik na bufor koloru (4).
\param coord Wskaznik na bufor koordynatow tekstury (4).
\param normal Wskaznik na bufor normalnych (3).
\param indices Wskaznik na bufor z indeksami wierzcholkow.
\param attribs Wskaznik na bufor atrybutow.
\param valtype Typ danych (XE_SINGLE: float; XE_DOUBLE: double).
\param vertoff Przesuniecie danych wierzcholkow.
\param coloff Przesuniecie danych koloru.
\param crdoff Przesuniecie danych koordynatow.
\param normoff Przesuniecie danych normalnych.
\param attoff Przesuniecie danych atrybutow.
\param attloc Indeks zmiennej atrybutow shadera.
\param attcom Liczba komponentow (1-4).
\param attnorm Ustala czy atrybuty maja byc znormalizowane (przyciete do wartosci: <-1;1>).
\param vertexasoffset Ustala czy wskaznik wierzcholkow ma byc uznawany za przesuniecie danych.
\param colorasoffset Ustala czy wskaznik kolorow ma byc uznawany za przesuniecie danych.
\param coordasoffset Ustala czy wskaznik koordynatow ma byc uznawany za przesuniecie danych.
\param normalasoffset Ustala czy wskaznik normalnych ma byc uznawany za przesuniecie danych.
\param indicesasoffset Ustala czy wskaznik indeksow ma byc uznawany za przesuniecie danych.
*/
XE_IMPEX void XE_CALLTYPE XeDrawData(XeEstate mode,int first,int count,void* vertex,void* color,void* coord,void* normal,unsigned int* indices=0,void* attribs=0,XeEstate valtype=XE_SINGLE,int vertoff=0,int coloff=0,int crdoff=0,int normoff=0,int attoff=0,int attloc=0,int attcom=4,bool attnorm=false,bool vertexasoffset=false,bool colorasoffset=false,bool coordasoffset=false,bool normalasoffset=false,bool indicesasoffset=false);

/*--- XeDrawDataStruct() ---*/
/*! Rysuje prymitywy pobierajac ich dane z jednego bufora. Upakowanie danych: coord4;color4;normal3;vertex4;attrib?.
\param mode Typ prymitywow. Dostepne wartosci:<br>
XE_POINTS: Punkty.<br>
XE_LINES: Linie.<br>
XE_LINELOOP: Petla linii.<br>
XE_LINESTRIP: Tasma linii.<br>
XE_TRIANGLES: Trojkaty.<br>
XE_TRIANGLESTRIP: Tasma trojkatow.<br>
XE_TRIANGLEFAN: Wachlaz trojkatow.<br>
XE_QUADS: Czworokaty.<br>
XE_QUADSTRIP: Tasma czworokatow.<br>
XE_POLYGON: Wielokat.
\param first Indeks pierwszego elementu.
\param count Liczba elementow do narysowania.
\param data Wskaznik na bufor danych wierzcholkow.
\param indices Wskaznik na bufor z indeksami wierzcholkow.
\param attribs Wskaznik na bufor atrybutow.
\param off Przesuniecie danych wierzcholkow.
\param attoff Przesuniecie danych atrybutow.
\param attloc Indeks zmiennej atrybutow shadera.
\param attcom Liczba komponentow (1-4).
\param attnorm Ustala czy atrybuty maja byc znormalizowane (przyciete do wartosci: <-1;1>).
*/
XE_IMPEX void XE_CALLTYPE XeDrawDataStruct(XeEstate mode,int first,int count,XePerVertex* data,unsigned int* indices=0,void* attribs=0,int off=0,int attoff=0,int attloc=0,int attcom=0,bool attnorm=false);

/*--- XeDrawDataCustom() ---*/
/*! Rysuje prymitywy przy uzyciu aktywnych vertex, index bufferow oraz shaderow.
\param mode Typ prymitywow. Dostepne wartosci:<br>
XE_POINTS: Punkty.<br>
XE_LINES: Linie.<br>
XE_LINELOOP: Petla linii.<br>
XE_LINESTRIP: Tasma linii.<br>
XE_TRIANGLES: Trojkaty.<br>
XE_TRIANGLESTRIP: Tasma trojkatow.<br>
XE_TRIANGLEFAN: Wachlaz trojkatow.<br>
XE_QUADS: Czworokaty.<br>
XE_QUADSTRIP: Tasma czworokatow.<br>
XE_POLYGON: Wielokat.
\param offset Przesuniecie w bajtach od poczatku bloku danych indeksow.
\param count Liczba elementow do narysowania.
\param structure Wskaznik na niestandardowa strukture upakowania danych VBO. Dostepne wartosci:<br>
XE_CUSTOM_VERTEX: Pole wierzcholka (4 kanaly).<br>
XE_CUSTOM_COLOR: Pole koloru (4 kanaly).<br>
XE_CUSTOM_COORD: Pole kordynatu tekstury (4 kanaly).<br>
XE_CUSTOM_NORMAL: Pole normalnej (3 kanaly).<br>
XE_CUSTOM_ATTRIBUTE: Pole wierzcholkow (kolejne: lokacja w shaderze; ilosc kanalow; czy znormalizowane).<br>
XE_NULL: Koniec definicji struktury (koniecznie zawsze na koncu struktury!).<br>
Przyklad:<br>
int structure[] = {XE_CUSTOM_VERTEX,XE_CUSTOM_COLOR,XE_CUSTOM_COORD,XE_CUSTOM_NORMAL,XE_CUSTOM_ATTRIBUTE,attribLocation,4,XE_FALSE,XE_NULL};
\param valtype Typ danych (XE_SINGLE: float; XE_DOUBLE: double).
*/
XE_IMPEX void XE_CALLTYPE XeDrawDataCustom(XeEstate mode,unsigned int bytesoffset,int count,int* structure,XeEstate valtype=XE_SINGLE);

} // Photon
} // XeCore

#endif // XE_COMPILE_PHOTON

#endif // _XE_PHOTON_EXPORTS_H_

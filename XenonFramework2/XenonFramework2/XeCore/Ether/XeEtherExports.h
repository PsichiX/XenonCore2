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

#ifndef _XE_ETHER_EXPORTS_H_
#define _XE_ETHER_EXPORTS_H_

#include "../XenonCore2.h"
#ifdef XE_COMPILE_ETHER
#include "../XeEther.h"
#include "XeNetworkAdapterInfoStruct.h"
#include "../Base/XeFile.h"

//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{
//! \namespace XeCore::Ether Przestrzen nazw modulu Ether
namespace Ether
{

/*--- XeSocketInitiation() ---*/
/*! Inicjuje tryb sieciowy.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeSocketInitiation();

/*--- XeSocketClosure() ---*/
/*! Zamyka tryb sieciowy. */
XE_IMPEX void XE_CALLTYPE XeSocketClosure();

/*--- XeSocketCreate() ---*/
/*! Tworzy gniazdo sieciowe.
\param elm Wskaznik na element gniazda.
*/
XE_IMPEX void XE_CALLTYPE XeSocketCreate(XeElmSocket* elm);

/*--- XeSocketOpen() ---*/
/*! Otwiera gniazdo sieciowe.
\param index Element gniazda.
\param udpmode Ustala czy gniazdo ma pracowac w trybie UDP.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeSocketOpen(XeElmSocket index,bool udpmode=false);

/*--- XeSocketClose() ---*/
/*! Zamyka gniazdo sieciowe.
\param index Element gniazda.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeSocketClose(XeElmSocket index);

/*--- XeSocketShutdown() ---*/
/*! Wylacza wysylanie/odbieranie na danym gniezdzie sieciowym. Operacja bezpowrotna!
\param index Element gniazda.
\param sending Ustala czy ma byc wylaczona mozliwosc wysylania danych.
\param receiving Ustala czy ma byc wylaczona mozliwosc odbierania danych danych.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeSocketShutdown(XeElmSocket index,bool sending,bool receiving);

/*--- XeSocketConnect() ---*/
/*! Laczy sie z hostem.
\param index Element gniazda.
\param address Adres hosta.
\param port Numer portu.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeSocketConnect(XeElmSocket index,char* address,XeWord port);

/*--- XeSocketListen() ---*/
/*! Wlacza nasluchiwanie na danym porcie.
\param index Element gniazda.
\param port Numer portu.
\param maxconn Maksymalna ilosc aktywnych polaczen.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeSocketListen(XeElmSocket index,XeWord port,int maxconn);

/*--- XeSocketAccept() ---*/
/*! Akceptuje nadchodzace polaczenie i przypisuje sobie jego gniazdo.
\param index Element gniazda.
\param listen Element gniazda nasluchujacego.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeSocketAccept(XeElmSocket index,XeElmSocket listen);

/*--- XeSocketSend() ---*/
/*! Wysyla dane do danego gniazda.
\param index Element gniazda.
\param buffer Wskaznik na bufor (plik) danych.
\param sizeheader Ustala czy ma wyslac pakiet z naglowkiem zawierajacym rozmiar pakietu.
\param offset Pozycja od ktorej zaczyna wysylac dane bufora.
\param size Rozmiar wysylanych danych (0 jesli ma wyslac caly bufor).
\return Rozmiar wyslanych danych jesli operacja powiodla sie, lub 0 jesli nie.
*/
XE_IMPEX unsigned int XE_CALLTYPE XeSocketSend(XeElmSocket index,XeFile* buffer,bool sizeheader=true,unsigned int offset=0,unsigned int size=0);

/*--- XeSocketReceive() ---*/
/*! Odbiera dane z danego gniazda.
\param index Element gniazda. Jesli jest pusty, to czysci bufor do ktorego wczesniej zostaly odebrane dane z gniazda.
\param buffer Wskaznik na bufor (plik) danych.
\param size Odbiera dane o podanym rozmiarze jesli wiekszy niz 0, inaczej wykorzystuje rozmiar w naglowku pakietu.
\param peekmsg Ustala czy dane po pobraniu maja byc pozostawione w kolejce wiadomosci gniazda.
\return Rozmiar odebranych danych jesli operacja powiodla sie, lub 0 jesli nie.
*/
XE_IMPEX unsigned int XE_CALLTYPE XeSocketReceive(XeElmSocket index,XeFile* buffer,unsigned int size=0,bool peekmsg=false);

/*--- XeSocketAsync() ---*/
/*! Asynchroniczny (nieblokowany) tryb gniazda (domyslnie wylaczony).
\param index Element gniazda.
\param mode Ustala tryb synchronizacji.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeSocketAsync(XeElmSocket index,bool mode);

/*--- XeSocketNagle() ---*/
/*! Aktywacja/dezaktywacja algorytmu Nagle (ogranicza liczbe malych pakietow wysylanych przez hosta, przez buforowanie danych, do momentu, az osiagna one naturalny rozmiar i pakiet zostanie wyslany; domyslnie wlaczony).
\param index Element gniazda.
\param mode Ustala tryb algorytmu Nagle.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeSocketNagle(XeElmSocket index,bool mode);

/*--- XeSocketIsOpened() ---*/
/*! Sprawdza czy gniazdo jest otwarte.
\param index Element gniazda.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeSocketIsOpened(XeElmSocket index);

/*--- XeSocketIsConnected() ---*/
/*! Sprawdza czy gniazdo jest polaczone.
\param index Element gniazda.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeSocketIsConnected(XeElmSocket index);

/*--- XeSocketIsUDP() ---*/
/*! Sprawdza czy gniazdo pracuje w trybie UDP.
\param index Element gniazda.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeSocketIsUDP(XeElmSocket index);

/*--- XeSocketSetUDPsendIpPort() ---*/
/*! Ustala maksymalny rozmiar wysylanych/odbieranych danych w trybie UDP.
\param index Element gniazda.
\param ip Adres IP.
\param port Numer portu.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeSocketSetUDPsendIpPort(XeElmSocket index,char* ip,XeWord port);

/*--- XeSocketSetUDPbuffSize() ---*/
/*! Ustala maksymalny rozmiar wysylanych/odbieranych danych w trybie UDP.
\param index Element gniazda.
\param size Rozmiar (w bajtach).
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeSocketSetUDPbuffSize(XeElmSocket index,unsigned int size);

/*--- XeSocketGetUDPbuffSize() ---*/
/*! Zwraca maksymalny rozmiar danych wysylanych/odbieranych w trybie UDP.
\param index Element gniazda.
\return Rozmiar danych (w bajtach).
*/
XE_IMPEX unsigned int XE_CALLTYPE XeSocketGetUDPbuffSize(XeElmSocket index);

/*--- XeSocketGetIp() ---*/
/*! Zwraca IP gniazda.
\param index Element gniazda.
\return IP gniazda jesli operacja powiodla sie, lub 0 jesli nie.
*/
XE_IMPEX char* XE_CALLTYPE XeSocketGetIp(XeElmSocket index);

/*--- XeSocketGetPort() ---*/
/*! Zwraca port gniazda.
\param index Element gniazda.
\return Port gniazda jesli operacja powiodla sie, lub 0 jesli nie.
*/
XE_IMPEX XeWord XE_CALLTYPE XeSocketGetPort(XeElmSocket index);

/*--- XeSocketGetUDPsendIp() ---*/
/*! Zwraca IP wysylanych wiadomosci w trybie UDP.
\param index Element gniazda.
\return IP odbiorcy jesli operacja powiodla sie, lub 0 jesli nie.
*/
XE_IMPEX char* XE_CALLTYPE XeSocketGetUDPsendIp(XeElmSocket index);

/*--- XeSocketGetUDPsendPort() ---*/
/*! Zwraca port odebranej wiadomosci w trybie UDP.
\param index Element gniazda.
\return Port odbiorcy jesli operacja powiodla sie, lub 0 jesli nie.
*/
XE_IMPEX XeWord XE_CALLTYPE XeSocketGetUDPsendPort(XeElmSocket index);

/*--- XeSocketGetUDPreceiveIp() ---*/
/*! Zwraca IP odebranej wiadomosci w trybie UDP.
\param index Element gniazda.
\return IP adresata jesli operacja powiodla sie, lub 0 jesli nie.
*/
XE_IMPEX char* XE_CALLTYPE XeSocketGetUDPreceiveIp(XeElmSocket index);

/*--- XeSocketGetUDPreceivePort() ---*/
/*! Zwraca port odebranej wiadomosci w trybie UDP.
\param index Element gniazda.
\return Port adresata jesli operacja powiodla sie, lub 0 jesli nie.
*/
XE_IMPEX XeWord XE_CALLTYPE XeSocketGetUDPreceivePort(XeElmSocket index);

/*--- XeSocketDestroy() ---*/
/*! Niszczy gniazdo sieciowe.
\param index Element gniazda.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeSocketDestroy(XeElmSocket index);

/*--- XeNetworkIsConnected() ---*/
/*! Sprawdza czy polaczenie z internetem jest aktywne.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeNetworkIsConnected();

/*--- XeNetworkHostName() ---*/
/*! Pobiera nazwe lokalnego hosta.
\return na wynikowy string z nazwa.
*/
XE_IMPEX char* XE_CALLTYPE XeNetworkHostName();

/*--- XeNetworkAdapterInfo() ---*/
/*! Pobiera informacje o urzadzeniu sieciowym.
\param info Wskaznik na docelowa strukture informacji o urzadzeniu sieciowym.
\return true jesli operacja powiodla sie.
*/
XE_IMPEX bool XE_CALLTYPE XeNetworkAdapterInfo(XeNetworkAdapterInfoStruct* info);

/*--- XeNetworkIpToString() ---*/
/*! Konwertuje adres IP do stringa.
\param ip Adres IP.
\return Wskaznik na wynikowy string adresu.
*/
XE_IMPEX char* XE_CALLTYPE XeNetworkIpToString(XeDword ip);

/*--- XeNetworkStringToIp() ---*/
/*! Konwertuje string do adresu IP.
\param ip String z adresem IP.
\return Adres IP.
*/
XE_IMPEX XeDword XE_CALLTYPE XeNetworkStringToIp(char* ip);

/*--- XeNetworkAddressToIp() ---*/
/*! Konwertuje string z adresem hosta do adresu IP.
\param address String z adresem hosta.
\return Adres IP.
*/
XE_IMPEX XeDword XE_CALLTYPE XeNetworkAddressToIp(char* address);

} // Ether
} // XeCore

#endif // XE_COMPILE_ETHER

#endif // _XE_ETHER_EXPORTS_H_

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

#ifndef _XENON_CORE_SOCKET_H_
#define _XENON_CORE_SOCKET_H_

#include "../XenonCore2.h"
#ifdef XE_COMPILE_ETHER
#include "../XeEther.h"
#include "../Base/XeFile.h"

//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{
//! \namespace XeCore::Ether Przestrzen nazw modulu Ether
namespace Ether
{

/*--- XenoN Core Socket ---*/
class XenonCoreSocket
{
#ifdef XE_COMPILE_EXPORT
public:
#else
private:
#endif /* XE_COMPILE_EXPORT */
SOCKET Socket;
bool UDPmode;
unsigned int UDPmaxsize;
XeByte Type;
sockaddr_in Addr;
sockaddr_in AddrSend;
sockaddr_in AddrRecv;
int AddrRecvLen;
bool NagleMode;
bool AsyncMode;
#ifdef XE_COMPILE_EXPORT
XenonCoreSocket();
bool Open(bool udpmode);
void Close();
void Shutdown(bool sending,bool receiving);
bool Connect(char* server,XeWord port);
bool Listen(XeWord port,int maxconn);
bool Accept(XenonCoreSocket* listen);
unsigned int Send(XeFile* buffer,bool sizeheader,unsigned int offset,unsigned int bsize);
unsigned int Receive(XeFile* buffer,unsigned int size,bool peek);
bool Async(bool mode);
bool Nagle(bool mode);
bool IsOpened();
bool IsConnected();
bool UDPsendIpPort(char* ip,XeWord port);
char* GetIP();
XeWord GetPort();
char* GetUDPsendIP();
XeWord GetUDPsendPort();
char* GetUDPreceiveIP();
XeWord GetUDPreceivePort();
static char* IpToString(XeDword ip);
static XeDword StringToIp(char* ip);
static XeDword AddressToIp(char* address);
#endif /* XE_COMPILE_EXPORT */
};

} // Ether
} // XeCore

#endif // XE_COMPILE_ETHER

#endif // _XENON_CORE_SOCKET_H_

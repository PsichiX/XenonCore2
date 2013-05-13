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

#ifndef _XE_NETWORK_ADAPTER_INFO_STRUCT_H_
#define _XE_NETWORK_ADAPTER_INFO_STRUCT_H_

#include "../XenonCore2.h"
#ifdef XE_COMPILE_ETHER

//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{
//! \namespace XeCore::Ether Przestrzen nazw modulu Ether
namespace Ether
{

/*--- XeNetworkAdapterInfoStruct ---*/
struct XeNetworkAdapterInfoStruct
{
char Name[260];
char Desc[132];
char Type[16];
char Ip[16];
char Mask[16];
char Mac[18];
};

} // Ether
} // XeCore

#endif // XE_COMPILE_ETHER

#endif _XE_NETWORK_ADAPTER_INFO_STRUCT_H_
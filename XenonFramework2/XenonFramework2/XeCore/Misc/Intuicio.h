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

#ifndef _INTUICIO_H_
#define _INTUICIO_H_

#include "../XenonCore2.h"
#ifdef XE_COMPILE_CORE_INTUICIO
#include "../Base/XeArray.h"

//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{

/*--- XenoN Core Intuicio ---*/
typedef void(*XeIntuicioInterface)(XeBuffer* Arguments);
typedef XeBuffer XeIntuicioProgram;
#define XE_INTUICIO_EXTERNAL(name) void name (XeBuffer* Arguments)
#define XE_INTUICIO_KEYWORD(name) XeDword name=0; Arguments->ReadBytes(&name,4);
#define XE_INTUICIO_POINTER(type,name) type* name=0; Arguments->ReadBytes(&name,4);
#define XE_INTUICIO_CONSTANT(type,name) type name; Arguments->ReadBytes(&name,sizeof(type));
#define XE_INTUICIO_RESTART Arguments->Seek(0);

} // XeCore

#endif // XE_COMPILE_CORE_INTUICIO

#endif // _INTUICIO_H_

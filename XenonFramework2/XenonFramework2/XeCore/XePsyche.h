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

#ifndef _XE_PSYCHE_H_
#define _XE_PSYCHE_H_

#include "Base/XeElements.h"
#ifdef XE_COMPILE_PSYCHE

//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{
//! \namespace XeCore::Psyche Przestrzen nazw modulu Psyche
namespace Psyche
{

/*! Definicja elementu: Psyche. */
class XenonCorePsyche;
typedef XeElementPointer<XenonCorePsyche> XeElmPsyche;

} // Psyche
} // XeCore

#endif // XE_COMPILE_PSYCHE

#endif // _XE_PSYCHE_H_

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

#ifndef _XENON_CORE_SUBSTANCE_H_
#define _XENON_CORE_SUBSTANCE_H_

#include "../XenonCore2.h"
#ifdef XE_COMPILE_CHAOS
#include "../XeChaos.h"
#include "../Base/XeVectorTemplate.h"

//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{
//! \namespace XeCore::Chaos Przestrzen nazw modulu Chaos
namespace Chaos
{

/*--- XenoN Core Substance ---*/
class XenonCoreSubstance
{
#ifdef XE_COMPILE_EXPORT
public:
#else
private:
#endif /* XE_COMPILE_EXPORT */
double object;
XeVector position;
double range;
double mass;
double energy;
unsigned int solid; // XE_FLAG_SUBSTANCE_SOLID_RANGE; XE_FLAG_SUBSTANCE_SOLID_SURFACE;
XeVector inertion;
XeVector prev;
XeVector temp;
double density;
#ifdef XE_COMPILE_EXPORT
XenonCoreSubstance();
#endif /* XE_COMPILE_EXPORT */
};

} // Chaos
} // XeCore

#endif // XE_COMPILE_CHAOS

#endif // _XENON_CORE_SUBSTANCE_H_

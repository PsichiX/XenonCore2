/*
	Name:			XenoN Core 2
	Version:		2.0.0.0 Frozen Eye
	Update:			2011-06-04
	Copyright:		Copyright � 2007-2011 XenoN Core by PsichiX. All rights reserved.
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

#ifndef _XENON_CORE_DNA_H_
#define _XENON_CORE_DNA_H_

#include "../XenonCore2.h"
#if defined(XE_COMPILE_CORE_DNA) && defined(XE_COMPILE_PSYCHE) && defined(XE_COMPILE_CHAOS) && defined(XE_COMPILE_PHOTON)
#include "../XeMisc.h"
#include "../XePsyche.h"
#include "../XeChaos.h"
#include "../XePhoton.h"
#include "../Base/XeArray.h"

//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{
//! \namespace XeCore::Misc Przestrzen nazw modulu roznosci
namespace Misc
{

/*--- XenoN Core DNA ---*/
class XenonCoreDna
{
#ifdef XE_COMPILE_EXPORT
public:
#else
private:
#endif /* XE_COMPILE_EXPORT */
Psyche::XeElmPsyche Brain;
XeArray<Chaos::XeElmSubstance> Cells;
XeArray<Chaos::XeElmCovalenceForce> Muscles;
XeArray<Chaos::XeElmSurface> Skin;
Photon::XeElmTexture BodyTexture;
#ifdef XE_COMPILE_EXPORT
XenonCoreDna();
void Die(bool destroybody=true);
void Birth(unsigned int cells,unsigned int muscles,unsigned int skin);
bool Link(XeEstate type,unsigned int id,void* element);
bool Unlink(XeEstate type,unsigned int id);
void* Get(XeEstate type,unsigned int id);
unsigned int Count(XeEstate type);
#endif /* XE_COMPILE_EXPORT */
};

} // Misc
} // XeCore

#endif // defined(XE_COMPILE_CORE_DNA) && defined(XE_COMPILE_PSYCHE) && defined(XE_COMPILE_CHAOS) && defined(XE_COMPILE_PHOTON)

#endif // _XENON_CORE_DNA_H_

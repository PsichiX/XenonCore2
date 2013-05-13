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

#ifndef _XENON_CORE_PARTICLE_H_
#define _XENON_CORE_PARTICLE_H_

#include "../XenonCore2.h"
#if defined(XE_COMPILE_CHAOS) && defined(XE_COMPILE_PHOTON)
#include "../XeChaos.h"
#include "../XePhoton.h"

//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{
//! \namespace XeCore::Chaos Przestrzen nazw modulu Chaos
namespace Chaos
{

/*--- XenoN Core Particle ---*/
class XenonCoreParticle
{
#ifdef XE_COMPILE_EXPORT
public:
#else
private:
#endif /* XE_COMPILE_EXPORT */
double size;
Photon::XeElmTexture texture_id;
XeEstate texture_type;
XeElmSubstance subst;
#ifdef XE_COMPILE_EXPORT
XenonCoreParticle();
#endif /* XE_COMPILE_EXPORT */
};

} // Chaos
} // XeCore

#endif // defined(XE_COMPILE_CHAOS) && defined(XE_COMPILE_PHOTON)

#endif // _XENON_CORE_PARTICLE_H_

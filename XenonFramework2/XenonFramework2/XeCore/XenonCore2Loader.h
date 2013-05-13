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

#ifndef _XENON_CORE_2_LOADER_H_
#define _XENON_CORE_2_LOADER_H_

// core
#include "XenonCore2.h"
// modules
#ifdef XE_COMPILE_CHAOS
#include "XeChaos.h"
#endif // XE_COMPILE_CHAOS
#ifdef XE_COMPILE_ECHO
#include "XeEcho.h"
#endif // XE_COMPILE_ECHO
#ifdef XE_COMPILE_ETHER
#include "XeEther.h"
#endif // XE_COMPILE_ETHER
#include "XeMisc.h"
#ifdef XE_COMPILE_PHOTON
#include "XePhoton.h"
#endif // XE_COMPILE_PHOTON
#ifdef XE_COMPILE_PSYCHE
#include "XePsyche.h"
#endif // XE_COMPILE_PSYCHE
#ifdef XE_COMPILE_TIMEBRIDGE
#include "XeTimeBridge.h"
#endif // XE_COMPILE_TIMEBRIDGE
// exports
#ifdef XE_COMPILE_CHAOS
#include "Chaos/XeChaosExports.h"
#endif // XE_COMPILE_CHAOS
#ifdef XE_COMPILE_ETHER
#include "Ether/XeEtherExports.h"
#endif // XE_COMPILE_ETHER
#include "Misc/XeMiscExports.h"
#ifdef XE_COMPILE_PHOTON
#include "Photon/XePhotonExports.h"
#endif // XE_COMPILE_PHOTON
#ifdef XE_COMPILE_PSYCHE
#include "Psyche/XePsycheExports.h"
#endif // XE_COMPILE_PSYCHE
// objects
#ifdef XE_COMPILE_CHAOS
#include "Chaos/XenonCoreBlackHole.h"
#include "Chaos/XenonCoreCovalenceForce.h"
#include "Chaos/XenonCoreForce.h"
#include "Chaos/XenonCoreGlobalForce.h"
#include "Chaos/XenonCoreParticle.h"
#include "Chaos/XenonCoreRay.h"
#include "Chaos/XenonCoreSubstance.h"
#include "Chaos/XenonCoreSurface.h"
#include "Chaos/XenonCoreWaveForce.h"
#endif // XE_COMPILE_CHAOS
#ifdef XE_COMPILE_ETHER
#include "Ether/XeNetworkAdapterInfoStruct.h"
#include "Ether/XenonCoreSocket.h"
#endif // XE_COMPILE_ETHER
#include "Misc/Helper.h"
#ifdef XE_COMPILE_CORE_INTUICIO
#include "Misc/Intuicio.h"
#endif // XE_COMPILE_CORE_INTUICIO
#ifdef XE_COMPILE_CORE_DNA
#include "Misc/XenonCoreDna.h"
#endif // XE_COMPILE_CORE_DNA
#ifdef XE_COMPILE_CORE_VIRTUAL_FILE
#include "Misc/XVF.h"
#endif // XE_COMPILE_CORE_VIRTUAL_FILE
#ifdef XE_COMPILE_PHOTON
#include "Photon/XenonCoreDisplayList.h"
#include "Photon/XenonCoreFrameBuffer.h"
#include "Photon/XenonCoreRenderTarget.h"
#include "Photon/XenonCoreShader.h"
#include "Photon/XenonCoreTexture.h"
#include "Photon/XenonCoreVertexBuffer.h"
#endif // XE_COMPILE_PHOTON
#ifdef XE_COMPILE_PSYCHE
#include "Psyche/XenonCorePsyche.h"
#endif // XE_COMPILE_PSYCHE

#endif // _XENON_CORE_2_LOADER_H_

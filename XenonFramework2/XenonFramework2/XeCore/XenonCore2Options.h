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

#ifndef _XENON_CORE_2_OPTIONS_H_
#define _XENON_CORE_2_OPTIONS_H_

// Kompiluj z modulem Photon
#define XE_COMPILE_PHOTON
// Kompiluj z modulem Chaos
#define XE_COMPILE_CHAOS
// Kompiluj z modulem Psyche
#define XE_COMPILE_PSYCHE
// Kompiluj z zezwoleniem ewolucji umyslu dla modulu Psyche
#define XE_COMPILE_PSYCHE_ALLOW_TO_EVOLVE
// Kompiluj z modulem TimeBridge
#define XE_COMPILE_TIMEBRIDGE
// Kompiluj z modulem Ether
#define XE_COMPILE_ETHER
// Kompiluj z modulem Echo
#define XE_COMPILE_ECHO
// Kompiluj z modulem rdzenia Virtual File
#define XE_COMPILE_CORE_VIRTUAL_FILE
// Kompiluj z modulem rdzenia Intuicio
#define XE_COMPILE_CORE_INTUICIO
// Kompiluj z modulem rdzenia DNA
#define XE_COMPILE_CORE_DNA
// Kompiluj dla biblioteki statycznej.
//#define XE_COMPILE_STATIC
// Kompiluj bez zasobow
//#define XE_NOT_USE_RESOURCES

/* Wersja Intuicio */
#ifdef XE_COMPILE_CORE_INTUICIO
#define XE_INTUICIO_VERSION_MAJOR			0
#define XE_INTUICIO_VERSION_MINOR			2
#define XE_INTUICIO_VERSION_RELEASE			0
#define XE_INTUICIO_VERSION_BUILD			2
#define XE_INTUICIO_VERSION_STRING			"0.2.0.2"
#else
#define XE_INTUICIO_VERSION_MAJOR			0
#define XE_INTUICIO_VERSION_MINOR			0
#define XE_INTUICIO_VERSION_RELEASE			0
#define XE_INTUICIO_VERSION_BUILD			0
#define XE_INTUICIO_VERSION_STRING			"0.0.0.0"
#endif // XE_COMPILE_CORE_INTUICIO
#define XE_INTUICIO_VERSION					{XE_INTUICIO_VERSION_MAJOR,XE_INTUICIO_VERSION_MINOR,XE_INTUICIO_VERSION_RELEASE,XE_INTUICIO_VERSION_BUILD}

#endif // _XENON_CORE_2_OPTIONS_H_

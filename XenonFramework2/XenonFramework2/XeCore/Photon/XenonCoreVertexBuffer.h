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

#ifndef _XENON_CORE_VERTEXBUFFER_H_
#define _XENON_CORE_VERTEXBUFFER_H_

#include "../XenonCore2.h"
#ifdef XE_COMPILE_PHOTON
#include "../XePhoton.h"

//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{
//! \namespace XeCore::Photon Przestrzen nazw modulu Photon
namespace Photon
{

/*--- XenoN Core VertexBuffer ---*/
class XenonCoreVertexBuffer
{
#ifdef XE_COMPILE_EXPORT
public:
#else
private:
#endif /* XE_COMPILE_EXPORT */
int MaxSize;
int MaxSizeIndices;
unsigned int Vbuffer;
unsigned int Ibuffer;
#ifdef XE_COMPILE_EXPORT
XenonCoreVertexBuffer();
bool Create(int maxsize,void* data,XeEstate type,int maxsizeindices,void* dataindices,XeEstate typeindices);
void Destroy();
void Activate(XeEstate mode);
static bool SendData(XeEstate mode,int size,int offset,void* data);
static void* Map(XeEstate mode,XeEstate type);
static void Unmap(XeEstate mode);
bool HasBuffer(XeEstate mode);
int Size(XeEstate mode);
#endif /* XE_COMPILE_EXPORT */
};

} // Photon
} // XeCore

#endif // XE_COMPILE_PHOTON

#endif // _XENON_CORE_VERTEXBUFFER_H_

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

#ifndef _XENON_CORE_TEXTURE_H_
#define _XENON_CORE_TEXTURE_H_

#include "../XenonCore2.h"
#ifdef XE_COMPILE_PHOTON
#include "../XePhoton.h"

//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{
//! \namespace XeCore::Photon Przestrzen nazw modulu Photon
namespace Photon
{

/*--- XenoN Core Texture ---*/
class XenonCoreTexture
{
#ifdef XE_COMPILE_EXPORT
public:
#else
private:
#endif /* XE_COMPILE_EXPORT */
unsigned int texture;
unsigned int width;
unsigned int height;
void* pixels;
unsigned int psize;
unsigned int type;
bool depth;
#ifdef XE_COMPILE_EXPORT
XenonCoreTexture();
void Create();
bool LoadEmpty(int w,int h,bool achan);
bool LoadFromXET(char* fname,bool achan);
bool LoadFromXETmem(void* pbuff,bool achan);
bool LoadFromRGBA(char* fname,int _width,int _height);
bool LoadFromRGBAmem(void* pbuff,int _width,int _height);
bool LoadFromRender(int px,int py,int width,int height,bool asnew);
bool LoadEmptyData(int w,int h);
bool LoadData(void* data,int w,int h);
bool LoadEmptyDepth(int w,int h);
bool LoadDepth(void* data,int w,int h);
bool Update(void* data,int px,int py,int width,int height);
bool Activate();
void Unactivate();
void Destroy();
void* Lock(bool xetfile=false);
void Unlock(bool update=true);
bool IsLocked();
#endif /* XE_COMPILE_EXPORT */
};

} // Photon
} // XeCore

#endif // XE_COMPILE_PHOTON

#endif // _XENON_CORE_TEXTURE_H_

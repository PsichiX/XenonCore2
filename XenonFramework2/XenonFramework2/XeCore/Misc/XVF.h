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

#ifndef _XVF_H_
#define _XVF_H_

#include "../XenonCore2.h"
#ifdef XE_COMPILE_CORE_VIRTUAL_FILE

//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{

class XvfFile
{
#ifdef XE_COMPILE_EXPORT
public:
#else
private:
#endif /* XE_COMPILE_EXPORT */
char Name[256];
unsigned int Size;
void* Data;
#ifdef XE_COMPILE_EXPORT
XvfFile();
XvfFile(char* name,unsigned int size,void* data);
void Free();
bool Empty();
void Encrypt(char* pass);
void Decrypt(char* pass);
#endif /* XE_COMPILE_EXPORT */
};

struct XvfInfo
{
unsigned int FileOffset;
unsigned int FileSize;
char FileName[256];
};

struct XvfHeader
{
unsigned int Offset;
unsigned int Count;
};

} // XeCore

#endif // XE_COMPILE_CORE_VIRTUAL_FILE

#endif // _XVF_H_
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

#include "Helper.h"
#include "XeMiscExports.h"

//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{

/*--- XeLengthdirLen() ---*/
XeVector XE_CALLTYPE XeLengthdirLen(XeAngleVector a,double l)
{
XeAngleVector va;
va=a;
va.Length=l;
XeVector vr;
XeLengthdir(va,&vr);
return(vr);
}

/*--- XeDirectionir() ---*/
XeAngleVector XE_CALLTYPE XeDirectionDir(XeVector b,XeVector e)
{
XeAngleVector vr;
XeDirection(b,e,&vr);
return(vr);
}

} // XeCore

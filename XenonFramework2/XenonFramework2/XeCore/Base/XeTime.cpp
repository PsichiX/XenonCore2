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

#include "XeTime.h"


//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{

XeTime::XeTime()
{
UseQPC=(QueryPerformanceFrequency(&Freq)!=0);
}

XeTime& XeTime::Use()
{
static XeTime Instance;
return(Instance);
}

float XeTime::GetSecs()
{
if(!XeTime::Use().UseQPC)return((float)GetTickCount()/1000);
else
{
LARGE_INTEGER Ticks;
QueryPerformanceCounter(&Ticks);
return((float)(Ticks.QuadPart/(double)XeTime::Use().Freq.QuadPart));
}
}

double XeTime::GetSecsSens()
{
if(!XeTime::Use().UseQPC)return((double)GetTickCount()/1000);
else
{
LARGE_INTEGER Ticks;
QueryPerformanceCounter(&Ticks);
return((double)Ticks.QuadPart/(double)XeTime::Use().Freq.QuadPart);
}
}

LONGLONG XeTime::GetMilisecs()
{
if(!XeTime::Use().UseQPC)return((LONGLONG)GetTickCount());
else
{
LARGE_INTEGER Ticks;
QueryPerformanceCounter(&Ticks);
return((LONGLONG)((Ticks.QuadPart/(double)XeTime::Use().Freq.QuadPart)*1000));
}
}

} // XeCore

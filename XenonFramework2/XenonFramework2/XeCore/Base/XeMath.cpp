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

#include <stdlib.h>
#include "XeTime.h"
#include "XeMath.h"


//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{

double XeMath::DegToRad(double deg)
{
return(deg*PI/180);
}

float XeMath::DegToRad(float deg)
{
return(deg*(float)PI/180);
}

double XeMath::RadToDeg(double rad)
{
return(rad*180/PI);
}

float XeMath::RadToDeg(float rad)
{
return(rad*180/(float)PI);
}

double XeMath::Random(double range)
{
return((((double)(rand()%1000))/1000.0f)*range);
}

void XeMath::RandomReset()
{
srand((unsigned int)XeTime::GetSecsSens());
}

double XeMath::Amount(double v1,double v2,double amount)
{
return((v2-v1)*min(1,max(0,amount))+v1);
}

void XeMath::BitInclude(void* data,unsigned int bit)
{
unsigned int _field=bit/8;
unsigned int _bit=bit%8;
unsigned char* _buff=(unsigned char*)data;
_buff[_field]=_buff[_field] | ((unsigned char)1 << _bit);
}

void XeMath::BitExclude(void* data,unsigned int bit)
{
unsigned int _field=bit/8;
unsigned int _bit=bit%8;
unsigned char* _buff=(unsigned char*)data;
_buff[_field]=_buff[_field] & ~((unsigned char)1 << _bit);
}

bool XeMath::BitCheck(void* data,unsigned int bit)
{
unsigned int _field=bit/8;
unsigned int _bit=bit%8;
unsigned char* _buff=(unsigned char*)data;
if(_buff[_field] & ((unsigned char)1 << _bit))
return(true);
return(false);
}

} // XeCore

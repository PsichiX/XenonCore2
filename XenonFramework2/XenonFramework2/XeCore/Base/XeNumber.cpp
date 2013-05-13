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

#include "XeNumber.h"


//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{

XeNumber::XeNumber()
{
Value=0;
}

XeNumber::XeNumber(double val)
{
Value=val;
}

XeNumber::XeNumber(int val)
{
Value=(double)val;
}

double XeNumber::Get()
{
return(Value);
}

void XeNumber::Set(double val)
{
Value=val;
}

XeNumber XeNumber::operator+ (XeNumber& n)
{
return(Value+n.Value);
}

XeNumber XeNumber::operator- (XeNumber& n)
{
return(Value-n.Value);
}

XeNumber XeNumber::operator* (XeNumber& n)
{
return(Value*n.Value);
}

XeNumber XeNumber::operator/ (XeNumber& n)
{
return(Value/n.Value);
}

XeNumber& XeNumber::operator+= (XeNumber& n)
{
*this=*this+n;
return(*this);
}

XeNumber& XeNumber::operator-= (XeNumber& n)
{
*this=*this-n;
return(*this);
}

XeNumber& XeNumber::operator*= (XeNumber& n)
{
*this=*this*n;
return(*this);
}

XeNumber& XeNumber::operator/= (XeNumber& n)
{
*this=*this/n;
return(*this);
}

double& XeNumber::operator= (double& val)
{
Set(val);
return(Value);
}

float& XeNumber::operator= (float& val)
{
Set((double&)val);
return((float&)Value);
}

int& XeNumber::operator= (int& val)
{
Set((double&)val);
return((int&)Value);
}

unsigned int& XeNumber::operator= (unsigned int& val)
{
Set((double&)val);
return((unsigned int&)Value);
}

char& XeNumber::operator= (char& val)
{
Set((double&)val);
return((char&)Value);
}

unsigned char& XeNumber::operator= (unsigned char& val)
{
Set((double&)val);
return((unsigned char&)Value);
}

bool& XeNumber::operator= (bool& val)
{
Set((double&)val);
return((bool&)Value);
}

bool XeNumber::operator== (XeNumber& val)
{
return((Value==val.Value)?true:false);
}

bool XeNumber::operator== (double& val)
{
return((Value==val)?true:false);
}

bool XeNumber::operator== (float& val)
{
return((Value==(double)val)?true:false);
}

bool XeNumber::operator== (int& val)
{
return((Value==(double)val)?true:false);
}

bool XeNumber::operator== (unsigned int& val)
{
return((Value==(double)val)?true:false);
}

bool XeNumber::operator== (short& val)
{
return((Value==(double)val)?true:false);
}

bool XeNumber::operator== (unsigned short& val)
{
return((Value==(double)val)?true:false);
}

bool XeNumber::operator== (char& val)
{
return((Value==(double)val)?true:false);
}

bool XeNumber::operator== (unsigned char& val)
{
return((Value==(double)val)?true:false);
}

bool XeNumber::operator== (bool& val)
{
return((Value==(double)val)?true:false);
}

bool XeNumber::operator!= (XeNumber& val)
{
return((Value!=val.Value)?true:false);
}

bool XeNumber::operator!= (double& val)
{
return((Value!=val)?true:false);
}

bool XeNumber::operator!= (float& val)
{
return((Value!=(double)val)?true:false);
}

bool XeNumber::operator!= (int& val)
{
return((Value!=(double)val)?true:false);
}

bool XeNumber::operator!= (unsigned int& val)
{
return((Value!=(double)val)?true:false);
}

bool XeNumber::operator!= (short& val)
{
return((Value!=(double)val)?true:false);
}

bool XeNumber::operator!= (unsigned short& val)
{
return((Value!=(double)val)?true:false);
}

bool XeNumber::operator!= (char& val)
{
return((Value!=(double)val)?true:false);
}

bool XeNumber::operator!= (unsigned char& val)
{
return((Value!=(double)val)?true:false);
}

bool XeNumber::operator!= (bool& val)
{
return((Value!=(double)val)?true:false);
}

XeNumber::operator double() const
{
return(Value);
}

XeNumber::operator float() const
{
return((float)Value);
}

XeNumber::operator int() const
{
return((int)Value);
}

XeNumber::operator unsigned int() const
{
return((unsigned int)Value);
}

XeNumber::operator short() const
{
return((short)Value);
}

XeNumber::operator unsigned short() const
{
return((unsigned short)Value);
}

XeNumber::operator char() const
{
return((char)Value);
}

XeNumber::operator unsigned char() const
{
return((unsigned char)Value);
}

XeNumber::operator bool() const
{
return(Value?true:false);
}

} // XeCore

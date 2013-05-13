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

#include "XeMath.h"


//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{

template<typename T>
XeAngleVectorTemplate<T>::XeAngleVectorTemplate(T alpha,T beta,T gamma,T length)
{
Alpha=alpha;
Beta=beta;
Gamma=gamma;
Length=length;
}

template<typename T>
void XeAngleVectorTemplate<T>::Set(T alpha,T beta,T gamma,T length)
{
Alpha=alpha;
Beta=beta;
Gamma=gamma;
Length=length;
}

template<typename T>
void XeAngleVectorTemplate<T>::Mod(XeAngleVectorTemplate<T>& angle)
{
Alpha=fmod(Alpha,angle.Alpha);
Beta=fmod(Beta,angle.Beta);
Gamma=fmod(Gamma,angle.Gamma);
Length=fmod(Length,angle.Length);
}

template<typename T>
void XeAngleVectorTemplate<T>::ToVector(T& x, T& y, T& z)
{
x = MATH_LENGTHDIR_X(Length*cos(XeMath::DegToRad(Beta)),Alpha);
y = MATH_LENGTHDIR_Y(Length*cos(XeMath::DegToRad(Beta)),Alpha);
z = MATH_LENGTHDIR_Y(Length,-Beta);
}

template<typename T>
XeAngleVectorTemplate<T> XeAngleVectorTemplate<T>::operator+ (XeAngleVectorTemplate<T>& v)
{
XeAngleVectorTemplate<T> vr;
vr.Alpha=Alpha+v.Alpha;
vr.Beta=Beta+v.Beta;
vr.Gamma=Gamma+v.Gamma;
vr.Length=Length+v.Length;
return(vr);
}

template<typename T>
XeAngleVectorTemplate<T> XeAngleVectorTemplate<T>::operator- (XeAngleVectorTemplate<T>& v)
{
XeAngleVectorTemplate<T> vr;
vr.Alpha=Alpha-v.Alpha;
vr.Beta=Beta-v.Beta;
vr.Gamma=Gamma-v.Gamma;
vr.Length=Length-v.Length;
return(vr);
}

template<typename T>
XeAngleVectorTemplate<T> XeAngleVectorTemplate<T>::operator* (XeAngleVectorTemplate<T>& v)
{
XeAngleVectorTemplate<T> vr;
vr.Alpha=Alpha*v.Alpha;
vr.Beta=Beta*v.Beta;
vr.Gamma=Gamma*v.Gamma;
vr.Length=Length*v.Length;
return(vr);
}

template<typename T>
XeAngleVectorTemplate<T> XeAngleVectorTemplate<T>::operator/ (XeAngleVectorTemplate<T>& v)
{
XeAngleVectorTemplate<T> vr;
vr.Alpha=Alpha/v.Alpha;
vr.Beta=Beta/v.Beta;
vr.Gamma=Gamma/v.Gamma;
if(v.Length!=0)vr.Length=Length/v.Length;
return(vr);
}

template<typename T>
XeAngleVectorTemplate<T>& XeAngleVectorTemplate<T>::operator+= (XeAngleVectorTemplate<T>& v)
{
*this=*this+v;
return(*this);
}

template<typename T>
XeAngleVectorTemplate<T>& XeAngleVectorTemplate<T>::operator-= (XeAngleVectorTemplate<T>& v)
{
*this=*this-v;
return(*this);
}

template<typename T>
XeAngleVectorTemplate<T>& XeAngleVectorTemplate<T>::operator*= (XeAngleVectorTemplate<T>& v)
{
*this=*this*v;
return(*this);
}

template<typename T>
XeAngleVectorTemplate<T>& XeAngleVectorTemplate<T>::operator/= (XeAngleVectorTemplate<T>& v)
{
*this=*this/v;
return(*this);
}

template<typename T>
XeAngleVectorTemplate<T>& XeAngleVectorTemplate<T>::operator- ()
{
Alpha=-Alpha;
Beta=-Beta;
Gamma=-Gamma;
return(*this);
}

template<typename T>
bool XeAngleVectorTemplate<T>::operator== (XeAngleVectorTemplate<T>& v)
{
if(Alpha==v.Alpha&&Beta==v.Beta&&Gamma==v.Gamma&&Length==v.Length)
return(true);
return(false);
}

template<typename T>
bool XeAngleVectorTemplate<T>::operator!= (XeAngleVectorTemplate<T>& v)
{
if(Alpha!=v.Alpha||Beta!=v.Beta||Gamma!=v.Gamma||Length!=v.Length)
return(true);
return(false);
}

} // XeCore

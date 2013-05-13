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
XeVectorTemplate<T>::XeVectorTemplate(T x,T y,T z,T w)
{
X=x;
Y=y;
Z=z;
W=w;
}

template<typename T>
void XeVectorTemplate<T>::Set(T x,T y,T z,T w)
{
X=x;
Y=y;
Z=z;
W=w;
}

template<typename T>
T XeVectorTemplate<T>::Length()
{
return(sqrt((X*X)+(Y*Y)+(Z*Z)));
}

template<typename T>
XeVectorTemplate<T> XeVectorTemplate<T>::Normalize()
{
T l=Length();
if(l==(T)0)return(XeVectorTemplate());
XeVectorTemplate<T> vr;
vr.X=X/l;
vr.Y=Y/l;
vr.Z=Z/l;
return(vr);
}

template<typename T>
XeVectorTemplate<T> XeVectorTemplate<T>::Min(XeVectorTemplate<T>& v)
{
XeVectorTemplate<T> vr;
vr.X=min(X,v.X);
vr.Y=min(Y,v.Y);
vr.Z=min(Z,v.Z);
vr.W=min(W,v.W);
return(vr);
}

template<typename T>
XeVectorTemplate<T> XeVectorTemplate<T>::Max(XeVectorTemplate<T>& v)
{
XeVectorTemplate<T> vr;
vr.X=max(X,v.X);
vr.Y=max(Y,v.Y);
vr.Z=max(Z,v.Z);
vr.W=max(W,v.W);
return(vr);
}

template<typename T>
XeVectorTemplate<T> XeVectorTemplate<T>::Without(unsigned int flags)
{
XeVectorTemplate<T> vr=*this;
if(flags&XE_FLAG_X)vr.X=0;
if(flags&XE_FLAG_Y)vr.Y=0;
if(flags&XE_FLAG_Z)vr.Z=0;
if(flags&XE_FLAG_W)vr.W=1;
return(vr);
}

template<typename T>
XeVectorTemplate<T> XeVectorTemplate<T>::Amount(XeVectorTemplate<T>& v,T amount)
{
XeVectorTemplate<T> vr;
vr.X=(X-v.X)*min(1,max(0,amount))+v.X;
vr.Y=(Y-v.Y)*min(1,max(0,amount))+v.Y;
vr.Z=(Z-v.Z)*min(1,max(0,amount))+v.Z;
vr.W=(W-v.W)*min(1,max(0,amount))+v.W;
return(vr);
}

template<typename T>
XeVectorTemplate<T> XeVectorTemplate<T>::Project(XeVectorTemplate<T>& v)
{
XeVectorTemplate<T> vr;
T dp=*this%v;
T mp=v.X*v.X+v.Y*v.Y+v.Z*v.Z;
vr.X=(dp/mp)*v.X;
vr.Y=(dp/mp)*v.Y;
vr.Z=(dp/mp)*v.Z;
return(vr);
}

template<typename T>
void XeVectorTemplate<T>::ToAngle(T& alpha, T& beta)
{
alpha = MATH_DIRECTION_ALPHA(X,Y,Z);
beta = MATH_DIRECTION_BETA(X,Y,Z);
}

template<typename T>
XeVectorTemplate<T> XeVectorTemplate<T>::operator+ (XeVectorTemplate<T>& v)
{
XeVectorTemplate<T> vr;
vr.X=X+v.X;
vr.Y=Y+v.Y;
vr.Z=Z+v.Z;
return(vr);
}

template<typename T>
XeVectorTemplate<T> XeVectorTemplate<T>::operator+ (XeNumber& n)
{
XeVectorTemplate<T> vr;
vr.X=X+(T)n.Get();
vr.Y=Y+(T)n.Get();
vr.Z=Z+(T)n.Get();
return(vr);
}

template<typename T>
XeVectorTemplate<T> XeVectorTemplate<T>::operator- (XeVectorTemplate<T>& v)
{
XeVectorTemplate<T> vr;
vr.X=X-v.X;
vr.Y=Y-v.Y;
vr.Z=Z-v.Z;
return(vr);
}

template<typename T>
XeVectorTemplate<T> XeVectorTemplate<T>::operator- (XeNumber& n)
{
XeVectorTemplate<T> vr;
vr.X=X-(T)n.Get();
vr.Y=Y-(T)n.Get();
vr.Z=Z-(T)n.Get();
return(vr);
}

template<typename T>
XeVectorTemplate<T> XeVectorTemplate<T>::operator* (XeVectorTemplate<T>& v)
{
XeVectorTemplate<T> vr;
vr.X=X*v.X;
vr.Y=Y*v.Y;
vr.Z=Z*v.Z;
return(vr);
}

template<typename T>
XeVectorTemplate<T> XeVectorTemplate<T>::operator* (XeNumber& n)
{
XeVectorTemplate<T> vr;
vr.X=X*(T)n.Get();
vr.Y=Y*(T)n.Get();
vr.Z=Z*(T)n.Get();
return(vr);
}

template<typename T>
XeVectorTemplate<T> XeVectorTemplate<T>::operator/ (XeVectorTemplate<T>& v)
{
XeVectorTemplate<T> vr;
vr.X=X/v.X;
vr.Y=Y/v.Y;
vr.Z=Z/v.Z;
return(vr);
}

template<typename T>
XeVectorTemplate<T> XeVectorTemplate<T>::operator/ (XeNumber& n)
{
XeVectorTemplate<T> vr;
vr.X=X/(T)n.Get();
vr.Y=Y/(T)n.Get();
vr.Z=Z/(T)n.Get();
return(vr);
}

template<typename T>
XeVectorTemplate<T> XeVectorTemplate<T>::operator^ (XeVectorTemplate<T>& v)
{
return(XeVectorTemplate((Y*v.Z)-(v.Y*Z),(v.X*Z)-(X*v.Z),(X*v.Y)-(v.X*Y)));
}

template<typename T>
T XeVectorTemplate<T>::operator% (XeVectorTemplate<T>& v)
{
return(X*v.X+Y*v.Y+Z*v.Z);
}

template<typename T>
XeVectorTemplate<T>& XeVectorTemplate<T>::operator+= (XeVectorTemplate<T>& v)
{
*this=*this+v;
return(*this);
}

template<typename T>
XeVectorTemplate<T>& XeVectorTemplate<T>::operator+= (XeNumber& n)
{
*this=*this+n;
return(*this);
}

template<typename T>
XeVectorTemplate<T>& XeVectorTemplate<T>::operator-= (XeVectorTemplate<T>& v)
{
*this=*this-v;
return(*this);
}

template<typename T>
XeVectorTemplate<T>& XeVectorTemplate<T>::operator-= (XeNumber& n)
{
*this=*this-n;
return(*this);
}

template<typename T>
XeVectorTemplate<T>& XeVectorTemplate<T>::operator*= (XeVectorTemplate<T>& v)
{
*this=*this*v;
return(*this);
}

template<typename T>
XeVectorTemplate<T>& XeVectorTemplate<T>::operator*= (XeNumber& n)
{
*this=*this*n;
return(*this);
}

template<typename T>
XeVectorTemplate<T>& XeVectorTemplate<T>::operator/= (XeVectorTemplate<T>& v)
{
*this=*this/v;
return(*this);
}

template<typename T>
XeVectorTemplate<T>& XeVectorTemplate<T>::operator/= (XeNumber& n)
{
*this=*this/n;
return(*this);
}

template<typename T>
XeVectorTemplate<T>& XeVectorTemplate<T>::operator^= (XeVectorTemplate<T>& v)
{
*this=*this^v;
return(*this);
}

template<typename T>
XeVectorTemplate<T>& XeVectorTemplate<T>::operator- ()
{
X=-X;
Y=-Y;
Z=-Z;
return(*this);
}

template<typename T>
bool XeVectorTemplate<T>::operator== (XeVectorTemplate<T>& v)
{
if(X==v.X&&Y==v.Y&&Z==v.Z&&W==v.W)
return(true);
return(false);
}

template<typename T>
bool XeVectorTemplate<T>::operator!= (XeVectorTemplate<T>& v)
{
if(X!=v.X||Y!=v.Y||Z!=v.Z||W!=v.W)
return(true);
return(false);
}

} // XeCore

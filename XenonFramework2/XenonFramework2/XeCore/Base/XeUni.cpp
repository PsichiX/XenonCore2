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

#include "XeUni.h"


//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{

XeUni::XeUni()
{
Data=0;
Type=0;
Static=false;
}

XeUni::XeUni(const XeUni& value)
{
Data=0;
Type=0;
Static=false;
if(value.Type==1)
SetNumber(((XeUni&)value).GetNumber());
else
if(value.Type==2)
SetString(((XeUni&)value).GetString());
else
if(value.Type==3)
SetAssoc(*(Assoc*)(((XeUni&)value).Data));
}

XeUni::XeUni(XeNumber value)
{
Data=0;
Type=0;
Static=false;
SetNumber(value);
}

XeUni::XeUni(XeString& value)
{
Data=0;
Type=0;
Static=false;
SetString(value);
}

XeUni::XeUni(double value)
{
Data=0;
Type=0;
Static=false;
SetNumber(XeNumber(value));
}

XeUni::XeUni(char* value)
{
Data=0;
Type=0;
Static=false;
SetString(XeString(value));
}

XeUni::XeUni(Assoc& value)
{
Data=0;
Type=0;
Static=false;
SetAssoc(value);
}

XeUni::~XeUni()
{
if(!Static)
Unset();
}

XeNumber XeUni::GetNumber()
{
if(Data)
{
if(Type==1)
return(*(XeNumber*)Data);
if(Type==2)
{
double temp=0;
((XeString*)Data)->Convert(&temp,'r');
return(XeNumber(temp));
}
if(Type==3)
{
if(((Assoc*)Data)->Size())
return(((Assoc*)Data)->FirstPointer()->Value.GetNumber());
return(XeNumber());
}
}
return(XeNumber());
}

XeString XeUni::GetString()
{
if(Data)
{
if(Type==1)
{
XeString temp;
temp.Format("%f",((XeNumber*)Data)->Get());
return(temp);
}
if(Type==2)
return(*(XeString*)Data);
if(Type==3)
{
if(((Assoc*)Data)->Size())
return(((Assoc*)Data)->FirstPointer()->Value.GetString());
return(XeString());
}
}
return(XeString());
}

double XeUni::GetPureNumber()
{
if(Data)
{
if(Type==1)
return(((XeNumber*)Data)->Get());
}
return(0);
}

char* XeUni::GetPureString()
{
if(Data)
{
if(Type==2)
return(((XeString*)Data)->Get());
}
return(0);
}

void XeUni::GetAssoc(XeUni::Assoc& result)
{
if(Data)
{
if(Type==1)
{
result.Clear();
result[XeNumber(0)]=*this;
}
if(Type==2)
{
result.Clear();
result[XeNumber(0)]=*this;
}
if(Type==3)
{
result.Clear();
for(XeElementPointer<XePair<XeUni,XeUni> > elm=((Assoc*)Data)->FirstPointer();!elm.IsEmpty();elm.Next())
result[elm->Key]=elm->Value;
}
}
}

XeUni::Assoc* XeUni::GetPureAssoc()
{
if(Data)
{
if(Type==3)
return((Assoc*)Data);
}
return(0);
}

unsigned char XeUni::GetType()
{
if(Type==1)return('n');
if(Type==2)return('s');
if(Type==3)return('a');
return(0);
}

bool XeUni::IsUndefined()
{
return((Type==0)?true:false);
}

bool XeUni::IsNumber()
{
return((Type==1)?true:false);
}

bool XeUni::IsString()
{
return((Type==2)?true:false);
}

bool XeUni::IsAssoc()
{
return((Type==3)?true:false);
}

void XeUni::SetNumber(XeNumber& value)
{
Unset();
Data=new XeNumber;
((XeNumber*)Data)->Set(value.Get());
Type=1;
}

void XeUni::SetString(XeString& value)
{
Unset();
Data=new XeString;
((XeString*)Data)->Set(value.Get());
Type=2;
}

void XeUni::SetAssoc(Assoc& value)
{
Unset();
Data=new Assoc;
for(XeElementPointer<XePair<XeUni,XeUni> > elm=value.FirstPointer();!elm.IsEmpty();elm.Next())
((Assoc*)Data)->operator[](elm->Key)=elm->Value;
Type=3;
}

void XeUni::Unset()
{
if(Data)
{
if(Type==1)
{
delete (XeNumber*)Data;
}
if(Type==2)
{
((XeString*)Data)->Clear();
delete (XeString*)Data;
}
if(Type==3)
{
((Assoc*)Data)->Clear();
delete (Assoc*)Data;
}
}
Data=0;
Type=0;
}

bool XeUni::Compare(XeUni& value)
{
if(Type==value.Type)
{
if(Type==0)return(true);
if(Type==1)if((*(XeNumber*)Data)==(*(XeNumber*)value.Data))return(true);
if(Type==2)if((*(XeString*)Data)==(*(XeString*)value.Data))return(true);
if(Type==3)
{
if(((Assoc*)Data)->Size()!=((Assoc*)value.Data)->Size())
return(false);
for(XeElementPointer<XePair<XeUni,XeUni> > elm1=((Assoc*)value.Data)->FirstPointer(),elm2=((Assoc*)Data)->FirstPointer();!elm1.IsEmpty()&&!elm2.IsEmpty();elm1.Next(),elm2.Next())
if(elm1->Key!=elm2->Key||elm1->Value!=elm2->Value)
return(false);
return(true);
}
}
return(false);
}

void XeUni::operator= (const XeUni& value)
{
if(value.Type==1)
SetNumber(((XeUni&)value).GetNumber());
else
if(value.Type==2)
SetString(((XeUni&)value).GetString());
else
if(value.Type==3)
SetAssoc(*((XeUni&)value).GetPureAssoc());
else
Unset();
}

void XeUni::operator= (XeNumber& value)
{
SetNumber(value);
}

void XeUni::operator= (XeString& value)
{
SetString(value);
}

void XeUni::operator= (double value)
{
SetNumber(XeNumber(value));
}

void XeUni::operator= (char* value)
{
SetString(XeString(value));
}

void XeUni::operator= (Assoc& value)
{
SetAssoc(value);
}

XeUni::operator XeNumber() const
{
return(((XeUni*)this)->GetNumber());
}

XeUni::operator XeString() const
{
return(((XeUni*)this)->GetString());
}

XeUni::operator double() const
{
if(Type==0)return(0);
return(((XeUni*)this)->GetNumber().Get());
}

XeUni::operator char*() const
{
if(Type==0)return(0);
return(((XeUni*)this)->GetString().Get());
}

bool XeUni::operator== (XeUni& value)
{
return(Compare(value));
}

bool XeUni::operator!= (XeUni& value)
{
return(!Compare(value));
}

XeUni& XeUni::operator[] (XeUni& key)
{
return(GetPureAssoc()->operator[](key));
}

} // XeCore

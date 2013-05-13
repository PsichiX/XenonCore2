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

#include "XeWstring.h"
#include <Windows.h>
#include <string.h>
#include <stdio.h>


//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{

XeWstring::XeWstring()
{
#ifdef XE_ALLOC_C
Text=(wchar_t*)malloc(sizeof(wchar_t)*1);
#else
Text=new wchar_t[1];
#endif /* XE_ALLOC_C */
Text[0]=0;
Static=false;
}

XeWstring::XeWstring(const XeWstring& str)
{
#ifdef XE_ALLOC_C
Text=(wchar_t*)malloc(sizeof(wchar_t)*1);
#else
Text=new wchar_t[1];
#endif /* XE_ALLOC_C */
Text[0]=0;
Static=false;
Set(str);
}

XeWstring::XeWstring(wchar_t* str)
{
#ifdef XE_ALLOC_C
Text=(wchar_t*)malloc(sizeof(wchar_t)*1);
#else
Text=new wchar_t[1];
#endif /* XE_ALLOC_C */
Text[0]=0;
Static=false;
Set(str);
}

XeWstring::XeWstring(char* str)
{
#ifdef XE_ALLOC_C
Text=(wchar_t*)malloc(sizeof(wchar_t)*1);
#else
Text=new wchar_t[1];
#endif /* XE_ALLOC_C */
Text[0]=0;
Static=false;
Set(str);
}

XeWstring::~XeWstring()
{
if(!Static)
{
if(Text!=0)
#ifdef XE_ALLOC_C
free(Text);
#else
delete[] Text;
#endif /* XE_ALLOC_C */
Text=0;
}
}

wchar_t XeWstring::Index(unsigned int index,bool invert)
{
if(!Text)return(0);
unsigned int len=wcslen(Text);
if(!len)return(Text[0]);
if(!invert)
return((Text+min(index,len))[0]);
else
return((Text+len-1-min(index,len))[0]);
}

wchar_t* XeWstring::Get(unsigned int index,bool invert)
{
if(!Text)return(0);
unsigned int len=wcslen(Text);
if(!len)return(Text);
if(!invert)
return(Text+min(index,len));
else
return(Text+len-1-min(index,len));
}

bool XeWstring::GetAnsi(char* result,unsigned int buffsize)
{
if(!result||!buffsize)return(false);
unsigned int len=wcslen(Text);
wcstombs_s(0,result,buffsize,Text,len);
return(true);
}

void XeWstring::Set(wchar_t* str)
{
if(!str)return;
unsigned int len=wcslen(str);
#ifdef XE_ALLOC_C
if(Text)free(Text);
Text=(wchar_t*)malloc(sizeof(wchar_t)*(len+1));
#else
if(Text)delete[] Text;
Text=new wchar_t[len+1];
#endif /* XE_ALLOC_C */
Text[0]=0;
wcscpy_s(Text,len+1,str);
Text[len]=0;
}

void XeWstring::Set(char* str)
{
if(!str)return;
unsigned int len=strlen(str);
#ifdef XE_ALLOC_C
if(Text)free(Text);
Text=(wchar_t*)malloc(sizeof(wchar_t)*(len+1));
#else
if(Text)delete[] Text;
Text=new wchar_t[len+1];
#endif /* XE_ALLOC_C */
Text[0]=0;
mbstowcs_s(0,Text,len+1,str,len);
Text[len]=0;
}

void XeWstring::Copy(wchar_t* src,unsigned int size)
{
if(!src)return;
unsigned int len=min(size,wcslen(src));
#ifdef XE_ALLOC_C
if(Text)free(Text);
Text=(wchar_t*)malloc(sizeof(wchar_t)*(len+1));
#else
if(Text)delete[] Text;
Text=new wchar_t[len+1];
#endif /* XE_ALLOC_C */
Text[0]=0;
memcpy(Text,src,len);
Text[len]=0;
}

void XeWstring::Format(wchar_t* str,...)
{
unsigned int count=0;
va_list vl;
va_start(vl,str);
count=_vscwprintf(str,vl);
va_end(vl);
#ifdef XE_ALLOC_C
if(Text)free(Text);
Text=(wchar_t*)malloc(sizeof(wchar_t)*(count+1));
#else
if(Text)delete[] Text;
Text=new wchar_t[count+1];
#endif /* XE_ALLOC_C */
Text[0]=0;
va_start(vl,str);
vswprintf_s(Text,count+1,str,vl);
va_end(vl);
}

XeWstring* XeWstring::Explode(wchar_t* sep,unsigned int& count,wchar_t* block)
{
XeWstring str;
str.Set(Text);
count=0;
unsigned int len=wcslen(str.Get());
unsigned int slen=wcslen(sep);
unsigned int ulen=0;
if(block)ulen=wcslen(block);
unsigned int num=0;
unsigned int lastp=0;
bool un=false;
bool fi=true;
for(unsigned int i=0;i<len;i++)
{
for(unsigned int k=0;k<ulen;k++)
if(str.Get()[i]==block[k])un=!un;
if(un)continue;
for(unsigned int j=0;j<slen;j++)
if(str.Get()[i]==sep[j]||str.Get()[i]==0)
{
if(i-lastp>1||(fi&&i>0))
num++;
lastp=i;
if(fi)fi=false;
break;
}
}
XeWstring* result=new XeWstring[num+1];
wchar_t* last=str;
lastp=0;
un=false;
fi=true;
for(unsigned int i=0;i<len+1;i++)
{
for(unsigned int k=0;k<ulen;k++)
if(str.Get()[i]==block[k])un=!un;
if(un)continue;
for(unsigned int j=0;j<slen;j++)
if(str.Get()[i]==sep[j]||str.Get()[i]==0)
{
if(i-lastp>1||(fi&&i>0))
{
str.Get()[i]=0;
result[count++].Set(last);
}
lastp=i;
last=&str.Get()[i+1];
if(fi)fi=false;
break;
}
}
return(result);
}

XeWstring* XeWstring::ExplodeBuff(wchar_t* buff,unsigned int size,wchar_t* sep,unsigned int& count,wchar_t* block)
{
count=0;
unsigned int slen=wcslen(sep);
unsigned int ulen=0;
if(block)ulen=wcslen(block);
unsigned int num=0;
unsigned int lastp=0;
bool un=false;
bool fi=true;
for(unsigned int i=0;i<size;i++)
{
for(unsigned int k=0;k<ulen;k++)
if(buff[i]==block[k])un=!un;
if(un)continue;
for(unsigned int j=0;j<slen;j++)
if(buff[i]==sep[j]||buff[i]==0)
{
if(i-lastp>1||(fi&&i>0))
num++;
lastp=i;
if(fi)fi=false;
break;
}
}
XeWstring* result=new XeWstring[num+1];
wchar_t* last=buff;
lastp=0;
un=false;
fi=true;
for(unsigned int i=0;i<size+1;i++)
{
for(unsigned int k=0;k<ulen;k++)
if(buff[i]==block[k])un=!un;
if(un)continue;
for(unsigned int j=0;j<slen;j++)
if(buff[i]==sep[j]||buff[i]==0)
{
if(i-lastp>1||(fi&&i>0))
{
wchar_t chr=buff[i];
buff[i]=0;
result[count++].Set(last);
buff[i]=chr;
}
lastp=i;
last=&buff[i+1];
if(fi)fi=false;
break;
}
}
return(result);
}

bool XeWstring::Convert(void* out,int deftype)
{
unsigned int len=wcslen(Text);
if((deftype&&len<=0)||(!deftype&&len<=1))return(false);
wchar_t type=Text[len-1];
if(deftype)type=deftype;
if(type=='x')
{
unsigned int sp=0;
wchar_t val=0;
unsigned int start=len-1;
if(deftype)start=len;
bool g=0;
for(unsigned int p=start;p>0;p--,g=!g)
{
if(g==0)((wchar_t*)out)[sp]=0;
if(Text[p-1]>='0'&&Text[p-1]<='9')
val=Text[p-1]-'0';
else
if(Text[p-1]>='a'&&Text[p-1]<='f')
val=Text[p-1]-'a'+10;
else
if(Text[p-1]>='A'&&Text[p-1]<='F')
val=Text[p-1]-'A'+10;
else
val=0;
((wchar_t*)out)[sp]|=val<<4*g;
if(g==1)sp++;
}
return(true);
}
else
if(type=='c')
{
if(!deftype)Text[len-1]=0;
*(wchar_t*)out=(wchar_t)wcstol(Text,0,0);
if(!deftype)Text[len-1]='c';
return(true);
}
/*else
if(type=='b')
{
if(!deftype)Text[len-1]=0;
*(wchar_t*)out=(wchar_t)wcstoul(Text,0,0);
if(!deftype)Text[len-1]='b';
return(true);
}*/
else
if(type=='s')
{
if(!deftype)Text[len-1]=0;
*(short*)out=(short)wcstol(Text,0,0);
if(!deftype)Text[len-1]='s';
return(true);
}
else
if(type=='w')
{
if(!deftype)Text[len-1]=0;
*(unsigned short*)out=(unsigned short)wcstoul(Text,0,0);
if(!deftype)Text[len-1]='w';
return(true);
}
else
if(type=='i')
{
if(!deftype)Text[len-1]=0;
*(int*)out=(int)wcstol(Text,0,0);
if(!deftype)Text[len-1]='i';
return(true);
}
else
if(type=='d')
{
if(!deftype)Text[len-1]=0;
*(unsigned int*)out=(unsigned int)wcstoul(Text,0,0);
if(!deftype)Text[len-1]='d';
return(true);
}
else
if(type=='h')
{
if(!deftype)Text[len-1]=0;
*(float*)out=(float)wcstod(Text,0);
if(!deftype)Text[len-1]='h';
return(true);
}
else
if(type=='r')
{
if(!deftype)Text[len-1]=0;
*(double*)out=(double)wcstod(Text,0);
if(!deftype)Text[len-1]='r';
return(true);
}
else
if(type=='f')
{
if(!deftype)Text[len-1]=0;
XeWstring temp;
unsigned int p=0;
unsigned int i=0;
p=Search(temp,L":",p);
((float*)out)[i++]=(float)wcstod(temp.Get(),0);
while(p&&i<4)
{
p=Search(temp,L":",p);
((float*)out)[i++]=(float)wcstod(temp.Get(),0);
}
if(!deftype)Text[len-1]='f';
return(true);
}
else
if(type=='v')
{
if(!deftype)Text[len-1]=0;
XeWstring temp;
unsigned int p=0;
unsigned int i=0;
p=Search(temp,L":",p);
((double*)out)[i++]=(double)wcstod(temp.Get(),0);
while(p&&i<4)
{
p=Search(temp,L":",p);
((double*)out)[i++]=(double)wcstod(temp.Get(),0);
}
if(!deftype)Text[len-1]='v';
return(true);
}
return(false);
}

int XeWstring::ConvertType()
{
unsigned int len=wcslen(Text);
if(len<=1)return(0);
wchar_t type=Text[len-1];
if(type=='x'||type=='c'||type=='b'||type=='s'||type=='w'||type=='i'||type=='d'||type=='h'||type=='r'||type=='f'||type=='v')return(type);
return(0);
}

unsigned int XeWstring::ConvertSize()
{
unsigned int len=wcslen(Text);
if(len<=1)return(0);
wchar_t type=Text[len-1];
if(type=='x')return(len/2);
if(type=='c'||type=='b')return(1);
if(type=='s'||type=='w')return(2);
if(type=='i'||type=='d')return(4);
if(type=='h')return(4);
if(type=='r')return(8);
if(type=='f')return(16);
if(type=='v')return(32);
return(0);
}

void XeWstring::EscapeSeq()
{
unsigned int len=wcslen(Text);
if(len<=0)return;
#ifdef XE_ALLOC_C
wchar_t* temp=(wchar_t*)malloc(sizeof(wchar_t)*len);
#else
wchar_t* temp=new wchar_t[len+1];
#endif /* XE_ALLOC_C */
if(!temp)return;
wchar_t* spos=Text;
wchar_t* dpos=temp;
while(*spos&&(unsigned int)spos<=(unsigned int)Text+len)
{
if(*spos!='\\')
{
*dpos=*spos;
spos++;
dpos++;
}
else
{
spos++;
if(!*spos)continue;
if(*spos=='0')*dpos='\0';
if(*spos=='a')*dpos='\a';
if(*spos=='b')*dpos='\b';
if(*spos=='f')*dpos='\f';
if(*spos=='n')*dpos='\n';
if(*spos=='r')*dpos='\r';
if(*spos=='t')*dpos='\t';
if(*spos=='v')*dpos='\v';
if(*spos=='\'')*dpos='\'';
if(*spos=='"')*dpos='\"';
if(*spos=='\\')*dpos='\\';
if(*spos=='?')*dpos='\?';
if(*spos=='x')
{
wchar_t res=0;
wchar_t tmp=0;
spos++;
if(!*spos)continue;
if(*spos>='0'&&*spos<='9')tmp=*spos-'0';
else
if(*spos>='a'&&*spos<='f')tmp=*spos-'a'+10;
else
if(*spos>='A'&&*spos<='F')tmp=*spos-'A'+10;
res|=tmp<<4;
spos++;
if(!*spos)continue;
if(*spos>='0'&&*spos<='9')tmp=*spos-'0';
else
if(*spos>='a'&&*spos<='f')tmp=*spos-'a'+10;
else
if(*spos>='A'&&*spos<='F')tmp=*spos-'A'+10;
res|=tmp;
*dpos=res;
}
spos++;
dpos++;
}
}
*dpos=0;
Set(temp);
delete[] temp;
}

unsigned int XeWstring::Length()
{
return(wcslen(Text));
}

unsigned int XeWstring::LengthUnicode(unsigned int extrachars)
{
return((wcslen(Text)+extrachars)*sizeof(char));
}

bool XeWstring::Find(unsigned int offset,wchar_t* substr,unsigned int* position)
{
if(offset>=wcslen(Text))return(false);
void* pos=wcsstr(&Text[offset],substr);
if((unsigned int)pos<(unsigned int)Text)return(false);
if(position)*position=(unsigned int)pos-(unsigned int)Text;
return(true);
}

unsigned int XeWstring::Search(XeWstring& result,wchar_t* delim,unsigned int offset)
{
if(offset>wcslen(Text))return(0);
wchar_t* begin=(wchar_t*)((unsigned int)Text+offset);
wchar_t* end=wcsstr(begin,delim);
if(!end)end=(wchar_t*)((unsigned int)Text+(unsigned int)wcslen(Text));
if((unsigned int)end<(unsigned int)Text||(unsigned int)end<(unsigned int)begin)return(0);
result.Copy(begin,(unsigned int)end-(unsigned int)begin);
unsigned int pos=(unsigned int)(end-Text)+wcslen(delim);
if(pos>wcslen(Text))pos=0;
return(pos);
}

unsigned int XeWstring::Replace(XeWstring& result,wchar_t* oldstr,wchar_t* newstr)
{
result.Clear();
unsigned int count=0;
wchar_t* pos=Text;
wchar_t* last=Text;
wchar_t* end=&Text[wcslen(Text)];
XeWstring part;
while(pos<end)
{
pos=wcsstr(last,oldstr);
if(!pos)
{
pos=end;
part.Copy(last,pos-last);
result<<part;
}
else
{
count++;
part.Copy(last,pos-last);
result<<part<<newstr;
}
part.Clear();
last=pos+wcslen(oldstr);
}
return(count);
}

unsigned int XeWstring::ReplaceChars(XeWstring& result,wchar_t oldchar,wchar_t newchar)
{
unsigned int count=0;
for(unsigned int i=0;i<Length();i++)
if(Text[i]==oldchar)
{
Text[i]=newchar;
count++;
}
return(count);
}

void XeWstring::Clear()
{
#ifdef XE_ALLOC_C
if(Text)free(Text);
Text=(wchar_t*)malloc(sizeof(wchar_t)*1);
#else
if(Text)delete[] Text;
Text=new wchar_t[1];
#endif /* XE_ALLOC_C */
Text[0]=0;
}

void XeWstring::operator= (const XeWstring& str)
{
Set(str);
}

void XeWstring::operator= (wchar_t* str)
{
Set(str);
}

XeWstring::operator wchar_t*() const
{
return(Text);
}

XeWstring& XeWstring::operator<< (wchar_t* value)
{
unsigned int _len=wcslen(Text)+wcslen(value);
#ifdef XE_ALLOC_C
wchar_t* newtext=(wchar_t*)malloc(sizeof(wchar_t)*(_len+1));
#else
wchar_t* newtext=new wchar_t[_len+1];
#endif /* XE_ALLOC_C */
wcscpy_s(newtext,_len+1,Text);
wcscat_s(newtext,_len+1,value);
#ifdef XE_ALLOC_C
if(Text)free(Text);
#else
if(Text)delete[] Text;
#endif /* XE_ALLOC_C */
Text=newtext;
Text[_len]=0;
return(*this);
}

bool XeWstring::operator== (XeWstring& str)
{
if(wcscmp(Text,str.Get())==0)
return(true);
return(false);
}

bool XeWstring::operator!= (XeWstring& str)
{
if(wcscmp(Text,str.Get())!=0)
return(true);
return(false);
}

bool XeWstring::operator== (wchar_t* str)
{
if(wcscmp(Text,str)==0)
return(true);
return(false);
}

bool XeWstring::operator!= (wchar_t* str)
{
if(wcscmp(Text,str)!=0)
return(true);
return(false);
}

} // XeCore

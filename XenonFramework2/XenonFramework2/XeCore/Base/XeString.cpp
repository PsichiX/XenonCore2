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

#include "XeString.h"
#include <Windows.h>
#include <string.h>
#include <stdio.h>


//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{

XeString::XeString()
{
#ifdef XE_ALLOC_C
Text=(char*)malloc(sizeof(char)*1);
#else
Text=new char[1];
#endif /* XE_ALLOC_C */
Text[0]=0;
Static=false;
}

XeString::XeString(const XeString& str)
{
#ifdef XE_ALLOC_C
Text=(char*)malloc(sizeof(char)*1);
#else
Text=new char[1];
#endif /* XE_ALLOC_C */
Text[0]=0;
Static=false;
Set(str);
}

XeString::XeString(char* str)
{
#ifdef XE_ALLOC_C
Text=(char*)malloc(sizeof(char)*1);
#else
Text=new char[1];
#endif /* XE_ALLOC_C */
Text[0]=0;
Static=false;
Set(str);
}

XeString::XeString(wchar_t* str)
{
#ifdef XE_ALLOC_C
Text=(char*)malloc(sizeof(char)*1);
#else
Text=new char[1];
#endif /* XE_ALLOC_C */
Text[0]=0;
Static=false;
Set(str);
}

XeString::~XeString()
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

char XeString::Index(unsigned int index,bool invert)
{
if(!Text)return(0);
unsigned int len=strlen(Text);
if(!len)return(Text[0]);
if(!invert)
return((Text+min(index,len))[0]);
else
return((Text+len-1-min(index,len))[0]);
}

char* XeString::Get(unsigned int index,bool invert)
{
if(!Text)return(0);
unsigned int len=strlen(Text);
if(!len)return(Text);
if(!invert)
return(Text+min(index,len));
else
return(Text+len-1-min(index,len));
}

bool XeString::GetUnicode(wchar_t* result,unsigned int buffsize)
{
if(!result||!buffsize)return(false);
unsigned int len=strlen(Text);
mbstowcs_s(0,result,buffsize,Text,len);
return(true);
}

void XeString::Set(char* str)
{
if(!str)return;
unsigned int len=strlen(str);
#ifdef XE_ALLOC_C
if(Text)free(Text);
Text=(char*)malloc(sizeof(char)*(len+1));
#else
if(Text)delete[] Text;
Text=new char[len+1];
#endif /* XE_ALLOC_C */
Text[0]=0;
strcpy_s(Text,len+1,str);
Text[len]=0;
}

void XeString::Set(wchar_t* str)
{
if(!str)return;
unsigned int len=wcslen(str);
#ifdef XE_ALLOC_C
if(Text)free(Text);
Text=(char*)malloc(sizeof(char)*(len+1));
#else
if(Text)delete[] Text;
Text=new char[len+1];
#endif /* XE_ALLOC_C */
Text[0]=0;
wcstombs_s(0,Text,len+1,str,len);
Text[len]=0;
}

void XeString::Copy(char* src,unsigned int size)
{
if(!src)return;
unsigned int len=min(size,strlen(src));
#ifdef XE_ALLOC_C
if(Text)free(Text);
Text=(char*)malloc(sizeof(char)*(len+1));
#else
if(Text)delete[] Text;
Text=new char[len+1];
#endif /* XE_ALLOC_C */
Text[0]=0;
memcpy(Text,src,len);
Text[len]=0;
}

void XeString::Format(char* str,...)
{
unsigned int count=0;
va_list vl;
va_start(vl,str);
count=_vscprintf(str,vl);
va_end(vl);
#ifdef XE_ALLOC_C
if(Text)free(Text);
Text=(char*)malloc(sizeof(char)*(count+1));
#else
if(Text)delete[] Text;
Text=new char[count+1];
#endif /* XE_ALLOC_C */
Text[0]=0;
va_start(vl,str);
vsprintf_s(Text,count+1,str,vl);
va_end(vl);
}

XeString* XeString::Explode(char* sep,unsigned int& count,char* block)
{
XeString str;
str.Set(Text);
count=0;
unsigned int len=strlen(str.Get());
unsigned int slen=strlen(sep);
unsigned int ulen=0;
if(block)ulen=strlen(block);
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
XeString* result=new XeString[num+1];
char* last=str;
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

XeString* XeString::ExplodeBuff(char* buff,unsigned int size,char* sep,unsigned int& count,char* block)
{
count=0;
unsigned int slen=strlen(sep);
unsigned int ulen=0;
if(block)ulen=strlen(block);
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
XeString* result=new XeString[num+1];
char* last=buff;
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
char chr=buff[i];
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

bool XeString::Convert(void* out,int deftype)
{
unsigned int len=strlen(Text);
if((deftype&&len<=0)||(!deftype&&len<=1))return(false);
char type=Text[len-1];
if(deftype)type=deftype;
if(type=='x')
{
unsigned int sp=0;
unsigned char val=0;
unsigned int start=len-1;
if(deftype)start=len;
bool g=0;
for(unsigned int p=start;p>0;p--,g=!g)
{
if(g==0)((unsigned char*)out)[sp]=0;
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
((unsigned char*)out)[sp]|=val<<4*g;
if(g==1)sp++;
}
return(true);
}
else
if(type=='c')
{
if(!deftype)Text[len-1]=0;
*(char*)out=(char)strtol(Text,0,0);
if(!deftype)Text[len-1]='c';
return(true);
}
else
if(type=='b')
{
if(!deftype)Text[len-1]=0;
*(unsigned char*)out=(unsigned char)strtoul(Text,0,0);
if(!deftype)Text[len-1]='b';
return(true);
}
else
if(type=='s')
{
if(!deftype)Text[len-1]=0;
*(short*)out=(short)strtol(Text,0,0);
if(!deftype)Text[len-1]='s';
return(true);
}
else
if(type=='w')
{
if(!deftype)Text[len-1]=0;
*(unsigned short*)out=(unsigned short)strtoul(Text,0,0);
if(!deftype)Text[len-1]='w';
return(true);
}
else
if(type=='i')
{
if(!deftype)Text[len-1]=0;
*(int*)out=(int)strtol(Text,0,0);
if(!deftype)Text[len-1]='i';
return(true);
}
else
if(type=='d')
{
if(!deftype)Text[len-1]=0;
*(unsigned int*)out=(unsigned int)strtoul(Text,0,0);
if(!deftype)Text[len-1]='d';
return(true);
}
else
if(type=='h')
{
if(!deftype)Text[len-1]=0;
*(float*)out=(float)strtod(Text,0);
if(!deftype)Text[len-1]='h';
return(true);
}
else
if(type=='r')
{
if(!deftype)Text[len-1]=0;
*(double*)out=(double)strtod(Text,0);
if(!deftype)Text[len-1]='r';
return(true);
}
else
if(type=='f')
{
if(!deftype)Text[len-1]=0;
XeString temp;
unsigned int p=0;
unsigned int i=0;
p=Search(temp,":",p);
((float*)out)[i++]=(float)strtod(temp.Get(),0);
while(p&&i<4)
{
p=Search(temp,":",p);
((float*)out)[i++]=(float)strtod(temp.Get(),0);
}
if(!deftype)Text[len-1]='f';
return(true);
}
else
if(type=='v')
{
if(!deftype)Text[len-1]=0;
XeString temp;
unsigned int p=0;
unsigned int i=0;
p=Search(temp,":",p);
((double*)out)[i++]=(double)strtod(temp.Get(),0);
while(p&&i<4)
{
p=Search(temp,":",p);
((double*)out)[i++]=(double)strtod(temp.Get(),0);
}
if(!deftype)Text[len-1]='v';
return(true);
}
return(false);
}

int XeString::ConvertType()
{
unsigned int len=strlen(Text);
if(len<=1)return(0);
char type=Text[len-1];
if(type=='x'||type=='c'||type=='b'||type=='s'||type=='w'||type=='i'||type=='d'||type=='h'||type=='r'||type=='f'||type=='v')return(type);
return(0);
}

unsigned int XeString::ConvertSize()
{
unsigned int len=strlen(Text);
if(len<=1)return(0);
char type=Text[len-1];
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

void XeString::EscapeSeq()
{
unsigned int len=strlen(Text);
if(len<=0)return;
#ifdef XE_ALLOC_C
char* temp=(char*)malloc(sizeof(char)*len);
#else
char* temp=new char[len+1];
#endif /* XE_ALLOC_C */
if(!temp)return;
char* spos=Text;
char* dpos=temp;
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
char res=0;
char tmp=0;
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

unsigned int XeString::Length()
{
return(strlen(Text));
}

unsigned int XeString::LengthUnicode(unsigned int extrachars)
{
return((strlen(Text)+extrachars)*sizeof(wchar_t));
}

bool XeString::Find(unsigned int offset,char* substr,unsigned int* position)
{
if(offset>=strlen(Text))return(false);
void* pos=strstr(&Text[offset],substr);
if((unsigned int)pos<(unsigned int)Text)return(false);
if(position)*position=(unsigned int)pos-(unsigned int)Text;
return(true);
}

unsigned int XeString::Search(XeString& result,char* delim,unsigned int offset)
{
if(offset>strlen(Text))return(0);
char* begin=(char*)((unsigned int)Text+offset);
char* end=strstr(begin,delim);
if(!end)end=(char*)((unsigned int)Text+(unsigned int)strlen(Text));
if((unsigned int)end<(unsigned int)Text||(unsigned int)end<(unsigned int)begin)return(0);
result.Copy(begin,(unsigned int)end-(unsigned int)begin);
unsigned int pos=(unsigned int)(end-Text)+strlen(delim);
if(pos>strlen(Text))pos=0;
return(pos);
}

unsigned int XeString::Replace(XeString& result,char* oldstr,char* newstr)
{
result.Clear();
unsigned int count=0;
char* pos=Text;
char* last=Text;
char* end=&Text[strlen(Text)];
XeString part;
while(pos<end)
{
pos=strstr(last,oldstr);
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
last=pos+strlen(oldstr);
}
return(count);
}

unsigned int XeString::ReplaceChars(XeString& result,char oldchar,char newchar)
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

void XeString::Clear()
{
#ifdef XE_ALLOC_C
if(Text)free(Text);
Text=(char*)malloc(sizeof(char)*1);
#else
if(Text)delete[] Text;
Text=new char[1];
#endif /* XE_ALLOC_C */
Text[0]=0;
}

void XeString::operator= (const XeString& str)
{
Set(str);
}

void XeString::operator= (char* str)
{
Set(str);
}

XeString::operator char*() const
{
return(Text);
}

XeString& XeString::operator<< (double value)
{
#ifdef XE_ALLOC_C
char* buff=(char*)malloc(sizeof(char)*33);
#else
char* buff=new char[33];
#endif /* XE_ALLOC_C */
_gcvt_s(buff,32,value,8);
unsigned int _len=strlen(Text)+strlen(buff);
#ifdef XE_ALLOC_C
char* newtext=(char*)malloc(sizeof(char)*(_len+1));
#else
char* newtext=new char[_len+1];
#endif /* XE_ALLOC_C */
strcpy_s(newtext,(_len+1),Text);
strcat_s(newtext,(_len+1),buff);
#ifdef XE_ALLOC_C
if(buff)free(buff);
if(Text)free(Text);
#else
if(buff)delete[] buff;
if(Text)delete[] Text;
#endif /* XE_ALLOC_C */
Text=newtext;
Text[_len]=0;
return(*this);
}

XeString& XeString::operator<< (int value)
{
#ifdef XE_ALLOC_C
char* buff=(char*)malloc(sizeof(char)*33);
#else
char* buff=new char[33];
#endif /* XE_ALLOC_C */
_itoa_s(value,buff,32,XE_BASE_DEC);
unsigned int _len=strlen(Text)+strlen(buff);
#ifdef XE_ALLOC_C
char* newtext=(char*)malloc(sizeof(char)*(_len+1));
#else
char* newtext=new char[_len+1];
#endif /* XE_ALLOC_C */
strcpy_s(newtext,_len+1,Text);
strcat_s(newtext,_len+1,buff);
#ifdef XE_ALLOC_C
if(buff)free(buff);
if(Text)free(Text);
#else
if(buff)delete[] buff;
if(Text)delete[] Text;
#endif /* XE_ALLOC_C */
Text=newtext;
Text[_len]=0;
return(*this);
}

XeString& XeString::operator<< (unsigned int value)
{
#ifdef XE_ALLOC_C
char* buff=(char*)malloc(sizeof(char)*33);
#else
char* buff=new char[33];
#endif /* XE_ALLOC_C */
_ultoa_s((unsigned long)value,buff,32,XE_BASE_DEC);
unsigned int _len=strlen(Text)+strlen(buff);
#ifdef XE_ALLOC_C
char* newtext=(char*)malloc(sizeof(char)*(_len+1));
#else
char* newtext=new char[_len+1];
#endif /* XE_ALLOC_C */
strcpy_s(newtext,_len+1,Text);
strcat_s(newtext,_len+1,buff);
#ifdef XE_ALLOC_C
if(buff)free(buff);
if(Text)free(Text);
#else
if(buff)delete[] buff;
if(Text)delete[] Text;
#endif /* XE_ALLOC_C */
Text=newtext;
Text[_len]=0;
return(*this);
}

XeString& XeString::operator<< (char* value)
{
unsigned int _len=strlen(Text)+strlen(value);
#ifdef XE_ALLOC_C
char* newtext=(char*)malloc(sizeof(char)*(_len+1));
#else
char* newtext=new char[_len+1];
#endif /* XE_ALLOC_C */
strcpy_s(newtext,_len+1,Text);
strcat_s(newtext,_len+1,value);
#ifdef XE_ALLOC_C
if(Text)free(Text);
#else
if(Text)delete[] Text;
#endif /* XE_ALLOC_C */
Text=newtext;
Text[_len]=0;
return(*this);
}

bool XeString::operator== (XeString& str)
{
if(strcmp(Text,str.Get())==0)
return(true);
return(false);
}

bool XeString::operator!= (XeString& str)
{
if(strcmp(Text,str.Get())!=0)
return(true);
return(false);
}

bool XeString::operator== (char* str)
{
if(strcmp(Text,str)==0)
return(true);
return(false);
}

bool XeString::operator!= (char* str)
{
if(strcmp(Text,str)!=0)
return(true);
return(false);
}

} // XeCore

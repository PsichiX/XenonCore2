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

#include "XeFontmap.h"
#include "XeString.h"
#include <stdio.h>


//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{

XeFontmap::Char::Char()
{
Width=0;
Height=0;
Xoffset=0;
Yoffset=0;
Advance=0;
Xbegin=0;
Ybegin=0;
Xend=0;
Yend=0;
}

XeFontmap::XeFontmap()
{
Xsep=0;
Ysep=0;
NewLine='\n';
Size=0;
}

bool XeFontmap::Compile(char* fname)
{
FILE* f=0;
fopen_s(&f,fname,"rb");
if(!f)return(false);
fseek(f,0,SEEK_END);
unsigned int size=ftell(f);
rewind(f);
char* buff=new char[size];
if(!buff)
{
fclose(f);
return(false);
}
fread(buff,size,1,f);
fclose(f);
bool status=CompileFromMemory(buff,size);
delete[] buff;
return(status);
}

bool XeFontmap::CompileFromMemory(void* buff,unsigned int size)
{
if(!buff||!size)return(false);
int tw=0;
int th=0;
int fs=0;
XeString param;
XeString value;
unsigned int linesc=0;
XeString* lines=XeString::ExplodeBuff((char*)buff,size,"\r\n",linesc);
if(!lines||!linesc)return(false);
for(unsigned int i=0;i<linesc;i++)
{
unsigned int wordsc=0;
XeString* words=lines[i].Explode(" \t",wordsc,"\"");
if(!words||!wordsc)continue;
if(words[0]=="common")
{
for(unsigned int j=1;j<wordsc;j++)
{
param.Clear();
value.Clear();
words[j].Search(value,"\n",words[j].Search(param,"="));
if(param=="lineHeight")value.Convert(&fs,'i');
if(param=="scaleW")value.Convert(&tw,'i');
if(param=="scaleH")value.Convert(&th,'i');
}
Size=(float)fs;
}
if(words[0]=="char")
{
int id=0;
int x=0;
int y=0;
int width=0;
int height=0;
int xoffset=0;
int yoffset=0;
int xadvance=0;
for(unsigned int j=1;j<wordsc;j++)
{
param.Clear();
value.Clear();
words[j].Search(value,"\n",words[j].Search(param,"="));
if(param=="id")
value.Convert(&id,'i');
if(param=="x")value.Convert(&x,'i');
if(param=="y")value.Convert(&y,'i');
if(param=="width")value.Convert(&width,'i');
if(param=="height")value.Convert(&height,'i');
if(param=="xoffset")value.Convert(&xoffset,'i');
if(param=="yoffset")value.Convert(&yoffset,'i');
if(param=="xadvance")value.Convert(&xadvance,'i');
}
if(id>=0&&id<256)
{
Desc[id].Width=(float)width;
Desc[id].Height=(float)height;
Desc[id].Xoffset=(float)xoffset;
Desc[id].Yoffset=(float)yoffset;
Desc[id].Advance=(float)xadvance;
Desc[id].Xbegin=(float)x/(float)tw;
Desc[id].Ybegin=(float)y/(float)th;
Desc[id].Xend=((float)x+(float)width)/(float)tw;
Desc[id].Yend=((float)y+(float)height)/(float)th;
}
}
delete[] words;
}
delete[] lines;
return(true);
}

} // XeCore

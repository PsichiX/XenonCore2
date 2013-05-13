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

#include "XeFile.h"
#include <stdio.h>


//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{

XeFile::XeFile()
{
CurrentSize=0;
ReallocBytes=0;
}

bool XeFile::Load(char* fname,unsigned int offset,unsigned int size)
{
FILE* file=0;
fopen_s(&file,fname,"rb");
if(!file)return(false);
if(!size)
{
fseek(file,0,SEEK_END);
size=ftell(file);
rewind(file);
}
if(offset)fseek(file,offset,SEEK_SET);
Buffer.Reserve(size);
CurrentSize=fread(Buffer.Get(),1,size,file);
fclose(file);
return(true);
}

bool XeFile::Save(char* fname,unsigned int offset,unsigned int size)
{
FILE* file=0;
fopen_s(&file,fname,"wb");
if(!file)return(false);
bool status=false;
if(offset)fseek(file,offset,SEEK_SET);
if(size)
status=fwrite(Buffer.Get(),min(CurrentSize,size),1,file)?true:false;
else
status=fwrite(Buffer.Get(),CurrentSize,1,file)?true:false;
fclose(file);
return(status);
}

bool XeFile::Append(char* fname)
{
FILE* file=0;
fopen_s(&file,fname,"ab");
if(!file)return(false);
bool status=fwrite(Buffer.Get(),CurrentSize,1,file)?true:false;
fclose(file);
return(true);
}

unsigned int XeFile::Write(void* buff,unsigned int size)
{
unsigned int curr=Buffer.Current();
unsigned int need=curr+size;
if(ReallocBytes)
{
unsigned int reneed=Buffer.Size();
while(reneed<need)reneed+=ReallocBytes;
Buffer.Resize(reneed);
}
else
Buffer.Resize(need);
Buffer.Seek(curr);
unsigned int w=Buffer.Write((char*)buff,size);
CurrentSize=need;
return(w);
}

unsigned int XeFile::WriteString(char* str,bool nullterm)
{
if(!str)return(0);
if(!nullterm)
return(Write(str,strlen(str)));
else
return(Write(str,strlen(str)+1));
}

unsigned int XeFile::Read(void* buff,unsigned int size)
{
if(!buff||Buffer.Current()>=CurrentSize)return(0);
return(Buffer.Read((char*)buff,min(size,CurrentSize-Buffer.Current())));
}

unsigned int XeFile::ReadString(XeString& str,bool nullterm)
{
if(!Buffer.Size())return(0);
if(!nullterm)
{
str.Copy(&Buffer.Get()[Buffer.Current()],CurrentSize-min(Buffer.Current(),CurrentSize));
Seek(str.Length(),true);
return(str.Length());
}
else
{
str.Copy(&Buffer.Get()[Buffer.Current()],min(strlen(&Buffer.Get()[Buffer.Current()]),CurrentSize-min(Buffer.Current(),CurrentSize)));
Seek(str.Length()+1,true);
return(str.Length()+1);
}
}

void XeFile::Seek(unsigned int offset,bool relative,bool reverse)
{
if(!relative&&!reverse)
Buffer.Seek(offset);
else
if(!relative&&reverse)
Buffer.Seek(CurrentSize-min(offset,CurrentSize));
else
if(relative&&!reverse)
Buffer.Seek(offset,XeBuffer::CUR);
else
if(relative&&reverse)
Buffer.Seek(offset,XeBuffer::RET);
if(Buffer.Current()>=CurrentSize)Buffer.Seek(CurrentSize);
}

bool XeFile::Eof()
{
if(Buffer.Current()>=CurrentSize)return(true);
return(false);
}

unsigned int XeFile::Size(char* fname)
{
if(!fname)return(CurrentSize);
FILE* file=0;
fopen_s(&file,fname,"rb");
if(!file)return(0);
fseek(file,0,SEEK_END);
unsigned int size=ftell(file);
fclose(file);
return(size);
}

unsigned int XeFile::Position()
{
return(Buffer.Current());
}

void* XeFile::Data()
{
return(Buffer.Get());
}

void XeFile::Free()
{
Buffer.Free();
CurrentSize=0;
}

XeBuffer* XeFile::GetBuffer()
{
return(&Buffer);
}

void XeFile::Update()
{
CurrentSize=Buffer.Size();
}

} // XeCore

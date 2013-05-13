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


//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{

template<typename T>
XeArray<T>::XeArray()
{
data=NULL;
position=data;
size=0;
Static=false;
}

template<typename T>
XeArray<T>::XeArray(unsigned int count)
{
data=new T[count];
position=data;
size=count;
Static=false;
}

template<typename T>
XeArray<T>::~XeArray()
{
if(!Static)Free();
}

template<typename T>
bool XeArray<T>::IsEmpty()
{
if(!data||!size)return(true);
return(false);
}

template<typename T>
unsigned int XeArray<T>::Size()
{
return(size);
}

template<typename T>
unsigned int XeArray<T>::SizeBytes()
{
return(size*sizeof(T));
}

template<typename T>
void XeArray<T>::Reserve(unsigned int count)
{
if(!count)
{
if(data)delete[] data;
data=NULL;
position=data;
size=0;
return;
}
if(data)delete[] data;
data=new T[count];
position=data;
size=count;
}

template<typename T>
void XeArray<T>::Resize(unsigned int count,unsigned int offset)
{
if(!count)
{
if(data)delete[] data;
data=NULL;
position=data;
size=0;
return;
}
T* temp=new T[count];
for(unsigned int i=0;i<min(size,count);i++)
temp[i]=data[min(i+offset,count-1)];
if(data)delete[] data;
data=temp;
position=data;
size=count;
}

template<typename T>
void XeArray<T>::Free()
{
if(data)delete[] data;
data=NULL;
position=data;
size=0;
}

template<typename T>
T* XeArray<T>::Get(bool current)
{
if(!current)
return(data);
else
return(position);
}

template<typename T>
unsigned int XeArray<T>::Current()
{
return((unsigned int)position-(unsigned int)data);
}

template<typename T>
bool XeArray<T>::EndOf()
{
if(!data||!size)return(true);
if((unsigned int)position<(unsigned int)data||(unsigned int)position>(unsigned int)data+size*sizeof(T))
return(true);
return(false);
}

template<typename T>
void XeArray<T>::Link(T* buffer,unsigned int count)
{
if(!buffer||!count)return;
data=buffer;
position=data;
size=count;
}

template<typename T>
void XeArray<T>::Unlink(unsigned int count)
{
if(!count)
{
data=NULL;
position=data;
size=0;
}
else
{
data=new T[count];
position=data;
size=count;
}
}

template<typename T>
void XeArray<T>::Seek(unsigned int pos,SeekType type)
{
if(!data||!size)return;
if(type==SET)
position=(T*)((unsigned int)data+min(pos,size)*sizeof(T));
else
if(type==END)
position=(T*)((unsigned int)data+size*sizeof(T)-min(pos,size));
else
if(type==CUR)
{
position+=pos*sizeof(T);
if((unsigned int)position<(unsigned int)data)position=data;
if((unsigned int)position>(unsigned int)data+size*sizeof(T))position=(T*)((unsigned int)data+size*sizeof(T));
}
else
if(type==RET)
{
position-=min(pos*sizeof(T),(unsigned int)(position-data));
if((unsigned int)position<(unsigned int)data)position=data;
if((unsigned int)position>(unsigned int)data+size*sizeof(T))position=(T*)((unsigned int)data+size*sizeof(T));
}
else
if(type==OFF)
position=(T*)((unsigned int)data+min(pos,size*sizeof(T)));
}

template<typename T>
unsigned int XeArray<T>::Read(T* dest,unsigned int count)
{
if(!count||!data||!size)return(0);
unsigned int bytes=min(count*sizeof(T),(unsigned int)data+size*sizeof(T)-(unsigned int)position);
memcpy(dest,position,bytes);
position+=bytes;
return(bytes);
}

template<typename T>
unsigned int XeArray<T>::Write(T* src,unsigned int count)
{
if(!count||!data||!size)return(0);
unsigned int bytes=min(count*sizeof(T),(unsigned int)data+size*sizeof(T)-(unsigned int)position);
memcpy(position,src,bytes);
position+=bytes;
return(bytes);
}

template<typename T>
unsigned int XeArray<T>::ReadBytes(void* dest,unsigned int sizebyte)
{
if(!sizebyte||!data||!size)return(0);
unsigned int bytes=min(sizebyte,(unsigned int)data+size*sizeof(T)-(unsigned int)position);
memcpy(dest,position,bytes);
position+=bytes;
return(bytes);
}

template<typename T>
unsigned int XeArray<T>::WriteBytes(void* src,unsigned int sizebyte)
{
if(!sizebyte||!data||!size)return(0);
unsigned int bytes=min(sizebyte,(unsigned int)data+size*sizeof(T)-(unsigned int)position);
memcpy(position,src,bytes);
position+=bytes;
return(bytes);
}

template<typename T>
T& XeArray<T>::operator[] (unsigned int index)
{
if(!data||!size||index>=size)return(temporary);
return(data[index]);
}

} // XeCore

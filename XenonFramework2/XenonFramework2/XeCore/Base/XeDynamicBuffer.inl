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
XeDynamicBuffer<T>::XeDynamicBuffer()
{
}

template<typename T>
XeDynamicBuffer<T>::~XeDynamicBuffer()
{
Clear();
}

template<typename T>
XeElementPointer<XePair<T*,unsigned int> > XeDynamicBuffer<T>::Add(T* source,unsigned int count)
{
if(count==0)return(Iterator());
XePair<T*,unsigned int> temp;
temp.Key=new T[count];
memcpy(temp.Key,source,count);
temp.Value=count;
return(Buffers.AddPointer(temp));
}

template<typename T>
bool XeDynamicBuffer<T>::Replace(Iterator elm,T* source,unsigned int count)
{
if(elm.IsEmpty())return(false);
if(elm->Key)delete[] elm->Key;
XePair<T*,unsigned int> temp;
temp.Key=new T[count];
memcpy(temp.Key,source,count);
temp.Value=count;
*elm.iPointer()=temp;
return(true);
}

template<typename T>
void XeDynamicBuffer<T>::Erase(Iterator elm)
{
if(elm.IsEmpty())return;
if(elm->Key)delete[] elm->Key;
Buffers.ErasePointer(elm);
}

template<typename T>
unsigned int XeDynamicBuffer<T>::Count()
{
return(Buffers.Size());
}

template<typename T>
unsigned int XeDynamicBuffer<T>::Size()
{
unsigned int size=0;
for(XeElementPointer<XePair<T*,unsigned int> > elm=Buffers.FirstPointer();!elm.IsEmpty();elm.Next())
size+=elm->Value;
return(size);
}

template<typename T>
unsigned int XeDynamicBuffer<T>::Bytesize()
{
return(Size()*sizeof(T));
}

template<typename T>
T* XeDynamicBuffer<T>::Build(unsigned int extra,unsigned int offset)
{
unsigned int size=Size();
unsigned int off=min(extra*sizeof(T),offset);
if(size+extra==0)return(NULL);
T* buff=NULL;
buff=new T[size+extra];
if(!buff)return(NULL);
T* pos=buff+off;
for(XeElementPointer<XePair<T*,unsigned int> > elm=Buffers.FirstPointer();!elm.IsEmpty();elm.Next())
{
memcpy(pos,elm->Key,elm->Value*sizeof(T));
pos+=elm->Value*sizeof(T);
}
return(buff);
}

template<typename T>
XeElementPointer<XePair<T*,unsigned int> > XeDynamicBuffer<T>::First()
{
return(Buffers.FirstPointer());
}

template<typename T>
XeElementPointer<XePair<T*,unsigned int> > XeDynamicBuffer<T>::Last()
{
return(Buffers.LastPointer());
}

template<typename T>
void XeDynamicBuffer<T>::Clear()
{
for(XeElementPointer<XePair<T*,unsigned int> > elm=Buffers.FirstPointer();!elm.IsEmpty();elm.Next())
if(elm->Key)delete[] elm->Key;
Buffers.Clear();
}

} // XeCore

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

#include <stdarg.h>


//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{

template<typename T>
XeStackBuffer<T>::XeStackBuffer()
{
stack=new T[1];
maxsize=1;
count=0;
}

template<typename T>
XeStackBuffer<T>::XeStackBuffer(int size)
{
stack=new T[max(size,1)];
maxsize=max(size,1);
count=0;
}

template<typename T>
XeStackBuffer<T>::~XeStackBuffer()
{
delete stack;
maxsize=0;
count=0;
}

template<typename T>
void XeStackBuffer<T>::Push(T val)
{
if(count>=maxsize)return;
stack[count++]=val;
}

template<typename T>
T XeStackBuffer<T>::Pop()
{
if(count<=0)return(T());
return(stack[count--]);
}

template<typename T>
int XeStackBuffer<T>::Count()
{
return(count);
}

template<typename T>
int XeStackBuffer<T>::MaxSize()
{
return(maxsize);
}

template<typename T>
T* XeStackBuffer<T>::Buffer()
{
return(stack);
}

template<typename T>
void XeStackBuffer<T>::Clear()
{
count=0;
}

template<typename T>
void XeStackBuffer<T>::PushMulti(int size,...)
{
va_list vl;
va_start(vl,size);
for(int i=0;i<size;i++)Push(va_arg(vl,T));
va_end(vl);
}

template<typename T>
void XeStackBuffer<T>::ClearPushMulti(int size,...)
{
count=0;
va_list vl;
va_start(vl,size);
for(int i=0;i<size;i++)Push(va_arg(vl,T));
va_end(vl);
}

} // XeCore

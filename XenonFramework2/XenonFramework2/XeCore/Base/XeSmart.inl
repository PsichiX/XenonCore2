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
XeSmart<T>::XeSmart()
{
Empty=true;
Static=false;
Counter=NULL;
Data=NULL;
RefClone(T());
}

template<typename T>
XeSmart<T>::XeSmart(T* _pointer)
{
Empty=true;
Static=false;
Counter=NULL;
Data=NULL;
RefPointer(_pointer);
}

template<typename T>
XeSmart<T>::XeSmart(const T _clone)
{
Empty=true;
Static=false;
Counter=NULL;
Data=NULL;
RefClone(_clone);
}

template<typename T>
XeSmart<T>::XeSmart(const XeSmart<T>& _smart)
{
Empty=true;
Static=false;
Counter=NULL;
Data=NULL;
RefSmart(_smart);
}

template<typename T>
XeSmart<T>::XeSmart(XeSmart<T>* _smartp)
{
Empty=true;
Static=false;
Counter=NULL;
Data=NULL;
RefSmartP(_smartp);
}

template<typename T>
XeSmart<T>::~XeSmart()
{
Unref();
}

template<typename T>
bool XeSmart<T>::RefPointer(T* _pointer)
{
if(Empty&&Counter==NULL)
{
Empty=false;
#ifdef XE_ALLOC_C
Counter=(unsigned int*)malloc(sizeof(unsigned int));
#else
Counter=new unsigned int[1];
#endif /* XE_ALLOC_C */
*Counter=0;
Data=_pointer;
*Counter+=1;
return(true);
}
if(!Empty&&Counter!=NULL)
if(_pointer!=Data)
{
Unref();
Empty=false;
#ifdef XE_ALLOC_C
Counter=(unsigned int*)malloc(sizeof(unsigned int));
#else
Counter=new unsigned int[1];
#endif /* XE_ALLOC_C */
*Counter=0;
Data=_pointer;
*Counter+=1;
return(true);
}
return(false);
}

template<typename T>
bool XeSmart<T>::RefClone(const T _clone)
{
if(Empty&&Counter==NULL)
{
Empty=false;
#ifdef XE_ALLOC_C
Counter=(unsigned int*)malloc(sizeof(unsigned int));
#else
Counter=new unsigned int[1];
#endif /* XE_ALLOC_C */
*Counter=0;
#ifdef XE_ALLOC_C
Data=(T*)malloc(sizeof(T));
#else
Data=new T[1];
#endif /* XE_ALLOC_C */
*Data=_clone;
*Counter+=1;
return(true);
}
if(!Empty&&Counter!=NULL)
{
Unref();
Empty=false;
#ifdef XE_ALLOC_C
Counter=(unsigned int*)malloc(sizeof(unsigned int));
#else
Counter=new unsigned int[1];
#endif /* XE_ALLOC_C */
*Counter=0;
#ifdef XE_ALLOC_C
Data=(T*)malloc(sizeof(T));
#else
Data=new T[1];
#endif /* XE_ALLOC_C */
*Data=_clone;
*Counter+=1;
return(true);
}
return(false);
}

template<typename T>
bool XeSmart<T>::RefSmart(const XeSmart<T>& _smart)
{
if(Empty&&Counter==NULL)
{
Empty=false;
Counter=_smart.Counter;
Data=_smart.Data;
*Counter+=1;
return(true);
}
if(!Empty&&Counter!=NULL)
if(_smart.Data!=Data)
{
Unref();
Empty=false;
Counter=_smart.Counter;
Data=_smart.Data;
*Counter+=1;
return(true);
}
return(false);
}

template<typename T>
bool XeSmart<T>::RefSmartP(XeSmart<T>* _smartp)
{
if(Empty&&Counter==NULL)
{
Empty=false;
Counter=_smartp->Counter;
Data=_smartp->Data;
*Counter+=1;
return(true);
}
if(!Empty&&Counter!=NULL)
if(_smartp->Data!=Data)
{
Unref();
Empty=false;
Counter=_smartp->Counter;
Data=_smartp->Data;
*Counter+=1;
return(true);
}
return(false);
}

template<typename T>
void XeSmart<T>::Unref()
{
if(!Empty&&Counter!=NULL)
{
*Counter-=1;
if(*Counter==0)
{
#ifdef XE_ALLOC_C
free(Counter);
#else
delete[] Counter;
#endif /* XE_ALLOC_C */
Counter=NULL;
if(!Static)
{
#ifdef XE_ALLOC_C
free(Data);
#else
delete[] Data;
#endif /* XE_ALLOC_C */
Data=NULL;
}
}
}
}

template<typename T>
bool XeSmart<T>::AbstractRef()
{
if(!Empty&&Counter!=NULL)
{
*Counter+=1;
return(true);
}
return(false);
}

template<typename T>
void XeSmart<T>::AbstractUnref()
{
if(!Empty&&Counter!=NULL)
*Counter-=1;
}

template<typename T>
T* XeSmart<T>::Pointer()
{
if(!Empty&&Counter!=NULL)
return(Data);
return(NULL);
}

template<typename T>
T XeSmart<T>::Clone()
{
if(!Empty&&Counter!=NULL)
return(*Data);
T _temp;
return(_temp);
}

template<typename T>
bool XeSmart<T>::IsEmpty()
{
return(Empty);
}

template<typename T>
unsigned int XeSmart<T>::Count()
{
if(!Empty&&Counter!=NULL)
return(*Counter);
return(0);
}

template<typename T>
void XeSmart<T>::operator= (T* _pointer)
{
RefPointer(_pointer);
}

template<typename T>
void XeSmart<T>::operator= (const T _clone)
{
RefClone(_clone);
}

template<typename T>
void XeSmart<T>::operator= (const XeSmart<T>& _smart)
{
RefSmart(_smart);
}

template<typename T>
void XeSmart<T>::operator= (XeSmart<T>* _smartp)
{
RefSmartP(_smartp);
}

template<typename T>
T* XeSmart<T>::operator-> ()
{
return(Pointer());
}

} // XeCore
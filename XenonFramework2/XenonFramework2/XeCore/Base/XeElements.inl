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
XeElementBase<T>::XeElementBase()
{
empty=true;
original=true;
parent=0;
prev=0;
next=0;
container=0;
}

template<typename T>
XeElementBase<T>::~XeElementBase()
{
}

template<typename T>
T* XeElementPointer<T>::operator-> ()
{
return(iPointer());
}

template<typename T>
T& XeElementPointer<T>::operator() ()
{
return(*iPointer());
}

template<typename T>
bool XeElementPointer<T>::operator== (XeElementPointer<T>& elm)
{
if(iPointer()==elm.iPointer())
return(true);
return(false);
}

template<typename T>
bool XeElementPointer<T>::operator!= (XeElementPointer<T>& elm)
{
if(iPointer()!=elm.iPointer())
return(true);
return(false);
}

template<typename T>
XeElementPointer<T> XeElementPointer<T>::operator++ ()
{
this->Next();
return(*this);
}

template<typename T>
XeElementPointer<T> XeElementPointer<T>::operator-- ()
{
this->Prev();
return(*this);
}

template<typename T>
XeElementPointer<T> XeElementPointer<T>::operator++ (int)
{
XeElementPointer<T> temp=*this;
this->Next();
return(temp);
}

template<typename T>
XeElementPointer<T> XeElementPointer<T>::operator-- (int)
{
XeElementPointer<T> temp=*this;
this->Prev();
return(temp);
}

template<typename T>
XeElementPointer<T>::XeElementPointer()
{
empty=true;
original=false;
parent=0;
}

template<typename T>
T XeElementPointer<T>::iClone()
{
if(!empty)
if(parent!=0)
return(parent->data);
return(T());
}

template<typename T>
T* XeElementPointer<T>::iPointer()
{
if(!empty)
if(parent!=0)
return(&parent->data);
return(0);
}

template<typename T>
void XeElementPointer<T>::Next(bool cycle)
{
if(parent!=0)
{
XeElementPointer<T> temp;
if(parent->next!=0)
{
temp.empty=parent->next->empty;
temp.parent=parent->next;
}
else
if(cycle)temp=parent->container->FirstPointer();
empty=temp.empty;
parent=temp.parent;
}
}

template<typename T>
void XeElementPointer<T>::Prev(bool cycle)
{
if(parent!=0)
{
XeElementPointer<T> temp;
if(parent->prev!=0)
{
temp.empty=parent->prev->empty;
temp.parent=parent->prev;
}
else
if(cycle)temp=parent->container->LastPointer();
empty=temp.empty;
parent=temp.parent;
}
}

template<typename T>
bool XeElementPointer<T>::IsEmpty()
{
if(empty||!parent)
return(true);
return(false);
}

template<typename T>
void XeElementPointer<T>::RefPointer(XeElementPointer<T>& elm)
{
if(elm.parent!=0)
{
empty=elm.parent->empty;
parent=elm.parent->parent;
}
}

template<typename T>
void XeElementPointer<T>::Unref()
{
empty=true;
parent=0;
}

template<typename T>
XeElements<T>::XeElements()
{
first=0;
last=0;
size=0;
Static=false;
AddingByCloning=false;
}

template<typename T>
XeElements<T>::~XeElements()
{
if(!Static)Clear();
}

template<typename T>
unsigned int XeElements<T>::Size()
{
return(size);
}

template<typename T>
void XeElements<T>::Clear()
{
if(size>0)
{
XeElementBase<T>* temp=first;
XeElementBase<T>* _temp;
while(temp!=0)
{
_temp=temp;
temp=temp->next;
#ifdef XE_ALLOC_C
free(_temp);
#else
delete[] _temp;
#endif /* XE_ALLOC_C */
}
first=0;
last=0;
size=0;
}
}

template<typename T>
void XeElements<T>::Sort(int(*foo)(T*,T*))
{
if(foo)
{
bool change=true;
XeElementPointer<T> iter;
XeElementPointer<T> temp;
while(change)
{
change=false;
iter=FirstPointer();
temp=iter;
temp.Next();
while(!iter.IsEmpty())
{
if(!temp.IsEmpty())
if(foo(iter.iPointer(),temp.iPointer())<0)
{
T toswap;
toswap=iter.parent->data;
iter.parent->data=temp.parent->data;
temp.parent->data=toswap;
change=true;
}
iter.Next();
temp.Next();
}
iter=LastPointer();
temp=iter;
temp.Prev();
if(change)
while(!iter.IsEmpty())
{
if(!temp.IsEmpty())
if(foo(iter.iPointer(),temp.iPointer())>0)
{
T toswap;
toswap=iter.parent->data;
iter.parent->data=temp.parent->data;
temp.parent->data=toswap;
change=true;
}
iter.Prev();
temp.Prev();
}
}
}
}

template<typename T>
bool XeElements<T>::Swap(XeElementPointer<T> elm1,XeElementPointer<T> elm2)
{
if(elm1.IsEmpty()||elm2.IsEmpty())return(false);
T toswap;
XeElements<T> *cont1=0;
XeElements<T> *cont2=0;
cont1=elm1.parent->container;
cont2=elm2.parent->container;
toswap=elm1.parent->data;
elm1.parent->data=elm2.parent->data;
elm2.parent->data=toswap;
elm1.parent->container=cont2;
elm2.parent->container=cont1;
return(true);
}

template<typename T>
bool XeElements<T>::Capture(XeElementPointer<T> elm)
{
if(elm.IsEmpty())return(false);
if(elm.parent->container==this)return(false);
XeElementBase<T>* _elm=elm.parent;
XeElementBase<T>* _prev=_elm->prev;
XeElementBase<T>* _next=_elm->next;
XeElements<T>* _con=_elm->container;
if(_prev)_prev->next=_next;
if(_next)_next->prev=_prev;
if(_con->first==_elm)(_next)?_con->first=_next:_con->first=0;
if(_con->last==_elm)(_prev)?_con->last=_prev:_con->last=0;
_elm->next=0;
_elm->prev=last;
if(last)last->next=_elm;
last=_elm;
if(!first)first=_elm;
size++;
if(_elm->container)_elm->container->size--;
_elm->container=this;
return(true);
}

template<typename T>
XeElementPointer<T> XeElements<T>::FirstPointer()
{
XeElementPointer<T> temp;
if(first!=0)
{
temp.empty=first->empty;
temp.parent=first;
}
return(temp);
}

template<typename T>
XeElementPointer<T> XeElements<T>::LastPointer()
{
XeElementPointer<T> temp;
if(last!=0)
{
temp.empty=last->empty;
temp.parent=last;
}
return(temp);
}

template<typename T>
XeElementPointer<T> XeElements<T>::AddPointer(const T& value)
{
if(size==0)
{
size++;
XeElementBase<T>* _first=first;
XeElementBase<T>* _last=last;
XeElementBase<T> temp;
temp.data=(T)value;
temp.empty=false;
temp.original=true;
temp.parent=0;
temp.next=0;
temp.prev=0;
#ifdef XE_ALLOC_C
first=(XeElementBase<T>*)malloc(sizeof(XeElementBase<T>));
#else
first=new XeElementBase<T>[1];
#endif /* XE_ALLOC_C */
last=first;
XeElementPointer<T> _temp;
if(last==0)
{
first=_first;
last=_last;
return(_temp);
}
if(AddingByCloning)
memcpy(last,&temp,sizeof(XeElementBase<T>));
else
*last=temp;
_temp.empty=false;
_temp.original=false;
_temp.parent=last;
_temp.parent->container=this;
return(_temp);
}
else
{
size++;
XeElementBase<T>* _first=first;
XeElementBase<T>* _last=last;
XeElementBase<T> temp;
temp.data=(T)value;
temp.empty=false;
temp.original=true;
temp.parent=0;
temp.next=0;
temp.prev=last;
#ifdef XE_ALLOC_C
last->next=(XeElementBase<T>*)malloc(sizeof(XeElementBase<T>));
#else
last->next=new XeElementBase<T>[1];
#endif /* XE_ALLOC_C */
last=last->next;
XeElementPointer<T> _temp;
if(last==0)
{
first=_first;
last=_last;
return(_temp);
}
*last=temp;
_temp.empty=false;
_temp.original=false;
_temp.parent=last;
_temp.parent->container=this;
return(_temp);
}
}

template<typename T>
XeElementPointer<T> XeElements<T>::InsertPointer(const T& value,XeElementPointer<T> elm)
{
if(!elm.IsEmpty())
if(elm.parent->container!=this)
return(XeElementPointer<T>());
if(size==0)
{
size++;
XeElementBase<T>* _first=first;
XeElementBase<T>* _last=last;
XeElementBase<T> temp;
temp.data=value;
temp.empty=false;
temp.original=true;
temp.parent=0;
temp.next=0;
temp.prev=0;
#ifdef XE_ALLOC_C
first=(XeElementBase<T>*)malloc(sizeof(XeElementBase<T>));
#else
first=new XeElementBase<T>[1];
#endif /* XE_ALLOC_C */
last=first;
XeElementPointer<T> _temp;
if(last==0)
{
first=_first;
last=_last;
return(_temp);
}
if(AddingByCloning)
memcpy(last,&temp,sizeof(XeElementBase<T>));
else
*last=temp;
_temp.empty=false;
_temp.original=false;
_temp.parent=last;
_temp.parent->container=this;
return(_temp);
}
else
{
size++;
XeElementBase<T>* _first=first;
XeElementBase<T>* _last=last;
XeElementBase<T> temp;
temp.data=value;
temp.empty=false;
temp.original=true;
temp.parent=0;
XeElementBase<T>* _base;
#ifdef XE_ALLOC_C
_base=(XeElementBase<T>*)malloc(sizeof(XeElementBase<T>));
#else
_base=new XeElementBase<T>[1];
#endif /* XE_ALLOC_C */
XeElementPointer<T> _temp;
if(_base==0)
{
first=_first;
last=_last;
return(_temp);
}
*_base=temp;
if(elm.parent==last)
{
temp.next=0;
temp.prev=last;
last->next=_base;
last=_base;
}
if(elm.IsEmpty())
{
temp.next=first;
temp.prev=0;
first->prev=_base;
first=_base;
}
if(elm.parent!=last&&!elm.IsEmpty())
{
temp.next=elm.parent->next;
temp.prev=elm.parent;
elm.parent->next=_base;
}
_temp.empty=false;
_temp.original=false;
_temp.parent=_base;
_temp.parent->container=this;
return(_temp);
}
}

template<typename T>
void XeElements<T>::ErasePointer(XeElementPointer<T>& elm)
{
if(size>0)
if(!elm.empty)
if(elm.parent!=0)
{
size--;
XeElementBase<T>* temp=elm.parent;
XeElementBase<T>* _prev=temp->prev;
XeElementBase<T>* _next=temp->next;
if(_prev!=0)_prev->next=_next;
if(_prev==0)first=_next;
if(_next!=0)_next->prev=_prev;
if(_next==0)last=_prev;
#ifdef XE_ALLOC_C
free(temp);
#else
delete[] temp;
#endif /* XE_ALLOC_C */
}
}

} // XeCore
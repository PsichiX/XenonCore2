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
XeNode<T>::XeNode()
{
Parent=NULL;
}

template<typename T>
XeNode<T>::XeNode(const T& val)
{
Data=val;
Parent=NULL;
}

template<typename T>
XeNode<T>::~XeNode()
{
Free();
}

template<typename T>
T XeNode<T>::Clone()
{
return(Data);
}

template<typename T>
T* XeNode<T>::Pointer()
{
return(&Data);
}

template<typename T>
XeNode<T>* XeNode<T>::GetParent()
{
return(Parent);
}

template<typename T>
XeElementPointer<XeNode<T> > XeNode<T>::FirstChild()
{
return(Childs.FirstPointer());
}

template<typename T>
XeElementPointer<XeNode<T> > XeNode<T>::LastChild()
{
return(Childs.LastPointer());
}

template<typename T>
XeElementPointer<XeNode<T> > XeNode<T>::AddChild(const T& value)
{
Node elm=Childs.AddPointer(XeNode<T>(value));
if(!elm.IsEmpty())elm->Parent=this;
return(elm);
}

template<typename T>
void XeNode<T>::RemoveChild(Node child)
{
if(child->Parent!=this)return;
child->Free();
Childs.ErasePointer(child);
}

template<typename T>
void XeNode<T>::RemoveChildPtr(XeNode<T>* child)
{
if(!child)return;
for(Node elm=Childs.FirstPointer();!elm.IsEmpty();elm.Next())
if(elm.iPointer()==child)
{
if(elm->Parent!=this)break;
elm->Free();
Childs.ErasePointer(elm);
break;
}
}

template<typename T>
void XeNode<T>::RemoveSelf()
{
if(!Parent)return;
Parent->RemoveChildPtr(this);
}

template<typename T>
unsigned int XeNode<T>::Count()
{
return(Childs.Size());
}

template<typename T>
void XeNode<T>::Free()
{
XeElementPointer<XeNode<T> > elm=Childs.FirstPointer();
while(!elm.IsEmpty())
{
elm->Free();
Childs.ErasePointer(elm);
elm=Childs.FirstPointer();
}
}

template<typename T>
bool XeNode<T>::CaptureChild(Node child)
{

XeNode<T>* par=Parent;
while(par)
{
if(par==child.iPointer())
{
XeNode<T>* tpar=child->Parent;
if(!tpar)return(false);
while(child->Count())
{
Node tn=child->FirstChild();
if(!tpar->Childs.Capture(tn))return(false);
if(!tn.IsEmpty())tn->Parent=tpar;
}
if(Childs.Capture(child))
{
if(!child.IsEmpty())child->Parent=this;
return(true);
}
}
par=par->Parent;
}

if(Childs.Capture(child))
{
if(!child.IsEmpty())child->Parent=this;
return(true);
}
return(false);
}

template<typename T>
bool XeNode<T>::CaptureChildPtr(XeNode<T>* child)
{
if(!child)return(false);
if(!child->GetParent())return(false);
for(Node elm=child->GetParent()->FirstChild();!elm.IsEmpty();elm.Next())
if(elm.iPointer()==child)
{

XeNode<T>* par=Parent;
while(par)
{
if(par==child)
{
XeNode<T>* tpar=child->Parent;
if(!tpar)return(false);
while(child->Count())
{
Node tn=child->FirstChild();
if(!tpar->Childs.Capture(tn))return(false);
if(!tn.IsEmpty())tn->Parent=tpar;
}
if(Childs.Capture(elm))
{
if(!elm.IsEmpty())elm->Parent=this;
return(true);
}
}
par=par->Parent;
}
if(Childs.Capture(elm))
{
if(!elm.IsEmpty())child->Parent=this;
return(true);
}
}
return(false);
}

template<typename T>
void XeNode<T>::SortChilds(int(*foo)(XeNode<T>*,XeNode<T>*))
{
Childs.Sort(foo);
}

template<typename T>
T* XeNode<T>::operator-> ()
{
return(Pointer());
}

} // XeCore

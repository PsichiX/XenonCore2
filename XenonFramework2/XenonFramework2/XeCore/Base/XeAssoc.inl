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

template <typename TK,typename TV>
XeElementPointer< XePair<TK,TV> > XeAssoc<TK,TV>::FirstPointer()
{
return(Array.FirstPointer());
}

template <typename TK,typename TV>
void XeAssoc<TK,TV>::Clear()
{
Array.Clear();
}

template <typename TK,typename TV>
bool XeAssoc<TK,TV>::Erase(TK key)
{
XeElementPointer< XePair<TK,TV> > elm;
for(elm=Array.FirstPointer();!elm.IsEmpty();elm.Next())
if(elm.iPointer()->Key==key)
{
Array.ErasePointer(elm);
return(true);
}
return(false);
}

template <typename TK,typename TV>
bool XeAssoc<TK,TV>::Change(TK oldkey,TK newkey)
{
XeElementPointer< XePair<TK,TV> > elm;
for(elm=Array.FirstPointer();!elm.IsEmpty();elm.Next())
if(elm.iPointer()->Key==oldkey)
{
elm.iPointer()->Key=newkey;
return(true);
}
return(false);
}

template <typename TK,typename TV>
unsigned int XeAssoc<TK,TV>::Size()
{
return(Array.Size());
}

template <typename TK,typename TV>
TV& XeAssoc<TK,TV>::operator[] (TK key)
{
XeElementPointer< XePair<TK,TV> > elm;
for(elm=Array.FirstPointer();!elm.IsEmpty();elm.Next())
if(elm.iPointer()->Key==key)
return(elm.iPointer()->Value);
XePair<TK,TV> pair;
pair.Key=key;
elm=Array.AddPointer(pair);
return(elm.iPointer()->Value);
}

template <typename TK,typename TV>
bool XeAssoc<TK,TV>::Exists(TK key)
{
XeElementPointer< XePair<TK,TV> > elm;
for(elm=Array.FirstPointer();!elm.IsEmpty();elm.Next())
if(elm.iPointer()->Key==key)
return(true);
return(false);
}

} // XeCore

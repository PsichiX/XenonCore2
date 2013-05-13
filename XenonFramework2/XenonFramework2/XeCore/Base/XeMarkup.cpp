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

#include "XeMarkup.h"


//! \namespace XeCore Przestrzen nazw XenoN Core
namespace XeCore
{

XeMarkup::Tag::Tag()
{
}

void XeMarkup::TagsToString(XeString& result,Ptag tag,int level)
{
if(!tag)return;
XeString temp;
if(tag->Pointer()->Name.Length())
{
for(int _counter_=0;_counter_<level;_counter_++)temp<<"\t";
temp<<"<"<<tag->Pointer()->Name.Get();
if(tag->Pointer()->Attribs.Size())
for(XeElementPointer< XePair<XeString,XeString> > elm=tag->Pointer()->Attribs.FirstPointer();!elm.IsEmpty();elm.Next())
if(elm->Key.Length())
temp<<" "<<elm->Key.Get()<<"=\""<<elm->Value.Get()<<"\"";
if(!tag->Count())
{
temp<<" />\r\n";
result<<temp.Get();
temp.Clear();
}
else
{
temp<<">\r\n";
result<<temp.Get();
temp.Clear();
for(XeNode<Tag>::Node elm=tag->FirstChild();!elm.IsEmpty();elm.Next())
TagsToString(result,elm.iPointer(),level+1);
for(int _counter_=0;_counter_<level;_counter_++)temp<<"\t";
temp<<"</"<<tag->Pointer()->Name.Get()<<">\r\n";
result<<temp.Get();
temp.Clear();
}
}
else
{
if(tag->Pointer()->Text.Length())
{
temp.Clear();
for(int _counter_=0;_counter_<level;_counter_++)temp<<"\t";
temp<<tag->Pointer()->Text.Get()<<"\r\n";
result<<temp.Get();
temp.Clear();
}
}
}

XeMarkup::XeMarkup()
{
}

XeMarkup::~XeMarkup()
{
Free();
}

bool XeMarkup::Parse(char* buff,unsigned int size,char* prepost)
{
if(!buff||!size)return(false);
XeString pp=prepost;
unsigned int ppl=pp.Length();
XeString src;
src.Copy(buff,size);
XeElements<XePair<XeString,int> > parts;
XeString temp;
unsigned int srclen=src.Length();
unsigned int pos=0;
pos=src.Search(temp,"<",pos);
XePair<XeString,int> pair;
while(pos)
{
XeString pref;
pref.Copy(src.Get(pos),8);
if(pos+8+3<=srclen&&pref=="![CDATA[")
{
pos+=8;
temp.Clear();
pair.Key.Clear();
pos=src.Search(temp,"]]>",pos);
pair.Key=temp;
pair.Value=2;
if(pair.Key.Length())parts.AddPointer(pair);
}
else
{
temp.Clear();
pair.Key.Clear();
pos=src.Search(temp,">",pos);
pair.Key=temp;
pair.Value=0;
if(pair.Key.Length())parts.AddPointer(pair);
}
temp.Clear();
pair.Key.Clear();
pos=src.Search(temp,"<",pos);
if(temp.Length())
{
if(prepost)
{
char t;
bool doit;
unsigned int pre=0;
doit=true;
for(unsigned int i=0;i<temp.Length()&&doit;i++)
{
t=temp.Index(i);
for(unsigned int j=0;j<ppl&&doit;j++)
{
if(t!=pp.Index(j))
doit=false;
else
pre++;
}
}
unsigned int post=0;
doit=true;
for(unsigned int i=0;i<temp.Length()&&doit;i++)
{
t=temp.Index(i,true);
for(unsigned int j=0;j<ppl&&doit;j++)
{
if(t!=pp.Index(j))
doit=false;
else
post++;
}
}
if(pre+post<temp.Length())
pair.Key.Copy(temp.Get(pre),temp.Length()-pre-post);
}
else
pair.Key=temp;
pair.Value=1;
if(pair.Key.Length())parts.AddPointer(pair);
}
}
src.Clear();
XeNode<Tag>* parent=0;
for(XeElementPointer<XePair<XeString,int> > part=parts.FirstPointer();!part.IsEmpty();part.Next())
{
if(!parent)parent=&Tags;
if(part->Value==0)
{
if(part->Key.Length()>=5&&part->Key.Index(0)=='!'&&part->Key.Index(1)=='-'&&part->Key.Index(2)=='-'&&part->Key.Index(0,true)=='-'&&part->Key.Index(1,true)=='-')
continue;
else
if(part->Key.Index(0)!='/')
{
XeNode<Tag>::Node tag=parent->AddChild(Tag());
XeString prop;
if(part->Key.Length()>=2&&part->Key.Index(0)=='?'&&part->Key.Index(0,true)=='?')
prop.Copy(part->Key.Get(1),part->Key.Length()-2);
else
if(part->Key.Length()>=1&&part->Key.Index(0,true)=='/')
prop.Copy(part->Key.Get(),part->Key.Length()-1);
else
{
parent=tag.iPointer();
prop=part->Key;
}
unsigned int argc=0;
XeString* args=prop.Explode(" \t\r\n",argc,"\"");
if(argc&&args)
{
tag->Pointer()->Name=args[0];
for(unsigned int i=1;i<argc;i++)
{
XePair<XeString,XeString> pair;
XeString attr;
unsigned int p=args[i].Search(pair.Key,"=");
args[i].Search(attr,"\n",p);
if(attr.Length()>=2&&attr.Index(0)=='"'&&attr.Index(0,true)=='"')
pair.Value.Copy(attr.Get(1),attr.Length()-2);
else
pair.Value=attr;
if(pair.Key.Length())tag->Pointer()->Attribs.AddPointer(pair);
}
delete[] args;
}
else
{
parent=parent->GetParent();
parent->RemoveChild(tag);
}
}
else
parent=parent->GetParent();
}
else
if(part->Value==1)
{
XeNode<Tag>::Node tag=parent->AddChild(Tag());
tag->Pointer()->Text=part->Key;
}
else
if(part->Value==2)
{
XeNode<Tag>::Node tag=parent->AddChild(Tag());
tag->Pointer()->Name="<CDATA>";
tag->Pointer()->Text=part->Key;
}
}
parts.Clear();
return(true);
}

bool XeMarkup::Make(XeBuffer& buff)
{
if(!Tags.Count())return(false);
XeString result;
for(XeNode<Tag>::Node elm=Tags.FirstChild();!elm.IsEmpty();elm.Next())
TagsToString(result,elm.iPointer(),0);
buff.Reserve(result.Length());
buff.Write(result,result.Length());
result.Clear();
return(true);
}

void XeMarkup::Free()
{
Tags.Free();
}

XeMarkup::Etag XeMarkup::operator() (char* path,Enum action,Ptag tag)
{
XeNode<Tag>::Node res;
XeNode<Tag>::Node elm;
XeString temp=path;
XeString word;
if(!tag)tag=&Tags;
unsigned int pos=temp.Search(word,"/");
bool optnew=false;
bool optlast=false;
unsigned int optid=0;
if(word.Find(0,"#"))
{
temp.Clear();
XeString option;
unsigned int op=word.Search(temp,"#");
while(op)
{
op=word.Search(option,"#",op);
if(option=="new")optnew=true;
if(option=="last")optlast=true;
if(option=="prev")if(optid)optid--;
if(option=="next")optid++;
if(option.Find(0,":"))
{
XeString subopt;
XeString subval;
option.Search(subval,":",option.Search(subopt,":"));
if(subopt=="id")subval.Convert(&optid,'d');
}
}
word=temp;
}
Ptag par=tag;
if(word==".")
{
if(tag->GetParent())
tag=tag->GetParent();
else
tag=&Tags;
}
if(word=="..")
{
if(tag->GetParent())
{
if(tag->GetParent()->GetParent())
tag=tag->GetParent()->GetParent();
else
tag=0;
}
else
tag=0;
}
if(!tag)return(Etag());
Etag start;
if(word!=".")
start=(!optlast)?(tag->FirstChild()):(tag->LastChild());
else
{
for(Etag elm=tag->FirstChild();!elm.IsEmpty();elm.Next())
if(elm.iPointer()==par)
{
start=elm;
break;
}
}
if(optnew)goto __marknew__;
for(elm=start;!elm.IsEmpty();(!optlast)?(elm.Next()):(elm.Prev()))
if((word!="."&&word!="..")?(elm->Pointer()->Name==word):(true))
{
if(optid)
{
optid--;
continue;
}
if(pos)
return((*this)(&path[pos],action,elm.iPointer()));
else
{
if(action!=DESTROY)
return(elm);
else
{
tag->RemoveChild(elm);
return(Etag());
}
}
}
__marknew__:
if(action==CREATE)
{
res=tag->AddChild(Tag());
if(res.IsEmpty())return(XeNode<Tag>::Node());
res->Pointer()->Name=word;
if(pos)
return((*this)(&path[pos],action,res.iPointer()));
else
return(res);
}
return(XeNode<Tag>::Node());
}

XeMarkup::Attrib XeMarkup::operator() (char* path,char* name,Enum action,Ptag tag)
{
XeNode<Tag>::Node res=(*this)(path,action,tag);
if(res.IsEmpty())return(Attrib());
for(Attrib elm=res->Pointer()->Attribs.FirstPointer();!elm.IsEmpty();elm.Next())
if(elm->Key==name)
return(elm);
Attrib atr=res->Pointer()->Attribs.AddPointer(XePair<XeString,XeString>());
if(atr.IsEmpty())return(Attrib());
atr->Key=name;
return(atr);
}

} // XeCore

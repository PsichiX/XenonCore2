#include "ActorManager.h"

RTTI_CLASS_DERIVATIONS(	ActorManager,
						RTTI_DERIVATIONS_END
						);

ActorManager::ActorManager():
RTTI_CLASS_DEFINE( ActorManager )
{
}

ActorManager::~ActorManager()
{
	removeAll();
}

void ActorManager::removeAll()
{
	XeCore::XeElementPointer< Pair > e = access().FirstPointer();
	while( !e.IsEmpty() )
	{
		if( e().value->getRemoveable() )
			remove( e().key );
		else
			detach( e().key );
		e = access().FirstPointer();
	}
}

void ActorManager::update()
{
	for( XeCore::XeElementPointer< Pair > e = access().FirstPointer(); !e.IsEmpty(); e.Next() )
		e().value->update();
	for( XeCore::XeElementPointer< Pair > e = access().FirstPointer(); !e.IsEmpty(); e.Next() )
		if( e().value->getRemoved() )
		{
			XeCore::XeElementPointer< Pair > t = e;
			e.Next();
			remove( t().key );
		}
}

void ActorManager::input()
{
	for( XeCore::XeElementPointer< Pair > e = access().FirstPointer(); !e.IsEmpty(); e.Next() )
		e().value->input();
}

void ActorManager::render()
{
	for( XeCore::XeElementPointer< Pair > e = access().FirstPointer(); !e.IsEmpty(); e.Next() )
		e().value->render();
}

void ActorManager::getInfoList( XeCore::XeString& out )
{
	for( XeCore::XeElementPointer< Pair > e = access().FirstPointer(); !e.IsEmpty(); e.Next() )
	{
		XeCore::XeString n, t, a;
		t = (char*)e->value->getName();
		findName( e->value, n );
		a.Format( "0x%p", e() );
		out << a << " <" << t << ">: " << n << "\n";
	}
}

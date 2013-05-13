#include "SceneManager.h"

RTTI_CLASS_DERIVATIONS(	SceneManager,
						RTTI_DERIVATIONS_END
						);

SceneManager::SceneManager():
RTTI_CLASS_DEFINE( SceneManager )
{
}

SceneManager::~SceneManager()
{
	XeCore::XeElementPointer< Pair > e = access().FirstPointer();
	while( !e.IsEmpty() )
	{
		remove( e().key );
		e = access().FirstPointer();
	}
}

void SceneManager::update()
{
	access().Sort( sort );
	for( XeCore::XeElementPointer< Pair > e = access().FirstPointer(); !e.IsEmpty(); e.Next() )
		if( e().value->isRenderable() )
			e().value->update();
}

void SceneManager::render()
{
	for( XeCore::XeElementPointer< Pair > e = access().FirstPointer(); !e.IsEmpty(); e.Next() )
		if( e().value->isRenderable() )
			e().value->render();
}

void SceneManager::getInfoList( XeCore::XeString& out )
{
	for( XeCore::XeElementPointer< Pair > e = access().FirstPointer(); !e.IsEmpty(); e.Next() )
	{
		XeCore::XeString n, a;
		n = e().key;
		a.Format( "0x%p", e().value );
		out << a << " <" << const_cast<char*>(e().value->getName()) << ">: " << n << "; is renderable: " << ( e().value->isRenderable() ? "true" : "false" ) << "; items: " << e().value->access().Size() << "\n";
	}
}

int SceneManager::sort( INamedItemsManager< NameID, IScene >::Pair* a, INamedItemsManager< NameID, IScene >::Pair* b )
{
	float ao = a->value->getOrder();
	float bo = b->value->getOrder();
	if( ao > bo )
		return( 1 );
	else
	if( ao == bo )
		return( 0 );
	else
		return( -1 );
}

#include "CanvasManager.h"

RTTI_CLASS_DERIVATIONS(	CanvasManager,
						RTTI_DERIVATIONS_END
						);

CanvasManager::CanvasManager():
RTTI_CLASS_DEFINE( CanvasManager )
{
}

CanvasManager::~CanvasManager()
{
	XeCore::XeElementPointer< Pair > e = access().FirstPointer();
	while( !e.IsEmpty() )
	{
		remove( e().key );
		e = access().FirstPointer();
	}
}
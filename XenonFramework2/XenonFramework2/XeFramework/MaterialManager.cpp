#include "MaterialManager.h"

RTTI_CLASS_DERIVATIONS(	MaterialManager,
						RTTI_DERIVATIONS_END
						);

MaterialManager::MaterialManager():
RTTI_CLASS_DEFINE( MaterialManager )
{
}

MaterialManager::~MaterialManager()
{
	XeCore::XeElementPointer< Pair > e = access().FirstPointer();
	while( !e.IsEmpty() )
	{
		remove( e().key );
		e = access().FirstPointer();
	}
}
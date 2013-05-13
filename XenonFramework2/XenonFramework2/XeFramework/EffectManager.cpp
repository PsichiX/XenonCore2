#include "EffectManager.h"

RTTI_CLASS_DERIVATIONS(	EffectManager,
						RTTI_DERIVATIONS_END
						);

EffectManager::EffectManager():
RTTI_CLASS_DEFINE( EffectManager )
{
}

EffectManager::~EffectManager()
{
	XeCore::XeElementPointer< Pair > e = access().FirstPointer();
	while( !e.IsEmpty() )
	{
		remove( e().key );
		e = access().FirstPointer();
	}
}
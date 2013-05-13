#include "TextureManager.h"

RTTI_CLASS_DERIVATIONS(	TextureManager,
						RTTI_DERIVATIONS_END
						);

TextureManager::TextureManager():
RTTI_CLASS_DEFINE( TextureManager )
{
}

TextureManager::~TextureManager()
{
	XeCore::XeElementPointer< Pair > e = access().FirstPointer();
	while( !e.IsEmpty() )
	{
		remove( e().key );
		e = access().FirstPointer();
	}
}
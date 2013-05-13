#include "FontManager.h"

RTTI_CLASS_DERIVATIONS(	FontManager,
						RTTI_DERIVATIONS_END
						);

FontManager::FontManager():
RTTI_CLASS_DEFINE( FontManager )
{
}

FontManager::~FontManager()
{
	XeCore::XeElementPointer< Pair > e = access().FirstPointer();
	while( !e.IsEmpty() )
	{
		remove( e().key );
		e = access().FirstPointer();
	}
}
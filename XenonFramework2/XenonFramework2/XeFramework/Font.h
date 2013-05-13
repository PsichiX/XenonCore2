#pragma once

#include "IRtti.h"
#include "../XeCore/Base/XeFontmap.h"
#include "Engine.h"
#include "Asset.h"

class Font : public virtual IRtti, public Asset, public virtual MemoryManager::Manageable
{
	RTTI_CLASS_DECLARE( Font );

public:
	enum Align
	{
		aLeft,
		aCenter,
		aRight,
		aTop,
		aMiddle,
		aBottom,
		aCount
	};

											Font();
											~Font();
	bool									load( const char* fname );
	bool									loadFromMemory( void* data, unsigned int size );
	bool									isValid();
	void									free();
	bool									getCharacter( int id, XeCore::XeHalfVector& coordsB, XeCore::XeHalfVector& coordsE, XeCore::XeHalfVector& offset, XeCore::XeHalfVector& size, float& advance );
	float									getSize();

	static Asset*							onLoad( AssetManager* manager, XeCore::XeString& name, Params& params, bool keepAlways );
	virtual void							onUnload();

private:
	XeCore::XeFontmap*						m_map;
};
#pragma once

#include "IRtti.h"
#include "Engine.h"
#include "Asset.h"

class Texture : public virtual IRtti, public Asset, public virtual MemoryManager::Manageable
{
	RTTI_CLASS_DECLARE( Texture );

public:
	enum Type
	{
		t2d,
		tData,
		tCount
	};

											Texture();
											Texture( const XeCore::Photon::XeElmTexture& texture );
											~Texture();
	bool									load( const char* fname );
	bool									loadImage( const char* fname );
	bool									loadAppIcon( const char* fname, int index, int width, int height );
	bool									empty( int w, int h );
	bool									data( int w, int h, void* data = 0 );
	bool									free();
	bool									filtering( int level );
	void									repeating( bool mode );
	int										getWidth();
	int										getHeight();
	int										getRealWidth();
	int										getRealHeight();
	Type									getType();
	bool									activate();
	const XeCore::Photon::XeElmTexture&		getTexture();
	bool									isAttached();
	void									unactivate();

	static Asset*							onLoad( AssetManager* manager, XeCore::XeString& name, Params& params, bool keepAlways );
	virtual void							onUnload();

private:
	XeCore::Photon::XeElmTexture			m_texture;
	Type									m_type;
	bool									m_attached;
};
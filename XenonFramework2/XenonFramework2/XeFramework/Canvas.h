#pragma once

#include "IRtti.h"
#include "Engine.h"
#include "Asset.h"

class Canvas : public virtual IRtti, public Asset, public virtual MemoryManager::Manageable
{
	RTTI_CLASS_DECLARE( Canvas );

public:
	enum Type
	{
		t2d,
		tData,
		tCount
	};

												Canvas( int w, int h, Type t = t2d );
												~Canvas();
	int											getWidth();
	int											getHeight();
	Type										getType();
	bool										activate();
	bool										unactivate();
	bool										activateTexture();
	bool										unactivateTexture();
	bool										activateTextureDepth();
	bool										unactivateTextureDepth();
	const XeCore::Photon::XeElmTexture&			getTexture();
	const XeCore::Photon::XeElmTexture&			getTextureDepth();
	const XeCore::Photon::XeElmFrameBuffer&		getFBO();
	void										setClearOnActivate( bool mode );
	bool										getClearOnActivate();
	void										setDepthMode( bool m );
	bool										getDepthMode();
	bool										filtering( int level );
	void										repeating( bool mode );
	bool										filteringDepth( int level );
	void										repeatingDepth( bool mode );

	static Asset*								onLoad( AssetManager* manager, XeCore::XeString& name, Params& params, bool keepAlways );
	virtual void								onUnload();

private:
	XeCore::Photon::XeElmFrameBuffer			m_fbo;
	XeCore::Photon::XeElmTexture				m_texture;
	XeCore::Photon::XeElmTexture				m_textureDepth;
	Type										m_type;
	bool										m_clearOnActivate;
	bool										m_depthTest;

protected:
												Canvas();
};
#pragma once

#include "IRtti.h"
#include "Texture.h"
#include "Effect.h"
#include "Asset.h"

class Material : public virtual IRtti, public Asset, public virtual MemoryManager::Manageable
{
	RTTI_CLASS_DECLARE( Material );

public:
	enum Blending
	{
		bSource,
		bDestination,
		bEquation,
		bCount
	};

													Material();
													~Material();
	void											activate();
	void											unactivate();
	void											setTexture( Texture* t, unsigned int unit );
	Texture*										getTexture( unsigned int unit );
	void											setEffect( Effect* e );
	Effect*											getEffect();
	void											setBlending( Blending b, XeCore::XeEstate s );
	XeCore::XeEstate								getBlending( Blending b );
	void											setAlphaTestBorder( float v );
	float											getAlphaTestBorder();
	Effect::Properties*								getProperties();

	static Asset*									onLoad( AssetManager* manager, XeCore::XeString& name, Params& params, bool keepAlways );
	virtual void									onUnload();

private:
	Texture*										m_texture[ 8 ];
	Effect*											m_effect;
	XeCore::XeEstate								m_blendSrc;
	XeCore::XeEstate								m_blendDest;
	XeCore::XeEstate								m_blendEquation;
	Effect::Properties*								m_properties;
	float											m_alphaTestBorder;
};

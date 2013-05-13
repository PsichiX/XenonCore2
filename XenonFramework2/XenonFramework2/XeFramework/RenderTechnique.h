#pragma once

#include "IRtti.h"
#include "SpriteBatch.h"
#include "../XeCore/Base/XeElements.h"
#include "Asset.h"

class RenderTechnique : public virtual IRtti, public Asset, public IScene, public virtual MemoryManager::Manageable
{
	RTTI_CLASS_DECLARE( RenderTechnique );

private:
	class Pass;

public:
	typedef XeCore::XeElementPointer< Pass* > PassElm;

											RenderTechnique();
											~RenderTechnique();
	void									free();
	void									update();
	void									render();
	PassElm									addPass( NameID& name, unsigned int texCount, Effect* effect, int width = 0, int height = 0, bool flipH = false, bool flipV = false, bool renderToCanvas = true );
	PassElm									addPassDome( NameID& name, unsigned int texCount, Effect* effect, int width = 0, int height = 0, bool renderToCanvas = true );
	bool									removePass( NameID& name );
	bool									removePass( PassElm& pass );
	PassElm									getPass( NameID& name );
	PassElm									firstPass();
	PassElm									lastPass();
	Material*								getPassMaterial( PassElm& pass );
	Canvas*									getPassCanvas( PassElm& pass );
	Texture*								getPassInputTexture( PassElm& pass, unsigned int unit );
	Camera*									getPassCamera( PassElm& pass );
	bool									bindPassInputTexture( PassElm& pass, Texture* texture, unsigned int unit );
	bool									bindPassInputTexture( PassElm& pass, const XeCore::Photon::XeElmTexture& texture, unsigned int unit );
	bool									unbindPassInputTexture( PassElm& pass, unsigned int unit );
	bool									rebuildPassMaterialTextures( PassElm& pass );

	static Asset*							onLoad( AssetManager* manager, XeCore::XeString& name, Params& params, bool keepAlways );
	virtual void							onUnload();

private:
	class Pass
	{
	public:
											Pass( NameID& n ) : name( n ), outputScene( 0 ), outputQuad( 0 ), outputCanvas( 0 ), outputMaterial( 0 ), isDome( false ) {}
											~Pass();
		NameID								name;
		XeCore::XeArray< Texture* >			inputTextures;
		XeCore::XeArray< bool >				inputTexturesMine;
		SpriteBatch*						outputScene;
		SpriteBatch::Sprite*				outputQuad;
		Canvas*								outputCanvas;
		Material*							outputMaterial;
		bool								isDome;
	};

	void									validatePassesInput( Pass* pass );

	XeCore::XeElements< Pass* >				m_passes;

protected:
	void									setCamera( Camera* newcamera ) {}
	Camera*									getCamera() { return( 0 ); }
	void									setCanvas( Canvas* canvas ) {}
	Canvas*									getCanvas() { return( 0 ); }
	bool									attach( IRenderable* i ) { return( false ); }
	bool									detach( IRenderable* i ) { return( false ); }
};
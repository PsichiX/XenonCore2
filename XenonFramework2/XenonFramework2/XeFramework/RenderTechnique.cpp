#include "RenderTechnique.h"
#include "Camera2D.h"
#include "Camera3D.h"
#include "SceneManager.h"
#include "AssetManager.h"
#include "Canvas.h"

RTTI_CLASS_DERIVATIONS(	RenderTechnique,
						RTTI_DERIVATION( Asset ),
						RTTI_DERIVATION( IScene ),
						RTTI_DERIVATIONS_END
						);

RenderTechnique::RenderTechnique():
RTTI_CLASS_DEFINE( RenderTechnique )
{
}

RenderTechnique::~RenderTechnique()
{
	free();

	Asset::release( this );
}

void RenderTechnique::free()
{
	PassElm p = m_passes.FirstPointer();
	while( !p.IsEmpty() )
	{
		XeCore::XeString name = p()->name;
		bool status = removePass( p );
		XASSERT( status, "Pass '%s' removing failed!", name.Get() );
		p = m_passes.FirstPointer();
	}
}

void RenderTechnique::update()
{
	for( PassElm p = m_passes.FirstPointer(); !p.IsEmpty(); p.Next() )
		p()->outputScene->update();
}

void RenderTechnique::render()
{
	for( PassElm p = m_passes.FirstPointer(); !p.IsEmpty(); p.Next() )
		p()->outputScene->render();
}

RenderTechnique::PassElm RenderTechnique::addPass( NameID& name, unsigned int texCount, Effect* effect, int width, int height, bool flipH, bool flipV, bool renderToCanvas )
{
	for( PassElm p = m_passes.FirstPointer(); !p.IsEmpty(); p.Next() )
		if( p() && name == p()->name )
			return( PassElm() );
	if( static_cast<int>(texCount) > Global::use().engine->getTextureUnitsCount() )
		return( PassElm() );
	Engine::WindowRect wr;
	Global::use().engine->getWindowRect( wr );
	if( width <= 0 )
		width = wr.width;
	if( height <= 0 )
		height = wr.height;
	Pass* p = new Pass( name );
	PassElm pass = m_passes.AddPointer( p );
	if( pass.IsEmpty() )
	{
		DELETE_OBJECT( p );
		return( PassElm() );
	}
	p->inputTextures.Reserve( texCount );
	p->inputTexturesMine.Reserve( texCount );
	for( unsigned int i = 0; i < p->inputTextures.Size(); i++ )
	{
		p->inputTextures[ i ] = 0;
		p->inputTexturesMine[ i ] = false;
	}
	p->outputMaterial = xnew Material();
	p->outputMaterial->setEffect( effect );
	p->outputScene = xnew SpriteBatch( 1 );
	p->outputScene->setCamera( xnew Camera2D( 0.0f, 0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f ) );
	p->outputQuad = xnew SpriteBatch::Sprite();
	p->outputQuad->setMaterial( p->outputMaterial );
	p->outputQuad->setWidth( static_cast<float>(width) );
	p->outputQuad->setHeight( static_cast<float>(height) );
	if( flipH )
		p->outputQuad->flip( SpriteBatch::Sprite::ftHorizontal );
	if( flipV )
		p->outputQuad->flip( SpriteBatch::Sprite::ftVertical );
	p->outputScene->attach( p->outputQuad );
	if( renderToCanvas )
	{
		p->outputCanvas = xnew Canvas( width, height );
		p->outputScene->setCanvas( p->outputCanvas );
		p->outputCanvas->setClearOnActivate( true );
	}
	return( pass );
}

RenderTechnique::PassElm RenderTechnique::addPassDome( NameID& name, unsigned int texCount, Effect* effect, int width, int height, bool renderToCanvas )
{
	for( PassElm p = m_passes.FirstPointer(); !p.IsEmpty(); p.Next() )
		if( p() && name == p()->name )
			return( PassElm() );
	if( static_cast<int>(texCount) > Global::use().engine->getTextureUnitsCount() )
		return( PassElm() );
	Engine::WindowRect wr;
	Global::use().engine->getWindowRect( wr );
	if( width <= 0 )
		width = wr.width;
	if( height <= 0 )
		height = wr.height;
	Pass* p = new Pass( name );
	PassElm pass = m_passes.AddPointer( p );
	if( pass.IsEmpty() )
	{
		DELETE_OBJECT( p );
		return( PassElm() );
	}
	p->inputTextures.Reserve( texCount );
	p->inputTexturesMine.Reserve( texCount );
	for( unsigned int i = 0; i < p->inputTextures.Size(); i++ )
	{
		p->inputTextures[ i ] = 0;
		p->inputTexturesMine[ i ] = false;
	}
	p->outputMaterial = xnew Material();
	p->outputMaterial->setEffect( effect );
	p->outputScene = xnew SpriteBatch( 6 );
	float asp = (float)width / (float)height;
	float d = sqrt( 1.0f + ( asp * asp ) );
	float D = sqrt( 2.0f * ( d * d ) );
	p->outputScene->setCamera( xnew Camera3D( 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, false, 45.0f, asp, d * 0.5f, D * 2.0f) );
	p->isDome = true;
	p->outputQuad = xnew SpriteBatch::Sprite();
	p->outputQuad->setMaterial( p->outputMaterial );
	p->outputQuad->reserve( 24 );
	// +x
	p->outputQuad->access( 0 )->vertex.position = XeCore::XeHalfVector( d, d, d );
	p->outputQuad->access( 1 )->vertex.position = XeCore::XeHalfVector( d, -d, d );
	p->outputQuad->access( 2 )->vertex.position = XeCore::XeHalfVector( d, -d, -d );
	p->outputQuad->access( 3 )->vertex.position = XeCore::XeHalfVector( d, d, -d );
	// +y
	p->outputQuad->access( 4 )->vertex.position = XeCore::XeHalfVector( d, d, d );
	p->outputQuad->access( 5 )->vertex.position = XeCore::XeHalfVector( -d, d, d );
	p->outputQuad->access( 6 )->vertex.position = XeCore::XeHalfVector( -d, d, -d );
	p->outputQuad->access( 7 )->vertex.position = XeCore::XeHalfVector( d, d, -d );
	// +z
	p->outputQuad->access( 8 )->vertex.position = XeCore::XeHalfVector( -d, d, d );
	p->outputQuad->access( 9 )->vertex.position = XeCore::XeHalfVector( -d, -d, d );
	p->outputQuad->access( 10 )->vertex.position = XeCore::XeHalfVector( d, -d, d );
	p->outputQuad->access( 11 )->vertex.position = XeCore::XeHalfVector( d, d, d );
	// -x
	p->outputQuad->access( 12 )->vertex.position = XeCore::XeHalfVector( -d, d, d );
	p->outputQuad->access( 13 )->vertex.position = XeCore::XeHalfVector( -d, -d, d );
	p->outputQuad->access( 14 )->vertex.position = XeCore::XeHalfVector( -d, -d, -d );
	p->outputQuad->access( 15 )->vertex.position = XeCore::XeHalfVector( -d, d, -d );
	// -y
	p->outputQuad->access( 16 )->vertex.position = XeCore::XeHalfVector( d, -d, d );
	p->outputQuad->access( 17 )->vertex.position = XeCore::XeHalfVector( -d, -d, d );
	p->outputQuad->access( 18 )->vertex.position = XeCore::XeHalfVector( -d, -d, -d );
	p->outputQuad->access( 19 )->vertex.position = XeCore::XeHalfVector( d, -d, -d );
	// -z
	p->outputQuad->access( 20 )->vertex.position = XeCore::XeHalfVector( -d, d, -d );
	p->outputQuad->access( 21 )->vertex.position = XeCore::XeHalfVector( -d, -d, -d );
	p->outputQuad->access( 22 )->vertex.position = XeCore::XeHalfVector( d, -d, -d );
	p->outputQuad->access( 23 )->vertex.position = XeCore::XeHalfVector( d, d, -d );
	for( unsigned int i = 0; i < 24; i++ )
	{
		p->outputQuad->access( i )->vertex.color = XeCore::XeHalfVector( 1.0f, 1.0f, 1.0f );
		p->outputQuad->access( i )->vertex.coords = p->outputQuad->access( i )->vertex.position.Normalize();
	}
	p->outputScene->attach( p->outputQuad );
	if( renderToCanvas )
	{
		p->outputCanvas = xnew Canvas( width, height );
		p->outputScene->setCanvas( p->outputCanvas );
		p->outputCanvas->setClearOnActivate( true );
	}
	return( pass );
}

bool RenderTechnique::removePass( NameID& name )
{
	for( PassElm p = m_passes.FirstPointer(); !p.IsEmpty(); p.Next() )
		if( p() && name == p()->name )
		{
			Pass* pass = p();
			validatePassesInput( pass );
			DELETE_OBJECT( pass );
			m_passes.ErasePointer( p );
			return( true );
		}
	return( false );
}

bool RenderTechnique::removePass( PassElm& pass )
{
	if( pass.IsEmpty() )
		return( false );
	Pass* p = pass();
	validatePassesInput( p );
	DELETE_OBJECT( p );
	m_passes.ErasePointer( pass );
	return( true );
}

RenderTechnique::PassElm RenderTechnique::getPass( NameID& name )
{
	for( PassElm p = m_passes.FirstPointer(); !p.IsEmpty(); p.Next() )
		if( p() && name == p()->name )
			return( p );
	return( PassElm() );
}

RenderTechnique::PassElm RenderTechnique::firstPass()
{
	return( m_passes.FirstPointer() );
}

RenderTechnique::PassElm RenderTechnique::lastPass()
{
	return( m_passes.LastPointer() );
}

Material* RenderTechnique::getPassMaterial( PassElm& pass )
{
	if( pass.IsEmpty() )
		return( 0 );
	return( pass()->outputMaterial );
}

Canvas* RenderTechnique::getPassCanvas( PassElm& pass )
{
	if( pass.IsEmpty() )
		return( 0 );
	return( pass()->outputCanvas );
}

Texture* RenderTechnique::getPassInputTexture( PassElm& pass, unsigned int unit )
{
	if( pass.IsEmpty() )
		return( 0 );
	if( unit >= pass()->inputTextures.Size() )
		return( 0 );
	return( pass()->inputTextures[ unit ] );
}

Camera* RenderTechnique::getPassCamera( PassElm& pass )
{
	if( pass.IsEmpty() )
		return( 0 );
	return( pass()->outputScene->getCamera() );
}

bool RenderTechnique::bindPassInputTexture( PassElm& pass, Texture* texture, unsigned int unit )
{
	if( pass.IsEmpty() )
		return( false );
	if( unit >= pass()->inputTextures.Size() )
		return( false );
	unbindPassInputTexture( pass, unit );
	pass()->inputTextures[ unit ] = texture;
	rebuildPassMaterialTextures( pass );
	return( true );
}

bool RenderTechnique::bindPassInputTexture( PassElm& pass, const XeCore::Photon::XeElmTexture& texture, unsigned int unit )
{
	if( pass.IsEmpty() )
		return( false );
	if( unit >= pass()->inputTextures.Size() )
		return( false );
	unbindPassInputTexture( pass, unit );
	pass()->inputTextures[ unit ] = xnew Texture( texture );
	pass()->inputTexturesMine[ unit ] = true;
	rebuildPassMaterialTextures( pass );
	return( true );
}

bool RenderTechnique::unbindPassInputTexture( PassElm& pass, unsigned int unit )
{
	if( pass.IsEmpty() )
		return( false );
	if( unit >= pass()->inputTextures.Size() )
		return( false );
	if( pass()->inputTexturesMine[ unit ] )
	{
		Texture* t = pass()->inputTextures[ unit ];
		DELETE_OBJECT( t );
	}
	pass()->inputTextures[ unit ] = 0;
	rebuildPassMaterialTextures( pass );
	return( true );
}

bool RenderTechnique::rebuildPassMaterialTextures( PassElm& pass )
{
	if( pass.IsEmpty() )
		return( false );
	for( unsigned int i = 0; i < 8; i++ )
		pass()->outputMaterial->setTexture( 0, i );
	for( unsigned int i = 0; i < pass()->inputTextures.Size(); i++ )
		pass()->outputMaterial->setTexture( pass()->inputTextures[ i ], i );
	return( true );
}

Asset* RenderTechnique::onLoad( AssetManager* manager, XeCore::XeString& name, Params& params, bool keepAlways )
{
	RenderTechnique* t = xnew RenderTechnique();
	for( ParamsElm p = params.FirstPointer(); !p.IsEmpty(); p.Next() )
	{
		if( p().Value.getType() == ParamData::tParams && p().Value.getGroupType() == "pass" )
		{
			Params& pass = p().Value.getParams();
			unsigned int tc( 0 );
			Effect* eff( 0 );
			int w( 0 ), h( 0 );
			bool fh( false ), fv( false ), rtc( true ), dome( false );
			if( pass.Exists( "textures" ) )
				pass[ "textures" ].getValue().Convert( &tc, 'd' );
			if( pass.Exists( "effectAsset" ) )
				eff = manager->get< Effect >( pass[ "effectAsset" ].getValue(), keepAlways );
			if( pass.Exists( "width" ) )
				pass[ "width" ].getValue().Convert( &w, 'i' );
			if( pass.Exists( "height" ) )
				pass[ "height" ].getValue().Convert( &h, 'i' );
			if( pass.Exists( "flipVertical" ) )
				fv = pass[ "flipVertical" ].getValue() == "true";
			if( pass.Exists( "flipHorizontal" ) )
				fh = pass[ "flipHorizontal" ].getValue() == "true";
			if( pass.Exists( "renderToCanvas" ) )
				rtc = pass[ "renderToCanvas" ].getValue() == "true";
			if( pass.Exists( "isDome" ) )
				dome = pass[ "isDome" ].getValue() == "true";
			RenderTechnique::PassElm elm = dome ? t->addPassDome( p().Key, tc, eff, w, h, rtc ) : t->addPass( p().Key, tc, eff, w, h, fh, fv, rtc );
			if( t->getPassCanvas( elm ) )
			{
				if( pass.Exists( "canvasColorFilteringLevel" ) )
				{
					int flevel( 0 );
					pass[ "canvasColorFilteringLevel" ].getValue().Convert( &flevel, 'i' );
					t->getPassCanvas( elm )->filtering( flevel );
				}
				if( pass.Exists( "canvasColorRepeating" ) )
					t->getPassCanvas( elm )->repeating( pass[ "canvasColorRepeating" ].getValue() == "true" );
				if( pass.Exists( "canvasDepthFilteringLevel" ) )
				{
					int flevel( 0 );
					pass[ "canvasDepthFilteringLevel" ].getValue().Convert( &flevel, 'i' );
					t->getPassCanvas( elm )->filteringDepth( flevel );
				}
				if( pass.Exists( "canvasDepthRepeating" ) )
					t->getPassCanvas( elm )->repeatingDepth( pass[ "canvasDepthRepeating" ].getValue() == "true" );
			}
			if( !elm.IsEmpty() && pass.Exists( "textureBinds" ) && pass[ "textureBinds" ].getType() == ParamData::tParams )
			{
				Params& tb = pass[ "textureBinds" ].getParams();
				for( ParamsElm _p = tb.FirstPointer(); !_p.IsEmpty(); _p.Next() )
				{
					if( _p().Value.getType() == ParamData::tValue )
					{
						unsigned int sc( 0 );
						XeCore::XeString* sv = _p().Key.Explode( " ", sc );
						if( sv && sc )
						{
							if( sc == 4 && sv[ 0 ] == "unit" && sv[ 2 ] == "from" )
							{
								int unit( 0 );
								sv[ 1 ].Convert( &unit, 'i' );
								if( sv[ 3 ] == "canvasAssetColorTexture" )
									t->bindPassInputTexture( elm, manager->get< Canvas >( _p().Value.getValue(), keepAlways )->getTexture(), unit );
								else
								if( sv[ 3 ] == "canvasAssetDepthTexture" )
									t->bindPassInputTexture( elm, manager->get< Canvas >( _p().Value.getValue(), keepAlways )->getTextureDepth(), unit );
								else
								if( sv[ 3 ] == "passCanvasColorTexture" )
									t->bindPassInputTexture( elm, t->getPassCanvas( t->getPass( NameID( _p().Value.getValue() ) ) )->getTexture(), unit );
								else
								if( sv[ 3 ] == "passCanvasDepthTexture" )
									t->bindPassInputTexture( elm, t->getPassCanvas( t->getPass( NameID( _p().Value.getValue() ) ) )->getTextureDepth(), unit );
								else
								if( sv[ 3 ] == "textureAsset" )
									t->bindPassInputTexture( elm, manager->get< Texture >( _p().Value.getValue(), keepAlways ), unit );
							}
							delete[] sv;
						}
					}
				}
			}
			if( pass.Exists( "properties" ) && pass[ "properties" ].getType() == ParamData::tParams )
			{
				Material* m = t->getPassMaterial( elm );
				for( ParamsElm _p = pass[ "properties" ].getParams().FirstPointer(); !_p.IsEmpty(); _p.Next() )
				{
					if( _p().Value.getType() != ParamData::tParams )
						continue;
					if( _p().Value.getGroupType() == "float" )
					{
						XeCore::XeHalfVector v;
						_p().Value.getParams()[ "x" ].getValue().Convert( &v.X, 'h' );
						m->getProperties()->setPropertyVec( _p().Key, v, 1 );
					}
					else
					if( _p().Value.getGroupType() == "vec2" )
					{
						XeCore::XeHalfVector v;
						_p().Value.getParams()[ "x" ].getValue().Convert( &v.X, 'h' );
						_p().Value.getParams()[ "y" ].getValue().Convert( &v.Y, 'h' );
						m->getProperties()->setPropertyVec( _p().Key, v, 2 );
					}
					else
					if( _p().Value.getGroupType() == "vec3" )
					{
						XeCore::XeHalfVector v;
						_p().Value.getParams()[ "x" ].getValue().Convert( &v.X, 'h' );
						_p().Value.getParams()[ "y" ].getValue().Convert( &v.Y, 'h' );
						_p().Value.getParams()[ "z" ].getValue().Convert( &v.Z, 'h' );
						m->getProperties()->setPropertyVec( _p().Key, v, 3 );
					}
					else
					if( _p().Value.getGroupType() == "vec4" )
					{
						XeCore::XeHalfVector v;
						_p().Value.getParams()[ "x" ].getValue().Convert( &v.X, 'h' );
						_p().Value.getParams()[ "y" ].getValue().Convert( &v.Y, 'h' );
						_p().Value.getParams()[ "z" ].getValue().Convert( &v.Z, 'h' );
						_p().Value.getParams()[ "w" ].getValue().Convert( &v.W, 'h' );
						m->getProperties()->setPropertyVec( _p().Key, v, 4 );
					}
					else
					if( _p().Value.getGroupType() == "int" )
					{
						XeCore::XeInteger v[ 4 ];
						_p().Value.getParams()[ "x" ].getValue().Convert( &v[ 0 ], 'i' );
						m->getProperties()->setPropertyInt( _p().Key, v, 1 );
					}
					else
					if( _p().Value.getGroupType() == "int2" )
					{
						XeCore::XeInteger v[ 4 ];
						_p().Value.getParams()[ "x" ].getValue().Convert( &v[ 0 ], 'i' );
						_p().Value.getParams()[ "y" ].getValue().Convert( &v[ 1 ], 'i' );
						m->getProperties()->setPropertyInt( _p().Key, v, 2 );
					}
					else
					if( _p().Value.getGroupType() == "int3" )
					{
						XeCore::XeInteger v[ 4 ];
						_p().Value.getParams()[ "x" ].getValue().Convert( &v[ 0 ], 'i' );
						_p().Value.getParams()[ "y" ].getValue().Convert( &v[ 1 ], 'i' );
						_p().Value.getParams()[ "z" ].getValue().Convert( &v[ 2 ], 'i' );
						m->getProperties()->setPropertyInt( _p().Key, v, 3 );
					}
					else
					if( _p().Value.getGroupType() == "int4" )
					{
						XeCore::XeInteger v[ 4 ];
						_p().Value.getParams()[ "x" ].getValue().Convert( &v[ 0 ], 'i' );
						_p().Value.getParams()[ "y" ].getValue().Convert( &v[ 1 ], 'i' );
						_p().Value.getParams()[ "z" ].getValue().Convert( &v[ 2 ], 'i' );
						_p().Value.getParams()[ "w" ].getValue().Convert( &v[ 3 ], 'i' );
						m->getProperties()->setPropertyInt( _p().Key, v, 4 );
					}
					else
					if( _p().Value.getGroupType() == "sampler2D" )
					{
						XeCore::XeInteger v;
						_p().Value.getParams()[ "unit" ].getValue().Convert( &v, 'i' );
						m->getProperties()->setPropertySampler( _p().Key, v );
					}
					else
					if( _p().Value.getGroupType() == "sampler3D" )
					{
						XeCore::XeInteger v;
						_p().Value.getParams()[ "unit" ].getValue().Convert( &v, 'i' );
						m->getProperties()->setPropertySampler( _p().Key, v );
					}
					else
					if( _p().Value.getGroupType() == "mat4" )
					{
						XeCore::XeHalfMatrix v;
						_p().Value.getParams()[ "0" ].getValue().Convert( &v.Cell[ 0 ], 'h' );
						_p().Value.getParams()[ "1" ].getValue().Convert( &v.Cell[ 1 ], 'h' );
						_p().Value.getParams()[ "2" ].getValue().Convert( &v.Cell[ 2 ], 'h' );
						_p().Value.getParams()[ "3" ].getValue().Convert( &v.Cell[ 3 ], 'h' );
						_p().Value.getParams()[ "4" ].getValue().Convert( &v.Cell[ 4 ], 'h' );
						_p().Value.getParams()[ "5" ].getValue().Convert( &v.Cell[ 5 ], 'h' );
						_p().Value.getParams()[ "6" ].getValue().Convert( &v.Cell[ 6 ], 'h' );
						_p().Value.getParams()[ "7" ].getValue().Convert( &v.Cell[ 7 ], 'h' );
						_p().Value.getParams()[ "8" ].getValue().Convert( &v.Cell[ 8 ], 'h' );
						_p().Value.getParams()[ "9" ].getValue().Convert( &v.Cell[ 9 ], 'h' );
						_p().Value.getParams()[ "10" ].getValue().Convert( &v.Cell[ 10 ], 'h' );
						_p().Value.getParams()[ "11" ].getValue().Convert( &v.Cell[ 11 ], 'h' );
						_p().Value.getParams()[ "12" ].getValue().Convert( &v.Cell[ 12 ], 'h' );
						_p().Value.getParams()[ "13" ].getValue().Convert( &v.Cell[ 13 ], 'h' );
						_p().Value.getParams()[ "14" ].getValue().Convert( &v.Cell[ 14 ], 'h' );
						_p().Value.getParams()[ "15" ].getValue().Convert( &v.Cell[ 15 ], 'h' );
						m->getProperties()->setPropertyMat( _p().Key, v, _p().Value.getParams()[ "transpose" ].getValue() == "true" ? true : false );
					}
					else
					if( _p().Value.getGroupType() == "float[]" )
					{
						if( _p().Value.getParams().Size() )
						{
							unsigned int i = 0;
							XeCore::XeArray< XeCore::XeHalf > temp( _p().Value.getParams().Size() );
							for( ParamsElm a = _p().Value.getParams().FirstPointer(); !a.IsEmpty(); a.Next(), i++ )
								a().Value.getValue().Convert( &temp[ i ], 'h' );
							m->getProperties()->setPropertyArrayHalf( _p().Key, temp.Get(), temp.Size(), 1 );
						}
					}
					else
					if( _p().Value.getGroupType() == "int[]" )
					{
						if( _p().Value.getParams().Size() )
						{
							unsigned int i = 0;
							XeCore::XeArray< XeCore::XeInteger > temp( _p().Value.getParams().Size() );
							for( ParamsElm a = _p().Value.getParams().FirstPointer(); !a.IsEmpty(); a.Next(), i++ )
								a().Value.getValue().Convert( &temp[ i ], 'i' );
							m->getProperties()->setPropertyArrayInt( _p().Key, temp.Get(), temp.Size(), 1 );
						}
					}
				}
			}
		}
	}
	if( Global::use().scenes->attach( NameID( name ), t ) )
	{
		ASSET_SET_PURE_POINTER( t );
		return( t );
	}
	else
	{
		DELETE_OBJECT( t );
		return( 0 );
	}
}

void RenderTechnique::onUnload()
{
	Global::use().scenes->detach( NameID( getAssetName() ) );
}

void RenderTechnique::validatePassesInput( Pass* pass )
{
	if( pass->outputCanvas )
		for( PassElm p = m_passes.FirstPointer(); !p.IsEmpty(); p.Next() )
		{
			for( unsigned int i = 0; i < p()->inputTextures.Size(); i++ )
			{
				if( !p()->inputTextures[ i ] )
					continue;
				XeCore::Photon::XeElmTexture it = p()->inputTextures[ i ]->getTexture();
				XeCore::Photon::XeElmTexture ct = pass->outputCanvas->getTexture();
				XeCore::Photon::XeElmTexture dt = pass->outputCanvas->getTextureDepth();
				if( it == ct || it == dt )
				{
					if( p()->inputTexturesMine[ i ] )
					{
						Texture* t = p()->inputTextures[ i ];
						DELETE_OBJECT( t );
					}
					p()->inputTextures[ i ] = 0;
				}
			}
			rebuildPassMaterialTextures( p );
		}
}

RenderTechnique::Pass::~Pass()
{
	if( outputCanvas )
	{
		outputScene->setCanvas( 0 );
		DELETE_OBJECT( outputCanvas );
	}
	outputQuad->setMaterial( 0 );
	DELETE_OBJECT( outputMaterial );
	DELETE_OBJECT( outputQuad );
	DELETE_OBJECT( outputScene );
	for( unsigned int i = 0; i < inputTextures.Size(); i++ )
		if( inputTexturesMine[ i ] )
		{
			Texture* t = inputTextures[ i ];
			DELETE_OBJECT( t );
		}
	inputTextures.Free();
	inputTexturesMine.Free();
}
#include "Material.h"
#include "Effect.h"
#include "Texture.h"
#include "MaterialManager.h"
#include "Asset.h"
#include "AssetManager.h"

RTTI_CLASS_DERIVATIONS(	Material,
						RTTI_DERIVATION( Asset ),
						RTTI_DERIVATIONS_END
						);

Material::Material():
RTTI_CLASS_DEFINE( Material ),
m_effect( 0 ),
m_blendSrc( XeCore::XE_RENDER_BLEND_SRC_ALPHA ),
m_blendDest( XeCore::XE_RENDER_BLEND_ONE_MINUS_SRC_ALPHA ),
m_blendEquation( XeCore::XE_RENDER_BLEND_ADD ),
m_properties( 0 ),
m_alphaTestBorder( 0.0f )
{
	for( int i = 0; i < 8; i++ )
		m_texture[ i ] = 0;
	m_properties = xnew Effect::Properties();
}

Material::~Material()
{
	DELETE_OBJECT( m_properties );

	Asset::release( this );
}

void Material::activate()
{
	for( int i = 0; i < 8; i++ )
	{
		XeCore::Photon::XeTextureUnit( i );
		if( m_texture[ i ] )
		{
			XeCore::XeSetState( XeCore::XE_RENDER_TEXTURING_2D, XeCore::XE_TRUE );
			m_texture[ i ]->activate();
		}
	}
	if( m_effect )
	{
		m_properties->apply( m_effect );
		m_effect->activate();
	}
	else
		Effect::unactivate();
	XeCore::XeSetState( XeCore::XE_RENDER_BLEND, XeCore::XE_TRUE );
	XeCore::XeSetState( XeCore::XE_RENDER_BLEND_TYPE, m_blendSrc, m_blendDest );
	XeCore::XeSetState( XeCore::XE_RENDER_BLEND_EQUATION, m_blendEquation );
	if( m_alphaTestBorder > 0.0f )
	{
		XeCore::XeSetState( XeCore::XE_RENDER_ALPHA_TEST, XeCore::XE_TRUE );
		double v = (double)m_alphaTestBorder;
		XeCore::XeSetState( XeCore::XE_RENDER_ALPHA_TYPE, XeCore::XE_RENDER_ALPHA_GEQUAL, v );
	}
}

void Material::unactivate()
{
	for( int i = 0; i < 8; i++ )
	{
		XeCore::Photon::XeTextureUnit( i );
		if( m_texture[ i ] )
		{
			//XeCore::XeSetState( XeCore::XE_RENDER_TEXTURING_2D, XeCore::XE_FALSE );
			m_texture[ i ]->unactivate();
		}
	}
	Effect::unactivate();
	XeCore::XeSetState( XeCore::XE_RENDER_BLEND, XeCore::XE_FALSE );
	XeCore::XeSetState( XeCore::XE_RENDER_ALPHA_TEST, XeCore::XE_FALSE );
}

void Material::setTexture( Texture* t, unsigned int unit )
{
	if( unit > 7 )
		unit = 0;
	m_texture[ unit ] = t;
}

Texture* Material::getTexture( unsigned int unit )
{
	if( unit > 7 )
		unit = 0;
	return( m_texture[ unit ] );
}

void Material::setEffect( Effect* e )
{
	m_effect = e;
}

Effect* Material::getEffect()
{
	return( m_effect );
}

void Material::setBlending( Blending b, XeCore::XeEstate s )
{
	if( b == bSource )
		m_blendSrc = s;
	else
	if( b == bDestination )
		m_blendDest = s;
	else
	if( b == bEquation )
		m_blendEquation = s;
}

XeCore::XeEstate Material::getBlending( Blending b )
{
	if( b == bSource )
		return( m_blendSrc );
	else
	if( b == bDestination )
		return( m_blendDest );
	else
	if( b == bEquation )
		return( m_blendEquation );
	return( XeCore::XE_FALSE );
}

void Material::setAlphaTestBorder( float v )
{
	m_alphaTestBorder = max( 0.0f, min( 1.0f, v ) );
}

float Material::getAlphaTestBorder()
{
	return( m_alphaTestBorder );
}

Effect::Properties* Material::getProperties()
{
	return( m_properties );
}

Asset* Material::onLoad( AssetManager* manager, XeCore::XeString& name, Params& params, bool keepAlways )
{
	XeCore::XeString s;
	Material* t = xnew Material();
	for( unsigned int i = 0; i < 8; i++ )
	{
		s.Format( "texture%uAsset", i );
		if( params.Exists( s ) )
			t->setTexture( manager->get< Texture >( params[ s ].getValue(), keepAlways ), i );
	}
	s.Clear();
	if( params.Exists( "effectAsset" ) )
		t->setEffect( manager->get< Effect >( params[ "effectAsset" ].getValue(), keepAlways ) );
	if( params.Exists( "alphaTestBorder" ) )
	{
		float v( 0.0f );
		params[ "alphaTestBorder" ].getValue().Convert( &v, 'h' );
		t->setAlphaTestBorder( v );
	}
	if( params.Exists( "properties" ) && params[ "properties" ].getType() == ParamData::tParams )
	{
		for( ParamsElm p = params[ "properties" ].getParams().FirstPointer(); !p.IsEmpty(); p.Next() )
		{
			if( p().Value.getType() != ParamData::tParams )
				continue;
			if( p().Value.getGroupType() == "float" )
			{
				XeCore::XeHalfVector v;
				p().Value.getParams()[ "x" ].getValue().Convert( &v.X, 'h' );
				t->getProperties()->setPropertyVec( p().Key, v, 1 );
			}
			else
			if( p().Value.getGroupType() == "vec2" )
			{
				XeCore::XeHalfVector v;
				p().Value.getParams()[ "x" ].getValue().Convert( &v.X, 'h' );
				p().Value.getParams()[ "y" ].getValue().Convert( &v.Y, 'h' );
				t->getProperties()->setPropertyVec( p().Key, v, 2 );
			}
			else
			if( p().Value.getGroupType() == "vec3" )
			{
				XeCore::XeHalfVector v;
				p().Value.getParams()[ "x" ].getValue().Convert( &v.X, 'h' );
				p().Value.getParams()[ "y" ].getValue().Convert( &v.Y, 'h' );
				p().Value.getParams()[ "z" ].getValue().Convert( &v.Z, 'h' );
				t->getProperties()->setPropertyVec( p().Key, v, 3 );
			}
			else
			if( p().Value.getGroupType() == "vec4" )
			{
				XeCore::XeHalfVector v;
				p().Value.getParams()[ "x" ].getValue().Convert( &v.X, 'h' );
				p().Value.getParams()[ "y" ].getValue().Convert( &v.Y, 'h' );
				p().Value.getParams()[ "z" ].getValue().Convert( &v.Z, 'h' );
				p().Value.getParams()[ "w" ].getValue().Convert( &v.W, 'h' );
				t->getProperties()->setPropertyVec( p().Key, v, 4 );
			}
			else
			if( p().Value.getGroupType() == "int" )
			{
				XeCore::XeInteger v[ 4 ];
				p().Value.getParams()[ "x" ].getValue().Convert( &v[ 0 ], 'i' );
				t->getProperties()->setPropertyInt( p().Key, v, 1 );
			}
			else
			if( p().Value.getGroupType() == "int2" )
			{
				XeCore::XeInteger v[ 4 ];
				p().Value.getParams()[ "x" ].getValue().Convert( &v[ 0 ], 'i' );
				p().Value.getParams()[ "y" ].getValue().Convert( &v[ 1 ], 'i' );
				t->getProperties()->setPropertyInt( p().Key, v, 2 );
			}
			else
			if( p().Value.getGroupType() == "int3" )
			{
				XeCore::XeInteger v[ 4 ];
				p().Value.getParams()[ "x" ].getValue().Convert( &v[ 0 ], 'i' );
				p().Value.getParams()[ "y" ].getValue().Convert( &v[ 1 ], 'i' );
				p().Value.getParams()[ "z" ].getValue().Convert( &v[ 2 ], 'i' );
				t->getProperties()->setPropertyInt( p().Key, v, 3 );
			}
			else
			if( p().Value.getGroupType() == "int4" )
			{
				XeCore::XeInteger v[ 4 ];
				p().Value.getParams()[ "x" ].getValue().Convert( &v[ 0 ], 'i' );
				p().Value.getParams()[ "y" ].getValue().Convert( &v[ 1 ], 'i' );
				p().Value.getParams()[ "z" ].getValue().Convert( &v[ 2 ], 'i' );
				p().Value.getParams()[ "w" ].getValue().Convert( &v[ 3 ], 'i' );
				t->getProperties()->setPropertyInt( p().Key, v, 4 );
			}
			else
			if( p().Value.getGroupType() == "sampler2D" )
			{
				XeCore::XeInteger v;
				p().Value.getParams()[ "unit" ].getValue().Convert( &v, 'i' );
				t->getProperties()->setPropertySampler( p().Key, v );
			}
			else
			if( p().Value.getGroupType() == "sampler3D" )
			{
				XeCore::XeInteger v;
				p().Value.getParams()[ "unit" ].getValue().Convert( &v, 'i' );
				t->getProperties()->setPropertySampler( p().Key, v );
			}
			else
			if( p().Value.getGroupType() == "mat4" )
			{
				XeCore::XeHalfMatrix v;
				p().Value.getParams()[ "0" ].getValue().Convert( &v.Cell[ 0 ], 'h' );
				p().Value.getParams()[ "1" ].getValue().Convert( &v.Cell[ 1 ], 'h' );
				p().Value.getParams()[ "2" ].getValue().Convert( &v.Cell[ 2 ], 'h' );
				p().Value.getParams()[ "3" ].getValue().Convert( &v.Cell[ 3 ], 'h' );
				p().Value.getParams()[ "4" ].getValue().Convert( &v.Cell[ 4 ], 'h' );
				p().Value.getParams()[ "5" ].getValue().Convert( &v.Cell[ 5 ], 'h' );
				p().Value.getParams()[ "6" ].getValue().Convert( &v.Cell[ 6 ], 'h' );
				p().Value.getParams()[ "7" ].getValue().Convert( &v.Cell[ 7 ], 'h' );
				p().Value.getParams()[ "8" ].getValue().Convert( &v.Cell[ 8 ], 'h' );
				p().Value.getParams()[ "9" ].getValue().Convert( &v.Cell[ 9 ], 'h' );
				p().Value.getParams()[ "10" ].getValue().Convert( &v.Cell[ 10 ], 'h' );
				p().Value.getParams()[ "11" ].getValue().Convert( &v.Cell[ 11 ], 'h' );
				p().Value.getParams()[ "12" ].getValue().Convert( &v.Cell[ 12 ], 'h' );
				p().Value.getParams()[ "13" ].getValue().Convert( &v.Cell[ 13 ], 'h' );
				p().Value.getParams()[ "14" ].getValue().Convert( &v.Cell[ 14 ], 'h' );
				p().Value.getParams()[ "15" ].getValue().Convert( &v.Cell[ 15 ], 'h' );
				t->getProperties()->setPropertyMat( p().Key, v, p().Value.getParams()[ "transpose" ].getValue() == "true" ? true : false );
			}
			else
			if( p().Value.getGroupType() == "float[]" )
			{
				if( p().Value.getParams().Size() )
				{
					unsigned int i = 0;
					XeCore::XeArray< XeCore::XeHalf > temp( p().Value.getParams().Size() );
					for( ParamsElm a = p().Value.getParams().FirstPointer(); !a.IsEmpty(); a.Next(), i++ )
						a().Value.getValue().Convert( &temp[ i ], 'h' );
					t->getProperties()->setPropertyArrayHalf( p().Key, temp.Get(), temp.Size(), 1 );
				}
			}
			else
			if( p().Value.getGroupType() == "int[]" )
			{
				if( p().Value.getParams().Size() )
				{
					unsigned int i = 0;
					XeCore::XeArray< XeCore::XeInteger > temp( p().Value.getParams().Size() );
					for( ParamsElm a = p().Value.getParams().FirstPointer(); !a.IsEmpty(); a.Next(), i++ )
						a().Value.getValue().Convert( &temp[ i ], 'i' );
					t->getProperties()->setPropertyArrayInt( p().Key, temp.Get(), temp.Size(), 1 );
				}
			}
		}
	}
	if( Global::use().materials->attach( NameID( name ), t ) )
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

void Material::onUnload()
{
	Global::use().materials->detach( NameID( getAssetName() ) );
}
#include "Asset.h"
#include "AssetManager.h"
#include "Manager.h"
#include "TextureManager.h"
#include "EffectManager.h"
#include "FontManager.h"
#include "MaterialManager.h"
#include "AudioManager.h"
#include "Music.h"
#include "Sound.h"
#include "SceneManager.h"
#include "SpriteBatch.h"
#include "Camera2D.h"
#include "CanvasManager.h"
#include "RenderTechnique.h"

RTTI_CLASS_DERIVATIONS(	Asset,
						RTTI_DERIVATIONS_END
						);

Asset::Asset():
RTTI_CLASS_DEFINE( Asset ),
m_manager( 0 ),
m_level( 0 ),
m_loaded( false ),
m_purePointer( 0 )
{
}

Asset::~Asset()
{
	onUnload();
}

void Asset::onUnload()
{
	if( m_loaded && m_manager )
	{
		XASSERT( 0, "Asset::release( this ) does not called from child destructor!" );
	}
}

XeCore::XeString& Asset::getAssetName()
{
	return( m_name );
}

unsigned int Asset::getAssetLevel()
{
	return( m_level );
}

bool Asset::isAssetLoaded()
{
	return( m_loaded );
}

AssetManager* Asset::getAssetManager()
{
	return( m_manager );
}

void* Asset::getAssetPurePointer()
{
	return( m_purePointer );
}

void Asset::release( Asset* asset )
{
	if( asset->isAssetLoaded() )
	{
		asset->onUnload();
		asset->m_manager = 0;
	}
}

void Asset::setAssetPurePointer( void* pp )
{
	m_purePointer = pp;
}

Asset::ParamData::ParamData():
m_data( 0 ),
m_type( tEmpty )
{
}

Asset::ParamData::~ParamData()
{
	setEmpty();
	m_staticParams.Clear();
	m_staticValue.Clear();
}

void Asset::ParamData::setValue( XeCore::XeString& name, XeCore::XeString& v )
{
	m_data = new XeCore::XeString( v );
	m_type = tValue;
	m_name = name;
}

void Asset::ParamData::setParams( XeCore::XeString& name, const char* grouptype )
{
	m_data = new Params();
	m_type = tParams;
	m_name = name;
	m_grouptype = const_cast<char*>(grouptype);
}

void Asset::ParamData::setEmpty()
{
	if( m_data && m_type == tValue )
	{
		((XeCore::XeString*)m_data)->Clear();
		delete (XeCore::XeString*)m_data;
	}
	else
	if( m_data && m_type == tParams )
	{
		((Params*)m_data)->Clear();
		delete (Params*)m_data;
	}
	m_data = 0;
	m_type = tEmpty;
	m_name.Clear();
}

XeCore::XeString& Asset::ParamData::getValue()
{
	if( m_type == tValue )
		return( *(XeCore::XeString*)m_data );
	return( m_staticValue );
}

Asset::Params& Asset::ParamData::getParams()
{
	if( m_type == tParams )
		return( *(Params*)m_data );
	return( m_staticParams );
}

Asset::ParamData::Type Asset::ParamData::getType()
{
	return( m_type );
}

XeCore::XeString& Asset::ParamData::getName()
{
	return( m_name );
}

XeCore::XeString& Asset::ParamData::getGroupType()
{
	return( m_grouptype );
}

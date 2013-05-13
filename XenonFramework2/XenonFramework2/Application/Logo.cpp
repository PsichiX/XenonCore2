#include "Logo.h"
#include "../XeFramework/AssetManager.h"
#include "../XeFramework/SceneManager.h"

RTTI_CLASS_DERIVATIONS(	Logo,
						RTTI_DERIVATION( IActor ),
						RTTI_DERIVATIONS_END
						);

Logo::Logo():
RTTI_CLASS_DEFINE( Logo )
{
	m_sprite = xnew SpriteBatch::Sprite();
	m_sprite->setWidth( 256.0f );
	m_sprite->setHeight( 128.0f );
	m_sprite->setXoffset( 256.0f );
	m_sprite->setYoffset( 128.0f );
	m_sprite->setMaterial( GLOBAL.assets->get< Material>( "matLogo.xml" ) );
	m_sprite->setPosition( XeCore::XeHalfVector( 1024.0f, 576.0f ) );
	m_sprite->setOrder( -2.0f );
	GLOBAL.assets->get< SpriteBatch>( "sbOverlay.xml" )->attach( m_sprite );
}

Logo::~Logo()
{
	DELETE_OBJECT( m_sprite );
}

void Logo::update()
{
}

void Logo::input()
{
}

void Logo::render()
{
}
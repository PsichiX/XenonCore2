#include "Crate.h"
#include "../XeFramework/AssetManager.h"
#include "../XeFramework/SceneManager.h"

RTTI_CLASS_DERIVATIONS(	Crate,
						RTTI_DERIVATION( IActor ),
						RTTI_DERIVATION( ICollisional ),
						RTTI_DERIVATIONS_END
						);

Crate::Crate( XeCore::XeHalfVector& pos, float angle, float spdx, float spdy, float rot ):
RTTI_CLASS_DEFINE( Crate ),
m_spd( spdx, spdy ),
m_rot( rot )
{
	m_sprite = xnew SpriteBatch::Sprite();
	m_sprite->setWidth( 64.0f );
	m_sprite->setHeight( 64.0f );
	m_sprite->setXoffset( 32.0f );
	m_sprite->setYoffset( 32.0f );
	m_sprite->setMaterial( GLOBAL.assets->get< Material>( "matCrate.xml" ) );
	m_sprite->setPosition( pos );
	m_sprite->setRotation( XeCore::XeAngleHalfVector( angle ) );
	GLOBAL.assets->get< SpriteBatch>( "sbSprites.xml" )->attach( m_sprite );

	ICollisional::bind( GLOBAL.collisions, this );
	ICollisional::setCollisionRange( 32.0f );
	ICollisional::setCollisionPosition( pos );
}

Crate::~Crate()
{
	DELETE_OBJECT( m_sprite );

	ICollisional::unbind();
}

void Crate::update()
{
	if( ICollisional::collisionChange() )
	{
		if( ICollisional::isCollide() )
			m_sprite->setColor( XeCore::XeHalfVector( 1.0f, 0.0f, 0.0f ) );
		else
			m_sprite->setColor( XeCore::XeHalfVector( 1.0f, 1.0f, 1.0f ) );
	}

	XeCore::XeHalfVector t = getCollisionPosition() + XeCore::XeHalfVector( m_spd.X * GLOBAL.engine->getDeltaTime(), m_spd.Y * GLOBAL.engine->getDeltaTime() );
	if( t.X < -getCollisionRange() * 2.0f )
		t.X = 1024.0f + getCollisionRange() * 2.0f;
	if( t.Y < -getCollisionRange() * 2.0f )
		t.Y = 576.0f + getCollisionRange() * 2.0f;
	if( t.X > 1024.0f + getCollisionRange() * 2.0f )
		t.X = -getCollisionRange() * 2.0f;
	if( t.Y > 576.0f + getCollisionRange() * 2.0f )
		t.Y = -getCollisionRange() * 2.0f;
	setCollisionPosition( t );
	m_sprite->setPosition( t );
	m_sprite->setRotation( XeCore::XeAngleHalfVector( m_sprite->getRotation().Alpha + m_rot * GLOBAL.engine->getDeltaTime() ) );
}

void Crate::input()
{
}

void Crate::render()
{
}

SpriteBatch::Sprite* Crate::getSprite()
{
	return( m_sprite );
}

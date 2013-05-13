#include "Player.h"
#include "PlayerBrain.h"
#include "../XeFramework/AssetManager.h"
#include "../XeFramework/SceneManager.h"

RTTI_CLASS_DERIVATIONS(	Player,
						RTTI_DERIVATION( IActor ),
						RTTI_DERIVATION( IControllable ),
						RTTI_DERIVATION( ICollisional ),
						RTTI_DERIVATIONS_END
						);

Player::Player( XeCore::XeHalfVector& pos ):
RTTI_CLASS_DEFINE( Player ),
m_skeleton( 0 ),
XMM_PRINTABLE( Player )
{
	XMM_PRINTABLE_SETUP(	XMM_PRINTABLE_MEMBER_PTR( m_skeleton ),
							XMM_PRINTABLE_MEMBERS_END
							);

	SpriteBatch::Sprite* sprite = xnew SpriteBatch::Sprite();
	sprite->setWidth( 64.0f );
	sprite->setHeight( 64.0f );
	sprite->setXoffset( 32.0f );
	sprite->setYoffset( 32.0f );
	sprite->setMaterial( GLOBAL.assets->get< Material>( "matPlayer.xml" ) );
	sprite->setPosition( pos );
	sprite->setOrder( -1.0f );
	GLOBAL.assets->get< SpriteBatch>( "sbSprites.xml" )->attach( sprite );

	m_skeleton = xnew Skeleton();
	m_skeleton->getRoot()->attach( sprite );
	m_skeleton->getRoot()->setRemoveable( true );

	IControllable::bind( GLOBAL.controls, this );
	IControllable::setController( xnew PlayerBrain() );

	ICollisional::bind( GLOBAL.collisions, this );
	ICollisional::setCollisionRange( 32.0f );
	ICollisional::setCollisionPosition( pos );
}

Player::~Player()
{
	DELETE_OBJECT( m_skeleton );
	
	IControllable::unbind();
	ICollisional::unbind();
}

void Player::update()
{
}

void Player::input()
{
	if( KEY_PRESSED( Input::kSPACE ) )
		DELETE_OBJECT( m_skeleton );
}

void Player::render()
{
}

void Player::move( XeCore::XeHalfVector& relativePos )
{
	XeCore::XeHalfVector t = getCollisionPosition() + relativePos;
	t.X = CLAMP( t.X, 0.0f + getCollisionRange(), 1024.0f - getCollisionRange() );
	t.Y = CLAMP( t.Y, 0.0f + getCollisionRange(), 576.0f - getCollisionRange() );
	setCollisionPosition( t );
	m_skeleton->setPosition( t );
	if( relativePos.X > 0.0f && relativePos.Y == 0.0f )
		m_skeleton->setRotation( XeCore::XeAngleHalfVector( 0.0f ) );
	else
	if( relativePos.X < 0.0f && relativePos.Y == 0.0f )
		m_skeleton->setRotation( XeCore::XeAngleHalfVector( 180.0f ) );
	else
	if( relativePos.Y > 0.0f && relativePos.X == 0.0f )
		m_skeleton->setRotation( XeCore::XeAngleHalfVector( 90.0f ) );
	else
	if( relativePos.Y < 0.0f && relativePos.X == 0.0f )
		m_skeleton->setRotation( XeCore::XeAngleHalfVector( 270.0f ) );
	m_skeleton->update();
}
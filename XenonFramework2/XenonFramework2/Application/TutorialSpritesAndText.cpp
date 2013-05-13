#include "../XeFramework/Base.h"
#include "../XeFramework/Manager.h"
#include "TutorialSpritesAndText.h"

RTTI_CLASS_DERIVATIONS(	TutorialSpritesAndText,
						RTTI_DERIVATION( IState ),
						RTTI_DERIVATIONS_END
						);

TutorialSpritesAndText::TutorialSpritesAndText():
RTTI_CLASS_DEFINE( TutorialSpritesAndText ),
m_sprite( 0 ),
m_text( 0 )
{
}

TutorialSpritesAndText::~TutorialSpritesAndText()
{
}

void TutorialSpritesAndText::onEnter( IProgressState* p )
{
	LOGNL( "* Enter state: TutorialSpritesAndText" );

	PROGRESS_STATE_UPDATE( p );

	m_sprite = xnew SpriteBatch::Sprite();
	m_sprite->setMaterial( GLOBAL.assets->get< Material >( "matLogo.xml" ) );
	m_sprite->setWidth( 512.0f );
	m_sprite->setHeight( 256.0f );
	m_sprite->setXoffset( 256.0f );
	m_sprite->setYoffset( 128.0f );
	m_sprite->setPosition( XeCore::XeHalfVector( 512.0f, 288.0f ) );
	GLOBAL.assets->get< SpriteBatch>( "sbOverlay.xml" )->attach( m_sprite );

	PROGRESS_STATE_UPDATE( p );

	m_text = xnew SpriteBatch::Text();
	m_text->setOrder( -1.0f );
	m_text->setMaterial( GLOBAL.assets->get< Material >( "matVerdana.xml" ) );
	m_text->setPosition( XeCore::XeHalfVector( 100.0f, 100.0f ) );
	m_text->build( GLOBAL.assets->get< Font>( "fntVerdana.xml" ), "Tutorial:\nSprites\nAnd\nText" );
	m_text->applyAlign( Font::aCenter );
	m_text->applyAlign( Font::aMiddle );
	m_text->changeColor( XeCore::XeHalfVector( 1.0f, 1.0f, 0.0f ), 0, 9 );
	GLOBAL.assets->get< SpriteBatch >( "sbOverlay.xml" )->attach( m_text );

	PROGRESS_STATE_UPDATE( p );
}

void TutorialSpritesAndText::onExit()
{
	LOGNL( "* Exit state: TutorialSpritesAndText" );

	DELETE_OBJECT( m_sprite );
	DELETE_OBJECT( m_text );
}

void TutorialSpritesAndText::onUpdate()
{
	GLOBAL.manager->update();

	m_sprite->setRotation( XeCore::XeAngleHalfVector( m_sprite->getRotation().Alpha + GLOBAL.engine->getDeltaTime() * 45.0f ) );
}

void TutorialSpritesAndText::onRender()
{
	GLOBAL.manager->render();
	GLOBAL.engine->flush();
	GLOBAL.engine->render();
}

void TutorialSpritesAndText::onInput()
{
	GLOBAL.manager->input();

	if( KEY_PRESSED( Input::kESC ) )
		GLOBAL.manager->popState();

	if( KEY_HOLD( Input::kCTRL ) && KEY_PRESSED( Input::kTYLDE ) )
	{
		ENTER_RUNTIME_DEBUGGER;
	}
}

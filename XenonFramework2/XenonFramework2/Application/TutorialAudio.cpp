#include "../XeFramework/Base.h"
#include "../XeFramework/Manager.h"
#include "../XeFramework/Music.h"
#include "TutorialAudio.h"

RTTI_CLASS_DERIVATIONS(	TutorialAudio,
						RTTI_DERIVATION( IState ),
						RTTI_DERIVATIONS_END
						);

TutorialAudio::TutorialAudio():
RTTI_CLASS_DEFINE( TutorialAudio ),
m_text( 0 )
{
}

TutorialAudio::~TutorialAudio()
{
}

void TutorialAudio::onEnter( IProgressState* p )
{
	LOGNL( "* Enter state: TutorialAudio" );

	PROGRESS_STATE_UPDATE( p );

	Music* m = GLOBAL.assets->get< Music >( "mscBackground.xml" );
	m->setRepeat( true );
	m->setVolume( 0.5f );
	m->play();

	PROGRESS_STATE_UPDATE( p );

	m_text = xnew SpriteBatch::Text();
	m_text->setOrder( -1.0f );
	m_text->setMaterial( GLOBAL.assets->get< Material >( "matVerdana.xml" ) );
	m_text->setPosition( XeCore::XeHalfVector( 512.0f, 288.0f ) );
	m_text->build();
	GLOBAL.assets->get< SpriteBatch>( "sbOverlay.xml" )->attach( m_text );

	PROGRESS_STATE_UPDATE( p );
}

void TutorialAudio::onExit()
{
	LOGNL( "* Exit state: TutorialAudio" );

	Music* m = GLOBAL.assets->get< Music >( "mscBackground.xml" );
	m->stop();

	DELETE_OBJECT( m_text );
}

void TutorialAudio::onUpdate()
{
	GLOBAL.manager->update();

	Music* m = GLOBAL.assets->get< Music >( "mscBackground.xml" );
	XeCore::XeString t;
	t.Format( "Tutorial: Audio\n\nVolume: %i%%\nPitch: %f\nTime: %f%%\n\nUp and Down arrows - change volume\nLeft and Right arrows - change pitch", (int)( m->getVolume() * 100.0f ), m->getPitch(), m->getLength() ? ( ( (float)m->getPosition() * 100.0f ) / (float)m->getLength() ) : 0.0f );
	m_text->rebuild( GLOBAL.assets->get< Font>( "fntVerdana.xml" ), t );
	m_text->applyAlign( Font::aCenter );
	m_text->applyAlign( Font::aMiddle );
}

void TutorialAudio::onRender()
{
	GLOBAL.manager->render();
	GLOBAL.engine->flush();
	GLOBAL.engine->render();
}

void TutorialAudio::onInput()
{
	GLOBAL.manager->input();

	Music* m = GLOBAL.assets->get< Music >( "mscBackground.xml" );

	if( KEY_HOLD( Input::kUP ) )
		m->setVolume( m->getVolume() + GLOBAL.engine->getDeltaTime() );
	else
	if( KEY_HOLD( Input::kDOWN ) )
		m->setVolume( m->getVolume() - GLOBAL.engine->getDeltaTime() );
	m->setVolume( CLAMP( m->getVolume(), 0.0f, 1.0f ) );

	if( KEY_HOLD( Input::kRIGHT ) )
		m->setPitch( m->getPitch() + GLOBAL.engine->getDeltaTime() );
	else
	if( KEY_HOLD( Input::kLEFT ) )
		m->setPitch( m->getPitch() - GLOBAL.engine->getDeltaTime() );

	if( KEY_PRESSED( Input::kSPACE ) )
	{
		if( m->isPlaying() )
			m->stop();
		else
			m->play();
	}

	if( KEY_PRESSED( Input::kESC ) )
		GLOBAL.manager->popState();

	if( KEY_HOLD( Input::kCTRL ) && KEY_PRESSED( Input::kTYLDE ) )
	{
		ENTER_RUNTIME_DEBUGGER;
	}
}

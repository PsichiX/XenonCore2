#include "../XeFramework/Base.h"
#include "../XeFramework/Manager.h"
#include "TutorialEffects.h"

RTTI_CLASS_DERIVATIONS(	TutorialEffects,
						RTTI_DERIVATION( IState ),
						RTTI_DERIVATIONS_END
						);

TutorialEffects::TutorialEffects():
RTTI_CLASS_DEFINE( TutorialEffects ),
m_sprite( 0 ),
m_text( 0 )
{
}

TutorialEffects::~TutorialEffects()
{
}

void TutorialEffects::onEnter( IProgressState* p )
{
	LOGNL( "* Enter state: TutorialEffects" );

	PROGRESS_STATE_UPDATE( p );

	SpriteBatch* overlay = GLOBAL.assets->get< SpriteBatch >( "sbOverlay.xml" );

	m_sprite = xnew SpriteBatch::Sprite();
	m_sprite->setMaterial( GLOBAL.assets->get< Material >( "matRocks.xml" ) );
	m_sprite->setWidth( 512.0f );
	m_sprite->setHeight( 512.0f );
	m_sprite->setXoffset( 256.0f );
	m_sprite->setYoffset( 256.0f );
	m_sprite->setPosition( XeCore::XeHalfVector( 512.0f, 288.0f ) );
	overlay->attach( m_sprite );

	PROGRESS_STATE_UPDATE( p );

	m_text = xnew ShapePool::Text();
	m_text->setMaterial( GLOBAL.assets->get< Material>( "matVerdana.xml" ) );
	m_text->setPosition( XeCore::XeHalfVector( 10.0f, 10.0f ) );
	m_text->setScale( XeCore::XeHalfVector( 0.5f, 0.5f ) );
	m_text->setOrder( -1.0f );
	m_text->build();
	overlay->attach( m_text );

	PROGRESS_STATE_UPDATE( p );
}

void TutorialEffects::onExit()
{
	LOGNL( "* Exit state: TutorialEffects" );

	DELETE_OBJECT( m_sprite );
	DELETE_OBJECT( m_text );
}

void TutorialEffects::onUpdate()
{
	GLOBAL.manager->update();

	Engine::WindowRect wr;
	GLOBAL.engine->getWindowRect( wr );
	m_sprite->getMaterial()->getProperties()->setPropertyVec(
		"in_LightDir",
		( INPUT.getMouseVec() - XeCore::XeHalfVector( 512.0f + (float)wr.x, 255.0f + (float)wr.y, -100.0f ) ).Normalize(),
		3
		);

	if( GLOBAL.engine->getFramesCounted() == 1 )
	{
		XeCore::XeString t;
		t.Format(	"Xenon Framework 2 - Tutorial: Effects\nFPS: %i\nDeltaTime: %f\n",
					GLOBAL.engine->getFps(),
					GLOBAL.engine->getDeltaTime()
					);
		m_text->rebuild(	GLOBAL.assets->get< Font>( "fntVerdana.xml" ),
							t
							);
		t.Clear();
	}
}

void TutorialEffects::onRender()
{
	GLOBAL.manager->render();
	GLOBAL.engine->flush();
	GLOBAL.engine->render();
}

void TutorialEffects::onInput()
{
	GLOBAL.manager->input();

	if( KEY_PRESSED( Input::kESC ) )
		GLOBAL.manager->popState();

	if( KEY_HOLD( Input::kCTRL ) && KEY_PRESSED( Input::kTYLDE ) )
	{
		ENTER_RUNTIME_DEBUGGER;
	}
}

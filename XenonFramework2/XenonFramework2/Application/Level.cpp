#include "../XeFramework/Base.h"
#include "../XeFramework/Manager.h"
#include "../XeFramework/Music.h"
#include "../XeCore/Base/XeTime.h"
#include "../XeFramework/RenderTechnique.h"
#include "Level.h"
#include "Logo.h"
#include "Player.h"
#include "Crate.h"

RTTI_CLASS_DERIVATIONS(	Level,
						RTTI_DERIVATION( IState ),
						RTTI_DERIVATIONS_END
						);

Level::Level():
RTTI_CLASS_DEFINE( Level ),
m_updateTime( 0 ),
m_renderTime( 0 ),
m_text( 0 ),
m_focus( 0.5f ),
m_bg( 0 ),
m_depthSprite( 0 )
{
}

Level::~Level()
{	
}

void Level::onEnter( IProgressState* p )
{
	LOGNL( "* Enter state: Level" );

	PROGRESS_STATE_UPDATE( p );

	XeCore::XeMath::RandomReset();

	GLOBAL.collisions->setActive( false );

	//=== SCENES ===

	SpriteBatch* sprites = GLOBAL.assets->get< SpriteBatch>( "sbSprites.xml" );

	PROGRESS_STATE_UPDATE( p );

	GLOBAL.assets->get< RenderTechnique>( "rtDefault.xml" )->setRenderable( false );

	PROGRESS_STATE_UPDATE( p );

	GLOBAL.assets->get< RenderTechnique>( "rtDepthOfField.xml" )->setRenderable( true );

	PROGRESS_STATE_UPDATE( p );

	GLOBAL.assets->get< RenderTechnique>( "rtDepth.xml" )->setRenderable( false );

	SpriteBatch* overlay = GLOBAL.assets->get< SpriteBatch>( "sbOverlay.xml" );

	PROGRESS_STATE_UPDATE( p );

	//=== ACTORS ===

	m_bg = xnew SpriteBatch::Sprite();
	m_bg->setPosition( XeCore::XeHalfVector( 0.0f, 0.0f, -0.99f ) );
	m_bg->setWidth( 1024.0f );
	m_bg->setHeight( 576.0f );
	m_bg->setMaterial( GLOBAL.assets->get< Material>( "matBackground.xml" ) );
	sprites->attach( m_bg );

	PROGRESS_STATE_UPDATE( p );

	Logo* logo = xnew Logo();
	GLOBAL.actors->attach( NameID( "logo" ), logo );

	PROGRESS_STATE_UPDATE( p );

	Player* player = xnew Player( XeCore::XeHalfVector( 1024.0f * 0.5f, 576.0f * 0.5f ) );
	GLOBAL.actors->attach( NameID( "player" ), player );

	PROGRESS_STATE_UPDATE( p );

	REPEAT( 100 )
	{
		float x = (float)XeCore::XeMath::Random( 1024.0 - 64.0 ) + 32.0f;
		float y = (float)XeCore::XeMath::Random( 576.0 - 64.0 ) + 32.0f;
		float z = max( -0.9f, min( 0.9f, (float)( XeCore::XeMath::Random( 2.0 ) - 1.0 ) ) );
		float a = (float)XeCore::XeMath::Random( 360.0 );
		float vx = (float)XeCore::XeMath::Random( 128.0 ) - 64.0f;
		float vy = (float)XeCore::XeMath::Random( 128.0 ) - 64.0f;
		float r = (float)XeCore::XeMath::Random( 90.0 ) - 45.0f;
		Crate* crate = xnew Crate( XeCore::XeHalfVector( x, y, z ), a, vx, vy, r );
		GLOBAL.actors->attach( NameID( "crate" ), crate );

		PROGRESS_STATE_UPDATE( p );
	}

	m_text = xnew ShapePool::Text();
	m_text->setMaterial( GLOBAL.assets->get< Material>( "matVerdana.xml" ) );
	m_text->setPosition( XeCore::XeHalfVector( 10.0f, 10.0f ) );
	m_text->setScale( XeCore::XeHalfVector( 0.5f, 0.5f ) );
	m_text->setOrder( -1.0f );
	m_text->build();
	overlay->attach( m_text );

	PROGRESS_STATE_UPDATE( p );

	m_depthSprite = xnew SpriteBatch::CanvasSprite( sprites->getCanvas(), GLOBAL.assets->get< Effect>( "effSpriteBatchDepth.xml" ) );
	m_depthSprite->getMaterial()->getProperties()->setPropertySampler( "in_DepthTex", 1 );
	m_depthSprite->setPosition( XeCore::XeHalfVector( 1024.0f, 0.0f ) );
	m_depthSprite->setXoffset( 1024.0f );
	m_depthSprite->setScale( XeCore::XeHalfVector( 0.2f, 0.2f ) );
	m_depthSprite->setRenderable( false );

	PROGRESS_STATE_UPDATE( p );
}

void Level::onExit()
{
	LOGNL( "* Exit state: Level" );

	DELETE_OBJECT( m_bg );

	DELETE_OBJECT( m_text );

	DELETE_OBJECT( m_depthSprite );
}

void Level::onUpdate()
{
	LONGLONG time = XeCore::XeTime::GetMilisecs();

	GLOBAL.manager->update();

	if( GLOBAL.engine->getFramesCounted() == 1 || ( KEY_HOLD( 'Z' ) || KEY_HOLD( 'X' ) ) )
	{
		XeCore::XeString t;
		t.Format(	"Xenon Framework 2 - Game\nFPS: %i\nDeltaTime: %f\nFocus: %f\nUpdate: %i ms\nRender: %i ms\nArrows - Movement\nSpace - Toggle DOF mode\nZ - Increase focus\nX - Decrease focus\nD - Toggle depth visualization\nH - Toggle HUD",
					GLOBAL.engine->getFps(),
					GLOBAL.engine->getDeltaTime(),
					m_focus,
					m_updateTime,
					m_renderTime
					);
		m_text->rebuild(	GLOBAL.assets->get< Font>( "fntVerdana.xml" ),
							t,
							XeCore::XeHalfVector( 1.0f, 1.0f, 1.0f )
							);
		t.Clear();
	}

	m_updateTime = XeCore::XeTime::GetMilisecs() - time;
}

void Level::onRender()
{
	LONGLONG time = XeCore::XeTime::GetMilisecs();

	GLOBAL.manager->render();
	GLOBAL.engine->flush();
	GLOBAL.engine->render();

	m_renderTime = XeCore::XeTime::GetMilisecs() - time;
}

void Level::onInput()
{
	GLOBAL.manager->input();

	if( KEY_PRESSED( VK_RETURN ) )
		GLOBAL.collisions->setActive( !GLOBAL.collisions->isActive() );

	if( KEY_PRESSED( Input::kH ) )
		GLOBAL.assets->get< SpriteBatch>( "sbOverlay.xml" )->setRenderable( !GLOBAL.assets->get< SpriteBatch>( "sbOverlay.xml" )->isRenderable() );

	if( KEY_PRESSED( VK_SPACE ) )
	{
		GLOBAL.assets->get< RenderTechnique>( "rtDefault.xml" )->setRenderable( !GLOBAL.assets->get< RenderTechnique>( "rtDefault.xml" )->isRenderable() );
		GLOBAL.assets->get< RenderTechnique>( "rtDepthOfField.xml" )->setRenderable( !GLOBAL.assets->get< RenderTechnique>( "rtDepthOfField.xml" )->isRenderable() );
	}

	if( KEY_PRESSED( 'D' ) )
		GLOBAL.assets->get< RenderTechnique>( "rtDepth.xml" )->setRenderable( !GLOBAL.assets->get< RenderTechnique>( "rtDepth.xml" )->isRenderable() );

	if( KEY_HOLD( 'Z' ) || KEY_HOLD( 'X' ) )
	{
		if( KEY_HOLD( 'Z' ) )
			m_focus += GLOBAL.engine->getDeltaTime() * 0.5f;
		else
		if( KEY_HOLD( 'X' ) )
			m_focus -= GLOBAL.engine->getDeltaTime() * 0.5f;
		m_focus = max( 0.0f, min( 1.0f, m_focus ) );
		RenderTechnique* rt = GLOBAL.assets->get< RenderTechnique>( "rtDepthOfField.xml" );
		rt->getPassMaterial( rt->getPass( NameID( "final" ) ) )->getProperties()->setPropertyVec( "in_Focus", XeCore::XeHalfVector( m_focus ), 1 );
	}

	if( KEY_PRESSED( Input::kESC ) )
		GLOBAL.manager->popState();

	if( KEY_HOLD( Input::kCTRL ) && KEY_PRESSED( Input::kTYLDE ) )
	{
		ENTER_RUNTIME_DEBUGGER;
	}
}

#include "../XeFramework/Base.h"
#include "../XeFramework/Manager.h"
#include "../XeCore/Base/XeTime.h"
#include "../XeFramework/RenderTechnique.h"
#include "../XeFramework/Camera3D.h"
#include "TutorialRenderTechnique.h"

#define D2R(v) ( ( v * float( PI ) ) / 180.0f )

RTTI_CLASS_DERIVATIONS(	TutorialRenderTechnique,
						RTTI_DERIVATION( IState ),
						RTTI_DERIVATIONS_END
						);

TutorialRenderTechnique::TutorialRenderTechnique():
RTTI_CLASS_DEFINE( TutorialRenderTechnique ),
m_updateTime( 0 ),
m_renderTime( 0 ),
m_text( 0 ),
m_sunAlpha( 0.0f ),
m_sunBeta( 45.0f ),
m_sunSpd( 0.0f ),
m_sunTime( 0.0f )
{
}

TutorialRenderTechnique::~TutorialRenderTechnique()
{
}

void TutorialRenderTechnique::onEnter( IProgressState* p )
{
	LOGNL( "* Enter state: TutorialRenderTechnique" );

	PROGRESS_STATE_UPDATE( p );

	RenderTechnique* rt = GLOBAL.assets->get< RenderTechnique>( "rtAtmos.xml" );
	((Camera3D*)rt->getPassCamera( rt->getPass( NameID( "final" ) ) ))->setBeta( -22.5f );
	((Camera3D*)rt->getPassCamera( rt->getPass( NameID( "final" ) ) ))->apply();

	PROGRESS_STATE_UPDATE( p );

	SpriteBatch* overlay = GLOBAL.assets->get< SpriteBatch>( "sbOverlay.xml" );

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

void TutorialRenderTechnique::onExit()
{
	LOGNL( "* Exit state: TutorialRenderTechnique" );

	DELETE_OBJECT( m_text );
}

void TutorialRenderTechnique::onUpdate()
{
	LONGLONG time = XeCore::XeTime::GetMilisecs();

	GLOBAL.manager->update();

	if( GLOBAL.engine->getFramesCounted() == 1 || ( KEY_HOLD( Input::kZ ) || KEY_HOLD( Input::kX ) ) )
	{
		XeCore::XeString t;
		t.Format(	"Xenon Framework 2 - Tutorial: Render techniques\nFPS: %i\nDeltaTime: %f\nSun speed: %f\nUpdate: %i ms\nRender: %i ms\nX - Increase sun speed\nZ - Decrease sun speed\nH - Toggle HUD",
					GLOBAL.engine->getFps(),
					GLOBAL.engine->getDeltaTime(),
					m_sunSpd,
					(int)m_updateTime,
					(int)m_renderTime
					);
		m_text->rebuild(	GLOBAL.assets->get< Font>( "fntVerdana.xml" ),
							t
							);
		t.Clear();
	}

	m_sunTime += GLOBAL.engine->getDeltaTime() * m_sunSpd;
	m_sunAlpha = sin( m_sunTime ) * 20.0f;
	m_sunBeta = cos( m_sunTime ) * 40.0f;
	XeCore::XeHalfVector v( cos( D2R( m_sunAlpha ) ) * cos( D2R( m_sunBeta ) ), sin( D2R( m_sunAlpha ) ) * cos( D2R( m_sunBeta ) ), sin( D2R( m_sunBeta ) ) );
	RenderTechnique* rt = GLOBAL.assets->get< RenderTechnique>( "rtAtmos.xml" );
	rt->getPassMaterial( rt->getPass( NameID( "final" ) ) )->getProperties()->setPropertyVec( "in_SunPos", v, 3 );

	m_updateTime = XeCore::XeTime::GetMilisecs() - time;
}

void TutorialRenderTechnique::onRender()
{
	LONGLONG time = XeCore::XeTime::GetMilisecs();

	GLOBAL.manager->render();
	GLOBAL.engine->flush();
	GLOBAL.engine->render();

	m_renderTime = XeCore::XeTime::GetMilisecs() - time;
}

void TutorialRenderTechnique::onInput()
{
	GLOBAL.manager->input();

	if( KEY_PRESSED( Input::kH ) )
		GLOBAL.assets->get< SpriteBatch>( "sbOverlay.xml" )->setRenderable( !GLOBAL.assets->get< SpriteBatch>( "sbOverlay.xml" )->isRenderable() );

	if( KEY_HOLD( Input::kZ ) )
		m_sunSpd -= GLOBAL.engine->getDeltaTime() * 0.2f;
	if( KEY_HOLD( Input::kX ) )
		m_sunSpd += GLOBAL.engine->getDeltaTime() * 0.2f;

	if( KEY_PRESSED( Input::kESC ) )
		GLOBAL.manager->popState();

	if( KEY_HOLD( Input::kCTRL ) && KEY_PRESSED( Input::kTYLDE ) )
	{
		ENTER_RUNTIME_DEBUGGER;
	}
}

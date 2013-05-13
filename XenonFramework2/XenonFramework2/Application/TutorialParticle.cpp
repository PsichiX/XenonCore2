#include "../XeFramework/Base.h"
#include "../XeFramework/Manager.h"
#include "TutorialParticle.h"
#include "../XeFramework/Camera2D.h"
#include "../XeFramework/SpriteBatch.h"

RTTI_CLASS_DERIVATIONS(	TutorialParticle,
						RTTI_DERIVATION( IState ),
						RTTI_DERIVATIONS_END
						);

TutorialParticle::TutorialParticle():
m_text( 0 ),
m_partControler( 0 ),
RTTI_CLASS_DEFINE( TutorialParticle )
{
}

TutorialParticle::~TutorialParticle()
{
}

void TutorialParticle::onEnter( IProgressState* p )
{
	LOGNL( "* Enter state: TutorialParticle" );

	ParticlesStream* particles = GLOBAL.assets->get< ParticlesStream >( "parParticles.xml" );
	particles->getMaterial()->setBlending( Material::bSource, XeCore::XE_RENDER_BLEND_SRC_ALPHA );
	particles->getMaterial()->setBlending( Material::bDestination, XeCore::XE_RENDER_BLEND_ONE );

	m_partControler = xnew ParticlesStream::UnitControler();
	m_partControler->scale.Reserve( 3 );
	m_partControler->scale[ 1 ] = XeCore::XeHalfVector( 64.0f, 64.0f );
	m_partControler->direction.Reserve( 1 );

	PROGRESS_STATE_UPDATE( p );

	m_text = xnew ShapePool::Text();
	m_text->setOrder( -1.0f );
	m_text->setMaterial( GLOBAL.assets->get< Material >( "matVerdana.xml" ) );
	m_text->setPosition( XeCore::XeHalfVector( 10.0f, 10.0f ) );
	m_text->build();
	GLOBAL.assets->get< SpriteBatch >( "sbOverlay.xml" )->attach( m_text );

	PROGRESS_STATE_UPDATE( p );
}

void TutorialParticle::onExit()
{
	LOGNL( "* Exit state: TutorialParticle" );

	DELETE_OBJECT( m_partControler );
	DELETE_OBJECT( m_text );
}

void TutorialParticle::onUpdate()
{
	GLOBAL.manager->update();

	ParticlesStream::GenerationDescription d;
	d.colorMax = XeCore::XeHalfVector( 1.0f, 1.0f, 0.5f, 0.25f );
	d.colorMin = XeCore::XeHalfVector( 1.0f, 1.0f, 1.0f, 0.25f );
	d.countMax = static_cast<unsigned int>(1000.0f * GLOBAL.engine->getDeltaTime());
	d.countMin = static_cast<unsigned int>(100.0f * GLOBAL.engine->getDeltaTime());
	d.lifetimeMax = 4.0f;
	d.lifetimeMin = 2.0f;
	d.offsetMax = XeCore::XeHalfVector();
	d.offsetMin = XeCore::XeHalfVector();
	d.position = INPUT.getMouseVec( true );
	d.scaleMax = XeCore::XeHalfVector( 32.0f, 32.0f );
	d.scaleMin = XeCore::XeHalfVector( 16.0f, 16.0f );
	d.velocityMax = XeCore::XeHalfVector( 100.0f, 100.0f );
	d.velocityMin = XeCore::XeHalfVector( -100.0f, -100.0f );
	GLOBAL.assets->get< ParticlesStream >( "parParticles.xml" )->generate( d, m_partControler );

	if( GLOBAL.engine->getFramesCounted() == 1 )
	{
		XeCore::XeString s;
		s.Format(
			"FPS: %i\nDT: %f\nCount: %u",
			GLOBAL.engine->getFps(),
			GLOBAL.engine->getDeltaTime(),
			GLOBAL.assets->get< ParticlesStream >( "parParticles.xml" )->getCount()
			);
		m_text->rebuild( GLOBAL.assets->get< Font >( "fntVerdana.xml" ), s );
		s.Clear();
	}
}

void TutorialParticle::onRender()
{
	GLOBAL.manager->render();
	GLOBAL.engine->flush();
	GLOBAL.engine->render();
}

void TutorialParticle::onInput()
{
	GLOBAL.manager->input();

	if( KEY_PRESSED( Input::kESC ) )
		GLOBAL.manager->popState();

	if( KEY_HOLD( Input::kCTRL ) && KEY_PRESSED( Input::kTYLDE ) )
	{
		ENTER_RUNTIME_DEBUGGER;
	}
}

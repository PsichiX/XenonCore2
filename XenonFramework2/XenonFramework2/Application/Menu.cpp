#include "../XeFramework/Base.h"
#include "../XeFramework/Manager.h"
#include "Menu.h"
#include "Level.h"
#include "TutorialBasic.h"
#include "TutorialSpritesAndText.h"
#include "TutorialAudio.h"
#include "TutorialEffects.h"
#include "TutorialRenderTechnique.h"
#include "TutorialParticle.h"

RTTI_CLASS_DERIVATIONS(	Menu,
						RTTI_DERIVATION( IState ),
						RTTI_DERIVATIONS_END
						);

Menu::Menu():
RTTI_CLASS_DEFINE( Menu ),
m_lvlbg( 0 )
{
	for( unsigned int i = 0; i < levelsCount; i++ )
		m_lvls[ i ] = 0;
}

Menu::~Menu()
{
}

void Menu::onEnter( IProgressState* p )
{
	LOGNL( "* Enter state: Menu" );

	PROGRESS_STATE_UPDATE( p );

	SpriteBatch* scene = GLOBAL.assets->get< SpriteBatch>( "sbMenu.xml" );

	PROGRESS_STATE_UPDATE( p );

	m_lvlbg = xnew SpriteBatch::Sprite();
	m_lvlbg->setColor( XeCore::XeHalfVector( 0.0f, 0.0f, 1.0f ) );
	m_lvlbg->setMaterial( GLOBAL.assets->get< Material>( "matMenu.xml" ) );
	m_lvlbg->setOrder( 1.0f );
	scene->attach( m_lvlbg );

	int lid( 0 );

	PROGRESS_STATE_UPDATE( p );

	m_lvls[ lid ] = xnew SpriteBatch::Text();
	m_lvls[ lid ]->setMaterial( GLOBAL.assets->get< Material>( "matVerdana.xml" ) );
	m_lvls[ lid ]->setPosition( XeCore::XeHalfVector( 512.0f, 20.0f ) );
	m_lvls[ lid ]->build(
		GLOBAL.assets->get< Font>( "fntVerdana.xml" ),
		"Game"
		);
	m_lvls[ lid ]->changeColor( XeCore::XeHalfVector( 1.0f, 1.0f, 0.0f ) );
	m_lvls[ lid ]->applyAlign( Font::aCenter );

	lid++;

	PROGRESS_STATE_UPDATE( p );
	
	m_lvls[ lid ] = xnew SpriteBatch::Text();
	m_lvls[ lid ]->setMaterial( GLOBAL.assets->get< Material>( "matVerdana.xml" ) );
	m_lvls[ lid ]->setPosition( XeCore::XeHalfVector( 512.0f, 60.0f ) );
	m_lvls[ lid ]->build(
		GLOBAL.assets->get< Font>( "fntVerdana.xml" ),
		"Tutorial #1: Basic"
		);
	m_lvls[ lid ]->changeColor( XeCore::XeHalfVector( 1.0f, 1.0f, 0.0f ), 0, 12 );
	m_lvls[ lid ]->applyAlign( Font::aCenter );

	lid++;

	PROGRESS_STATE_UPDATE( p );

	m_lvls[ lid ] = xnew SpriteBatch::Text();
	m_lvls[ lid ]->setMaterial( GLOBAL.assets->get< Material>( "matVerdana.xml" ) );
	m_lvls[ lid ]->setPosition( XeCore::XeHalfVector( 512.0f, 100.0f ) );
	m_lvls[ lid ]->build(
		GLOBAL.assets->get< Font>( "fntVerdana.xml" ),
		"Tutorial #2: Sprites and text"
		);
	m_lvls[ lid ]->changeColor( XeCore::XeHalfVector( 1.0f, 1.0f, 0.0f ), 0, 12 );
	m_lvls[ lid ]->applyAlign( Font::aCenter );

	lid++;

	PROGRESS_STATE_UPDATE( p );

	m_lvls[ lid ] = xnew SpriteBatch::Text();
	m_lvls[ lid ]->setMaterial( GLOBAL.assets->get< Material>( "matVerdana.xml" ) );
	m_lvls[ lid ]->setPosition( XeCore::XeHalfVector( 512.0f, 140.0f ) );
	m_lvls[ lid ]->build(
		GLOBAL.assets->get< Font>( "fntVerdana.xml" ),
		"Tutorial #3: Audio"
		);
	m_lvls[ lid ]->changeColor( XeCore::XeHalfVector( 1.0f, 1.0f, 0.0f ), 0, 12 );
	m_lvls[ lid ]->applyAlign( Font::aCenter );

	lid++;

	PROGRESS_STATE_UPDATE( p );

	m_lvls[ lid ] = xnew SpriteBatch::Text();
	m_lvls[ lid ]->setMaterial( GLOBAL.assets->get< Material>( "matVerdana.xml" ) );
	m_lvls[ lid ]->setPosition( XeCore::XeHalfVector( 512.0f, 180.0f ) );
	m_lvls[ lid ]->build(
		GLOBAL.assets->get< Font>( "fntVerdana.xml" ),
		"Tutorial #4: Effects"
		);
	m_lvls[ lid ]->changeColor( XeCore::XeHalfVector( 1.0f, 1.0f, 0.0f ), 0, 12 );
	m_lvls[ lid ]->applyAlign( Font::aCenter );

	lid++;

	PROGRESS_STATE_UPDATE( p );

	m_lvls[ lid ] = xnew SpriteBatch::Text();
	m_lvls[ lid ]->setMaterial( GLOBAL.assets->get< Material>( "matVerdana.xml" ) );
	m_lvls[ lid ]->setPosition( XeCore::XeHalfVector( 512.0f, 220.0f ) );
	m_lvls[ lid ]->build(
		GLOBAL.assets->get< Font>( "fntVerdana.xml" ),
		"Tutorial #5: Render techniques"
		);
	m_lvls[ lid ]->changeColor( XeCore::XeHalfVector( 1.0f, 1.0f, 0.0f ), 0, 12 );
	m_lvls[ lid ]->applyAlign( Font::aCenter );

	lid++;

	PROGRESS_STATE_UPDATE( p );

	m_lvls[ lid ] = xnew SpriteBatch::Text();
	m_lvls[ lid ]->setMaterial( GLOBAL.assets->get< Material>( "matVerdana.xml" ) );
	m_lvls[ lid ]->setPosition( XeCore::XeHalfVector( 512.0f, 260.0f ) );
	m_lvls[ lid ]->build(
		GLOBAL.assets->get< Font>( "fntVerdana.xml" ),
		"Tutorial #6: Particles"
		);
	m_lvls[ lid ]->changeColor( XeCore::XeHalfVector( 1.0f, 1.0f, 0.0f ), 0, 12 );
	m_lvls[ lid ]->applyAlign( Font::aCenter );

	lid++;

	PROGRESS_STATE_UPDATE( p );

	for( unsigned int i = 0; i < levelsCount; i++ )
		scene->attach( m_lvls[ i ] );

	PROGRESS_STATE_UPDATE( p );
}

void Menu::onExit()
{
	LOGNL( "* Exit state: Menu" );
	
	DELETE_OBJECT( m_lvlbg );

	for( unsigned int i = 0; i < levelsCount; i++ )
		DELETE_OBJECT( m_lvls[ i ] );
}

void Menu::onUpdate()
{
	GLOBAL.manager->update();
}

void Menu::onRender()
{
	GLOBAL.manager->render();
	GLOBAL.engine->flush();
	GLOBAL.engine->render();
}

void Menu::onInput()
{
	GLOBAL.manager->input();

	for( unsigned int i = 0; i < levelsCount; i++ )
		if( mouseTextOver( m_lvls[ i ] ) )
		{
			applyBgDim( m_lvls[ i ] );
			if( BUTTON_RELEASED( InputManager::ibLeft ) )
				gotoTextLvl( i );
		}

	if( KEY_PRESSED( Input::kESC ) )
		GLOBAL.manager->popState();

	if( KEY_PRESSED( Input::kSPACE ) )
		GLOBAL.manager->changeState( xnew Menu() );

	if( KEY_HOLD( Input::kCTRL ) && KEY_PRESSED( Input::kTYLDE ) )
	{
		ENTER_RUNTIME_DEBUGGER;
	}
}

bool Menu::mouseTextOver( SpriteBatch::Text* t )
{
	XASSERT( t, "Text cannot be empty" );

	Engine::WindowRect wr;
	GLOBAL.engine->getWindowRect( wr );
	XeCore::XeHalfVector wp( static_cast< float >(wr.x), static_cast< float >(wr.y) );
	XeCore::XeHalfVector m = INPUT.getMouseVec() - wp;
	float tminx = t->getPosition().X - t->getOffsetX();
	float tminy = t->getPosition().Y - t->getOffsetY();
	float tmaxx = tminx + t->getWidth();
	float tmaxy = tminy + t->getHeight();
	return( m.X >= tminx && m.Y >= tminy && m.X < tmaxx && m.Y < tmaxy );
}

void Menu::applyBgDim( SpriteBatch::Text* t )
{
	if( t )
	{
		m_lvlbg->setPosition( t->getPosition() - XeCore::XeHalfVector( t->getOffsetX(), t->getOffsetY() ) );
		m_lvlbg->setWidth( t->getWidth() );
		m_lvlbg->setHeight( t->getHeight() );
	}
	else
	{
		m_lvlbg->setWidth( 0.0f );
		m_lvlbg->setHeight( 0.0f );
	}
}

void Menu::gotoTextLvl( unsigned int i )
{
	if( i == 0 )
		GLOBAL.manager->pushState( xnew Level() );
	else
	if( i == 1 )
		GLOBAL.manager->pushState( xnew TutorialBasic() );
	else
	if( i == 2 )
		GLOBAL.manager->pushState( xnew TutorialSpritesAndText() );
	else
	if( i == 3 )
		GLOBAL.manager->pushState( xnew TutorialAudio() );
	else
	if( i == 4 )
		GLOBAL.manager->pushState( xnew TutorialEffects() );
	else
	if( i == 5 )
		GLOBAL.manager->pushState( xnew TutorialRenderTechnique() );
	else
	if( i == 6 )
		GLOBAL.manager->pushState( xnew TutorialParticle() );
}

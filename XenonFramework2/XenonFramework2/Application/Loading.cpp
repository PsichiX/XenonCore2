#include "Loading.h"
#include "../XeFramework/Manager.h"

RTTI_CLASS_DERIVATIONS(	Loading,
						RTTI_DERIVATION( IProgressState ),
						RTTI_DERIVATIONS_END
						);

Loading::Loading():
RTTI_CLASS_DEFINE( Loading ),
m_text( 0 ),
m_dots( 0 )
{
}

Loading::~Loading()
{
}

void Loading::onEnter()
{
	GLOBAL.assetsLoading->get< SpriteBatch >( "sbLoading.xml", true )->setRenderable( true );
	m_text = xnew SpriteBatch::Text();
	m_text->setMaterial( GLOBAL.assetsLoading->get< Material >( "matVerdana.xml", true ) );
	m_text->setPosition( XeCore::XeHalfVector( 512.0f, 288.0f ) );
	m_text->build();
	GLOBAL.assetsLoading->get< SpriteBatch >( "sbLoading.xml" )->attach( m_text );
	GLOBAL.assetsLoading->get< Font >( "fntVerdana.xml", true );
}

void Loading::onExit()
{
	GLOBAL.assetsLoading->get< SpriteBatch >( "sbLoading.xml", true )->setRenderable( false );
	DELETE_OBJECT( m_text );
}

bool Loading::onProgress()
{
	m_dots++;
	if( m_dots > 3 )
		m_dots = 0;

	XeCore::XeString t;
	t << "LOADING";
	for( int i = 0; i < m_dots; i++ )
		t << ".";
	m_text->rebuild(
		GLOBAL.assetsLoading->get< Font >( "fntVerdana.xml", true ),
		t
		);
	m_text->applyAlign( Font::aCenter );
	m_text->applyAlign( Font::aMiddle );

	GLOBAL.assetsLoading->get< SpriteBatch >( "sbLoading.xml", true )->update();
	GLOBAL.assetsLoading->get< SpriteBatch >( "sbLoading.xml", true )->render();

	GLOBAL.engine->flush();
	GLOBAL.engine->render();

	return( true );
}

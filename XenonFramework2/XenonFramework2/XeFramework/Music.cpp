#include "Music.h"
#include "AudioManager.h"
#include "Asset.h"

RTTI_CLASS_DERIVATIONS(	Music,
						RTTI_DERIVATION( Asset ),
						RTTI_DERIVATION( Audio ),
						RTTI_DERIVATIONS_END
						);

Music::Music( NameID& name, AudioManager* m ):
RTTI_CLASS_DEFINE( Music ),
m_manager( m ),
m_name( name ),
m_music( 0 ),
m_file( 0 )
{
	m_manager->INamedItemsManager< NameID, Audio >::attach( m_name, this );
}

Music::~Music()
{
	m_music = 0;
	m_file = 0;

	m_manager->INamedItemsManager< NameID, Audio >::detach( m_name );

	Asset::release( this );
}

bool Music::load( const char* fname )
{
	m_music = audiere::OpenSound( m_manager->getDevice(), fname, true );
	return( m_music );
}

bool Music::load( void* data, int size )
{
	m_file = audiere::CreateMemoryFile( data, size );
	if( !m_file )
		return( false );
	m_music = audiere::OpenSound( m_manager->getDevice(), m_file, true );
	return( m_music );
}

void Music::free()
{
	m_music = 0;
	m_file = 0;
}

void Music::play()
{
	if( !m_music )
		return;
	m_music->play();
}

void Music::stop()
{
	if( !m_music )
		return;
	m_music->stop();
}

void Music::reset()
{
	if( !m_music )
		return;
	m_music->reset();
}

bool Music::isPlaying()
{
	return( m_music ? m_music->isPlaying() : false );
}

void Music::setVolume( float v )
{
	if( !m_music )
		return;
	m_music->setVolume( v );
}

void Music::setPan( float v )
{
	if( !m_music )
		return;
	m_music->setPan( v );
}

void Music::setPitch( float v )
{
	if( !m_music )
		return;
	m_music->setPitchShift( v );
}

void Music::setPosition( int f )
{
	if( !m_music )
		return;
	m_music->setPosition( f );
}

void Music::setRepeat( bool m )
{
	if( !m_music )
		return;
	m_music->setRepeat( m );
}

float Music::getVolume()
{
	return( m_music ? m_music->getVolume() : 0.0f );
}

float Music::getPan()
{
	return( m_music ? m_music->getPan() : 0.0f );
}

float Music::getPitch()
{
	return( m_music ? m_music->getPitchShift() : 0.0f );
}

int Music::getPosition()
{
	return( m_music ? m_music->getPosition() : 0 );
}

int Music::getLength()
{
	return( m_music ? m_music->getLength() : 0 );
}

Asset* Music::onLoad( AssetManager* manager, XeCore::XeString& name, Params& params, bool keepAlways )
{
	Music* t = xnew Music( NameID( name ), Global::use().audio );
	if( t->load( params[ "path" ].getValue() ) )
	{
		ASSET_SET_PURE_POINTER( t );
		return( t );
	}
	else
	{
		DELETE_OBJECT( t );
		return( 0 );
	}
}

void Music::onUnload()
{
}

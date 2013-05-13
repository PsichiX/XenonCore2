#include "Sound.h"
#include "AudioManager.h"
#include "Asset.h"

RTTI_CLASS_DERIVATIONS(	Sound,
						RTTI_DERIVATION( Asset ),
						RTTI_DERIVATION( Audio ),
						RTTI_DERIVATIONS_END
						);

Sound::Sound( NameID& name, AudioManager* m ):
RTTI_CLASS_DEFINE( Sound ),
m_manager( m ),
m_name( name ),
m_sound( 0 ),
m_file( 0 )
{
	m_manager->INamedItemsManager< NameID, Audio >::attach( m_name, this );
}

Sound::~Sound()
{
	m_sound = 0;
	m_file = 0;

	m_manager->INamedItemsManager< NameID, Audio >::detach( m_name );

	Asset::release( this );
}

bool Sound::load( const char* fname )
{
	m_sound = audiere::OpenSoundEffect( m_manager->getDevice(), fname, audiere::MULTIPLE );
	return( m_sound );
}

bool Sound::load( void* data, int size )
{
	m_file = audiere::CreateMemoryFile( data, size );
	if( !m_file )
		return( false );
	m_sound = audiere::OpenSoundEffect( m_manager->getDevice(), m_file, audiere::MULTIPLE );
	return( m_sound );
}

void Sound::free()
{
	m_sound = 0;
	m_file = 0;
}

void Sound::play()
{
	if( !m_sound )
		return;
	m_sound->play();
}

void Sound::stop()
{
	if( !m_sound )
		return;
	m_sound->stop();
}

void Sound::setVolume( float v )
{
	if( !m_sound )
		return;
	m_sound->setVolume( v );
}

void Sound::setPan( float v )
{
	if( !m_sound )
		return;
	m_sound->setPan( v );
}

void Sound::setPitch( float v )
{
	if( !m_sound )
		return;
	m_sound->setPitchShift( v );
}

float Sound::getVolume()
{
	return( m_sound ? m_sound->getVolume() : 0.0f );
}

float Sound::getPan()
{
	return( m_sound ? m_sound->getPan() : 0.0f );
}

float Sound::getPitch()
{
	return( m_sound ? m_sound->getPitchShift() : 0.0f );
}

Asset* Sound::onLoad( AssetManager* manager, XeCore::XeString& name, Params& params, bool keepAlways )
{
	Sound* t = xnew Sound( NameID( name ), Global::use().audio );
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

void Sound::onUnload()
{
}

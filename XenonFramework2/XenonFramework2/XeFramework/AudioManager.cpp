#include "AudioManager.h"
#include "Music.h"
#include "Sound.h"

RTTI_CLASS_DERIVATIONS(	AudioManager,
						RTTI_DERIVATIONS_END
						);

AudioManager::AudioManager():
RTTI_CLASS_DEFINE( AudioManager )
{
	m_device = audiere::OpenDevice();
	XASSERT( m_device, "Cannot open device!");
}

AudioManager::~AudioManager()
{
	XeCore::XeElementPointer< Pair > e = access().FirstPointer();
	while( !e.IsEmpty() )
	{
		remove( e().key );
		e = access().FirstPointer();
	}
	m_device = 0;
}

audiere::AudioDevicePtr AudioManager::getDevice()
{
	return( m_device );
}

Music* AudioManager::getMusic( NameID& name )
{
	Audio* a = find( name );
	if( a && IRtti::isDerived< Music >( a ) )
		return( RTTI_TREAT_AS( a, Music ) );
	return( 0 );
}

Sound* AudioManager::getSound( NameID& name )
{
	Audio* a = find( name );
	if( a && IRtti::isDerived< Sound >( a ) )
		return( RTTI_TREAT_AS( a, Sound ) );
	return( 0 );
}

RTTI_CLASS_DERIVATIONS(	Audio,
						RTTI_DERIVATIONS_END
						);

Audio::Audio():
RTTI_CLASS_DEFINE( Audio )
{
}

Audio::~Audio()
{
}
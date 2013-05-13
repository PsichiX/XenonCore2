#pragma once

#include "IRtti.h"
#include "Audiere/audiere.h"
#include "AudioManager.h"
#include "Asset.h"

class Music : public virtual IRtti, public Asset, public Audio, public virtual MemoryManager::Manageable
{
	RTTI_CLASS_DECLARE( Music );

public:
								Music( NameID& name, AudioManager* m );
								~Music();
	bool						load( const char* fname );
	bool						load( void* data, int size );
	void						free();
	void						play();
	void						stop();
	void						reset();
	bool						isPlaying();
	void						setVolume( float v );
	void						setPan( float v );
	void						setPitch( float v );
	void						setPosition( int f );
	void						setRepeat( bool m );
	float						getVolume();
	float						getPan();
	float						getPitch();
	int							getPosition();
	int							getLength();

	static Asset*				onLoad( AssetManager* manager, XeCore::XeString& name, Params& params, bool keepAlways );
	virtual void				onUnload();

private:
	AudioManager*				m_manager;
	NameID						m_name;
	audiere::OutputStreamPtr	m_music;
	audiere::FilePtr			m_file;
};

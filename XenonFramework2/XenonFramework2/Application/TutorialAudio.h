#pragma once

#include "../XeFramework/IRtti.h"
#include "../XeFramework/IState.h"
#include "../XeFramework/SpriteBatch.h"

class TutorialAudio : public virtual IRtti, public IState
{
	RTTI_CLASS_DECLARE( TutorialAudio );

public:
									TutorialAudio();
									~TutorialAudio();
	void							onEnter( IProgressState* p );
	void							onExit();
	void							onUpdate();
	void							onRender();
	void							onInput();

private:
	SpriteBatch::Text*				m_text;
};

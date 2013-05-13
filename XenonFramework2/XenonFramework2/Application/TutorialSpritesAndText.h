#pragma once

#include "../XeFramework/IRtti.h"
#include "../XeFramework/IState.h"
#include "../XeFramework/SpriteBatch.h"

class TutorialSpritesAndText : public virtual IRtti, public IState
{
	RTTI_CLASS_DECLARE( TutorialSpritesAndText );

public:
									TutorialSpritesAndText();
									~TutorialSpritesAndText();
	void							onEnter( IProgressState* p );
	void							onExit();
	void							onUpdate();
	void							onRender();
	void							onInput();

private:
	SpriteBatch::Sprite*			m_sprite;
	SpriteBatch::Text*				m_text;
};

#pragma once

#include "../XeFramework/IRtti.h"
#include "../XeFramework/IState.h"
#include "../XeFramework/SpriteBatch.h"

class TutorialEffects : public virtual IRtti, public IState
{
	RTTI_CLASS_DECLARE( TutorialEffects );

public:
									TutorialEffects();
									~TutorialEffects();
	void							onEnter( IProgressState* p );
	void							onExit();
	void							onUpdate();
	void							onRender();
	void							onInput();

private:
	SpriteBatch::Sprite*			m_sprite;
	ShapePool::Text*				m_text;
};

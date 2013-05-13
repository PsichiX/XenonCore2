#pragma once

#include "../XeFramework/IRtti.h"
#include "../XeFramework/IState.h"
#include "../XeFramework/SpriteBatch.h"

class Menu : public virtual IRtti, public IState
{
	RTTI_CLASS_DECLARE( Menu );

public:
									Menu();
									~Menu();
	void							onEnter( IProgressState* p );
	void							onExit();
	void							onUpdate();
	void							onRender();
	void							onInput();

	static const unsigned int		levelsCount = 7;

private:
	bool							mouseTextOver( SpriteBatch::Text* t );
	void							applyBgDim( SpriteBatch::Text* t );
	void							gotoTextLvl( unsigned int i );

	SpriteBatch::Text*				m_lvls[ levelsCount ];
	SpriteBatch::Sprite*			m_lvlbg;
};

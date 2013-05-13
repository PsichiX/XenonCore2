#pragma once

#include "../XeFramework/IRtti.h"
#include "../XeFramework/IState.h"
#include "../XeFramework/SpriteBatch.h"

class Level : public virtual IRtti, public IState
{
	RTTI_CLASS_DECLARE( Level );

public:
									Level();
									~Level();
	void							onEnter( IProgressState* p );
	void							onExit();
	void							onUpdate();
	void							onRender();
	void							onInput();

private:
	LONGLONG						m_updateTime;
	LONGLONG						m_renderTime;
	ShapePool::Text*				m_text;
	float							m_focus;
	SpriteBatch::Sprite*			m_bg;
	SpriteBatch::CanvasSprite*		m_depthSprite;
};

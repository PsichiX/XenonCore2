#pragma once

#include "../XeFramework/IRtti.h"
#include "../XeFramework/IState.h"
#include "../XeFramework/SpriteBatch.h"

class TutorialRenderTechnique : public virtual IRtti, public IState
{
	RTTI_CLASS_DECLARE( TutorialRenderTechnique );

public:
									TutorialRenderTechnique();
									~TutorialRenderTechnique();
	void							onEnter( IProgressState* p );
	void							onExit();
	void							onUpdate();
	void							onRender();
	void							onInput();

private:
	LONGLONG						m_updateTime;
	LONGLONG						m_renderTime;
	ShapePool::Text*				m_text;
	float							m_sunAlpha;
	float							m_sunBeta;
	float							m_sunSpd;
	float							m_sunTime;
};

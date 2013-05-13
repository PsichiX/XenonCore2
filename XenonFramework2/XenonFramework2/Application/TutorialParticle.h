#pragma once

#include "../XeFramework/IRtti.h"
#include "../XeFramework/IState.h"
#include "../XeFramework/ParticlesStream.h"

class TutorialParticle : public virtual IRtti, public IState
{
	RTTI_CLASS_DECLARE( TutorialParticle );

public:
									TutorialParticle();
									~TutorialParticle();
	void							onEnter( IProgressState* p );
	void							onExit();
	void							onUpdate();
	void							onRender();
	void							onInput();

private:
	ShapePool::Text*				m_text;
	ParticlesStream::UnitControler*	m_partControler;
};

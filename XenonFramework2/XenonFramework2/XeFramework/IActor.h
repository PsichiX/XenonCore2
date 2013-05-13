#pragma once

#include "IRtti.h"

class IActor : public virtual IRtti, public virtual MemoryManager::Manageable
{
	RTTI_CLASS_DECLARE( IActor );

public:
					IActor();
	virtual			~IActor() = 0;
	virtual void	update() = 0;
	virtual void	input() = 0;
	virtual void	render() = 0;
	void			remove();
	bool			getRemoved();
	void			setRemoveable( bool mode );
	bool			getRemoveable();

private:
	bool			m_toRemove;
	bool			m_removeable;
};

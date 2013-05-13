#include "IActor.h"
#include "Base.h"

RTTI_CLASS_DERIVATIONS(	IActor,
						RTTI_DERIVATIONS_END
						);

IActor::IActor():
RTTI_CLASS_DEFINE( IActor ),
m_toRemove( false ),
m_removeable( true )
{
}

IActor::~IActor()
{
}

void IActor::remove()
{
	m_toRemove = true;
}

bool IActor::getRemoved()
{
	return( m_toRemove );
}

void IActor::setRemoveable( bool mode )
{
	m_removeable = mode;
}

bool IActor::getRemoveable()
{
	return( m_removeable );
}

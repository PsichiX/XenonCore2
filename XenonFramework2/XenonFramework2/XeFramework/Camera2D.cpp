#include "Camera2D.h"

RTTI_CLASS_DERIVATIONS(	Camera2D,
						RTTI_DERIVATION( Camera ),
						RTTI_DERIVATIONS_END
						);

Camera2D::Camera2D( float x, float y, float w, float h, float a ):
RTTI_CLASS_DEFINE( Camera2D ),
m_x( x ),
m_y( y ),
m_width( w ),
m_height( h ),
m_angle( a )
{
	apply();
}
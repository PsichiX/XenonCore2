#include "Camera3D.h"

RTTI_CLASS_DERIVATIONS(	Camera3D,
						RTTI_DERIVATION( Camera ),
						RTTI_DERIVATIONS_END
						);

Camera3D::Camera3D( float a, float b, float g, float x, float y, float z, bool p, float ang, float asp, float zn, float zf ):
RTTI_CLASS_DEFINE( Camera3D ),
m_a( a ),
m_b( b ),
m_g( g ),
m_x( x ),
m_y( y ),
m_z( z ),
m_p( p ),
m_ang( ang ),
m_asp( asp ),
m_zn( zn ),
m_zf( zf )
{
	apply();
}
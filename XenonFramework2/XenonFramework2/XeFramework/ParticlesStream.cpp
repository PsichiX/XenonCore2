#include "ParticlesStream.h"
#include "Asset.h"
#include "SceneManager.h"
#include "AssetManager.h"
#include "Camera2D.h"
#include <limits>

RTTI_CLASS_DERIVATIONS(	ParticlesStream,
						RTTI_DERIVATION( Asset ),
						RTTI_DERIVATION( ShapePool ),
						RTTI_DERIVATIONS_END
						);

ParticlesStream::ParticlesStream( unsigned int capacity, bool doublebuff, bool pointsprites ):
ShapePool( capacity * ( pointsprites ? 1 : 4 ), doublebuff, true, ShapePool::rmStream, ShapePool::rmStatic ),
m_freeUnitsCount( capacity ),
m_asPointSprites( pointsprites ),
m_pointSpritesSize( 1.0f ),
RTTI_CLASS_DEFINE( ParticlesStream )
{
	setStaticRenderMode( m_asPointSprites ? XeCore::XE_POINTS : XeCore::XE_QUADS );
	m_units.Reserve( capacity );
	m_freeUnits.Reserve( capacity );
	VertexStruct* v = getStaticVertices();
	unsigned int* n = getStaticIndices();
	Unit* u = m_units.Get();
	Unit** f = m_freeUnits.Get();
	unsigned int k = 0;
	for( unsigned int i = 0; i < capacity; i++ )
	{
		*n = k; n++; k++;
		if( !m_asPointSprites )
		{
			*n = k; n++; k++;
			*n = k; n++; k++;
			*n = k; n++; k++;
		}
		*f = u; f++;
		v->position = XeCore::XeHalfVector( std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity() );
		u->m_vertices = v; u++; v += m_asPointSprites ? 1 : 4;
	}
	setStaticUpdateMode( sumVertex | sumIndex );
	ShapePool::swapBuffers();
	ShapePool::update();
	ShapePool::swapBuffers();
	ShapePool::update();
	setStaticUpdateMode( sumVertex );
}

ParticlesStream::~ParticlesStream()
{
	m_units.Free();
	m_freeUnits.Free();
	Asset::release( this );
}

void ParticlesStream::update()
{
	float dt = Global::use().engine->getDeltaTime();
	Unit* u = m_units.Get();
	for( unsigned int i = 0; i < m_units.Size(); i++, u++ )
		if( u->m_active )
		{
			u->m_lifeTime += dt;
			if( u->m_lifeTime >= u->m_lifeTimeLimit )
			{
				kill( u );
			}
			else
			{
				u->update( this, dt );
			}
		}
	ShapePool::swapBuffers();
	ShapePool::update();
}

void ParticlesStream::render()
{
	if( m_asPointSprites )
	{
		XeCore::XeSetState( XeCore::XE_RENDER_POINT_SIZE, (double)m_pointSpritesSize );
		XeCore::XeSetState( XeCore::XE_RENDER_POINT_SIZE_VERTEX_SHADER, XeCore::XE_TRUE );
		XeCore::XeSetState( XeCore::XE_RENDER_POINT_SPRITES_MODE, XeCore::XE_TRUE );
		XeCore::XeSetState( XeCore::XE_RENDER_POINT_SPRITES_COORD_REPLACE, XeCore::XE_TRUE );
	}
	ShapePool::render();
	if( m_asPointSprites )
	{
		XeCore::XeSetState( XeCore::XE_RENDER_POINT_SIZE, 1.0 );
		XeCore::XeSetState( XeCore::XE_RENDER_POINT_SIZE_VERTEX_SHADER, XeCore::XE_FALSE );
		XeCore::XeSetState( XeCore::XE_RENDER_POINT_SPRITES_MODE, XeCore::XE_FALSE );
		XeCore::XeSetState( XeCore::XE_RENDER_POINT_SPRITES_COORD_REPLACE, XeCore::XE_FALSE );
	}
}

bool ParticlesStream::generate( GenerationDescription& d, UnitControler* cnt )
{
	float f = (float)XeCore::XeMath::Random( 1.0 );
	unsigned int c = (unsigned int)LERP( f, (float)d.countMin, (float)d.countMax );
	for( unsigned int i = 0; i < c; i++ )
	{
		if( m_freeUnitsCount <= 0 )
			return( false );
		m_freeUnitsCount--;
		Unit* u = m_freeUnits[ m_freeUnitsCount ];
		UnitDescription ud;
		f = (float)XeCore::XeMath::Random( 1.0 );
		ud.lifetime = LERP( f, d.lifetimeMin, d.lifetimeMax );
		f = (float)XeCore::XeMath::Random( 1.0 );
		ud.position.X = d.position.X + LERP( f, d.offsetMin.X, d.offsetMax.X );
		f = (float)XeCore::XeMath::Random( 1.0 );
		ud.position.Y = d.position.Y + LERP( f, d.offsetMin.Y, d.offsetMax.Y );
		f = (float)XeCore::XeMath::Random( 1.0 );
		ud.position.Z = d.position.Z + LERP( f, d.offsetMin.Z, d.offsetMax.Z );
		f = (float)XeCore::XeMath::Random( 1.0 );
		ud.velocity.X = LERP( f, d.velocityMin.X, d.velocityMax.X );
		f = (float)XeCore::XeMath::Random( 1.0 );
		ud.velocity.Y = LERP( f, d.velocityMin.Y, d.velocityMax.Y );
		f = (float)XeCore::XeMath::Random( 1.0 );
		ud.velocity.Z = LERP( f, d.velocityMin.Z, d.velocityMax.Z );
		f = (float)XeCore::XeMath::Random( 1.0 );
		ud.scale.X = LERP( f, d.scaleMin.X, d.scaleMax.X );
		f = (float)XeCore::XeMath::Random( 1.0 );
		ud.scale.Y = LERP( f, d.scaleMin.Y, d.scaleMax.Y );
		f = (float)XeCore::XeMath::Random( 1.0 );
		ud.scale.Z = LERP( f, d.scaleMin.Z, d.scaleMax.Z );
		f = (float)XeCore::XeMath::Random( 1.0 );
		ud.color.X = LERP( f, d.colorMin.X, d.colorMax.X );
		f = (float)XeCore::XeMath::Random( 1.0 );
		ud.color.Y = LERP( f, d.colorMin.Y, d.colorMax.Y );
		f = (float)XeCore::XeMath::Random( 1.0 );
		ud.color.Z = LERP( f, d.colorMin.Z, d.colorMax.Z );
		f = (float)XeCore::XeMath::Random( 1.0 );
		ud.color.W = LERP( f, d.colorMin.W, d.colorMax.W );
		u->create( this, ud, cnt );
	}
	return( true );
}

bool ParticlesStream::kill( Unit* u )
{
	if( m_freeUnitsCount >= m_units.Size() )
		return( false );
	u->destroy( this );
	m_freeUnits[ m_freeUnitsCount ] = u;
	m_freeUnitsCount++;
	return( true );
}

Asset* ParticlesStream::onLoad( AssetManager* manager, XeCore::XeString& name, Params& params, bool keepAlways )
{
	unsigned int capacity = 0;
	bool doublebuff = false;
	bool pointsprites = false;
	if( params.Exists( "capacity" ) )
		params[ "capacity" ].getValue().Convert( &capacity, 'd' );
	if( params.Exists( "pointSprites" ) )
		pointsprites = params[ "pointSprites" ].getValue() == "true";
	if( params.Exists( "doubleBuffer" ) )
		doublebuff = params[ "doubleBuffer" ].getValue() == "true";
	if( capacity )
	{
		ParticlesStream* t = xnew ParticlesStream( capacity, doublebuff, pointsprites );
		float size = 1.0f;
		if( params.Exists( "pointSpritesSize" ) )
			params[ "pointSpritesSize" ].getValue().Convert( &size, 'h' );
		t->setPointSpritesSize( size );
		if( params.Exists( "camera" ) && params[ "camera" ].getType() == ParamData::tParams )
		{
			Params& cam = params[ "camera" ].getParams();
			float x( 0.0f ), y( 0.0f ), w( 1.0f ), h( 1.0f ), a( 0.0f );
			if( cam.Exists( "x" ) )
				cam[ "x" ].getValue().Convert( &x, 'h' );
			if( cam.Exists( "y" ) )
				cam[ "y" ].getValue().Convert( &y, 'h' );
			if( cam.Exists( "width" ) )
				cam[ "width" ].getValue().Convert( &w, 'h' );
			if( cam.Exists( "height" ) )
				cam[ "height" ].getValue().Convert( &h, 'h' );
			if( cam.Exists( "angle" ) )
				cam[ "angle" ].getValue().Convert( &a, 'h' );
			t->setCamera( xnew Camera2D( x, y, w, h, a ) );
		}
		if( params.Exists( "canvasAsset" ) )
			t->setCanvas( manager->get< Canvas >( params[ "canvasAsset" ].getValue(), keepAlways ) );
		if( params.Exists( "materialAsset" ) )
			t->setMaterial( manager->get< Material >( params[ "materialAsset" ].getValue(), keepAlways ) );
		if( Global::use().scenes->attach( NameID( name ), t ) )
		{
			ASSET_SET_PURE_POINTER( t );
			return( t );
		}
		else
		{
			DELETE_OBJECT( t );
			return( 0 );
		}
	}
	else
		return( 0 );
}

void ParticlesStream::onUnload()
{
	Global::use().scenes->detach( NameID( getAssetName() ) );
}

RTTI_CLASS_DERIVATIONS(	ParticlesStream::UnitControler,
						RTTI_DERIVATIONS_END
						);

ParticlesStream::UnitControler::UnitControler():
RTTI_CLASS_DEFINE( ParticlesStream::UnitControler )
{
}

ParticlesStream::UnitControler::~UnitControler()
{
	position.Free();
	velocity.Free();
	direction.Free();
	scale.Free();
	color.Free();
}

ParticlesStream::Unit::Unit():
m_active( false ),
m_vertices( 0 ),
m_lifeTime( 0.0f ),
m_lifeTimeLimit( 0.0f ),
m_controler( 0 )
{
}

ParticlesStream::Unit::~Unit()
{
}

void ParticlesStream::Unit::create( ParticlesStream* sys, UnitDescription& d, UnitControler* c )
{
	m_active = true;
	m_lifeTime = 0.0f;
	m_lifeTimeLimit = d.lifetime;
	m_position = d.position;
	m_posStart = m_position;
	m_direction = XeCore::XeAngleHalfVector();
	m_scale = d.scale;
	m_velocity = d.velocity;
	m_color = d.color;
	if( !sys->usesPointSprites() )
	{
		m_vertices[ 0 ].position = XeCore::XeHalfVector( -0.5f, -0.5f );
		m_vertices[ 1 ].position = XeCore::XeHalfVector( 0.5f, -0.5f );
		m_vertices[ 2 ].position = XeCore::XeHalfVector( 0.5f, 0.5f );
		m_vertices[ 3 ].position = XeCore::XeHalfVector( -0.5f, 0.5f );
		m_vertices[ 0 ].coords = XeCore::XeHalfVector( 0.0f, 0.0f );
		m_vertices[ 1 ].coords = XeCore::XeHalfVector( 1.0f, 0.0f );
		m_vertices[ 2 ].coords = XeCore::XeHalfVector( 1.0f, 1.0f );
		m_vertices[ 3 ].coords = XeCore::XeHalfVector( 0.0f, 1.0f );
		for( unsigned int i = 0; i < 4; i++ )
		{
			m_vertices[ i ].color = m_color;
		}
	}
	else
	{
		m_vertices->position = XeCore::XeHalfVector();
		m_vertices->coords = m_scale;
		m_vertices->color = m_color;
	}
	m_controler = c;
}

void ParticlesStream::Unit::update( ParticlesStream* sys, float dt )
{
	if( !m_vertices )
		return;
	float f = m_lifeTimeLimit > 0.0f ? m_lifeTime / m_lifeTimeLimit : 0.0f;
	// velocity
	if( m_controler && m_controler->velocity.Size() > 0 )
	{
		m_velocity = XeCore::XeHalfVector(
			XeCore::XeCurveHalf( f, m_controler->velocity.Size(), (float*)m_controler->velocity.Get(), 4, 0 ),
			XeCore::XeCurveHalf( f, m_controler->velocity.Size(), (float*)m_controler->velocity.Get(), 4, 1 ),
			XeCore::XeCurveHalf( f, m_controler->velocity.Size(), (float*)m_controler->velocity.Get(), 4, 2 )
			);
	}
	// position
	if( m_controler && m_controler->position.Size() > 0 )
	{
		XeCore::XeHalfVector p(
			XeCore::XeCurveHalf( f, m_controler->position.Size(), (float*)m_controler->position.Get(), 4, 0 ),
			XeCore::XeCurveHalf( f, m_controler->position.Size(), (float*)m_controler->position.Get(), 4, 1 ),
			XeCore::XeCurveHalf( f, m_controler->position.Size(), (float*)m_controler->position.Get(), 4, 2 )
			);
		m_position = m_posStart + p;
	}
	else
		m_position += m_velocity * XeCore::XeHalfVector( dt, dt, dt );
	// direction
	if( m_controler && m_controler->direction.Size() > 0 )
	{
		m_direction.Alpha = XeCore::XeCurveHalf( f, m_controler->direction.Size(), (float*)m_controler->direction.Get(), 4, 0 );
	}
	else
		m_velocity.ToAngle( m_direction.Alpha, m_direction.Beta );
	m_direction.Gamma = 0.0f;
	m_direction.Length = 1.0f;
	// scale
	if( m_controler && m_controler->scale.Size() > 0 )
	{
		m_scale = XeCore::XeHalfVector(
			XeCore::XeCurveHalf( f, m_controler->scale.Size(), (float*)m_controler->scale.Get(), 4, 0 ),
			XeCore::XeCurveHalf( f, m_controler->scale.Size(), (float*)m_controler->scale.Get(), 4, 1 ),
			XeCore::XeCurveHalf( f, m_controler->scale.Size(), (float*)m_controler->scale.Get(), 4, 2 )
			);
	}
	// color
	if( m_controler && m_controler->color.Size() > 0 )
	{
		m_color = XeCore::XeHalfVector(
			XeCore::XeCurveHalf( f, m_controler->color.Size(), (float*)m_controler->color.Get(), 4, 0 ),
			XeCore::XeCurveHalf( f, m_controler->color.Size(), (float*)m_controler->color.Get(), 4, 1 ),
			XeCore::XeCurveHalf( f, m_controler->color.Size(), (float*)m_controler->color.Get(), 4, 2 ),
			XeCore::XeCurveHalf( f, m_controler->color.Size(), (float*)m_controler->color.Get(), 4, 3 )
			);
	}
	else
		m_color.W = 1.0f - f;
	// apply
	XeCore::XeHalfMatrix mat;
	transform( mat );
	if( !sys->usesPointSprites() )
	{
		for( unsigned int i = 0; i < 4; i++ )
		{
			m_vertices[ i ].matrix = mat;
			m_vertices[ i ].color = m_color;
		}
	}
	else
	{
		m_vertices->matrix = mat;
		m_vertices->color = m_color;
		m_vertices->coords = m_scale;
	}
}

void ParticlesStream::Unit::destroy( ParticlesStream* sys )
{
	m_active = false;
	if( !sys->usesPointSprites() )
	{
		for( unsigned int i = 0; i < 4; i++ )
		{
			m_vertices[ i ].color = XeCore::XeHalfVector( 0.0f, 0.0f, 0.0f, 0.0f );
			m_vertices[ i ].coords = XeCore::XeHalfVector( 0.0f, 0.0f, 0.0f, 0.0f );
			m_vertices[ i ].matrix.Identity();
			m_vertices[ i ].position = XeCore::XeHalfVector( std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity() );
		}
	}
	else
	{
		m_vertices->color = XeCore::XeHalfVector( 0.0f, 0.0f, 0.0f, 0.0f );
		m_vertices->coords = XeCore::XeHalfVector( 0.0f, 0.0f, 0.0f, 0.0f );
		m_vertices->matrix.Identity();
		m_vertices->position = XeCore::XeHalfVector( std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity() );
	}
	m_controler = 0;
}

void ParticlesStream::Unit::transform( XeCore::XeHalfMatrix& mat )
{
	XeCore::XeHalfMatrix t;
	t.Translate( m_position.X, m_position.Y, m_position.Z, mat );
	mat.Rotate( m_direction.Alpha, m_direction.Beta, m_direction.Gamma, t );
	t.Scale( m_scale.X, m_scale.Y, m_scale.Z, mat );
}

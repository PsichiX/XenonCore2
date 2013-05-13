#include "ShapePool.h"

RTTI_CLASS_DERIVATIONS(	ShapePool,
						RTTI_DERIVATION( IScene ),
						RTTI_DERIVATIONS_END
						);

ShapePool::ShapePool( unsigned int capacity, bool doublebuff, bool staticMode, RenderMode vertrm, RenderMode indrm ):
RTTI_CLASS_DEFINE( ShapePool ),
m_doubleBuff( doublebuff ),
m_doubleBuffCurr( false ),
m_capacity( 0 ),
m_rest( 0 ),
m_allocMap( 0 ),
m_allocMapPos( 0 ),
m_staticMode( staticMode ),
m_staticMaterial( 0 ),
m_staticRenderMode( XeCore::XE_POLYGON ),
m_staticUpdateMode( 0 )
{
	rebuild( capacity, vertrm, indrm );
}

ShapePool::~ShapePool()
{
	free();
}

void ShapePool::render()
{
	int id = m_doubleBuff ? ( m_doubleBuffCurr ? 0 : 1 ) : 0;
	if( getCanvas() )
		if( !getCanvas()->activate() )
			return;
	int vertexDefinition[] = {
			XeCore::XE_CUSTOM_ATTRIBUTE, -1, 4, 0,
			XeCore::XE_CUSTOM_ATTRIBUTE, -1, 4, 0,
			XeCore::XE_CUSTOM_ATTRIBUTE, -1, 4, 0,
			XeCore::XE_CUSTOM_ATTRIBUTE, -1, 4, 0,
			XeCore::XE_CUSTOM_ATTRIBUTE, -1, 4, 0,
			XeCore::XE_CUSTOM_ATTRIBUTE, -1, 4, 0,
			XeCore::XE_CUSTOM_ATTRIBUTE, -1, 4, 0,
			0
		};
	XeCore::Photon::XeVertexBufferActivate( m_vbo[ id ], XeCore::XE_VERTEXBUFFER_ARRAY );
	XeCore::Photon::XeVertexBufferActivate( m_vbo[ id ], XeCore::XE_VERTEXBUFFER_ELEMENT );
	if( m_staticMode )
	{
		if( getCamera() )
			getCamera()->activateScissor();
		if( m_staticMaterial )
		{
			m_staticMaterial->activate();
			if( m_staticMaterial->getEffect() )
			{
				vertexDefinition[ 1 ] = m_staticMaterial->getEffect()->locationAttribute( "in_Position" );
				vertexDefinition[ 5 ] = m_staticMaterial->getEffect()->locationAttribute( "in_Color" );
				vertexDefinition[ 9 ] = m_staticMaterial->getEffect()->locationAttribute( "in_Coord" );
				vertexDefinition[ 13 ] = m_staticMaterial->getEffect()->locationAttribute( "in_ModelViewTransform1" );
				vertexDefinition[ 17 ] = m_staticMaterial->getEffect()->locationAttribute( "in_ModelViewTransform2" );
				vertexDefinition[ 21 ] = m_staticMaterial->getEffect()->locationAttribute( "in_ModelViewTransform3" );
				vertexDefinition[ 25 ] = m_staticMaterial->getEffect()->locationAttribute( "in_ModelViewTransform4" );
				if( getCamera() )
					m_staticMaterial->getEffect()->uniform( "in_ProjectionMatrix", getCamera()->getMatrix() );
			}
			else
			{
				vertexDefinition[ 1 ] = -1;
				vertexDefinition[ 5 ] = -1;
				vertexDefinition[ 9 ] = -1;
				vertexDefinition[ 13 ] = -1;
				vertexDefinition[ 17 ] = -1;
				vertexDefinition[ 21 ] = -1;
				vertexDefinition[ 25 ] = -1;
			}
		}
		XeCore::Photon::XeDrawDataCustom( m_staticRenderMode, 0, m_staticIndices.Size(), vertexDefinition );
		if( m_staticMaterial )
			m_staticMaterial->unactivate();
		if( getCamera() )
			getCamera()->unactivateScissor();
	}
	else
	{
		for( XeCore::XeElementPointer< RenderChunk > e = m_renderQueue[ id ].FirstPointer(); !e.IsEmpty(); e.Next() )
		{
			if( e->scene )
			{
				XeCore::Photon::XeVertexBufferUnactivate( XeCore::XE_VERTEXBUFFER_ARRAY );
				XeCore::Photon::XeVertexBufferUnactivate( XeCore::XE_VERTEXBUFFER_ELEMENT );
				e->scene->render();
				XeCore::Photon::XeVertexBufferActivate( m_vbo[ id ], XeCore::XE_VERTEXBUFFER_ARRAY );
				XeCore::Photon::XeVertexBufferActivate( m_vbo[ id ], XeCore::XE_VERTEXBUFFER_ELEMENT );
			}
			else
			{
				if( getCamera() )
					getCamera()->activateScissor();
				if( e->material )
				{
					e->material->activate();
					if( e->material->getEffect() )
					{
						vertexDefinition[ 1 ] = e->material->getEffect()->locationAttribute( "in_Position" );
						vertexDefinition[ 5 ] = e->material->getEffect()->locationAttribute( "in_Color" );
						vertexDefinition[ 9 ] = e->material->getEffect()->locationAttribute( "in_Coord" );
						vertexDefinition[ 13 ] = e->material->getEffect()->locationAttribute( "in_ModelViewTransform1" );
						vertexDefinition[ 17 ] = e->material->getEffect()->locationAttribute( "in_ModelViewTransform2" );
						vertexDefinition[ 21 ] = e->material->getEffect()->locationAttribute( "in_ModelViewTransform3" );
						vertexDefinition[ 25 ] = e->material->getEffect()->locationAttribute( "in_ModelViewTransform4" );
						if( getCamera() )
							e->material->getEffect()->uniform( "in_ProjectionMatrix", getCamera()->getMatrix() );
					}
					else
					{
						vertexDefinition[ 1 ] = -1;
						vertexDefinition[ 5 ] = -1;
						vertexDefinition[ 9 ] = -1;
						vertexDefinition[ 13 ] = -1;
						vertexDefinition[ 17 ] = -1;
						vertexDefinition[ 21 ] = -1;
						vertexDefinition[ 25 ] = -1;
					}
				}
				XeCore::Photon::XeDrawDataCustom( e->mode, e->first * sizeof(unsigned int), e->last - e->first, vertexDefinition );
				if( e->material )
					e->material->unactivate();
				if( getCamera() )
					getCamera()->unactivateScissor();
			}
		}
	}
	XeCore::Photon::XeVertexBufferUnactivate( XeCore::XE_VERTEXBUFFER_ARRAY );
	XeCore::Photon::XeVertexBufferUnactivate( XeCore::XE_VERTEXBUFFER_ELEMENT );
	if( getCanvas() )
		getCanvas()->unactivate();
}

void ShapePool::update()
{
	int id = m_doubleBuff ? ( m_doubleBuffCurr ? 1 : 0 ) : 0;
	if( m_staticMode && m_staticUpdateMode )
	{
		if( m_staticUpdateMode & sumVertex )
		{
			XeCore::Photon::XeVertexBufferActivate( m_vbo[ id ], XeCore::XE_VERTEXBUFFER_ARRAY );
			XeCore::Photon::XeVertexBufferSendData( XeCore::XE_VERTEXBUFFER_ARRAY, m_staticVetices.SizeBytes(), 0, m_staticVetices.Get() );
			XeCore::Photon::XeVertexBufferUnactivate( XeCore::XE_VERTEXBUFFER_ARRAY );
		}
		if( m_staticUpdateMode & sumIndex )
		{
			XeCore::Photon::XeVertexBufferActivate( m_vbo[ id ], XeCore::XE_VERTEXBUFFER_ELEMENT );
			XeCore::Photon::XeVertexBufferSendData( XeCore::XE_VERTEXBUFFER_ELEMENT, m_staticIndices.SizeBytes(), 0, m_staticIndices.Get() );
			XeCore::Photon::XeVertexBufferUnactivate( XeCore::XE_VERTEXBUFFER_ELEMENT );
		}
	}
	else
	{
		bool act = false;
		XeCore::XeHalfMatrix mat;
		XeCore::XeHalfMatrix mat2;
		for( IScene::Element e = IScene::access().FirstPointer(); !e.IsEmpty(); e.Next() )
		{
			if( IRtti::isDerived< Shape >( e() ) )
			{
				if( e()->isNeedUpdate() )
				{
					mat.Identity();
					mat.Translate( e()->getPosition().X, e()->getPosition().Y, e()->getPosition().Z, mat2 );
					mat2.Rotate( e()->getRotation().Alpha, e()->getRotation().Beta, e()->getRotation().Gamma, mat );
					mat.Scale( e()->getScale().X, e()->getScale().Y, e()->getScale().Z, mat2 );
					for( unsigned int i = 0; i < RTTI_TREAT_AS( e(), Shape )->size(); i++ )
					{
						if( !act )
						{
							XeCore::Photon::XeVertexBufferActivate( m_vbo[ id ], XeCore::XE_VERTEXBUFFER_ARRAY );
							act = true;
						}
						RTTI_TREAT_AS( e(), Shape )->access( i )->vertex.matrix = mat2;
						XeCore::Photon::XeVertexBufferSendData( XeCore::XE_VERTEXBUFFER_ARRAY, sizeof(VertexStruct), RTTI_TREAT_AS( e(), Shape )->access( i )->m_index * sizeof(VertexStruct), &(RTTI_TREAT_AS( e(), Shape )->access( i )->vertex) );
					}
					e()->decreaseNeedUpdateCounter();
				}
			}
			else
			if( IRtti::isDerived< IScene >( e() ) )
				RTTI_TREAT_AS( e(), IScene )->update();
		}
		if( act )
			XeCore::Photon::XeVertexBufferUnactivate( XeCore::XE_VERTEXBUFFER_ARRAY );
	}
}

void ShapePool::optimize()
{
	if( m_staticMode )
		return;
	IScene::access().Sort( ShapePool::sort );
}

void ShapePool::rebuildRenderQueue()
{
	if( m_staticMode )
		return;
	int id = m_doubleBuff ? ( m_doubleBuffCurr ? 1 : 0 ) : 0;
	bool act = false;
	m_renderQueue[ id ].Clear();
	XeCore::XeElementPointer< RenderChunk > chunk;
	unsigned int j = 0;
	unsigned int m = 0;
	for( IScene::Element e = IScene::access().FirstPointer(); !e.IsEmpty(); e.Next() )
	{
		if( !e()->isRenderable() )
			continue;
		if( IRtti::isDerived< Shape >( e() ) )
		{
			for( unsigned int i = 0; i < RTTI_TREAT_AS( e(), Shape )->size(); i++ )
			{
				if( !act )
				{
					m = XeCore::Photon::XeVertexBufferSize( m_vbo[ id ], XeCore::XE_VERTEXBUFFER_ELEMENT ) / sizeof(unsigned int);
					XeCore::Photon::XeVertexBufferActivate( m_vbo[ id ], XeCore::XE_VERTEXBUFFER_ELEMENT );
					act = true;
				}
				if( chunk.IsEmpty() || ( j < m && !chunk.IsEmpty() && ( RTTI_TREAT_AS( e(), Shape )->getRenderMode() != chunk->mode || RTTI_TREAT_AS( e(), Shape )->getMaterial() != chunk->material) ) )
				{
					chunk = m_renderQueue[ id ].AddPointer( RenderChunk() );
					chunk->material = RTTI_TREAT_AS( e(), Shape )->getMaterial();
					chunk->mode = RTTI_TREAT_AS( e(), Shape )->getRenderMode();
					chunk->first = j;
					chunk->last = j;
				}
				XeCore::Photon::XeVertexBufferSendData( XeCore::XE_VERTEXBUFFER_ELEMENT, sizeof(unsigned int), j * sizeof(unsigned int), &(RTTI_TREAT_AS( e(), Shape )->access( i )->m_index) );
				j++;
				chunk->last++;
			}
		}
		else
		if( IRtti::isDerived< IScene >( e() ) )
		{
			chunk = m_renderQueue[ id ].AddPointer( RenderChunk() );
			chunk->scene = RTTI_TREAT_AS( e(), IScene );
		}
	}
	if( act )
		XeCore::Photon::XeVertexBufferUnactivate( XeCore::XE_VERTEXBUFFER_ELEMENT );
}

unsigned int ShapePool::renderQueueCount( unsigned int id )
{
	return( m_renderQueue[ id ].Size() );
}

bool ShapePool::attach( IRenderable* s )
{
	if( m_staticMode )
		return( false );
	if( IRtti::isDerived< Shape >( s ) )
	{
		if( IScene::attach( s ) )
		{
			if( alloc( RTTI_TREAT_AS( s, Shape ) ) )
			{
				s->setNeedUpdateCounterMax( m_doubleBuff ? 2 : 1 );
				s->setNeedUpdate( true );
				return( true );
			}
			else
				return( false );
		}
		else
			return( false );
	}
	else
		return( IScene::attach( s ) );
}

bool ShapePool::detach( IRenderable* s )
{
	if( m_staticMode )
		return( false );
	if( IRtti::isDerived< Shape >( s ) )
		return( IScene::detach( s ) ? dealloc( RTTI_TREAT_AS( s, Shape ) ) : false );
	else
		return( IScene::detach( s ) );
}

bool ShapePool::rebuild( unsigned int count, RenderMode vertrm, RenderMode indrm )
{
	if( !count )
		return( false );
	free();
	XeCore::XeEstate vm = XE_NULL;
	if( vertrm == rmStatic )
		vm = XeCore::XE_VERTEXBUFFER_STATIC_DRAW;
	else
	if( vertrm == rmDynamic )
		vm = XeCore::XE_VERTEXBUFFER_DYNAMIC_DRAW;
	else
	if( vertrm == rmStream )
		vm = XeCore::XE_VERTEXBUFFER_STREAM_DRAW;
	XeCore::XeEstate im = XE_NULL;
	if( indrm == rmStatic )
		im = XeCore::XE_VERTEXBUFFER_STATIC_DRAW;
	else
	if( indrm == rmDynamic )
		im = XeCore::XE_VERTEXBUFFER_DYNAMIC_DRAW;
	else
	if( indrm == rmStream )
		im = XeCore::XE_VERTEXBUFFER_STREAM_DRAW;
	if( vm == XE_NULL || im == XE_NULL )
		return( false );
	XeCore::Photon::XeVertexBufferCreate( &m_vbo[ 0 ], sizeof(VertexStruct) * static_cast<int>(count), 0, vm, sizeof(unsigned int) * static_cast<int>(count), 0, im );
	if( m_doubleBuff )
		XeCore::Photon::XeVertexBufferCreate( &m_vbo[ 1 ], sizeof(VertexStruct) * static_cast<int>(count), 0, vm, sizeof(unsigned int) * static_cast<int>(count), 0, im );
	XeCore::Photon::XeVertexBufferUnactivate( XeCore::XE_VERTEXBUFFER_ARRAY );
	XeCore::Photon::XeVertexBufferUnactivate( XeCore::XE_VERTEXBUFFER_ELEMENT );
	m_capacity = count;
	m_rest = count;
	if( !m_staticMode )
	{
		m_allocMap.Reserve( count );
		memset( m_allocMap.Get(), 0, m_allocMap.SizeBytes() );
	}
	else
	{
		m_staticVetices.Reserve( count );
		m_staticIndices.Reserve( count );
	}
	m_allocMapPos = 0;
	return( true );
}

bool ShapePool::alloc( Shape* s )
{
	if( m_staticMode )
		return( false );
	XeCore::XeArray< Vertex >& a = s->m_vertices;
	if( !m_allocMap.Size() || !a.Size() || a.Size() > m_rest )
		return( false );
	m_rest -= a.Size();

	Vertex* sc = &a[ 0 ];
	Vertex* se = &a[ a.Size() - 1 ];

	XeCore::XeByte* mb = &m_allocMap[ 0 ];
	XeCore::XeByte* ms = &m_allocMap[ m_allocMapPos ];
	XeCore::XeByte* mc = ms;
	XeCore::XeByte* me = &m_allocMap[ m_allocMap.Size() - 1 ];

	do
	{
		if( !*mc )
		{
			sc->m_index = m_allocMapPos;
			*mc = true;
			sc++;
		}
		mc++;
		m_allocMapPos++;
		if( mc > me )
		{
			mc = mb;
			m_allocMapPos = 0;
		}
	}while( sc <= se && mc != ms );

	return( true );
}

bool ShapePool::dealloc( Shape* s )
{
	if( m_staticMode )
		return( false );
	XeCore::XeArray< Vertex >& a = s->m_vertices;
	if( !m_allocMap.Size() || !a.Size() || a.Size() > m_capacity )
		return( false );
	m_rest += a.Size();

	Vertex* sc = &a[ 0 ];
	Vertex* se = &a[ a.Size() - 1 ];

	do
	{
		m_allocMap[ sc->m_index ] = false;
		sc++;
		
	}while( sc <= se );

	return( true );
}

void ShapePool::free()
{
	XeCore::Photon::XeVertexBufferUnactivate( XeCore::XE_VERTEXBUFFER_ARRAY );
	XeCore::Photon::XeVertexBufferUnactivate( XeCore::XE_VERTEXBUFFER_ELEMENT );
	for( unsigned int i = 0; i < 2; i++ )
	{
		if( !m_vbo[ i ].IsEmpty() )
		{
			XeCore::Photon::XeVertexBufferDestroy( m_vbo[ i ] );
			m_vbo[ i ].Unref();
		}
		m_renderQueue[ i ].Clear();
	}
	for( IScene::Element e = IScene::access().FirstPointer(); !e.IsEmpty(); e.Next() )
		IScene::setParent( 0, e() );
	IScene::access().Clear();
	m_allocMap.Free();
	m_allocMapPos = 0;
	m_capacity = 0;
	m_rest = 0;
	m_doubleBuffCurr = false;
	m_staticVetices.Free();
	m_staticIndices.Free();
}

int ShapePool::sort( IRenderable** a, IRenderable** b )
{
	if(	( !IRtti::isDerived< Shape >( *a ) && !IRtti::isDerived< IScene >( *a ) )	||
		( !IRtti::isDerived< Shape >( *b ) && !IRtti::isDerived< IScene >( *b ) )	)
		return( 0 );
	float ao = (*a)->getOrder();
	float bo = (*b)->getOrder();
	if( ao > bo )
		return( 1 );
	else
	if( ao == bo )
	{
		if( IRtti::isDerived< IScene >( *a ) || IRtti::isDerived< IScene >( *b ) )
			return( 0 );
		XeCore::XeEstate am = RTTI_TREAT_AS( *a, Shape )->getRenderMode();
		XeCore::XeEstate bm = RTTI_TREAT_AS( *b, Shape )->getRenderMode();
		Material* amt = RTTI_TREAT_AS( *a, Shape )->getMaterial();
		Material* bmt = RTTI_TREAT_AS( *b, Shape )->getMaterial();
		if( am > bm )
			return( 1 );
		else
		if( am == bm )
		{
			if( amt > bmt )
				return( 1 );
			else
			if( amt == bmt )
				return( 0 );
			else
			if( amt < bmt )
				return( -1 );
			return( 0 );
		}
		else
		if( am < bm )
			return( -1 );
		return( 0 );
	}
	else
	if( ao < bo )
		return( -1 );
	return( 0 );
}

RTTI_CLASS_DERIVATIONS(	ShapePool::Shape,
						RTTI_DERIVATION( IRenderable ),
						RTTI_DERIVATIONS_END
						);

ShapePool::Shape::Shape():
RTTI_CLASS_DEFINE( ShapePool::Shape ),
m_material( 0 ),
m_renderMode( XeCore::XE_POLYGON )
{
}

ShapePool::Shape::~Shape()
{
	IRenderable::~IRenderable();
	m_vertices.Free();
}

void ShapePool::Shape::reserve( unsigned int count)
{
	if( getParent() )
		getParent()->detach( this );
	m_vertices.Reserve( count );
}

unsigned int ShapePool::Shape::size()
{
	return( m_vertices.Size() );	
}

void ShapePool::Shape::setRenderMode( XeCore::XeEstate m )
{
	m_renderMode = m;
}

XeCore::XeEstate ShapePool::Shape::getRenderMode()
{
	return( m_renderMode );
}

void ShapePool::Shape::setMaterial( Material* m )
{
	m_material = m;
}

Material* ShapePool::Shape::getMaterial()
{
	return( m_material );
}

ShapePool::Vertex* ShapePool::Shape::access( unsigned int i )
{
	if( i >= m_vertices.Size() )
		return( 0 );
	return( &m_vertices[ i ] );
}

RTTI_CLASS_DERIVATIONS(	ShapePool::Text,
						RTTI_DERIVATION( ShapePool::Shape ),
						RTTI_DERIVATIONS_END
						);

ShapePool::Text::Text():
RTTI_CLASS_DEFINE( ShapePool::Text ),
m_width( 0.0f ),
m_height( 0.0f ),
m_offsetX( 0.0f ),
m_offsetY( 0.0f )
{
}

ShapePool::Text::~Text()
{
	m_br.Free();
}

bool ShapePool::Text::build( Font* font, const char* text, XeCore::XeHalfVector& col )
{
	if( getParent() )
		return( false );
	if( font && text )
	{
		unsigned int len = strlen( text );
		unsigned int len4 = len * 4;
		unsigned int count = 0;
		unsigned int br = 0;
		for( unsigned int i = 0; i < len; i++ )
		{
			if(	text[ i ] != '\r'	&&
				text[ i ] != '\n'	)
				count++;
			else
				br++;
		}
		m_br.Free();
		m_br.Reserve( br + 1 );
		m_br[ br ] = 4 * count;
		br = 0;
		m_br.Seek( 0 );
		setRenderMode( XeCore::XE_QUADS );
		reserve( 4 * count );
		float	px( 0.0f ),
				py( 0.0f ),
				sz( font->getSize() );
		unsigned int i = 0;
		float minx( 0.0f ), miny( 0.0f ), maxx( 0.0f ), maxy( 0.0f );
		for( unsigned int c = 0; c < len; c++ )
		{
			XeCore::XeHalfVector cb, ce, off, siz;
			float adv;
			if(	text[ c ] == '\r'	||
				text[ c ] == '\n'	)
			{
				px = 0.0f;
				py += sz;
				m_br[ br++ ]= i;
				continue;
			}
			if( !font->getCharacter( text[ c ], cb, ce, off, siz, adv ) )
				continue;
			access( i + 0 )->vertex.color = col;
			access( i + 1 )->vertex.color = col;
			access( i + 2 )->vertex.color = col;
			access( i + 3 )->vertex.color = col;
			access( i + 0 )->vertex.coords = XeCore::XeHalfVector( cb.X, cb.Y );
			access( i + 1 )->vertex.coords = XeCore::XeHalfVector( ce.X, cb.Y );
			access( i + 2 )->vertex.coords = XeCore::XeHalfVector( ce.X, ce.Y );
			access( i + 3 )->vertex.coords = XeCore::XeHalfVector( cb.X, ce.Y );
			access( i + 0 )->vertex.position = XeCore::XeHalfVector( px + off.X, py + off.Y );
			access( i + 1 )->vertex.position = XeCore::XeHalfVector( px + off.X + siz.X, py + off.Y );
			access( i + 2 )->vertex.position = XeCore::XeHalfVector( px + off.X + siz.X, py + off.Y + siz.Y );
			access( i + 3 )->vertex.position = XeCore::XeHalfVector( px + off.X, py + off.Y + siz.Y );
			minx = min( minx, access( i + 0 )->vertex.position.X );
			minx = min( minx, access( i + 1 )->vertex.position.X );
			minx = min( minx, access( i + 2 )->vertex.position.X );
			minx = min( minx, access( i + 3 )->vertex.position.X );
			miny = min( miny, access( i + 0 )->vertex.position.Y );
			miny = min( miny, access( i + 1 )->vertex.position.Y );
			miny = min( miny, access( i + 2 )->vertex.position.Y );
			miny = min( miny, access( i + 3 )->vertex.position.Y );
			maxx = max( maxx, access( i + 0 )->vertex.position.X );
			maxx = max( maxx, access( i + 1 )->vertex.position.X );
			maxx = max( maxx, access( i + 2 )->vertex.position.X );
			maxx = max( maxx, access( i + 3 )->vertex.position.X );
			maxy = max( maxy, access( i + 0 )->vertex.position.Y );
			maxy = max( maxy, access( i + 1 )->vertex.position.Y );
			maxy = max( maxy, access( i + 2 )->vertex.position.Y );
			maxy = max( maxy, access( i + 3 )->vertex.position.Y );
			px += adv;
			i += 4;
		}
		m_width = maxx - minx;
		m_height = maxy - miny;
		m_offsetX = -minx;
		m_offsetY = -miny;
		return( true );
	}
	else
	{
		reserve( 4 );
		setRenderMode( XeCore::XE_QUADS );
		m_width = 0.0f;
		m_height = 0.0f;
		m_offsetX = 0.0f;
		m_offsetY = 0.0f;
		return( false );
	}
}

bool ShapePool::Text::rebuild( Font* font, const char* text, XeCore::XeHalfVector& col )
{
	if( !getParent() )
		return( false );
	if( !IRtti::isDerived< ShapePool >( getParent() ) )
		return( false );
	ShapePool* scene = RTTI_TREAT_AS( getParent(), ShapePool );
	if( !RTTI_TREAT_AS( getParent(), ShapePool )->detach( this ) )
		return( false );
	if( !build( font, text, col ) )
		return( false );
	return( scene->attach( this ) );
}

void ShapePool::Text::changeColor( XeCore::XeHalfVector& col, unsigned int start, unsigned int end )
{
	unsigned int s( min( start * 4, size() ) ), e( end == -1 ? size() : min( end * 4, size() ) );
	for( unsigned int i = s; i < e; i++ )
		access( i )->vertex.color = col;
	setNeedUpdate( true );
}

void ShapePool::Text::applyAlign( Font::Align a )
{
	if( a == Font::aLeft || a == Font::aCenter || a == Font::aRight )
	{
		unsigned int c = 0;
		for( unsigned int bi = 0; bi < m_br.Size(); bi++ )
		{
			float smin( 0.0f ), smax( 0.0f );
			for( unsigned int i = c; i < m_br[ bi ]; i++ )
			{
				smin = min( smin, access( i )->vertex.position.X );
				smax = max( smax, access( i )->vertex.position.X );
			}
			float off( smin ), siz( smax - smin );
			for( unsigned int i = c; i < m_br[ bi ]; i++ )
			{
				if( a == Font::aLeft )
					access( i )->vertex.position.X -= off;
				else
				if( a == Font::aCenter )
					access( i )->vertex.position.X -= off + siz * 0.5f;
				else
				if( a == Font::aRight )
					access( i )->vertex.position.X -= off + siz;
			}
			c = m_br[ bi ];
		}
		if( a == Font::aLeft )
			m_offsetX = 0.0f;
		else
		if( a == Font::aCenter )
			m_offsetX = m_width * 0.5f;
		else
		if( a == Font::aRight )
			m_offsetX = m_width;
	}
	else
	if( a == Font::aTop || a == Font::aMiddle || a == Font::aBottom )
	{
		for( unsigned int i = 0; i < size(); i++ )
		{
			if( a == Font::aTop )
				access( i )->vertex.position.Y -= m_offsetY;
			else
			if( a == Font::aMiddle )
				access( i )->vertex.position.Y -= m_offsetY + m_height * 0.5f;
			else
			if( a == Font::aBottom )
				access( i )->vertex.position.Y -= m_offsetY + m_height;
		}
		if( a == Font::aTop )
			m_offsetY = 0.0f;
		else
		if( a == Font::aMiddle )
			m_offsetY = m_height * 0.5f;
		else
		if( a == Font::aBottom )
			m_offsetY = m_height;
	}
	setNeedUpdate( true );
}

float ShapePool::Text::getWidth()
{
	return( m_width );
}

float ShapePool::Text::getHeight()
{
	return( m_height );
}

float ShapePool::Text::getOffsetX()
{
	return( m_offsetX );
}

float ShapePool::Text::getOffsetY()
{
	return( m_offsetY );
}
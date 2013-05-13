#include "Effect.h"
#include "EffectManager.h"
#include "Asset.h"

RTTI_CLASS_DERIVATIONS(	Effect,
						RTTI_DERIVATION( Asset ),
						RTTI_DERIVATIONS_END
						);

Effect::Effect():
RTTI_CLASS_DEFINE( Effect )
{
	XeCore::Photon::XeShaderCreate( &m_vert );
	XeCore::Photon::XeShaderCreate( &m_frag );
	XeCore::Photon::XeShaderCreate( &m_prog );
}

Effect::~Effect()
{
	free();

	Asset::release( this );
}

bool Effect::load( const char* vertname, const char* fragname, const char* ver )
{
	if( m_vert.IsEmpty() || m_frag.IsEmpty() || m_prog.IsEmpty() )
		return( false );
	XeCore::XeString pre;
	XeCore::XeString vendor = (char*)XeCore::XeGetState( XeCore::XE_RENDER_VENDOR );
	_strlwr_s( vendor, vendor.Length() + 1 );
	Engine::WindowRect wr;
	(float)Global::use().engine->getWindowRect( wr );
	pre.Format( "#version %s\n#define XE_WINDOW_SIZE vec2( %f, %f )\n#define XE_WINDOW_POS vec2( %f, %f )\n", ver, (float)wr.width, (float)wr.height, (float)wr.x, (float)wr.y );
	if( vendor.Find( 0, "intel" ) )
		pre << "#define XE_VENDOR_INTEL float( 1.0 )\n";
	else
	if( vendor.Find( 0, "ati" ) )
		pre << "#define XE_VENDOR_ATI float( 1.0 )\n";
	else
	if( vendor.Find( 0, "nvidia" ) )
		pre << "#define XE_VENDOR_NVIDIA float( 1.0 )\n";
	else
		pre << "#define XE_VENDOR_UNKNOWN float( 1.0 )\n";
	if( !XeCore::Photon::XeShaderLoad( m_vert, XeCore::XE_SHADER_VP_SL, const_cast<char*>(vertname), pre.Get() ) )
	{
		m_log.Format( "Vertex Shader: %s", XeCore::Photon::XeShaderLastLog() );
		free();
		return( false );
	}
	if( !XeCore::Photon::XeShaderLoad( m_frag, XeCore::XE_SHADER_FP_SL, const_cast<char*>(fragname), pre.Get() ) )
	{
		m_log.Format( "Fragment Shader: %s", XeCore::Photon::XeShaderLastLog() );
		free();
		return( false );
	}
	if( !XeCore::Photon::XeShaderMakeProgram( m_prog, &m_vert, 2 ) )
	{
		m_log.Format( "Shader Program: %s", XeCore::Photon::XeShaderLastLog() );
		free();
		return( false );
	}
	if( !m_vert.IsEmpty() )
	{
		XeCore::Photon::XeShaderDestroy( m_vert );
		m_vert.Unref();
	}
	if( !m_frag.IsEmpty() )
	{
		XeCore::Photon::XeShaderDestroy( m_frag );
		m_frag.Unref();
	}
	m_log.Format( "Shader Program: %s", XeCore::Photon::XeShaderLastLog() );
	XeCore::XeFile fv, ff;
	fv.Load( const_cast<char*>(vertname) );
	ff.Load( const_cast<char*>(fragname) );
	XeCore::Photon::XeShaderActivate( m_prog );
	unsigned int c = 0;
	XeCore::XeString* v = XeCore::XeString::ExplodeBuff( (char*)fv.Data(), fv.Size(), " \t\r\n;[]", c );
	if( v && c )
	{
		for( unsigned int i = 0; i < c; i++ )
		{
			XeCore::XeString t = v[ i ];
			if( t == "attribute" )
			{
				i++; i++;
				int l = XeCore::Photon::XeShaderAttributeLocation( m_prog, v[ i ] );
				if( l >= 0 )
					m_attribs[ v[ i ] ].id = l;
				else
					XWARNING( "Uniform '%s' not found", v[ i ] );
			}
			else
			if( t == "uniform" )
			{
				i++; i++;
				int l = XeCore::Photon::XeShaderUniformLocation( m_prog, v[ i ] );
				if( l >= 0 )
					m_uniforms[ v[ i ] ].id = l;
				else
					XWARNING( "Uniform '%s' not found", v[ i ] );
			}
		}
		DELETE_ARRAY( v );
	}
	c = 0;
	v = XeCore::XeString::ExplodeBuff( (char*)ff.Data(), ff.Size(), " \t\r\n;[]", c );
	if( v && c )
	{
		for( unsigned int i = 0; i < c; i++ )
		{
			XeCore::XeString t = v[ i ];
			if( t == "attribute" )
			{
				i++; i++;
				int l = XeCore::Photon::XeShaderAttributeLocation( m_prog, v[ i ] );
				if( l >= 0 )
					m_attribs[ v[ i ] ].id = l;
				else
					XWARNING( "Uniform '%s' not found", v[ i ] );
			}
			else
			if( t == "uniform" )
			{
				i++; i++;
				int l = XeCore::Photon::XeShaderUniformLocation( m_prog, v[ i ] );
				if( l >= 0 )
					m_uniforms[ v[ i ] ].id = l;
				else
					XWARNING( "Uniform '%s' not found", v[ i ] );
			}
		}
		DELETE_ARRAY( v );
	}
	XeCore::Photon::XeShaderUnactivate( XeCore::XE_SHADER_PROGRAM_SL );
	fv.Free();
	ff.Free();
	return( true );
}

void Effect::free()
{
	if( !m_vert.IsEmpty() )
	{
		XeCore::Photon::XeShaderDestroy( m_vert );
		m_vert.Unref();
	}
	if( !m_frag.IsEmpty() )
	{
		XeCore::Photon::XeShaderDestroy( m_frag );
		m_frag.Unref();
	}
	if( !m_prog.IsEmpty() )
	{
		XeCore::Photon::XeShaderDestroy( m_prog );
		m_prog.Unref();
	}
	m_attribs.Clear();
	m_uniforms.Clear();
}

void Effect::activate()
{
	XeCore::Photon::XeShaderActivate( m_prog );
}

void Effect::unactivate()
{
	XeCore::Photon::XeShaderUnactivate( XeCore::XE_SHADER_PROGRAM_SL );
}

XeCore::Photon::XeElmShader Effect::getShader()
{
	return( m_prog );
}

const char* Effect::getLog()
{
	return( m_log );
}

int Effect::locationUniform( const char* name )
{
	XeCore::XeString str = const_cast<char*>(name);
	if( !m_uniforms.Exists( str ) )
		return( -1 );
	return( m_uniforms[ str ].id );
}

int Effect::locationAttribute( const char* name )
{
	XeCore::XeString str = const_cast<char*>(name);
	if( !m_attribs.Exists( str ) )
		return( -1 );
	return( m_attribs[ str ].id );
}

bool Effect::uniform( const char* loc, XeCore::XeHalfVector* v, int channels )
{
	if( channels <= 0 || channels > 4 )
		return( false );
	XeCore::XeString str = const_cast<char*>(loc);
	if( !m_uniforms.Exists( str ) )
		return( false );
	return( XeCore::Photon::XeShaderUniform( m_uniforms[ str ].id, *v, channels ) );
}

bool Effect::uniform( const char* loc, XeCore::XeInteger* v, int channels )
{
	if( channels <= 0 || channels > 4 )
		return( false );
	XeCore::XeString str = const_cast<char*>(loc);
	if( !m_uniforms.Exists( str ) )
		return( false );
	return( XeCore::Photon::XeShaderUniformInteger( m_uniforms[ str ].id, v, channels ) );
}

bool Effect::uniform( const char* loc, XeCore::XeHalfMatrix* m, bool trans )
{
	XeCore::XeString str = const_cast<char*>(loc);
	if( !m_uniforms.Exists( str ) )
		return( false );
	return( XeCore::Photon::XeShaderUniformMatrix( m_uniforms[ str ].id, m, trans ) );
}

bool Effect::uniformArray( const char* loc, XeCore::XeHalf* v, int count, int channels )
{
	if( channels <= 0 || channels > 4 || count <= 0 )
		return( false );
	XeCore::XeString str = const_cast<char*>(loc);
	if( !m_uniforms.Exists( str ) )
		return( false );
	return( XeCore::Photon::XeShaderUniformArray( m_uniforms[ str ].id, v, count, channels ) );
}

bool Effect::uniformArray( const char* loc, XeCore::XeInteger* v, int count, int channels )
{
	if( channels <= 0 || channels > 4 || count <= 0 )
		return( false );
	XeCore::XeString str = const_cast<char*>(loc);
	if( !m_uniforms.Exists( str ) )
		return( false );
	return( XeCore::Photon::XeShaderUniformArrayInteger( m_uniforms[ str ].id, v, count, channels ) );
}

bool Effect::attribute( const char* loc, XeCore::XeHalfVector* v, int channels )
{
	if( channels < 0 || channels >= 4 )
		return( false );
	XeCore::XeString str = const_cast<char*>(loc);
	if( !m_attribs.Exists( str ) )
		return( false );
	return( XeCore::Photon::XeShaderAttribute( m_attribs[ str ].id, *v, channels ) );
}

Asset* Effect::onLoad( AssetManager* manager, XeCore::XeString& name, Params& params, bool keepAlways )
{
	if( !params.Exists( "vertPath" ) || !params.Exists( "fragPath" ) )
		return( false );
	Effect* t = xnew Effect();
	if( t->load( params[ "vertPath" ].getValue(), params[ "fragPath" ].getValue(), params.Exists( "version" ) ? params[ "version" ].getValue() : "120" ) )
	{
		if( Global::use().effects->attach( NameID( name ), t ) )
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
	{
		XPEDANTICWARNING( ">>> Effect loading result:\n%s", t->getLog() );
		DELETE_OBJECT( t );
		return( 0 );
	}
}

void Effect::onUnload()
{
	Global::use().effects->detach( NameID( getAssetName() ) );
}


RTTI_CLASS_DERIVATIONS(	Effect::Properties,
						RTTI_DERIVATIONS_END
						);

Effect::Properties::Properties():
RTTI_CLASS_DEFINE(Properties)
{
}

Effect::Properties::~Properties()
{
	m_properties.Clear();
}

void Effect::Properties::setPropertyVec( const char* name, XeCore::XeHalfVector& v, int channels )
{
	if( m_properties.Exists( const_cast<char*>(name) ) )
	{
		Property& p = m_properties[ const_cast<char*>(name) ];
		if( p.count > 0 )
		{
			if( p.type == 'h' && p.value.ah )
				DELETE_ARRAY( p.value.ah )
			else
			if( p.type == 'i' && p.value.ai )
				DELETE_ARRAY( p.value.ai )
		}
	}
	Property& p = m_properties[ const_cast<char*>(name) ];
	p.value.v[ 0 ] = v.X;
	p.value.v[ 1 ] = v.Y;
	p.value.v[ 2 ] = v.Z;
	p.value.v[ 3 ] = v.W;
	p.type = 'h';
	p.channels = min( max( channels, 0 ), 4 );
	p.count = 0;
}

void Effect::Properties::setPropertyInt( const char* name, XeCore::XeInteger v[ 4 ], int channels )
{
	if( m_properties.Exists( const_cast<char*>(name) ) )
	{
		Property& p = m_properties[ const_cast<char*>(name) ];
		if( p.count > 0 )
		{
			if( p.type == 'h' && p.value.ah )
				DELETE_ARRAY( p.value.ah )
			else
			if( p.type == 'i' && p.value.ai )
				DELETE_ARRAY( p.value.ai )
		}
	}
	Property& p = m_properties[ const_cast<char*>(name) ];
	p.value.i[ 0 ] = v[ 0 ];
	p.value.i[ 1 ] = v[ 1 ];
	p.value.i[ 2 ] = v[ 2 ];
	p.value.i[ 3 ] = v[ 3 ];
	p.type = 'i';
	p.channels = min( max( channels, 0 ), 4 );
	p.count = 0;
}

void Effect::Properties::setPropertySampler( const char* name, XeCore::XeInteger v )
{
	if( m_properties.Exists( const_cast<char*>(name) ) )
	{
		Property& p = m_properties[ const_cast<char*>(name) ];
		if( p.count > 0 )
		{
			if( p.type == 'h' && p.value.ah )
				DELETE_ARRAY( p.value.ah )
			else
			if( p.type == 'i' && p.value.ai )
				DELETE_ARRAY( p.value.ai )
		}
	}
	Property& p = m_properties[ const_cast<char*>(name) ];
	p.value.s = v;
	p.type = 's';
	p.channels = 1;
	p.count = 0;
}

void Effect::Properties::setPropertyMat( const char* name, XeCore::XeHalfMatrix& v, bool trans )
{
	if( m_properties.Exists( const_cast<char*>(name) ) )
	{
		Property& p = m_properties[ const_cast<char*>(name) ];
		if( p.count > 0 )
		{
			if( p.type == 'h' && p.value.ah )
				DELETE_ARRAY( p.value.ah )
			else
			if( p.type == 'i' && p.value.ai )
				DELETE_ARRAY( p.value.ai )
		}
	}
	Property& p = m_properties[ const_cast<char*>(name) ];
	for( int i = 0; i < 16; i++ )
		p.value.m[ i ] = v.Cell[ i ];
	p.type = 'm';
	p.channels = trans ? 1 : 0;
	p.count = 0;
}

void Effect::Properties::setPropertyArrayHalf( const char* name, XeCore::XeHalf* v, int count, int channels )
{
	if( m_properties.Exists( const_cast<char*>(name) ) )
	{
		Property& p = m_properties[ const_cast<char*>(name) ];
		if( p.count > 0 )
		{
			if( p.type == 'h' && p.value.ah )
				DELETE_ARRAY( p.value.ah )
			else
			if( p.type == 'i' && p.value.ai )
				DELETE_ARRAY( p.value.ai )
		}
	}
	Property& p = m_properties[ const_cast<char*>(name) ];
	p.value.ah = new XeCore::XeHalf[ count ];
	memcpy_s( p.value.ah, sizeof( XeCore::XeHalf ) * count, v, sizeof( XeCore::XeHalf ) * count );
	p.type = 'h';
	p.channels = min( max( channels, 0 ), 4 );
	p.count = count;
}

void Effect::Properties::setPropertyArrayInt( const char* name, XeCore::XeInteger* v, int count, int channels )
{
	if( m_properties.Exists( const_cast<char*>(name) ) )
	{
		Property& p = m_properties[ const_cast<char*>(name) ];
		if( p.count > 0 )
		{
			if( p.type == 'h' && p.value.ah )
				DELETE_ARRAY( p.value.ah )
			else
			if( p.type == 'i' && p.value.ai )
				DELETE_ARRAY( p.value.ai )
		}
	}
	Property& p = m_properties[ const_cast<char*>(name) ];
	p.value.ai = new XeCore::XeInteger[ count ];
	memcpy_s( p.value.ai, sizeof( XeCore::XeInteger ) * count, v, sizeof( XeCore::XeInteger ) * count );
	p.type = 'i';
	p.channels = min( max( channels, 0 ), 4 );
	p.count = count;
}

XeCore::XeHalfVector* Effect::Properties::getPropertyVec( const char* name, int* channels )
{
	if( !m_properties.Exists( const_cast<char*>(name) ) )
		return( 0 );
	Property& p = m_properties[ const_cast<char*>(name) ];
	if( p.type != 'h' )
		return( 0 );
	if( channels )
		*channels = p.channels;
	return( (XeCore::XeHalfVector*)&p.value.v );
}

XeCore::XeInteger* Effect::Properties::getPropertyInt( const char* name, int* channels )
{
	if( !m_properties.Exists( const_cast<char*>(name) ) )
		return( 0 );
	Property& p = m_properties[ const_cast<char*>(name) ];
	if( p.type != 'i' )
		return( 0 );
	if( channels )
		*channels = p.channels;
	return( (XeCore::XeInteger*)&p.value.i );
}

XeCore::XeInteger Effect::Properties::getPropertySampler( const char* name )
{
	if( !m_properties.Exists( const_cast<char*>(name) ) )
		return( -1 );
	Property& p = m_properties[ const_cast<char*>(name) ];
	if( p.type != 's' )
		return( -1 );
	return( (XeCore::XeInteger)p.value.s );
}

XeCore::XeHalfMatrix* Effect::Properties::getPropertyMat( const char* name, int* channels )
{
	if( !m_properties.Exists( const_cast<char*>(name) ) )
		return( 0 );
	Property& p = m_properties[ const_cast<char*>(name) ];
	if( p.type != 'm' )
		return( 0 );
	if( channels )
		*channels = p.channels;
	return( (XeCore::XeHalfMatrix*)&p.value.m );
}

XeCore::XeHalf* Effect::Properties::getPropertyArrayHalf( const char* name, int* count, int* channels )
{
	if( !m_properties.Exists( const_cast<char*>(name) ) )
		return( 0 );
	Property& p = m_properties[ const_cast<char*>(name) ];
	if( p.type != 'h' || p.count <= 0 )
		return( 0 );
	if( count )
		*count = p.count;
	if( channels )
		*channels = p.channels;
	return( p.value.ah );
}

XeCore::XeInteger* Effect::Properties::getPropertyArrayInt( const char* name, int* count, int* channels )
{
	if( !m_properties.Exists( const_cast<char*>(name) ) )
		return( 0 );
	Property& p = m_properties[ const_cast<char*>(name) ];
	if( p.type != 'i' || p.count <= 0 )
		return( 0 );
	if( count )
		*count = p.count;
	if( channels )
		*channels = p.channels;
	return( p.value.ai );
}

bool Effect::Properties::eraseProperty( const char* name )
{
	if( !m_properties.Exists( const_cast<char*>(name) ) )
		return( false );
	return( m_properties.Erase( const_cast<char*>(name) ) );
}

Effect::Properties::PropertyElm Effect::Properties::firstProperty()
{
	return( m_properties.FirstPointer() );
}

void Effect::Properties::apply( Effect* effect )
{
	effect->activate();
	for( Effect::Properties::PropertyElm p = firstProperty(); !p.IsEmpty(); p.Next() )
	{
		if( p->Value.type == 'h' )
		{
			if( p->Value.count > 0 )
				effect->uniformArray( p->Key, p->Value.value.ah, p->Value.count, p->Value.channels );
			else
				effect->uniform( p->Key, (XeCore::XeHalfVector*)p->Value.value.v, p->Value.channels );
		}
		else
		if( p->Value.type == 'i' )
		{
			if( p->Value.count > 0 )
				effect->uniformArray( p->Key, p->Value.value.ai, p->Value.count, p->Value.channels );
			else
				effect->uniform( p->Key, (XeCore::XeInteger*)p->Value.value.i, p->Value.channels );
		}
		else
		if( p->Value.type == 's' )
		{
			effect->uniform( p->Key, (XeCore::XeInteger*)&p->Value.value.s, 1 );
		}
		else
		if( p->Value.type == 'm' )
			effect->uniform( p->Key, (XeCore::XeHalfMatrix*)p->Value.value.m, p->Value.channels ? true : false );
	}
	Effect::unactivate();
}
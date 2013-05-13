#pragma once

#include "IRtti.h"
#include "Engine.h"
#include "Asset.h"
#include "../XeCore/Base/XeAssoc.h"

class Effect : public virtual IRtti, public Asset, public virtual MemoryManager::Manageable
{
	RTTI_CLASS_DECLARE( Effect );

public:
	struct Location
	{
													Location() : id( -1 ) {}
		int											id;
	};
													Effect();
													~Effect();
	bool											load( const char* vertname, const char* fragname, const char* ver = "120" );
	void											free();
	void											activate();
	static void										unactivate();
	XeCore::Photon::XeElmShader						getShader();
	const char*										getLog();
	int												locationUniform( const char* name );
	int												locationAttribute( const char* name );
	bool											uniform( const char* loc, XeCore::XeHalfVector* v, int channels = 4 );
	bool											uniform( const char* loc, XeCore::XeInteger* v, int channels = 4 );
	bool											uniform( const char* loc, XeCore::XeHalfMatrix* m, bool trans = false );
	bool											uniformArray( const char* loc, XeCore::XeHalf* v, int count, int channels = 4 );
	bool											uniformArray( const char* loc, XeCore::XeInteger* v, int count, int channels = 4 );
	bool											attribute( const char* loc, XeCore::XeHalfVector* v, int channels = 4 );

	static Asset*									onLoad( AssetManager* manager, XeCore::XeString& name, Params& params, bool keepAlways );
	virtual void									onUnload();

private:
	XeCore::Photon::XeElmShader						m_prog;
	XeCore::Photon::XeElmShader						m_vert;
	XeCore::Photon::XeElmShader						m_frag;
	XeCore::XeString								m_log;
	XeCore::XeAssoc< XeCore::XeString, Location	>	m_attribs;
	XeCore::XeAssoc< XeCore::XeString, Location >	m_uniforms;

public:
	class Properties : public virtual IRtti, public virtual MemoryManager::Manageable
	{
		RTTI_CLASS_DECLARE( Properties );

	public:
		struct Property
		{
			union
			{
				XeCore::XeHalf							v[ 4 ];
				XeCore::XeInteger						i[ 4 ];
				XeCore::XeHalf							m[ 16 ];
				XeCore::XeHalf*							ah;
				XeCore::XeInteger*						ai;
				XeCore::XeInteger						s;
			}											value;
			int											type;
			int											channels;
			int											count;
		};

		typedef XeCore::XeElementPointer< XeCore::XePair< XeCore::XeString, Property > > PropertyElm;

														Properties();
														~Properties();
		void											setPropertyVec( const char* name, XeCore::XeHalfVector& v, int channels );
		void											setPropertyInt( const char* name, XeCore::XeInteger v[ 4 ], int channels );
		void											setPropertySampler( const char* name, XeCore::XeInteger v );
		void											setPropertyMat( const char* name, XeCore::XeHalfMatrix& v, bool trans = false );
		void											setPropertyArrayHalf( const char* name, XeCore::XeHalf* v, int count, int channels );
		void											setPropertyArrayInt( const char* name, XeCore::XeInteger* v, int count, int channels );
		XeCore::XeHalfVector*							getPropertyVec( const char* name, int* channels );
		XeCore::XeInteger*								getPropertyInt( const char* name, int* channels );
		XeCore::XeInteger								getPropertySampler( const char* name );
		XeCore::XeHalfMatrix*							getPropertyMat( const char* name, int* channels );
		XeCore::XeHalf*									getPropertyArrayHalf( const char* name, int* channels, int* count = 0 );
		XeCore::XeInteger*								getPropertyArrayInt( const char* name, int* channels, int* count = 0 );
		bool											eraseProperty( const char* name );
		PropertyElm										firstProperty();
		void											apply( Effect* effect );

	private:
		XeCore::XeAssoc< XeCore::XeString, Property >	m_properties;
	};
};

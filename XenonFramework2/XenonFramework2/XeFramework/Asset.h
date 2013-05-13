#pragma once

#include "IRtti.h"
#include "../XeCore/Base/XeAssoc.h"

#define ASSET_SET_PURE_POINTER(o)	( o )->setAssetPurePointer( o );

class Asset : public virtual IRtti, public virtual MemoryManager::Manageable
{
	RTTI_CLASS_DECLARE( Asset );

	friend class AssetManager;

public:
	class ParamData;

	typedef XeCore::XeAssoc< XeCore::XeString, ParamData > Params;
	typedef XeCore::XeElementPointer< XeCore::XePair< XeCore::XeString, ParamData > > ParamsElm;

									Asset();
	virtual							~Asset();
	static Asset*					onLoad( AssetManager* manager, XeCore::XeString& name, Params& params, bool keepAlways ) { XASSERT( 0, "Need implementation in child class!" ); return( 0 ); }
	virtual void					onUnload() = 0;
	XeCore::XeString&				getAssetName();
	unsigned int					getAssetLevel();
	bool							isAssetLoaded();
	AssetManager*					getAssetManager();
	void*							getAssetPurePointer();

	static void						release( Asset* asset );

private:
	AssetManager*					m_manager;
	bool							m_loaded;
	XeCore::XeString				m_name;
	unsigned int					m_level;
	void*							m_purePointer;

protected:
	void							setAssetPurePointer( void* pp );

public:
	class ParamData
	{
	public:
		enum Type
		{
			tValue,
			tParams,
			tEmpty
		};

									ParamData();
									~ParamData();
		void						setValue( XeCore::XeString& name, XeCore::XeString& v );
		void						setParams( XeCore::XeString& name, const char* grouptype );
		void						setEmpty();
		XeCore::XeString&			getValue();
		Params&						getParams();
		Type						getType();
		XeCore::XeString&			getName();
		XeCore::XeString&			getGroupType();

	private:
		void*						m_data;
		Type						m_type;
		XeCore::XeString			m_name;
		XeCore::XeString			m_grouptype;
		Params						m_staticParams;
		XeCore::XeString			m_staticValue;
	};
};
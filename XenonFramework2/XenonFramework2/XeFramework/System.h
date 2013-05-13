#pragma once

#include "Base.h"
#include "../XeCore/Base/XeAssoc.h"

class System
{
public:
	enum IO
	{
		ioOpen,
		ioSave,
		ioFile,
		ioDirectory,

		ioCount
	};

	enum FileFlags
	{
		ffEmpty = 0x0,
		ffOverwritePrompt = 0x1,
		ffMultiSelect = 0x2,
		ffNoReadonlySelect = 0x4,
		ffNoPlacesBar = 0x8,

	};

	typedef XeCore::XeElements< XeCore::XePair< XeCore::XeString, IO > > FileList;
	typedef XeCore::XeElementPointer< XeCore::XePair< XeCore::XeString, IO > > FileListElm;
	typedef XeCore::XePair< XeCore::XeString, IO > FileListData;

	static int		message( const char* text, const char* title = 0, unsigned int flags = 0 );
	static void		open( const char* file, const char* parameters = 0, const char* initdir = 0 );
	static bool		getFilename( XeCore::XeString& result, IO type = ioOpen, const char* extensions = 0, const char* title = 0, const char* initdir = 0, FileFlags flags = ffEmpty );
	static bool		getDirname( XeCore::XeString& result, const char* title = 0, const char* initdir = 0 );
	static void		listFiles( FileList& result, const char* path );
};
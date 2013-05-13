#include "System.h"
#include "Engine.h"
#include <ShlObj.h>

int System::message( const char* text, const char* title, unsigned int flags )
{
	return( MessageBox( Global::use().engine->getWindow(), text, title ? title : "XenonFramework2", flags ) );
}

void System::open( const char* file, const char* parameters, const char* initdir )
{
	ShellExecute( Global::use().engine->getWindow(), "OPEN", file, parameters, initdir, SW_SHOWDEFAULT );
}

bool System::getFilename( XeCore::XeString& result, IO type, const char* extensions, const char* title, const char* initdir, FileFlags flags )
{
	OPENFILENAME file = { 0 };
	char dir[ MAX_PATH ] = { 0 };
	char path[ MAX_PATH ] = { 0 };
	if( !initdir )
		GetCurrentDirectory( MAX_PATH, dir );
	file.lStructSize = sizeof( OPENFILENAME );
	file.hwndOwner = Global::use().engine->getWindow();
	file.lpstrFile = path;
	file.nMaxFile = MAX_PATH;
	if( !initdir )
		file.lpstrInitialDir = dir;
	else
		file.lpstrInitialDir = initdir;
	if( title )
		file.lpstrTitle = title;
	file.Flags = OFN_EXPLORER | OFN_NOCHANGEDIR;
	file.FlagsEx = 0;
	if( flags & ffOverwritePrompt )
		file.Flags |= OFN_OVERWRITEPROMPT;
	if( flags & ffMultiSelect )
		file.Flags |= OFN_ALLOWMULTISELECT;
	if( flags & ffNoReadonlySelect )
		file.Flags |= OFN_HIDEREADONLY;
	if( flags & ffNoPlacesBar )
		file.FlagsEx |= OFN_EX_NOPLACESBAR;
	if( type == ioOpen )
		file.Flags |= OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	XeCore::XeString ext;
	if( extensions )
	{
		ext.Format( "%s|", extensions );
		unsigned int len = ext.Length();
		for( unsigned int i = 0; i < len; i++ )
			if( ext.Get()[ i ] == '|' )
				ext.Get()[ i ] = 0;
		file.lpstrFilter = ext.Get();
	}
	if( type == ioOpen )
	{
		if( GetOpenFileName( &file ) )
		{
			result = path;
			return( true );
		}
	}
	else
	if( type == ioSave )
	{
		if( GetSaveFileName( &file ) )
		{
			result = path;
			return( true );
		}
	}
	return( false );
}

bool System::getDirname( XeCore::XeString& result, const char* title, const char* initdir )
{
	BROWSEINFO bi = { 0 };
	bi.hwndOwner = Global::use().engine->getWindow();
	if( title )
		bi.lpszTitle = title;
	LPITEMIDLIST pidl = SHBrowseForFolder( &bi );
	if( pidl != 0 )
	{
		char* path[ MAX_PATH ];
		if( SHGetPathFromIDList( pidl, (char*)path ) )
			result = (char*)path;
		IMalloc* imalloc = 0;
		if( SUCCEEDED( SHGetMalloc( &imalloc ) ) )
		{
			imalloc->Free( pidl );
			imalloc->Release();
			return( true );
		}
	}
	return( false );
}

void System::listFiles( FileList& result, const char* path )
{
	WIN32_FIND_DATA find;
	HANDLE handle;
	result.Clear();
	handle = FindFirstFile( path, &find );
	if( handle != INVALID_HANDLE_VALUE )
	{
		do
		{
			FileListElm elm = result.AddPointer( FileListData() );
			elm->Key = find.cFileName;
			if( find.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
				elm->Value = ioDirectory;
			else
				elm->Value = ioFile;
		}while( FindNextFile( handle, &find ) );
	}
	FindClose( handle );
}
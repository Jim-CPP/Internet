// TextFileClass.h

#pragma once

#include <windows.h>

#include "Ascii.h"
#include "Common.h"

#define TEXT_FILE_CLASS_UNABLE_TO_GET_FILE_SIZE_ERROR_MESSAGE_FORMAT_STRING		"Unable to get size of file %s"
#define TEXT_FILE_CLASS_UNABLE_TO_OPEN_FILE_ERROR_MESSAGE_FORMAT_STRING			"Unable to open file %s"
#define TEXT_FILE_CLASS_UNABLE_TO_READ_FILE_ERROR_MESSAGE_FORMAT_STRING			"Unable to read file %s"

class TextFile
{
public:
	TextFile();
	~TextFile();

	TextFile& operator = ( HANDLE hTextFile );

	BOOL operator == ( HANDLE hTextFile );

	BOOL operator != ( HANDLE hTextFile );

	operator HANDLE();

	BOOL Close();

	BOOL Create( LPCTSTR lpszFileName );

	int DisplayText( HWND hWndParent, LPTSTR lpszTitle, UINT uType = ( MB_OK | MB_ICONINFORMATION ) );

	DWORD GetSize();

	BOOL Open( LPCTSTR lpszFileName );

	DWORD Read( DWORD dwNumberOfBytesToRead );

	BOOL Read( LPTSTR lpszFileText, DWORD dwNumberOfBytesToRead );

	BOOL Write( LPCTSTR lpszFileText, DWORD dwNumberOfBytesToWrite );

protected:
	HANDLE m_hTextFile;
	LPTSTR m_lpszFileText;

}; // End of class TextFile

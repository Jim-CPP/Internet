// FileClass.h

#pragma once

#include <windows.h>

#include "Ascii.h"
#include "Common.h"

#define FILE_CLASS_UNABLE_TO_GET_FILE_SIZE_ERROR_MESSAGE_FORMAT_STRING			"Unable to get size of file %s"
#define FILE_CLASS_UNABLE_TO_OPEN_FILE_ERROR_MESSAGE_FORMAT_STRING				"Unable to open file %s"
#define FILE_CLASS_UNABLE_TO_READ_FILE_ERROR_MESSAGE_FORMAT_STRING				"Unable to read file %s"

class File
{
public:
	File();
	~File();

	File& operator = ( HANDLE hFile );

	BOOL operator == ( HANDLE hFile );

	BOOL operator != ( HANDLE hFile );

	operator HANDLE();

	BOOL Close();

	BOOL Create( LPCTSTR lpszFileName );

	DWORD GetSize();

	BOOL Open( LPCTSTR lpszFileName );

	BOOL Read( LPVOID lpFileText, DWORD dwNumberOfBytesToRead );

	BOOL Write( LPVOID lpFileText, DWORD dwNumberOfBytesToWrite );

protected:
	HANDLE m_hFile;

}; // End of class File

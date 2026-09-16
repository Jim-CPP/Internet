// InternetFileClass.h

#pragma once

#include <windows.h>
#include <wininet.h>

#include "Ascii.h"
#include "Common.h"

class InternetFile
{
public:
	InternetFile();
	~InternetFile();

	InternetFile& operator = ( HINTERNET hInternetFile );

	BOOL operator == ( HINTERNET hInternetFile );

	BOOL operator != ( HINTERNET hInternetFile );

	operator HINTERNET();

	BOOL Close();

	BOOL Open( HINTERNET hInternet, LPCSTR lpszUrl, LPCSTR lpszHeaders = NULL, DWORD dwHeadersLength = 0, DWORD dwFlags = 0, DWORD_PTR dwContext = 0 );

	BOOL Read( LPVOID lpBuffer, DWORD dwNumberOfBytesToRead, LPDWORD lpdwNumberOfBytesRead );

protected:
	HINTERNET m_hInternetFile;

}; // End of class InternetFile

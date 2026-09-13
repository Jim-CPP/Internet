// InternetClass.h

#pragma once

#include <windows.h>
#include <wininet.h>

#include "Ascii.h"
#include "Common.h"

#define INTERNET_CLASS_USER_AGENT												"InetURL/1.0"

#define INTERNET_CLASS_DOWNLOAD_BUFFER_LENGTH									1024

#define INTERNET_CLASS_UNABLE_TO_CONNECT_TO_INTERNET_ERROR_MESSAGE				"Unable to connect to internet"

class Internet
{
public:
	Internet();
	~Internet();

	Internet& operator = ( HINTERNET hInternet );

	BOOL operator == ( HINTERNET hInternet );

	BOOL operator != ( HINTERNET hInternet );

	operator HINTERNET();

	BOOL Connect( LPCSTR lpszAgent = INTERNET_CLASS_USER_AGENT, DWORD dwAccessType = INTERNET_OPEN_TYPE_PRECONFIG, LPCSTR lpszProxy = NULL, LPCSTR lpszProxyBypass = NULL, DWORD dwFlags = 0 );

	BOOL Disconnect();

protected:
	HINTERNET m_hInternet;

}; // End of class Internet

// InternetFileClass.cpp

#include "InternetFileClass.h"

InternetFile::InternetFile()
{
	// Initialise member variables
	ZeroMemory( &m_hInternetFile, sizeof( m_hInternetFile ) );

} // End of function InternetFile::InternetFile

InternetFile::~InternetFile()
{
	// Clear member variables
	ZeroMemory( &m_hInternetFile, sizeof( m_hInternetFile ) );

} // End of function InternetFile::~InternetFile

InternetFile& InternetFile::operator = ( HINTERNET hInternetFile )
{
	// Update member variables
	m_hInternetFile = hInternetFile;

	return *this;

} // End of function InternetFile::operator =

BOOL InternetFile::operator == ( HINTERNET hInternetFile )
{
	BOOL bResult = FALSE;

	// See if item equals member item
	if( hInternetFile == m_hInternetFile )
	{
		// Item equals member item

		// Update return value
		bResult = TRUE;

	} // End of item equals member item

	return bResult;

} // End of function InternetFile::operator ==

BOOL InternetFile::operator != ( HINTERNET hInternetFile )
{
	BOOL bResult = FALSE;

	// See if item is different to member item
	if( hInternetFile != m_hInternetFile )
	{
		// Item is different to member item

		// Update return value
		bResult = TRUE;

	} // End of item is different to member item

	return bResult;

} // End of function InternetFile::operator !=

InternetFile::operator HINTERNET()
{
	return m_hInternetFile;

} // End of function InternetFile::operator HINTERNET()

BOOL InternetFile::Close()
{
	// Close internet file
	return InternetCloseHandle( m_hInternetFile );

} // End of function InternetFile::Close

BOOL InternetFile::Open( HINTERNET hInternet, LPCSTR lpszUrl, LPCSTR lpszHeaders, DWORD dwHeadersLength, DWORD dwFlags, DWORD_PTR dwContext )
{
	BOOL bResult = FALSE;

	// Open internet file
	m_hInternetFile = InternetOpenUrl( hInternet, lpszUrl, lpszHeaders, dwHeadersLength, dwFlags, dwContext );

	// Ensure that internet file was opened
	if( m_hInternetFile )
	{
		// Successfully opened internet file

		// Update return value
		bResult = TRUE;

	} // End of successfully opened internet file

	return bResult;

} // End of function InternetFile::Open

BOOL InternetFile::Read( LPVOID lpBuffer, DWORD dwNumberOfBytesToRead, LPDWORD lpdwNumberOfBytesRead )
{
	// Read internet file
	return InternetReadFile( m_hInternetFile, lpBuffer, dwNumberOfBytesToRead, lpdwNumberOfBytesRead );

} // End of function InternetFile::Read

/*
InternetFile::
{
} // End of function InternetFile::
*/

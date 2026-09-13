// InternetClass.cpp

#include "InternetClass.h"

Internet::Internet()
{
	// Initialise member variables
	ZeroMemory( &m_hInternet, sizeof( m_hInternet ) );

} // End of function Internet::Internet

Internet::~Internet()
{
	// Clear member variables
	ZeroMemory( &m_hInternet, sizeof( m_hInternet ) );

} // End of function Internet::~Internet

Internet& Internet::operator = ( HINTERNET hInternet )
{
	// Update member variables
	m_hInternet = hInternet;

	return *this;

} // End of function Internet::operator =

BOOL Internet::operator == ( HINTERNET hInternet )
{
	BOOL bResult = FALSE;

	// See if item equals member item
	if( hInternet == m_hInternet )
	{
		// Item equals member item

		// Update return value
		bResult = TRUE;

	} // End of item equals member item

	return bResult;

} // End of function Internet::operator ==

BOOL Internet::operator != ( HINTERNET hInternet )
{
	BOOL bResult = FALSE;

	// See if item is different to member item
	if( hInternet != m_hInternet )
	{
		// Item is different to member item

		// Update return value
		bResult = TRUE;

	} // End of item is different to member item

	return bResult;

} // End of function Internet::operator !=

Internet::operator HINTERNET()
{
	return m_hInternet;

} // End of function Internet::operator HINTERNET()

BOOL Internet::Connect( LPCSTR lpszAgent, DWORD dwAccessType, LPCSTR lpszProxy, LPCSTR lpszProxyBypass, DWORD dwFlags )
{
	BOOL bResult = FALSE;

	// Connect to internet
	m_hInternet = InternetOpen( lpszAgent, dwAccessType, lpszProxy, lpszProxyBypass, dwFlags );

	// Ensure that internet was connected to
	if( m_hInternet )
	{
		// Successfully connected to internet

		// Update return value
		bResult = TRUE;

	} // End of successfully connected to internet

	return bResult;

} // End of function Internet::Connect

BOOL Internet::Disconnect()
{
	// Disconnect from internet
	return InternetCloseHandle( m_hInternet );

} // End of function Internet::Disconnect

/*
Internet::
{
} // End of function Internet::
*/

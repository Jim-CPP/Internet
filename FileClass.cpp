// FileClass.cpp

#include "FileClass.h"

File::File()
{
	// Initialise member variables
	ZeroMemory( &m_hFile, sizeof( m_hFile ) );

} // End of function File::File

File::~File()
{
	// Clear member variables
	ZeroMemory( &m_hFile, sizeof( m_hFile ) );

} // End of function File::~File

File& File::operator = ( HANDLE hFile )
{
	// Update member variables
	m_hFile = hFile;

	return *this;

} // End of function File::operator =

BOOL File::operator == ( HANDLE hFile )
{
	BOOL bResult = FALSE;

	// See if item equals member item
	if( hFile == m_hFile )
	{
		// Item equals member item

		// Update return value
		bResult = TRUE;

	} // End of item equals member item

	return bResult;

} // End of function File::operator ==

BOOL File::operator != ( HANDLE hFile )
{
	BOOL bResult = FALSE;

	// See if item is different to member item
	if( hFile != m_hFile )
	{
		// Item is different to member item

		// Update return value
		bResult = TRUE;

	} // End of item is different to member item

	return bResult;

} // End of function File::operator !=

File::operator HANDLE()
{
	return m_hFile;

} // End of function File::operator HANDLE()

BOOL File::Close()
{
	// Close file
	return CloseHandle( m_hFile );

} // End of function File::Close

BOOL File::Create( LPCTSTR lpszFileName )
{
	BOOL bResult = FALSE;

	// Create file
	m_hFile = CreateFile( lpszFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );

	// Ensure that file was opened
	if( m_hFile != INVALID_HANDLE_VALUE )
	{
		// Successfully created file

		// Update return value
		bResult = TRUE;

	} // End of successfully created file

	return bResult;

} // End of function File::Create

DWORD File::GetSize()
{
	// Get file size
	return GetFileSize( m_hFile, NULL );

} // End of function File::GetSize

BOOL File::Open( LPCTSTR lpszFileName )
{
	BOOL bResult = FALSE;

	// Open file
	m_hFile = CreateFile( lpszFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );

	// Ensure that file was opened
	if( m_hFile != INVALID_HANDLE_VALUE )
	{
		// Successfully opened file

		// Update return value
		bResult = TRUE;

	} // End of successfully opened file

	return bResult;

} // End of function File::Open

BOOL File::Read( LPVOID lpFileText, DWORD dwNumberOfBytesToRead )
{
	// Read file
	return ReadFile( m_hFile, lpFileText, dwNumberOfBytesToRead, NULL, NULL );

} // End of function File::Read

BOOL File::Write( LPVOID lpFileText, DWORD dwNumberOfBytesToWrite )
{
	// Write file
	return WriteFile( m_hFile, lpFileText, dwNumberOfBytesToWrite, NULL, NULL );

} // End of function File::Write

/*
File::
{
} // End of function File::
*/

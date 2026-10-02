// TextFileClass.cpp

#include "TextFileClass.h"

TextFile::TextFile()
{
	// Initialise member variables
	ZeroMemory( &m_hTextFile, sizeof( m_hTextFile ) );
	m_lpszFileText = NULL;

} // End of function TextFile::TextFile

TextFile::~TextFile()
{
	// Clear member variables
	ZeroMemory( &m_hTextFile, sizeof( m_hTextFile ) );

	// See if file text is valid
	if( m_lpszFileText )
	{
		// File text is valid

		// Free string memory
		delete [] m_lpszFileText;

	} // End of file text is valid

} // End of function TextFile::~TextFile

TextFile& TextFile::operator = ( HANDLE hTextFile )
{
	// Update member variables
	m_hTextFile = hTextFile;

	return *this;

} // End of function TextFile::operator =

BOOL TextFile::operator == ( HANDLE hTextFile )
{
	BOOL bResult = FALSE;

	// See if item equals member item
	if( hTextFile == m_hTextFile )
	{
		// Item equals member item

		// Update return value
		bResult = TRUE;

	} // End of item equals member item

	return bResult;

} // End of function TextFile::operator ==

BOOL TextFile::operator != ( HANDLE hTextFile )
{
	BOOL bResult = FALSE;

	// See if item is different to member item
	if( hTextFile != m_hTextFile )
	{
		// Item is different to member item

		// Update return value
		bResult = TRUE;

	} // End of item is different to member item

	return bResult;

} // End of function TextFile::operator !=

TextFile::operator HANDLE()
{
	return m_hTextFile;

} // End of function TextFile::operator HANDLE()

BOOL TextFile::Close()
{
	// Close text file
	return CloseHandle( m_hTextFile );

} // End of function TextFile::Close

BOOL TextFile::Create( LPCTSTR lpszFileName )
{
	BOOL bResult = FALSE;

	// Create text file
	m_hTextFile = CreateFile( lpszFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );

	// Ensure that text file was opened
	if( m_hTextFile != INVALID_HANDLE_VALUE )
	{
		// Successfully created text file

		// Update return value
		bResult = TRUE;

	} // End of successfully created text file

	return bResult;

} // End of function TextFile::Create

int TextFile::DisplayText( HWND hWndParent, LPTSTR lpszTitle, UINT uType )
{
	// Display file text
	return MessageBox( hWndParent, m_lpszFileText, lpszTitle, uType );

} // End of function TextFile::DisplayText

DWORD TextFile::GetSize()
{
	// Get text file size
	return GetFileSize( m_hTextFile, NULL );

} // End of function TextFile::GetSize

BOOL TextFile::Open( LPCTSTR lpszFileName )
{
	BOOL bResult = FALSE;

	// Open text file
	m_hTextFile = CreateFile( lpszFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );

	// Ensure that text file was opened
	if( m_hTextFile != INVALID_HANDLE_VALUE )
	{
		// Successfully opened text file

		// Update return value
		bResult = TRUE;

	} // End of successfully opened text file

	return bResult;

} // End of function TextFile::Open

DWORD TextFile::Read( DWORD dwNumberOfBytesToRead )
{
	DWORD dwResult = 0;

	// See if file text is valid
	if( m_lpszFileText )
	{
		// File text is valid

		// Free string memory
		delete [] m_lpszFileText;

	} // End of file text is valid

	// Allocate string memory
	m_lpszFileText = new char[ dwNumberOfBytesToRead + sizeof( char ) ];

	// Read file text
	ReadFile( m_hTextFile, m_lpszFileText, dwNumberOfBytesToRead, &dwResult, NULL );

	return dwResult;

} // End of function TextFile::Read

BOOL TextFile::Read( LPTSTR lpszFileText, DWORD dwNumberOfBytesToRead )
{
	// Read text file
	return ReadFile( m_hTextFile, lpszFileText, dwNumberOfBytesToRead, NULL, NULL );

} // End of function TextFile::Read

BOOL TextFile::Write( LPCTSTR lpszFileText, DWORD dwNumberOfBytesToWrite )
{
	// Write text file
	return WriteFile( m_hTextFile, lpszFileText, dwNumberOfBytesToWrite, NULL, NULL );

} // End of function TextFile::Write


/*
TextFile::
{
} // End of function TextFile::
*/

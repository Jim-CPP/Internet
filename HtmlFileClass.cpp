// HtmlFileClass.cpp

#include "HtmlFileClass.h"

HtmlFile::HtmlFile()
{
	// Call default constructor
	TextFile();

} // End of function HtmlFile::HtmlFile

HtmlFile::~HtmlFile()
{
} // End of function HtmlFile::~HtmlFile

int HtmlFile::ProcessTags( BOOL( *lpTagFunction )( LPCTSTR lpszTag ) )
{
	int nResult = 0;

	LPTSTR lpszStartOfTag;
	LPTSTR lpszEndOfTag;
	DWORD dwMaximumTagLength = STRING_LENGTH;
	DWORD dwTagLengthIncludingTerminator;

	// Find start of first tag
	lpszStartOfTag = strchr( m_lpszFileText, HTML_FILE_CLASS_START_OF_TAG_CHARACTER );

	// Allocate string memory
	LPTSTR lpszTag = new char[ dwMaximumTagLength + sizeof( char ) ];

	// Loop through all tags
	while( lpszStartOfTag )
	{
		// Find end of tag
		lpszEndOfTag = strchr( lpszStartOfTag, HTML_FILE_CLASS_END_OF_TAG_CHARACTER );

		// Ensure that end of tag was found
		if( lpszEndOfTag )
		{
			// Successfully found end of tag

			//   <tag>
			//   |   |
			// 0123456

			// Calculate tag length (including terminator)
			dwTagLengthIncludingTerminator = ( ( lpszEndOfTag - lpszStartOfTag ) + 2 );

			// Ensure that tag length is not greater than maximum
			if( dwTagLengthIncludingTerminator > dwMaximumTagLength )
			{
				// Tag length is greater than maximum

				// Set tag length to maximum
				dwTagLengthIncludingTerminator = dwMaximumTagLength;

			} // End of tag length is greater than maximum

			// Store tag
			lstrcpyn( lpszTag, lpszStartOfTag, dwTagLengthIncludingTerminator );

			// Call tag function
			if( ( *lpTagFunction )( lpszTag ) )
			{
				// Successfully called tag function

				// Update return value
				nResult ++;

			} // End of successfully called tag function

			// Find start of next tag
			lpszStartOfTag = strchr( lpszEndOfTag, HTML_FILE_CLASS_START_OF_TAG_CHARACTER );

		} // End of successfully found end of tag
		else
		{
			// Unable to find end of tag

			// Force exit from loop
			lpszStartOfTag = NULL;

		} // End of unable to find end of tag

	}; // End of loop through all tags

	return nResult;

} // End of function HtmlFile::ProcessTags

/*
HtmlFile::
{
} // End of function HtmlFile::
*/

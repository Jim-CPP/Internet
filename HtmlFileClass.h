// HtmlFileClass.h

#pragma once

#include <windows.h>

#include "Ascii.h"
#include "Common.h"

#include "TextFileClass.h"

#define HTML_FILE_CLASS_START_OF_TAG_CHARACTER									'<'
#define HTML_FILE_CLASS_END_OF_TAG_CHARACTER									'>'

class HtmlFile : public TextFile
{
public:
	HtmlFile();
	~HtmlFile();

	int ProcessTags( BOOL( *lpTagFunction )( LPCTSTR lpszTag ) );

protected:

}; // End of class HtmlFile

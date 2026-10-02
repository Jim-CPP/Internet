// HtmlFileClass.h

#pragma once

#include <windows.h>

#include "Ascii.h"
#include "Common.h"

#include "TextFileClass.h"

#define TEMPLATE_WINDOW_CLASS_NAME												WC_LISTBOX
#define TEMPLATE_WINDOW_CLASS_DEFAULT_TEXT										NULL
#define TEMPLATE_WINDOW_CLASS_DEFAULT_MENU										NULL
#define TEMPLATE_WINDOW_CLASS_DEFAULT_EXTENDED_STYLE							0
#define TEMPLATE_WINDOW_CLASS_DEFAULT_STYLE										( WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOINTEGRALHEIGHT | LBS_NOTIFY )
#define TEMPLATE_WINDOW_CLASS_DEFAULT_LEFT										0
#define TEMPLATE_WINDOW_CLASS_DEFAULT_TOP										0
#define TEMPLATE_WINDOW_CLASS_DEFAULT_WIDTH										100
#define TEMPLATE_WINDOW_CLASS_DEFAULT_HEIGHT									100
#define TEMPLATE_WINDOW_CLASS_DEFAULT_LP_PARAM									NULL

class HtmlFile : public TextFile
{
public:
	HtmlFile();
	~HtmlFile();

protected:

}; // End of class HtmlFile

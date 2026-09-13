// EditWindow.h

#pragma once

#include <windows.h>
#include <commctrl.h>

#include "Ascii.h"
#include "Common.h"

#define EDIT_WINDOW_CLASS_NAME													WC_EDIT

#define EDIT_WINDOW_EXTENDED_STYLE												0
#define EDIT_WINDOW_STYLE														( WS_CHILD | WS_VISIBLE | WS_BORDER )
#define EDIT_WINDOW_TEXT														NULL

BOOL EditWindowCreate( HWND hWndParent, HINSTANCE hInstance, HFONT hFont, LPCTSTR lpszText );

LRESULT EditWindowGetText( LPTSTR lpszText, DWORD dwMaximumBufferLength = STRING_LENGTH );

LRESULT EditWindowHandleCommandMessage( HWND hWndMain, WPARAM wParam, LPARAM lParam, void( *lpUpdateFunction )( int nTextLength ) );

BOOL EditWindowMove( int nLeft, int nTop, int nWidth, int nHeight );

void EditWindowSelect( int nStart = 0, int nEnd = -1 );

HWND EditWindowSetFocus();

BOOL IsEditWindow( HWND hWndSupplied );

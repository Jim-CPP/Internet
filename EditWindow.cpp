// EditWindow.cpp

#include "EditWindow.h"

// Global variables
static HWND g_hWndEdit;

BOOL EditWindowCreate( HWND hWndParent, HINSTANCE hInstance, HFONT hFont, LPCTSTR lpszText )
{
	BOOL bResult = FALSE;

	// Create edit window
	g_hWndEdit = CreateWindowEx( EDIT_WINDOW_EXTENDED_STYLE, EDIT_WINDOW_CLASS_NAME, lpszText, EDIT_WINDOW_STYLE, 0, 0, 0, 0, hWndParent, ( HMENU )NULL, hInstance, NULL );

	// Ensure that edit window was created
	if( g_hWndEdit )
	{
		// Successfully created edit window

		// Set edit window font
		SendMessage( g_hWndEdit, WM_SETFONT, ( WPARAM )hFont, ( LPARAM )TRUE );

		// Update return value
		bResult = TRUE;

	} // End of successfully created edit window

	return bResult;

} // End of function EditWindowCreate

LRESULT EditWindowGetText( LPTSTR lpszText, DWORD dwMaximumBufferLength )
{
	// Get text
	return SendMessage( g_hWndEdit, WM_GETTEXT, ( WPARAM )dwMaximumBufferLength, ( LPARAM )lpszText );

} // End of function EditWindowGetText

LRESULT EditWindowHandleCommandMessage( HWND hWndMain, WPARAM wParam, LPARAM lParam, void( *lpUpdateFunction )( int nTextLength ) )
{
	LRESULT lResult = 0;

	// Select edit window notification code
	switch( HIWORD( wParam ) )
	{
		case EN_UPDATE:
		{
			// An edit window update notification code
			int nTextLength;

			// Get text length
			nTextLength = SendMessage( g_hWndEdit, WM_GETTEXTLENGTH, ( WPARAM )NULL, ( LPARAM )NULL );

			// Call update function
			( *lpUpdateFunction )( nTextLength );

			// Break out of switch
			break;

		} // End of a edit window update notification code
		default:
		{
			// Default edit window notification code

			// Call default procedure
			lResult = DefWindowProc( hWndMain, WM_COMMAND, wParam, lParam );

			// Break out of switch
			break;

		} // End of default edit window notification code

	}; // End of selection for edit window notification code

	return lResult;

} // End of function ListBoxWindowHandleCommandMessage

BOOL EditWindowMove( int nLeft, int nTop, int nWidth, int nHeight )
{
	// Move edit window
	return MoveWindow( g_hWndEdit, nLeft, nTop, nWidth, nHeight, TRUE );

} // End of function EditWindowMove

void EditWindowSelect( int nStart, int nEnd )
{
	// Select edit window text
	SendMessage( g_hWndEdit, EM_SETSEL, ( WPARAM )nStart, ( LPARAM )nEnd );

} // End of function EditWindowSelect

HWND EditWindowSetFocus()
{
	// Focus on edit window
	return SetFocus( g_hWndEdit );

} // End of function EditWindowSetFocus

BOOL IsEditWindow( HWND hWndSupplied )
{
	BOOL bResult = FALSE;

	// See if supplied window is edit window
	if( hWndSupplied == g_hWndEdit )
	{
		// Supplied window is edit window

		// Update return value
		bResult = TRUE;

	} // End of supplied window is edit window

	return bResult;

} // End of function IsEditWindow

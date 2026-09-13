// ButtonWindow.cpp

#include "ButtonWindow.h"

// Global variables
static HWND g_hWndButton;

BOOL ButtonWindowCreate( HWND hWndParent, HINSTANCE hInstance, HFONT hFont )
{
	BOOL bResult = FALSE;

	// Create button window
	g_hWndButton = CreateWindowEx( BUTTON_WINDOW_EXTENDED_STYLE, BUTTON_WINDOW_CLASS_NAME, BUTTON_WINDOW_TEXT, BUTTON_WINDOW_STYLE, 0, 0, 0, 0, hWndParent, ( HMENU )BUTTON_WINDOW_ID, hInstance, NULL );

	// Ensure that button window was created
	if( g_hWndButton )
	{
		// Successfully created button window

		// Set button window font
		SendMessage( g_hWndButton, WM_SETFONT, ( WPARAM )hFont, ( LPARAM )TRUE );

		// Update return value
		bResult = TRUE;

	} // End of successfully created button window

	return bResult;

} // End of function ButtonWindowCreate

BOOL ButtonWindowEnable( BOOL bEnableOrDisable )
{
	// Enable (or disable) button window
	return EnableWindow( g_hWndButton, bEnableOrDisable );

} // End of function ButtonWindowEnable

BOOL ButtonWindowMove( int nLeft, int nTop, int nWidth, int nHeight )
{
	// Move button window
	return MoveWindow( g_hWndButton, nLeft, nTop, nWidth, nHeight, TRUE );

} // End of function ButtonWindowMove

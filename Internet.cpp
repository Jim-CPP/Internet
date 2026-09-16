// Internet.cpp

#include "Internet.h"

// Global variables
Internet g_internet;

void EditWindowUpdateFunction( int nTextLength )
{
	// See if edit window contains text
	if( nTextLength == 0 )
	{
		// Edit window is empty

		// Disable button window
		ButtonWindowEnable( FALSE );

	} // End of edit window is empty
	else
	{
		// Edit window contains text

		// Enable button window
		ButtonWindowEnable( TRUE );

	} // End of edit window contains text

} // End of function EditWindowUpdateFunction

int ShowAboutMessage( HWND hWndOwner )
{
	int nResult;

	MSGBOXPARAMS msgBoxParams;

	// Clear message box parameter structure
	ZeroMemory( &msgBoxParams, sizeof( msgBoxParams ) );

	// Initialise message box parameter structure
	msgBoxParams.cbSize			= sizeof( MSGBOXPARAMS );
	msgBoxParams.hwndOwner		= hWndOwner;
	msgBoxParams.hInstance		= NULL; // Must be null to use standard system-defined icons
	msgBoxParams.lpszText		= ABOUT_MESSAGE_TEXT;
	msgBoxParams.lpszCaption	= ABOUT_MESSAGE_CAPTION;
	msgBoxParams.dwStyle		= ( MB_OK | MB_USERICON );
	msgBoxParams.lpszIcon		= MAIN_WINDOW_CLASS_ICON_NAME;

	// Show message box
	nResult = MessageBoxIndirect( &msgBoxParams );

	return nResult;

} // End of function ShowAboutMessage

LRESULT CALLBACK MainWindowProcedure( HWND hWndMain, UINT uMessage, WPARAM wParam, LPARAM lParam )
{
	LRESULT lResult = 0;

	// Select message
	switch( uMessage )
	{
		case WM_CREATE:
		{
			// A create message
			HINSTANCE hInstance;
			HFONT hFont;

			// Get instance
			hInstance = ( ( LPCREATESTRUCT )lParam )->hInstance;

			// Get font
			hFont = ( HFONT )GetStockObject( DEFAULT_GUI_FONT );

			// Create edit window
			if( EditWindowCreate( hWndMain, hInstance, hFont, DEFAULT_URL ) )
			{
				// Successfully created edit window

				// Create button window
				if( ButtonWindowCreate( hWndMain, hInstance, hFont ) )
				{
					// Successfully created button window

					// Create list box window
					if( ListBoxWindowCreate( hWndMain, hInstance, hFont ) )
					{
						// Successfully created list box window

						// Create status bar window
						if( StatusBarWindowCreate( hWndMain, hInstance, hFont ) )
						{
							// Successfully created status bar window

							// Select edit window text
							EditWindowSelect();

						} // End of successfully created status bar window

					} // End of successfully created list box window

				} // End of successfully created button window

			} // End of successfully created edit window

			// Break out of switch
			break;

		} // End of a create message
		case WM_SIZE:
		{
			// A size message
			int nClientWidth;
			int nClientHeight;
			int nStatusBarWindowHeight;
			int nEditWindowWidth;
			int nButtonWindowLeft;
			int nListBoxWindowHeight;
			int nListBoxWindowTop;

			// Store client size
			nClientWidth	= LOWORD( lParam );
			nClientHeight	= HIWORD( lParam );

			// Size status bar window
			nStatusBarWindowHeight = StatusBarWindowSize();

			// Calculate control window sizes
			nListBoxWindowHeight	= ( nClientHeight - ( BUTTON_WINDOW_HEIGHT + nStatusBarWindowHeight ) + WINDOW_BORDER_HEIGHT );
			nEditWindowWidth		= ( ( nClientWidth - BUTTON_WINDOW_WIDTH ) + WINDOW_BORDER_WIDTH );

			// Calculate control window positions
			nButtonWindowLeft		= ( nEditWindowWidth - WINDOW_BORDER_WIDTH );
			nListBoxWindowTop		= ( BUTTON_WINDOW_HEIGHT - WINDOW_BORDER_HEIGHT );

			// Move control windows
			EditWindowMove( 0, 0, nEditWindowWidth, BUTTON_WINDOW_HEIGHT );
			ButtonWindowMove( nButtonWindowLeft, 0, BUTTON_WINDOW_WIDTH, BUTTON_WINDOW_HEIGHT );
			ListBoxWindowMove( 0, nListBoxWindowTop, nClientWidth, nListBoxWindowHeight );

			// Break out of switch
			break;

		} // End of a size message
		case WM_ACTIVATE:
		{
			// An activate message

			// Focus on edit window
			EditWindowSetFocus();

			// Break out of switch
			break;

		} // End of an activate message
		case WM_GETMINMAXINFO:
		{
			// A get min max info message
			MINMAXINFO FAR *lpMinMaxInfo;

			// Get min max info structure
			lpMinMaxInfo = ( MINMAXINFO FAR * )lParam;

			// Update min max info structure
			lpMinMaxInfo->ptMinTrackSize.x = MAIN_WINDOW_MINIMUM_WIDTH;
			lpMinMaxInfo->ptMinTrackSize.y = MAIN_WINDOW_MINIMUM_HEIGHT;

			// Break out of switch
			break;

		} // End of a get min max info message
		case WM_COMMAND:
		{
			// A command message

			// Select command
			switch( LOWORD( wParam ) )
			{
				case BUTTON_WINDOW_ID:
				{
					// Button has been pressed

					// Allocate string memory
					LPTSTR lpszUrl = new char[ STRING_LENGTH + sizeof( char ) ];

					// Get url from edit window
					if( EditWindowGetText( lpszUrl ) )
					{
						// Successfully got url from edit window

						// Allocate string memory
						LPTSTR lpszLocalFilePath = new char[ STRING_LENGTH + sizeof( char ) ];
						LPTSTR lpszStatusMessage = new char[ STRING_LENGTH + sizeof( char ) ];

						// Format downloading status message
						wsprintf( lpszStatusMessage, INTERNET_CLASS_DOWNLOADING_STATUS_MESSAGE_FORMAT_STRING, lpszUrl );

						// Add downloading status message to list box window
						ListBoxWindowAddText( lpszStatusMessage );

						// Download file
						if( g_internet.DownloadFile( lpszUrl, lpszLocalFilePath ) )
						{
							// Successfully downloaded file
							File localFile;

							// Open local file
							if( localFile.Open( lpszLocalFilePath ) )
							{
								// Successfully opened local file
								DWORD dwLocalFileSize;

								// Get local file size
								dwLocalFileSize = localFile.GetSize();

								// Ensure that local file size was got
								if( dwLocalFileSize != INVALID_FILE_SIZE )
								{
									// Successfully got local file size

									// Allocate string memory
									LPTSTR lpszLocalFileText = new char[ dwLocalFileSize + sizeof( char ) ];

									// Read local file text
									if( localFile.Read( lpszLocalFileText, dwLocalFileSize ) )
									{
										// Successfully read local file text

										// Terminate local file text
										lpszLocalFileText[ dwLocalFileSize ] = ( char )NULL;

										// Display local file text
										MessageBox( hWndMain, lpszLocalFileText, lpszLocalFilePath, ( MB_OK | MB_ICONINFORMATION ) );

										// Format successfully downloaded status message
										wsprintf( lpszStatusMessage, INTERNET_CLASS_SUCCESSFULLY_DOWNLOADED_STATUS_MESSAGE_FORMAT_STRING, lpszUrl, lpszLocalFilePath );

									} // End of successfully read local file text
									else
									{
										// Unable to read local file

										// Format status message
										wsprintf( lpszStatusMessage, FILE_CLASS_UNABLE_TO_READ_FILE_ERROR_MESSAGE_FORMAT_STRING, lpszLocalFilePath );

									} // End of unable to read local file

									// Free string memory
									delete [] lpszLocalFileText;

								} // End of successfully got local file size
								else
								{
									// Unable to get local file size

									// Format status message
									wsprintf( lpszStatusMessage, FILE_CLASS_UNABLE_TO_GET_FILE_SIZE_ERROR_MESSAGE_FORMAT_STRING, lpszLocalFilePath );

								} // End of unable to get local file size

								// Close local file
								localFile.Close();

							} // End of successfully opened local file
							else
							{
								// Unable to open local file

								// Format status message
								wsprintf( lpszStatusMessage, FILE_CLASS_UNABLE_TO_OPEN_FILE_ERROR_MESSAGE_FORMAT_STRING, lpszLocalFilePath );

							} // End of unable to open local file

							// Add successfully downloaded status message to list box window
							ListBoxWindowAddText( lpszStatusMessage );

						} // End of successfully downloaded file
						else
						{
							// Unable to download file

							// Format unable to download status message
							wsprintf( lpszStatusMessage, INTERNET_CLASS_UNABLE_TO_DOWNLOAD_STATUS_MESSAGE_FORMAT_STRING, lpszUrl );

							// Add unable to download status message to list box window
							ListBoxWindowAddText( lpszStatusMessage );

						} // End of unable to download file

						// Free string memory
						delete [] lpszLocalFilePath;
						delete [] lpszStatusMessage;

					} // End of successfully got url from edit window

					// Free string memory
					delete [] lpszUrl;

					// Break out of switch
					break;

				} // End of button has been pressed
				default:
				{
					// Default command

					// See if command message is from control window
					if( IsEditWindow( ( HWND )lParam ) )
					{
						// Command message is from edit window

						// Handle command message from edit window
						lResult = EditWindowHandleCommandMessage( hWndMain, wParam, lParam, &EditWindowUpdateFunction );

					} // End of command message is from edit window
					else if( IsListBoxWindow( ( HWND )lParam ) )
					{
						// Command message is from list box window

						// Handle command message from list box window
						lResult = ListBoxWindowHandleCommandMessage( hWndMain, wParam, lParam, &StatusBarWindowSetText );

					} // End of command message is from list box window
					else
					{
						// Command message is not from list box window

						// Call default window procedure
						lResult = DefWindowProc( hWndMain, uMessage, wParam, lParam );

					} // End of command message is not from list box window

					// Break out of switch
					break;

				} // End of default command

			}; // End of selection for command

			// Break out of switch
			break;

		} // End of a command message
		case WM_SYSCOMMAND:
		{
			// A system command message

			// Select system command
			switch( LOWORD( wParam ) )
			{
				case SYSTEM_MENU_ABOUT_ITEM_ID:
				{
					// A help about system command

					// Show about message
					ShowAboutMessage( hWndMain );

					// Break out of switch
					break;

				} // End of a help about system command
				default:
				{
					// Default system command

					// Call default procedure
					lResult = DefWindowProc( hWndMain, uMessage, wParam, lParam );

					// Break out of switch
					break;

				} // End of default system command

			}; // End of selection for system command

			// Break out of switch
			break;

		} // End of a system command message
		case WM_CLOSE:
		{
			// A close message

			// Destroy main window
			DestroyWindow( hWndMain );

			// Break out of switch
			break;

		} // End of a close message
		case WM_DESTROY:
		{
			// A destroy message

			// Terminate thread
			PostQuitMessage( 0 );

			// Break out of switch
			break;

		} // End of a destroy message
		default:
		{
			// Default message

			// Call default window procedure
			lResult = DefWindowProc( hWndMain, uMessage, wParam, lParam );

			// Break out of switch
			break;

		} // End of default message

	}; // End of selection for message

	return lResult;

} // End of function MainWindowProcedure

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE, LPTSTR, int nCmdShow )
{
	MSG msg;

	// Clear message structure
	ZeroMemory( &msg, sizeof( msg ) );

	// Connect to internet
	if( g_internet.Connect() )
	{
		// Successfully connected to internet
		WNDCLASSEX wcMain;

		// Clear main window class structure
		ZeroMemory( &wcMain, sizeof( wcMain ) );

		// Initialise main window class structure
		wcMain.cbSize			= sizeof( WNDCLASSEX );
		wcMain.lpfnWndProc		= MainWindowProcedure;
		wcMain.hInstance		= hInstance;
		wcMain.lpszClassName	= MAIN_WINDOW_CLASS_NAME;
		wcMain.style			= MAIN_WINDOW_CLASS_STYLE;
		wcMain.hIcon			= MAIN_WINDOW_CLASS_ICON;
		wcMain.hCursor			= MAIN_WINDOW_CLASS_CURSOR;
		wcMain.hbrBackground	= MAIN_WINDOW_CLASS_BACKGROUND;
		wcMain.lpszMenuName		= MAIN_WINDOW_CLASS_MENU_NAME;
		wcMain.hIconSm			= MAIN_WINDOW_CLASS_ICON_SMALL;

		// Register main window class
		if( RegisterClassEx( &wcMain ) )
		{
			// Successfully registered main window class
			HWND hWndMain;

			// Create main window
			hWndMain = CreateWindowEx( MAIN_WINDOW_EXTENDED_STYLE, MAIN_WINDOW_CLASS_NAME, MAIN_WINDOW_TEXT, MAIN_WINDOW_STYLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,  NULL, NULL, hInstance, NULL );

			// Ensure that main window was created
			if( hWndMain )
			{
				// Successfully created main window
				int nItemCount;
				HMENU hMenuSystem;

				// Get system menu
				hMenuSystem = GetSystemMenu( hWndMain, FALSE );

				// Add separator item to system menu
				InsertMenu( hMenuSystem, SYSTEM_MENU_SEPARATOR_ITEM_POSITION, ( MF_BYPOSITION | MF_SEPARATOR ), 0, NULL );

				// Add about item to system menu
				InsertMenu( hMenuSystem, SYSTEM_MENU_ABOUT_ITEM_POSITION, MF_BYPOSITION, SYSTEM_MENU_ABOUT_ITEM_ID, SYSTEM_MENU_ABOUT_ITEM_TEXT );

				// Allocate string memory
				LPTSTR lpszStatusMessage = new char[ STRING_LENGTH + sizeof( char ) ];

				// Show main window
				ShowWindow( hWndMain, nCmdShow );

				// Update main window
				UpdateWindow( hWndMain );

				// Populate list box window
				nItemCount = ListBoxWindowPopulate();

				// Format status message
				wsprintf( lpszStatusMessage, LIST_BOX_WINDOW_POPULATE_STATUS_MESSAGE_FORMAT_STRING, nItemCount );

				// Show status message on status bar window
				StatusBarWindowSetText( lpszStatusMessage );

				// Main message loop
				while( GetMessage( &msg, NULL, 0, 0 ) > 0 )
				{
					// Translate message
					TranslateMessage( &msg );

					// Dispatch message
					DispatchMessage( &msg );

				}; // End of main message loop

				// Free string memory
				delete [] lpszStatusMessage;

			} // End of successfully created main window

		} // End of successfully registered main window class

		// Disconnect from internet
		g_internet.Disconnect();

	} // End of successfully connected to internet
	else
	{
		// Unable to connect to internet

		// Display error message
		MessageBox( NULL, INTERNET_CLASS_UNABLE_TO_CONNECT_TO_INTERNET_ERROR_MESSAGE, ERROR_MESSAGE_CAPTION, ( MB_OK | MB_ICONERROR ) );

	} // End of unable to connect to internet

	return msg.wParam;

} // End of function

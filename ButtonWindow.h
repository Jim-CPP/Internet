// ButtonWindow.h

#pragma once

#include <windows.h>
#include <commctrl.h>

#include "Ascii.h"
#include "Common.h"

#define BUTTON_WINDOW_CLASS_NAME												WC_BUTTON

#define BUTTON_WINDOW_EXTENDED_STYLE											0
#define BUTTON_WINDOW_STYLE														( WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_FLAT )
#define BUTTON_WINDOW_TEXT														"Go"

#define BUTTON_WINDOW_ID														WM_USER

#define BUTTON_WINDOW_WIDTH														30
#define BUTTON_WINDOW_HEIGHT													25

BOOL ButtonWindowCreate( HWND hWndParent, HINSTANCE hInstance, HFONT hFont );

BOOL ButtonWindowEnable( BOOL bEnableOrDisable );

BOOL ButtonWindowMove( int nLeft, int nTop, int nWidth, int nHeight );

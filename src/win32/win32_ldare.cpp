#include <ldare/ldare.h>
#include <ldare/game.h>
#include "../ldare_core_gl.h"
#include <ldare/game.h>

#include <winuser.h>
#include <windowsx.h>
#include <windows.h>
#include <tchar.h>

#define GAME_WINDOW_CLASS "LDARE_WINDOW_CLASS"

static struct GameWindow
{
	HDC dc;
	HGLRC rc;
	HWND hwnd;
	bool shouldClose;
} _gameWindow;

LRESULT CALLBACK GameWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{

		case WM_CLOSE:
		_gameWindow.shouldClose = true;	
		break;

		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);	
		break;
	}

	return TRUE;
}

static bool RegisterGameWindowClass(HINSTANCE hInstance, TCHAR* className)
{
	WNDCLASS windowClass = {};
	windowClass.style = CS_OWNDC;
	windowClass.lpfnWndProc = GameWindowProc;
	windowClass.hInstance = hInstance;
	windowClass.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
	windowClass.lpszClassName = className;
	return RegisterClass(&windowClass) != 0;
}

static bool CreateGameWindow(
		GameWindow* gameWindow, int width, int height, HINSTANCE hInstance, TCHAR* title)
{
		 gameWindow->hwnd = CreateWindow(TEXT(GAME_WINDOW_CLASS),
			title,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			width,
			height,
			NULL,
			NULL,
			hInstance,
			NULL);

		if (!gameWindow->hwnd)
			return false;

		gameWindow->dc = GetDC(gameWindow->hwnd);
		return gameWindow->dc != NULL;

}

static void* Win32_GetGLfunctionPointer(const char* functionName)
{
	static HMODULE opengl32dll = GetModuleHandleA("OpenGL32.dll");
	void* functionPtr = wglGetProcAddress(functionName);
	if( functionPtr == (void*)0x1 || functionPtr == (void*) 0x02 ||
			functionPtr == (void*) 0x3 || functionPtr == (void*) -1 ||
			functionPtr == (void*) 0x0)
	{
		functionPtr = GetProcAddress(opengl32dll, functionName);
		if(!functionPtr)
		{
			LogError("Could not get GL function pointer");
			LogError(functionName);
			return nullptr;
		}
	}
	
	return functionPtr;
}

static bool Win32_InitOpenGL(GameWindow* gameWindow, HINSTANCE hInstance, int major, int minor)
{

	GameWindow dummyWindow = {};
	if (! CreateGameWindow(&dummyWindow,0,0,hInstance,TEXT("")) )
	{
		LogError("Could not create a dummy window for openGl initialization");
		return false;
	}

	PIXELFORMATDESCRIPTOR pfd = {};
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER ;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;

  int pfId = ChoosePixelFormat(dummyWindow.dc, &pfd);
	if (pfId == 0)
	{
		LogError("Could not find a matching pixel format for GL dummy window");
		return false;
	}

	if (! SetPixelFormat(dummyWindow.dc, pfId, &pfd))
	{
		LogError("Could not set the pixel format for the Gl dummy window");
		return false;
	}

	dummyWindow.rc = wglCreateContext(dummyWindow.dc);
	if (!dummyWindow.rc)
	{
		LogError("Could not create a dummy OpenGl context");
		return false;
	}

	if (!wglMakeCurrent(dummyWindow.dc, dummyWindow.rc))
	{
		LogError("Could not make dummy OpenGL context current");
		return false;
	}

	bool success = true;

#define FETCH_GL_FUNC(type, name) success = success && (name = (type) Win32_GetGLfunctionPointer(#name))
	FETCH_GL_FUNC(PFNGLCLEARPROC, glClear);
	FETCH_GL_FUNC(PFNGLCLEARCOLORPROC, glClearColor);
	FETCH_GL_FUNC(PFNWGLCREATECONTEXTATTRIBSARBPROC, wglCreateContextAttribsARB);
	FETCH_GL_FUNC(PFNWGLCHOOSEPIXELFORMATARBPROC, wglChoosePixelFormatARB);
#undef FETCH_GL_FUNC

	if (!success)
	{
		LogError("Could not fetch all necessary OpenGL function pointers");
		return false;
	}

	wglMakeCurrent(0,0);
	wglDeleteContext(dummyWindow.rc);
	DestroyWindow(dummyWindow.hwnd);

	// specify OPENGL attributes for pixel format
	const int pixelFormatAttribList[] =
	{
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
		WGL_COLOR_BITS_ARB, 32,
		WGL_DEPTH_BITS_ARB, 8,
		0
	};

	pfd = {};
	int numPixelFormats = 0;
	wglChoosePixelFormatARB(
			gameWindow->dc,
			pixelFormatAttribList,
			nullptr,
			1,
			&pfId,
			(UINT*) &numPixelFormats);

	if ( numPixelFormats <= 0)
	{
		LogError("Could not find a matching pixel format");
		return false;
	}
	
	if (! SetPixelFormat(gameWindow->dc, pfId, &pfd))
	{
		LogError("Could not set pixel format for OpenGL context creation");
		return false;
	}

	const int contextAttribs[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, major,
		WGL_CONTEXT_MINOR_VERSION_ARB, minor,
		WGL_CONTEXT_FLAGS_ARB,
			#ifdef DEBUG
				WGL_CONTEXT_DEBUG_BIT_ARB |
			#endif
					WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
				0
	};

	gameWindow->rc = wglCreateContextAttribsARB(
			gameWindow->dc,
			0,
			contextAttribs);

	if (!gameWindow->rc)
	{
		LogError("Could not create a core profile OpenGL context");
		return false;
	}

	if(!wglMakeCurrent(gameWindow->dc, gameWindow->rc))
	{
		LogError("Could not make core profile OpenGL context current");
		return false;
	}

	return true;
}

	//---------------------------------------------------------------------------
	// processes Windows Keyboard messages
	//---------------------------------------------------------------------------
static inline void 
Win32_ProcessKeyboardMessage(KeyState& keyState, int8 lastState, int8 state)
{
		keyState.state = state;
		keyState.thisFrame += state != lastState || keyState.thisFrame;
}

	//---------------------------------------------------------------------------
	// Main
	//---------------------------------------------------------------------------
int CALLBACK WinMain(
		HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	LogInfo("Initializing");
	Input gameInput;

	// Initialize the game settings
	LDGameContext gameContext = gameInit();

	if ( !RegisterGameWindowClass(hInstance,TEXT(GAME_WINDOW_CLASS)) )
	{
		LogError("Could not register window class");
	}

	if (!CreateGameWindow(&_gameWindow, gameContext.windowWidth,
				gameContext.windowHeight, hInstance, TEXT("lDare Engine") ))
	{
		LogError("Could not create window");
	}

	if (! Win32_InitOpenGL(&_gameWindow, hInstance, 3, 2))
	{
		LogError("Could not initialize OpenGL for game window" );
	}

	// start the game
	gameStart();

	ShowWindow(_gameWindow.hwnd, SW_SHOW);
	
	while (!_gameWindow.shouldClose)
	{
		MSG msg;

		// clear 'this frame' flags from input key state
		for(int i=0; i < MAX_GAME_KBD_KEYS ; i++)
		{
			gameInput.keyboard[i].thisFrame = 0;
		}

		while (PeekMessage(&msg, _gameWindow.hwnd, 0, 0, PM_REMOVE))
		{
			// handle keyboard input messages directly
			switch(msg.message)
			{
				case WM_KEYDOWN:
				case WM_KEYUP:
				{
					// bit 30 has previous key state
					// bit 31 has current key state
					// shitty fact: 0 means pressed, 1 means released
					int8 isDown = (msg.lParam & (1 << 31)) == 0;
					int8 wasDown = (msg.lParam & (1 << 30)) != 0;
					int16 vkCode = msg.wParam;
					KeyState& currentState = gameInput.keyboard[vkCode];
				
					Win32_ProcessKeyboardMessage(gameInput.keyboard[vkCode], wasDown, isDown);
					continue;
				}
				break;

				// Cursor position
				case WM_MOUSEMOVE:
				{
					gameInput.cursor.x = GET_X_LPARAM(msg.lParam);
					gameInput.cursor.y = GET_Y_LPARAM(msg.lParam);
					continue;
				}
				break;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg) ;
			//glClear(GL_COLOR_BUFFER_BIT);
		}
		//Update the game
		gameUpdate(gameInput);
		SwapBuffers(_gameWindow.dc);
	}

	gameStop();
	LogInfo("Finished");
	return 0;
}

#ifdef DEBUG
int _tmain(int argc, _TCHAR** argv)
{
	return WinMain(GetModuleHandle(NULL), NULL, NULL,SW_SHOW);
}
#endif //DEBUG


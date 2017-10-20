/**
 * win32_platform.h
 * Win32 implementation for ldare platform functions
 */
typedef struct _XINPUT_GAMEPAD 
{
	WORD  wButtons;
	BYTE  bLeftTrigger;
	BYTE  bRightTrigger;
	SHORT sThumbLX;
	SHORT sThumbLY;
	SHORT sThumbRX;
	SHORT sThumbRY;
} XINPUT_GAMEPAD, *PXINPUT_GAMEPAD;

typedef struct _XINPUT_STATE 
{
	DWORD dwPacketNumber;
	XINPUT_GAMEPAD Gamepad;
} XINPUT_STATE, *PXINPUT_STATE;

namespace ldare 
{
	namespace platform 
	{
		static struct Win32TimerData
		{
			LARGE_INTEGER ticksPerSecond;
			LARGE_INTEGER ticksSinceEngineStartup;
		} _timerData;

		void* memoryAlloc(size_t size)
		{
			ASSERT(size>0, "allocation size must be greater than zero");
			void* mem =
				VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
			if (mem==0) { LogError("Error allocating memory"); }
			return mem;
		}

		void* Win32_getGlFunctionPointer(const char* functionName)
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

		void* loadFileToBuffer(const char* fileName, size_t* bufferSize)
		{
			HANDLE hFile = CreateFile((LPCSTR)fileName,
					GENERIC_READ,
					FILE_SHARE_READ,
					0,
					OPEN_EXISTING,
					FILE_ATTRIBUTE_NORMAL,
					0);

			DWORD err = GetLastError();

			if (hFile == INVALID_HANDLE_VALUE) 
			{
				LogError("Could not open file '%s'", fileName);
				return nullptr;
			}

			int32 fileSize;
			fileSize = GetFileSize(hFile, 0);

			if ( bufferSize != nullptr) { *bufferSize = fileSize; }
			//TODO: alloc memory from the proper Heap
			void *buffer = memoryAlloc(fileSize);
			uint32 bytesRead;
			if (!buffer || ReadFile(hFile, buffer, fileSize, (LPDWORD)&bytesRead, 0) == 0)
			{
				err = GetLastError();
				LogError("%d Could not read file '%s'", err, fileName);
				return nullptr;
			}

			CloseHandle(hFile);
			return buffer;
		}

		void memoryFree(void* memory, size_t size)
		{
			VirtualFree(memory, size, MEM_DECOMMIT);	
		}

		void Win32_initTimer()
		{
			QueryPerformanceFrequency(&_timerData.ticksPerSecond);
			QueryPerformanceCounter(&_timerData.ticksSinceEngineStartup);
		}

		uint64 getTicks()
		{
			LARGE_INTEGER value;
			QueryPerformanceCounter(&value);
			return value.QuadPart;
		}

		float getTimeBetweenTicks(uint64 start, uint64 end)
		{ 
			end -= _timerData.ticksSinceEngineStartup.QuadPart;
			start -= _timerData.ticksSinceEngineStartup.QuadPart;

			float deltaTime = (( end - start))/ (float)_timerData.ticksPerSecond.QuadPart;
#if DEBUG
			// if we stopped on a breakpoint, make things behave mor natural
			if ( deltaTime > 0.05f)
				deltaTime = 0.016f;
#endif
			return deltaTime;
		}


#define XINPUT_GET_STATE_FUNC(name) DWORD name(DWORD dwUserIndex, XINPUT_STATE *pState)
		typedef XINPUT_GET_STATE_FUNC(XInputGetStateFunc);
		XInputGetStateFunc* XInputGetState = nullptr;
		XINPUT_GET_STATE_FUNC(XInputGetStateStub)
		{
			return ERROR_DEVICE_NOT_CONNECTED;
		}

#define XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  7849
#define XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE 8689
#define XINPUT_GAMEPAD_TRIGGER_THRESHOLD    30
		//---------------------------------------------------------------------------
		// Initializes XInput
		//---------------------------------------------------------------------------
		void Win32_initXInput()
		{
			char* xInputDllName = "xinput1_1.dll"; 
			HMODULE hXInput = LoadLibraryA(xInputDllName);
			if (!hXInput)
			{				
				xInputDllName = "xinput9_1_0.dll";
				hXInput = LoadLibraryA(xInputDllName);
			}

			if (!hXInput)
			{
				xInputDllName = "xinput1_3.dll";
				hXInput = LoadLibraryA(xInputDllName);
			}

			if (!hXInput)
			{
				LogError("could not initialize xinput. No suitable xinput dll found");
				return;
			}

			LogInfo("Initializing xinput %s", xInputDllName);
			//get xinput function pointers
			XInputGetState = (XInputGetStateFunc*) GetProcAddress(hXInput, "XInputGetState");
			if (!XInputGetState) XInputGetState = XInputGetStateStub;
		}

	}	// platform namespace
} 	// ldare namespace

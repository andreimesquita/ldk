
namespace ldk
{
	namespace input
	{
		static const platform::MouseState* _mouseState;

		const ldk::Vec2& getMouseCursor()
		{
			return _mouseState.cursor;		
		}

		bool getMouseButton(uint16 mouseButton)
		{

			return _mouseState[mouseButton] & LDK_KEYSTATE_PRESSED;
		}

		bool getMouseButtonDown(uint16 mouseButton)
		{
			return _mouseState->key[mouseButton] == (LDK_KEYSTATE_CHANGED | LDK_KEYSTATE_PRESSED);
		}
	
		bool getMouseButtonUp(uint16 mouseButton)
		{
			return _mouseState->key[key] == LDK_KEYSTATE_CHANGED;
		}

		void MouseUpdate()
		{
			_mouseState = ldk::platform::getMouseState();	
		}
	} //namespace input
} // namespace ldk

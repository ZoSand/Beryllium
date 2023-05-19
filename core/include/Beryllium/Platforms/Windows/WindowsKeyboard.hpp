#ifndef BE_WINDOWS_KEYBOARD_HPP
#define BE_WINDOWS_KEYBOARD_HPP

#	include <Beryllium/API.hpp>
#	include <Beryllium/Keyboard.hpp>

namespace Beryllium
{
	class BE_API WindowsKeyboard : public Keyboard
	{
	public:
		WindowsKeyboard();
		~WindowsKeyboard();

	protected:
		virtual bool IsKeyPressedImpl(std::string _key) override;
		virtual bool IsKeyPressedImpl(char _key) override;
	};
}

#endif
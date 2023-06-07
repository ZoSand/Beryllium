#include <Beryllium\Platforms\Windows\WindowsKeyboard.hpp>

#include <algorithm>
#include <windows.h>

namespace Beryllium
{
	Beryllium::Keyboard* Beryllium::Keyboard::s_instance = new Beryllium::WindowsKeyboard;

	WindowsKeyboard::WindowsKeyboard()
	{
		Keyboard::SetInstance(this);
	}

	WindowsKeyboard::~WindowsKeyboard()
	{
		Keyboard::SetInstance(nullptr);
	}

	bool WindowsKeyboard::IsKeyPressedImpl(std::string _key)
	{
		std::transform(_key.begin(), _key.end(), _key.begin(),
			[](unsigned char c) { return std::tolower(c); } 
		);
		if (_key == "shift")
		{
			return ::GetKeyState(VK_SHIFT) & (1 << 15);
		}
		else if (_key == "control")
		{
			return ::GetKeyState(VK_CONTROL) & (1 << 15);
		}
		else if (_key == "menu")
		{
			return ::GetKeyState(VK_MENU) & (1 << 15);
		}
		else if (_key == "backspace")
		{
			return ::GetKeyState(VK_BACK) & (1 << 15);
		}
		else if (_key == "tab")
		{
			return ::GetKeyState(VK_TAB) & (1 << 15);
		}
		else if (_key == "return")
		{
			return ::GetKeyState(VK_RETURN) & (1 << 15);
		}
		else if (_key == "end")
		{
			return ::GetKeyState(VK_END) & (1 << 15);
		}
		else if (_key == "escape")
		{
			return ::GetKeyState(VK_ESCAPE) & (1 << 15);
		}
		else if (_key == "up")
		{
			return ::GetKeyState(VK_UP) & (1 << 15);
		}
		else if (_key == "down")
		{
			return ::GetKeyState(VK_DOWN) & (1 << 15);
		}
		else if (_key == "left")
		{
			return ::GetKeyState(VK_LEFT) & (1 << 15);
		}
		else if (_key == "right")
		{
			return ::GetKeyState(VK_RIGHT) & (1 << 15);
		}
		//TODO: add other special keys
		return IsKeyPressedImpl(_key[0]);
	}

	bool WindowsKeyboard::IsKeyPressedImpl(char _key)
	{
		return ::GetKeyState(std::toupper((int)_key)) & (1 << 15);
	}
}


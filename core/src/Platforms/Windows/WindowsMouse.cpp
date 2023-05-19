#include <Beryllium/Platforms/Windows/WindowsMouse.hpp>

#include <windows.h>

namespace Beryllium
{
	WindowsMouse::WindowsMouse()
	{
		Mouse::SetInstance(this);
	}

	WindowsMouse::~WindowsMouse()
	{
		Mouse::SetInstance(nullptr);
	}

	bool WindowsMouse::IsButtonPressedImpl(Mouse::Button _key)
	{
		switch (_key)
		{
		case Beryllium::Mouse::Button::Left:
			return ::GetKeyState(VK_LBUTTON) & (1 << 15);
			break;
		case Beryllium::Mouse::Button::Right:
			return ::GetKeyState(VK_RBUTTON) & (1 << 15);
			break;
		case Beryllium::Mouse::Button::Middle:
			return ::GetKeyState(VK_MBUTTON) & (1 << 15);
			break;
		default:
			return false;
			break;
		}
	}

	std::pair<float, float> WindowsMouse::GetPositionImpl()
	{
		POINT pos;
		::GetCursorPos(&pos);
		return std::make_pair(pos.x, pos.y);
	}

	void WindowsMouse::ShowCursorImpl(bool _show)
	{
		::ShowCursor(_show);
	}
}
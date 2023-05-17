#include <Beryllium/Mouse.hpp>

#include <cassert>

namespace Beryllium
{
	Mouse* Mouse::s_instance = nullptr;

	Mouse* Mouse::GetInstance()
	{
		assert(s_instance != nullptr && "Mouse instance not initialized");
		return s_instance;
	}

	bool Mouse::IsButtonPressed(Mouse::Button _Button)
	{
		return Mouse::GetInstance()->IsButtonPressedImpl(_Button);
	}

	std::pair<float, float> Mouse::GetPosition()
	{
		return Mouse::GetInstance()->GetPositionImpl();
	}

	float Mouse::GetX()
	{
		auto [x, y] = Mouse::GetPosition();
		return x;
	}

	float Mouse::GetY()
	{
		auto [x, y] = Mouse::GetPosition();
		return y;
	}

	void Mouse::ShowCursor(bool _show)
	{
		Mouse::GetInstance()->ShowCursorImpl(_show);
	}

	void Mouse::SetInstance(Mouse* _instance)
	{
		if (s_instance != nullptr && s_instance != _instance)
		{
			delete s_instance;
		}
		s_instance = _instance;
	}

}
#ifndef BE_MOUSE_HPP
#define BE_MOUSE_HPP

#include <Beryllium/API.hpp>

namespace Beryllium
{
	class BE_API Mouse
	{
	public:
		enum class BE_API Button
		{
			Left,
			Right,
			Middle,
			Count
		};

		//static bool IsButtonPressed(Button _button);
		//static bool IsButtonReleased(Button _button);
	};
}

#endif // BE_MOUSE_HPP
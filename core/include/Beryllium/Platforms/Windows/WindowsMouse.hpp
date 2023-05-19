#ifndef BE_WINDOWS_MOUSE_HPP
#define BE_WINDOWS_MOUSE_HPP

#	include <Beryllium/Mouse.hpp>

namespace Beryllium
{
	class BE_API WindowsMouse : public Mouse
	{
	public:
		WindowsMouse();
		~WindowsMouse();
	protected:
		virtual bool IsButtonPressedImpl(Mouse::Button _key) override;
		virtual std::pair<float, float> GetPositionImpl() override;

		virtual void ShowCursorImpl(bool _show) override;
	};
}

#endif
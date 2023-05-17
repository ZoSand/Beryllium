#ifndef BE_MOUSE_HPP
#define BE_MOUSE_HPP

#include <Beryllium/API.hpp>

#include <tuple>

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

	public:
		static bool IsButtonPressed(Mouse::Button _key);
		static std::pair<float, float> GetPosition();
		static float GetX();
		static float GetY();

		static void ShowCursor(bool _show);

	private:
		static Mouse* s_instance;
		static Mouse* GetInstance();

	protected:
		void SetInstance(Mouse* _instance);

		virtual bool IsButtonPressedImpl(Mouse::Button _key) = 0;
		virtual std::pair<float, float> GetPositionImpl() = 0;

		virtual void ShowCursorImpl(bool _show) = 0;
	};
}

#endif // BE_MOUSE_HPP
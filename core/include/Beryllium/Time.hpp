#ifndef BE_TIME_HPP
#define BE_TIME_HPP

#	include <Beryllium/API.hpp>

#	include <chrono>

namespace Beryllium
{
	class BE_API Time
	{
	public:
		static float DeltaTime();
		static float UnscaledDeltaTime();

		static float GetTimeScale();
		static void SetTimeScale(float _ts);

		static void Tick();

	private:
		static float s_dt;
		static float s_timeScale;
		static std::chrono::time_point<std::chrono::system_clock> s_lastTick;
	};
}

#endif // BE_TIME_HPP

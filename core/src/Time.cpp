#include <Beryllium/Time.hpp>

namespace Beryllium
{
	float Time::s_dt = 0;
	std::chrono::time_point<std::chrono::system_clock> Time::s_lastTick;

	float Time::DeltaTime()
	{
		return s_dt;
	}

	void Time::Tick()
	{
		std::chrono::time_point<std::chrono::system_clock> tick = std::chrono::system_clock::now();
		s_dt = std::chrono::duration_cast<std::chrono::milliseconds>(tick - s_lastTick).count() / 1000.f;
		s_lastTick = tick;
	}
}
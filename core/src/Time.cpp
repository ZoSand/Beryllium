#include <Beryllium/Time.hpp>

namespace Beryllium
{
	float Time::s_dt = 0.f;
	float Time::s_timeScale = 1.f;
	std::chrono::time_point<std::chrono::system_clock> Time::s_lastTick;

	float Time::DeltaTime()
	{
		return s_dt;
	}

	float Time::UnscaledDeltaTime()
	{
		return s_dt / s_timeScale;
	}

	void Time::Tick()
	{
		std::chrono::time_point<std::chrono::system_clock> tick = std::chrono::system_clock::now();
		s_dt = (std::chrono::duration_cast<std::chrono::milliseconds>(tick - s_lastTick).count() / 1000.f) * s_timeScale;
		s_lastTick = tick;
	}


	float Time::GetTimeScale()
	{
		return s_timeScale;
	}

	void Time::SetTimeScale(float _ts)
	{
		s_timeScale = _ts;
	}
}
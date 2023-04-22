#include <Beryllium/Events/CommonEvents/KeyReleased.hpp>

namespace Beryllium::Events
{
	KeyReleased::KeyReleased(int _key)
		: m_key(_key)
	{
	}

	int KeyReleased::GetKey() const
	{
		return m_key;
	}
}

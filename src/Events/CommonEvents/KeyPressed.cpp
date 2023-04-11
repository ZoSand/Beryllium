#include <Beryllium/Events/CommonEvents/KeyPressed.hpp>

namespace Beryllium::Events
{
	KeyPressed::KeyPressed(int _key)
		: m_key(_key)
	{
	}

	int KeyPressed::GetKey() const
	{
		return m_key;
	}
}
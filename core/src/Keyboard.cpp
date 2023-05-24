#include <Beryllium/Keyboard.hpp>

#include <cassert>

namespace Beryllium
{
	//Keyboard* Keyboard::s_instance = nullptr;

	Keyboard* Keyboard::GetInstance()
	{
		assert(s_instance != nullptr && "Keyboard instance not initialized");
		return s_instance;
	}

	void Keyboard::SetInstance(Keyboard* _instance)
	{
		if (s_instance != nullptr && s_instance != _instance)
		{
			delete s_instance;
		}
		s_instance = _instance;
	}

	bool Keyboard::IsKeyPressed(std::string _key)
	{
		return Keyboard::GetInstance()->IsKeyPressedImpl(_key);
	}

	bool Keyboard::IsKeyPressed(char _key)
	{
		return Keyboard::GetInstance()->IsKeyPressedImpl(_key);
	}
}
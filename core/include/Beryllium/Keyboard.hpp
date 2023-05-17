#ifndef BE_KEYBOARD_HPP
#define BE_KEYBOARD_HPP

#include <Beryllium/API.hpp>

#include <string>

namespace Beryllium 
{
	class BE_API Keyboard
	{
	public:
		static bool IsKeyPressed(std::string _key);
	private: 
		static Keyboard* s_instance;
		static Keyboard* GetInstance();
	
	protected:
		void SetInstance(Keyboard* _instance);

		virtual bool IsKeyPressedImpl(std::string _key) = 0;
	};
}

#endif
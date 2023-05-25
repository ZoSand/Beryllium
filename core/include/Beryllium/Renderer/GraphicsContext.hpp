#ifndef BE_GRAPHICS_CONTEXT_HPP
#define BE_GRAPHICS_CONTEXT_HPP

#	include <Beryllium/API.hpp>

namespace Beryllium
{
	class BE_API GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
		virtual void Destroy() = 0;
	};
}

#endif 
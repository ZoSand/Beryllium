#ifndef BE_GRAPHICS_CONTEXT_HPP
#define BE_GRAPHICS_CONTEXT_HPP

#	include <Beryllium/API.hpp>

namespace Beryllium
{
	class Window;

	/// <summary>
	/// Abstract class that represents a renderers context
	/// </summary>
	class BE_API GraphicsContext
	{
	public:
		GraphicsContext(Window* _handle);
		/// <summary>
		/// Inits the context using m_windowHandle provided in ctor
		/// </summary>
		virtual void Init() = 0;
		/// <summary>
		/// Swap rendering buffers. This should be done at rendering time
		/// </summary>
		virtual void SwapBuffers() = 0;
		/// <summary>
		/// Destroys the context
		/// </summary>
		virtual void Destroy() = 0;

	protected:
		Beryllium::Window* m_windowHandle;
	};
}

#endif 
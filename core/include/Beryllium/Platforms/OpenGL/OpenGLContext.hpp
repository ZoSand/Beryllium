#ifndef BE_OPENGL_CONTEXT_HPP
#define BE_OPENGL_CONTEXT_HPP

#	include <Beryllium/API.hpp>
#	include <Beryllium/Renderer/GraphicsContext.hpp>

#if defined(BE_PLATFORM_WINDOWS)
#	include <windows.h>
#endif

namespace Beryllium
{
	class Window;

	class BE_API OpenGLContext : public Beryllium::GraphicsContext
	{
	public:
		OpenGLContext(Beryllium::Window* _window);
		~OpenGLContext();
		virtual void Init() override;
		virtual void SwapBuffers() override;
		virtual void Destroy() override;

	private: 
		Beryllium::Window* m_windowHandle;

#if defined(BE_PLATFORM_WINDOWS)
		::HGLRC m_context;
#else
#	error "Missing OpenGL Context tracking for this platform"
#endif
	};
}

#endif
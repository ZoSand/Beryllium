#ifndef BE_OPENGL_GRAPHICS_CONTEXT_HPP
#define BE_OPENGL_GRAPHICS_CONTEXT_HPP

#	include <Beryllium/API.hpp>
#	include <Beryllium/Renderer/GraphicsContext.hpp>

#if defined(BE_PLATFORM_WINDOWS)
#	include <windows.h>
#endif

namespace Beryllium
{
	class BE_API OpenGLGraphicsContext : public Beryllium::GraphicsContext
	{
	public:
		OpenGLGraphicsContext(Beryllium::Window* _window);
		~OpenGLGraphicsContext();
		virtual void Init() override;
		virtual void SwapBuffers() override;
		virtual void Destroy() override;

#if defined(BE_PLATFORM_WINDOWS)
		::HGLRC m_context;
#else
#	error "Missing OpenGL Context tracking for this platform"
#endif
	};
}

#endif
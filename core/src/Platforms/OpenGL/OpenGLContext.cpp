#include <Beryllium/Platforms/OpenGL/OpenGLContext.hpp>

#include <glad/glad.h>

#include <Beryllium/Window.hpp>
#include <Beryllium/Logger.hpp>

#include <stdexcept>

namespace Beryllium
{

	OpenGLContext::OpenGLContext(Beryllium::Window* _window)
		: m_windowHandle(_window)
	{
	}

	OpenGLContext::~OpenGLContext()
	{
	}

	void OpenGLContext::Init()
	{
#if defined(BE_PLATFORM_WINDOWS) //kinda forced to do platform specific things because of freaking types duhh
		::HWND handle = (::HWND)m_windowHandle->GetNativeWindow();
		::HDC deviceContext = GetDC(handle);
		::HGLRC context = ::wglCreateContext(deviceContext);
		if (context == nullptr)
		{
			Logger::Critical("Failed to create OpenGL context");
			throw std::runtime_error("Failed to create OpenGL context");
		}

		if (!::wglMakeCurrent(deviceContext, context))
		{
			Logger::Critical("Failed to make OpenGL context current");
			throw std::runtime_error("Failed to make OpenGL context current");
		}
#else
#	error "Missing OpenGL Context init for this platform"
#endif


		if (!::gladLoadGL())
		{
			Logger::Critical("Failed to load GLAD");
			throw std::runtime_error("Failed to load GLAD");
		}

		BE_TRACE("[OpenGL] Context Initialized");
		BE_INFO("[OpenGL] Vendor: %s", ::glGetString(GL_VENDOR));
		BE_INFO("[OpenGL] Renderer: %s", ::glGetString(GL_RENDERER));
		BE_INFO("[OpenGL] Version: %s", ::glGetString(GL_VERSION));
		BE_INFO("[OpenGL] GLSL Version: %s", ::glGetString(GL_SHADING_LANGUAGE_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
#if defined(BE_PLATFORM_WINDOWS) //kinda forced to do platform specific things because of freaking types duhh
		::HDC deviceContext = ::GetDC((::HWND)m_windowHandle->GetNativeWindow());
		::SwapBuffers(deviceContext);
#else
#	error "Missing OpenGL Context init for this platform"
#endif
	}

	void OpenGLContext::Destroy()
	{
#if defined(BE_PLATFORM_WINDOWS)
		::HWND handle = (::HWND)m_windowHandle->GetNativeWindow();
		::HDC deviceContext = ::GetDC(handle);
		::wglMakeCurrent(nullptr, nullptr);
		if (m_context)
		{
			::wglDeleteContext(m_context);
		}

		if (deviceContext)
		{
			::ReleaseDC(handle, deviceContext);
		}
#else
#	error "Missing OpenGL Context destrcution for this platform"
#endif

		BE_TRACE("[OpenGL] Context Destroyed");
	}

}
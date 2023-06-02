#include <Beryllium/Platforms/OpenGL/OpenGLGraphicsContext.hpp>

#include <glad/glad.h>

#include <Beryllium/Window.hpp>
#include <Beryllium/Logger.hpp>

#include <stdexcept>

namespace Beryllium
{

	OpenGLGraphicsContext::OpenGLGraphicsContext(Beryllium::Window* _window)
		: m_windowHandle(_window)
		, m_context(nullptr)
	{
	}

	OpenGLGraphicsContext::~OpenGLGraphicsContext()
	{
	}

	void OpenGLGraphicsContext::Init()
	{
#if defined(BE_PLATFORM_WINDOWS) //kinda forced to do platform specific things because of freaking types duhh
		::HWND handle = (::HWND)m_windowHandle->GetNativeWindow();
		::HDC deviceContext = GetDC(handle);
		::HGLRC context = ::wglCreateContext(deviceContext);
		if (context == nullptr)
		{
			BE_CRITICAL("[OpenGL][Context] Failed to create OpenGL context");
			throw std::runtime_error("Failed to create OpenGL context");
		}

		if (!::wglMakeCurrent(deviceContext, context))
		{
			BE_CRITICAL("[OpenGL][Context] Failed to make OpenGL context current");
			throw std::runtime_error("Failed to make OpenGL context current");
		}
#else
#	error "Missing OpenGL Context init for this platform"
#endif

		if (!::gladLoadGL())
		{
			BE_CRITICAL("[OpenGL][Context] Failed to load GLAD");
			throw std::runtime_error("Failed to load GLAD");
		}

		BE_TRACE("[OpenGL][Context] Context Initialized");
		BE_INFO("[OpenGL][Context] Vendor: %s", ::glGetString(GL_VENDOR));
		BE_INFO("[OpenGL][Context] Renderer: %s", ::glGetString(GL_RENDERER));
		BE_INFO("[OpenGL][Context] Version: %s", ::glGetString(GL_VERSION));
		BE_INFO("[OpenGL][Context] GLSL Version: %s", ::glGetString(GL_SHADING_LANGUAGE_VERSION));
	}

	void OpenGLGraphicsContext::SwapBuffers()
	{
#if defined(BE_PLATFORM_WINDOWS) //kinda forced to do platform specific things because of freaking types duhh
		::HDC deviceContext = ::GetDC((::HWND)m_windowHandle->GetNativeWindow());
		::SwapBuffers(deviceContext);
#else
#	error "Missing OpenGL Context init for this platform"
#endif
	}

	void OpenGLGraphicsContext::Destroy()
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

		BE_TRACE("[OpenGL][Context] Context Destroyed");
	}

}
#ifndef BE_BERYLLIUM_HPP
#define BE_BERYLLIUM_HPP

// API
#	include <Beryllium/API.hpp>

// APPLICATION
#	include <Beryllium/Application.hpp>

// CORE
#	include <Beryllium/Logger.hpp>
#	include <Beryllium/Window.hpp>
#	include <Beryllium/Keyboard.hpp>
#	include <Beryllium/Mouse.hpp>

// EVENTS
#	include <Beryllium/Events/EventDispatcher.hpp>
#	include <Beryllium/Events/EventListener.hpp>
#	include <Beryllium/Events/Event.hpp>
#	include <Beryllium/Events/CommonEvents.hpp>

//	RENDERERS
#	include <Beryllium/Renderer/Renderer.hpp>
#	include <Beryllium/Renderer/BufferElement.hpp>
#	include <Beryllium/Renderer/BufferLayout.hpp>
#	include <Beryllium/Renderer/GraphicsContext.hpp>
#	include <Beryllium/Renderer/IndexBuffer.hpp>
#	include <Beryllium/Renderer/Shader.hpp>
#	include <Beryllium/Renderer/ShaderDataType.hpp>
#	include <Beryllium/Renderer/VertexArray.hpp>
#	include <Beryllium/Renderer/VertexBuffer.hpp>

// RENDERERS:OPENGL
#	include <Beryllium/Platforms/OpenGL/OpenGLRenderer.hpp>
#	include <Beryllium/Platforms/OpenGL/OpenGLGraphicsContext.hpp>
#	include <Beryllium/Platforms/OpenGL/OpenGLIndexBuffer.hpp>
#	include <Beryllium/Platforms/OpenGL/OpenGLShader.hpp>
#	include <Beryllium/Platforms/OpenGL/OpenGLVertexArray.hpp>
#	include <Beryllium/Platforms/OpenGL/OpenGLVertexBuffer.hpp>

// LAYERS
#	include <Beryllium/Layer.hpp>
#	include <Beryllium/LayerStack.hpp>

#	include <Beryllium/Layers/ImGuiLayer.hpp>

// APPLICATION

// PLATFORM
#	if defined(BE_PLATFORM_WINDOWS)
#		include <Beryllium/Platforms/Windows/WindowsWindow.hpp>
#		include <Beryllium/Platforms/Windows/WindowsKeyboard.hpp>
#		include <Beryllium/Platforms/Windows/WindowsMouse.hpp>
#	else
#		error "Beryllium Window is only implemented on Windows for now!"
#	endif

#endif // BE_BERYLLIUM_HPP
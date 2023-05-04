#ifndef BE_BERYLLIUM_HPP
#define BE_BERYLLIUM_HPP

// API
#	include <Beryllium/API.hpp>

// CORE
#	include <Beryllium/Logger.hpp>


// EVENTS
#	include <Beryllium/Events/EventDispatcher.hpp>
#	include <Beryllium/Events/EventListener.hpp>
#	include <Beryllium/Events/Event.hpp>
#	include <Beryllium/Events/CommonEvents.hpp>

// PLATFORMS
#	include <Beryllium/Window.hpp>

// LAYERS
#	include <Beryllium/Layer.hpp>
#	include <Beryllium/LayerStack.hpp>

#	include <Beryllium/Layers/ImGuiLayer.hpp>

// APPLICATION
#	include <Beryllium/Application.hpp>
//#	include <Beryllium/Entry.hpp>

// PLATFORM
#	if defined(BE_PLATFORM_WINDOWS)
#		include <Beryllium/Platforms/Windows/WindowsWindow.hpp>
#	else
#		error "Beryllium Window is only implemented on Windows for now!"
#	endif

#endif // BE_BERYLLIUM_HPP
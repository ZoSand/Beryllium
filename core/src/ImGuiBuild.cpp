//This file is only for compiling backends 


#define IMGUI_IMPL_OPENGL_LOADER_GLAD

#include <backends/imgui_impl_opengl3.cpp>

#if defined(BE_PLATFORM_WINDOWS)
#	include <backends/imgui_impl_win32.cpp>
#else
#	error "No ImGui Backend for platform"
#endif
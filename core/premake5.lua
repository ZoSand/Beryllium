project "Beryllium"
	location "" 
	kind "StaticLib"
	staticruntime "on"
	language "C++"
	cppdialect "C++17"
	
	files {
		"**.cd",
		"include/**.hpp",
		"include/**.h",
		"include/**.inl",
		"src/**.cpp",

		"../vendor/glm/glm/**.hpp",
		"../vendor/glm/glm/**.inl"
	}
	defines {
		"BE_EXPORTS"
	}
	includedirs {
		"include",
		"../vendor/glad/include",
		"../vendor/imgui",
		"../vendor/glm"
	}
	links {
		"glad",
		"ImGui",
		"opengl32"
	}

	filter { "system:linux" }
		removefiles { 
			"**/Platforms/Windows/**",
			"**/Platforms/MacOSX/**"
		}

	filter { "system:macosx" }
		removefiles { 
			"**/Platforms/Linux/**",
			"**/Platforms/Windows/**"
		}

	filter { "system:windows" }
		systemversion "latest"
		defines {
			"BE_BUILD_DLL"
		}
		removefiles {
			"**/Platforms/Linux/**",
			"**/Platforms/MacOSX/**"
		}
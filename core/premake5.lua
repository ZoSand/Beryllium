project "Beryllium"
  location "" 
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"
	systemversion "latest"
	files {
		"**.cd",
		"include/**.hpp",
		"include/**.inl",
		"src/**.cpp"
	}
	defines {
		"BE_EXPORTS"
	}
	includedirs {
		"include"
    "vendor/glad/include"
	}
	links {
		"glad"
	}

	filter { "system:linux" }
		removefiles { 
			"**/Platforms/Linux/**",
			"**/Platforms/MacOSX/**"
		}

	filter { "system:macosx" }
		removefiles { 
			"**/Platforms/Linux/**",
			"**/Platforms/Windows/**"
		}

	filter { "system:windows" }
		defines {
			"BE_BUILD_DLL"
		}
		removefiles {
			"**/Platforms/Linux/**",
			"**/Platforms/MacOSX/**"
		}
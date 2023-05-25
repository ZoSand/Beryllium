configurations {
	"Debug",
	"Release",
	"Distribution"
}
platforms { 
	"Win32",
	"Win64"
}

targetdir "%{wks.location}/Build/bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
objdir "%{wks.location}/Build/bin-obj/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
debugdir "%{wks.location}/Build/bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

filter { "platforms:Win32" }
    system "Windows"
    architecture "x86"
	defines {
		"BE_PLATFORM_32BIT"
	}
	
filter { "platforms:Win64" }
    system "Windows"
    architecture "x64"
	defines {
		"BE_PLATFORM_64BIT"
	}

filter { "system:linux"}
	systemversion "latest"
	defines {
		"BE_PLATFORM_LINUX"
	}

filter { "system:macosx"}
	systemversion "latest"
	defines {
		"BE_PLATFORM_MACOSX"
	}

filter { "system:windows"}
	systemversion "latest"
	defines {
		"BE_PLATFORM_WINDOWS"
	}

filter { "configurations:Debug" }
	defines {
		"DEBUG"
	}
	symbols "on"

filter { "configurations:Release" }
	defines {
		"NDEBUG",
		"RELEASE"
	}
	optimize "on"

filter { "configurations:Distribution" }
	defines {
		"NDEBUG",
		"DIST"
	}
	optimize "on"

filter { "system:windows", "configurations:Debug" }
	buildoptions "/MDd"
	
filter { "system:windows", "configurations:Release" }
	buildoptions "/MD"
	
filter { "system:windows", "configurations:Distribution" }
	buildoptions "/MD"
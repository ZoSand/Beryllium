project "glad"
  location ""
  kind "StaticLib"
  staticruntime "off"
  language "C"
  
  files {
    "include/glad/glad.h",
    "include/KHR/khrplatform.h",
    "src/glad.c"
  }
  
  includedirs {
    "include"
  }

  links {
	"opengl32"
  }
  
  filter "system:windows"
    systemversion "latest"

  filter "configurations:Debug"
    runtime "Debug"
    symbols "on"
    
  filter "configurations:Release"
    runtime "Release"
    optimize "on"
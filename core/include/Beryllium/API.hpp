#ifndef BE_API_HPP
#define BE_API_HPP

#	if defined(BE_PLATFORM_WINDOWS)
#		if defined(BE_DYNAMIC_LINK)
#			if defined(BE_EXPORTS)
#				define BE_API __declspec(dllexport)
#			else
#				define BE_API __declspec(dllimport)
#			endif
#		else
#			define BE_API
#		endif
#	else
#		error "Beryllium is only supported on Windows!"
#	endif

#endif // BE_API_HPP
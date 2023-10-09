/*********************************************************************************************
 * [Owner]                                                                                   *
 *  Library: Beryllium                                                                       *
 *  Author: Zo LAMBERT                                                                       *
 *  Contact: <zo.lambert@zosand.fr>                                                          *
 *                         										                             *
 * [Header]                                                                                  *
 * This file defines the Beryllium Core API definitions.                                     *
 *********************************************************************************************/

#ifndef BERYLLIUM_PLATFORM_API_HPP
#define BERYLLIUM_PLATFORM_API_HPP

// Generic API visibility macros
#   if defined(BE_PLATFORM_WINDOWS)
#       define BE_PLATFORM_API_EXPORT __declspec(dllexport)
#       define BE_PLATFORM_API_IMPORT __declspec(dllimport)
#       define BE_PLATFORM_API_LOCAL
#   elif defined(BE_PLATFORM_UNIX)
#       if defined(__GNUC__) && __GNUC__ >= 4
#           define BE_PLATFORM_API_EXPORT __attribute__((visibility("default")))
#           define BE_PLATFORM_API_IMPORT __attribute__((visibility("default")))
#           define BE_PLATFORM_API_LOCAL __attribute__((visibility("hidden")))
#       else
#           define BE_PLATFORM_API_EXPORT
#           define BE_PLATFORM_API_IMPORT
#           define BE_PLATFORM_API_LOCAL
#       endif
#   endif

// Now we use the generic helper definitions above to define BERYLLIUM_API and BERYLLIUM_API_PRIVATE.
// BERYLLIUM_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
#   if defined(BE_BUILD_SHARED_LIBS)
#       if defined(BE_PLATFORM_EXPORT_SYMBOLS)
#           define BE_PLATFORM_API_PUBLIC BE_PLATFORM_API_EXPORT
#       else
#           define BE_PLATFORM_API_PUBLIC BE_PLATFORM_API_IMPORT
#       endif
#       define BE_PLATFORM_API_PRIVATE BE_PLATFORM_API_LOCAL
#   else
#       define BE_PLATFORM_API_PUBLIC
#       define BE_PLATFORM_API_PRIVATE
#   endif

#endif //BERYLLIUM_PLATFORM_API_HPP

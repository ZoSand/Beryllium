/*********************************************************************************************
 * [Owner]                                                                                   *
 *  Library: Beryllium                                                                       *
 *  Author: Zo LAMBERT                                                                       *
 *  Contact: <zo.lambert@zosand.fr>                                                          *
 *                         										                             *
 * [Header]                                                                                  *
 * This file defines the Beryllium API definitions.                                          *
 *********************************************************************************************/

#ifndef BERYLLIUM_API_HPP
#define BERYLLIUM_API_HPP

// Generic API visibility macros
#   if defined(BERYLLIUM_PLATFORM_WINDOWS)
#       define BE_API_EXPORT __declspec(dllexport)
#       define BE_API_IMPORT __declspec(dllimport)
#       define BE_API_LOCAL
#   elif defined(BERYLLIUM_PLATFORM_LINUX)
#       if defined(__GNUC__) && __GNUC__ >= 4
#           define BE_API_EXPORT __attribute__((visibility("default")))
#           define BE_API_IMPORT __attribute__((visibility("default")))
#           define BE_API_LOCAL __attribute__((visibility("hidden")))
#       else
#           define BE_API_EXPORT
#           define BE_API_IMPORT
#           define BE_API_LOCAL
#       endif
#   endif

// Now we use the generic helper definitions above to define BERYLLIUM_API and BERYLLIUM_API_PRIVATE.
// BERYLLIUM_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
#   if defined(BERYLLIUM_BUILD_SHARED_LIBS)
#       if defined(BERYLLIUM_EXPORT_SYMBOLS)
#           define BE_API_PUBLIC BE_API_EXPORT
#       else
#           define BE_API_PUBLIC BE_API_IMPORT
#       endif
#       define BE_API_PRIVATE BE_API_LOCAL
#   else
#       define BE_API_PUBLIC
#       define BE_API_PRIVATE
#   endif

// default API visibility
// you want to keep that public for DLL builds, but does not matter for static builds
#   define BE_API BE_API_PUBLIC

#endif //BERYLLIUM_API_HPP

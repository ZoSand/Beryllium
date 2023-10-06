/*********************************************************************************************
 * [Owner]                                                                                   *
 *  Library: Beryllium                                                                       *
 *  Author: Zo LAMBERT                                                                       *
 *  Contact: <zo.lambert@zosand.fr>                                                          *
 *                         										                             *
 * [Header]                                                                                  *
 * This file includes the Window class contract for current platform.                        *
 *********************************************************************************************/

#ifndef BERYLLIUM_WINDOW_HPP
#define BERYLLIUM_WINDOW_HPP

#   if defined(BERYLLIUM_PLATFORM_WINDOWS)
#       include <Beryllium/Windows/Window.hpp>
#   elif defined(BERYLLIUM_PLATFORM_LINUX)
#       include <Beryllium/Linux/Window.hpp>
#   endif

namespace Be
{
    using Window = Platform::Window;
}

#endif //BERYLLIUM_WINDOW_HPP

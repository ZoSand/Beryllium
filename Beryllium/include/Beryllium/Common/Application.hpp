/*********************************************************************************************
 * [Owner]                                                                                   *
 *  Library: Beryllium                                                                       *
 *  Author: Zo LAMBERT                                                                       *
 *  Contact: <zo.lambert@zosand.fr>                                                          *
 *                         										                             *
 * [Header]                                                                                  *
 * This file defines the Beryllium Application interface.                                    *
 *********************************************************************************************/

#ifndef BERYLLIUM_APPLICATION_HPP
#define BERYLLIUM_APPLICATION_HPP

#   include <Beryllium/Common/Api.hpp>
#   include <Beryllium/Common/Types.hpp>
#   include <Beryllium/Common/Meta.hpp>

#   include <Beryllium/Platform/Window.hpp>

#   include <vector>
#   include <string>

namespace Be
{
	class BE_API_PUBLIC Application
	{
	public:
		explicit Application(const std::vector<std::string>& _arguments);

		META_VIRTUAL                            (~Application());

		META_METHOD                             (int Run());

		META_UNUSED_NODISCARD                   (Window *GetWindow() const);

        META_UNUSED_NODISCARD                   (static std::string GetApplicationDefaultName());

	private:
		Window *m_window;
	};
}

#endif //BERYLLIUM_APPLICATION_HPP

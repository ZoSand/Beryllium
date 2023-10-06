/*********************************************************************************************
 * [Owner]                                                                                   *
 *  Library: Beryllium                                                                       *
 *  Author: Zo LAMBERT                                                                       *
 *  Contact: <zo.lambert@zosand.fr>                                                          *
 *                         										                             *
 * [Header]                                                                                  *
 * This file describe the Window class contract.                                             *
 *********************************************************************************************/

#ifndef BERYLLIUM_CONTRACTS_WINDOW_HPP
#define BERYLLIUM_CONTRACTS_WINDOW_HPP

#   include <Beryllium/Common/Types.hpp>
#   include <Beryllium/Common/Meta.hpp>

#   include <string>
#   include <utility>


namespace Be::Contracts
{
	class Window
	{
	public:
		Window() = default;

		virtual ~Window() = default;

		META_UNUSED_INTERFACE               (void Create());
		META_UNUSED_INTERFACE               (void Destroy());
		META_UNUSED_INTERFACE               (void Update());

		META_UNUSED_INTERFACE               (void SetTitle(const std::string &_title));
		META_UNUSED_NODISCARD_INTERFACE     (std::string GetTitle() const);

        META_UNUSED_INTERFACE               (void Open(bool _open));
        META_UNUSED_NODISCARD_INTERFACE     (bool IsOpen() const);

        META_UNUSED_INTERFACE               (void SetSize(std::pair<int, int> _size));
        META_UNUSED_NODISCARD_INTERFACE     (std::pair<int, int> GetSize() const);

        META_UNUSED_INTERFACE               (void SetPosition(std::pair<int, int> _position));
        META_UNUSED_NODISCARD_INTERFACE     (std::pair<int, int> GetPosition() const);
	};
}


#endif //BERYLLIUM_CONTRACTS_WINDOW_HPP

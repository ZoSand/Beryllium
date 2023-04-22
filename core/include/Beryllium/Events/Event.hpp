#ifndef BE_EVENT_HPP
#define BE_EVENT_HPP

#	include <Beryllium/API.hpp>

namespace Beryllium
{
	class BE_API Event
	{
	public:
		Event() = default;
		virtual ~Event() = default;

		template <typename T>
		const bool Is() const;

		template <typename T>
		const T& As() const;
	};

#	include <Beryllium/Events/Event.inl>
}

#endif // BE_EVENT_HPP
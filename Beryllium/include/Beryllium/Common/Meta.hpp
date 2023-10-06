/*********************************************************************************************
 * [Owner]                                                                                   *
 *  Library: Beryllium                                                                       *
 *  Author: Zo LAMBERT                                                                       *
 *  Contact: <zo.lambert@zosand.fr>                                                          *
 *                         										                             *
 * [Header]                                                                                  *
 * This file defines the Beryllium keyword macros.                                           *
 *********************************************************************************************/

#ifndef BERYLLIUM_META_HPP
#define BERYLLIUM_META_HPP

#   define META_NODISCARD(...)                         [[nodiscard]] __VA_ARGS__
#   define META_UNUSED(...)                            [[maybe_unused]]  __VA_ARGS__
#   define META_UNUSED_NODISCARD(...)                  [[maybe_unused, nodiscard]]  __VA_ARGS__

#   define META_TYPEDEF(base_type, ...)                 META_UNUSED(typedef base_type __VA_ARGS__)
#   define META_VIRTUAL(...)                            virtual __VA_ARGS__
#   define META_OVERRIDE(...)                           __VA_ARGS__ override
#   define META_FINAL(...)                              __VA_ARGS__ final
#   define META_ABSTRACT(...)                           __VA_ARGS__ = 0
#   define META_DEFAULT(...)                            __VA_ARGS__ = default
#   define META_DELETE(...)                             __VA_ARGS__ = delete
#   define META_METHOD(...)                             __VA_ARGS__

#   define META_DEFAULT_VIRTUAL(...)                    META_DEFAULT(META_VIRTUAL(__VA_ARGS__))
#   define META_DEFAULT_OVERRIDE(...)                   META_DEFAULT(META_OVERRIDE(__VA_ARGS__))

#   define META_NODISCARD_INTERFACE(...)                META_NODISCARD(META_ABSTRACT(META_VIRTUAL(__VA_ARGS__)))
#   define META_UNUSED_INTERFACE(...)                   META_UNUSED(META_ABSTRACT(META_VIRTUAL(__VA_ARGS__)))
#   define META_UNUSED_NODISCARD_INTERFACE(...)         META_UNUSED_NODISCARD(META_ABSTRACT(META_VIRTUAL(__VA_ARGS__)))

#   define META_NODISCARD_IMPLEMENTATION(...)           META_NODISCARD(META_OVERRIDE(__VA_ARGS__))
#   define META_UNUSED_IMPLEMENTATION(...)              META_UNUSED(META_OVERRIDE(__VA_ARGS__))
#   define META_UNUSED_NODISCARD_IMPLEMENTATION(...)    META_UNUSED_NODISCARD(META_OVERRIDE(__VA_ARGS__))

#   define META_UNUSED_CLASS(class_name)                class META_UNUSED(class_name)
#endif //BERYLLIUM_META_HPP

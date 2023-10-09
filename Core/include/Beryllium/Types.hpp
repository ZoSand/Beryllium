/*********************************************************************************************
 * [Owner]                                                                                   *
 *  Library: Beryllium                                                                       *
 *  Author: Zo LAMBERT                                                                       *
 *  Contact: <zo.lambert@zosand.fr>                                                          *
 *                         										                             *
 * [Header]                                                                                  *
 * This file defines the Beryllium types and type macros.                                    *
 *********************************************************************************************/

#ifndef BERYLLIUM_CORE_TYPES_HPP
#define BERYLLIUM_CORE_TYPES_HPP

// Types
namespace Be
{
    [[maybe_unused]]
    typedef bool b8, bool8, boolean8;

    [[maybe_unused]]
    typedef unsigned char u8, byte, unsigned8, uint8, uchar;
    [[maybe_unused]]
    typedef unsigned short u16, unsigned16, uint16, ushort;
    [[maybe_unused]]
    typedef unsigned int u32, unsigned32, uint32, uint;
    [[maybe_unused]]
    typedef unsigned long long u64, unsigned64, uint64, ulong;

    [[maybe_unused]]
    typedef signed char s8, signed8, int8;
    [[maybe_unused]]
    typedef signed short s16, signed16, int16;
    [[maybe_unused]]
    typedef signed int s32, signed32, int32;
    [[maybe_unused]]
    typedef signed long long s64, signed64, int64;

    [[maybe_unused]]
    typedef float f32, float32, real32;
    [[maybe_unused]]
    typedef double f64, float64, real64;
}

// Print formats
#   define PRINT_U8 "%hhu"
#   define PRINT_U16 "%hu"
#   define PRINT_U32 "%u"
#   define PRINT_U64 "%llu"

#   define PRINT_S8 "%hhd"
#   define PRINT_S16 "%hd"
#   define PRINT_S32 "%d"
#   define PRINT_S64 "%lld"

#   define PRINT_F32 "%f"
#   define PRINT_F64 "%lf"

#endif //BERYLLIUM_CORE_TYPES_HPP
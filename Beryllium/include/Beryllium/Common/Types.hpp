/*********************************************************************************************
 * [Owner]                                                                                   *
 *  Library: Beryllium                                                                       *
 *  Author: Zo LAMBERT                                                                       *
 *  Contact: <zo.lambert@zosand.fr>                                                          *
 *                         										                             *
 * [Header]                                                                                  *
 * This file defines the Beryllium types and type macros.                                    *
 *********************************************************************************************/

#ifndef BERYLLIUM_TYPES_HPP
#define BERYLLIUM_TYPES_HPP

#   include <Beryllium/Common/Meta.hpp>

// Types
namespace Be
{
	META_TYPEDEF(bool, b8, bool8, boolean8);

	META_TYPEDEF(unsigned char, u8, byte, unsigned8, uint8, uchar);
	META_TYPEDEF(unsigned short, u16, unsigned16, uint16, ushort);
	META_TYPEDEF(unsigned int, u32, unsigned32, uint32, uint);
	META_TYPEDEF(unsigned long long, u64, unsigned64, uint64, ulong);

	META_TYPEDEF(signed char, s8, signed8, int8);
	META_TYPEDEF(signed short, s16, signed16, int16);
	META_TYPEDEF(signed int, s32, signed32, int32);
	META_TYPEDEF(signed long long, s64, signed64, int64);

	META_TYPEDEF(float, f32, float32, real32);
	META_TYPEDEF(double, f64, float64, real64);
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

#endif //BERYLLIUM_TYPES_HPP

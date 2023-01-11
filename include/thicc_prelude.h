/*
 *   ___       ___       ___       ___       ___
 *  /\  \     /\__\     /\  \     /\  \     /\  \
 *  \:\  \   /:/__/_   _\:\  \   /::\  \   /::\  \
 *  /::\__\ /::\/\__\ /\/::\__\ /:/\:\__\ /:/\:\__\
 * /:/\/__/ \/\::/  / \::/\/__/ \:\ \/__/ \:\ \/__/
 * \/__/      /:/  /   \:\__\    \:\__\    \:\__\
 *            \/__/     \/__/     \/__/     \/__/
 *
 * Copyright 2022 Ville Rissanen
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1.   Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2.   Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef THICC_THICC_PRELUDE_H
#define THICC_THICC_PRELUDE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "thicc_enum_rank.h"
#include <limits.h>
#include <stddef.h>

#undef THICC_YES
#undef THICC_NO
#if (!defined __STDC_VERSION__) || (__STDC_VERSION__ < 199901L)
typedef unsigned int MutableBoolean;
#define THICC_YES 1u
#define THICC_NO 0u
#else
#include <stdbool.h>
typedef _Bool MutableBoolean;
#define THICC_YES true
#define THICC_NO false
#endif
typedef MutableBoolean const Boolean;

#undef THICC_C89
#undef THICC_C99
#undef THICC_C11
#undef THICC_C17
#undef THICC_C_VERSION
#if (!defined __STDC_VERSION__) || (__STDC_VERSION__ < 199901L)
#undef THICC_C_VERSION
#define THICC_C89 THICC_YES
#define THICC_C99 THICC_NO
#define THICC_C11 THICC_NO
#define THICC_C17 THICC_NO
#define THICC_C_VERSION 1989
#elif (__STDC_VERSION__ >= 199901L) && (__STDC_VERSION__ < 201112L)
#define THICC_C89 THICC_NO
#define THICC_C99 THICC_YES
#define THICC_C11 THICC_NO
#define THICC_C17 THICC_NO
#define THICC_C_VERSION 1999
#elif (__STDC_VERSION__ >= 201112L) && (__STDC_VERSION__ < 201710L)
#define THICC_C89 THICC_NO
#define THICC_C99 THICC_NO
#define THICC_C11 THICC_YES
#define THICC_C17 THICC_NO
#define THICC_C_VERSION 2011
#elif (__STDC_VERSION__ >= 201112L)
#define THICC_C89 THICC_NO
#define THICC_C99 THICC_NO
#define THICC_C11 THICC_NO
#define THICC_C17 THICC_YES
#define THICC_C_VERSION 2017
#endif

#undef THICC_C_AT_LEAST
#define THICC_C_AT_LEAST(_version_year) (THICC_C_VERSION >= (_version_year) ? THICC_YES : THICC_NO)

#undef THICC_RESTRICT
#if THICC_C89
#if defined(__GNUC__)
#define THICC_RESTRICT __restrict
#elif defined(__clang__)
#define THICC_RESTRICT __restrict
#elif defined(_MSC_VER)
#define THICC_RESTRICT __restrict
#else
#define THICC_RESTRICT
#endif
#else
#define THICC_RESTRICT restrict
#endif

#undef THICC_DEPRECATED
#undef THICC_FALLTHROUGH
#undef THICC_MAYBE_UNUSED
#undef THICC_NODISCARD
#undef THICC_NORETURN
#if THICC_C_AT_LEAST(2023)
#define THICC_DEPRECATED [[deprecated]]
#define THICC_FALLTHROUGH [[fallthrough]]
#define THICC_MAYBE_UNUSED [[maybe_unused]]
#define THICC_NODISCARD [[nodiscard]]
#define THICC_NORETURN [[noreturn]]
#else
#define THICC_DEPRECATED
#define THICC_FALLTHROUGH
#define THICC_MAYBE_UNUSED
#if (__GNUC__)
#define THICC_NODISCARD __attribute__((warn_unused_result))
#elif (__clang__)
#define THICC_NODISCARD __attribute__((warn_unused_result))
#else
#define THICC_NODISCARD
#endif
#if (__GNUC__)
#define THICC_NORETURN __attribute__((noreturn))
#elif (__clang__)
#define THICC_NODISCARD __attribute__((noreturn))
#else
#define THICC_NORETURN
#endif
#endif

#undef THICC_NAUGHT
#define THICC_NAUGHT NULL

#undef THICC_LEFT_GREATER
#undef THICC_RIGHT_GREATER
#undef THICC_EQUAL
#define THICC_LEFT_GREATER (-1)
#define THICC_RIGHT_GREATER (1)
#define THICC_EQUAL (0)

#undef THICC_CHAR_SIGNED
#undef THICC_CHAR_UNSIGNED
#if (CHAR_MIN == SCHAR_MIN)
#define THICC_CHAR_SIGNED THICC_YES
#define THICC_CHAR_UNSIGNED THICC_NO
#else
#define THICC_CHAR_SIGNED THICC_NO
#define THICC_CHAR_UNSIGNED THICC_YES
#endif

#undef THICC_FOREVER
#define THICC_FOREVER for (;;)

#undef THICC_DEBUG
#ifdef NDEBUG
#define THICC_DEBUG THICC_NO
#else
#define THICC_DEBUG THICC_YES
#endif

#if (UCHAR_MAX > INT_MAX)
typedef unsigned int	   MutableUnsignedCharacterPromotedType;
typedef unsigned int const UnsignedCharacterPromotedType;
#else
typedef int										   MutableUnsignedCharacterPromotedType;
typedef MutableUnsignedCharacterPromotedType const UnsignedCharacterPromotedType;
#endif

#undef THICC_CHAR_SIGNED
#undef THICC_CHAR_UNSIGNED
#if (CHAR_MIN == SCHAR_MIN)
#define THICC_CHAR_SIGNED THICC_YES
#define THICC_CHAR_UNSIGNED THICC_NO
typedef int								   MutableCharacterPromotedType;
typedef MutableCharacterPromotedType const CharacterPromotedType;
#else
#define THICC_CHAR_SIGNED THICC_NO
#define THICC_CHAR_UNSIGNED THICC_YES
typedef MutableUnsignedCharacterPromotedType	   MutableCharPromotedType;
typedef UnsignedCharacterPromotedType			   CharacterPromotedType;
#endif

typedef int				  MutableComparison;
typedef int const		  Comparison;
typedef size_t			  MutableSize;
typedef MutableSize const Size;

union thicc_union_value;
struct thicc_struct_behaviour;
struct thicc_struct_var;
struct thicc_struct_complex;
struct thicc_struct_string;
struct thicc_struct_array;
struct thicc_struct_object;

typedef enum thicc_enum_rank			  MutableRank;
typedef MutableRank const				  Rank;
typedef struct thicc_struct_var 		  Var;
typedef Var const						  Let;
typedef struct thicc_struct_behaviour	  MutableBehaviour;
typedef MutableBehaviour const			  Behaviour;
typedef union thicc_union_value			  MutableValue;
typedef MutableValue const				  Value;
typedef struct thicc_struct_object*		  MutableRoot;
typedef struct thicc_struct_object const* Root;

#undef THICC_STRINGIFY_HELPER
#undef THICC_STRINGIFY
#define THICC_STRINGIFY_HELPER(_value) #_value
#define THICC_STRINGIFY(_value) THICC_STRINGIFY_HELPER(_value)

typedef char				   MutableCharacter;
typedef MutableCharacter const Character;
#if THICC_C89
typedef unsigned long MutableNatural;
typedef long		  MutableInteger;
/* clang-format off */
#define THICC_NATURAL_FORMAT %lu
#define THICC_INTEGER_FORMAT %li
/* clang-format on */
#else
typedef unsigned long long						   MutableNatural;
typedef long long								   MutableInteger;
/* clang-format off */
#define THICC_NATURAL_FORMAT %llu
#define THICC_INTEGER_FORMAT %lli
/* clang-format on */
#endif
typedef MutableNatural const Natural;
typedef MutableInteger const Integer;
typedef long double			 MutableReal;
typedef MutableReal const	 Real;
/* clang-format off */
#define THICC_REAL_FORMAT %Lg
#define THICC_IMAGINARY_FORMAT %+Lgi
/* clang-format on */

typedef struct thicc_struct_complex MutableComplex;
typedef MutableComplex const		Complex;
typedef Let* (*MutableFunction)(Let*, Let*);
typedef MutableFunction const	   Function;
typedef struct thicc_struct_string MutableString;
typedef MutableString const        String;
typedef struct thicc_struct_array  MutableArray;
typedef MutableArray const		   Array;
typedef void* THICC_RESTRICT	   MutableObject;
typedef void const* THICC_RESTRICT Object;
typedef Object const			   ImmutableObject;

#ifdef __cplusplus
}
#endif

#endif /* THICC_THICC_PRELUDE_H */

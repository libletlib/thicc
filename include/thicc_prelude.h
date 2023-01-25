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
 * docs and/or other materials provided with the distribution.
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

/**
 * \file thicc_prelude.h
 * A header with macros and typedef to write ThicC C API's and functions in a clean way.
 */

/**
 * \mainpage ThicC
 *
 * A ducktyping library intended to for interfacing with multiple other languages. Written in pure C89, because that
 * is what most other languages share as a common denominator Foreign Function Interface.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "thicc_enum_rank.h"
#include <limits.h>
#include <stddef.h>

#undef THICC_YES
#undef THICC_NO
#if (!defined __STDC_VERSION__) || (__STDC_VERSION__ < 199901L)
/** Define Boolean type. In C89 this is unsigned int and in later standards it is `_Bool` */
typedef unsigned int MutableBoolean;
/** True value for boolean usage. In C89 this is 1u and in later standards it is `true`. */
#define THICC_YES 1u
/** False value for boolean usage. In C89 this is 0u and in later standards later it is `false`.*/
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
/** Boolean macro to determine if this version is C89. */
#define THICC_C89 THICC_YES
/** Boolean macro to determine if this version is C99. */
#define THICC_C99 THICC_NO
/** Boolean macro to determine if this version is C11. */
#define THICC_C11 THICC_NO
/** Boolean macro to determine if this version is C17. */
#define THICC_C17 THICC_NO
/** Year number of the standard. */
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
/** Define the restrict attribute for pointers using compiler specific attributes or the standard when available. */
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
/** Define the [[deprecated]] attribute when available. */
#define THICC_DEPRECATED
/** Define the [[fallthrough]] attribute when available. */
#define THICC_FALLTHROUGH
/** Define the [[maybe_unused]] attribute when available. */
#define THICC_MAYBE_UNUSED
#if (__GNUC__)
#define THICC_NODISCARD __attribute__((warn_unused_result))
#elif (__clang__)
#define THICC_NODISCARD __attribute__((warn_unused_result))
#else
/** Define the [[nodiscard]] attribute when available. */
#define THICC_NODISCARD
#endif
#if (__GNUC__)
#define THICC_NORETURN __attribute__((noreturn))
#elif (__clang__)
#define THICC_NODISCARD __attribute__((noreturn))
#else
/** Define the [[noreturn]] attribute when available. */
#define THICC_NORETURN
#endif
#endif

#undef THICC_NAUGHT
/** Define a `nothing` constant. */
#define THICC_NAUGHT NULL

#undef THICC_LEFT_GREATER
#undef THICC_RIGHT_GREATER
#undef THICC_EQUAL
/** Define standardised way to communicate three way comparison result for left side being greater. */
#define THICC_LEFT_GREATER (-1)
/** Define standardised way to communicate three way comparison result for right side being greater. */
#define THICC_RIGHT_GREATER (1)
/** Define standardised way to communicate three way comparison result for both sides being equal. */
#define THICC_EQUAL (0)

#undef THICC_DEBUG
#ifdef NDEBUG
#define THICC_DEBUG THICC_NO
#else
/** Define if debug mode is in use based on the `NDEBUG` macro `assert()` uses. */
#define THICC_DEBUG THICC_YES
#endif

#if (UCHAR_MAX > INT_MAX)
typedef unsigned int	   MutableUnsignedCharacterPromotedType;
typedef unsigned int const UnsignedCharacterPromotedType;
#else
/** UnsignedCharacter promoted type, can be int or if the domain of the signed int is not enough, the type will be unsigned int. */
typedef int										   MutableUnsignedCharacterPromotedType;
/** Const version of the UnsignedCharacter promoted type. */
typedef MutableUnsignedCharacterPromotedType const UnsignedCharacterPromotedType;
#endif

#undef THICC_CHAR_SIGNED
#undef THICC_CHAR_UNSIGNED
#if (CHAR_MIN == SCHAR_MIN)
/** Boolean macro to determine the signedness of `char`. */
#define THICC_CHAR_SIGNED THICC_YES
/** Boolean macro to determine the unsignedness of `char`. */
#define THICC_CHAR_UNSIGNED THICC_NO
/** Character promoted type. Can be int or unsigned int depending on if `char` is unsigned and if `int` has enough domain. */
typedef int								   MutableCharacterPromotedType;
/** Const version of the Characters promoted type. */
typedef MutableCharacterPromotedType const CharacterPromotedType;
#else
#define THICC_CHAR_SIGNED THICC_NO
#define THICC_CHAR_UNSIGNED THICC_YES
typedef MutableUnsignedCharacterPromotedType	   MutableCharPromotedType;
typedef UnsignedCharacterPromotedType			   CharacterPromotedType;
#endif

/** Comparison type, int to enable -1, 0, and 1. */
typedef int				  MutableComparison;
/** Const version of the Comparison type. */
typedef int const		  Comparison;
/** Size type, maps to to `size_t`. */
typedef size_t			  MutableSize;
/** Const version of the Size type. */
typedef MutableSize const Size;

union thicc_union_value;
struct thicc_struct_behaviour;
struct thicc_struct_var;
struct thicc_struct_complex;
struct thicc_struct_string;
struct thicc_struct_array;
struct thicc_struct_object;

/** Typedef for easier access to Ranks. */
typedef enum thicc_enum_rank			  MutableRank;
/** Const version of the Rank typedef. */
typedef MutableRank const				  Rank;
/** Typedef for easier access to Let internal structure. */
typedef struct thicc_struct_var 		  Var;
/** Const typedef for Let internal structure. */
typedef Var const						  Let;
/** Typedef for easier access to Behaviour. */
typedef struct thicc_struct_behaviour	  MutableBehaviour;
/** Const typedef for Behaviour. */
typedef MutableBehaviour const			  Behaviour;
/** Typedef for easier access to Let internal Value union. */
typedef union thicc_union_value			  MutableValue;
/** Const typedef of the Let internal Value union. */
typedef MutableValue const				  Value;
/** Typedef for easier access to Let object struct. */
typedef struct thicc_struct_object*		  MutableRoot;
/** Const typedef of the Let object struct. */
typedef struct thicc_struct_object const* Root;

#undef THICC_STRINGIFY_HELPER
#undef THICC_STRINGIFY
/** Helps with the `THICC_STRINGIFY` macro to expand and stringify arguments. */
#define THICC_STRINGIFY_HELPER(_value) #_value
/** Produces a string version of the given argument. */
#define THICC_STRINGIFY(_value) THICC_STRINGIFY_HELPER(_value)

/** Define Character type. */
typedef char				   MutableCharacter;
/** Const typedef of `Character` type. */
typedef MutableCharacter const Character;
#if THICC_C89
/** Define Natural type. In C89 it is `unsigned long`, in later standards it is `unsigned long long`. */
typedef unsigned long MutableNatural;
/** Define Integer type. In C89 it is `long`, in later standards it is `long long`. */
typedef long		  MutableInteger;
/* clang-format off */
/** Helper macro to format print Natural types. */
#define THICC_NATURAL_FORMAT %lu
/** Helper macro to format print Integer types. */
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
/** Const typedef of Natural. */
typedef MutableNatural const Natural;
/** Const typedef of Integer. */
typedef MutableInteger const Integer;
/** Define the Real type. */
typedef long double			 MutableReal;
/** Const typedef of the Real type. */
typedef MutableReal const	 Real;
/* clang-format off */
/** Helper macro to format print Real types. */
#define THICC_REAL_FORMAT %Lg
/** Helper macro to format print imaginary parts of Complex types. */
#define THICC_IMAGINARY_FORMAT %+Lgi
/* clang-format on */

/** Define the Complex type. Compatible with C99 _Complex number type definition. */
typedef struct thicc_struct_complex MutableComplex;
/** Const typedef of the Complex type. See `thicc_struct_complex.h` for details. */
typedef MutableComplex const		Complex;
/** Define the Function type and its signature. */
typedef Let* (*MutableFunction)(Let*, Let*);
/** Const typedef of the Function type. */
typedef MutableFunction const	   Function;
/** Define the String type. See `thicc_struct_string.h` for details. */
typedef struct thicc_struct_string MutableString;
/** Const typedef of the String type. */
typedef MutableString const        String;
/** Define the Array type. See `thicc_struct_array.h` for details. */
typedef struct thicc_struct_array  MutableArray;
/** Const typedef of the Array type. */
typedef MutableArray const		   Array;
/** Define the Object type. It usually is an empty Let or a Let Object type. */
typedef void* THICC_RESTRICT	   MutableObject;
/** Const typedef of the Object type. */
typedef void const* THICC_RESTRICT Object;
/** Even more const typedef of the Object type. */
typedef Object const			   ImmutableObject;

#ifdef __cplusplus
}
#endif

#endif /* THICC_THICC_PRELUDE_H */

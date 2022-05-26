/*
 * TTTTTTTTTTTTTTTTTTTTTTThhhhhhh               iiii                              CCCCCCCCCCCCC
 * T:::::::::::::::::::::Th:::::h              i::::i                          CCC::::::::::::C
 * T:::::::::::::::::::::Th:::::h               iiii                         CC:::::::::::::::C
 * T:::::TT:::::::TT:::::Th:::::h                                           C:::::CCCCCCCC::::C
 * TTTTTT  T:::::T  TTTTTT h::::h hhhhh       iiiiiii     cccccccccccccccc C:::::C       CCCCCC
 *         T:::::T         h::::hh:::::hhh    i:::::i   cc:::::::::::::::cC:::::C
 *         T:::::T         h::::::::::::::hh   i::::i  c:::::::::::::::::cC:::::C
 *         T:::::T         h:::::::hhh::::::h  i::::i c:::::::cccccc:::::cC:::::C
 *         T:::::T         h::::::h   h::::::h i::::i c::::::c     cccccccC:::::C
 *         T:::::T         h:::::h     h:::::h i::::i c:::::c             C:::::C
 *         T:::::T         h:::::h     h:::::h i::::i c:::::c             C:::::C
 *         T:::::T         h:::::h     h:::::h i::::i c::::::c     ccccccc C:::::C       CCCCCC
 *       TT:::::::TT       h:::::h     h:::::hi::::::ic:::::::cccccc:::::c  C:::::CCCCCCCC::::C
 *       T:::::::::T       h:::::h     h:::::hi::::::i c:::::::::::::::::c   CC:::::::::::::::C
 *       T:::::::::T       h:::::h     h:::::hi::::::i  cc:::::::::::::::c     CCC::::::::::::C
 *       TTTTTTTTTTT       hhhhhhh     hhhhhhhiiiiiiii    cccccccccccccccc        CCCCCCCCCCCCC
 *
 * Copyright 2021 - 2022 Ville Rissanen
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
 * following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following
 * disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 * following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef THICC_TYPEDEF_H
#define THICC_TYPEDEF_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <limits.h>
#include <stddef.h>

#if !defined(__STDC_VERSION__)
	#undef THICC_RESTRICT
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

#undef THICC_NOTHING
#define THICC_NOTHING NULL

#undef THICC_YES
#undef THICC_NO
#if defined(__STDC_VERSION__)
	#include <stdbool.h>
	typedef _Bool MutableBoolean;
	typedef MutableBoolean const Boolean;
	#define THICC_YES true
	#define THICC_NO false
#else
typedef unsigned int MutableBoolean;
typedef unsigned int const Boolean;
	#define THICC_YES 1u
	#define THICC_NO 0u
#endif

#undef THICC_LEFT_GREATER
#undef THICC_RIGHT_GREATER
#undef THICC_EQUAL
#define THICC_LEFT_GREATER (-1)
#define THICC_RIGHT_GREATER (1)
#define THICC_EQUAL (0)

#if (UCHAR_MAX > INT_MAX)
	typedef unsigned int MutableUnsignedCharacterPromotedType;
	typedef unsigned int const UnsignedCharacterPromotedType;
	#undef UnsignedCharacterPromotedRank
	#define UnsignedCharacterPromotedRank unsigned_integer_rank
#else
typedef int MutableUnsignedCharacterPromotedType;
typedef MutableUnsignedCharacterPromotedType const UnsignedCharacterPromotedType;
	#undef UnsignedCharacterPromotedRank
	#define UnsignedCharacterPromotedRank integer_rank
#endif

#undef UnsignedShortPromotedRank
#if (USHRT_MAX > INT_MAX)
	typedef unsigned int MutableUnsignedShortPromotedType;
	typedef unsigned int const UnsignedShortPromotedType;
	#undef UnsignedShortPromotedRank
	#define UnsignedShortPromotedRank unsigned_integer_rank
#else
typedef int MutableUnsignedShortPromotedType;
typedef MutableUnsignedShortPromotedType const UnsignedShortPromotedType;
	#undef UnsignedShortPromotedRank
	#define UnsignedShortPromotedRank integer_rank
#endif

#if (CHAR_MIN == SCHAR_MIN)
	#undef THICC_CHAR_SIGNED
	#undef THICC_CHAR_UNSIGNED
	#define THICC_CHAR_SIGNED THICC_YES
	#define THICC_CHAR_UNSIGNED THICC_NO
	typedef int MutableCharacterPromotedType;
	typedef MutableCharacterPromotedType const CharacterPromotedType;
	#undef CharacterPromotedRank
	#define CharacterPromotedRank integer_rank
#else
	#undef THICC_CHAR_SIGNED
	#undef THICC_CHAR_UNSIGNED
	#define THICC_CHAR_SIGNED THICC_NO
	#define THICC_CHAR_UNSIGNED THICC_YES
typedef MutableUnsignedCharacterPromotedType MutableCharPromotedType;
typedef UnsignedCharacterPromotedType CharacterPromotedType;
	#undef CharacterPromotedRank
	#define CharacterPromotedRank UnsignedCharacterPromotedRank
#endif

#define THICC_IF(_value) ((_value) == THICC_YES)
#define THICC_NOT(_value) ((_value) == THICC_NO)
#define THICC_IF_NOT(_value) THICC_NOT(THICC_IF(_value))
#define THICC_OR ||
#define THICC_AND &&

#if (!defined __STDC_VERSION__) THICC_OR(__STDC_VERSION__ < 199901L)
	#undef THICC_C89
	#undef THICC_C99
	#undef THICC_C11
	#undef THICC_C17
	#undef THICC_C_VERSION
	#define THICC_C89 THICC_YES
	#define THICC_C99 THICC_NO
	#define THICC_C11 THICC_NO
	#define THICC_C17 THICC_NO
	#define THICC_C_VERSION 1989
#elif (__STDC_VERSION__ >= 199901L) THICC_AND(__STDC_VERSION__ < 201112L)
	#undef THICC_C89
	#undef THICC_C99
	#undef THICC_C11
	#undef THICC_C17
	#define THICC_C89 THICC_NO
	#define THICC_C99 THICC_YES
	#define THICC_C11 THICC_NO
	#define THICC_C17 THICC_NO
	#define THICC_C_VERSION 1999
#elif (__STDC_VERSION__ >= 201112L) && (__STDC_VERSION__ < 201710L)
	#undef THICC_C89
	#undef THICC_C99
	#undef THICC_C11
	#undef THICC_C17
	#define THICC_C89 THICC_NO
	#define THICC_C99 THICC_NO
	#define THICC_C11 THICC_YES
	#define THICC_C17 THICC_NO
	#define THICC_C_VERSION 2011
#elif (__STDC_VERSION__ >= 201112L)
	#undef THICC_C89
	#undef THICC_C99
	#undef THICC_C11
	#undef THICC_C17
	#define THICC_C89 THICC_NO
	#define THICC_C99 THICC_NO
	#define THICC_C11 THICC_NO
	#define THICC_C17 THICC_YES
	#define THICC_C_VERSION 2017
#endif
#undef THICC_C_AT_LEAST
#define THICC_C_AT_LEAST(_version_year) THICC_C_VERSION >= (_version_year) ? THICC_YES : THICC_NO

#undef THICC_FOREVER
#define THICC_FOREVER (;;)

#undef THICC_DEBUG
#ifdef NDEBUG
	#define THICC_DEBUG THICC_NO
#else
	#define THICC_DEBUG THICC_YES
#endif

#undef subroutine
#undef function
#define subroutine(_name) void _name(Let self, Let args)
#define function(_name) MutableLet _name(Let self, Let args)

	typedef int MutableComparison;
	typedef int const Comparison;
	typedef size_t MutableSize;
	typedef MutableSize const Size;

	struct thicc_struct_let;
	typedef struct thicc_struct_let MutableLet;
	typedef MutableLet const Let;
	struct thicc_struct_behaviour;
	typedef struct thicc_struct_behaviour MutableBehaviour;
	typedef MutableBehaviour const Behaviour;
	union thicc_union_value;
	typedef union thicc_union_value MutableValue;
	typedef MutableValue const Value;

	typedef char MutableCharacter;
	typedef MutableCharacter const Character;
	typedef signed char MutableSignedCharacter;
	typedef MutableSignedCharacter const SignedCharacter;
	typedef unsigned char MutableUnsignedCharacter;
	typedef MutableUnsignedCharacter const UnsignedCharacter;
	typedef short MutableShort;
	typedef MutableShort const Short;
	typedef unsigned short MutableUnsignedShort;
	typedef MutableUnsignedShort const UnsignedShort;
	typedef int MutableInteger;
	typedef MutableInteger const Integer;
	typedef unsigned int MutableUnsignedInteger;
	typedef MutableUnsignedInteger const UnsignedInteger;
	typedef long MutableLong;
	typedef MutableLong const Long;
	typedef unsigned long MutableUnsignedLong;
	typedef MutableUnsignedLong const UnsignedLong;
	typedef float MutableFloat;
	typedef MutableFloat const Float;
	typedef double MutableDouble;
	typedef MutableDouble const Double;
	typedef long double MutableLongDouble;
	typedef MutableLongDouble const LongDouble;
	typedef char* THICC_RESTRICT MutableString;
	typedef char const* THICC_RESTRICT String;
	typedef String const ImmutableString;
	typedef MutableLet* THICC_RESTRICT MutableArray;
	typedef Let* THICC_RESTRICT Array;
	typedef Array const ImmutableArray;
	typedef void (*MutableSubroutine)(Let, Let);
	typedef MutableSubroutine const Subroutine;
	typedef MutableLet (*MutableFunction)(Let, Let);
	typedef MutableFunction const Function;
	typedef void* THICC_RESTRICT MutableObject;
	typedef void const* THICC_RESTRICT Object;
	typedef Object const ImmutableObject;

#if THICC_IF(THICC_C_AT_LEAST(1999))
	typedef long long MutableLongLong;
	typedef MutableLongLong const LongLong;
	typedef unsigned long long MutableUnsignedLongLong;
	typedef MutableUnsignedLongLong const UnsignedLongLong;
#endif

#undef THICC_HAS_COMPLEX
#if THICC_IF(THICC_C_AT_LEAST(1999)) THICC_AND(!defined __STDC_NO_COMPLEX__)
	#define THICC_HAS_COMPLEX THICC_YES
	typedef float _Complex MutableFloatComplex;
	typedef MutableFloatComplex const FloatComplex;
	typedef double _Complex MutableDoubleComplex;
	typedef MutableDoubleComplex const DoubleComplex;
	typedef long double _Complex MutableLongDoubleComplex;
	typedef MutableLongDoubleComplex const LongDoubleComplex;
#else
	#define THICC_HAS_COMPLEX THICC_NO
#endif

#undef THICC_HAS_IMAGINARY
#if THICC_IF(THICC_HAS_COMPLEX) && ( \
       (((THICC_C_VERSION >= 1999) && (THICC_C_VERSION < 2023) && (defined __STDC_IEC_559_COMPLEX__)) \
    || ((THICC_C_AT_LEAST(2023)) && (defined __STDC_IEC_60559_COMPLEX__))) \
    && (defined _Imaginary_I && defined imaginary))
	#define THICC_HAS_IMAGINARY THICC_YES
	typedef float _Imaginary MutableFloatImaginary;
	typedef MutableFloatImaginary const FloatImaginary;
	typedef double _Imaginary MutableDoubleImaginary;
	typedef MutableDoubleImaginary const DoubleImaginary;
	typedef long double _Imaginary MutableLongDoubleImaginary;
	typedef MutableLongDoubleImaginary const LongDoubleImaginary;
#else
	#define THICC_HAS_IMAGINARY THICC_NO
#endif

#ifdef __cplusplus
}
#endif

#endif//THICC_TYPEDEF_H

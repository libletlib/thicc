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
#ifndef THICC_STRING_H
#define THICC_STRING_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "../core/thicc_enum_rank.h"
#include "thicc_math_typedef.h"
#include <stdlib.h>

#undef THICC_STRING_TO_FLOATING_POINT
#if THICC_IF(THICC_C89)
	#define THICC_STRING_TO_FLOATING_POINT(_string, _string_end) ((LongDouble) strtod(_string, _string_end))
#else
	#define THICC_STRING_TO_FLOATING_POINT(_string, _string_end) (strtold(_string, _string_end))
#endif

#undef THICC_STRING_TO_INTEGER
#if THICC_IF(THICC_C89)
	#define THICC_STRING_TO_INTEGER(_string, _string_end) (strtol(_string, _string_end, 0))
#else
	#define THICC_STRING_TO_INTEGER(_string, _string_end) (strtoll(_string, _string_end, 0))
#endif

#undef THICC_STRING_TO_UNSIGNED_INTEGER
#if THICC_IF(THICC_C89)
	#define THICC_STRING_TO_UNSIGNED_INTEGER(_string, _string_end) (strtoul(_string, _string_end, 0))
#else
	#define THICC_STRING_TO_UNSIGNED_INTEGER(_string, _string_end) (strtoull(_string, _string_end, 0))
#endif

#undef THICC_CHARACTERS_IN_INTEGER
#if THICC_IF(THICC_C89)
	#define THICC_CHARACTERS_IN_INTEGER(_number) ((Size) THICC_MAX(1ul, THICC_FLOORD(THICC_LOG10D((Double) _number))) + 1) // sign
#else
	#define THICC_CHARACTERS_IN_INTEGER(_number) ((Size) THICC_MAX(1ull, THICC_FLOORL(THICC_LOG10L((LongDouble) (_number)))) + 1) // sign
#endif

	MutableSize string_length(ImmutableString);
	MutableString string_copy(ImmutableString);
	MutableString string_copy_slice(ImmutableString, Size, Size);
	MutableComparison string_compare(ImmutableString, String);
	MutableString string_filter_and(ImmutableString, ImmutableString);
	MutableString string_filter_or(ImmutableString, ImmutableString);
	MutableString string_filter_xor(ImmutableString, ImmutableString);
	MutableString string_map_bit_not(ImmutableString);
	MutableString string_map_bit_complement(ImmutableString);
	MutableString string_map_positive(ImmutableString);
	MutableString string_map_negative(ImmutableString);
	MutableString string_map_increment(MutableString);
	MutableString string_map_decrement(MutableString);
	MutableCharacter string_character_at(ImmutableString, Long);
	MutableLet string_to_number(ImmutableString);
	MutableString string_concatenate(ImmutableString, ImmutableString);
	String string_find_substring(ImmutableString, ImmutableString);
	MutableString string_remove_substring(ImmutableString, ImmutableString);
	MutableString string_remove_characters(ImmutableString, ImmutableString);
	MutableString string_empty(void);
	MutableBoolean string_is_empty(String);
	MutableString string_from_characters(Size, ...);
	MutableString string_from_signed_characters(Size, ...);
	MutableString string_from_unsigned_characters(Size, ...);
	MutableSize characters_in_float(Float);
	MutableSize characters_in_double(Double);
	MutableSize characters_in_long_double(LongDouble);
	MutableString string_from_integer(Integer);
	MutableString string_from_unsigned_integer(UnsignedInteger);
	MutableString string_from_long(Long);
	MutableString string_from_unsigned_long(UnsignedLong);
	MutableString string_from_float(Float);
	MutableString string_from_double(Double);
	MutableString string_from_long_double(LongDouble);

#if THICC_IF(THICC_C_AT_LEAST(1999))
#include "c99/thicc_c99_string.h"
#endif

#ifdef __cplusplus
}
#endif

#endif//THICC_STRING_H

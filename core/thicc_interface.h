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
#ifndef THICC_INTERFACE_H
#define THICC_INTERFACE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "thicc_enum_rank.h"

	MutableRank rank(Let);
	MutableLet cast(Let, Rank);
	MutableBoolean requires_free(Let);
	void unlet(Let);

	String string_view(Let);
	Array array_view(Let);
	Object object_view(Let);

	MutableBoolean as_boolean(Let);
	MutableCharacter as_character(Let);
	MutableSignedCharacter as_signed_character(Let);
	MutableUnsignedCharacter as_unsigned_character(Let);
	MutableShort as_short(Let);
	MutableUnsignedShort as_unsigned_short(Let);
	MutableInteger as_integer(Let);
	MutableUnsignedInteger as_unsigned_integer(Let);
	MutableLong as_long(Let);
	MutableUnsignedLong as_unsigned_long(Let);
	MutableFloat as_float(Let);
	MutableDouble as_double(Let);
	MutableLongDouble as_long_double(Let);
	MutableString as_string(Let);
	MutableSubroutine as_subroutine(Let);
	MutableFunction as_function(Let);
	MutableArray as_array(Let);
	MutableObject as_object(Let);

	MutableLet array_of(Size, ...);
	MutableLet object_of(Size, ...);
	MutableLet invoke(Let, Size, ...);
	MutableLet member(Let, Let);
	MutableLet sum(Let, Let);
	MutableLet difference(Let, Let);
	MutableLet quotient(Let, Let);
	MutableLet modulo(Let, Let);
	MutableLet product(Let, Let);
	MutableLet power(Let, Let);
	MutableLet root(Let, Let);
	MutableLet logarithm(Let, Let);
	MutableLet bit_and(Let, Let);
	MutableLet bit_or(Let, Let);
	MutableLet bit_xor(Let, Let);
	MutableLet index_of(Let, Let);

	MutableLet bit_not(Let);
	MutableLet bit_complement(Let);
	MutableLet indirection(Let);
	MutableLet negative(Let);
	MutableLet positive(Let);

	MutableLet pre_increment(Let);
	MutableLet pre_decrement(Let);
	MutableLet post_increment(Let);
	MutableLet post_decrement(Let);

	MutableComparison compare(Let, Let);
	MutableBoolean equal(Let, Let);
	MutableBoolean greater_than(Let, Let);
	MutableBoolean less_than(Let, Let);
	MutableBoolean not_equal(Let, Let);

	MutableBoolean is_character(Let);
	MutableBoolean is_unsigned(Let);
	MutableBoolean is_signed(Let);
	MutableBoolean is_numeric(Let);
	MutableBoolean is_string(Let);
	MutableBoolean is_invokable(Let);
	MutableBoolean is_array(Let);
	MutableBoolean is_object(Let);

#if THICC_IF(THICC_C_AT_LEAST(1999))
	#include "c99/thicc_c99_interface.h"
#endif

#ifdef __cplusplus
}
#endif

#endif//THICC_INTERFACE_H

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
#ifndef THICC_STRUCT_LET_H
#define THICC_STRUCT_LET_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "thicc_typedef.h"
#include "thicc_union_value.h"
#include "c99/thicc_c99_struct_let.h"

struct Behaviour;

	struct thicc_struct_let
	{
		MutableValue value;
		Behaviour* behaviour;
	};

	MutableLet let_init(void);
	MutableLet let_boolean(Boolean);
	MutableLet let_character(Character);
	MutableLet let_signed_character(SignedCharacter);
	MutableLet let_unsigned_character(UnsignedCharacter);
	MutableLet let_short(Short);
	MutableLet let_unsigned_short(UnsignedShort);
	MutableLet let_integer(Integer);
	MutableLet let_unsigned_integer(UnsignedInteger);
	MutableLet let_long(Long);
	MutableLet let_unsigned_long(UnsignedLong);
	MutableLet let_long_long(LongLong);
	MutableLet let_unsigned_long_long(UnsignedLongLong);
	MutableLet let_float(Float);
	MutableLet let_double(Double);
	MutableLet let_long_double(LongDouble);
	MutableLet let_float_complex(FloatComplex);
	MutableLet let_double_complex(DoubleComplex);
	MutableLet let_long_double_complex(LongDoubleComplex);
	MutableLet let_string(ImmutableString);
	MutableLet let_string_no_copy(MutableString);
	MutableLet let_subroutine(Subroutine);
	MutableLet let_function(Function);
	MutableLet let_array(ImmutableArray);
	MutableLet let_array_no_copy(MutableArray);
	MutableLet let_object(ImmutableObject);
	MutableLet let_object_no_copy(MutableObject);
	MutableLet let_copy(Let);
	MutableLet let_move(MutableLet);

	MutableLet let_empty(void);
	MutableBoolean let_is_empty(Let);

#ifdef __cplusplus
}
#endif

#endif//THICC_STRUCT_LET_H

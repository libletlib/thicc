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
#ifndef THICC_STRUCT_BEHAVIOUR_H
#define THICC_STRUCT_BEHAVIOUR_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "thicc_enum_rank.h"

	struct thicc_struct_behaviour {
		Rank rank;
		void (*const deallocate)(Let);
		MutableBoolean (*const as_boolean)(Let);
		MutableCharacter (*const as_character)(Let);
		MutableSignedCharacter (*const as_signed_character)(Let);
		MutableUnsignedCharacter (*const as_unsigned_character)(Let);
		MutableShort (*const as_short)(Let);
		MutableUnsignedShort (*const as_unsigned_short)(Let);
		MutableInteger (*const as_integer)(Let);
		MutableUnsignedInteger (*const as_unsigned_integer)(Let);
		MutableLong (*const as_long)(Let);
		MutableUnsignedLong (*const as_unsigned_long)(Let);
#if THICC_IF(THICC_C_AT_LEAST(1999))
		MutableLongLong (*const as_long_long)(Let);
		MutableUnsignedLongLong (*const as_unsigned_long_long)(Let);
#endif
		MutableFloat (*const as_float)(Let);
		MutableDouble (*const as_double)(Let);
		MutableLongDouble (*const as_long_double)(Let);
#if THICC_IF(THICC_HAS_COMPLEX)
		MutableFloatComplex (*const as_float_complex)(Let);
		MutableDoubleComplex (*const as_double_complex)(Let);
		MutableLongDoubleComplex (*const as_long_double_complex)(Let);
#endif
		MutableString (*const as_string)(Let);
		MutableSubroutine (*const as_subroutine)(Let);
		MutableFunction (*const as_function)(Let);
		MutableArray (*const as_array)(Let);
		MutableObject (*const as_object)(Let);
		MutableLet (*const sum)(Let, Let);
		MutableLet (*const difference)(Let, Let);
		MutableLet (*const product)(Let, Let);
		MutableLet (*const quotient)(Let, Let);
		MutableLet (*const power)(Let, Let);
		MutableLet (*const modulo)(Let, Let);
		MutableLet (*const logarithm)(Let, Let);
		MutableLet (*const root)(Let, Let);
		MutableLet (*const bit_and)(Let, Let);
		MutableLet (*const bit_or)(Let, Let);
		MutableLet (*const bit_xor)(Let, Let);
		MutableLet (*const bit_not)(Let);
		MutableLet (*const bit_complement)(Let);
		MutableLet (*const index_of)(Let, Let);
		MutableLet (*const indirection)(Let);
		MutableLet (*const negative)(Let);
		MutableLet (*const positive)(Let);
		MutableLet (*const increment)(Let);
		MutableLet (*const decrement)(Let);
		MutableComparison (*const comparison)(Let, Let);
	};

	extern Behaviour boolean_behaviour;
	extern Behaviour character_behaviour;
	extern Behaviour signed_character_behaviour;
	extern Behaviour unsigned_character_behaviour;
	extern Behaviour short_behaviour;
	extern Behaviour unsigned_short_behaviour;
	extern Behaviour integer_behaviour;
	extern Behaviour unsigned_integer_behaviour;
	extern Behaviour long_behaviour;
	extern Behaviour unsigned_long_behaviour;
	extern Behaviour float_behaviour;
	extern Behaviour double_behaviour;
	extern Behaviour long_double_behaviour;
	extern Behaviour string_behaviour;
	extern Behaviour subroutine_behaviour;
	extern Behaviour function_behaviour;
	extern Behaviour array_behaviour;
	extern Behaviour object_behaviour;

#if THICC_IF(THICC_C_AT_LEAST(1999))
#include "c99/thicc_c99_struct_behaviour.h"
#endif

#ifdef __cplusplus
}
#endif

#endif//THICC_STRUCT_BEHAVIOUR_H

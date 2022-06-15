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
#ifdef __cplusplus
extern "C"
{
#endif

#include "thicc_struct_let.h"
#include "thicc_struct_behaviour.h"
#include "../utility/thicc_string.h"
#include "../utility/thicc_array.h"
#include "../utility/thicc_object.h"
#include <string.h>

	MutableLet let_init() {
		MutableLet let;
		(void) memset(&let, 0, sizeof(MutableLet));
		return let;
	}

	MutableLet let_boolean(Boolean _value) {
		MutableLet let = let_init();
		let.value.boolean_type = _value;
		let.behaviour = &boolean_behaviour;
		return let;
	}

	MutableLet let_character(Character _value) {
		MutableLet let = let_init();
		let.value.character_type = _value;
		let.behaviour = &character_behaviour;
		return let;
	}

	MutableLet let_signed_character(SignedCharacter _value) {
		MutableLet let = let_init();
		let.value.signed_character_type = _value;
		let.behaviour = &signed_character_behaviour;
		return let;
	}

	MutableLet let_unsigned_character(UnsignedCharacter _value) {
		MutableLet let = let_init();
		let.value.unsigned_character_type = _value;
		let.behaviour = &unsigned_character_behaviour;
		return let;
	}

	MutableLet let_short(Short _value) {
		MutableLet let = let_init();
		let.value.short_type = _value;
		let.behaviour = &short_behaviour;
		return let;
	}

	MutableLet let_unsigned_short(UnsignedShort _value) {
		MutableLet let = let_init();
		let.value.unsigned_short_type = _value;
		let.behaviour = &unsigned_short_behaviour;
		return let;
	}

	MutableLet let_integer(Integer _value) {
		MutableLet let = let_init();
		let.value.integer_type = _value;
		let.behaviour = &integer_behaviour;
		return let;
	}

	MutableLet let_unsigned_integer(UnsignedInteger _value) {
		MutableLet let = let_init();
		let.value.unsigned_integer_type = _value;
		let.behaviour = &unsigned_integer_behaviour;
		return let;
	}

	MutableLet let_long(Long _value) {
		MutableLet let = let_init();
		let.value.long_type = _value;
		let.behaviour = &long_behaviour;
		return let;
	}

	MutableLet let_unsigned_long(UnsignedLong _value) {
		MutableLet let = let_init();
		let.value.unsigned_long_type = _value;
		let.behaviour = &unsigned_long_behaviour;
		return let;
	}

	MutableLet let_long_long(LongLong _value) {
		MutableLet let = let_init();
		let.value.long_long_type = _value;
		let.behaviour = &long_long_behaviour;
		return let;
	}

	MutableLet let_unsigned_long_long(UnsignedLongLong _value) {
		MutableLet let = let_init();
		let.value.unsigned_long_long_type = _value;
		let.behaviour = &unsigned_long_long_behaviour;
		return let;
	}

	MutableLet let_float(Float _value) {
		MutableLet let = let_init();
		let.value.float_type = _value;
		let.behaviour = &float_behaviour;
		return let;
	}

	MutableLet let_double(Double _value) {
		MutableLet let = let_init();
		let.value.double_type = _value;
		let.behaviour = &double_behaviour;
		return let;
	}

	MutableLet let_long_double(LongDouble _value) {
		MutableLet let = let_init();
		let.value.long_double_type = _value;
		let.behaviour = &long_double_behaviour;
		return let;
	}

	MutableLet let_float_complex(FloatComplex _value) {
		MutableLet let = let_init();
		let.value.float_complex_type = _value;
		let.behaviour = &float_complex_behaviour;
		return let;
	}

	MutableLet let_double_complex(DoubleComplex _value) {
		MutableLet let = let_init();
		let.value.double_complex_type = _value;
		let.behaviour = &double_complex_behaviour;
		return let;
	}

	MutableLet let_long_double_complex(LongDoubleComplex _value) {
		MutableLet let = let_init();
		let.value.long_double_complex_type = _value;
		let.behaviour = &long_double_complex_behaviour;
		return let;
	}

	MutableLet let_string(ImmutableString _value) {
		MutableLet let = let_init();
		let.value.string_type = string_copy(_value);
		let.behaviour = &string_behaviour;
		return let;
	}

	MutableLet let_string_no_copy(MutableString _value) {
		MutableLet let = let_init();
		let.value.string_type = _value;
		let.behaviour = &string_behaviour;
		return let;
	}

	MutableLet let_subroutine(Subroutine _value) {
		MutableLet let = let_init();
		let.value.subroutine_type = _value;
		let.behaviour = &subroutine_behaviour;
		return let;
	}

	MutableLet let_function(Function _value) {
		MutableLet let = let_init();
		let.value.function_type = _value;
		let.behaviour = &function_behaviour;
		return let;
	}

	MutableLet let_array(Array _value) {
		MutableLet let = let_init();
		let.value.array_type = array_copy(_value);
		let.behaviour = &array_behaviour;
		return let;
	}

	MutableLet let_array_no_copy(MutableArray _value) {
		MutableLet let = let_init();
		let.value.array_type = _value;
		let.behaviour = &array_behaviour;
		return let;
	}

	MutableLet let_object(ImmutableObject _value) {
		MutableLet let = let_init();
		let.value.object_type = object_copy(_value);
		let.behaviour = &object_behaviour;
		return let;
	}

	MutableLet let_object_no_copy(MutableObject _value) {
		MutableLet let = let_init();
		let.value.object_type = _value;
		let.behaviour = &object_behaviour;
		return let;
	}

	MutableLet let_copy(Let _let) {
		if(let_is_empty(_let))
			return let_empty();
		switch(_let.behaviour->rank) {
			case boolean_rank:
				return let_boolean(_let.value.boolean_type);
			case character_rank:
				return let_character(_let.value.character_type);
			case signed_character_rank:
				return let_signed_character(_let.value.signed_character_type);
			case unsigned_character_rank:
				return let_unsigned_character(_let.value.unsigned_character_type);
			case short_rank:
				return let_short(_let.value.short_type);
			case unsigned_short_rank:
				return let_unsigned_short(_let.value.unsigned_short_type);
			case integer_rank:
				return let_integer(_let.value.integer_type);
			case unsigned_integer_rank:
				return let_unsigned_integer(_let.value.unsigned_integer_type);
			case long_rank:
				return let_long(_let.value.long_type);
			case unsigned_long_rank:
				return let_unsigned_long(_let.value.unsigned_long_type);
			case long_long_rank:
				return let_long_long(_let.value.long_long_type);
			case unsigned_long_long_rank:
				return let_unsigned_long_long(_let.value.unsigned_long_long_type);
			case float_rank:
				return let_float(_let.value.float_type);
			case double_rank:
				return let_double(_let.value.double_type);
			case long_double_rank:
				return let_long_double(_let.value.long_double_type);
			case float_complex_rank:
				return let_float_complex((_let.value.float_complex_type));
			case double_complex_rank:
				return let_double_complex(_let.value.double_complex_type);
			case long_double_complex_rank:
				return let_long_double_complex(_let.value.long_double_complex_type);
			case string_rank:
				return let_string(_let.value.string_type);
			case subroutine_rank:
				return let_subroutine(_let.value.subroutine_type);
			case function_rank:
				return let_function(_let.value.function_type);
			case array_rank:
				return let_array(_let.value.array_type);
			case object_rank:
				return let_object(_let.value.object_type);
		}
	}

	MutableLet let_move(MutableLet _let) {
		MutableLet let = let_init();
		let.value = _let.value;
		_let.value = zero_out_value(_let.value);
		_let.value.object_type = THICC_NOTHING;
		let.behaviour = _let.behaviour;
		_let.behaviour = THICC_NOTHING;
		return let;
	}

	MutableLet let_empty(void) {
		MutableLet let = let_init();
		let.value.object_type = THICC_NOTHING;
		let.behaviour = THICC_NOTHING;
		return let;
	}

	MutableBoolean let_is_empty(Let _let) {
		return _let.behaviour ? THICC_NO : THICC_YES;
	}

#ifdef __cplusplus
}
#endif

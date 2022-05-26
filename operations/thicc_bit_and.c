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
#include "../utility/thicc_float.h"
#include "../utility/thicc_array.h"
#ifdef __cplusplus
extern "C"
{
#endif

#include "thicc_bit_and.h"
#include "../core/thicc_interface.h"
#include "../core/thicc_struct_let.h"
#include "../utility/thicc_function.h"
#include "../utility/thicc_string.h"
#include "../utility/thicc_float.h"

	MutableLet boolean_bit_and(Let _left, Let _right) {
		if(_left.value.boolean_type && _right.value.boolean_type)
			return let_boolean(THICC_YES);
		return let_boolean(THICC_NO);
	}

	MutableLet character_bit_and(Let _left, Let _right) {
		return let_character((Character) (CharacterPromotedType) (_left.value.character_type & _right.value.character_type));
	}
	
	MutableLet signed_character_bit_and(Let _left, Let _right) {
		return let_signed_character((SignedCharacter) (Integer) (_left.value.character_type & _right.value.character_type));
	}

	MutableLet unsigned_character_bit_and(Let _left, Let _right) {
		return let_unsigned_character((UnsignedCharacter) (UnsignedCharacterPromotedType) (_left.value.character_type & _right.value.character_type));
	}
	
	MutableLet short_bit_and(Let _left, Let _right) {
		return let_short((Short) (_left.value.short_type & _right.value.short_type));
	}
	
	MutableLet unsigned_short_bit_and(Let _left, Let _right) {
		return let_unsigned_short(_left.value.unsigned_short_type & _right.value.unsigned_short_type);
	}

	MutableLet integer_bit_and(Let _left, Let _right) {
		return let_integer(_left.value.integer_type & _right.value.integer_type);
	}

	MutableLet unsigned_integer_bit_and(Let _left, Let _right) {
		return let_unsigned_integer(_left.value.unsigned_integer_type & _right.value.unsigned_integer_type);
	}

	MutableLet long_bit_and(Let _left, Let _right) {
		return let_long(_left.value.long_type & _right.value.long_type);
	}

	MutableLet unsigned_long_bit_and(Let _left, Let _right) {
		return let_unsigned_long(_left.value.unsigned_long_type & _right.value.unsigned_long_type);
	}

	MutableLet float_bit_and(Let _left, Let _right) {
		MutableFloatBytes left_bytes, right_bytes;
		left_bytes.real = _left.value.float_type;
		right_bytes.real = _right.value.float_type;
		return let_float(float_byte_and(left_bytes, right_bytes).real);
	}

	MutableLet double_bit_and(Let _left, Let _right) {
		MutableDoubleBytes left_bytes, right_bytes;
		left_bytes.real = _left.value.double_type;
		right_bytes.real = _right.value.double_type;
		return let_double(double_byte_and(left_bytes, right_bytes).real);
	}

	MutableLet long_double_bit_and(Let _left, Let _right) {
		MutableLongDoubleBytes left_bytes, right_bytes;
		left_bytes.real = _left.value.long_double_type;
		right_bytes.real = _right.value.long_double_type;
		return let_long_double(long_double_byte_and(left_bytes, right_bytes).real);
	}

	MutableLet string_bit_and(Let _left, Let _right) {
		return let_string_no_copy(string_filter_and(string_view(_left), string_view(_right)));
	}

	MutableLet subroutine_bit_and(Let _left, Let _right) {
		return let_empty();
	}

	MutableLet function_bit_and(Let _left, Let _right) {
		Let left_result = function_invoke(_left, let_empty());
		Let right_result = function_invoke(_right, let_empty());
		Let result = bit_and(left_result, right_result);
		if(requires_free(right_result))
			unlet(right_result);
		if(requires_free(left_result))
			unlet(left_result);
		return result;
	}

	MutableLet array_bit_and(Let _left, Let _right) {
		return let_array_no_copy(array_filter_and(array_view(_left), array_view(_right)));
	}

	MutableLet object_bit_and(Let _left, Let _right) {
		Let property_name = let_string("&");
		Let property = member(_left, property_name);
		unlet(property_name);
		if(let_is_empty(property) || !is_invokable(property))
			return let_empty();
		return invoke(property, 2, &_left, &_right);
	}

#ifdef __cplusplus
}
#endif

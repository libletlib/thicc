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

#include "thicc_bit_not.h"
#include "../core/thicc_interface.h"
#include "../core/thicc_struct_let.h"
#include "../utility/thicc_function.h"
#include "../utility/thicc_math.h"

	MutableLet boolean_bit_not(Let _let) {
		return let_boolean(_let.value.boolean_type ? THICC_NO : THICC_YES);
	}

	MutableLet character_bit_not(Let _let) {
		if(_let.value.character_type)
			return let_boolean(THICC_NO);
		return let_boolean(THICC_YES);
	}

	MutableLet signed_character_bit_not(Let _let) {
		if(_let.value.signed_character_type)
			return let_boolean(THICC_NO);
		return let_boolean(THICC_YES);
	}

	MutableLet unsigned_character_bit_not(Let _let) {
		if(_let.value.unsigned_character_type)
			return let_boolean(THICC_NO);
		return let_boolean(THICC_YES);
	}

	MutableLet short_bit_not(Let _let) {
		if(_let.value.short_type)
			return let_boolean(THICC_NO);
		return let_boolean(THICC_YES);
	}

	MutableLet unsigned_short_bit_not(Let _let) {
		if(_let.value.unsigned_short_type)
			return let_boolean(THICC_NO);
		return let_boolean(THICC_YES);
	}

	MutableLet integer_bit_not(Let _let) {
		if(_let.value.integer_type)
			return let_boolean(THICC_NO);
		return let_boolean(THICC_YES);
	}

	MutableLet unsigned_integer_bit_not(Let _let) {
		if(_let.value.unsigned_integer_type)
			return let_boolean(THICC_NO);
		return let_boolean(THICC_YES);
	}

	MutableLet long_bit_not(Let _let) {
		if(_let.value.long_type)
			return let_boolean(THICC_NO);
		return let_boolean(THICC_YES);
	}

	MutableLet unsigned_long_bit_not(Let _let) {
		if(_let.value.unsigned_long_type)
			return let_boolean(THICC_NO);
		return let_boolean(THICC_YES);
	}

	MutableLet float_bit_not(Let _let) {
		if(math_float_equal(_let.value.float_type, 0.0f))
			return let_boolean(THICC_YES);
		return let_boolean(THICC_NO);
	}

	MutableLet double_bit_not(Let _let) {
		if(math_double_equal(_let.value.double_type, 0.0))
			return let_boolean(THICC_YES);
		return let_boolean(THICC_NO);
	}

	MutableLet long_double_bit_not(Let _let) {
		if(math_long_double_equal(_let.value.long_double_type, 0.0l))
			return let_boolean(THICC_YES);
		return let_boolean(THICC_NO);
	}

	MutableLet string_bit_not(Let _let) {
		if(_let.value.string_type)
			return let_boolean(THICC_NO);
		return let_boolean(THICC_YES);
	}

	MutableLet subroutine_bit_not(Let _let) {
		return let_empty();
	}

	MutableLet function_bit_not(Let _let) {
		Let let_result = function_invoke(_let, let_empty());
		Let result = bit_not(let_result);
		if(requires_free(let_result))
			unlet(let_result);
		return result;
	}

	MutableLet array_bit_not(Let _let) {
		if(_let.value.array_type)
			return let_boolean(THICC_NO);
		return let_boolean(THICC_YES);
	}

	MutableLet object_bit_not(Let _let) {
		Let property_name = let_string("!");
		Let property = member(_let, property_name);
		unlet(property_name);
		if(let_is_empty(property) || !is_invokable(property))
			return let_empty();
		return invoke(property, 1, &_let);
	}

#ifdef __cplusplus
}
#endif

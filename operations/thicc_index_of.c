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

#include <stdlib.h>
#include "thicc_index_of.h"
#include "../core/thicc_struct_let.h"
#include "../core/thicc_interface.h"
#include "../utility/thicc_function.h"
#include "../utility/thicc_string.h"
#include "../utility/thicc_array.h"

	MutableLet boolean_index_of(Let _let, Let _index) {
		return let_boolean(_let.value.boolean_type);
	}

	MutableLet character_index_of(Let _let, Let _index) {
		return let_character(_let.value.character_type);
	}
	
	MutableLet signed_character_index_of(Let _let, Let _index) {
		return let_signed_character(_let.value.signed_character_type);
	}

	MutableLet unsigned_character_index_of(Let _let, Let _index) {
		return let_unsigned_character(_let.value.unsigned_character_type);
	}
	
	MutableLet short_index_of(Let _let, Let _index) {
		MutableString string = string_from_integer((Integer) _let.value.short_type);
		Let result = let_short((Short) strtol(string, NULL, 10));
		free((void*) string);
		return result;
	}
	
	MutableLet unsigned_short_index_of(Let _let, Let _index) {
		MutableString string = string_from_unsigned_integer((UnsignedInteger) _let.value.unsigned_short_type);
		Let result = let_unsigned_short((UnsignedShort) strtoul(string, NULL, 10));
		free((void*) string);
		return result;
	}

	MutableLet integer_index_of(Let _let, Let _index) {
		MutableString string = string_from_integer(_let.value.integer_type);
		Let result = let_integer((Integer) strtol(string, NULL, 10));
		free((void*) string);
		return result;
	}

	MutableLet unsigned_integer_index_of(Let _let, Let _index) {
		MutableString string = string_from_unsigned_integer(_let.value.unsigned_integer_type);
		Let result = let_unsigned_integer((UnsignedInteger) strtoul(string, NULL, 10));
		free((void*) string);
		return result;
	}

	MutableLet long_index_of(Let _let, Let _index) {
		MutableString string = string_from_long(_let.value.long_type);
		Let result = let_long(strtol(string, NULL, 10));
		free((void*) string);
		return result;
	}

	MutableLet unsigned_long_index_of(Let _let, Let _index) {
		MutableString string = string_from_unsigned_long(_let.value.unsigned_long_type);
		Let result = let_unsigned_long(strtoul(string, NULL, 10));
		free((void*) string);
		return result;
	}

	MutableLet float_index_of(Let _let, Let _index) {
		MutableString string = string_from_float(_let.value.float_type);
		Let result = let_float(strtof(string, NULL));
		free((void*) string);
		return result;
	}

	MutableLet double_index_of(Let _let, Let _index) {
		MutableString string = string_from_double(_let.value.double_type);
		Let result = let_double(strtod(string, NULL));
		free((void*) string);
		return result;
	}

	MutableLet long_double_index_of(Let _let, Let _index) {
		MutableString string = string_from_long_double(_let.value.long_double_type);
		Let result = let_long_double(strtold(string, NULL));
		free((void*) string);
		return result;
	}

	MutableLet string_index_of(Let _let, Let _index) {
		return let_character(string_character_at(_let.value.string_type, as_long(_index)));
	}

	MutableLet subroutine_index_of(Let _let, Let _index) {
		return let_empty();
	}

	MutableLet function_index_of(Let _let, Let _index) {
		Let let_result = function_invoke(_let, let_empty());
		Let index_result = function_invoke(_index, let_empty());
		Let result = index_of(let_result, index_result);
		if(requires_free(index_result))
			unlet(index_result);
		if(requires_free(let_result))
			unlet(let_result);
		return result;
	}

	MutableLet array_index_of(Let _let, Let _index) {
		return let_copy(array_element_at(_let.value.array_type, as_long(_index)));
	}

	MutableLet object_index_of(Let _let, Let _index) {
		Let property_name = let_string("[]");
		Let property = member(_let, property_name);
		unlet(property_name);
		if(let_is_empty(property) || !is_invokable(property))
			return let_empty();
		return invoke(property, 2, &_let, &_index);
	}

#ifdef __cplusplus
}
#endif

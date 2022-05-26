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

#include "thicc_as_string.h"
#include "../core/thicc_interface.h"
#include "../core/thicc_struct_let.h"
#include "../utility/thicc_function.h"
#include "../utility/thicc_string.h"

	MutableString boolean_as_string(Let _let) {
		return _let.value.boolean_type ? "true" : "false";
	}

	MutableString character_as_string(Let _let) {
		return string_from_characters(1, _let.value.character_type);
	}
	
	MutableString signed_character_as_string(Let _let) {
		return string_from_signed_characters(1, _let.value.character_type);
	}

	MutableString unsigned_character_as_string(Let _let) {
		return string_from_unsigned_characters(1, _let.value.character_type);
	}

	MutableString short_as_string(Let _let) {
		return string_from_integer((Integer) _let.value.short_type);
	}

	MutableString unsigned_short_as_string(Let _let) {
		return string_from_unsigned_integer((UnsignedInteger) _let.value.short_type);
	}

	MutableString integer_as_string(Let _let) {
		return string_from_integer(_let.value.integer_type);
	}

	MutableString unsigned_integer_as_string(Let _let) {
		return string_from_unsigned_integer(_let.value.unsigned_integer_type);
	}

	MutableString long_as_string(Let _let) {
		return string_from_long(_let.value.long_type);
	}

	MutableString unsigned_long_as_string(Let _let) {
		return string_from_unsigned_long(_let.value.unsigned_long_type);
	}

	MutableString float_as_string(Let _let) {
		return string_from_float(_let.value.float_type);
	}

	MutableString double_as_string(Let _let) {
		return string_from_double(_let.value.double_type);
	}

	MutableString long_double_as_string(Let _let) {
		return string_from_long_double(_let.value.long_double_type);
	}

	MutableString string_as_string(Let _let) {
		return string_copy(string_view(_let));
	}

	MutableString subroutine_as_string(Let _let) {
		return string_empty();
	}

	MutableString function_as_string(Let _let) {
		Let temporary = function_invoke(_let, let_empty());
		MutableString result = as_string(temporary);
		if(requires_free(temporary))
			unlet(temporary);
		return result;
	}

	MutableString array_as_string(Let _let) {
		return as_string(*array_view(_let)); /*TODO: Make robust*/
	}

	MutableString object_as_string(Let _let) {
		return string_copy((String) object_view(_let)); /*TODO: Make robust*/
	}

#ifdef __cplusplus
}
#endif

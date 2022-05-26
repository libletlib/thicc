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

#include "thicc_as_long_double.h"
#include "../core/thicc_interface.h"
#include "../core/thicc_struct_let.h"
#include "../utility/thicc_character.h"
#include "../utility/thicc_function.h"

	MutableLongDouble boolean_as_long_double(Let _let) {
		return _let.value.boolean_type ? 1.0l : 0.0l;
	}

	MutableLongDouble character_as_long_double(Let _let) {
		return (LongDouble) (CharacterPromotedType) character_to_number(_let.value.character_type);
	}
	
	MutableLongDouble signed_character_as_long_double(Let _let) {
		return (LongDouble) (int) signed_character_to_number(_let.value.signed_character_type);
	}

	MutableLongDouble unsigned_character_as_long_double(Let _let) {
		return (LongDouble) (UnsignedCharacterPromotedType) unsigned_character_to_number(_let.value.unsigned_character_type);
	}

	MutableLongDouble short_as_long_double(Let _let) {
		return (LongDouble) _let.value.short_type;
	}

	MutableLongDouble unsigned_short_as_long_double(Let _let) {
		return (LongDouble) _let.value.unsigned_short_type;
	}

	MutableLongDouble integer_as_long_double(Let _let) {
		return (LongDouble) _let.value.integer_type;
	}

	MutableLongDouble unsigned_integer_as_long_double(Let _let) {
		return (LongDouble) _let.value.unsigned_integer_type;
	}

	MutableLongDouble long_as_long_double(Let _let) {
		return (LongDouble) _let.value.long_type;
	}

	MutableLongDouble unsigned_long_as_long_double(Let _let) {
		return (LongDouble) _let.value.unsigned_long_type;
	}

	MutableLongDouble float_as_long_double(Let _let) {
		return (LongDouble) _let.value.float_type;
	}

	MutableLongDouble double_as_long_double(Let _let) {
		return (LongDouble) _let.value.double_type;
	}

	MutableLongDouble long_double_as_long_double(Let _let) {
		return _let.value.long_double_type;
	}

	MutableLongDouble string_as_long_double(Let _let) {
		return (LongDouble) *string_view(_let);
	}

	MutableLongDouble subroutine_as_long_double(Let _let) {
		return 0.0l;
	}

	MutableLongDouble function_as_long_double(Let _let) {
		Let temporary = function_invoke(_let, let_empty());
		LongDouble result = as_long_double(temporary);
		if(requires_free(temporary))
			unlet(temporary);
		return result;
	}

	MutableLongDouble array_as_long_double(Let _let) {
		return as_long_double(*array_view(_let));
	}

	MutableLongDouble object_as_long_double(Let _let) {
		return *((LongDouble* THICC_RESTRICT) object_view(_let));
	}

#ifdef __cplusplus
}
#endif

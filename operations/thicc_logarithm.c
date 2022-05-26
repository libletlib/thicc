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

#include "thicc_logarithm.h"
#include "../core/thicc_interface.h"
#include "../core/thicc_struct_let.h"
#include "../utility/thicc_array.h"
#include "../utility/thicc_function.h"
#include "../utility/thicc_math_typedef.h"
#include "../utility/thicc_string.h"

	MutableLet boolean_logarithm(Let _let, Let _right) {
		return let_boolean(THICC_NO);
	}

	MutableLet character_logarithm(Let _left, Let _right) {
		return let_float(THICC_LOGARITHMF(as_float(_left), as_float(_right)));
	}
	
	MutableLet signed_character_logarithm(Let _left, Let _right) {
		return let_float(THICC_LOGARITHMF(as_float(_left), as_float(_right)));
	}

	MutableLet unsigned_character_logarithm(Let _left, Let _right) {
		return let_float(THICC_LOGARITHMF(as_float(_left), as_float(_right)));
	}
	
	MutableLet short_logarithm(Let _left, Let _right) {
		return let_float(THICC_LOGARITHMF(as_float(_left), as_float(_right)));
	}
	
	MutableLet unsigned_short_logarithm(Let _left, Let _right) {
		return let_float(THICC_LOGARITHMF(as_float(_left), as_float(_right)));
	}

	MutableLet integer_logarithm(Let _left, Let _right) {
		return let_double(THICC_LOGARITHMD(as_double(_left), as_double(_right)));
	}

	MutableLet unsigned_integer_logarithm(Let _left, Let _right) {
		return let_double(THICC_LOGARITHMD(as_double(_left), as_double(_right)));
	}

	MutableLet long_logarithm(Let _left, Let _right) {
		return let_long_double(THICC_LOGARITHML(as_long_double(_left), as_long_double(_right)));
	}

	MutableLet unsigned_long_logarithm(Let _left, Let _right) {
		return let_long_double(THICC_LOGARITHML(as_long_double(_left), as_long_double(_right)));
	}

	MutableLet float_logarithm(Let _left, Let _right) {
		return let_float(THICC_LOGARITHMF(_left.value.float_type, _right.value.float_type));
	}

	MutableLet double_logarithm(Let _left, Let _right) {
		return let_double(THICC_LOGARITHMD(_left.value.double_type, _right.value.double_type));
	}

	MutableLet long_double_logarithm(Let _left, Let _right) {
		return let_long_double(THICC_LOGARITHML(_left.value.long_double_type, _right.value.long_double_type));
	}

	MutableLet string_logarithm(Let _left, Let _right) {
		return let_empty();
	}

	MutableLet subroutine_logarithm(Let _left, Let _right) {
		return let_empty();
	}

	MutableLet function_logarithm(Let _left, Let _right) {
		Let left_result = function_invoke(_left, let_empty());
		Let right_result = function_invoke(_right, let_empty());
		Let result = logarithm(left_result, right_result);
		if(requires_free(right_result))
			unlet(right_result);
		if(requires_free(left_result))
			unlet(left_result);
		return result;
	}

	MutableLet array_logarithm(Let _left, Let _right) {
		return let_empty(); /*TODO: Implement.*/
	}

	MutableLet object_logarithm(Let _left, Let _right) {
		Let property_name = let_string("logarithm");
		Let property = member(_left, property_name);
		unlet(property_name);
		if(let_is_empty(property) || !is_invokable(property))
			return let_empty();
		return invoke(property, 2, &_left, &_right);
	}

#ifdef __cplusplus
}
#endif

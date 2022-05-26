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

#include "thicc_comparison.h"
#include "../core/thicc_interface.h"
#include "../core/thicc_struct_let.h"
#include "../utility/thicc_array.h"
#include "../utility/thicc_math.h"
#include "../utility/thicc_object.h"
#include "../utility/thicc_string.h"
#include <stdlib.h>
#include <stdio.h>

	MutableComparison boolean_comparison(Let _left, Let _right) {
		if(_left.value.boolean_type && !_right.value.boolean_type)
			THICC_LEFT_GREATER;
		if(!_left.value.boolean_type && _right.value.boolean_type)
			THICC_RIGHT_GREATER;
		return THICC_EQUAL;
	}

	MutableComparison character_comparison(Let _left, Let _right) {
		if(_left.value.character_type > _right.value.character_type)
			return THICC_LEFT_GREATER;
		if(_right.value.character_type > _left.value.character_type)
			return THICC_RIGHT_GREATER;
		return THICC_EQUAL;
	}
	
	MutableComparison signed_character_comparison(Let _left, Let _right) {
		if(_left.value.signed_character_type > _right.value.signed_character_type)
			return THICC_LEFT_GREATER;
		if(_right.value.signed_character_type > _left.value.signed_character_type)
			return THICC_RIGHT_GREATER;
		return THICC_EQUAL;
	}

	MutableComparison unsigned_character_comparison(Let _left, Let _right) {
		if(_left.value.unsigned_character_type > _right.value.unsigned_character_type)
			return THICC_LEFT_GREATER;
		if(_right.value.unsigned_character_type > _left.value.unsigned_character_type)
			return THICC_RIGHT_GREATER;
		return THICC_EQUAL;
	}
	
	MutableComparison short_comparison(Let _left, Let _right) {
		if(_left.value.short_type > _right.value.short_type)
			return THICC_LEFT_GREATER;
		if(_right.value.short_type > _left.value.short_type)
			return THICC_RIGHT_GREATER;
		return THICC_EQUAL;
	}
	
	MutableComparison unsigned_short_comparison(Let _left, Let _right) {
		if(_left.value.unsigned_short_type > _right.value.unsigned_short_type)
			return THICC_LEFT_GREATER;
		if(_right.value.unsigned_short_type > _left.value.unsigned_short_type)
			return THICC_RIGHT_GREATER;
		return THICC_EQUAL;
	}

	MutableComparison integer_comparison(Let _left, Let _right) {
		if(_left.value.integer_type > _right.value.integer_type)
			return THICC_LEFT_GREATER;
		if(_right.value.integer_type > _left.value.integer_type)
			return THICC_RIGHT_GREATER;
		return THICC_EQUAL;
	}

	MutableComparison unsigned_integer_comparison(Let _left, Let _right) {
		if(_left.value.unsigned_integer_type > _right.value.unsigned_integer_type)
			return THICC_LEFT_GREATER;
		if(_right.value.unsigned_integer_type > _left.value.unsigned_integer_type)
			return THICC_RIGHT_GREATER;
		return THICC_EQUAL;
	}

	MutableComparison long_comparison(Let _left, Let _right) {
		if(_left.value.long_type > _right.value.long_type)
			return THICC_LEFT_GREATER;
		if(_right.value.long_type > _left.value.long_type)
			return THICC_RIGHT_GREATER;
		return THICC_EQUAL;
	}

	MutableComparison unsigned_long_comparison(Let _left, Let _right) {
		if(_left.value.unsigned_long_type > _right.value.unsigned_long_type)
			return THICC_LEFT_GREATER;
		if(_right.value.unsigned_long_type > _left.value.unsigned_long_type)
			return THICC_RIGHT_GREATER;
		return THICC_EQUAL;
	}

	MutableComparison float_comparison(Let _left, Let _right) {
		if(math_float_equal(_left.value.float_type, _right.value.float_type))
			return THICC_EQUAL;
		if(_left.value.float_type > _right.value.float_type)
			return THICC_LEFT_GREATER;
		return THICC_RIGHT_GREATER;

	}

	MutableComparison double_comparison(Let _left, Let _right) {
		if(math_double_equal(_left.value.double_type, _right.value.double_type))
			return THICC_EQUAL;
		if(_left.value.double_type > _right.value.double_type)
			return THICC_LEFT_GREATER;
		return THICC_RIGHT_GREATER;
	}

	MutableComparison long_double_comparison(Let _left, Let _right) {
		if(math_long_double_equal(_left.value.long_double_type, _right.value.long_double_type))
			return THICC_EQUAL;
		if(_left.value.long_double_type > _right.value.long_double_type)
			return THICC_LEFT_GREATER;
		return THICC_RIGHT_GREATER;
	}

	MutableComparison string_comparison(Let _left, Let _right) {
		if(!is_string(_left)) {
			MutableString string = as_string(_left);
			MutableComparison result = string_compare(string, string_view(_right));
			free(string);
			return result;
		} else if(!is_string(_right)) {
			MutableString string = as_string(_right);
			MutableComparison result = string_compare(string_view(_left), string);
			free(string);
			return result;
		} else {
			return string_compare(string_view(_left), string_view(_right));
		}
	}

	MutableComparison subroutine_comparison(Let _left, Let _right) {
		if(_left.value.subroutine_type != _right.value.subroutine_type)
			return THICC_LEFT_GREATER;
		return THICC_EQUAL;
	}

	MutableComparison function_comparison(Let _left, Let _right) {
		if(_left.value.function_type != _right.value.function_type)
			return THICC_LEFT_GREATER;
		return THICC_EQUAL;
	}

	MutableComparison array_comparison(Let _left, Let _right) {
		return array_compare(array_view(_left), array_view(_right));
	}

	MutableComparison object_comparison(Let _left, Let _right) {
		Let property_name = let_string("comparison");
		Let property = member(_left, property_name);
#if THICC_IF(THICC_DEBUG)
		MutableLet result;
		unlet(property_name);
		if(let_is_empty(property) || !is_invokable(property))
			return object_compare(object_view(_left), object_view(_right));
		result = invoke(property, 2, &_left, &_right);
		if(requires_free(result))
			perror("Object comparison override returns a let that requires free, leaking memory.");
		return as_integer(result);
#else
	    unlet(property_name);
	    if(let_is_empty(property) || !is_invokable(property))
		    return object_compare(object_view(_left), object_view(_right));
	    return as_integer(invoke(property, 2, &_left, &_right););
#endif
	}

#ifdef __cplusplus
}
#endif

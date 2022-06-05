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

#include "thicc_interface.h"
#include "thicc_struct_let.h"
#include "thicc_struct_object.h"
#include "thicc_struct_behaviour.h"
#include "../utility/thicc_array.h"
#include "../utility/thicc_function.h"
#include "../utility/thicc_rank.h"
#include "../utility/thicc_comparison.h"
#include "../utility/thicc_object.h"
#include <stdarg.h>

#define select_operator(_left, _left_rank, _operator, _right, _right_rank) \
	(_left_rank) == (_right_rank) ?       \
		(_left).behaviour->_operator(_left, _right) : \
			(_left_rank) > (_right_rank) ?                      \
				(_left).behaviour->_operator(_left, cast(_right, _left_rank)) : \
					(_right).behaviour->_operator(cast(_left, _right_rank), _right)

	static MutableLet evaluate_let_value(Let _let) {
		if(rank(_let) == function_rank)
			return function_invoke(_let, let_array_no_copy(array_empty()));
		return _let;
	}

	MutableRank rank(Let _let) {
		if(let_is_empty(_let))
			return object_rank;
		return _let.behaviour->rank;
	}

	MutableLet array_of(Size _size, ...) {
		va_list list;
		MutableArray buffer;
		va_start(list, _size);
		buffer = array_from_list(_size, list);
		va_end(list);
		return let_array_no_copy(buffer);
	}

	MutableLet object_of(Size _size, ...) {
		va_list list;
		MutableObject object;
		va_start(list, _size);
		object = object_compose_list(_size, list);
		va_end(list);
		return let_object_no_copy(object);
	}

	MutableLet invoke(Let _let, Size _size, ...) {
		va_list list;
		MutableLet array;
		MutableLet result;
		if(_size == 0 || !rank_is_invokable(_let))
			return let_empty();
		va_start(list, _size);
		array = let_array_no_copy(array_from_list(_size, list));
		va_end(list);
		result = function_invoke(_let, array);
		unlet(array);
		return result;
	}

	MutableLet member(Let _object, Let _member) {
		MutableLet keys;
		MutableLet values;
		MutableSize size;
		MutableSize index = 0;
		MutableLet result = let_empty();

		if(object_is_empty(_object.value.object_type) || let_is_empty(_member))
			return result;

		keys = index_of(((Root) _object.value.object_type)->members, let_long(0l));
		values = index_of(((Root) _object.value.object_type)->members, let_long(1l));
		size = array_length(keys.value.array_type);

		for(; index < size; ++index) {
			Let key = index_of(keys, let_long((MutableLong) index));
			if(equal(key, _member)) {
				result = index_of(values, let_long((MutableLong)index));
				unlet(key);
				break;
			}
			unlet(key);
		}
		unlet(keys);
		unlet(values);
		return result;
	}

	MutableLet cast(Let _let, Rank _rank) {
		switch(_rank) {
			case boolean_rank:
				return let_boolean(as_boolean(_let));
			case character_rank:
				return let_character(as_character(_let));
			case signed_character_rank:
				return let_signed_character(as_signed_character(_let));
			case unsigned_character_rank:
				return let_unsigned_character(as_unsigned_character(_let));
			case short_rank:
				return let_short(as_short(_let));
			case unsigned_short_rank:
				return let_unsigned_short(as_unsigned_short(_let));
			case integer_rank:
				return let_integer(as_integer(_let));
			case unsigned_integer_rank:
				return let_unsigned_integer(as_unsigned_integer(_let));
			case long_rank:
				return let_long(as_long(_let));
			case unsigned_long_rank:
				return let_unsigned_long(as_unsigned_long(_let));
#if THICC_IF(THICC_C_AT_LEAST(1999))
			case long_long_rank:
				return let_long_long(as_long_long(_let));
			case unsigned_long_long_rank:
				return let_unsigned_long_long(as_unsigned_long_long(_let));
#endif
			case float_rank:
				return let_float(as_float(_let));
			case double_rank:
				return let_double(as_double(_let));
			case long_double_rank:
				return let_long_double(as_long_double(_let));
#if THICC_IF(THICC_HAS_COMPLEX)
			case float_complex_rank:
				return let_float_complex(as_float_complex(_let));
			case double_complex_rank:
				return let_double_complex(as_double_complex(_let));
			case long_double_complex_rank:
				return let_long_double_complex(as_long_double_complex(_let));
#endif
			case string_rank:
				return let_string_no_copy(as_string(_let));
			case subroutine_rank:
				return let_subroutine(as_subroutine(_let));
			case function_rank:
				return let_function(as_function(_let));
			case array_rank:
				return let_array_no_copy(as_array(_let));
			case object_rank:
				return let_object_no_copy(as_object(_let));
			default:
				return let_empty();
		}
	}

	MutableBoolean requires_free(Let _let) {
		switch(rank(_let)) {
			case string_rank:
			case array_rank:
			case object_rank:
				return THICC_YES;
			default:
				return THICC_NO;
		}
	}

	void unlet(Let _let) {
		_let.behaviour->deallocate(_let);
	}

	String string_view(Let _let) {
		return _let.value.string_type;
	}

	Array array_view(Let _let) {
		return _let.value.array_type;
	}

	Object object_view(Let _let) {
		return _let.value.object_type;
	}

	MutableBoolean as_boolean(Let _let) {
		return _let.behaviour->as_boolean(_let);
	}

	MutableCharacter as_character(Let _let) {
		return _let.behaviour->as_character(_let);
	}

	MutableSignedCharacter as_signed_character(Let _let) {
		return _let.behaviour->as_signed_character(_let);
	}

	MutableUnsignedCharacter as_unsigned_character(Let _let) {
		return _let.behaviour->as_unsigned_character(_let);
	}

	MutableShort as_short(Let _let) {
		return _let.behaviour->as_short(_let);
	}

	MutableUnsignedShort as_unsigned_short(Let _let) {
		return _let.behaviour->as_unsigned_short(_let);
	}

	MutableInteger as_integer(Let _let) {
		return _let.behaviour->as_integer(_let);
	}

	MutableUnsignedInteger as_unsigned_integer(Let _let) {
		return _let.behaviour->as_unsigned_integer(_let);
	}

	MutableLong as_long(Let _let) {
		return _let.behaviour->as_long(_let);
	}

	MutableUnsignedLong as_unsigned_long(Let _let) {
		return _let.behaviour->as_unsigned_long(_let);
	}

	MutableFloat as_float(Let _let) {
		return _let.behaviour->as_float(_let);
	}

	MutableDouble as_double(Let _let) {
		return _let.behaviour->as_double(_let);
	}

	MutableLongDouble as_long_double(Let _let) {
		return _let.behaviour->as_long_double(_let);
	}

	MutableString as_string(Let _let) {
		return _let.behaviour->as_string(_let);
	}

	MutableSubroutine as_subroutine(Let _let) {
		return _let.behaviour->as_subroutine(_let);
	}

	MutableFunction as_function(Let _let) {
		return _let.behaviour->as_function(_let);
	}

	MutableArray as_array(Let _let) {
		return _let.behaviour->as_array(_let);
	}

	MutableObject as_object(Let _let) {
		return _let.behaviour->as_object(_let);
	}

	MutableLet sum(Let _left, Let _right) {
		Let left = evaluate_let_value(_left);
		Let right = evaluate_let_value(_right);
		Rank left_rank = rank(left);
		Rank right_rank = rank(right);
		if(requires_free(left) && left_rank > right_rank && !requires_free(right)) {
			Let right_temporary = cast(right, left_rank);
			MutableLet result = select_operator(left, left_rank, sum, right_temporary, left_rank);
			unlet(right_temporary);
			return result;
		}
		if(!requires_free(left) && right_rank > left_rank && requires_free(right)) {
			Let left_temporary = cast(left, right_rank);
			MutableLet result = select_operator(left_temporary, right_rank, sum, right, right_rank);
			unlet(left_temporary);
			return result;
		}
		return select_operator(left, left_rank, sum, right, right_rank);
	}

	MutableLet difference(Let _left, Let _right) {
		Let left = evaluate_let_value(_left);
		Let right = evaluate_let_value(_right);
		Rank left_rank = rank(left);
		Rank right_rank = rank(right);
		if(requires_free(left) && left_rank > right_rank && !requires_free(right)) {
			Let right_temporary = cast(right, left_rank);
			MutableLet result = select_operator(left, left_rank, difference, right_temporary, left_rank);
			unlet(right_temporary);
			return result;
		}
		if(!requires_free(left) && right_rank > left_rank && requires_free(right)) {
			Let left_temporary = cast(left, right_rank);
			MutableLet result = select_operator(left_temporary, right_rank, difference, right, right_rank);
			unlet(left_temporary);
			return result;
		}
		return select_operator(left, left_rank, difference, right, right_rank);
	}

	MutableLet quotient(Let _left, Let _right) {
		Let left = evaluate_let_value(_left);
		Let right = evaluate_let_value(_right);
		Rank left_rank = rank(left);
		Rank right_rank = rank(right);
		if(requires_free(left) && left_rank > right_rank && !requires_free(right)) {
			Let right_temporary = cast(right, left_rank);
			MutableLet result = select_operator(left, left_rank, quotient, right_temporary, left_rank);
			unlet(right_temporary);
			return result;
		}
		if(!requires_free(left) && right_rank > left_rank && requires_free(right)) {
			Let left_temporary = cast(left, right_rank);
			MutableLet result = select_operator(left_temporary, right_rank, quotient, right, right_rank);
			unlet(left_temporary);
			return result;
		}
		return select_operator(left, left_rank, quotient, right, right_rank);
	}

	MutableLet modulo(Let _left, Let _right) {
		Let left = evaluate_let_value(_left);
		Let right = evaluate_let_value(_right);
		Rank left_rank = rank(left);
		Rank right_rank = rank(right);
		if(requires_free(left) && left_rank > right_rank && !requires_free(right)) {
			Let right_temporary = cast(right, left_rank);
			MutableLet result = select_operator(left, left_rank, modulo, right_temporary, left_rank);
			unlet(right_temporary);
			return result;
		}
		if(!requires_free(left) && right_rank > left_rank && requires_free(right)) {
			Let left_temporary = cast(left, right_rank);
			MutableLet result = select_operator(left_temporary, right_rank, modulo, right, right_rank);
			unlet(left_temporary);
			return result;
		}
		return select_operator(left, left_rank, modulo, right, right_rank);
	}

	MutableLet product(Let _left, Let _right) {
		Let left = evaluate_let_value(_left);
		Let right = evaluate_let_value(_right);
		Rank left_rank = rank(left);
		Rank right_rank = rank(right);
		if(requires_free(left) && left_rank > right_rank && !requires_free(right)) {
			Let right_temporary = cast(right, left_rank);
			MutableLet result = select_operator(left, left_rank, product, right_temporary, left_rank);
			unlet(right_temporary);
			return result;
		}
		if(!requires_free(left) && right_rank > left_rank && requires_free(right)) {
			Let left_temporary = cast(left, right_rank);
			MutableLet result = select_operator(left_temporary, right_rank, product, right, right_rank);
			unlet(left_temporary);
			return result;
		}
		return select_operator(left, left_rank, product, right, right_rank);
	}

	MutableLet power(Let _left, Let _right) {
		Let left = evaluate_let_value(_left);
		Let right = evaluate_let_value(_right);
		Rank left_rank = rank(left);
		Rank right_rank = rank(right);
		if(requires_free(left) && left_rank > right_rank && !requires_free(right)) {
			Let right_temporary = cast(right, left_rank);
			MutableLet result = select_operator(left, left_rank, power, right_temporary, left_rank);
			unlet(right_temporary);
			return result;
		}
		if(!requires_free(left) && right_rank > left_rank && requires_free(right)) {
			Let left_temporary = cast(left, right_rank);
			MutableLet result = select_operator(left_temporary, right_rank, power, right, right_rank);
			unlet(left_temporary);
			return result;
		}
		return select_operator(left, left_rank, power, right, right_rank);
	}

	MutableLet root(Let _left, Let _right) {
		Let left = evaluate_let_value(_left);
		Let right = evaluate_let_value(_right);
		Rank left_rank = rank(left);
		Rank right_rank = rank(right);
		if(requires_free(left) && left_rank > right_rank && !requires_free(right)) {
			Let right_temporary = cast(right, left_rank);
			MutableLet result = select_operator(left, left_rank, root, right_temporary, left_rank);
			unlet(right_temporary);
			return result;
		}
		if(!requires_free(left) && right_rank > left_rank && requires_free(right)) {
			Let left_temporary = cast(left, right_rank);
			MutableLet result = select_operator(left_temporary, right_rank, root, right, right_rank);
			unlet(left_temporary);
			return result;
		}
		return select_operator(left, left_rank, root, right, right_rank);
	}

	MutableLet logarithm(Let _left, Let _right) {
		Let left = evaluate_let_value(_left);
		Let right = evaluate_let_value(_right);
		Rank left_rank = rank(left);
		Rank right_rank = rank(right);
		if(requires_free(left) && left_rank > right_rank && !requires_free(right)) {
			Let right_temporary = cast(right, left_rank);
			MutableLet result = select_operator(left, left_rank, logarithm, right_temporary, left_rank);
			unlet(right_temporary);
			return result;
		}
		if(!requires_free(left) && right_rank > left_rank && requires_free(right)) {
			Let left_temporary = cast(left, right_rank);
			MutableLet result = select_operator(left_temporary, right_rank, logarithm, right, right_rank);
			unlet(left_temporary);
			return result;
		}
		return select_operator(left, left_rank, logarithm, right, right_rank);
	}

	MutableLet bit_and(Let _left, Let _right) {
		Let left = evaluate_let_value(_left);
		Let right = evaluate_let_value(_right);
		Rank left_rank = rank(left);
		Rank right_rank = rank(right);
		if(requires_free(left) && left_rank > right_rank && !requires_free(right)) {
			Let right_temporary = cast(right, left_rank);
			MutableLet result = select_operator(left, left_rank, bit_and, right_temporary, left_rank);
			unlet(right_temporary);
			return result;
		}
		if(!requires_free(left) && right_rank > left_rank && requires_free(right)) {
			Let left_temporary = cast(left, right_rank);
			MutableLet result = select_operator(left_temporary, right_rank, bit_and, right, right_rank);
			unlet(left_temporary);
			return result;
		}
		return select_operator(left, left_rank, bit_and, right, right_rank);
	}

	MutableLet bit_or(Let _left, Let _right)  {
		Let left = evaluate_let_value(_left);
		Let right = evaluate_let_value(_right);
		Rank left_rank = rank(left);
		Rank right_rank = rank(right);
		if(requires_free(left) && left_rank > right_rank && !requires_free(right)) {
			Let right_temporary = cast(right, left_rank);
			MutableLet result = select_operator(left, left_rank, bit_or, right_temporary, left_rank);
			unlet(right_temporary);
			return result;
		}
		if(!requires_free(left) && right_rank > left_rank && requires_free(right)) {
			Let left_temporary = cast(left, right_rank);
			MutableLet result = select_operator(left_temporary, right_rank, bit_or, right, right_rank);
			unlet(left_temporary);
			return result;
		}
		return select_operator(left, left_rank, bit_or, right, right_rank);
	}

	MutableLet bit_xor(Let _left, Let _right) {
		Let left = evaluate_let_value(_left);
		Let right = evaluate_let_value(_right);
		Rank left_rank = rank(left);
		Rank right_rank = rank(right);
		if(requires_free(left) && left_rank > right_rank && !requires_free(right)) {
			Let right_temporary = cast(right, left_rank);
			MutableLet result = select_operator(left, left_rank, bit_xor, right_temporary, left_rank);
			unlet(right_temporary);
			return result;
		}
		if(!requires_free(left) && right_rank > left_rank && requires_free(right)) {
			Let left_temporary = cast(left, right_rank);
			MutableLet result = select_operator(left_temporary, right_rank, bit_xor, right, right_rank);
			unlet(left_temporary);
			return result;
		}
		return select_operator(left, left_rank, bit_xor, right, right_rank);
	}

	MutableLet index_of(Let _indexable, Let _index) {
		Let left = evaluate_let_value(_indexable);
		Let right = evaluate_let_value(_index);
		Rank right_rank = rank(right);
		if(right_rank != long_rank) {
			Let right_temporary = cast(right, long_rank);
			return left.behaviour->index_of(left, right_temporary);
		}
		return left.behaviour->index_of(left, right);
	}

	MutableLet bit_not(Let _let) {
		return _let.behaviour->bit_not(_let);
	}

	MutableLet bit_complement(Let _let) {
		return _let.behaviour->bit_complement(_let);
	}

	MutableLet indirection(Let _let) {
		return _let.behaviour->indirection(_let);
	}

	MutableLet positive(Let _let) {
		return _let.behaviour->positive(_let);
	}

	MutableLet negative(Let _let) {
		return _let.behaviour->negative(_let);
	}

	MutableComparison compare(Let _left, Let _right) {
		Let left = evaluate_let_value(_left);
		Let right = evaluate_let_value(_right);
		Rank left_rank = rank(left);
		Rank right_rank = rank(right);
		if(let_is_empty(_left) && let_is_empty(_right))
			return THICC_EQUAL;
		if(requires_free(left) && left_rank > right_rank && !requires_free(right)) {
			Let right_temporary = cast(right, left_rank);
			MutableComparison result = select_operator(left, left_rank, comparison, right_temporary, left_rank);
			unlet(right_temporary);
			return result;
		}
		if(!requires_free(left) && right_rank > left_rank && requires_free(right)) {
			Let left_temporary = cast(left, right_rank);
			MutableComparison result = select_operator(left_temporary, right_rank, comparison, right, right_rank);
			unlet(left_temporary);
			return result;
		}
		return select_operator(left, left_rank, comparison, right, right_rank);
	}

	MutableBoolean equal(Let _left, Let _right) {
		return comparison_equal(compare(_left, _right));
	}

	MutableBoolean greater_than(Let _left, Let _right) {
		return comparison_left_greater(compare(_left, _right));
	}

	MutableBoolean less_than(Let _left, Let _right) {
		return comparison_right_greater(compare(_left, _right));
	}

	MutableBoolean not_equal(Let _left, Let _right) {
		if(equal(_left, _right))
			return THICC_NO;
		return THICC_YES;
	}

	MutableBoolean is_character(Let _let) {
		if(rank(_let) <= unsigned_character_rank)
			return THICC_YES;
		return THICC_NO;
	}

	MutableBoolean is_signed(Let _let) {
		if(rank_is_unsigned(_let))
			return THICC_NO;
		return THICC_YES;
	}

	MutableBoolean is_unsigned(Let _let) {
		Rank this_rank = rank(_let);
#if THICC_IF(THICC_CHAR_SIGNED)
		if(this_rank <= float_rank && this_rank % 2 == 0)
			return THICC_YES;
#else
	    if(this_rank > character_rank && this_rank <= float_rank && this_rank % 2 == 0)
		    return THICC_YES;
#endif
		if(this_rank == double_rank || this_rank == long_double_rank)
			return THICC_YES;
		return THICC_NO;
	}

	MutableBoolean is_numeric(Let _let) {
		Rank this_rank = rank(_let);
		if(this_rank >= short_rank && this_rank <= long_double_rank)
			return THICC_YES;
		return THICC_NO;
	}

	MutableBoolean is_string(Let _let) {
		if(rank(_let) == string_rank)
			return THICC_YES;
		return THICC_NO;
	}

	MutableBoolean is_array(Let _let) {
		if(rank(_let) == array_rank)
			return THICC_YES;
		return THICC_NO;
	}

	MutableBoolean is_object(Let _let) {
		if(rank(_let) == object_rank)
			return THICC_YES;
		return THICC_NO;
	}

	MutableBoolean is_invokable(Let _let) {
		switch(rank(_let)) {
			case subroutine_rank:
			case function_rank:
				return THICC_YES;
			default:
				return THICC_NO;
		}
	}

#ifdef __cplusplus
}
#endif

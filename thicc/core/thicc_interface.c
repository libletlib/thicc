/*
 *   ___       ___       ___       ___       ___
 *  /\  \     /\__\     /\  \     /\  \     /\  \
 *  \:\  \   /:/__/_   _\:\  \   /::\  \   /::\  \
 *  /::\__\ /::\/\__\ /\/::\__\ /:/\:\__\ /:/\:\__\
 * /:/\/__/ \/\::/  / \::/\/__/ \:\ \/__/ \:\ \/__/
 * \/__/      /:/  /   \:\__\    \:\__\    \:\__\
 *            \/__/     \/__/     \/__/     \/__/
 *
 * Copyright 2022 Ville Rissanen
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1.   Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *
 * 2.   Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifdef __cplusplus
extern "C" {
#endif

#include "thicc_interface.h"
#include "../utility/thicc_array.h"
#include "../utility/thicc_comparison.h"
#include "../utility/thicc_function.h"
#include "../utility/thicc_object.h"
#include "../utility/thicc_rank.h"
#include "../utility/thicc_string.h"
#include "thicc_struct_array.h"
#include "thicc_struct_behaviour.h"
#include "thicc_struct_object.h"
#include "thicc_struct_var.h"
#include <stdarg.h>

#define select_operator(_left, _left_rank, _operator, _right, _right_rank)                       \
  (_left_rank) == (_right_rank)	 ? (_left).behaviour->_operator(_left, _right)                   \
  : (_left_rank) > (_right_rank) ? (_left).behaviour->_operator(_left, cast(_right, _left_rank)) \
								 : (_right).behaviour->_operator(cast(_left, _right_rank), _right)

THICC_NODISCARD static Var evaluate_let_value(Let _let) {
  if (rank(_let) == function_rank)
	return function_invoke(_let, move_array(array_empty()));
  return _let;
}

THICC_NODISCARD MutableRank rank(Let _let) {
  if (let_is_empty(_let))
	return object_rank;
  return _let.behaviour->rank;
}

THICC_NODISCARD Var array_of(Size _size, ...) {
  va_list	   list;
  MutableArray buffer;
  va_start(list, _size);
  buffer = array_from_list(_size, list);
  va_end(list);
  return move_array(buffer);
}

THICC_NODISCARD Var object_of(Size _size, ...) {
  va_list		list;
  MutableObject object;
  va_start(list, _size);
  object = object_compose_list(_size, list);
  va_end(list);
  return move_object(object);
}

THICC_NODISCARD Var call(Let _invokable) {
  Let array	 = array_of(0);
  Let result = function_invoke(_invokable, array);
  unlet(array);
  return result;
}

THICC_NODISCARD Var invoke(Let _invokable, Size _size, ...) {
  va_list list;
  Var	  array, result;
  if (_size == 0 || !rank_is_invokable(_invokable))
	return let_empty();
  va_start(list, _size);
  array = move_array(array_from_list(_size, list));
  va_end(list);
  result = function_invoke(_invokable, array);
  unlet(array);
  return result;
}

THICC_NODISCARD Var invoke_from_list(Let _invokable, Size _size, va_list _list) {
  Var array, result;
  if (_size == 0 || !rank_is_invokable(_invokable))
	return let_empty();
  array	 = move_array(array_from_list(_size, _list));
  result = function_invoke(_invokable, array);
  unlet(array);
  return result;
}

THICC_NODISCARD Var member(Let _object, Let _member) {
  Var		  keys, values;
  MutableSize size, index = 0;
  Var		  result = let_empty();

  if (object_is_empty(object_view(_object)) || let_is_empty(_member))
	return result;

  keys	 = let_array(root_keys(_object));
  values = let_array(root_values(_object));
  size	 = length(keys);

  for (; index < size; ++index) {
	Let key = index_of(keys, let_natural(index));
	if (equal(key, _member)) {
	  result = index_of(values, let_natural(index));
	  unlet(key);
	  break;
	}
	unlet(key);
  }

  unlet(keys);
  unlet(values);

  return result;
}

THICC_NODISCARD Var cast(Let _let, Rank _rank) {
  switch (_rank) {
	case boolean_rank:
	  return let_boolean(as_boolean(_let));
	case character_rank:
	  return let_character(as_character(_let));
	case natural_rank:
	  return let_natural(as_natural(_let));
	case integer_rank:
	  return let_integer(as_integer(_let));
	case real_rank:
	  return let_real(as_real(_let));
	case complex_rank:
	  return let_complex(as_complex(_let));
	case string_rank:
	  return move_string(as_string(_let));
	case function_rank:
	  return let_function(as_function(_let));
	case array_rank:
	  return move_array(as_array(_let));
	case object_rank:
	  return move_object(as_object(_let));
	default:
	  return let_empty();
  }
}

THICC_NODISCARD MutableBoolean requires_free(Let _let) {
  if (let_is_empty(_let))
	return THICC_NO;

  switch (rank(_let)) {
	case string_rank:
	case array_rank:
	case object_rank:
	  return THICC_YES;
	default:
	  return THICC_NO;
  }
}

void unlet(Let _let) {
  if (!let_is_empty(_let))
	_let.behaviour->deallocate(_let);
}

void unlet_if_required(Let _let) {
  if (requires_free(_let))
	unlet(_let);
}

THICC_NODISCARD Character* string_view(Let _let) {
  return _let.value.string_type.string;
}

THICC_NODISCARD Var* array_view(Let _let) {
  return _let.value.array_type.array;
}

THICC_NODISCARD Object object_view(Let _let) {
  return _let.value.object_type;
}

THICC_NODISCARD MutableBoolean as_boolean(Let _let) {
  return _let.behaviour->as_boolean(_let);
}

THICC_NODISCARD MutableCharacter as_character(Let _let) {
  return _let.behaviour->as_character(_let);
}

THICC_NODISCARD MutableNatural as_natural(Let _let) {
  return _let.behaviour->as_natural(_let);
}

THICC_NODISCARD MutableInteger as_integer(Let _let) {
  return _let.behaviour->as_integer(_let);
}

THICC_NODISCARD MutableReal as_real(Let _let) {
  return _let.behaviour->as_real(_let);
}

THICC_NODISCARD MutableComplex as_complex(Let _let) {
  return _let.behaviour->as_complex(_let);
}

THICC_NODISCARD MutableString as_string(Let _let) {
  return _let.behaviour->as_string(_let);
}

THICC_NODISCARD MutableFunction as_function(Let _let) {
  return _let.behaviour->as_function(_let);
}

THICC_NODISCARD MutableArray as_array(Let _let) {
  return _let.behaviour->as_array(_let);
}

THICC_NODISCARD MutableObject as_object(Let _let) {
  return _let.behaviour->as_object(_let);
}

THICC_NODISCARD Var sum(Let _left, Let _right) {
  Let  left		  = evaluate_let_value(_left);
  Let  right	  = evaluate_let_value(_right);
  Rank left_rank  = rank(left);
  Rank right_rank = rank(right);
  if (requires_free(left) && left_rank > right_rank && !requires_free(right)) {
	Let right_temporary = cast(right, left_rank);
	Var result			= select_operator(left, left_rank, sum, right_temporary, left_rank);
	unlet(right_temporary);
	return result;
  }
  if (!requires_free(left) && right_rank > left_rank && requires_free(right)) {
	Let left_temporary = cast(left, right_rank);
	Var result		   = select_operator(left_temporary, right_rank, sum, right, right_rank);
	unlet(left_temporary);
	return result;
  }
  return select_operator(left, left_rank, sum, right, right_rank);
}

THICC_NODISCARD Var difference(Let _left, Let _right) {
  Let  left		  = evaluate_let_value(_left);
  Let  right	  = evaluate_let_value(_right);
  Rank left_rank  = rank(left);
  Rank right_rank = rank(right);
  if (requires_free(left) && left_rank > right_rank && !requires_free(right)) {
	Let right_temporary = cast(right, left_rank);
	Var result			= select_operator(left, left_rank, difference, right_temporary, left_rank);
	unlet(right_temporary);
	return result;
  }
  if (!requires_free(left) && right_rank > left_rank && requires_free(right)) {
	Let left_temporary = cast(left, right_rank);
	Var result		   = select_operator(left_temporary, right_rank, difference, right, right_rank);
	unlet(left_temporary);
	return result;
  }
  return select_operator(left, left_rank, difference, right, right_rank);
}

THICC_NODISCARD Var quotient(Let _left, Let _right) {
  Let  left		  = evaluate_let_value(_left);
  Let  right	  = evaluate_let_value(_right);
  Rank left_rank  = rank(left);
  Rank right_rank = rank(right);
  if (requires_free(left) && left_rank > right_rank && !requires_free(right)) {
	Let right_temporary = cast(right, left_rank);
	Var result			= select_operator(left, left_rank, quotient, right_temporary, left_rank);
	unlet(right_temporary);
	return result;
  }
  if (!requires_free(left) && right_rank > left_rank && requires_free(right)) {
	Let left_temporary = cast(left, right_rank);
	Var result		   = select_operator(left_temporary, right_rank, quotient, right, right_rank);
	unlet(left_temporary);
	return result;
  }
  return select_operator(left, left_rank, quotient, right, right_rank);
}

THICC_NODISCARD Var modulo(Let _left, Let _right) {
  Let  left		  = evaluate_let_value(_left);
  Let  right	  = evaluate_let_value(_right);
  Rank left_rank  = rank(left);
  Rank right_rank = rank(right);
  if (requires_free(left) && left_rank > right_rank && !requires_free(right)) {
	Let right_temporary = cast(right, left_rank);
	Var result			= select_operator(left, left_rank, modulo, right_temporary, left_rank);
	unlet(right_temporary);
	return result;
  }
  if (!requires_free(left) && right_rank > left_rank && requires_free(right)) {
	Let left_temporary = cast(left, right_rank);
	Var result		   = select_operator(left_temporary, right_rank, modulo, right, right_rank);
	unlet(left_temporary);
	return result;
  }
  return select_operator(left, left_rank, modulo, right, right_rank);
}

THICC_NODISCARD Var product(Let _left, Let _right) {
  Let  left		  = evaluate_let_value(_left);
  Let  right	  = evaluate_let_value(_right);
  Rank left_rank  = rank(left);
  Rank right_rank = rank(right);
  if (requires_free(left) && left_rank > right_rank && !requires_free(right)) {
	Let right_temporary = cast(right, left_rank);
	Var result			= select_operator(left, left_rank, product, right_temporary, left_rank);
	unlet(right_temporary);
	return result;
  }
  if (!requires_free(left) && right_rank > left_rank && requires_free(right)) {
	Let left_temporary = cast(left, right_rank);
	Var result		   = select_operator(left_temporary, right_rank, product, right, right_rank);
	unlet(left_temporary);
	return result;
  }
  return select_operator(left, left_rank, product, right, right_rank);
}

THICC_NODISCARD Var bit_and(Let _left, Let _right) {
  Let  left		  = evaluate_let_value(_left);
  Let  right	  = evaluate_let_value(_right);
  Rank left_rank  = rank(left);
  Rank right_rank = rank(right);
  if (requires_free(left) && left_rank > right_rank && !requires_free(right)) {
	Let right_temporary = cast(right, left_rank);
	Var result			= select_operator(left, left_rank, bit_and, right_temporary, left_rank);
	unlet(right_temporary);
	return result;
  }
  if (!requires_free(left) && right_rank > left_rank && requires_free(right)) {
	Let left_temporary = cast(left, right_rank);
	Var result		   = select_operator(left_temporary, right_rank, bit_and, right, right_rank);
	unlet(left_temporary);
	return result;
  }
  return select_operator(left, left_rank, bit_and, right, right_rank);
}

THICC_NODISCARD Var bit_or(Let _left, Let _right) {
  Let  left		  = evaluate_let_value(_left);
  Let  right	  = evaluate_let_value(_right);
  Rank left_rank  = rank(left);
  Rank right_rank = rank(right);
  if (requires_free(left) && left_rank > right_rank && !requires_free(right)) {
	Let right_temporary = cast(right, left_rank);
	Var result			= select_operator(left, left_rank, bit_or, right_temporary, left_rank);
	unlet(right_temporary);
	return result;
  }
  if (!requires_free(left) && right_rank > left_rank && requires_free(right)) {
	Let left_temporary = cast(left, right_rank);
	Var result		   = select_operator(left_temporary, right_rank, bit_or, right, right_rank);
	unlet(left_temporary);
	return result;
  }
  return select_operator(left, left_rank, bit_or, right, right_rank);
}

THICC_NODISCARD Var bit_xor(Let _left, Let _right) {
  Let  left		  = evaluate_let_value(_left);
  Let  right	  = evaluate_let_value(_right);
  Rank left_rank  = rank(left);
  Rank right_rank = rank(right);
  if (requires_free(left) && left_rank > right_rank && !requires_free(right)) {
	Let right_temporary = cast(right, left_rank);
	Var result			= select_operator(left, left_rank, bit_xor, right_temporary, left_rank);
	unlet(right_temporary);
	return result;
  }
  if (!requires_free(left) && right_rank > left_rank && requires_free(right)) {
	Let left_temporary = cast(left, right_rank);
	Var result		   = select_operator(left_temporary, right_rank, bit_xor, right, right_rank);
	unlet(left_temporary);
	return result;
  }
  return select_operator(left, left_rank, bit_xor, right, right_rank);
}

THICC_NODISCARD Var index_of(Let _indexable, Let _index) {
  Let  left		  = evaluate_let_value(_indexable);
  Let  right	  = evaluate_let_value(_index);
  Rank right_rank = rank(right);
  if (right_rank < natural_rank || right_rank > complex_rank) {
	Let right_temporary = cast(right, integer_rank);
	return left.behaviour->index_of(left, right_temporary);
  }
  return left.behaviour->index_of(left, right);
}

THICC_NODISCARD Var bit_not(Let _let) {
  return _let.behaviour->bit_not(_let);
}

THICC_NODISCARD Var bit_complement(Let _let) {
  return _let.behaviour->bit_complement(_let);
}

THICC_NODISCARD Var indirection(Let _let) {
  return _let.behaviour->indirection(_let);
}

THICC_NODISCARD Var positive(Let _let) {
  return _let.behaviour->positive(_let);
}

THICC_NODISCARD Var negative(Let _let) {
  return _let.behaviour->negative(_let);
}

THICC_NODISCARD MutableComparison compare(Let _left, Let _right) {
  Let  left		  = evaluate_let_value(_left);
  Let  right	  = evaluate_let_value(_right);
  Rank left_rank  = rank(left);
  Rank right_rank = rank(right);
  if (let_is_empty(left) && let_is_empty(right))
	return THICC_EQUAL;
  if (requires_free(left) && left_rank > right_rank && !requires_free(right)) {
	Let				  right_temporary = cast(right, left_rank);
	MutableComparison result		  = select_operator(left, left_rank, comparison, right_temporary, left_rank);
	unlet(right_temporary);
	return result;
  }
  if (!requires_free(left) && right_rank > left_rank && requires_free(right)) {
	Let				  left_temporary = cast(left, right_rank);
	MutableComparison result		 = select_operator(left_temporary, right_rank, comparison, right, right_rank);
	unlet(left_temporary);
	return result;
  }
  return select_operator(left, left_rank, comparison, right, right_rank);
}

THICC_NODISCARD MutableBoolean equal(Let _left, Let _right) {
  return comparison_equal(compare(_left, _right));
}

THICC_NODISCARD MutableBoolean greater_than(Let _left, Let _right) {
  return comparison_left_greater(compare(_left, _right));
}

THICC_NODISCARD MutableBoolean less_than(Let _left, Let _right) {
  return comparison_right_greater(compare(_left, _right));
}

THICC_NODISCARD MutableBoolean not_equal(Let _left, Let _right) {
  if (equal(_left, _right))
	return THICC_NO;
  return THICC_YES;
}

THICC_NODISCARD MutableSize length(Let _let) {
  switch (rank(_let)) {
	case complex_rank:
	  return 2;
	case string_rank:
	  return string_length(_let.value.string_type);
	case array_rank:
	  return _let.value.array_type.length;
	case object_rank:
	  return object_size(object_view(_let));
	default:
	  return 1;
  }
}

THICC_NODISCARD MutableBoolean is_character(Let _let) {
  return rank_is_character(_let);
}

THICC_NODISCARD MutableBoolean is_signed(Let _let) {
  return rank_is_signed(_let);
}

THICC_NODISCARD MutableBoolean is_unsigned(Let _let) {
  return rank_is_unsigned(_let);
}

THICC_NODISCARD MutableBoolean is_numeric(Let _let) {
  return rank_is_numeric(_let);
}

THICC_NODISCARD MutableBoolean is_integral(Let _let) {
  return rank_is_integral(_let);
}

THICC_NODISCARD MutableBoolean is_floating_point(Let _let) {
  return rank_is_floating_point(_let);
}

THICC_NODISCARD MutableBoolean is_indexable(Let _let) {
  return rank_is_indexable(_let);
}

THICC_NODISCARD MutableBoolean is_string(Let _let) {
  return rank_is_string(_let);
}

THICC_NODISCARD MutableBoolean is_array(Let _let) {
  return rank_is_array(_let);
}

THICC_NODISCARD MutableBoolean is_object(Let _let) {
  return rank_is_invokable(_let);
}

THICC_NODISCARD MutableBoolean is_invokable(Let _let) {
  return rank_is_invokable(_let);
}

#ifdef __cplusplus
}
#endif

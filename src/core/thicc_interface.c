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
 * docs and/or other materials provided with the distribution.
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

#include <thicc_interface.h>
#include "thicc_memory.h"
#include "../utility/thicc_array.h"
#include "../utility/thicc_comparison.h"
#include "../utility/thicc_function.h"
#include "../utility/thicc_object.h"
#include "../utility/thicc_rank.h"
#include "thicc_struct_object.h"

#define select_operator(_left, _left_rank, _operator, _right, _right_rank)                        \
  (_left_rank) == (_right_rank)	 ? (_left)->behaviour->_operator(_left, _right)                   \
  : (_left_rank) > (_right_rank) ? (_left)->behaviour->_operator(_left, cast(_right, _left_rank)) \
								 : (_right)->behaviour->_operator(cast(_left, _right_rank), _right)

THICC_NODISCARD MutableRank rank(Let* _let) {
  if (let_is_empty(_let))
	return object_rank;
  return _let->behaviour->rank;
}

THICC_NODISCARD Let* array_of(Size _size, ...) {
  va_list	   list;
  MutableArray buffer;
  va_start(list, _size);
  buffer = array_from_list(_size, list);
  va_end(list);
  return move_array(buffer);
}

Let* array_from_booleans(Size _size, Boolean* _array) {
    MutableArray result = array_allocate(_size);
	MutableSize index = 0;
	result.length = _size;
	for(; index < _size; ++index)
		result.array[index] = let_boolean(_array[index]);
	return move_array(result);
}

Let* array_from_characters(Size _size, Character* _array) {
	MutableArray result = array_allocate(_size);
	MutableSize index = 0;
	result.length = _size;
	for(; index < _size; ++index)
		result.array[index] = let_character(_array[index]);
	return move_array(result);
}

Let* array_from_integers(Size _size, Integer* _array) {
	MutableArray result = array_allocate(_size);
	MutableSize index = 0;
	result.length = _size;
	for(; index < _size; ++index)
		result.array[index] = let_integer(_array[index]);
	return move_array(result);
}

Let* array_from_reals(Size _size, Real* _array) {
	MutableArray result = array_allocate(_size);
	MutableSize index = 0;
	result.length = _size;
	for(; index < _size; ++index)
		result.array[index] = let_real(_array[index]);
	return move_array(result);
}

Let* array_from_complex(Size _size, Complex* _array) {
	MutableArray result = array_allocate(_size);
	MutableSize index = 0;
	result.length = _size;
	for(; index < _size; ++index)
		result.array[index] = let_complex(_array[index]);
	return move_array(result);
}

Let* array_from_strings(Size _size, MutableCharacter** _array) {
	MutableArray result = array_allocate(_size);
	MutableSize index = 0;
	result.length = _size;
	for(; index < _size; ++index)
		result.array[index] = let_string(_array[index]);
	return move_array(result);
}

THICC_NODISCARD Let* object_of(Size _size, ...) {
  va_list		list;
  MutableObject object;
  va_start(list, _size);
  object = object_compose_list(_size, list);
  va_end(list);
  return move_object(object);
}

THICC_NODISCARD Let* call(Let* _invokable) {
  Let* array	 = array_of(0);
  Let* result = function_invoke(_invokable, array);
  unlet(array);
  return result;
}

THICC_NODISCARD Let* invoke(Let* _invokable, Size _size, ...) {
  va_list list;
  Let*	  array;
  Let*    result;

  if (_size == 0 || !rank_is_invokable(_invokable))
	return let_empty();

  va_start(list, _size);
  array = move_array(array_from_list(_size, list));
  va_end(list);
  result = function_invoke(_invokable, array);
  unlet(array);
  return result;
}

THICC_NODISCARD Let* invoke_from_list(Let* _invokable, Size _size, va_list _list) {
  Let* array;
  Let* result;
  if (_size == 0 || !rank_is_invokable(_invokable))
	return let_empty();
  array	 = move_array(array_from_list(_size, _list));
  result = function_invoke(_invokable, array);
  unlet(array);
  return result;
}

THICC_NODISCARD Let* member(Let* _object, Let* _member) {
  MutableArray  keys;
  MutableArray  values;
  MutableSize   index = 0;

  if (object_is_empty(object_view(_object)) || let_is_empty(_member))
	return let_empty();

  keys	 = root_keys(_object);
  values = root_values(_object);

  for (; index < keys.length; ++index)
	if (equal(keys.array[index], _member))
	  return let_copy(values.array[index]);

  return let_empty();
}


THICC_NODISCARD Let* cast(Let* _let, Rank _rank) {
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

void unlet(Let* _let) {
  if (!let_is_empty(_let))
	_let->behaviour->deallocate(_let);
}

THICC_NODISCARD Character* string_view(Let* _let) {
  return _let->value.string_type.string;
}

THICC_NODISCARD Let* const* array_view(Let* _let) {
  return _let->value.array_type.array;
}

THICC_NODISCARD Object object_view(Let* _let) {
  return _let->value.object_type;
}

THICC_NODISCARD MutableBoolean as_boolean(Let* _let) {
  return _let->behaviour->as_boolean(_let);
}

THICC_NODISCARD MutableCharacter as_character(Let* _let) {
  return _let->behaviour->as_character(_let);
}

THICC_NODISCARD MutableNatural as_natural(Let* _let) {
  return _let->behaviour->as_natural(_let);
}

THICC_NODISCARD MutableInteger as_integer(Let* _let) {
  return _let->behaviour->as_integer(_let);
}

THICC_NODISCARD MutableReal as_real(Let* _let) {
  return _let->behaviour->as_real(_let);
}

THICC_NODISCARD MutableComplex as_complex(Let* _let) {
  return _let->behaviour->as_complex(_let);
}

THICC_NODISCARD MutableString as_string(Let* _let) {
  return _let->behaviour->as_string(_let);
}

THICC_NODISCARD MutableFunction as_function(Let* _let) {
  return _let->behaviour->as_function(_let);
}

THICC_NODISCARD MutableArray as_array(Let* _let) {
  return _let->behaviour->as_array(_let);
}

THICC_NODISCARD MutableObject as_object(Let* _let) {
  return _let->behaviour->as_object(_let);
}


THICC_NODISCARD Let* sum(Let* _left, Let* _right) {
  Rank left_rank  = rank(_left);
  Rank right_rank = rank(_right);
  if (left_rank > right_rank) {
	Let* right_temporary = cast(_right, left_rank);
	Let* result			= select_operator(_left, left_rank, sum, right_temporary, left_rank);
	unlet(right_temporary);
	return result;
  }
  if (right_rank > left_rank) {
	Let* left_temporary = cast(_left, right_rank);
	Let* result		   = select_operator(left_temporary, right_rank, sum, _right, right_rank);
	unlet(left_temporary);
	return result;
  }
  return select_operator(_left, left_rank, sum, _right, right_rank);
}

THICC_NODISCARD Let* difference(Let* _left, Let* _right) {
  Rank left_rank  = rank(_left);
  Rank right_rank = rank(_right);
  if (left_rank > right_rank) {
	Let* right_temporary = cast(_right, left_rank);
	Let* result			= select_operator(_left, left_rank, difference, right_temporary, left_rank);
	unlet(right_temporary);
	return result;
  }
  if (right_rank > left_rank) {
	Let* left_temporary = cast(_left, right_rank);
	Let* result		   = select_operator(left_temporary, right_rank, difference, _right, right_rank);
	unlet(left_temporary);
	return result;
  }
  return select_operator(_left, left_rank, difference, _right, right_rank);
}

THICC_NODISCARD Let* quotient(Let* _left, Let* _right) {
  Rank left_rank  = rank(_left);
  Rank right_rank = rank(_right);
  if (left_rank > right_rank) {
	Let* right_temporary = cast(_right, left_rank);
	Let* result			= select_operator(_left, left_rank, quotient, right_temporary, left_rank);
	unlet(right_temporary);
	return result;
  }
  if (right_rank > left_rank) {
	Let* left_temporary = cast(_left, right_rank);
	Let* result		   = select_operator(left_temporary, right_rank, quotient, _right, right_rank);
	unlet(left_temporary);
	return result;
  }
  return select_operator(_left, left_rank, quotient, _right, right_rank);
}

THICC_NODISCARD Let* modulo(Let* _left, Let* _right) {
  Rank left_rank  = rank(_left);
  Rank right_rank = rank(_right);
  if (left_rank > right_rank) {
	Let* right_temporary = cast(_right, left_rank);
	Let* result			= select_operator(_left, left_rank, modulo, right_temporary, left_rank);
	unlet(right_temporary);
	return result;
  }
  if (right_rank > left_rank) {
	Let* left_temporary = cast(_left, right_rank);
	Let* result		   = select_operator(left_temporary, right_rank, modulo, _right, right_rank);
	unlet(left_temporary);
	return result;
  }
  return select_operator(_left, left_rank, modulo, _right, right_rank);
}

THICC_NODISCARD Let* product(Let* _left, Let* _right) {
  Rank left_rank  = rank(_left);
  Rank right_rank = rank(_right);
  if (left_rank > right_rank) {
	Let* right_temporary = cast(_right, left_rank);
	Let* result			= select_operator(_left, left_rank, product, right_temporary, left_rank);
	unlet(right_temporary);
	return result;
  }
  if (right_rank > left_rank) {
	Let* left_temporary = cast(_left, right_rank);
	Let* result		   = select_operator(left_temporary, right_rank, product, _right, right_rank);
	unlet(left_temporary);
	return result;
  }
  return select_operator(_left, left_rank, product, _right, right_rank);
}

THICC_NODISCARD Let* bit_and(Let* _left, Let* _right) {
  Rank left_rank  = rank(_left);
  Rank right_rank = rank(_right);
  if (left_rank > right_rank) {
	Let* right_temporary = cast(_right, left_rank);
	Let* result			= select_operator(_left, left_rank, bit_and, right_temporary, left_rank);
	unlet(right_temporary);
	return result;
  }
  if (right_rank > left_rank) {
	Let* left_temporary = cast(_left, right_rank);
	Let* result		   = select_operator(left_temporary, right_rank, bit_and, _right, right_rank);
	unlet(left_temporary);
	return result;
  }
  return select_operator(_left, left_rank, bit_and, _right, right_rank);
}

THICC_NODISCARD Let* bit_or(Let* _left, Let* _right) {
  Rank left_rank  = rank(_left);
  Rank right_rank = rank(_right);
  if (left_rank > right_rank) {
	Let* right_temporary = cast(_right, left_rank);
	Let* result			= select_operator(_left, left_rank, bit_or, right_temporary, left_rank);
	unlet(right_temporary);
	return result;
  }
  if (right_rank > left_rank) {
	Let* left_temporary = cast(_left, right_rank);
	Let* result		   = select_operator(left_temporary, right_rank, bit_or, _right, right_rank);
	unlet(left_temporary);
	return result;
  }
  return select_operator(_left, left_rank, bit_or, _right, right_rank);
}

THICC_NODISCARD Let* bit_xor(Let* _left, Let* _right) {
  Rank left_rank  = rank(_left);
  Rank right_rank = rank(_right);
  if (left_rank > right_rank) {
	Let* right_temporary = cast(_right, left_rank);
	Let* result			= select_operator(_left, left_rank, bit_xor, right_temporary, left_rank);
	unlet(right_temporary);
	return result;
  }
  if (right_rank > left_rank) {
	Let* left_temporary = cast(_left, right_rank);
	Let* result		   = select_operator(left_temporary, right_rank, bit_xor, _right, right_rank);
	unlet(left_temporary);
	return result;
  }
  return select_operator(_left, left_rank, bit_xor, _right, right_rank);
}

THICC_NODISCARD Let* index_of(Let* _indexable, Let* _index) {
  Rank right_rank = rank(_index);
  if (right_rank < natural_rank || right_rank > complex_rank) {
	Let* right_temporary = cast(_index, integer_rank);
	Let* result = _indexable->behaviour->index_of(_indexable, right_temporary);
	unlet(right_temporary);
	return result;
  }
  return _indexable->behaviour->index_of(_indexable, _index);
}

THICC_NODISCARD Let* bit_not(Let* _let) {
  return _let->behaviour->bit_not(_let);
}

THICC_NODISCARD Let* bit_complement(Let* _let) {
  return _let->behaviour->bit_complement(_let);
}

THICC_NODISCARD Let* indirection(Let* _let) {
  return _let->behaviour->indirection(_let);
}

THICC_NODISCARD Let* negative(Let* _let) {
  return _let->behaviour->negative(_let);
}

THICC_NODISCARD Let* positive(Let* _let) {
  return _let->behaviour->positive(_let);
}

THICC_NODISCARD MutableComparison compare(Let* _left, Let* _right) {
  Rank left_rank  = rank(_left);
  Rank right_rank = rank(_right);
  if (let_is_empty(_left) && let_is_empty(_right))
	return THICC_EQUAL;
  if (left_rank > right_rank) {
	Let*				  right_temporary = cast(_right, left_rank);
	MutableComparison result		  = select_operator(_left, left_rank, comparison, right_temporary, left_rank);
	unlet(right_temporary);
	return result;
  }
  if (right_rank > left_rank) {
	Let*				  left_temporary = cast(_left, right_rank);
	MutableComparison result		 = select_operator(left_temporary, right_rank, comparison, _right, right_rank);
	unlet(left_temporary);
	return result;
  }
  return select_operator(_left, left_rank, comparison, _right, right_rank);
}


THICC_NODISCARD MutableBoolean equal(Let* _left, Let* _right) {
  return comparison_equal(compare(_left, _right));
}

THICC_NODISCARD MutableBoolean greater_than(Let* _left, Let* _right) {
  return comparison_left_greater(compare(_left, _right));
}

THICC_NODISCARD MutableBoolean less_than(Let* _left, Let* _right) {
  return comparison_right_greater(compare(_left, _right));
}

THICC_NODISCARD MutableBoolean not_equal(Let* _left, Let* _right) {
  if (equal(_left, _right))
	return THICC_NO;
  return THICC_YES;
}

THICC_NODISCARD MutableSize length(Let* _let) {
  switch (rank(_let)) {
	case complex_rank:
	  return 2;
	case string_rank:
	  return string_length(_let->value.string_type);
	case array_rank:
	  return _let->value.array_type.length;
	case object_rank:
	  return object_size(object_view(_let));
	default:
	  return 1;
  }
}

THICC_NODISCARD MutableBoolean is_character(Let* _let) {
  return rank_is_character(_let);
}

THICC_NODISCARD MutableBoolean is_signed(Let* _let) {
  return rank_is_signed(_let);
}

THICC_NODISCARD MutableBoolean is_unsigned(Let* _let) {
  return rank_is_unsigned(_let);
}

THICC_NODISCARD MutableBoolean is_numeric(Let* _let) {
  return rank_is_numeric(_let);
}

THICC_NODISCARD MutableBoolean is_integral(Let* _let) {
  return rank_is_integral(_let);
}

THICC_NODISCARD MutableBoolean is_floating_point(Let* _let) {
  return rank_is_floating_point(_let);
}

THICC_NODISCARD MutableBoolean is_indexable(Let* _let) {
  return rank_is_indexable(_let);
}

THICC_NODISCARD MutableBoolean is_string(Let* _let) {
  return rank_is_string(_let);
}

THICC_NODISCARD MutableBoolean is_array(Let* _let) {
  return rank_is_array(_let);
}

THICC_NODISCARD MutableBoolean is_object(Let* _let) {
  return rank_is_invokable(_let);
}

THICC_NODISCARD MutableBoolean is_invokable(Let* _let) {
  return rank_is_invokable(_let);
}

#ifdef __cplusplus
}
#endif

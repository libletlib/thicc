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

#include "thicc_array.h"
#include "../core/thicc_interface.h"
#include "../core/thicc_memory.h"
#include "../core/thicc_struct_array.h"
#include "../core/thicc_struct_var.h"
#include "thicc_math.h"
#include <stdio.h>
#include <stdlib.h>

THICC_NODISCARD MutableComparison array_compare(Array _left, Array _right) {
  MutableSize index = 0;

  if (array_is_empty(_left) && array_is_empty(_right))
	return THICC_EQUAL;
  if (_left.length > _right.length)
	return THICC_LEFT_GREATER;
  if (_right.length > _left.length)
	return THICC_RIGHT_GREATER;

  for (; index < _left.length; ++index) {
	Comparison comparison = compare(_left.array[index], _right.array[index]);
	if (comparison != THICC_EQUAL)
	  return comparison;
  }

  return THICC_EQUAL;
}

THICC_NODISCARD MutableArray array_copy(Array _original) {
  MutableArray buffer = array_allocate(_original.length);
  MutableSize  index  = 0;
  for (; index < _original.length; ++index)
	buffer.array[index] = let_copy(_original.array[index]);
  buffer.length = _original.length;
  return buffer;
}

THICC_NODISCARD static MutableComparison array_compare_n(Array _left, Size _left_offset, Array _right, Size _n) {
  MutableSize index		  = 0, limit;
  Size		  left_length = _left.length - _left_offset;

  if (array_is_empty(_left) && array_is_empty(_right))
	return THICC_EQUAL;
  if (left_length > _right.length)
	return THICC_LEFT_GREATER;
  if (_right.length > left_length)
	return THICC_RIGHT_GREATER;

  limit = THICC_MIN(_n, left_length);
  for (; index < limit; ++index) {
	Comparison comparison = compare(_left.array[index], _right.array[index]);
	if (comparison != THICC_EQUAL)
	  return comparison;
  }

  return THICC_EQUAL;
}

THICC_NODISCARD MutableArray array_remove_subarray(Array _original, Array _subarray) {
  MutableArray buffer = array_allocate(_original.length);
  MutableSize  index  = 0;
  MutableSize  jindex = 0;
  MutableSize   kindex = 0;
  for (; jindex < _original.length; ++index, ++jindex) {
	if (array_compare_n(_original, index, _subarray, _subarray.length))
	  jindex += _subarray.length;
	else {
	  buffer.array[index] = _original.array[jindex];
	  ++kindex;
	}
  }
  buffer.length = kindex;
  return buffer;
}

THICC_NODISCARD MutableArray array_filter_and(Array _left, Array _right) {
  Size		   shortest_length = THICC_MIN(_left.length, _right.length);
  MutableArray buffer		   = array_allocate(shortest_length);
  MutableSize  index		   = 0;
  for (; index < shortest_length; ++index)
	if (equal(_left.array[index], _right.array[index]))
	  buffer.array[index] = let_copy(_left.array[index]);
  buffer.length = shortest_length;
  return buffer;
}

THICC_NODISCARD MutableArray array_filter_or(Array _left, Array _right) {
  MutableArray buffer = array_allocate(_left.length);
  MutableSize  index = 0, jindex = 0, kindex = 0;
  for (; index < _left.length; ++index) {
	for (; jindex < _right.length; ++jindex) {
	  if (not_equal(_left.array[index], _right.array[jindex])) {
		buffer.array[index] = let_copy(_left.array[index]);
		++kindex;
	  }
	}
  }
  buffer.length = kindex;
  return buffer;
}

THICC_NODISCARD MutableArray array_filter_xor(Array _left, Array _right) {
  MutableArray buffer		   = array_allocate(_left.length + _right.length);
  Size		   shortest_length = THICC_MIN(_left.length, _right.length);
  Size		   longest_length  = THICC_MAX(_left.length, _right.length);
  Var*		   longer_pointer  = THICC_LONGER_POINTER(_left.length, _left.array, _right.length, _right.array);
  MutableSize  index = 0, jindex = 0;
  for (; index < longest_length; ++index) {
	if (index < shortest_length && not_equal(_left.array[index], _right.array[jindex])) {
	  buffer.array[jindex] = let_copy(_left.array[index]);
	  ++jindex;
	  buffer.array[jindex] = let_copy(_right.array[index]);
	  ++jindex;
	} else if (index >= shortest_length) {
	  buffer.array[jindex] = let_copy(longer_pointer[index]);
	  ++jindex;
	}
  }
  buffer.length = jindex;
  return buffer;
}

THICC_NODISCARD MutableArray array_map_bit_not(Array _array) {
  MutableSize  index = 0;
  MutableArray copy	 = array_allocate(_array.length);
  for (; index < _array.length; ++index)
	copy.array[index] = bit_not(_array.array[index]);
  copy.length = index;
  return copy;
}

THICC_NODISCARD MutableArray array_map_bit_complement(Array _array) {
  MutableSize  index = 0;
  MutableArray copy	 = array_allocate(_array.length);
  for (; index < _array.length; ++index)
	copy.array[index] = bit_complement(_array.array[index]);
  copy.length = index;
  return copy;
}

THICC_NODISCARD MutableArray array_map_positive(Array _array) {
  MutableSize  index = 0;
  MutableArray copy	 = array_allocate(_array.length);
  for (; index < _array.length; ++index)
	copy.array[index] = positive(_array.array[index]);
  copy.length = index;
  return copy;
}

THICC_NODISCARD MutableArray array_map_negative(Array _array) {
  MutableSize  index = 0;
  MutableArray copy	 = array_allocate(_array.length);
  for (; index < _array.length; ++index)
	copy.array[index] = negative(_array.array[index]);
  copy.length = index;
  return copy;
}

THICC_NODISCARD MutableArray array_zip(Array _left, Array _right) {
  MutableSize  max, min, index = 0;
  MutableArray result;
  Var*		   longer_pointer = THICC_LONGER_POINTER(_left.length, _left.array, _right.length, _right.array);

  if (_left.length > _right.length) {
	max = _left.length;
	min = _right.length;
  } else if (_left.length < _right.length) {
	max = _right.length;
	min = _left.length;
  } else {
	max = _left.length;
	min = _left.length;
  }

  result = array_allocate(max + 1);

  for (; index < max; ++index) {
	if (index < min) {
	  result.array[index] = array_of(2, &_left.array[index], &_right.array[index]);
	} else {
	  result.array[index] = array_of(1, &longer_pointer[index]);
	}
  }
  result.length = max;
  return result;
}

THICC_NODISCARD Var array_element_at(Array _array, Integer _index) {
  Integer array_length = (Integer) _array.length - 1;

  if (_index >= 0l && _index < array_length)
	return _array.array[_index];
  if (_index >= array_length)
	return _array.array[array_length];
  return _array.array[THICC_ABS(_index) > array_length ? 0l : array_length + _index];
}

THICC_NODISCARD MutableArray array_concatenate(Array _left, Array _right) {
  Size length = _left.length + _right.length;
  MutableSize  index = 0, jindex = 0;
  MutableArray buffer = array_allocate(length);
  for (; index < _left.length; ++index)
	buffer.array[index] = let_copy(_left.array[index]);
  for (; jindex < _right.length; ++index, ++jindex)
	buffer.array[index] = let_copy(_right.array[jindex]);
  buffer.length = length;
  return buffer;
}

THICC_NODISCARD MutableArray array_with_self_reference_from_list(Let _self, Size _size, va_list _list) {
  MutableArray buffer = array_allocate(_size + 1);
  MutableSize  index  = 1;
  buffer.array[0]	  = let_copy(_self);
  for (; index < _size; ++index)
	buffer.array[index] = let_copy(*va_arg(_list, Let*));
  buffer.length = _size + 1;
  return buffer;
}

THICC_NODISCARD MutableArray array_from_list(Size _size, va_list _list) {
  MutableArray buffer = array_allocate(_size);
  MutableSize  index  = 0;
  for (; index < _size; ++index)
	buffer.array[index] = let_copy(*va_arg(_list, Let*));
  buffer.length = _size;
  return buffer;
}

THICC_NODISCARD MutableArray array_from_elements(Size _size, ...) {
  va_list	   list;
  MutableArray buffer;
  va_start(list, _size);
  buffer = array_from_list(_size, list);
  va_end(list);
  return buffer;
}

#ifdef __cplusplus
}
#endif

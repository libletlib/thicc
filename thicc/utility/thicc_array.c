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
#include "../core/thicc_struct_var.h"
#include "thicc_comparison.h"
#include "thicc_math.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

THICC_NODISCARD MutableSize array_length(ImmutableArray _array) {
  MutableSize index = 0;
  if (array_is_empty(_array))
	return 0;
  for (;; ++index)
	if (let_is_empty(_array[index]))
	  return index;
}

THICC_NODISCARD MutableComparison array_compare(ImmutableArray _left, ImmutableArray _right) {
  Size		  left_size	 = array_length(_left);
  Size		  right_size = array_length(_right);
  MutableSize index		 = 0;

  if (array_is_empty(_left) && array_is_empty(_right))
	return THICC_EQUAL;
  if (left_size > right_size)
	return THICC_LEFT_GREATER;
  if (right_size > left_size)
	return THICC_RIGHT_GREATER;

  for (; index < left_size; ++index) {
	Comparison comparison = compare(_left[index], _right[index]);
	if (comparison != THICC_EQUAL)
	  return comparison;
  }

  return THICC_EQUAL;
}

THICC_NODISCARD static MutableComparison array_compare_n(ImmutableArray _left, ImmutableArray _right, Size _n) {
  Size		  left_size	 = array_length(_left);
  Size		  right_size = array_length(_right);
  MutableSize index		 = 0, limit;

  if (array_is_empty(_left) && array_is_empty(_right))
	return THICC_EQUAL;
  if (left_size > right_size)
	return THICC_LEFT_GREATER;
  if (right_size > left_size)
	return THICC_RIGHT_GREATER;

  limit = THICC_MIN(_n, left_size);
  for (; index < limit; ++index) {
	Comparison comparison = compare(_left[index], _right[index]);
	if (comparison != THICC_EQUAL)
	  return comparison;
  }

  return THICC_EQUAL;
}

THICC_NODISCARD MutableArray array_copy(ImmutableArray _original) {
  MutableSize  original_length = array_length(_original);
  MutableArray buffer		   = array_allocate(original_length);
  MutableSize  index		   = 0;
  for (; index < original_length; ++index)
	buffer[index] = let_copy(_original[index]);
  buffer[original_length] = let_empty();
  return buffer;
}

THICC_NODISCARD MutableArray array_remove_subarray(ImmutableArray _original, ImmutableArray _subarray) {
  Size		   size			   = array_length(_original);
  Size		   subarray_length = array_length(_subarray);
  MutableArray buffer		   = array_allocate(size);
  MutableSize  index		   = 0;
  MutableSize  jindex		   = 0;
  for (; jindex < size; ++index, ++jindex) {
	if (array_compare_n(_original + index, _subarray, subarray_length))
	  jindex += subarray_length;
	else
	  buffer[index] = _original[jindex];
  }
  buffer[index] = let_empty();
  return buffer;
}

THICC_NODISCARD MutableArray array_filter_and(ImmutableArray _left, ImmutableArray _right) {
  Size		   left_length	   = array_length(_left);
  Size		   right_length	   = array_length(_right);
  MutableArray buffer		   = array_allocate(left_length + right_length);
  Size		   shortest_length = THICC_MIN(left_length, right_length);
  MutableSize  index		   = 0;
  for (; index < shortest_length; ++index)
	if (equal(_left[index], _right[index]))
	  buffer[index] = let_copy(_left[index]);
  buffer[index] = let_empty();
  return buffer;
}

THICC_NODISCARD MutableArray array_filter_or(ImmutableArray _left, ImmutableArray _right) {
  Size		   buffer_length = array_length(_left);
  Size		   filter_length = array_length(_right);
  MutableArray buffer		 = array_allocate(buffer_length);
  MutableSize  index = 0, jindex = 0;
  for (; index < buffer_length; ++index)
	for (; jindex < filter_length; ++jindex)
	  if (not_equal(_left[index], _right[jindex]))
		buffer[index] = let_copy(_left[index]);
  buffer[index] = let_empty();
  return buffer;
}

THICC_NODISCARD MutableArray array_filter_xor(ImmutableArray _left, ImmutableArray _right) {
  Size			 left_length	 = array_length(_left);
  Size			 right_length	 = array_length(_right);
  MutableArray	 buffer			 = array_allocate(left_length + right_length + 1);
  Size			 shortest_length = THICC_MIN(left_length, right_length);
  Size			 longest_length	 = THICC_MAX(left_length, right_length);
  ImmutableArray longer_pointer	 = THICC_LONGER_POINTER(left_length, _left, right_length, _right);
  MutableSize	 index = 0, jindex = 0;
  for (; index < longest_length; ++index) {
	if (index < shortest_length && not_equal(_left[index], _right[jindex])) {
	  buffer[jindex] = let_copy(_left[index]);
	  ++jindex;
	  buffer[jindex] = let_copy(_right[index]);
	  ++jindex;
	} else if (index >= shortest_length) {
	  buffer[jindex] = let_copy(longer_pointer[index]);
	  ++jindex;
	}
  }
  buffer[index] = let_empty();
  return buffer;
}

THICC_NODISCARD MutableArray array_map_bit_not(ImmutableArray _array) {
  Size		   length = array_length(_array);
  MutableSize  index  = 0;
  MutableArray copy	  = array_allocate(length + 1);
  for (; index < length; ++index)
	copy[index] = bit_not(_array[index]);
  return copy;
}

THICC_NODISCARD MutableArray array_map_bit_complement(ImmutableArray _array) {
  Size		   length = array_length(_array);
  MutableSize  index  = 0;
  MutableArray copy	  = array_allocate(length + 1);
  for (; index < length; ++index)
	copy[index] = bit_complement(_array[index]);
  return copy;
}

THICC_NODISCARD MutableArray array_map_positive(ImmutableArray _array) {
  Size		   length = array_length(_array);
  MutableSize  index  = 0;
  MutableArray copy	  = array_allocate(length + 1);
  for (; index < length; ++index)
	copy[index] = positive(_array[index]);
  return copy;
}

THICC_NODISCARD MutableArray array_map_negative(ImmutableArray _array) {
  Size		   length = array_length(_array);
  MutableSize  index  = 0;
  MutableArray copy	  = array_allocate(length + 1);
  for (; index < length; ++index)
	copy[index] = negative(_array[index]);
  return copy;
}

THICC_NODISCARD MutableArray array_zip(ImmutableArray _left, ImmutableArray _right) {
  Size			 left_length  = array_length(_left);
  Size			 right_length = array_length(_right);
  MutableSize	 max, min, index = 0;
  MutableArray	 result;
  ImmutableArray longer_pointer = THICC_LONGER_POINTER(left_length, _left, right_length, _right);

  if (left_length > right_length) {
	max = left_length;
	min = right_length;
  } else if (left_length < right_length) {
	max = right_length;
	min = left_length;
  } else {
	max = left_length;
	min = left_length;
  }

  result = array_allocate(max + 1);

  for (; index < max; ++index) {
	if (index < min) {
	  result[index] = array_of(2, &_left[index], &_right[index]);
	} else {
	  result[index] = array_of(1, &longer_pointer[index]);
	}
  }

  result[max] = let_empty();
  return result;
}

THICC_NODISCARD Var array_element_at(ImmutableArray _array, Integer _index) {
  Integer size = (Integer) array_length(_array);
  if (_index >= 0l && _index < size)
	return _array[_index];
  if (_index >= size)
	return _array[size];
  return _array[labs(_index) > size ? 0l : size + _index];
}

THICC_NODISCARD MutableArray array_concatenate(ImmutableArray _left, ImmutableArray _right) {
  Size		   left_length	= array_length(_left);
  Size		   right_length = array_length(_right);
  MutableArray buffer		= array_allocate(left_length + right_length + 1);
  MutableSize  index = 0, jindex = 0;
  for (; index < left_length; ++index)
	buffer[index] = let_copy(_left[index]);
  for (; jindex < right_length; ++index, ++jindex)
	buffer[index] = let_copy(_right[jindex]);
  buffer[left_length + right_length + 1] = let_empty();
  return buffer;
}

THICC_NODISCARD MutableArray array_with_self_reference_from_list(Let _self, Size _size, va_list _list) {
  MutableArray buffer = array_allocate(_size + 2);
  MutableSize  index  = 1;
  buffer[0]			  = let_copy(_self);
  for (; index < _size; ++index)
	buffer[index] = let_copy(*va_arg(_list, Let*));
  buffer[index] = let_empty();
  return buffer;
}

THICC_NODISCARD MutableArray array_from_list(Size _size, va_list _list) {
  MutableArray buffer = array_allocate(_size + 1);
  MutableSize  index  = 0;
  for (; index < _size; ++index)
	buffer[index] = let_copy(*va_arg(_list, Let*));
  buffer[index] = let_empty();
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

THICC_NODISCARD MutableArray array_empty(void) {
  return THICC_NAUGHT;
}

THICC_NODISCARD MutableBoolean array_is_empty(ImmutableArray _array) {
  return _array == THICC_NAUGHT || let_is_empty(*_array);
}

#ifdef __cplusplus
}
#endif

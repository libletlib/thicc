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

#include "thicc_array.h"
#include "../core/thicc_struct_let.h"
#include "../core/thicc_memory.h"
#include "../core/thicc_interface.h"
#include "thicc_math.h"
#include "thicc_comparison.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

	MutableSize array_length(ImmutableArray _array) {
		MutableSize index = 0;
		if(array_is_empty(_array))
			return 0;
		for(;;++index)
			if(let_is_empty(_array[index]))
			    return index;
	}

	MutableComparison array_compare(ImmutableArray _left, ImmutableArray _right) {
		Size left_size = array_length(_left);
		Size right_size = array_length(_right);
		MutableSize index = 0;
		if(array_is_empty(_left) && array_is_empty(_right))
			return THICC_EQUAL;
		if(left_size > right_size)
			return THICC_LEFT_GREATER;
		if(right_size > left_size)
			return THICC_RIGHT_GREATER;
		for(; index < left_size; ++index) {
			if(greater_than(*_left, *_right))
				return THICC_LEFT_GREATER;
			if(less_than(*_left, *_right))
				return THICC_RIGHT_GREATER;
		}
		return THICC_EQUAL;
	}

	MutableArray array_copy(ImmutableArray _original) {
		MutableSize original_length = array_length(_original);
		MutableArray buffer = array_allocate(original_length);
		MutableSize index = 0;
		for(; index < original_length; ++index)
			buffer[index] = let_copy(_original[index]);
		buffer[original_length] = let_empty();
		return buffer;
	}

	MutableArray array_remove_subarray(ImmutableArray _original, ImmutableArray _subarray) {
		Size size = array_length(_original);
		Size subarray_size = array_length(_subarray);
		MutableArray buffer = array_allocate(size);
		MutableSize index = 0;
		MutableSize jindex = 0;
		for(; jindex < size; ++index, ++jindex) {
			if(comparison_equal(memcmp(_original+index, _subarray, subarray_size)))
				jindex += subarray_size;
			else
				buffer[index] = _original[jindex];
		}
		buffer[index] = let_empty();
		return buffer;
	}

	MutableArray array_filter_and(ImmutableArray _left, ImmutableArray _right) {
		Size left_length = array_length(_left);
		Size right_length = array_length(_right);
		MutableArray buffer = array_allocate(left_length + right_length);
		Size shortest_length = THICC_MIN(left_length, right_length);
		MutableSize index = 0;
		for(; index < shortest_length; ++index)
			if(equal(_left[index], _right[index]))
				buffer[index] = let_copy(_left[index]);
		buffer[index] = let_empty();
		return buffer;
	}

	MutableArray array_filter_or(ImmutableArray _left, ImmutableArray _right) {
		Size buffer_length = array_length(_left);
		Size filter_length = array_length(_right);
		MutableArray buffer = array_allocate(buffer_length);
		MutableSize index = 0, jindex = 0;
		for(; index < buffer_length; ++index)
			for (; jindex < filter_length; ++jindex)
				if (not_equal(_left[index], _right[jindex]))
					buffer[index] = let_copy(_left[index]);
		buffer[index] = let_empty();
		return buffer;
	}

	MutableArray array_filter_xor(ImmutableArray _left, ImmutableArray _right) {
		Size left_length = array_length(_left);
		Size right_length = array_length(_right);
		MutableArray buffer = array_allocate(left_length+right_length+1);
		Size shortest_length = THICC_MIN(left_length, right_length);
		Size longest_length = THICC_MAX(left_length, right_length);
		ImmutableArray longer_pointer = THICC_LONGER_POINTER(left_length, _left, right_length, _right);
		MutableSize index = 0, jindex = 0;
		for(; index < longest_length; ++index)
		{
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

	MutableArray array_map_bit_not(ImmutableArray _array) {
		Size length = array_length(_array);
		MutableSize index = 0;
		MutableArray copy = array_allocate(length + 1);
		for(; index < length; ++index)
			copy[index] = bit_not(_array[index]);
		return copy;
	}

	MutableArray array_map_bit_complement(ImmutableArray _array) {
		Size length = array_length(_array);
		MutableSize index = 0;
		MutableArray copy = array_allocate(length + 1);
		for(; index < length; ++index)
			copy[index] = bit_complement(_array[index]);
		return copy;
	}

	MutableArray array_map_positive(ImmutableArray _array) {
		Size length = array_length(_array);
		MutableSize index = 0;
		MutableArray copy = array_allocate(length + 1);
		for(; index < length; ++index)
			copy[index] = positive(_array[index]);
		return copy;
	}

	MutableArray array_map_negative(ImmutableArray _array) {
		Size length = array_length(_array);
		MutableSize index = 0;
		MutableArray copy = array_allocate(length + 1);
		for(; index < length; ++index)
			copy[index] = negative(_array[index]);
		return copy;
	}

	MutableArray array_map_increment(MutableArray _array) {
		Size length = array_length(_array);
		MutableSize index = 0;
		for(; index < length; ++index)
			_array[index] = pre_increment(_array[index]);
		return _array;
	}

	MutableArray array_map_decrement(MutableArray _array) {
		Size length = array_length(_array);
		MutableSize index = 0;
		for(; index < length; ++index)
			_array[index] = pre_decrement(_array[index]);
		return _array;
	}

	MutableLet array_element_at(ImmutableArray _array, Long _index) {
		Long size = (Long) array_length(_array);
		if(_index >= 0l && _index < size)
			return _array[_index];
		if(_index >= size)
			return _array[size];
		return _array[labs(_index) > size ? 0l : size + _index];
	}

	MutableArray array_concatenate(ImmutableArray _left, ImmutableArray _right) {
		Size left_length = array_length(_left);
		Size right_length = array_length(_right);
		MutableArray buffer = array_allocate(left_length + right_length + 1);
		MutableSize index = 0, jindex = 0;
		for(; index < left_length; ++index)
			buffer[index] = let_copy(_left[index]);
		for(; jindex < right_length; ++index, ++jindex)
			buffer[index] = let_copy(_right[jindex]);
		buffer[left_length + right_length + 1] = let_empty();
		return buffer;
 	}

	MutableArray array_from_list(Size _size, va_list _list) {
		MutableArray buffer = array_allocate(_size + 1);
		MutableSize index = 0;
		for(;index < _size; ++index)
			buffer[index] = let_copy(*va_arg(_list, Let*));
		buffer[index] = let_empty();
		return buffer;
	}

	MutableArray array_from_elements(Size _size, ...) {
		va_list list;
		MutableArray buffer;
		va_start(list, _size);
		buffer = array_from_list(_size, list);
		va_end(list);
		return buffer;
	}

	MutableArray array_empty(void) {
		return THICC_NOTHING;
	}

	MutableBoolean array_is_empty(ImmutableArray _array) {
		return _array == THICC_NOTHING || let_is_empty(*_array);
	}

#ifdef __cplusplus
}
#endif

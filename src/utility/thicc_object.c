/*
 *   ___       ___       ___       ___       ___
 *  /\  \     /\__\     /\  \     /\  \     /\  \
 *  \:\  \   /:/__/_   _\:\  \   /::\  \   /::\  \
 *  /::\__\ /::\/\__\ /\/::\__\ /:/\:\__\ /:/\:\__\
 * /:/\/__/ \/\::/  / \::/\/__/ \:\ \/__/ \:\ \/__/
 * \/__/      /:/  /   \:\__\    \:\__\    \:\__\
 *            \/__/     \/__/     \/__/     \/__/
 *
 * Copyright 2022 - 2023 Ville Rissanen
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1.   Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *
 * 2.   Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
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

#include "thicc_object.h"
#include "../core/thicc_memory.h"
#include "../core/thicc_struct_object.h"
#include "thicc_array.h"
#include "thicc_function.h"
#include <thicc_interface.h>

THICC_NODISCARD MutableSize object_size(ImmutableObject _object) {
  return ((Root) _object)->members->value.array_type.array[0]->value.array_type.length;
}

THICC_NODISCARD MutableComparison object_compare(ImmutableObject _left, ImmutableObject _right) {
  MutableArray left_keys;
  MutableArray right_keys;
  MutableSize  index = 0;

  if (!_left && !_right)
	return THICC_EQUAL;
  if (_left && !_right)
	return THICC_LEFT_GREATER;
  if (!_left)
	return THICC_RIGHT_GREATER;

  left_keys	 = root_keys_from_pointer(_left);
  right_keys = root_keys_from_pointer(_right);

  if (left_keys.length > right_keys.length)
	return THICC_LEFT_GREATER;
  if (right_keys.length > left_keys.length)
	return THICC_RIGHT_GREATER;

  for (; index < left_keys.length; ++index) {
	Comparison key_comparison = compare(left_keys.array[index], right_keys.array[index]);
	Comparison value_comparison =
		compare(root_values_from_pointer(_left).array[index], root_values_from_pointer(_right).array[index]);
	if (key_comparison)
	  return key_comparison;
	if (value_comparison)
	  return value_comparison;
  }
  return THICC_EQUAL;
}

THICC_NODISCARD MutableObject object_copy(ImmutableObject _object) {
  MutableRoot copy;

  if (!_object)
	return object_empty();

  copy			= object_allocate();
  copy->members = let_copy(((Root) _object)->members);
  return copy;
}

THICC_NODISCARD MutableObject object_empty(void) {
  return THICC_NAUGHT;
}

THICC_NODISCARD MutableBoolean object_is_empty(ImmutableObject _object) {
  return _object == THICC_NAUGHT ? THICC_YES : THICC_NO;
}

THICC_NODISCARD MutableObject object_compose_list(Size _size, va_list _list) {
  MutableSize  index = 0, length;
  MutableArray key;
  MutableArray value;
  MutableRoot  root = object_allocate();
  MutableArray buffer;

  if (_size % 2 != 0)
	return object_empty();

  length = _size / 2;

  key	= array_allocate(length);
  value = array_allocate(length);

  for (; index < length; ++index) {
	key.array[index]   = let_copy(va_arg(_list, Let*));
	value.array[index] = let_copy(va_arg(_list, Let*));
  }

  key.length	  = length;
  value.length	  = length;
  buffer		  = array_allocate(2);
  buffer.array[0] = move_array(key);
  buffer.array[1] = move_array(value);
  buffer.length	  = 2;

  root->members = move_array(buffer);
  return root;
}

THICC_NODISCARD MutableObject object_compose(Size _size, ...) {
  va_list		list;
  MutableObject object;
  va_start(list, _size);
  object = object_compose_list(_size, list);
  va_end(list);
  return object;
}

THICC_NODISCARD Let* object_method_invoke(Let* _object, Let* _method, Size _argument_count, ...) {
  va_list list;
  Let*	  array;
  Let*	  result;

  va_start(list, _argument_count);
  array = move_array(array_with_self_reference_from_list(_object, _argument_count, list));
  va_end(list);

  result = function_invoke(_method, array);
  unlet(array);

  return result;
}

#ifdef __cplusplus
}
#endif

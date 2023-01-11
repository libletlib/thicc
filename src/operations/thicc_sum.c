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

#include "thicc_sum.h"
#include <thicc_interface.h>
#include <thicc_struct_var.h>
#include "../utility/thicc_array.h"
#include "../utility/thicc_function.h"
#include "../utility/thicc_object.h"
#include "../utility/thicc_string.h"

THICC_NODISCARD Let* boolean_sum(Let* _left, Let* _right) {
  return let_boolean((!_left->value.boolean_type && !_right->value.boolean_type) ? THICC_NO : THICC_YES);
}

THICC_NODISCARD Let* character_sum(Let* _left, Let* _right) {
  return move_string(string_from_characters(2, _left->value.character_type, _right->value.character_type));
}

THICC_NODISCARD Let* natural_sum(Let* _left, Let* _right) {
  return let_natural(_left->value.natural_type + _right->value.natural_type);
}

THICC_NODISCARD Let* integer_sum(Let* _left, Let* _right) {
  return let_integer(_left->value.integer_type + _right->value.integer_type);
}

THICC_NODISCARD Let* real_sum(Let* _left, Let* _right) {
  return let_real(_left->value.real_type + _right->value.real_type);
}

THICC_NODISCARD Let* complex_sum(Let* _left, Let* _right) {
  return let_complex(cmplx(_left->value.complex_type.real + _right->value.complex_type.real,
						   _left->value.complex_type.imaginary + _right->value.complex_type.imaginary));
}

THICC_NODISCARD Let* string_sum(Let* _left, Let* _right) {
  return move_string(string_concatenate(_left->value.string_type, _right->value.string_type));
}

THICC_NODISCARD Let* function_sum(Let* _left, Let* _right) {
  Let* left_result  = function_invoke(_left, let_empty());
  Let* right_result = function_invoke(_right, let_empty());
  Let* result	   = sum(left_result, right_result);

  unlet(right_result);
  unlet(left_result);
  return result;
}

THICC_NODISCARD Let* array_sum(Let* _left, Let* _right) {
  return move_array(array_concatenate(_left->value.array_type, _right->value.array_type));
}

THICC_NODISCARD Let* object_sum(Let* _left, Let* _right) {
  Let* property_name = let_string("+");
  Let* property		= member(_left, property_name);
  Let* result;
  unlet(property_name);

  if (let_is_empty(property) || !is_invokable(property)) {
	unlet(property);
	return let_empty();
  }

  result = object_method_invoke(_left, property, 2, _right);

  unlet(property);

  return result;
}

#ifdef __cplusplus
}
#endif

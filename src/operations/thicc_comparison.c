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

#include "thicc_comparison.h"
#include "../utility/thicc_array.h"
#include "../utility/thicc_math.h"
#include "../utility/thicc_object.h"
#include "../utility/thicc_string.h"
#include <stdlib.h>
#include <thicc_interface.h>
#include <thicc_struct_var.h>

THICC_NODISCARD MutableComparison boolean_comparison(Let* _left, Let* _right) {
  if (_left->value.boolean_type && !_right->value.boolean_type)
	THICC_LEFT_GREATER;
  if (!_left->value.boolean_type && _right->value.boolean_type)
	THICC_RIGHT_GREATER;
  return THICC_EQUAL;
}

THICC_NODISCARD MutableComparison character_comparison(Let* _left, Let* _right) {
  if (_left->value.character_type > _right->value.character_type)
	return THICC_LEFT_GREATER;
  if (_right->value.character_type > _left->value.character_type)
	return THICC_RIGHT_GREATER;
  return THICC_EQUAL;
}

THICC_NODISCARD MutableComparison natural_comparison(Let* _left, Let* _right) {
  if (_left->value.natural_type > _right->value.natural_type)
	return THICC_LEFT_GREATER;
  if (_right->value.natural_type > _left->value.natural_type)
	return THICC_RIGHT_GREATER;
  return THICC_EQUAL;
}

THICC_NODISCARD MutableComparison integer_comparison(Let* _left, Let* _right) {
  if (_left->value.integer_type > _right->value.integer_type)
	return THICC_LEFT_GREATER;
  if (_right->value.integer_type > _left->value.integer_type)
	return THICC_RIGHT_GREATER;
  return THICC_EQUAL;
}

THICC_NODISCARD MutableComparison real_comparison(Let* _left, Let* _right) {
  if (math_real_equal(_left->value.real_type, _right->value.real_type))
	return THICC_EQUAL;
  if (_left->value.real_type > _right->value.real_type)
	return THICC_LEFT_GREATER;
  return THICC_RIGHT_GREATER;
}

THICC_NODISCARD MutableComparison complex_comparison(Let* _left, Let* _right) {
  if (math_complex_equal(_left->value.complex_type, _right->value.complex_type))
	return THICC_EQUAL;
  if (_left->value.complex_type.real > _right->value.complex_type.real)
	return THICC_LEFT_GREATER;
  if (math_real_equal(_left->value.complex_type.real, _right->value.complex_type.real) &&
	  _left->value.complex_type.imaginary > _right->value.complex_type.imaginary)
	return THICC_LEFT_GREATER;
  return THICC_RIGHT_GREATER;
}

THICC_NODISCARD MutableComparison string_comparison(Let* _left, Let* _right) {
  if (!is_string(_left)) {
	MutableString	  string = as_string(_left);
	MutableComparison result = string_compare(string, _right->value.string_type);
	free(string.string);
	return result;
  } else if (!is_string(_right)) {
	MutableString	  string = as_string(_right);
	MutableComparison result = string_compare(_left->value.string_type, string);
	free(string.string);
	return result;
  } else {
	return string_compare(_left->value.string_type, _right->value.string_type);
  }
}

THICC_NODISCARD MutableComparison function_comparison(Let* _left, Let* _right) {
  if (_left->value.function_type != _right->value.function_type)
	return THICC_LEFT_GREATER;
  return THICC_EQUAL;
}

THICC_NODISCARD MutableComparison array_comparison(Let* _left, Let* _right) {
  return array_compare(_left->value.array_type, _right->value.array_type);
}

THICC_NODISCARD MutableComparison object_comparison(Let* _left, Let* _right) {
  Let*				property_name = let_string("<=>");
  Let*				property	  = member(_left, property_name);
  Let*				temporary;
  MutableComparison result;
  unlet(property_name);

  if (let_is_empty(property) || !is_invokable(property)) {
	unlet(property);
	return object_compare(object_view(_left), object_view(_right));
  }

  temporary = object_method_invoke(_left, property, 2, _right);
  result	= (Comparison) as_integer(temporary);

  unlet(property);
  unlet(temporary);

  return result;
}

#ifdef __cplusplus
}
#endif

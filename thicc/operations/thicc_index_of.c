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

#include "thicc_index_of.h"
#include <thicc_interface.h>
#include <thicc_struct_var.h>
#include <stdlib.h>
#include "../utility/thicc_array.h"
#include "../utility/thicc_character.h"
#include "../utility/thicc_function.h"
#include "../utility/thicc_object.h"
#include "../utility/thicc_string.h"

THICC_NODISCARD Var boolean_index_of(Let _let, THICC_MAYBE_UNUSED Let _index) {
  return let_boolean(_let.value.boolean_type);
}

THICC_NODISCARD Var character_index_of(Let _let, THICC_MAYBE_UNUSED Let _index) {
  return let_character(_let.value.character_type);
}

THICC_NODISCARD Var natural_index_of(Let _let, Let _index) {
  MutableString string = string_from_natural(_let.value.natural_type);
  Let			result = let_natural((Natural) character_to_number(string_character_at(string, as_integer(_index))));
  free((void*) string.string);
  return result;
}

THICC_NODISCARD Var integer_index_of(Let _let, Let _index) {
  MutableString			string	= string_from_integer(_let.value.integer_type);
  CharacterPromotedType numeric = character_to_number(string_character_at(string, as_integer(_index)));

  if (numeric == THICC_NONNUMERIC) {
	Let result = let_character((Character) numeric);
	free((void*) string.string);
	return result;
  } else {
	Let result = let_natural((Natural) numeric);
	free((void*) string.string);
	return result;
  }
}

THICC_NODISCARD Var real_index_of(Let _let, Let _index) {
  MutableString			string	= string_from_real(_let.value.real_type);
  CharacterPromotedType numeric = character_to_number(string_character_at(string, as_integer(_index)));

  if (numeric == THICC_NONNUMERIC) {
	Let result = let_character((Character) numeric);
	free((void*) string.string);
	return result;
  } else {
	Let result = let_natural((Natural) numeric);
	free((void*) string.string);
	return result;
  }
}

THICC_NODISCARD Var complex_index_of(Let _let, Let _index) {
  if (_index.value.integer_type == 0 || _index.value.integer_type < -1)
	return let_real(_let.value.complex_type.real);
  else
	return let_real(_let.value.complex_type.imaginary);
}

THICC_NODISCARD Var string_index_of(Let _let, Let _index) {
  return let_character(string_character_at(_let.value.string_type, as_integer(_index)));
}

THICC_NODISCARD Var function_index_of(Let _let, Let _index) {
  Let let_result   = function_invoke(_let, let_empty());
  Let index_result = function_invoke(_index, let_empty());
  Let result	   = index_of(let_result, index_result);
  unlet_if_required(index_result);
  unlet_if_required(let_result);
  return result;
}

THICC_NODISCARD Var array_index_of(Let _let, Let _index) {
  return let_copy(array_element_at(_let.value.array_type, as_integer(_index)));
}

THICC_NODISCARD Var object_index_of(Let _let, Let _index) {
  Let property_name = move_string(string_literal("[]"));
  Let property		= member(_let, property_name);
  Var result;

  if (let_is_empty(property) || !is_invokable(property)) {
	unlet_if_required(property);

	return let_empty();
  }

  result = object_method_invoke(_let, property, 2, &_index);

  unlet_if_required(property);

  return result;
}

#ifdef __cplusplus
}
#endif

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

#include "thicc_as_string.h"
#include "../core/thicc_interface.h"
#include "../core/thicc_struct_object.h"
#include "../core/thicc_struct_var.h"
#include "../utility/thicc_function.h"
#include "../utility/thicc_object.h"
#include "../utility/thicc_string.h"

THICC_NODISCARD MutableString boolean_as_string(Let _let) {
  return _let.value.boolean_type ? string_copy(string_literal("true")) : string_copy(string_literal("false"));
}

THICC_NODISCARD MutableString character_as_string(Let _let) {
  return string_from_characters(1, _let.value.character_type);
}

THICC_NODISCARD MutableString natural_as_string(Let _let) {
  return string_from_natural(_let.value.natural_type);
}

THICC_NODISCARD MutableString integer_as_string(Let _let) {
  return string_from_integer(_let.value.integer_type);
}

THICC_NODISCARD MutableString real_as_string(Let _let) {
  return string_from_real(_let.value.real_type);
}

THICC_NODISCARD MutableString complex_as_string(Let _let) {
  return string_from_complex(_let.value.complex_type);
}

THICC_NODISCARD MutableString string_as_string(Let _let) {
  return string_copy(_let.value.string_type);
}

THICC_NODISCARD MutableString function_as_string(Let _let) {
  Let			temporary = function_invoke(_let, let_empty());
  MutableString result	  = as_string(temporary);
  unlet_if_required(temporary);
  return result;
}

THICC_NODISCARD MutableString array_as_string(Let _let) {
  return string_from_array(_let.value.array_type);
}

THICC_NODISCARD MutableString object_as_string(Let _let) {
  Let conversion_value = member(_let, move_string(string_literal("string")));
  if (!let_is_empty(conversion_value)) {
	if (is_invokable(conversion_value)) {
	  Let			temporary = object_method_invoke(_let, conversion_value, 2, &_let);
	  MutableString result	  = as_string(temporary);
	  unlet_if_required(temporary);

	  return result;
	} else {
	  MutableString result = as_string(conversion_value);
	  unlet_if_required(conversion_value);

	  return result;
	}
  }

  unlet_if_required(conversion_value);
  return string_from_object(object_view(_let));
}

#ifdef __cplusplus
}
#endif

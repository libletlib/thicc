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

#include "thicc_as_character.h"
#include "../core/thicc_interface.h"
#include "../core/thicc_struct_object.h"
#include "../core/thicc_struct_var.h"
#include "../utility/thicc_function.h"
#include "../utility/thicc_object.h"

THICC_NODISCARD MutableCharacter boolean_as_character(Let _let) {
  return _let.value.boolean_type ? '1' : '\0';
}

THICC_NODISCARD MutableCharacter character_as_character(Let _let) {
  return _let.value.character_type;
}

THICC_NODISCARD MutableCharacter natural_as_character(Let _let) {
  return (Character) _let.value.natural_type;
}

THICC_NODISCARD MutableCharacter integer_as_character(Let _let) {
  return (Character) _let.value.integer_type;
}

THICC_NODISCARD MutableCharacter real_as_character(Let _let) {
  return (Character) _let.value.real_type;
}

THICC_NODISCARD MutableCharacter complex_as_character(Let _let) {
  return (Character) _let.value.complex_type.real;
}

THICC_NODISCARD MutableCharacter string_as_character(Let _let) {
  return *string_view(_let);
}

THICC_NODISCARD MutableCharacter function_as_character(Let _let) {
  Let		temporary = function_invoke(_let, let_empty());
  Character result	  = as_character(temporary);
  unlet_if_required(temporary);
  return result;
}

THICC_NODISCARD MutableCharacter array_as_character(Let _let) {
  return as_character(*array_view(_let));
}

THICC_NODISCARD MutableCharacter object_as_character(Let _let) {
  Let conversion_value = member(_let, move_string("character_type"));
  if (!let_is_empty(conversion_value)) {
	if (is_invokable(conversion_value)) {
	  Let		temporary = object_method_invoke(_let, conversion_value, 2, &_let);
	  Character result	  = as_character(temporary);

	  unlet_if_required(temporary);

	  return result;
	} else {
	  Character result = as_character(conversion_value);

	  unlet_if_required(conversion_value);

	  return result;
	}
  }

  unlet_if_required(conversion_value);

  if (object_size(object_view(_let)) > 0)
	return as_character(array_view(array_view(((Root) object_view(_let))->members)[1])[0]);

  return '\0';
}

#ifdef __cplusplus
}
#endif

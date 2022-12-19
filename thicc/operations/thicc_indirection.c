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

#include "thicc_indirection.h"
#include <thicc_interface.h>
#include <thicc_struct_var.h>
#include "../utility/thicc_function.h"
#include "../utility/thicc_object.h"

THICC_NODISCARD Var boolean_indirection(Let _let) {
  return let_boolean(_let.value.boolean_type);
}

THICC_NODISCARD Var character_indirection(Let _let) {
  return let_character(_let.value.character_type);
}

THICC_NODISCARD Var natural_indirection(Let _let) {
  return let_natural(_let.value.natural_type);
}

THICC_NODISCARD Var integer_indirection(Let _let) {
  return let_integer(_let.value.integer_type);
}

THICC_NODISCARD Var real_indirection(Let _let) {
  return let_real(_let.value.real_type);
}

THICC_NODISCARD Var complex_indirection(Let _let) {
  return let_complex(_let.value.complex_type);
}

THICC_NODISCARD Var string_indirection(Let _let) {
  return let_character(*string_view(_let));
}

THICC_NODISCARD Var function_indirection(Let _let) {
  Let let_result = function_invoke(_let, let_empty());
  Let result	 = indirection(let_result);
  unlet_if_required(let_result);
  return result;
}

THICC_NODISCARD Var array_indirection(Let _let) {
  return let_copy(*_let.value.array_type.array);
}

THICC_NODISCARD Var object_indirection(Let _let) {
  Let property_name = move_string(string_literal("indirection"));
  Let property		= member(_let, property_name);
  Var result;

  if (let_is_empty(property) || !is_invokable(property)) {
	unlet_if_required(property);

	return let_empty();
  }

  result = object_method_invoke(_let, property, 0);

  unlet_if_required(property);

  return result;
}

#ifdef __cplusplus
}
#endif

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

#include "thicc_negative.h"
#include "../utility/thicc_array.h"
#include "../utility/thicc_function.h"
#include "../utility/thicc_object.h"
#include "../utility/thicc_string.h"
#include <thicc_interface.h>
#include <thicc_struct_var.h>

THICC_NODISCARD Let* boolean_negative(THICC_MAYBE_UNUSED Let* _let) {
  return let_boolean(THICC_NO);
}

THICC_NODISCARD Let* character_negative(Let* _let) {
#if THICC_CHAR_SIGNED
  return let_character((Character) - ((CharacterPromotedType) _let->value.character_type));
#else
  return let_integer(-((Integer) _let.value.character_type));
#endif
}

THICC_NODISCARD Let* natural_negative(Let* _let) {
  return let_integer(-(Integer) _let->value.natural_type);
}

THICC_NODISCARD Let* integer_negative(Let* _let) {
  return let_integer(-_let->value.integer_type);
}

THICC_NODISCARD Let* real_negative(Let* _let) {
  return let_real(-_let->value.real_type);
}

THICC_NODISCARD Let* complex_negative(Let* _let) {
  return let_complex(cmplx(-_let->value.complex_type.real, -_let->value.complex_type.imaginary));
}

THICC_NODISCARD Let* string_negative(Let* _let) {
  return move_string(string_map_negative(_let->value.string_type));
}

THICC_NODISCARD Let* function_negative(Let* _let) {
  Let* let_result = function_invoke(_let, let_empty());
  Let* result	  = negative(let_result);
  unlet(let_result);
  return result;
}

THICC_NODISCARD Let* array_negative(Let* _let) {
  return move_array(array_map_negative(_let->value.array_type));
}

THICC_NODISCARD Let* object_negative(Let* _let) {
  Let* property_name = let_string("negative");
  Let* property		 = member(_let, property_name);
  Let* result;
  unlet(property_name);

  if (let_is_empty(property) || !is_invokable(property)) {
	unlet(property);

	return let_empty();
  }

  result = object_method_invoke(_let, property, 0);

  unlet(property);

  return result;
}

#ifdef __cplusplus
}
#endif

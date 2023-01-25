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
 * docs and/or other materials provided with the distribution.
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

#include "thicc_bit_not.h"
#include <thicc_struct_var.h>
#include <thicc_interface.h>
#include "../utility/thicc_array.h"
#include "../utility/thicc_function.h"
#include "../utility/thicc_math.h"
#include "../utility/thicc_object.h"

THICC_NODISCARD Let* boolean_bit_not(Let* _let) {
  return let_boolean(_let->value.boolean_type ? THICC_NO : THICC_YES);
}

THICC_NODISCARD Let* character_bit_not(Let* _let) {
  if (_let->value.character_type)
	return let_boolean(THICC_NO);
  return let_boolean(THICC_YES);
}

THICC_NODISCARD Let* natural_bit_not(Let* _let) {
  if (_let->value.natural_type)
	return let_boolean(THICC_NO);
  return let_boolean(THICC_YES);
}

THICC_NODISCARD Let* integer_bit_not(Let* _let) {
  if (_let->value.integer_type)
	return let_boolean(THICC_NO);
  return let_boolean(THICC_YES);
}

THICC_NODISCARD Let* real_bit_not(Let* _let) {
  if (math_real_equal(_let->value.real_type, 0.0))
	return let_boolean(THICC_YES);
  return let_boolean(THICC_NO);
}

THICC_NODISCARD Let* complex_bit_not(Let* _let) {
  if (math_complex_equal(_let->value.complex_type, cmplx(0.0l, 0.0l)))
	return let_boolean(THICC_YES);
  return let_boolean(THICC_NO);
}

THICC_NODISCARD Let* string_bit_not(Let* _let) {
  if (string_view(_let))
	return let_boolean(THICC_NO);
  return let_boolean(THICC_YES);
}

THICC_NODISCARD Let* function_bit_not(Let* _let) {
  Let* let_result = function_invoke(_let, let_empty());
  Let* result	 = bit_not(let_result);
  unlet(let_result);
  return result;
}

THICC_NODISCARD Let* array_bit_not(Let* _let) {
  return move_array(array_map_bit_not(_let->value.array_type));
}

THICC_NODISCARD Let* object_bit_not(Let* _let) {
  Let* property_name = let_string("!");
  Let* property		= member(_let, property_name);
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

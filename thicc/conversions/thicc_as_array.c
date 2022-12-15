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

#include "thicc_as_array.h"
#include "../core/thicc_interface.h"
#include "../core/thicc_struct_object.h"
#include "../core/thicc_struct_var.h"
#include "../utility/thicc_array.h"
#include "../utility/thicc_object.h"

THICC_NODISCARD MutableArray boolean_as_array(Let _let) {
  return array_from_elements(1, &_let);
}

THICC_NODISCARD MutableArray character_as_array(Let _let) {
  return array_from_elements(1, &_let);
}

THICC_NODISCARD MutableArray natural_as_array(Let _let) {
  return array_from_elements(1, &_let);
}

THICC_NODISCARD MutableArray integer_as_array(Let _let) {
  return array_from_elements(1, &_let);
}

THICC_NODISCARD MutableArray real_as_array(Let _let) {
  return array_from_elements(1, &_let);
}

THICC_NODISCARD MutableArray complex_as_array(Let _let) {
  return array_from_elements(1, &_let);
}

THICC_NODISCARD MutableArray string_as_array(Let _let) {
  return array_from_elements(1, &_let);
}

THICC_NODISCARD MutableArray function_as_array(Let _let) {
  return array_from_elements(1, &_let);
}

THICC_NODISCARD MutableArray array_as_array(Let _let) {
  return array_copy(array_view(_let));
}

THICC_NODISCARD MutableArray object_as_array(Let _let) {
  Let conversion_value = member(_let, move_string("array_type"));
  if (!let_is_empty(conversion_value)) {
	if (is_invokable(conversion_value)) {
	  Let		   temporary = object_method_invoke(_let, conversion_value, 2, &_let);
	  MutableArray result	 = as_array(temporary);

	  unlet_if_required(temporary);

	  return result;
	} else {
	  MutableArray result = as_array(conversion_value);

	  unlet_if_required(conversion_value);

	  return result;
	}
  }

  unlet_if_required(conversion_value);

  if (object_size(object_view(_let)) > 0)
	return array_copy(root_values(_let));

  return 0;
}

#ifdef __cplusplus
}
#endif

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

#include "thicc_as_array.h"
#include "../core/thicc_struct_object.h"
#include "../utility/thicc_array.h"
#include "../utility/thicc_object.h"
#include <thicc_interface.h>

THICC_NODISCARD MutableArray boolean_as_array(Let* _let) {
  return array_from_elements(1, _let);
}

THICC_NODISCARD MutableArray character_as_array(Let* _let) {
  return array_from_elements(1, _let);
}

THICC_NODISCARD MutableArray natural_as_array(Let* _let) {
  return array_from_elements(1, _let);
}

THICC_NODISCARD MutableArray integer_as_array(Let* _let) {
  return array_from_elements(1, _let);
}

THICC_NODISCARD MutableArray real_as_array(Let* _let) {
  return array_from_elements(1, _let);
}

THICC_NODISCARD MutableArray complex_as_array(Let* _let) {
  return array_from_elements(1, _let);
}

THICC_NODISCARD MutableArray string_as_array(Let* _let) {
  return array_from_elements(1, _let);
}

THICC_NODISCARD MutableArray function_as_array(Let* _let) {
  return array_from_elements(1, _let);
}

THICC_NODISCARD MutableArray array_as_array(Let* _let) {
  return array_copy(_let->value.array_type);
}

THICC_NODISCARD MutableArray object_as_array(Let* _let) {
  Let* key				= let_string("array");
  Let* conversion_value = member(_let, key);
  unlet(key);
  if (!let_is_empty(conversion_value)) {
	if (is_invokable(conversion_value)) {
	  Let*		   temporary = object_method_invoke(_let, conversion_value, 0);
	  MutableArray result	 = as_array(temporary);

	  unlet(temporary);

	  return result;
	} else {
	  MutableArray result = as_array(conversion_value);

	  unlet(conversion_value);

	  return result;
	}
  }

  unlet(conversion_value);

  if (object_size(object_view(_let)) > 0)
	return array_copy(root_values(_let));

  return array_empty();
}

#ifdef __cplusplus
}
#endif

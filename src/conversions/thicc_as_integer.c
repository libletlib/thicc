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

#include "thicc_as_integer.h"
#include <thicc_interface.h>
#include "../core/thicc_struct_object.h"
#include "../utility/thicc_function.h"
#include "../utility/thicc_object.h"
#include "../utility/thicc_string.h"

THICC_NODISCARD MutableInteger boolean_as_integer(Let* _let) {
#if THICC_C89
  return _let->value.boolean_type ? 1l : 0l;
#else
  return _let->value.boolean_type ? 1ll : 0ll;
#endif
}

THICC_NODISCARD MutableInteger character_as_integer(Let* _let) {
  return (Integer) _let->value.character_type;
}

THICC_NODISCARD MutableInteger natural_as_integer(Let* _let) {
  return (Integer) _let->value.natural_type;
}

THICC_NODISCARD MutableInteger integer_as_integer(Let* _let) {
  return _let->value.integer_type;
}

THICC_NODISCARD MutableInteger real_as_integer(Let* _let) {
  return (Integer) _let->value.real_type;
}

THICC_NODISCARD MutableInteger complex_as_integer(Let* _let) {
  return (Integer) _let->value.complex_type.real;
}

THICC_NODISCARD MutableInteger string_as_integer(Let* _let) {
  return string_to_integer(_let->value.string_type);
}

THICC_NODISCARD MutableInteger function_as_integer(Let* _let) {
  Let*	  temporary = function_invoke(_let, let_empty());
  Integer result	= as_integer(temporary);
  unlet(temporary);
  return result;
}

THICC_NODISCARD MutableInteger array_as_integer(Let* _let) {
  return as_integer(*array_view(_let));
}

THICC_NODISCARD MutableInteger object_as_integer(Let* _let) {
  Let* key = let_string("integer");
  Let* conversion_value = member(_let, key);
  unlet(key);
  if (!let_is_empty(conversion_value)) {
	if (is_invokable(conversion_value)) {
	  Let*	  temporary = object_method_invoke(_let, conversion_value, 0);
	  Integer result	= as_integer(temporary);

	  unlet(temporary);

	  return result;
	} else {
	  Integer result = as_integer(conversion_value);

	  unlet(conversion_value);

	  return result;
	}
  }

  unlet(conversion_value);

  if (object_size(object_view(_let)) > 0)
	return as_integer(array_view(array_view(((Root) object_view(_let))->members)[1])[0]);

  return 0;
}

#ifdef __cplusplus
}
#endif

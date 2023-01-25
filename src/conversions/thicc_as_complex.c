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

#include "thicc_as_complex.h"
#include "../core/thicc_struct_object.h"
#include "../utility/thicc_function.h"
#include "../utility/thicc_object.h"
#include "../utility/thicc_string.h"
#include <thicc_interface.h>

THICC_NODISCARD MutableComplex boolean_as_complex(Let* _let) {
  return _let->value.boolean_type ? cmplx(1.0l, 0.0l) : cmplx(0.0l, 0.0l);
}

THICC_NODISCARD MutableComplex character_as_complex(Let* _let) {
  return cmplx(as_real(_let), 0.0l);
}

THICC_NODISCARD MutableComplex natural_as_complex(Let* _let) {
  return cmplx(as_real(_let), 0.0l);
}

THICC_NODISCARD MutableComplex integer_as_complex(Let* _let) {
  return cmplx(as_real(_let), 0.0l);
}

THICC_NODISCARD MutableComplex real_as_complex(Let* _let) {
  return cmplx(as_real(_let), 0.0l);
}

THICC_NODISCARD MutableComplex complex_as_complex(Let* _let) {
  return _let->value.complex_type;
}

THICC_NODISCARD MutableComplex string_as_complex(Let* _let) {
  return string_to_complex(_let->value.string_type);
}

THICC_NODISCARD MutableComplex function_as_complex(Let* _let) {
  Let*	  temporary = function_invoke(_let, let_empty());
  Complex result	= as_complex(temporary);
  unlet(temporary);
  return result;
}

THICC_NODISCARD MutableComplex array_as_complex(Let* _let) {
  return as_complex(*array_view(_let));
}

THICC_NODISCARD MutableComplex object_as_complex(Let* _let) {
  Let* key				= let_string("complex");
  Let* conversion_value = member(_let, key);
  unlet(key);
  if (!let_is_empty(conversion_value)) {
	if (is_invokable(conversion_value)) {
	  Let*	  temporary = object_method_invoke(_let, conversion_value, 0);
	  Complex result	= as_complex(temporary);
	  unlet(temporary);

	  return result;
	} else {
	  Complex result = as_complex(conversion_value);
	  unlet(conversion_value);

	  return result;
	}
  }

  unlet(conversion_value);

  if (object_size(object_view(_let)) > 0)
	return as_complex(array_view(array_view(((Root) object_view(_let))->members)[1])[0]);

  return cmplx(0, 0);
}

#ifdef __cplusplus
}
#endif

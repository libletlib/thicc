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

#include "../include/thicc.h"
#include <assert.h>

THICC_NODISCARD static function(foo) {
  return let_integer(1);
}

THICC_NODISCARD static int conversions(void) {
  Let value		 = let_integer(1);
  Let comparable = let_integer(1);

  Let string			= move_string(as_string(value));
  Let comparison_array	= array_of(1, &comparable);
  Let array				= array_of(1, &value);
  Let object			= let_object(as_object(value));
  Let comparison_object = let_object(THICC_NAUGHT);

  assert(equal(cast(value, boolean_rank), let_boolean(THICC_YES)));
  assert(equal(cast(value, character_rank), let_character(1)));
  assert(equal(cast(value, natural_rank), let_natural(1)));
  assert(equal(value, let_integer(1)));
  assert(equal(value, let_real(1)));
  assert(equal(value, let_complex(cmplx(1, 0))));
  assert(equal(string, move_string(string_literal("1"))));
  assert(equal(value, let_function(foo)));
  assert(equal(array, comparison_array));
  assert(equal(object, comparison_object));

  unlet(string);
  unlet(array);
  unlet(comparison_array);
  unlet(object);
  unlet(comparison_object);

  return 1;
}

THICC_NODISCARD static int operations(void) {
  Let left	= let_integer(1);
  Let right = let_integer(1);

  assert(equal(bit_and(left, right), let_integer(1 & 1)));
  assert(equal(bit_complement(left), let_integer(~1)));
  assert(equal(bit_not(left), let_boolean(THICC_NO)));
  assert(equal(bit_or(left, right), let_integer(1 | 1)));
  assert(equal(bit_xor(left, right), let_integer(1 ^ 1)));
  assert(compare(left, right) == THICC_EQUAL);
  assert(equal(difference(left, right), let_integer(0)));
  assert(equal(index_of(left, let_integer(0)), let_integer(1)));
  assert(equal(indirection(left), let_integer(1)));
  assert(equal(modulo(left, right), let_integer(0)));
  assert(equal(negative(left), let_integer(-1)));
  assert(equal(positive(left), let_integer(1)));
  assert(equal(product(left, right), move_string(string_literal("1"))));
  assert(equal(quotient(left, right), let_integer(1)));
  assert(equal(sum(left, right), let_integer(2)));

  return 1;
}

THICC_NODISCARD int integer_test(void) {
  assert(conversions());
  assert(operations());
  return 1;
}

#ifdef __cplusplus
}
#endif

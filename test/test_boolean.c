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

#include "test.h"

THICC_NODISCARD static function(foo) {
  return let_boolean(THICC_YES);
}

THICC_NODISCARD static int conversions(void) {
  Let value = let_boolean(THICC_YES);

  Let string			= move_string(as_string(value));
  Let character			= let_character('1');
  Let comparison_array	= array_of(1, &character);
  Let array				= array_of(1, &value);
  Let object			= let_object(as_object(value));
  Let comparison_object = let_object(THICC_NAUGHT);

  assert(equal(value, let_boolean(THICC_YES)));
  assert(equal(value, let_character('1')));
  assert(equal(value, let_natural(1)));
  assert(equal(value, let_integer(1)));
  assert(equal(value, let_real(1.0)));
  assert(equal(value, let_complex(cmplx(1.0, 0.0))));
  assert(equal(string, move_string(string_literal("true"))));
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
  Let left	= let_boolean(THICC_YES);
  Let right = let_boolean(THICC_YES);
  Let yes	= let_boolean(THICC_YES);
  Let no	= let_boolean(THICC_NO);

  assert(equal(bit_and(left, right), yes));
  assert(equal(bit_complement(left), no));
  assert(equal(bit_not(left), no));
  assert(equal(bit_or(left, right), yes));
  assert(equal(bit_xor(left, right), no));
  assert(compare(left, right) == THICC_EQUAL);
  assert(equal(difference(left, right), no));
  assert(equal(index_of(left, let_integer(0)), yes));
  assert(equal(indirection(left), yes));
  assert(equal(modulo(left, right), yes));
  assert(equal(negative(left), no));
  assert(equal(positive(left), yes));
  assert(equal(product(left, right), yes));
  assert(equal(quotient(left, right), yes));
  assert(equal(sum(left, right), yes));

  return 1;
}

THICC_NODISCARD int boolean_test(void) {
  assert(conversions());
  assert(operations());
  return 1;
}

#ifdef __cplusplus
}
#endif

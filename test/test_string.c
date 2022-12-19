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
  return move_string(string_literal("1"));
}

THICC_NODISCARD static int conversions(void) {
  Let value		 = move_string(string_literal("1"));
  Let comparable = move_string(string_literal("1"));

  Let string			= move_string(as_string(value));
  Let comparison_array	= array_of(1, &comparable);
  Let array				= array_of(1, &value);
  Let object			= let_object(as_object(value));
  Let comparison_object = let_object(THICC_NAUGHT);

  assert(equal(cast(value, character_rank), let_character('1')));
  assert(equal(cast(value, natural_rank), let_natural(1)));
  assert(equal(cast(value, integer_rank), let_integer(1)));
  assert(equal(cast(value, real_rank), let_real(1)));
  assert(equal(cast(value, complex_rank), let_complex(cmplx(1, 0))));
  assert(equal(value, move_string(string_literal("1"))));
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
  Let left	= move_string(string_literal("1"));
  Let right = move_string(string_literal("1"));

  Let bit_and_string	= bit_and(left, right);
  Let bit_or_string		= bit_or(left, right);
  Let bit_xor_string	= bit_xor(left, right);
  Let difference_string = difference(left, right);
  Let modulo_string		= modulo(left, right);
  Let token_array		= array_of(0);
  Let positive_string	= positive(left);
  Let product_string	= product(left, right);
  Let quotient_string	= quotient(left, right);
  Let sum_string		= sum(left, right);

  assert(equal(bit_and_string, move_string(string_literal("1"))));
  /*assert(equal(bit_complement(left), let_integer(~'1')));*/
  assert(equal(bit_not(left), let_boolean(THICC_NO)));
  assert(equal(bit_or_string, move_string(string_literal(""))));
  assert(equal(bit_xor_string, move_string(string_literal(""))));
  assert(compare(left, right) == THICC_EQUAL);
  assert(equal(difference_string, move_string(string_literal(""))));
  assert(equal(index_of(left, let_integer(0)), let_character('1')));
  assert(equal(indirection(left), let_character('1')));
  assert(equal(modulo_string, token_array));
  /*assert(equal(negative(left), let_integer(-1)));*/
  assert(equal(positive_string, move_string(string_literal("1"))));
  assert(equal(product_string, move_string(string_literal("11"))));
  assert(equal(quotient_string, move_string(string_literal(""))));
  assert(equal(sum_string, move_string(string_literal("11"))));

  unlet(bit_and_string);
  unlet(bit_or_string);
  unlet(bit_xor_string);
  unlet(difference_string);
  unlet(modulo_string);
  unlet(token_array);
  unlet(positive_string);
  unlet(product_string);
  unlet(quotient_string);
  unlet(sum_string);
  return 1;
}

THICC_NODISCARD int string_test(void) {
  assert(conversions());
  assert(operations());
  return 1;
}

#ifdef __cplusplus
}
#endif

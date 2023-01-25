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

#include "test.h"

THICC_NODISCARD static THICC_FUNCTION(foo) {
  return let_natural(1);
}

THICC_NODISCARD static int conversions(void) {
  Let* value		 = let_natural(1);
  Let* comparable = let_natural(1);

  Let* string			= move_string(as_string(value));
  Let* array			= array_of(1, value);
  Let* object			= move_object(as_object(value));
  Let* key = let_string("natural");

  Let* boolean_one = let_boolean(THICC_YES);
  Let* character_one = let_character(1);
  Let* natural_one	= let_natural(1);
  Let* integer_one	= let_integer(1);
  Let* real_one		= let_real(1);
  Let* complex_one	= let_complex(cmplx(1, 0.0));
  Let* string_one	= let_string("1");
  Let* function_one = let_function(foo);
  Let* function_one_return = call(function_one);
  Let* array_one			= array_of(1, comparable);
  Let* object_one = object_of(2, key, value);

  Let* boolean_cast = cast(value, boolean_rank);
  Let* character_cast = cast(value, character_rank);

  assert(equal(boolean_cast, boolean_one));
  assert(equal(character_cast, character_one));
  assert(equal(value, natural_one));
  assert(equal(value, integer_one));
  assert(equal(value, real_one));
  assert(equal(value, complex_one));
  assert(equal(string, string_one));
  assert(equal(value, function_one_return));
  assert(equal(array, array_one));
  assert(equal(object, object_one));

  unlet(boolean_cast);
  unlet(character_cast);

  unlet(boolean_one);
  unlet(character_one);
  unlet(natural_one);
  unlet(integer_one);
  unlet(real_one);
  unlet(complex_one);
  unlet(string_one);
  unlet(function_one);
  unlet(function_one_return);
  unlet(array_one);
  unlet(object_one);

  unlet(key);
  unlet(string);
  unlet(array);
  unlet(object);

  unlet(value);
  unlet(comparable);

  return 1;
}

THICC_NODISCARD static int operations(void) {
  Let* left	= let_natural(1);
  Let* right = let_natural(1);
  Let* zero = let_natural(0);

  Let* bit_and_result = bit_and(left, right);
  Let* bit_complement_result = bit_complement(left);
  Let* bit_not_result = bit_not(left);
  Let* bit_or_result = bit_or(left, right);
  Let* bit_xor_result = bit_xor(left, right);
  Let* difference_result = difference(left, right);
  Let* index_of_result = index_of(left, zero);
  Let* indirection_result = indirection(left);
  Let* modulo_result = modulo(left, right);
  Let* negative_result = negative(left);
  Let* positive_result = positive(left);
  Let* product_result = product(left, right);
  Let* quotient_result = quotient(left, right);
  Let* sum_result = sum(left, right);

  Let* bit_and_validation = let_natural(1 & 1);
  Let* bit_complement_validation = let_natural(~1);
  Let* bit_not_validation = let_boolean(THICC_NO);
  Let* bit_or_validation = let_natural(1 | 1);
  Let* bit_xor_validation = let_natural(1 ^ 1);
  Let* difference_validation = let_natural(0);
  Let* index_of_validation = let_natural(1);
  Let* indirection_validation = let_natural(1);
  Let* modulo_validation = let_natural(0);
  Let* negative_validation = let_integer(-1);
  Let* positive_validation = let_natural(1);
  Let* product_validation = let_natural(1);
  Let* quotient_validation = let_natural(1);
  Let* sum_validation = let_natural(2);

  assert(equal(bit_and_result, bit_and_validation));
  assert(equal(bit_complement_result, bit_complement_validation));
  assert(equal(bit_not_result, bit_not_validation));
  assert(equal(bit_or_result, bit_or_validation));
  assert(equal(bit_xor_result, bit_xor_validation));
  assert(compare(left, right) == THICC_EQUAL);
  assert(equal(difference_result, difference_validation));
  assert(equal(index_of_result, index_of_validation));
  assert(equal(indirection_result, indirection_validation));
  assert(equal(modulo_result, modulo_validation));
  assert(equal(negative_result, negative_validation));
  assert(equal(positive_result, positive_validation));
  assert(equal(product_result, product_validation));
  assert(equal(quotient_result, quotient_validation));
  assert(equal(sum_result, sum_validation));

  unlet(sum_result);
  unlet(sum_validation);
  unlet(quotient_result);
  unlet(quotient_validation);
  unlet(product_result);
  unlet(product_validation);
  unlet(positive_result);
  unlet(positive_validation);
  unlet(negative_result);
  unlet(negative_validation);
  unlet(modulo_result);
  unlet(modulo_validation);
  unlet(indirection_result);
  unlet(indirection_validation);
  unlet(index_of_result);
  unlet(index_of_validation);
  unlet(difference_result);
  unlet(difference_validation);
  unlet(bit_xor_result);
  unlet(bit_xor_validation);
  unlet(bit_or_result);
  unlet(bit_or_validation);
  unlet(bit_not_result);
  unlet(bit_not_validation);
  unlet(bit_complement_result);
  unlet(bit_complement_validation);
  unlet(bit_and_result);
  unlet(bit_and_validation);

  unlet(left);
  unlet(right);
  unlet(zero);
  return 1;
}

THICC_NODISCARD int natural_test(void) {
  assert(conversions());
  assert(operations());
  return 1;
}

#ifdef __cplusplus
}
#endif

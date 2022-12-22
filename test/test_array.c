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

THICC_NODISCARD static THICC_FUNCTION(foo) {
  Let foo_element = let_integer(1);
  return array_of(1, &foo_element);
}

THICC_NODISCARD static int conversions(void) {
  Let value_element = let_integer(1);
  Let value			= array_of(1, &value_element);
  Let comparable	= array_of(1, &value_element);

  Let string			= move_string(as_string(value));
  Let function_return	= call(let_function(foo));
  Let object			= move_object(as_object(value));
  Let key = weak_string("array");
  Let comparison_object = object_of(2, &key, &value);

  assert(equal(cast(value, boolean_rank), let_boolean(THICC_YES)));
  assert(equal(cast(value, character_rank), let_character(1)));
  assert(equal(cast(value, natural_rank), let_natural(1)));
  assert(equal(cast(value, integer_rank), let_integer(1)));
  assert(equal(cast(value, real_rank), let_real(1)));
  assert(equal(cast(value, complex_rank), let_complex(cmplx(1, 0))));
  assert(equal(string, weak_string("[1]")));
  assert(equal(value, function_return));
  assert(equal(value, comparable));
  assert(equal(object, comparison_object));

  unlet(value);
  unlet(comparable);
  unlet(string);
  unlet(function_return);
  unlet(object);
  unlet(comparison_object);

  return 1;
}

THICC_NODISCARD static int operations(void) {
  Let left_element	= let_integer(1);
  Let right_element = weak_string("1");
  Let left			= array_of(1, &left_element);
  Let right			= array_of(1, &right_element);

  Let bit_and_array	   = bit_and(left, right);
  Let bit_not_array	   = bit_not(left);
  Let bit_or_array	   = bit_or(left, right);
  Let bit_xor_array	   = bit_xor(left, right);
  Let difference_array = difference(left, right);
  Let positive_array   = positive(left);
  Let product_array	   = product(left, right);
  Let quotient_array   = quotient(left, right);
  Let sum_array		   = sum(left, right);

  Let sum_array_result = array_of(2, &left_element, &right_element);
  Let empty_array	   = array_of(0);

  assert(equal(bit_and_array, left_element));
  /*assert(equal(bit_complement(left), let_integer(~1)));*/
  assert(equal(bit_not_array, let_boolean(THICC_NO)));
  assert(equal(bit_or_array, empty_array));
  assert(equal(bit_xor_array, empty_array));
  assert(compare(left, right) == THICC_EQUAL);
  assert(equal(difference_array, left));
  assert(equal(index_of(left, let_integer(0)), let_integer(1)));
  assert(equal(indirection(left), let_integer(1)));
  /*assert(equal(modulo(left, right), let_integer(0)));
  assert(equal(negative(left), let_integer(-1)));*/
  assert(equal(positive_array, left_element));
  assert(equal(product_array, sum_array));
  assert(equal(quotient_array, empty_array));
  assert(equal(sum_array, sum_array));

  unlet(left);
  unlet(right);

  unlet(bit_and_array);
  unlet(bit_not_array);
  unlet(bit_or_array);
  unlet(bit_xor_array);
  unlet(difference_array);
  unlet(positive_array);
  unlet(product_array);
  unlet(quotient_array);
  unlet(sum_array);

  unlet(sum_array_result);
  unlet(empty_array);

  return 1;
}

THICC_NODISCARD int array_test(void) {
  assert(conversions());
  assert(operations());
  return 1;
}

#ifdef __cplusplus
}
#endif

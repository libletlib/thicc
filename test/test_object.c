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

MutableArray root_values(Let*);

THICC_NODISCARD static int conversions(void) {
  Let* value_element = let_integer(1);
  Let* value_name	= let_string("integer");
  Let* value		= object_of(2, value_name, value_element);
  Let* comparable	= object_of(2, value_name, value_element);

  Let* boolean_one = let_boolean(THICC_YES);
  Let* character_one = let_character(1);
  Let* natural_one	= let_natural(1);
  Let* integer_one	= let_integer(1);
  Let* real_one		= let_real(1);
  Let* complex_one	= let_complex(cmplx(1, 0.0));
  Let* string_one	= let_string("{\n\t\"integer\": 1\n}");
  Let* array_one	= array_of(1, value);
  Let* object_one = object_of(2, value_name, value_element);

  Let* boolean_cast = cast(value, boolean_rank);
  Let* character_cast = cast(value, character_rank);
  Let* natural_cast = cast(value, natural_rank);
  Let* integer_cast = cast(value, integer_rank);
  Let* real_cast = cast(value, real_rank);
  Let* complex_cast = cast(value, complex_rank);
  Let* string_cast = cast(value, string_rank);
  Let* array_cast = cast(value, array_rank);

  assert(equal(boolean_cast, boolean_one));
  assert(equal(character_cast, character_one));
  assert(equal(natural_cast, natural_one));
  assert(equal(integer_cast, integer_one));
  assert(equal(real_cast, real_one));
  assert(equal(complex_cast, complex_one));
  assert(equal(string_cast, string_one));
  assert(equal(array_cast, array_one));
  assert(equal(value, object_one));

  unlet(boolean_cast);
  unlet(character_cast);
  unlet(natural_cast);
  unlet(integer_cast);
  unlet(real_cast);
  unlet(complex_cast);
  unlet(string_cast);
  unlet(array_cast);

  unlet(boolean_one);
  unlet(character_one);
  unlet(natural_one);
  unlet(integer_one);
  unlet(real_one);
  unlet(complex_one);
  unlet(string_one);
  unlet(array_one);
  unlet(object_one);

  unlet(value);
  unlet(comparable);
  unlet(value_element);
  unlet(value_name);

  return 1;
}

THICC_NODISCARD static THICC_FUNCTION(bi_operator) {
  Let* index	= let_integer(0);
  Let* left	    = index_of(args, index);
  Let* right	= index_of(args, index);
  Let* result   = let_integer(as_integer(left) + as_integer(right));
  unlet(index);
  unlet(left);
  unlet(right);
  return result;
}

THICC_NODISCARD static THICC_FUNCTION(mono_operator) {
  Let* index  = let_integer(0);
  Let* object = index_of(args, index);
  Let* result = let_integer(as_integer(object) * 2);
  unlet(index);
  unlet(object);
  return result;
}

THICC_NODISCARD static int operations(void) {
  Let* value	  = let_integer(1);
  Let* bi_op	  = let_function(bi_operator);
  Let* mono_op    = let_function(mono_operator);

  Let* value_key	      = let_string("integer");
  Let* bit_and_key		  = let_string("&");
  Let* bit_complement_key = let_string("~");
  Let* bit_not_key		  = let_string("!");
  Let* bit_or_key		  = let_string("|");
  Let* bit_xor_key		  = let_string("^");
  Let* comparison_key	  = let_string("<=>");
  Let* difference_key	  = let_string("-");
  Let* index_of_key		  = let_string("[]");
  Let* indirection_key	  = let_string("indirection");
  Let* modulo_key		  = let_string("%");
  Let* negative_key		  = let_string("negative");
  Let* positive_key		  = let_string("positive");
  Let* product_key		  = let_string("*");
  Let* quotient_key		  = let_string("+");
  Let* sum_key			  = let_string("/");

  Let* object = object_of(32,
						 value_key,
						 value,
						 bit_and_key,
						 bi_op,
						 bit_complement_key,
						 mono_op,
						 bit_not_key,
						 mono_op,
						 bit_or_key,
						 bi_op,
						 bit_xor_key,
						 bi_op,
						 comparison_key,
						 bi_op,
						 difference_key,
						 bi_op,
						 index_of_key,
						 bi_op,
						 indirection_key,
						 mono_op,
						 modulo_key,
						 bi_op,
						 negative_key,
						 mono_op,
						 positive_key,
						 mono_op,
						 product_key,
						 bi_op,
						 quotient_key,
						 bi_op,
						 sum_key,
						 bi_op);

  Let* result = let_integer(2);

  Let* bit_and_result = bit_and(object, object);
  Let* bit_complement_result = bit_complement(object);
  Let* bit_not_result = bit_not(object);
  Let* bit_or_result = bit_or(object, object);
  Let* bit_xor_result = bit_xor(object, object);
  Let* compare_result = let_integer(compare(object, object));
  Let* difference_result = difference(object, object);
  Let* index_of_result = index_of(object, object);
  Let* indirection_result = indirection(object);
  Let* modulo_result = modulo(object, object);
  Let* negative_result = negative(object);
  Let* positive_result = positive(object);
  Let* product_result = product(object, object);
  Let* quotient_result = quotient(object, object);
  Let* sum_result = sum(object, object);

  assert(equal(bit_and_result, result));
  assert(equal(bit_complement_result, result));
  assert(equal(bit_not_result, result));
  assert(equal(bit_or_result, result));
  assert(equal(bit_xor_result, result));
  assert(equal(compare_result, result));
  assert(equal(difference_result, result));
  assert(equal(index_of_result, result));
  assert(equal(indirection_result, result));
  assert(equal(modulo_result, result));
  assert(equal(negative_result, result));
  assert(equal(positive_result, result));
  assert(equal(product_result, result));
  assert(equal(quotient_result, result));
  assert(equal(sum_result, result));

  unlet(bit_and_result);
  unlet(bit_complement_result);
  unlet(bit_not_result);
  unlet(bit_or_result);
  unlet(bit_xor_result);
  unlet(compare_result);
  unlet(difference_result);
  unlet(index_of_result);
  unlet(indirection_result);
  unlet(modulo_result);
  unlet(negative_result);
  unlet(positive_result);
  unlet(product_result);
  unlet(quotient_result);
  unlet(sum_result);

  unlet(value);
  unlet(bi_op);
  unlet(mono_op);

  unlet(value_key);
  unlet(bit_and_key);
  unlet(bit_complement_key);
  unlet(bit_not_key);
  unlet(bit_or_key);
  unlet(bit_xor_key);
  unlet(comparison_key);
  unlet(difference_key);
  unlet(index_of_key);
  unlet(indirection_key);
  unlet(modulo_key);
  unlet(negative_key);
  unlet(positive_key);
  unlet(product_key);
  unlet(quotient_key);
  unlet(sum_key);

  unlet(object);
  unlet(result);

  return 1;
}

THICC_NODISCARD int object_test(void) {
  assert(conversions());
  assert(operations());
  return 1;
}

#ifdef __cplusplus
}
#endif

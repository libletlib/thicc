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
#include "../thicc/core/thicc_struct_object.h"
#include <assert.h>

THICC_NODISCARD static int conversions(void) {
  Let value_element = let_integer(1);
  Let value_name	= move_string("integer_type");
  Let value			= object_of(2, &value_name, &value_element);
  Let comparable	= object_of(2, &value_name, &value_element);

  Let string		   = cast(value, string_rank);
  Let array			   = cast(value, array_rank);
  Let array_comparable = let_array(root_values(value));

  assert(equal(cast(value, boolean_rank), let_boolean(THICC_YES)));
  assert(equal(cast(value, character_rank), let_character(1)));
  assert(equal(cast(value, natural_rank), let_natural(1)));
  assert(equal(cast(value, integer_rank), let_integer(1)));
  assert(equal(cast(value, real_rank), let_real(1)));
  assert(equal(cast(value, complex_rank), let_complex(cmplx(1, 0))));
  assert(equal(string, move_string("{\n\t\"integer_type\": 1\n}")));
  assert(equal(cast(value, function_rank), let_function(empty_function)));
  assert(equal(array, array_comparable));
  assert(equal(value, comparable));

  unlet(value);
  unlet(comparable);
  unlet(string);
  unlet(array);
  unlet(array_comparable);

  return 1;
}

THICC_NODISCARD static function(bi_operator) {
  Let index	 = let_integer(0);
  Let left	 = index_of(args, index);
  Let right	 = index_of(args, index);
  Let result = let_integer(as_integer(left) + as_integer(right));
  unlet(left);
  unlet(right);
  return result;
}

THICC_NODISCARD static function(mono_operator) {
  Let index	 = let_integer(0);
  Let object = index_of(args, index);
  Let result = let_integer(as_integer(object) * 2);
  unlet(object);
  return result;
}

THICC_NODISCARD static int operations(void) {
  Let value	  = let_integer(1);
  Let bi_op	  = let_function(bi_operator);
  Let mono_op = let_function(mono_operator);

  Let value_key			 = move_string("integer_type");
  Let bit_and_key		 = move_string("&");
  Let bit_complement_key = move_string("~");
  Let bit_not_key		 = move_string("!");
  Let bit_or_key		 = move_string("|");
  Let bit_xor_key		 = move_string("^");
  Let comparison_key	 = move_string("<=>");
  Let difference_key	 = move_string("-");
  Let index_of_key		 = move_string("[]");
  Let indirection_key	 = move_string("indirection");
  Let modulo_key		 = move_string("%");
  Let negative_key		 = move_string("negative");
  Let positive_key		 = move_string("positive");
  Let product_key		 = move_string("*");
  Let quotient_key		 = move_string("+");
  Let sum_key			 = move_string("/");

  Let object = object_of(32,
						 &value_key,
						 &value,
						 &bit_and_key,
						 &bi_op,
						 &bit_complement_key,
						 &mono_op,
						 &bit_not_key,
						 &mono_op,
						 &bit_or_key,
						 &bi_op,
						 &bit_xor_key,
						 &bi_op,
						 &comparison_key,
						 &bi_op,
						 &difference_key,
						 &bi_op,
						 &index_of_key,
						 &bi_op,
						 &indirection_key,
						 &mono_op,
						 &modulo_key,
						 &bi_op,
						 &negative_key,
						 &mono_op,
						 &positive_key,
						 &mono_op,
						 &product_key,
						 &bi_op,
						 &quotient_key,
						 &bi_op,
						 &sum_key,
						 &bi_op);

  Let result = let_integer(2);

  assert(equal(bit_and(object, object), result));
  assert(equal(bit_complement(object), result));
  assert(equal(bit_not(object), result));
  assert(equal(bit_or(object, object), result));
  assert(equal(bit_xor(object, object), result));
  assert(equal(let_integer(compare(object, object)), result));
  assert(equal(difference(object, object), result));
  assert(equal(index_of(object, object), result));
  assert(equal(indirection(object), result));
  assert(equal(modulo(object, object), result));
  assert(equal(negative(object), result));
  assert(equal(positive(object), result));
  assert(equal(product(object, object), result));
  assert(equal(quotient(object, object), result));
  assert(equal(sum(object, object), result));

  unlet(object);

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

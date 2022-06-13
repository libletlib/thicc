/*
 * TTTTTTTTTTTTTTTTTTTTTTThhhhhhh               iiii                              CCCCCCCCCCCCC
 * T:::::::::::::::::::::Th:::::h              i::::i                          CCC::::::::::::C
 * T:::::::::::::::::::::Th:::::h               iiii                         CC:::::::::::::::C
 * T:::::TT:::::::TT:::::Th:::::h                                           C:::::CCCCCCCC::::C
 * TTTTTT  T:::::T  TTTTTT h::::h hhhhh       iiiiiii     cccccccccccccccc C:::::C       CCCCCC
 *         T:::::T         h::::hh:::::hhh    i:::::i   cc:::::::::::::::cC:::::C
 *         T:::::T         h::::::::::::::hh   i::::i  c:::::::::::::::::cC:::::C
 *         T:::::T         h:::::::hhh::::::h  i::::i c:::::::cccccc:::::cC:::::C
 *         T:::::T         h::::::h   h::::::h i::::i c::::::c     cccccccC:::::C
 *         T:::::T         h:::::h     h:::::h i::::i c:::::c             C:::::C
 *         T:::::T         h:::::h     h:::::h i::::i c:::::c             C:::::C
 *         T:::::T         h:::::h     h:::::h i::::i c::::::c     ccccccc C:::::C       CCCCCC
 *       TT:::::::TT       h:::::h     h:::::hi::::::ic:::::::cccccc:::::c  C:::::CCCCCCCC::::C
 *       T:::::::::T       h:::::h     h:::::hi::::::i c:::::::::::::::::c   CC:::::::::::::::C
 *       T:::::::::T       h:::::h     h:::::hi::::::i  cc:::::::::::::::c     CCC::::::::::::C
 *       TTTTTTTTTTT       hhhhhhh     hhhhhhhiiiiiiii    cccccccccccccccc        CCCCCCCCCCCCC
 *
 * Copyright 2021 - 2022 Ville Rissanen
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
 * following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following
 * disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 * following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifdef __cplusplus
extern "C"
{
#endif

#include "thicc.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>

	void test_boolean_casting(void);
	void test_character_casting(void);
	void test_signed_character_casting(void);
	void test_unsigned_character_casting(void);
	void test_short_casting(void);
	void test_unsigned_short_casting(void);
	void test_integer_casting(void);
	void test_unsigned_integer_casting(void);
	void test_long_casting(void);
	void test_unsigned_long_casting(void);
#if THICC_IF(THICC_C_AT_LEAST(1999))
	void test_long_long_casting(void);
	void test_unsigned_long_long_casting(void);
#endif
	void test_float_casting(void);
	void test_double_casting(void);
	void test_long_double_casting(void);
#if THICC_IF(THICC_HAS_STD_COMPLEX)
	void test_float_complex_casting(void);
	void test_double_complex_casting(void);
	void test_long_double_complex_casting(void);
#endif
	void test_string_casting(void);
	void test_subroutine_casting(void);
	void test_function_casting(void);
	void test_array_casting(void);
	void test_object_casting(void);

	void test_boolean_operation(void);
	void test_character_operation(void);
	void test_signed_character_operation(void);
	void test_unsigned_character_operation(void);
	void test_short_operation(void);
	void test_unsigned_short_operation(void);
	void test_integer_operation(void);
	void test_unsigned_integer_operation(void);
	void test_long_operation(void);
	void test_unsigned_long_operation(void);
#if THICC_IF(THICC_C_AT_LEAST(1999))
	void test_long_long_operation(void);
	void test_unsigned_long_long_operation(void);
#endif
	void test_float_operation(void);
	void test_double_operation(void);
	void test_long_double_operation(void);
#if THICC_IF(THICC_HAS_STD_COMPLEX)
	void test_float_complex_operation(void);
	void test_double_complex_operation(void);
	void test_long_double_complex_operation(void);
#endif
	void test_string_operation(void);
	void test_subroutine_operation(void);
	void test_function_operation(void);
	void test_array_operation(void);
	void test_object_operation(void);
	void test(void);

	MutableBoolean loose_equal(Double _left, Double _right) {
		Double absolute_left = fabs(_left), absolute_right = fabs(_right);
		return fabs(_left - _right)
		       <= ((absolute_left > absolute_right ? absolute_right : absolute_left)
		           * 0.000001);
	}

	void a_subroutine(MutableLet self, MutableLet args) {
		Let index = let_long(0l);
		Let text = let_string(as_string(index_of(args, index)));
		printf("%s", string_view(text));
		unlet(text);
	}

	MutableLet a_function(MutableLet self, MutableLet args) {
		Let index = let_long(0l);
		return index_of(args, index);
	}

	MutableLet foo_sum(MutableLet self, MutableLet args) {
		Let left = array_view(args)[0];
		Let right = array_view(args)[1];
		Let key = let_string("foo");
		Integer left_result = as_integer(member(left, key));
		Integer right_result = as_integer(member(right, key));
		unlet(key);
		return let_integer(left_result + right_result);
	}

	int main(void) {
		Let foo_key = let_string("foo");
		Let foo_value = let_integer(2);
		Let foo_sum_key = let_string("+");
		Let foo_sum_function = let_function(foo_sum);
		Let object1 = object_of(4, &foo_key, &foo_value, &foo_sum_key, &foo_sum_function);
		Let object2 = object_of(4, &foo_key, &foo_value, &foo_sum_key, &foo_sum_function);
		Let result = sum(object1, object2);

		printf("%f", as_double(root(let_character('2'), let_character('2'))));//, as_integer(result));

		test();
		unlet(object1);
		unlet(object2);
		unlet(foo_key);
		unlet(foo_value);
		unlet(foo_sum_key);
		unlet(foo_sum_function);
		unlet(result);
		return EXIT_SUCCESS;
	}

#undef THICC_INTEGER_TEST
#define THICC_INTEGER_TEST(TYPE, SUFFIX)                                                                               \
	void test_##TYPE##_operation(void)                                                                                 \
	{                                                                                                                  \
		MutableLet left  = let_##TYPE(2##SUFFIX);                                                                      \
		MutableLet right = let_##TYPE(2##SUFFIX);                                                                      \
		assert(equal(sum(left, right), let_##TYPE(4##SUFFIX)));                                                        \
		assert(equal(difference(left, right), let_##TYPE(0##SUFFIX)));                                                 \
		assert(equal(product(left, right), let_##TYPE(4##SUFFIX)));                                                    \
		assert(equal(quotient(left, right), let_##TYPE(1##SUFFIX)));                                                   \
		assert(equal(modulo(left, right), let_##TYPE(0##SUFFIX)));                                                     \
		assert(equal(power(left, right), let_##TYPE(4##SUFFIX)));                                                      \
		assert(loose_equal(as_double(root(left, right)), sqrt(2.0)));                                                  \
		assert(equal(logarithm(left, right), let_##TYPE(1##SUFFIX)));                                                  \
		assert(equal(negative(left), let_integer(-2)));                                                                \
		assert(equal(positive(left), let_##TYPE(2##SUFFIX)));                                                          \
		assert(equal(indirection(left), let_##TYPE(2##SUFFIX)));                                                       \
		assert(equal(bit_and(left, right), let_##TYPE(2##SUFFIX)));                                                    \
		assert(equal(bit_or(left, right), let_##TYPE(2##SUFFIX)));                                                     \
		assert(equal(bit_xor(left, right), let_##TYPE(0##SUFFIX)));                                                    \
		assert(equal(index_of(left, right), let_##TYPE(2##SUFFIX)));                                                   \
	}

#undef THICC_CHARACTER_TEST
#define THICC_CHARACTER_TEST(TYPE)                                                                                     \
	void test_##TYPE##_operation(void)                                                                                 \
	{                                                                                                                  \
		MutableLet left  = let_##TYPE('2');                                                                            \
		MutableLet right = let_##TYPE('2');                                                                            \
        Let sum_string = let_string("22");                                                                             \
		assert(equal(sum(left, right), sum_string));                                                                   \
		assert(equal(difference(left, right), let_##TYPE('0')));                                                       \
		assert(equal(product(left, right), let_##TYPE('4')));                                                          \
		assert(equal(quotient(left, right), let_##TYPE('1')));                                                         \
		assert(equal(modulo(left, right), let_##TYPE('0')));                                                           \
		assert(loose_equal(as_double(power(left, let_character('0'))), 1.0));                              		       \
		assert(loose_equal(as_double(root(left, right)), sqrt(2.0)));                                       		   \
		assert(equal(logarithm(left, right), let_##TYPE(1)));                                                          \
		assert(equal(negative(left), let_integer(-'2')));                                                              \
		assert(equal(positive(left), let_##TYPE('2')));                                                                \
		assert(equal(indirection(left), let_##TYPE('2')));                                                             \
		assert(equal(bit_and(left, right), let_##TYPE('2')));                                                          \
		assert(equal(bit_or(left, right), let_##TYPE('2')));                                                           \
		assert(equal(bit_xor(left, right), let_##TYPE('0')));                                                          \
		assert(equal(index_of(left, right), let_##TYPE('2')));                                                         \
	}

#undef THICC_FLOATING_TEST
#define THICC_FLOATING_TEST(TYPE, SUFFIX)                                                                              \
	void test_##TYPE##_operation(void)                                                                                 \
	{                                                                                                                  \
		MutableLet left  = let_##TYPE(2##SUFFIX);                                                                      \
		MutableLet right = let_##TYPE(2##SUFFIX);                                                                      \
		assert(equal(sum(left, right), let_##TYPE(4##SUFFIX)));                                                        \
		assert(equal(difference(left, right), let_##TYPE(0##SUFFIX)));                                                 \
		assert(equal(product(left, right), let_##TYPE(4##SUFFIX)));                                                    \
		assert(equal(quotient(left, right), let_##TYPE(1##SUFFIX)));                                                   \
		assert(equal(modulo(left, right), let_##TYPE(0##SUFFIX)));                                                     \
		assert(equal(power(left, right), let_##TYPE(4##SUFFIX)));                                                      \
		assert(loose_equal(as_double(root(left, right)), sqrt(2.0)));                                                  \
		assert(equal(logarithm(left, right), let_##TYPE(1##SUFFIX)));                                                  \
		assert(equal(negative(left), let_integer(-2)));                                                                \
		assert(equal(positive(left), let_##TYPE(2##SUFFIX)));                                                          \
		assert(equal(indirection(left), let_##TYPE(2##SUFFIX)));                                                       \
		/*assert(equal(bit_and(left, right), let_##TYPE(2##SUFFIX)));                                                  \
		assert(equal(bit_or(left, right), let_##TYPE(2##SUFFIX)));                                                     \
		assert(equal(bit_xor(left, right), let_##TYPE(0##SUFFIX)));                                                  */\
		assert(equal(index_of(left, right), let_##TYPE(2##SUFFIX)));                                                   \
	}

#undef THICC_COMPLEX_TEST
#define THICC_COMPLEX_TEST(TYPE, SUFFIX)                                                                               \
	void test_##TYPE##_operation(void)                                                                                 \
	{                                                                                                                  \
		MutableLet left  = let_##TYPE(2##SUFFIX);                                                                      \
		MutableLet right = let_##TYPE(2##SUFFIX);                                                                      \
		assert(equal(sum(left, right), let_##TYPE(4##SUFFIX)));                                                        \
		assert(equal(difference(left, right), let_##TYPE(0##SUFFIX)));                                                 \
		assert(equal(product(left, right), let_##TYPE(4##SUFFIX)));                                                    \
		assert(equal(quotient(left, right), let_##TYPE(1##SUFFIX)));                                                   \
		assert(equal(modulo(left, right), let_##TYPE(0##SUFFIX)));                                                     \
		assert(equal(power(left, right), let_##TYPE(4##SUFFIX)));                                                      \
		assert(loose_equal(as_double(root(left, right)), sqrt(2.0)));                                                  \
		assert(equal(logarithm(left, right), let_##TYPE(1##SUFFIX)));                                                  \
		assert(equal(negative(left), let_integer(-2)));                                                                \
		assert(equal(positive(left), let_##TYPE(2##SUFFIX)));                                                          \
		assert(equal(indirection(left), let_##TYPE(2##SUFFIX)));                                                       \
		/*assert(equal(bit_and(left, right), let_##TYPE(2##SUFFIX)));                                                  \
		assert(equal(bit_or(left, right), let_##TYPE(2##SUFFIX)));                                                     \
		assert(equal(bit_xor(left, right), let_##TYPE(0##SUFFIX)));                                                  */\
		assert(equal(index_of(left, right), let_##TYPE(2##SUFFIX)));                                                   \
	}


	THICC_CHARACTER_TEST(character)
	THICC_CHARACTER_TEST(signed_character)
	THICC_CHARACTER_TEST(unsigned_character)

	THICC_INTEGER_TEST(short, )
	THICC_INTEGER_TEST(unsigned_short, u)
	THICC_INTEGER_TEST(integer, )
	THICC_INTEGER_TEST(unsigned_integer, u)
	THICC_INTEGER_TEST(long, l)
	THICC_INTEGER_TEST(unsigned_long, ul)
#if THICC_IF(THICC_C_AT_LEAST(1999))
	THICC_INTEGER_TEST(long_long, ll)
	THICC_INTEGER_TEST(unsigned_long_long, ull)
#endif

	THICC_FLOATING_TEST(float, .0f)
	THICC_FLOATING_TEST(double, .0)
	THICC_FLOATING_TEST(long_double, .0l)

	void test(void) {
		test_character_casting();
		test_signed_character_casting();
		test_unsigned_character_casting();
		test_short_casting();
		test_unsigned_short_casting();
		test_integer_casting();
		test_unsigned_integer_casting();
		test_long_casting();
		test_unsigned_long_casting();
		test_float_casting();
		test_double_casting();
		test_long_double_casting();
		test_string_casting();
		test_subroutine_casting();
		test_function_casting();
		test_array_casting();
		/*test_array_casting();*/

		test_character_operation();
		test_signed_character_operation();
		test_unsigned_character_operation();
		test_short_operation();
		test_unsigned_short_operation();
		test_integer_operation();
		test_unsigned_integer_operation();
		test_long_operation();
		test_unsigned_long_operation();
		test_float_operation();
		test_double_operation();
		test_long_double_operation();
		test_string_operation();
		/*test_subroutine_operation();
		test_function_operation();*/
		test_array_operation();
		/*test_object_operation();*/
	}

	void test_string_operation(void) {
		MutableLet a = let_string("2");
		MutableLet b = let_string("2");
		Let four = let_string("22");
		Let char_and = let_string("2");
		Let char_xor = let_string("");
		Let char_or = let_string("");
		Let char_complement = let_string("2");
		Let char_minus = let_string("\316");
		Let zero = let_string("");
		Let negative_one = let_long(-1l);
		Let char_minus_one = let_string("1");
		Let char_plus_one = let_string("3");

		Let sum_string = sum(a, b);
		Let difference_string = difference(a, b);
		Let negative_string = negative(a);
		Let positive_string = positive(a);

		Let and_string = bit_and(a, b);
		Let or_string = bit_or(a, b);
		Let xor_string = bit_xor(a, b);
		Let complement_string = bit_complement(a);
		char const c = ~'2';
		char const complement_result[2] = { c, '\0' };
		Let complement_temp = let_string(complement_result);

		assert(equal(sum_string, four));
		assert(equal(difference_string, zero));
		assert(equal(modulo(a, b), let_empty()));
		assert(equal(and_string, char_and));
		assert(equal(or_string, char_or));
		assert(equal(xor_string, char_xor));
		assert(equal(complement_string, complement_temp));
		
		assert(equal(index_of(a, negative_one), b));
		assert(equal(negative_string, char_minus));
		assert(equal(positive_string, b));
		assert(equal(bit_not(a), let_unsigned_integer(0)));
		assert(equal(indirection(a), b));
		assert(equal(a, b));

		unlet(complement_string);
		unlet(complement_temp);
		unlet(and_string);
		unlet(or_string);
		unlet(xor_string);
		unlet(sum_string);
		unlet(difference_string);
		unlet(negative_string);
		unlet(positive_string);
		unlet(a);
		unlet(b);
		unlet(four);
		unlet(char_and);
		unlet(char_xor);
		unlet(char_or);
		unlet(char_complement);
		unlet(char_minus);
		unlet(zero);
		unlet(char_minus_one);
		unlet(char_plus_one);
	}

	void test_array_operation(void) {
		Let x = let_integer(2);
		Let y = let_string("2");
		Let xx = let_integer(3);
		Let yy = let_string("3");
		Let xxx = let_integer(1);
		Let yyy = let_string("1");
		Let empty = let_empty();
		MutableLet a = array_of(2, &x, &y);
		MutableLet b = array_of(2, &x, &y);
		Let four = array_of(4, &x, &y, &x, &y);
		Let char_and = four;
		Let char_xor = array_of(1, &empty);
		Let char_or = four;
		Let char_complement = let_string("2");
		Let char_minus = let_string("2");
		Let zero = char_xor;
		Let negative_one = let_long(-1l);
		Let char_minus_one = array_of(2, &xxx, &yyy);
		Let char_plus_one = array_of(2, &xx, &yy);

		Let sum_string = sum(a, b);
		Let difference_string = difference(a, b);
		Let negative_string = negative(a);
		Let positive_string = positive(a);
		Let negative_x = negative(x);
		Let negative_y = negative(y);
		Let negative_array = array_of(2, &negative_x, &negative_y);

		Let and_array = bit_and(a, b);
		Let or_array = bit_or(a, b);
		Let xor_array = bit_xor(a, b);

		Let indexed = index_of(a, negative_one);
		assert(equal(sum_string, four));
		assert(equal(difference_string, zero));
		assert(equal(modulo(a, b), let_empty()));
		assert(equal(and_array, b));
		assert(equal(or_array, char_xor));
		assert(equal(xor_array, char_xor));
		/*assert(equal(bit_complement(a), char_complement));*/
		assert(equal(indexed, char_minus));
		assert(equal(negative_string, negative_array));
		assert(equal(positive_string, a));
		assert(equal(bit_not(a), let_unsigned_integer(0)));
		assert(equal(indirection(a), x));
		assert(equal(a, b));

		unlet(and_array);
		unlet(or_array);
		unlet(xor_array);
		unlet(indexed);
		unlet(x);
		unlet(y);
		unlet(negative_x);
		unlet(negative_y);
		unlet(negative_array);
		unlet(xx);
		unlet(yy);
		unlet(xxx);
		unlet(yyy);
		unlet(sum_string);
		unlet(difference_string);
		unlet(negative_string);
		unlet(positive_string);
		unlet(a);
		unlet(b);
		unlet(four);
		unlet(char_xor);
		unlet(char_complement);
		unlet(char_minus);
		unlet(char_minus_one);
		unlet(char_plus_one);
	}

	void test_character_casting(void) {
		Let v = let_character('1');

		Let string = let_string_no_copy(as_string(v));
		Let comparison_string = let_string("1");

		Let temporary = let_character('1');
		Let comparison_array = array_of(1, &temporary);
		Let array = array_of(1, &v);

		Let object = let_object(as_object(v));
		Let comparison_object = let_object(NULL);

		assert(equal(v, let_character('1')));
		assert(equal(v, let_signed_character((signed char) '1')));
		assert(equal(v, let_unsigned_character((unsigned char) '1')));
		assert(equal(v, let_short((short) 1)));
		assert(equal(v, let_unsigned_short((unsigned short) 1)));
		assert(equal(v, let_integer(1)));
		assert(equal(v, let_unsigned_integer(1u)));
		assert(equal(v, let_long(1l)));
		assert(equal(v, let_unsigned_long(1ul)));
		assert(equal(v, let_float(1.0f)));
		assert(equal(v, let_double(1.0)));
		assert(equal(v, let_long_double(1.0l)));
		assert(equal(string, comparison_string));
		assert(equal(array, comparison_array));
		assert(equal(object, comparison_object));
		unlet(v);
		unlet(string);
		unlet(comparison_string);
		unlet(array);
		unlet(comparison_array);
		unlet(object);
		unlet(comparison_object);
	}

	void test_signed_character_casting(void) {
		Let v = let_signed_character((signed char) '1');

		Let string = let_string_no_copy(as_string(v));
		Let comparison_string = let_string("1");

		Let temporary = let_signed_character((signed char) '1');
		Let comparison_array = array_of(1, &temporary);
		Let array = array_of(1, &v);

		Let object = let_object(as_object(v));
		Let comparison_object = let_object(NULL);

		assert(equal(v, let_character('1')));
		assert(equal(v, let_signed_character((signed char) '1')));
		assert(equal(v, let_unsigned_character((unsigned char) '1')));
		assert(equal(v, let_short((short) 1)));
		assert(equal(v, let_unsigned_short((unsigned short) 1)));
		assert(equal(v, let_integer(1)));
		assert(equal(v, let_unsigned_integer(1u)));
		assert(equal(v, let_long(1l)));
		assert(equal(v, let_unsigned_long(1ul)));
		assert(equal(v, let_float(1.0f)));
		assert(equal(v, let_double(1.0)));
		assert(equal(v, let_long_double(1.0l)));
		assert(equal(string, comparison_string));
		assert(equal(array, comparison_array));
		assert(equal(object, comparison_object));
		unlet(v);
		unlet(string);
		unlet(comparison_string);
		unlet(array);
		unlet(comparison_array);
		unlet(object);
		unlet(comparison_object);
	}

	void test_unsigned_character_casting(void) {
		Let v = let_unsigned_character((unsigned char) '1');

		Let string = let_string_no_copy(as_string(v));
		Let comparison_string = let_string("1");

		Let temporary = let_unsigned_character((unsigned char) '1');
		Let comparison_array = array_of(1, &temporary);
		Let array = array_of(1, &v);

		Let object = let_object(as_object(v));
		Let comparison_object = let_object(NULL);

		assert(equal(v, let_character('1')));
		assert(equal(v, let_signed_character((signed char) '1')));
		assert(equal(v, let_unsigned_character((unsigned char) '1')));
		assert(equal(v, let_short((short) 1)));
		assert(equal(v, let_unsigned_short((unsigned short) 1)));
		assert(equal(v, let_integer(1)));
		assert(equal(v, let_unsigned_integer(1u)));
		assert(equal(v, let_long(1l)));
		assert(equal(v, let_unsigned_long(1ul)));
		assert(equal(v, let_float(1.0f)));
		assert(equal(v, let_double(1.0)));
		assert(equal(v, let_long_double(1.0l)));
		assert(equal(string, comparison_string));
		assert(equal(array, comparison_array));
		assert(equal(object, comparison_object));
		unlet(v);
		unlet(string);
		unlet(comparison_string);
		unlet(array);
		unlet(comparison_array);
		unlet(object);
		unlet(comparison_object);
	}

	void test_short_casting(void) {
		Let v = let_short((short) 1);

		Let string = let_string_no_copy(as_string(v));
		Let comparison_string = let_string("1");

		Let temporary = let_short((short) 1);
		Let comparison_array = array_of(1, &temporary);
		Let array = array_of(1, &v);

		Let object = let_object(as_object(v));
		Let comparison_object = let_object(NULL);

		assert(equal(v, let_character('1')));
		assert(equal(v, let_signed_character((signed char) '1')));
		assert(equal(v, let_unsigned_character((unsigned char) '1')));
		assert(equal(v, let_short((short) 1)));
		assert(equal(v, let_unsigned_short((unsigned short) 1)));
		assert(equal(v, let_integer(1)));
		assert(equal(v, let_unsigned_integer(1u)));
		assert(equal(v, let_long(1l)));
		assert(equal(v, let_unsigned_long(1ul)));
		assert(equal(v, let_float(1.0f)));
		assert(equal(v, let_double(1.0)));
		assert(equal(v, let_long_double(1.0l)));
		assert(equal(string, comparison_string));
		assert(equal(array, comparison_array));
		assert(equal(object, comparison_object));
		unlet(v);
		unlet(string);
		unlet(comparison_string);
		unlet(array);
		unlet(comparison_array);
		unlet(object);
		unlet(comparison_object);
	}

	void test_unsigned_short_casting(void) {
		Let v = let_short((unsigned short) 1);

		Let string = let_string_no_copy(as_string(v));
		Let comparison_string = let_string("1");

		Let temporary = let_short((unsigned short) 1);
		Let comparison_array = array_of(1, &temporary);
		Let array = array_of(1, &v);

		Let object = let_object(as_object(v));
		Let comparison_object = let_object(NULL);

		assert(equal(v, let_character('1')));
		assert(equal(v, let_signed_character((signed char) '1')));
		assert(equal(v, let_unsigned_character((unsigned char) '1')));
		assert(equal(v, let_short((short) 1)));
		assert(equal(v, let_unsigned_short((unsigned short) 1)));
		assert(equal(v, let_integer(1)));
		assert(equal(v, let_unsigned_integer(1u)));
		assert(equal(v, let_long(1l)));
		assert(equal(v, let_unsigned_long(1ul)));
		assert(equal(v, let_float(1.0f)));
		assert(equal(v, let_double(1.0)));
		assert(equal(v, let_long_double(1.0l)));
		assert(equal(string, comparison_string));
		assert(equal(array, comparison_array));
		assert(equal(object, comparison_object));
		unlet(v);
		unlet(string);
		unlet(comparison_string);
		unlet(array);
		unlet(comparison_array);
		unlet(object);
		unlet(comparison_object);
	}

	void test_integer_casting(void) {
		Let v = let_integer(1);

		Let string = let_string_no_copy(as_string(v));
		Let comparison_string = let_string("1");

		Let temporary = let_integer(1);
		Let comparison_array = array_of(1, &temporary);
		Let array = array_of(1, &v);

		Let object = let_object(as_object(v));
		Let comparison_object = let_object(NULL);

		assert(equal(v, let_character('1')));
		assert(equal(v, let_signed_character((signed char) '1')));
		assert(equal(v, let_unsigned_character((unsigned char) '1')));
		assert(equal(v, let_short((short) 1)));
		assert(equal(v, let_unsigned_short((unsigned short) 1)));
		assert(equal(v, let_integer(1)));
		assert(equal(v, let_unsigned_integer(1u)));
		assert(equal(v, let_long(1l)));
		assert(equal(v, let_unsigned_long(1ul)));
		assert(equal(v, let_float(1.0f)));
		assert(equal(v, let_double(1.0)));
		assert(equal(v, let_long_double(1.0l)));
		assert(equal(string, comparison_string));
		assert(equal(array, comparison_array));
		assert(equal(object, comparison_object));
		unlet(v);
		unlet(string);
		unlet(comparison_string);
		unlet(array);
		unlet(comparison_array);
		unlet(object);
		unlet(comparison_object);
	}

	void test_unsigned_integer_casting(void) {
		Let v = let_unsigned_integer(1u);

		Let string = let_string_no_copy(as_string(v));
		Let comparison_string = let_string("1");

		Let temporary = let_unsigned_integer(1u);
		Let comparison_array = array_of(1, &temporary);
		Let array = array_of(1, &v);

		Let object = let_object(as_object(v));
		Let comparison_object = let_object(NULL);

		assert(equal(v, let_character('1')));
		assert(equal(v, let_signed_character((signed char) '1')));
		assert(equal(v, let_unsigned_character((unsigned char) '1')));
		assert(equal(v, let_short((short) 1)));
		assert(equal(v, let_unsigned_short((unsigned short) 1)));
		assert(equal(v, let_integer(1)));
		assert(equal(v, let_unsigned_integer(1u)));
		assert(equal(v, let_long(1l)));
		assert(equal(v, let_unsigned_long(1ul)));
		assert(equal(v, let_float(1.0f)));
		assert(equal(v, let_double(1.0)));
		assert(equal(v, let_long_double(1.0l)));
		assert(equal(string, comparison_string));
		assert(equal(array, comparison_array));
		assert(equal(object, comparison_object));
		unlet(v);
		unlet(string);
		unlet(comparison_string);
		unlet(array);
		unlet(comparison_array);
		unlet(object);
		unlet(comparison_object);
	}

	void test_long_casting(void) {
		Let v = let_long(1l);

		Let string = let_string_no_copy(as_string(v));
		Let comparison_string = let_string("1");

		Let temporary = let_long(1l);
		Let comparison_array = array_of(1, &temporary);
		Let array = array_of(1, &v);

		Let object = let_object(as_object(v));
		Let comparison_object = let_object(NULL);

		assert(equal(v, let_character('1')));
		assert(equal(v, let_signed_character((signed char) '1')));
		assert(equal(v, let_unsigned_character((unsigned char) '1')));
		assert(equal(v, let_short((short) 1)));
		assert(equal(v, let_unsigned_short((unsigned short) 1)));
		assert(equal(v, let_integer(1)));
		assert(equal(v, let_unsigned_integer(1u)));
		assert(equal(v, let_long(1l)));
		assert(equal(v, let_unsigned_long(1ul)));
		assert(equal(v, let_float(1.0f)));
		assert(equal(v, let_double(1.0)));
		assert(equal(v, let_long_double(1.0l)));
		assert(equal(string, comparison_string));
		assert(equal(array, comparison_array));
		assert(equal(object, comparison_object));
		unlet(v);
		unlet(string);
		unlet(comparison_string);
		unlet(array);
		unlet(comparison_array);
		unlet(object);
		unlet(comparison_object);
	}

	void test_unsigned_long_casting(void) {
		Let v = let_unsigned_long(1ul);

		Let string = let_string_no_copy(as_string(v));
		Let comparison_string = let_string("1");

		Let temporary = let_unsigned_long(1ul);
		Let comparison_array = array_of(1, &temporary);
		Let array = array_of(1, &v);

		Let object = let_object(as_object(v));
		Let comparison_object = let_object(NULL);

		assert(equal(v, let_character('1')));
		assert(equal(v, let_signed_character((signed char) '1')));
		assert(equal(v, let_unsigned_character((unsigned char) '1')));
		assert(equal(v, let_short((short) 1)));
		assert(equal(v, let_unsigned_short((unsigned short) 1)));
		assert(equal(v, let_integer(1)));
		assert(equal(v, let_unsigned_integer(1u)));
		assert(equal(v, let_long(1l)));
		assert(equal(v, let_unsigned_long(1ul)));
		assert(equal(v, let_float(1.0f)));
		assert(equal(v, let_double(1.0)));
		assert(equal(v, let_long_double(1.0l)));
		assert(equal(string, comparison_string));
		assert(equal(array, comparison_array));
		assert(equal(object, comparison_object));
		unlet(v);
		unlet(string);
		unlet(comparison_string);
		unlet(array);
		unlet(comparison_array);
		unlet(object);
		unlet(comparison_object);
	}

	void test_float_casting(void) {
		Let v = let_float(1.0f);

		Let string = let_string_no_copy(as_string(v));
		Let comparison_string = let_string("1");

		Let temporary = let_float(1.0f);
		Let comparison_array = array_of(1, &temporary);
		Let array = array_of(1, &v);

		Let object = let_object(as_object(v));
		Let comparison_object = let_object(NULL);

		assert(equal(v, let_character('1')));
		assert(equal(v, let_signed_character((signed char) '1')));
		assert(equal(v, let_unsigned_character((unsigned char) '1')));
		assert(equal(v, let_short((short) 1)));
		assert(equal(v, let_unsigned_short((unsigned short) 1)));
		assert(equal(v, let_integer(1)));
		assert(equal(v, let_unsigned_integer(1u)));
		assert(equal(v, let_long(1l)));
		assert(equal(v, let_unsigned_long(1ul)));
		assert(equal(v, let_float(1.0f)));
		assert(equal(v, let_double(1.0)));
		assert(equal(v, let_long_double(1.0l)));
		assert(equal(string, comparison_string));
		assert(equal(array, comparison_array));
		assert(equal(object, comparison_object));
		unlet(v);
		unlet(string);
		unlet(comparison_string);
		unlet(array);
		unlet(comparison_array);
		unlet(object);
		unlet(comparison_object);
	}

	void test_double_casting(void) {
		Let v = let_double(1.0);

		Let string = let_string_no_copy(as_string(v));
		Let comparison_string = let_string("1");

		Let temporary = let_double(1.0);
		Let comparison_array = array_of(1, &temporary);
		Let array = array_of(1, &v);

		Let object = let_object(as_object(v));
		Let comparison_object = let_object(NULL);

		assert(equal(v, let_character('1')));
		assert(equal(v, let_signed_character((signed char) '1')));
		assert(equal(v, let_unsigned_character((unsigned char) '1')));
		assert(equal(v, let_short((short) 1)));
		assert(equal(v, let_unsigned_short((unsigned short) 1)));
		assert(equal(v, let_integer(1)));
		assert(equal(v, let_unsigned_integer(1u)));
		assert(equal(v, let_long(1l)));
		assert(equal(v, let_unsigned_long(1ul)));
		assert(equal(v, let_float(1.0f)));
		assert(equal(v, let_double(1.0)));
		assert(equal(v, let_long_double(1.0l)));
		assert(equal(string, comparison_string));
		assert(equal(array, comparison_array));
		assert(equal(object, comparison_object));
		unlet(v);
		unlet(string);
		unlet(comparison_string);
		unlet(array);
		unlet(comparison_array);
		unlet(object);
		unlet(comparison_object);
	}

	void test_long_double_casting(void) {
		Let v = let_long_double(1.0l);

		Let string = let_string_no_copy(as_string(v));
		Let comparison_string = let_string("1");

		Let temporary = let_long_double(1.0l);
		Let comparison_array = array_of(1, &temporary);
		Let array = array_of(1, &v);

		Let object = let_object(as_object(v));
		Let comparison_object = let_object(NULL);

		assert(equal(v, let_character('1')));
		assert(equal(v, let_signed_character((signed char) '1')));
		assert(equal(v, let_unsigned_character((unsigned char) '1')));
		assert(equal(v, let_short((short) 1)));
		assert(equal(v, let_unsigned_short((unsigned short) 1)));
		assert(equal(v, let_integer(1)));
		assert(equal(v, let_unsigned_integer(1u)));
		assert(equal(v, let_long(1l)));
		assert(equal(v, let_unsigned_long(1ul)));
		assert(equal(v, let_float(1.0f)));
		assert(equal(v, let_double(1.0)));
		assert(equal(v, let_long_double(1.0l)));
		assert(equal(string, comparison_string));
		assert(equal(array, comparison_array));
		assert(equal(object, comparison_object));
		unlet(v);
		unlet(string);
		unlet(comparison_string);
		unlet(array);
		unlet(comparison_array);
		unlet(object);
		unlet(comparison_object);
	}

	void test_string_casting(void) {
		Let v = let_string("1");

		Let string = let_string_no_copy(as_string(v));
		Let comparison_string = let_string("1");

		Let temporary = let_string("1");
		Let comparison_array = array_of(1, &temporary);
		Let array = array_of(1, &v);

		Let object = let_object(as_object(v));
		Let comparison_object = let_object(NULL);

		assert(equal(v, let_character('1')));
		assert(equal(v, let_signed_character((signed char) '1')));
		assert(equal(v, let_unsigned_character((unsigned char) '1')));
		assert(equal(v, let_short((short) 1)));
		assert(equal(v, let_unsigned_short((unsigned short) 1)));
		assert(equal(v, let_integer(1)));
		assert(equal(v, let_unsigned_integer(1u)));
		assert(equal(v, let_long(1l)));
		assert(equal(v, let_unsigned_long(1ul)));
		assert(equal(v, let_float(1.0f)));
		assert(equal(v, let_double(1.0)));
		assert(equal(v, let_long_double(1.0l)));
		assert(equal(string, comparison_string));
		assert(equal(array, comparison_array));
		assert(equal(object, comparison_object));
		unlet(v);
		unlet(string);
		unlet(temporary);
		unlet(comparison_string);
		unlet(array);
		unlet(comparison_array);
		unlet(object);
		unlet(comparison_object);
	}

	static subroutine(test_subroutine) {
		return;
	}

	void test_subroutine_casting(void) {
		Let v = let_subroutine(test_subroutine);

		Let string = let_string_no_copy(as_string(v));
		Let comparison_string = let_string("1");

		Let temporary = let_subroutine(test_subroutine);
		Let comparison_array = array_of(1, &temporary);
		Let array = array_of(1, &v);

		Let object = let_object(as_object(v));
		Let comparison_object = let_object(NULL);

		assert(!equal(v, let_character('1')));
		assert(!equal(v, let_signed_character((signed char) '1')));
		assert(!equal(v, let_unsigned_character((unsigned char) '1')));
		assert(!equal(v, let_short((short) 1)));
		assert(!equal(v, let_unsigned_short((unsigned short) 1)));
		assert(!equal(v, let_integer(1)));
		assert(!equal(v, let_unsigned_integer(1u)));
		assert(!equal(v, let_long(1l)));
		assert(!equal(v, let_unsigned_long(1ul)));
		assert(!equal(v, let_float(1.0f)));
		assert(!equal(v, let_double(1.0)));
		assert(!equal(v, let_long_double(1.0l)));
		assert(!equal(string, comparison_string));
		assert(equal(v, temporary));
		assert(equal(array, comparison_array));
		assert(equal(object, comparison_object));
		unlet(v);
		unlet(string);
		unlet(comparison_string);
		unlet(array);
		unlet(comparison_array);
		unlet(object);
		unlet(comparison_object);
	}

	static function(test_function) {
		return let_integer(1);
	}

	void test_function_casting(void) {
		Let v = let_function(test_function);

		Let string = let_string_no_copy(as_string(v));
		Let comparison_string = let_string("1");

		Let temporary = let_function(test_function);
		Let comparison_array = array_of(1, &temporary);
		Let array = array_of(1, &v);

		Let object = let_object(as_object(v));
		Let comparison_object = let_object(NULL);

		assert(equal(v, let_character('1')));
		assert(equal(v, let_signed_character((signed char) '1')));
		assert(equal(v, let_unsigned_character((unsigned char) '1')));
		assert(equal(v, let_short((short) 1)));
		assert(equal(v, let_unsigned_short((unsigned short) 1)));
		assert(equal(v, let_integer(1)));
		assert(equal(v, let_unsigned_integer(1u)));
		assert(equal(v, let_long(1l)));
		assert(equal(v, let_unsigned_long(1ul)));
		assert(equal(v, let_float(1.0f)));
		assert(equal(v, let_double(1.0)));
		assert(equal(v, let_long_double(1.0l)));
		assert(equal(string, comparison_string));
		assert(equal(array, comparison_array));
		assert(equal(object, comparison_object));
		unlet(v);
		unlet(string);
		unlet(comparison_string);
		unlet(array);
		unlet(comparison_array);
		unlet(object);
		unlet(comparison_object);
	}
	void test_array_casting(void) {
		Let vvv = let_integer(1);
		Let vv = array_of(1, &vvv);
		Let v = array_of(1, &vv);

		Let string = let_string_no_copy(as_string(v));
		Let comparison_string = let_string("1");

		Let temporary = let_long_double(1.0l);
		Let comparison_array = array_of(1, &temporary);
		Let array = array_of(1, &vv);

		Let object = let_object(as_object(v));
		Let comparison_object = let_object(NULL);

		assert(equal(v, let_character('1')));
		assert(equal(v, let_signed_character((signed char) '1')));
		assert(equal(v, let_unsigned_character((unsigned char) '1')));
		assert(equal(v, let_short((short) 1)));
		assert(equal(v, let_unsigned_short((unsigned short) 1)));
		assert(equal(v, let_integer(1)));
		assert(equal(v, let_unsigned_integer(1u)));
		assert(equal(v, let_long(1l)));
		assert(equal(v, let_unsigned_long(1ul)));
		assert(equal(v, let_float(1.0f)));
		assert(equal(v, let_double(1.0)));
		assert(equal(v, let_long_double(1.0l)));
		assert(equal(string, comparison_string));
		assert(equal(array, comparison_array));
		assert(equal(object, comparison_object));
		unlet(v);
		unlet(vv);
		unlet(vvv);
		unlet(string);
		unlet(comparison_string);
		unlet(array);
		unlet(comparison_array);
		unlet(object);
		unlet(comparison_object);
	}

	void test_object_casting(void) {
		Let v = let_object(NULL);

		Let string = let_string(as_string(v));
		Let comparison_string = let_string("1");

		Let temporary = let_object(NULL);
		Let comparison_array = array_of(1, &temporary);
		Let array = array_of(1, &v);

		Let object = let_object(as_object(v));
		Let comparison_object = let_object(NULL);

		assert(equal(v, let_character('1')));
		assert(equal(v, let_signed_character((signed char) '1')));
		assert(equal(v, let_unsigned_character((unsigned char) '1')));
		assert(equal(v, let_short((short) 1)));
		assert(equal(v, let_unsigned_short((unsigned short) 1)));
		assert(equal(v, let_integer(1)));
		assert(equal(v, let_unsigned_integer(1u)));
		assert(equal(v, let_long(1l)));
		assert(equal(v, let_unsigned_long(1ul)));
		assert(equal(v, let_float(1.0f)));
		assert(equal(v, let_double(1.0)));
		assert(equal(v, let_long_double(1.0l)));
		assert(equal(string, comparison_string));
		assert(equal(array, comparison_array));
		assert(equal(object, comparison_object));
		unlet(v);
		unlet(string);
		unlet(comparison_string);
		unlet(array);
		unlet(comparison_array);
		unlet(object);
		unlet(comparison_object);
	}

#ifdef __cplusplus
}
#endif

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

#include <thicc_struct_behaviour.h>
#include "../conversions/thicc_as_array.h"
#include "../conversions/thicc_as_boolean.h"
#include "../conversions/thicc_as_character.h"
#include "../conversions/thicc_as_complex.h"
#include "../conversions/thicc_as_function.h"
#include "../conversions/thicc_as_integer.h"
#include "../conversions/thicc_as_natural.h"
#include "../conversions/thicc_as_object.h"
#include "../conversions/thicc_as_real.h"
#include "../conversions/thicc_as_string.h"
#include "../operations/thicc_bit_and.h"
#include "../operations/thicc_bit_complement.h"
#include "../operations/thicc_bit_not.h"
#include "../operations/thicc_bit_or.h"
#include "../operations/thicc_bit_xor.h"
#include "../operations/thicc_comparison.h"
#include "../operations/thicc_difference.h"
#include "../operations/thicc_index_of.h"
#include "../operations/thicc_indirection.h"
#include "../operations/thicc_modulo.h"
#include "../operations/thicc_negative.h"
#include "../operations/thicc_positive.h"
#include "../operations/thicc_product.h"
#include "../operations/thicc_quotient.h"
#include "../operations/thicc_sum.h"
#include "thicc_memory.h"

Behaviour boolean_behaviour = {boolean_rank,	   stack_deallocate,	   boolean_as_boolean, boolean_as_character,
							   boolean_as_natural, boolean_as_integer,	   boolean_as_real,	   boolean_as_complex,
							   boolean_as_string,  boolean_as_function,	   boolean_as_array,   boolean_as_object,
							   boolean_sum,		   boolean_difference,	   boolean_product,	   boolean_quotient,
							   boolean_modulo,	   boolean_bit_and,		   boolean_bit_or,	   boolean_bit_xor,
							   boolean_bit_not,	   boolean_bit_complement, boolean_index_of,   boolean_indirection,
							   boolean_negative,   boolean_positive,	   boolean_comparison};

Behaviour character_behaviour = {
	character_rank,		  stack_deallocate,			character_as_boolean, character_as_character, character_as_natural,
	character_as_integer, character_as_real,		character_as_complex, character_as_string,	  character_as_function,
	character_as_array,	  character_as_object,		character_sum,		  character_difference,	  character_product,
	character_quotient,	  character_modulo,			character_bit_and,	  character_bit_or,		  character_bit_xor,
	character_bit_not,	  character_bit_complement, character_index_of,	  character_indirection,  character_negative,
	character_positive,	  character_comparison};

Behaviour natural_behaviour = {natural_rank,	   stack_deallocate,	   natural_as_boolean, natural_as_character,
							   natural_as_natural, natural_as_integer,	   natural_as_real,	   natural_as_complex,
							   natural_as_string,  natural_as_function,	   natural_as_array,   natural_as_object,
							   natural_sum,		   natural_difference,	   natural_product,	   natural_quotient,
							   natural_modulo,	   natural_bit_and,		   natural_bit_or,	   natural_bit_xor,
							   natural_bit_not,	   natural_bit_complement, natural_index_of,   natural_indirection,
							   natural_negative,   natural_positive,	   natural_comparison};

Behaviour integer_behaviour = {integer_rank,	   stack_deallocate,	   integer_as_boolean, integer_as_character,
							   integer_as_natural, integer_as_integer,	   integer_as_real,	   integer_as_complex,
							   integer_as_string,  integer_as_function,	   integer_as_array,   integer_as_object,
							   integer_sum,		   integer_difference,	   integer_product,	   integer_quotient,
							   integer_modulo,	   integer_bit_and,		   integer_bit_or,	   integer_bit_xor,
							   integer_bit_not,	   integer_bit_complement, integer_index_of,   integer_indirection,
							   integer_negative,   integer_positive,	   integer_comparison};

Behaviour real_behaviour = {real_rank,		 stack_deallocate,	  real_as_boolean, real_as_character, real_as_natural,
							real_as_integer, real_as_real,		  real_as_complex, real_as_string,	  real_as_function,
							real_as_array,	 real_as_object,	  real_sum,		   real_difference,	  real_product,
							real_quotient,	 real_modulo,		  real_bit_and,	   real_bit_or,		  real_bit_xor,
							real_bit_not,	 real_bit_complement, real_index_of,   real_indirection,  real_negative,
							real_positive,	 real_comparison};

Behaviour complex_behaviour = {complex_rank,	   stack_deallocate,	   complex_as_boolean, complex_as_character,
							   complex_as_natural, complex_as_integer,	   complex_as_real,	   complex_as_complex,
							   complex_as_string,  complex_as_function,	   complex_as_array,   complex_as_object,
							   complex_sum,		   complex_difference,	   complex_product,	   complex_quotient,
							   complex_modulo,	   complex_bit_and,		   complex_bit_or,	   complex_bit_xor,
							   complex_bit_not,	   complex_bit_complement, complex_index_of,   complex_indirection,
							   complex_negative,   complex_positive,	   complex_comparison};

Behaviour string_behaviour = {
	string_rank,	 string_deallocate, string_as_boolean, string_as_character,	  string_as_natural, string_as_integer,
	string_as_real,	 string_as_complex, string_as_string,  string_as_function,	  string_as_array,	 string_as_object,
	string_sum,		 string_difference, string_product,	   string_quotient,		  string_modulo,	 string_bit_and,
	string_bit_or,	 string_bit_xor,	string_bit_not,	   string_bit_complement, string_index_of,	 string_indirection,
	string_negative, string_positive,	string_comparison};

Behaviour function_behaviour = {
	function_rank,		 stack_deallocate,		  function_as_boolean, function_as_character, function_as_natural,
	function_as_integer, function_as_real,		  function_as_complex, function_as_string,	  function_as_function,
	function_as_array,	 function_as_object,	  function_sum,		   function_difference,	  function_product,
	function_quotient,	 function_modulo,		  function_bit_and,	   function_bit_or,		  function_bit_xor,
	function_bit_not,	 function_bit_complement, function_index_of,   function_indirection,  function_negative,
	function_positive,	 function_comparison};

Behaviour array_behaviour = {
	array_rank,		array_deallocate, array_as_boolean, array_as_character,	  array_as_natural, array_as_integer,
	array_as_real,	array_as_complex, array_as_string,	array_as_function,	  array_as_array,	array_as_object,
	array_sum,		array_difference, array_product,	array_quotient,		  array_modulo,		array_bit_and,
	array_bit_or,	array_bit_xor,	  array_bit_not,	array_bit_complement, array_index_of,	array_indirection,
	array_negative, array_positive,	  array_comparison,
};

Behaviour object_behaviour = {
	object_rank,	 object_deallocate, object_as_boolean, object_as_character,	  object_as_natural, object_as_integer,
	object_as_real,	 object_as_complex, object_as_string,  object_as_function,	  object_as_array,	 object_as_object,
	object_sum,		 object_difference, object_product,	   object_quotient,		  object_modulo,	 object_bit_and,
	object_bit_or,	 object_bit_xor,	object_bit_not,	   object_bit_complement, object_index_of,	 object_indirection,
	object_negative, object_positive,	object_comparison};

#ifdef __cplusplus
}
#endif

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

#include "thicc_struct_var.h"
#include "../utility/thicc_array.h"
#include "../utility/thicc_object.h"
#include "../utility/thicc_string.h"
#include "thicc_struct_behaviour.h"
#include <string.h>

THICC_NODISCARD Var let_init(void) {
  Var let;
  (void) memset(&let, 0, sizeof(Var));
  return let;
}

THICC_NODISCARD Var let_boolean(Boolean _value) {
  Var let				 = let_init();
  let.value.boolean_type = _value;
  let.behaviour			 = &boolean_behaviour;
  return let;
}

THICC_NODISCARD Var let_character(Character _value) {
  Var let				   = let_init();
  let.value.character_type = _value;
  let.behaviour			   = &character_behaviour;
  return let;
}

THICC_NODISCARD Var let_natural(Natural _value) {
  Var let				 = let_init();
  let.value.natural_type = _value;
  let.behaviour			 = &natural_behaviour;
  return let;
}

THICC_NODISCARD Var let_integer(Integer _value) {
  Var let				 = let_init();
  let.value.integer_type = _value;
  let.behaviour			 = &integer_behaviour;
  return let;
}

THICC_NODISCARD Var let_real(Real _value) {
  Var let			  = let_init();
  let.value.real_type = _value;
  let.behaviour		  = &real_behaviour;
  return let;
}

THICC_NODISCARD Var let_complex(Complex _value) {
  Var let				 = let_init();
  let.value.complex_type = _value;
  let.behaviour			 = &complex_behaviour;
  return let;
}

THICC_NODISCARD Var let_string(String _value) {
  Var let				= let_init();
  let.value.string_type = string_copy(_value);
  let.behaviour			= &string_behaviour;
  return let;
}

THICC_NODISCARD Var move_string(MutableString _value) {
  Var let				= let_init();
  let.value.string_type = _value;
  let.behaviour			= &string_behaviour;
  return let;
}

THICC_NODISCARD Var let_function(Function _value) {
  Var let				  = let_init();
  let.value.function_type = _value;
  let.behaviour			  = &function_behaviour;
  return let;
}

THICC_NODISCARD Var let_array(Array _value) {
  Var let			   = let_init();
  let.value.array_type = array_copy(_value);
  let.behaviour		   = &array_behaviour;
  return let;
}

THICC_NODISCARD Var move_array(MutableArray _value) {
  Var let			   = let_init();
  let.value.array_type = _value;
  let.behaviour		   = &array_behaviour;
  return let;
}

THICC_NODISCARD Var let_object(ImmutableObject _value) {
  Var let				= let_init();
  let.value.object_type = object_copy(_value);
  let.behaviour			= &object_behaviour;
  return let;
}

THICC_NODISCARD Var move_object(MutableObject _value) {
  Var let				= let_init();
  let.value.object_type = _value;
  let.behaviour			= &object_behaviour;
  return let;
}

THICC_NODISCARD Var let_copy(Let _let) {
  if (let_is_empty(_let))
	return let_empty();

  switch (_let.behaviour->rank) {
	case boolean_rank:
	  return let_boolean(_let.value.boolean_type);
	case character_rank:
	  return let_character(_let.value.character_type);
	case natural_rank:
	  return let_natural(_let.value.natural_type);
	case integer_rank:
	  return let_integer(_let.value.integer_type);
	case real_rank:
	  return let_real(_let.value.real_type);
	case complex_rank:
	  return let_complex(_let.value.complex_type);
	case string_rank:
	  return let_string(_let.value.string_type);
	case function_rank:
	  return let_function(_let.value.function_type);
	case array_rank:
	  return let_array(_let.value.array_type);
	case object_rank:
	  return let_object(_let.value.object_type);
  }

  return let_empty();
}

THICC_NODISCARD Var let_move(Var _let) {
  Var let	= let_init();
  let.value = _let.value;
  memset(&_let.value, 0, sizeof(Value));
  _let.value.object_type = THICC_NAUGHT;
  let.behaviour			 = _let.behaviour;
  _let.behaviour		 = THICC_NAUGHT;
  return let;
}

THICC_NODISCARD Var let_empty(void) {
  Var let				= let_init();
  let.value.object_type = THICC_NAUGHT;
  let.behaviour			= THICC_NAUGHT;
  return let;
}

THICC_NODISCARD MutableBoolean let_is_empty(Let _let) {
  if (_let.value.object_type == THICC_NAUGHT && _let.behaviour == THICC_NAUGHT)
	return THICC_YES;
  return THICC_NO;
}

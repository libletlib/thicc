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
 * 2.   Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifdef __cplusplus
extern "C" {
#endif

#include <thicc_opaque.h>
#include <stdlib.h>

THICC_NODISCARD static MutableOpaque var_to_opaque(Var _var) {
  MutableOpaque opaque;
  opaque.variable = calloc(1, sizeof(Opaque));
  *opaque.variable = _var;
  return opaque;
}

THICC_NODISCARD static Var opaque_to_var(Opaque _opaque) {
  return *_opaque.variable;
}

THICC_NODISCARD MutableRank opaque_rank(Opaque _opaque) {
  return rank(opaque_to_var(_opaque));
}

THICC_NODISCARD MutableOpaque opaque_cast(Opaque _opaque, Rank _rank) {
  return var_to_opaque(cast(opaque_to_var(_opaque), _rank));
}

THICC_NODISCARD MutableBoolean opaque_requires_free(Opaque _opaque) {
  return requires_free(opaque_to_var(_opaque));
}

void opaque_unlet(Opaque _opaque) {
  unlet(opaque_to_var(_opaque));
  free(_opaque.variable);
}

void opaque_unlet_if_required(Opaque _opaque) {
  unlet_if_required(opaque_to_var(_opaque));
  free(_opaque.variable);
}

THICC_NODISCARD Character* opaque_string_view(Opaque _opaque) {
  return string_view(opaque_to_var(_opaque));
}

THICC_NODISCARD Var* opaque_array_view(Opaque _opaque) {
  return array_view(opaque_to_var(_opaque));
}

THICC_NODISCARD Object opaque_object_view(Opaque _opaque) {
  return object_view(opaque_to_var(_opaque));
}

THICC_NODISCARD MutableBoolean opaque_as_boolean(Opaque _opaque) {
	return as_boolean(opaque_to_var(_opaque));
}

THICC_NODISCARD MutableCharacter opaque_as_character(Opaque _opaque) {
	return as_character(opaque_to_var(_opaque));
}

THICC_NODISCARD MutableNatural opaque_as_natural(Opaque _opaque) {
	return as_natural(opaque_to_var(_opaque));
}

THICC_NODISCARD MutableInteger opaque_as_integer(Opaque _opaque) {
	return as_integer(opaque_to_var(_opaque));
}

THICC_NODISCARD MutableReal opaque_as_real(Opaque _opaque) {
	return as_real(opaque_to_var(_opaque));
}

THICC_NODISCARD MutableComplex opaque_as_complex(Opaque _opaque) {
	return as_complex(opaque_to_var(_opaque));
}

THICC_NODISCARD MutableString opaque_as_string(Opaque _opaque) {
	return as_string(opaque_to_var(_opaque));
}

THICC_NODISCARD MutableFunction opaque_as_function(Opaque _opaque) {
	return as_function(opaque_to_var(_opaque));
}

THICC_NODISCARD MutableArray opaque_as_array(Opaque _opaque) {
	return as_array(opaque_to_var(_opaque));
}

THICC_NODISCARD MutableObject opaque_as_object(Opaque _opaque) {
	return as_object(opaque_to_var(_opaque));
}

THICC_NODISCARD MutableOpaque opaque_weak_string(MutableCharacter* _string) {
	return var_to_opaque(weak_string(_string));
}

THICC_NODISCARD MutableOpaque opaque_call(Opaque _opaque) {
	return var_to_opaque(call(opaque_to_var(_opaque)));
}

THICC_NODISCARD MutableOpaque opaque_member(Opaque _object, Opaque _member) {
	return var_to_opaque(member(opaque_to_var(_object), opaque_to_var(_member)));
}

THICC_NODISCARD MutableOpaque opaque_sum(Opaque _left, Opaque _right) {
	return var_to_opaque(sum(opaque_to_var(_left), opaque_to_var(_right)));
}

THICC_NODISCARD MutableOpaque opaque_difference(Opaque _left, Opaque _right) {
	return var_to_opaque(difference(opaque_to_var(_left), opaque_to_var(_right)));
}

THICC_NODISCARD MutableOpaque opaque_quotient(Opaque _left, Opaque _right) {
	return var_to_opaque(quotient(opaque_to_var(_left), opaque_to_var(_right)));
}

THICC_NODISCARD MutableOpaque opaque_modulo(Opaque _left, Opaque _right) {
	return var_to_opaque(modulo(opaque_to_var(_left), opaque_to_var(_right)));
}

THICC_NODISCARD MutableOpaque opaque_product(Opaque _left, Opaque _right) {
	return var_to_opaque(product(opaque_to_var(_left), opaque_to_var(_right)));
}

THICC_NODISCARD MutableOpaque opaque_bit_and(Opaque _left, Opaque _right) {
	return var_to_opaque(bit_and(opaque_to_var(_left), opaque_to_var(_right)));
}

THICC_NODISCARD MutableOpaque opaque_bit_or(Opaque _left, Opaque _right) {
	return var_to_opaque(bit_or(opaque_to_var(_left), opaque_to_var(_right)));
}

THICC_NODISCARD MutableOpaque opaque_bit_xor(Opaque _left, Opaque _right) {
	return var_to_opaque(bit_xor(opaque_to_var(_left), opaque_to_var(_right)));
}

THICC_NODISCARD MutableOpaque opaque_index_of(Opaque _left, Opaque _right) {
	return var_to_opaque(index_of(opaque_to_var(_left), opaque_to_var(_right)));
}

THICC_NODISCARD MutableOpaque opaque_bit_not(Opaque _opaque) {
	return var_to_opaque(bit_not(opaque_to_var(_opaque)));
}

THICC_NODISCARD MutableOpaque opaque_bit_complement(Opaque _opaque) {
	return var_to_opaque(bit_complement(opaque_to_var(_opaque)));
}

THICC_NODISCARD MutableOpaque opaque_indirection(Opaque _opaque) {
	return var_to_opaque(indirection(opaque_to_var(_opaque)));
}

THICC_NODISCARD MutableOpaque opaque_negative(Opaque _opaque) {
	return var_to_opaque(negative(opaque_to_var(_opaque)));
}

THICC_NODISCARD MutableOpaque opaque_positive(Opaque _opaque) {
	return var_to_opaque(positive(opaque_to_var(_opaque)));
}

THICC_NODISCARD MutableComparison opaque_compare(Opaque _left, Opaque _right) {
	return compare(opaque_to_var(_left), opaque_to_var(_right));
}

THICC_NODISCARD MutableBoolean opaque_equal(Opaque _left, Opaque _right) {
	return equal(opaque_to_var(_left), opaque_to_var(_right));
}

THICC_NODISCARD MutableBoolean opaque_greater_than(Opaque _left, Opaque _right) {
	return greater_than(opaque_to_var(_left), opaque_to_var(_right));
}

THICC_NODISCARD MutableBoolean opaque_less_than(Opaque _left, Opaque _right) {
	return less_than(opaque_to_var(_left), opaque_to_var(_right));
}

THICC_NODISCARD MutableBoolean opaque_not_equal(Opaque _left, Opaque _right) {
	return not_equal(opaque_to_var(_left), opaque_to_var(_right));
}

THICC_NODISCARD MutableSize opaque_length(Opaque _opaque) {
	return length(opaque_to_var(_opaque));
}

THICC_NODISCARD MutableBoolean opaque_is_character(Opaque _opaque) {
	return is_character(opaque_to_var(_opaque));
}

THICC_NODISCARD MutableBoolean opaque_is_numeric(Opaque _opaque) {
	return is_numeric(opaque_to_var(_opaque));
}

THICC_NODISCARD MutableBoolean opaque_is_integral(Opaque _opaque) {
	return is_integral(opaque_to_var(_opaque));
}

THICC_NODISCARD MutableBoolean opaque_is_unsigned(Opaque _opaque) {
	return is_unsigned(opaque_to_var(_opaque));
}

THICC_NODISCARD MutableBoolean opaque_is_signed(Opaque _opaque) {
	return is_signed(opaque_to_var(_opaque));
}

THICC_NODISCARD MutableBoolean opaque_is_floating_point(Opaque _opaque) {
	return is_floating_point(opaque_to_var(_opaque));
}

THICC_NODISCARD MutableBoolean opaque_is_string(Opaque _opaque) {
	return is_string(opaque_to_var(_opaque));
}

THICC_NODISCARD MutableBoolean opaque_is_invokable(Opaque _opaque) {
	return is_invokable(opaque_to_var(_opaque));
}

THICC_NODISCARD MutableBoolean opaque_is_array(Opaque _opaque) {
	return is_array(opaque_to_var(_opaque));
}

THICC_NODISCARD MutableBoolean opaque_is_object(Opaque _opaque) {
	return is_object(opaque_to_var(_opaque));
}

THICC_NODISCARD MutableBoolean opaque_is_indexable(Opaque _opaque) {
	return is_indexable(opaque_to_var(_opaque));
}

MutableOpaque opaque_let_init(void) {
	return var_to_opaque(let_init());
}

MutableOpaque opaque_let_boolean(Boolean _value) {
	return var_to_opaque(let_boolean(_value));
}

MutableOpaque opaque_let_character(Character _value) {
	return var_to_opaque(let_character(_value));
}

MutableOpaque opaque_let_natural(Natural _value) {
	return var_to_opaque(let_natural(_value));
}

MutableOpaque opaque_let_integer(Integer _value) {
	return var_to_opaque(let_integer(_value));
}

MutableOpaque opaque_let_real(Real _value) {
	return var_to_opaque(let_real(_value));
}

MutableOpaque opaque_let_complex(Complex _value) {
	return var_to_opaque(let_complex(_value));
}

MutableOpaque opaque_let_string(MutableCharacter* _value) {
	return var_to_opaque(let_string(_value));
}

MutableOpaque opaque_move_string(MutableString _value) {
	return var_to_opaque(move_string(_value));
}

MutableOpaque opaque_let_function(Function _value) {
	return var_to_opaque(let_function(_value));
}

MutableOpaque opaque_let_array(Array _value) {
	return var_to_opaque(let_array(_value));
}

MutableOpaque opaque_move_array(MutableArray _value) {
	return var_to_opaque(move_array(_value));
}

MutableOpaque opaque_let_object(ImmutableObject _value) {
	return var_to_opaque(let_object(_value));
}

MutableOpaque opaque_move_object(MutableObject _value) {
	return var_to_opaque(move_object(_value));
}

MutableOpaque opaque_let_copy(Opaque _opaque) {
	return var_to_opaque(let_copy(opaque_to_var(_opaque)));
}

MutableOpaque opaque_let_move(Opaque _opaque) {
	return var_to_opaque(let_move(opaque_to_var(_opaque)));
}

MutableOpaque opaque_let_empty(void) {
	return var_to_opaque(let_empty());
}

MutableBoolean opaque_let_is_empty(Opaque _opaque) {
	return let_is_empty(opaque_to_var(_opaque));
}

#ifdef __cplusplus
}
#endif

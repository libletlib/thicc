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
#ifndef THICC_THICC_OPAQUE_H
#define THICC_THICC_OPAQUE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <thicc.h>

struct thicc_struct_opaque {
  Var* variable;
};

typedef struct thicc_struct_opaque MutableOpaque;
typedef MutableOpaque const Opaque;

MutableRank	   opaque_rank(Opaque);
MutableOpaque		   opaque_cast(Opaque, Rank);
MutableBoolean opaque_requires_free(Opaque);
void		   opaque_unlet(Opaque);
void		   opaque_unlet_if_required(Opaque);

Character* opaque_string_view(Opaque);
Var* opaque_array_view(Opaque);
Object opaque_object_view(Opaque);

MutableBoolean	 opaque_as_boolean(Opaque);
MutableCharacter opaque_as_character(Opaque);
MutableNatural	 opaque_as_natural(Opaque);
MutableInteger	 opaque_as_integer(Opaque);
MutableReal		 opaque_as_real(Opaque);
MutableComplex	 opaque_as_complex(Opaque);
MutableString	 opaque_as_string(Opaque);
MutableFunction	 opaque_as_function(Opaque);
MutableArray	 opaque_as_array(Opaque);
MutableObject	 opaque_as_object(Opaque);

MutableOpaque opaque_weak_string(MutableCharacter*);
MutableOpaque opaque_call(Opaque);
MutableOpaque opaque_member(Opaque, Opaque);
MutableOpaque opaque_sum(Opaque, Opaque);
MutableOpaque opaque_difference(Opaque, Opaque);
MutableOpaque opaque_quotient(Opaque, Opaque);
MutableOpaque opaque_modulo(Opaque, Opaque);
MutableOpaque opaque_product(Opaque, Opaque);
MutableOpaque opaque_bit_and(Opaque, Opaque);
MutableOpaque opaque_bit_or(Opaque, Opaque);
MutableOpaque opaque_bit_xor(Opaque, Opaque);
MutableOpaque opaque_index_of(Opaque, Opaque);

MutableOpaque opaque_bit_not(Opaque);
MutableOpaque opaque_bit_complement(Opaque);
MutableOpaque opaque_indirection(Opaque);
MutableOpaque opaque_negative(Opaque);
MutableOpaque opaque_positive(Opaque);

MutableComparison opaque_compare(Opaque, Opaque);
MutableBoolean	  opaque_equal(Opaque, Opaque);
MutableBoolean	  opaque_greater_than(Opaque, Opaque);
MutableBoolean	  opaque_less_than(Opaque, Opaque);
MutableBoolean	  opaque_not_equal(Opaque, Opaque);

MutableSize opaque_length(Opaque);

MutableBoolean opaque_is_character(Opaque);
MutableBoolean opaque_is_numeric(Opaque);
MutableBoolean opaque_is_integral(Opaque);
MutableBoolean opaque_is_unsigned(Opaque);
MutableBoolean opaque_is_signed(Opaque);
MutableBoolean opaque_is_floating_point(Opaque);
MutableBoolean opaque_is_string(Opaque);
MutableBoolean opaque_is_invokable(Opaque);
MutableBoolean opaque_is_array(Opaque);
MutableBoolean opaque_is_object(Opaque);
MutableBoolean opaque_is_indexable(Opaque);

MutableOpaque opaque_let_init(void);
MutableOpaque opaque_let_boolean(Boolean);
MutableOpaque opaque_let_character(Character);
MutableOpaque opaque_let_natural(Natural);
MutableOpaque opaque_let_integer(Integer);
MutableOpaque opaque_let_real(Real);
MutableOpaque opaque_let_complex(Complex);
MutableOpaque opaque_let_string(MutableCharacter*);
MutableOpaque opaque_move_string(MutableString);
MutableOpaque opaque_let_function(Function);
MutableOpaque opaque_let_array(Array);
MutableOpaque opaque_move_array(MutableArray);
MutableOpaque opaque_let_object(ImmutableObject);
MutableOpaque opaque_move_object(MutableObject);
MutableOpaque opaque_let_copy(Opaque);
MutableOpaque opaque_let_move(Opaque);

MutableOpaque opaque_let_empty(void);
MutableBoolean opaque_let_is_empty(Opaque);

#ifdef __cplusplus
}
#endif

#endif /* THICC_THICC_OPAQUE_H */

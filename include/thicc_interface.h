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
#ifndef THICC_THICC_INTERFACE_H
#define THICC_THICC_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "thicc_prelude.h"
#include <stdarg.h>

MutableRank	   rank(Let);
Var			   cast(Let, Rank);
MutableBoolean requires_free(Let);
void		   unlet(Let);
void		   unlet_if_required(Let);
Var			   empty_function(Let, Let);

Character* string_view(Let);
Var*   array_view(Let);
Object object_view(Let);

MutableBoolean	 as_boolean(Let);
MutableCharacter as_character(Let);
MutableNatural	 as_natural(Let);
MutableInteger	 as_integer(Let);
MutableReal		 as_real(Let);
MutableComplex	 as_complex(Let);
MutableString	 as_string(Let);
MutableFunction	 as_function(Let);
MutableArray	 as_array(Let);
MutableObject	 as_object(Let);

Var array_of(Size, ...);
Var object_of(Size, ...);
Var call(Let);
Var invoke(Let, Size, ...);
Var invoke_from_list(Let, Size, va_list);
Var member(Let, Let);
Var sum(Let, Let);
Var difference(Let, Let);
Var quotient(Let, Let);
Var modulo(Let, Let);
Var product(Let, Let);
Var bit_and(Let, Let);
Var bit_or(Let, Let);
Var bit_xor(Let, Let);
Var index_of(Let, Let);

Var bit_not(Let);
Var bit_complement(Let);
Var indirection(Let);
Var negative(Let);
Var positive(Let);

MutableComparison compare(Let, Let);
MutableBoolean	  equal(Let, Let);
MutableBoolean	  greater_than(Let, Let);
MutableBoolean	  less_than(Let, Let);
MutableBoolean	  not_equal(Let, Let);

MutableSize length(Let);

MutableBoolean is_character(Let);
MutableBoolean is_numeric(Let);
MutableBoolean is_integral(Let);
MutableBoolean is_unsigned(Let);
MutableBoolean is_signed(Let);
MutableBoolean is_floating_point(Let);
MutableBoolean is_string(Let);
MutableBoolean is_invokable(Let);
MutableBoolean is_array(Let);
MutableBoolean is_object(Let);
MutableBoolean is_indexable(Let);

#ifdef __cplusplus
}
#endif

#endif /* THICC_THICC_INTERFACE_H */

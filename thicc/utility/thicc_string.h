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
#ifndef THICC_THICC_STRING_H
#define THICC_THICC_STRING_H

#ifdef __cplusplus
extern "C" {
#endif

#include "thicc_math_prelude.h"

MutableSize		  string_length(ImmutableString);
MutableString	  string_copy(ImmutableString);
MutableString	  string_copy_slice(ImmutableString, Size, Size);
MutableComparison string_compare(ImmutableString, String);
MutableArray	  string_tokenise(MutableString, ImmutableString);
MutableString	  string_filter_and(ImmutableString, ImmutableString);
MutableString	  string_filter_or(ImmutableString, ImmutableString);
MutableString	  string_filter_xor(ImmutableString, ImmutableString);
MutableString	  string_map_bit_not(ImmutableString);
MutableString	  string_map_bit_complement(ImmutableString);
MutableString	  string_map_positive(ImmutableString);
MutableString	  string_map_negative(ImmutableString);
MutableString	  string_map_increment(MutableString);
MutableString	  string_map_decrement(MutableString);
MutableCharacter  string_character_at(ImmutableString, Integer);
Var				  string_to_number(ImmutableString);
MutableString	  string_concatenate(ImmutableString, ImmutableString);
String			  string_find_substring(ImmutableString, ImmutableString);
MutableString	  string_remove_substring(ImmutableString, ImmutableString);
MutableString	  string_empty(void);
MutableBoolean	  string_is_empty(String);
MutableString	  string_from_characters(Size, ...);
MutableString	  string_from_signed_characters(Size, ...);
MutableString	  string_from_unsigned_characters(Size, ...);
MutableSize		  characters_in_natural(Natural);
MutableSize		  characters_in_integer(Integer);
MutableSize		  characters_in_real(Real);
MutableSize		  characters_in_complex(Complex);
MutableString	  string_from_natural(Natural);
MutableString	  string_from_integer(Integer);
MutableString	  string_from_real(Real);
MutableString	  string_from_complex(Complex);
MutableString	  string_from_array(ImmutableArray);
MutableString	  string_from_object(ImmutableObject);
MutableNatural	  string_to_natural(ImmutableString);
MutableInteger	  string_to_integer(ImmutableString);
MutableReal		  string_to_real(ImmutableString);
MutableComplex	  string_to_complex(ImmutableString);

#ifdef __cplusplus
}
#endif

#endif /* THICC_THICC_STRING_H */

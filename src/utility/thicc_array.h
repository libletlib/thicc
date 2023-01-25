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
 * docs and/or other materials provided with the distribution.
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
#ifndef THICC_THICC_ARRAY_H
#define THICC_THICC_ARRAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <thicc_prelude.h>
#include <stdarg.h>

MutableComparison array_compare(Array, Array);
MutableArray	  array_copy(Array);
MutableArray	  array_remove_subarray(Array, Array);
MutableArray	  array_from_elements(size_t, ...);
MutableArray	  array_with_self_reference_from_list(Let*, Size, va_list);
MutableArray	  array_from_list(Size, va_list);
MutableArray	  array_concatenate(Array, Array);
MutableArray	  array_filter_and(Array, Array);
MutableArray	  array_filter_or(Array, Array);
MutableArray	  array_filter_xor(Array, Array);
MutableArray	  array_map_bit_not(Array);
MutableArray	  array_map_bit_complement(Array);
MutableArray	  array_map_positive(Array);
MutableArray	  array_map_negative(Array);
MutableArray	  array_zip(Array, Array);
Let*              array_element_at(Array, Integer);

#ifdef __cplusplus
}
#endif

#endif /* THICC_THICC_ARRAY_H */

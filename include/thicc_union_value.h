/*
 *   ___       ___       ___       ___       ___
 *  /\  \     /\__\     /\  \     /\  \     /\  \
 *  \:\  \   /:/__/_   _\:\  \   /::\  \   /::\  \
 *  /::\__\ /::\/\__\ /\/::\__\ /:/\:\__\ /:/\:\__\
 * /:/\/__/ \/\::/  / \::/\/__/ \:\ \/__/ \:\ \/__/
 * \/__/      /:/  /   \:\__\    \:\__\    \:\__\
 *            \/__/     \/__/     \/__/     \/__/
 *
 * Copyright 2022 - 2023 Ville Rissanen
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1.   Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *
 * 2.   Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
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
#ifndef THICC_THICC_UNION_VALUE_H
#define THICC_THICC_UNION_VALUE_H

/**
 * \file thicc_union_value.h
 * Declare the union that actually holds the data inside Lets.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "thicc_prelude.h"
#include "thicc_struct_array.h"
#include "thicc_struct_complex.h"
#include "thicc_struct_string.h"

/**
 * \brief Holds the memory of the Let values.
 */
union thicc_union_value {
  MutableBoolean   boolean_type; /**< Boolean type, in C89 it is an unsigned int and in C99 or later the _Bool type. */
  MutableCharacter character_type; /**< Character type, which is of type char. */
  MutableNatural
	  natural_type; /**< Natural type, in C89 it is unsigned long and in C99 or later the unsigned long long type. */
  MutableInteger integer_type; /**< Integer type, in C89 it is long and in C99 or later the long long type. */
  MutableReal	 real_type;	   /**< Real type, equivalent of the long double type. */
  MutableComplex complex_type; /**< Complex number type which is compatible with the C99 _Complex type. */
  MutableString string_type; /**< Struct that holds a C string and its length. See thicc_struct_string.h for details. */
  MutableFunction function_type; /**< Function pointer of type Let* (*)(Let*, Let*). */
  MutableArray array_type; /**< Struct that holds an array of Let pointers and its length. See thicc_struct_array.h for
							  details. */
  MutableObject object_type; /**< A void pointer. Represents either an empty Let or a Let object. */
};

#ifdef __cplusplus
}
#endif

#endif /* THICC_THICC_UNION_VALUE_H */

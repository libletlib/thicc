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
#ifndef THICC_THICC_STRUCT_STRING_H
#define THICC_THICC_STRUCT_STRING_H

/**
 * \file thicc_struct_string.h
 * Declare the String type struct and directly related functions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "thicc_prelude.h"

/**
 * \brief Hold a Let array type values and their length.
 */
struct thicc_struct_string {
  MutableCharacter* string; /**< Raw C string, null terminated. */
  MutableSize		length; /**< Length of the string, excluding the null terminator. */
};

/**
 * \brief Produces an empty string.
 * This is a string with a pointer to `THICC_NAUGHT` and length of 0.
 * \return An empty string.
 */
MutableString string_empty(void);
/**
 * \brief Calculates the length of a String.
 * \param _string to evaluate length for.
 * \return Length of the string.
 */
MutableSize string_length(String _string);
/**
 * \brief Construct a Let String from a C string literal.
 * \param _literal to copy.
 * \return A copy of _literal as a Let.
 */
MutableString string_from_pointer(MutableCharacter* _literal);
/**
 * \brief Check if a string is empty.
 * A String is empty, if the pointer to it is `THICC_NAUGHT` or its length is 0.
 * \param _string to evaluate for emptiness.
 * \return true if _string is empty, false otherwise.
 */
MutableBoolean string_is_empty(String _string);

#ifdef __cplusplus
}
#endif

#endif /* THICC_THICC_STRUCT_STRING_H */

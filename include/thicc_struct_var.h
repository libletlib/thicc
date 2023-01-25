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
#ifndef THICC_THICC_STRUCT_VAR_H
#define THICC_THICC_STRUCT_VAR_H

/**
 * \file thicc_struct_var.h
 * Declare the var struct that is behind every Let and directly related functions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "thicc_struct_behaviour.h"
#include "thicc_union_value.h"

/**
 * \brief The primary struct behind every Let pointer.
 */
struct thicc_struct_var {
  MutableValue value; /**< Union that holds all possible Let internal data types. */
  Behaviour*
	  behaviour; /**< Pointer to a global struct, that dictates behaviour on operations based on internal type. */
};

/**
 * \brief Make a Let from a Boolean value.
 * \param _value to make Let out of.
 * \return Let with _value.
 */
Let* let_boolean(Boolean _value);
/**
 * \brief Make a Let from a Character value.
 * \param _value to make Let out of.
 * \return Let with _value.
 */
Let* let_character(Character _value);
/**
 * \brief Make a Let from a Natural value.
 * \param _value to make Let out of.
 * \return Let with _value.
 */
Let* let_natural(Natural _value);
/**
 * \brief Make a Let from a Integer value.
 * \param _value to make Let out of.
 * \return Let with _value.
 */
Let* let_integer(Integer _value);
/**
 * \brief Make a Let from a Real value.
 * \param _value to make Let out of.
 * \return Let with _value.
 */
Let* let_real(Real _value);
/**
 * \brief Make a Let from a Complex value.
 * \param _value to make Let out of.
 * \return Let with _value.
 */
Let* let_complex(Complex _value);
/**
 * \brief Make a Let from a String value.
 * \param _value to make Let out of.
 * \return Let with _value.
 */
Let* let_string(MutableCharacter* _value);
/**
 * \brief Move a String's memory to a Let.
 * \param _value to move memory from to Let.
 * \return Let with _value, without copy.
 */
Let* move_string(MutableString _value);
/**
 * \brief Make a Let from a Function value.
 * \param _value to make Let out of.
 * \return Let with _value.
 */
Let* let_function(Function _value);
/**
 * \brief Make a Let from a Array value.
 * \param _value to make Let out of.
 * \return Let with _value.
 */
Let* let_array(Array _value);
/**
 * \brief Move a Array's memory to a Let.
 * \param _value to move memory from to Let.
 * \return Let with _value, without copy.
 */
Let* move_array(MutableArray _value);
/**
 * \brief Make a Let from a Object value.
 * \param _value to make Let out of.
 * \return Let with _value.
 */
Let* let_object(ImmutableObject _value);
/**
 * \brief Move a Object's memory to a Let.
 * \param _value to move memory from to Let.
 * \return Let with _value, without copy.
 */
Let* move_object(MutableObject _value);
/**
 * \brief Produce a deep copy of a Let.
 * \param _let to copy.
 * \return Deep copy of _let.
 */
Let* let_copy(Let* _let);
/**
 * \brief Move memory from one Let to a new one.
 * \param _let to move from.
 * \return New Let with memory of _let.
 */
Let* let_move(Var* _let);
/**
 * \brief Make an empty Let value.
 * \return An empty Let.s
 */
Let* let_empty(void);
/**
 * \brief Test if a Let is empty.
 * \param _let to evaluate for emptiness.
 * \return true if Let is empty, false otherwise.
 */
MutableBoolean let_is_empty(Let* _let);

#ifdef __cplusplus
}
#endif

#endif /* THICC_THICC_STRUCT_VAR_H */

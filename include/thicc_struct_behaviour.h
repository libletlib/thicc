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
#ifndef THICC_THICC_STRUCT_BEHAVIOUR_H
#define THICC_THICC_STRUCT_BEHAVIOUR_H

/**
 * \file thicc_struct_behaviour.h
 * Includes declarations for behavioural struct that holds function pointers for type-based operations.
 */

#include "thicc_enum_rank.h"
#include "thicc_prelude.h"

/**
 * \brief Struct to hold behaviour of each type of Let in a standardised way.
 */
struct thicc_struct_behaviour {
  Rank rank;									/**< Rank of the type. See `thicc_enum_rank.h` for details. */
  void (*const deallocate)(Let*);				/**< Function to deallocate the memory owned by this Let. */
  MutableBoolean (*const as_boolean)(Let*);		/**< Function to convert this type to a Boolean. */
  MutableCharacter (*const as_character)(Let*); /**< Function to convert this type to a Character. */
  MutableNatural (*const as_natural)(Let*);		/**< Function to convert this type to a Natural. */
  MutableInteger (*const as_integer)(Let*);		/**< Function to convert this type to a Integer. */
  MutableReal (*const as_real)(Let*);			/**< Function to convert this type to a Real. */
  MutableComplex (*const as_complex)(Let*);		/**< Function to convert this type to a Complex. */
  MutableString (*const as_string)(Let*);		/**< Function to convert this type to a String. */
  MutableFunction (*const as_function)(Let*);	/**< Function to convert this type to a Function. */
  MutableArray (*const as_array)(Let*);			/**< Function to convert this type to an Array. */
  MutableObject (*const as_object)(Let*);		/**< Function to convert this type to an Object. */
  Let* (*const sum)(Let*, Let*);				/**< Function to compute the sum (+) operation for this type. */
  Let* (*const difference)(Let*, Let*);			/**< Function to compute the difference (-) operation for this type. */
  Let* (*const product)(Let*, Let*);			/**< Function to compute the product (*) operation for this type. */
  Let* (*const quotient)(Let*, Let*);			/**< Function to compute the quotient (/) operation for this type. */
  Let* (*const modulo)(Let*, Let*);				/**< Function to compute the modulo (%) operation for this type. */
  Let* (*const bit_and)(Let*, Let*);			/**< Function to compute the bitwise AND (&) operation for this type. */
  Let* (*const bit_or)(Let*, Let*);				/**< Function to compute the bitwise OR (|) operation for this type. */
  Let* (*const bit_xor)(Let*, Let*);			/**< Function to compute the bitwise XOR (^) operation for this type. */
  Let* (*const bit_not)(Let*);		  /**< Function to compute the boolean negation (!) operation for this type. */
  Let* (*const bit_complement)(Let*); /**< Function to compute the bitwise complement (~) operation for this type. */
  Let* (*const index_of)(Let*, Let*); /**< Function to compute the index-of ([]) operation for this type. */
  Let* (*const indirection)(Let*);	  /**< Function to compute the unary indirection (*) operation for this type. */
  Let* (*const negative)(Let*);		  /**< Function to compute the unary negative (-) operation for this type. */
  Let* (*const positive)(Let*);		  /**< Function to compute the unary positive (+) operation for this type. */
  MutableComparison (*const comparison)(Let*,
										Let*); /**< Function to compute the three-way (<=>) comparison for this type. */
};

extern Behaviour boolean_behaviour;
extern Behaviour character_behaviour;
extern Behaviour natural_behaviour;
extern Behaviour integer_behaviour;
extern Behaviour real_behaviour;
extern Behaviour complex_behaviour;
extern Behaviour string_behaviour;
extern Behaviour function_behaviour;
extern Behaviour array_behaviour;
extern Behaviour object_behaviour;

#endif /* THICC_THICC_STRUCT_BEHAVIOUR_H */

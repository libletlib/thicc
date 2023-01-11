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
#ifndef THICC_THICC_STRUCT_BEHAVIOUR_H
#define THICC_THICC_STRUCT_BEHAVIOUR_H

#include "thicc_enum_rank.h"
#include "thicc_prelude.h"

struct thicc_struct_behaviour {
  Rank rank;
  void (*const deallocate)(Let*);
  MutableBoolean (*const as_boolean)(Let*);
  MutableCharacter (*const as_character)(Let*);
  MutableNatural (*const as_natural)(Let*);
  MutableInteger (*const as_integer)(Let*);
  MutableReal (*const as_real)(Let*);
  MutableComplex (*const as_complex)(Let*);
  MutableString (*const as_string)(Let*);
  MutableFunction (*const as_function)(Let*);
  MutableArray (*const as_array)(Let*);
  MutableObject (*const as_object)(Let*);
  Let* (*const sum)(Let*, Let*);
  Let* (*const difference)(Let*, Let*);
  Let* (*const product)(Let*, Let*);
  Let* (*const quotient)(Let*, Let*);
  Let* (*const modulo)(Let*, Let*);
  Let* (*const bit_and)(Let*, Let*);
  Let* (*const bit_or)(Let*, Let*);
  Let* (*const bit_xor)(Let*, Let*);
  Let* (*const bit_not)(Let*);
  Let* (*const bit_complement)(Let*);
  Let* (*const index_of)(Let*, Let*);
  Let* (*const indirection)(Let*);
  Let* (*const negative)(Let*);
  Let* (*const positive)(Let*);
  MutableComparison (*const comparison)(Let*, Let*);
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

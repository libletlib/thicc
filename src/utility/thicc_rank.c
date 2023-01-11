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
#include "thicc_rank.h"
#include <thicc_interface.h>
#include <thicc_struct_var.h>

THICC_NODISCARD MutableBoolean rank_is_character(Let* _let) {
  switch (rank(_let)) {
	case character_rank:
	  return THICC_YES;
	default:
	  return THICC_NO;
  }
}

THICC_NODISCARD MutableBoolean rank_is_numeric(Let* _let) {
  switch (rank(_let)) {
	case natural_rank:
	  THICC_FALLTHROUGH
	case integer_rank:
	  THICC_FALLTHROUGH
	case real_rank:
	  THICC_FALLTHROUGH
	case complex_rank:
	  return THICC_YES;
	default:
	  return THICC_NO;
  }
}

THICC_NODISCARD MutableBoolean rank_is_integral(Let* _let) {
  switch (rank(_let)) {
	case natural_rank:
	  THICC_FALLTHROUGH
	case integer_rank:
	  return THICC_YES;
	default:
	  return THICC_NO;
  }
}

THICC_NODISCARD MutableBoolean rank_is_signed(Let* _let) {
  switch (rank(_let)) {
#if (THICC_CHAR_SIGNED == THICC_YES)
	case character_rank:
	  THICC_FALLTHROUGH
#endif
	case integer_rank:
	  THICC_FALLTHROUGH
	case real_rank:
	  THICC_FALLTHROUGH
	case complex_rank:
	  return THICC_YES;
	default:
	  return THICC_NO;
  }
}

THICC_NODISCARD MutableBoolean rank_is_unsigned(Let* _let) {
  switch (rank(_let)) {
#if (THICC_CHAR_UNSIGNED == THICC_YES)
	case character_rank:
	  THICC_FALLTHROUGH
#endif
	case natural_rank:
	  return THICC_YES;
	default:
	  return THICC_NO;
  }
}

THICC_NODISCARD MutableBoolean rank_is_floating_point(Let* _let) {
  switch (rank(_let)) {
	case real_rank:
	  THICC_FALLTHROUGH
	case complex_rank:
	  return THICC_YES;
	default:
	  return THICC_NO;
  }
}

THICC_NODISCARD MutableBoolean rank_is_string(Let* _let) {
  if (rank(_let) == string_rank)
	return THICC_YES;
  else
	return THICC_NO;
}

THICC_NODISCARD MutableBoolean rank_is_invokable(Let* _let) {
  switch (rank(_let)) {
	case function_rank:
	  return THICC_YES;
	default:
	  return THICC_NO;
  }
}

THICC_NODISCARD MutableBoolean rank_is_array(Let* _let) {
  if (rank(_let) == array_rank)
	return THICC_YES;
  else
	return THICC_NO;
}

THICC_NODISCARD MutableBoolean rank_is_indexable(Let* _let) {
  switch (rank(_let)) {
	case string_rank:
	  THICC_FALLTHROUGH
	case array_rank:
	  THICC_FALLTHROUGH
	case object_rank:
	  return THICC_YES;
	default:
	  return THICC_NO;
  }
}

THICC_NODISCARD MutableBoolean rank_is_object(Let* _let) {
  if (rank(_let) == object_rank)
	return THICC_YES;
  else
	return THICC_NO;
}

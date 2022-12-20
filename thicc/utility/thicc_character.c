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

#ifdef __cplusplus
extern "C" {
#endif

#include "thicc_character.h"
#include <thicc_struct_string.h>

THICC_NODISCARD MutableCharacterPromotedType character_to_number(Character _character) {
  switch (_character) {
	case '0':
	  return (CharacterPromotedType) 0;
	case '1':
	  return (CharacterPromotedType) 1;
	case '2':
	  return (CharacterPromotedType) 2;
	case '3':
	  return (CharacterPromotedType) 3;
	case '4':
	  return (CharacterPromotedType) 4;
	case '5':
	  return (CharacterPromotedType) 5;
	case '6':
	  return (CharacterPromotedType) 6;
	case '7':
	  return (CharacterPromotedType) 7;
	case '8':
	  return (CharacterPromotedType) 8;
	case '9':
	  return (CharacterPromotedType) 9;
	default:
	  return THICC_NONNUMERIC;
  }
}

THICC_NODISCARD MutableBoolean character_in_string(Character _needle, String _haystack) {
  Character* _haystack_pointer = _haystack.string;
  while (*_haystack_pointer != '\0') {
	if (_needle == *_haystack_pointer)
	  return THICC_YES;
	++_haystack_pointer;
  }
  return THICC_NO;
}

#ifdef __cplusplus
}
#endif

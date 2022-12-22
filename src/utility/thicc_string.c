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

#include "thicc_string.h"
#include <thicc_interface.h>
#include <thicc_struct_string.h>
#include "../core/thicc_memory.h"
#include "../core/thicc_struct_object.h"
#include "thicc_array.h"
#include "thicc_comparison.h"
#include "thicc_math.h"
#include "thicc_object.h"
#include <float.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

THICC_NODISCARD MutableString string_copy(String _original) {
  MutableString buffer = string_allocate(_original.length + 1);
  buffer.string = strcpy(buffer.string, _original.string);
  buffer.length = _original.length;
  return buffer;
}

THICC_NODISCARD MutableString string_copy_slice(String _original, Size _start, Size _stop) {
  Size			size   = _stop - _start;
  MutableString buffer = string_allocate(size + 1);
  buffer.string = strncpy(buffer.string, _original.string + _start, size);
  buffer.string[size] = '\0';
  buffer.length = size;
  return buffer;
}

THICC_NODISCARD MutableComparison string_compare(String _left, String _right) {
  if (string_is_empty(_left)) {
	if (string_is_empty(_right))
	  return THICC_EQUAL;
	return THICC_RIGHT_GREATER;
  }
  if (string_is_empty(_right))
	return THICC_LEFT_GREATER;
  return comparison_clamp(strcmp(_left.string, _right.string));
}

THICC_NODISCARD static char* string_tokenise_helper(MutableCharacter* THICC_RESTRICT _string,
													Character* THICC_RESTRICT _delimiter,
													MutableCharacter** THICC_RESTRICT _state) {
  MutableCharacter* THICC_RESTRICT end;

  if (!_string)
	_string = *_state;

  if (*_string == '\0')
	return THICC_NAUGHT;

  _string += strspn(_string, _delimiter);
  if (*_string == '\0')
	return THICC_NAUGHT;

  end = _string + strcspn(_string, _delimiter);
  if (*end == '\0') {
	*_state = end;
  } else {
	*end	= '\0';
	*_state = end + 1;
  }
  return _string;
}

THICC_NODISCARD MutableArray string_tokenise(MutableString _string, String _delimiter) {
  MutableCharacter* THICC_RESTRICT state;
  MutableCharacter* THICC_RESTRICT position = _string.string;
  MutableString token;
  MutableArray result;
  token.string = string_tokenise_helper(position, _delimiter.string, &state);
  result = array_from_elements(0);

  while (token.string) {
	Let token_string = let_string(token.string);
	result			 = array_concatenate(result, array_from_elements(1, &token_string));
	token.string	 = string_tokenise_helper(THICC_NAUGHT, _delimiter.string, &state);
	unlet(token_string);
  }

  return result;
}

THICC_NODISCARD MutableString string_filter_and(String _left, String _right) {
  MutableString buffer = string_allocate(_left.length + 1);
  MutableSize	index = 0, jindex = 0, kindex = 0;

  for (; index < _left.length; ++index)
	for (; jindex < _right.length; ++jindex)
	  if (_left.string[index] == _right.string[jindex]) {
		buffer.string[index] = _left.string[index];
		++kindex;
	  }

  buffer.length = kindex;
  return buffer;
}

THICC_NODISCARD MutableString string_filter_or(String _left, String _right) {
  MutableString buffer		  = string_allocate(_left.length + 1);
  MutableSize	index = 0, jindex = 0, kindex = 0;

  for (; index < _left.length; ++index)
	for (; jindex < _right.length; ++jindex)
	  if (_left.string[index] != _right.string[jindex]) {
		buffer.string[index] = _left.string[index];
		++kindex;
	  }

  buffer.length = kindex;
  return buffer;
}

THICC_NODISCARD MutableString string_filter_xor(String _left, String _right) {
  MutableString	  buffer		  = string_allocate(_left.length + _right.length + 1);
  Size			  shortest_length = THICC_MIN(_left.length, _right.length);
  Size			  longest_length  = THICC_MAX(_left.length, _right.length);
  MutableCharacter* THICC_RESTRICT longer_pointer  = THICC_LONGER_POINTER(_left.length, _left.string, _right.length, _right.string);
  MutableSize	  index = 0, jindex = 0;

  for (; index < longest_length; ++index) {
	if (index < shortest_length && _left.string[index] != _right.string[index]) {
	  buffer.string[jindex] = _left.string[index];
	  ++jindex;
	  buffer.string[jindex] = _right.string[index];
	  ++jindex;
	} else if (index >= shortest_length) {
	  buffer.string[jindex] = longer_pointer[index];
	  ++jindex;
	}
  }
  buffer.length = jindex;
  return buffer;
}

THICC_NODISCARD MutableString string_map_bit_not(String _string) {
  MutableSize	index  = 0;
  MutableString copy   = string_allocate(_string.length + 1);

  for (; index < _string.length; ++index)
	copy.string[index] = (Character) !(CharacterPromotedType) _string.string[index];

  return copy;
}

THICC_NODISCARD MutableString string_map_bit_complement(String _string) {
  MutableSize	index  = 0;
  MutableString copy   = string_allocate(_string.length + 1);
  copy.length = _string.length;

  for (; index < _string.length; ++index)
	copy.string[index] = (Character) ~(CharacterPromotedType) _string.string[index];

  return copy;
}

THICC_NODISCARD MutableString string_map_positive(String _string) {
#if THICC_CHAR_SIGNED
  MutableSize	index  = 0;
  MutableString copy   = string_allocate(_string.length + 1);
  copy.length = _string.length;

  for (; index < _string.length; ++index)
	copy.string[index] = (Character) + (CharacterPromotedType) _string.string[index];

  return copy;
#else
  return string_copy(_string);
#endif
}

THICC_NODISCARD MutableString string_map_negative(String _string) {
#if THICC_CHAR_SIGNED
  MutableSize	index  = 0;
  MutableString copy   = string_allocate(_string.length + 1);

  for (; index < _string.length; ++index)
	copy.string[index] = (Character) - (CharacterPromotedType) _string.string[index];

  return copy;
#else
  return string_copy(_string);
#endif
}

THICC_NODISCARD MutableString string_map_increment(MutableString _string) {
  MutableSize index	 = 0;

  for (; index < _string.length; ++index)
	++_string.string[index];

  return _string;
}

THICC_NODISCARD MutableString string_map_decrement(MutableString _string) {
  MutableSize index	 = 0;

  for (; index < _string.length; ++index)
	--_string.string[index];

  return _string;
}

THICC_NODISCARD MutableCharacter string_character_at(String _string, Integer _index) {
  Integer size = (Integer) _string.length - 1;

  if (_index >= 0 && _index < size)
	return _string.string[_index];
  if (_index >= size)
	return _string.string[size];
  return _string.string[THICC_ABS(_index) > size ? 0 : size + _index];
}

THICC_NODISCARD MutableString string_concatenate(String _left, String _right) {
  MutableString buffer = string_allocate(_left.length + _right.length + 1);
  buffer.length = _left.length + _right.length;
  buffer.string	= strcat(buffer.string, _left.string);
  buffer.string	= strcat(buffer.string, _right.string);
  return buffer;
}

THICC_NODISCARD MutableString string_remove_substring(String _original, String _substring) {
  MutableString buffer		   = string_allocate(_original.length);
  MutableSize	index		   = 0;
  MutableSize	jindex		   = 0;
  MutableSize   kindex         = 0;
  for (; jindex < _original.length; ++index, ++jindex) {
	if (comparison_equal(memcmp(_original.string + index, _substring.string, _substring.length))) {
	  jindex += _substring.length;
	  continue;
	}
	buffer.string[index] = _original.string[jindex];
	++kindex;
  }
  buffer.length = kindex;
  return buffer;
}

THICC_NODISCARD MutableString string_from_characters(Size _size, ...) {
  va_list		list;
  MutableString buffer = string_allocate(_size + 1);
  MutableSize	index  = 0;
  va_start(list, _size);
  for (; index < _size; ++index) {
	buffer.string[index] = (Character) va_arg(list, CharacterPromotedType);
  }
  va_end(list);
  buffer.length = _size;
  return buffer;
}

THICC_NODISCARD MutableSize characters_in_natural(Natural _number) {
  return ((Size) THICC_MAX(1, THICC_FLOOR(THICC_LOG10((Real) _number))) + 1);
}

THICC_NODISCARD MutableSize characters_in_integer(Integer _number) {
  return ((Size) THICC_MAX(1, THICC_FLOOR(THICC_LOG10((Real) _number))) + 2); /* sign */
}

THICC_NODISCARD MutableSize characters_in_real(Real _number) {
  MutableRealFmodStruct parts;
  MutableSize			integral; /* Zero needs a symbol too. */
  Size					fractional = LDBL_DIG;
  parts							   = math_real_modf(_number);
  integral						   = (Size) THICC_MAX(1, THICC_FLOOR(THICC_LOG10(parts.integral)));
  return integral + fractional + 2; /*sign, full stop*/
}

THICC_NODISCARD MutableSize characters_in_complex(Complex _number) {
  return characters_in_real(_number.real) + characters_in_real(_number.imaginary) + 1; /* imaginary i */
}

THICC_NODISCARD MutableString string_from_natural(Natural _number) {
  MutableString buffer = string_allocate(characters_in_natural(_number));
  sprintf(buffer.string, THICC_STRINGIFY(THICC_NATURAL_FORMAT), _number);
  buffer.length = string_length(buffer);
  return buffer;
}

THICC_NODISCARD MutableString string_from_integer(Integer _number) {
  MutableString buffer = string_allocate(characters_in_integer(_number));
  sprintf(buffer.string, THICC_STRINGIFY(THICC_INTEGER_FORMAT), _number);
  buffer.length = string_length(buffer);
  return buffer;
}

THICC_NODISCARD MutableString string_from_real(Real _number) {
  MutableString buffer = string_allocate(characters_in_real(_number));
  sprintf(buffer.string, THICC_STRINGIFY(THICC_REAL_FORMAT), _number);
  buffer.length = string_length(buffer);
  return buffer;
}

THICC_NODISCARD MutableString string_from_complex(Complex _number) {
  MutableString real_buffer		 = string_allocate(characters_in_real(_number.real));
  MutableString imaginary_buffer = string_allocate(characters_in_real(_number.imaginary) + 1); /* final i */
  MutableString result;
  sprintf(real_buffer.string, THICC_STRINGIFY(THICC_REAL_FORMAT), _number.real);
  sprintf(imaginary_buffer.string, THICC_STRINGIFY(THICC_IMAGINARY_FORMAT), _number.imaginary);
  real_buffer.length = string_length(real_buffer);
  imaginary_buffer.length = string_length(imaginary_buffer);
  result = string_concatenate(real_buffer, imaginary_buffer);
  free(real_buffer.string);
  free(imaginary_buffer.string);
  result.length = string_length(result);
  return result;
}

THICC_NODISCARD MutableString string_from_array(Array _array) {
  MutableString buffer = string_from_pointer("[");
  MutableString old;
  MutableSize	index = 0;

  if (_array.length != 0) {
	MutableString tail = as_string(_array.array[index]);
	buffer			   = string_concatenate(buffer, tail);
	free(tail.string);
	++index;

	if (index < _array.length) {
	  old	 = buffer;
	  tail = string_from_pointer(", ");
	  buffer = string_concatenate(buffer, tail);
	  free(old.string);
	}

	for (; index < _array.length; ++index) {
	  old	 = buffer;
	  tail	 = as_string(_array.array[index]);
	  buffer = string_concatenate(buffer, tail);
	  free(old.string);
	  free(tail.string);

	  if ((index + 1) < _array.length) {
		old	   = buffer;
		tail   = string_from_pointer(", ");
		buffer = string_concatenate(buffer, tail);
		free(old.string);
	  }
	}

	tail   = string_from_pointer("]");
	old	   = buffer;
	buffer = string_concatenate(buffer, tail);
	free(old.string);
	buffer.length = string_length(buffer);
	return buffer;
  }

  return string_copy(string_from_pointer("[]"));
}

THICC_NODISCARD static MutableString string_from_object_helper(Let* _let) {
  if (rank(*_let) == function_rank)
	return string_copy(string_from_pointer("function"));
  return as_string(*_let);
}

THICC_NODISCARD MutableString string_from_object(ImmutableObject _object) {
  String indent			  = string_from_pointer("\n\t\"");
  String key_value_delimiter = string_from_pointer("\": ");
  MutableString	  buffer = string_from_pointer("{\n\t\"");
  MutableString	  old;
  Size			  size	 = object_size(_object);
  Array			  keys	 = root_keys_from_pointer(_object);
  Array			  values = root_values_from_pointer(_object);
  MutableSize	  index	 = 0;

  if (size != 0) {
	MutableString tail = string_from_object_helper(&keys.array[index]);

	buffer = string_concatenate(buffer, tail);
	old	   = buffer;
	buffer = string_concatenate(buffer, key_value_delimiter);
	free(old.string);
	free(tail.string);
	tail = string_from_object_helper(&values.array[index]);

	old	   = buffer;
	buffer = string_concatenate(buffer, tail);
	free(old.string);
	free(tail.string);
	++index;

	if (index < size) {
	  old	 = buffer;
	  buffer = string_concatenate(buffer, indent);
	  free(old.string);
	}

	for (; index < size; ++index) {
	  tail = string_from_object_helper(&keys.array[index]);

	  old	 = buffer;
	  buffer = string_concatenate(buffer, tail);
	  free(tail.string);
	  free(old.string);

	  old	 = buffer;
	  buffer = string_concatenate(buffer, key_value_delimiter);
	  free(old.string);

	  tail = string_from_object_helper(&values.array[index]);

	  old	 = buffer;
	  buffer = string_concatenate(buffer, tail);
	  free(old.string);
	  free(tail.string);

	  if ((index + 1) < size) {
		old	   = buffer;
		buffer = string_concatenate(buffer, indent);
		free(old.string);
	  }
	}

	tail   = string_from_pointer("\n}");
	old	   = buffer;
	buffer = string_concatenate(buffer, tail);
	free(old.string);
	buffer.length = string_length(buffer);
	return buffer;
  }

  return string_copy(string_from_pointer("{}"));
}

THICC_NODISCARD MutableNatural string_to_natural(String _string) {
#if THICC_C89
  return strtoul(_string.string, THICC_NAUGHT, 0);
#else
  return strtoull(_string, THICC_NAUGHT, 0);
#endif
}

THICC_NODISCARD MutableInteger string_to_integer(String _string) {
#if THICC_C89
  return strtol(_string.string, THICC_NAUGHT, 0);
#else
  return strtoll(_string, THICC_NAUGHT, 0);
#endif
}

THICC_NODISCARD MutableReal string_to_real(String _string) {
#if THICC_C89
  return (Real) strtod(_string.string, THICC_NAUGHT);
#else
  return strtold(_string, THICC_NAUGHT);
#endif
}

THICC_NODISCARD MutableComplex string_to_complex(String _string) {
  char const* const i = strchr(_string.string, 'i');
  MutableSize		mid_sign;
  MutableString		real_part;
  MutableComplex	result;

  if (!i)
	return cmplx(string_to_real(_string), 0.0l);

  mid_sign	= strcspn(_string.string + 1, "+-");
  real_part = string_copy_slice(_string, 0, mid_sign);

  result = cmplx(string_to_real(real_part), string_to_real(string_from_pointer(_string.string + mid_sign)));
  free(real_part.string);
  return result;
}

#ifdef __cplusplus
}
#endif

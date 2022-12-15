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
#include "../core/thicc_interface.h"
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

THICC_NODISCARD MutableSize string_length(ImmutableString _string) {
  return strlen(_string);
}

THICC_NODISCARD MutableString string_copy(ImmutableString _original) {
  MutableString buffer = string_allocate(string_length(_original));
  return strcpy(buffer, _original);
}

THICC_NODISCARD MutableString string_copy_slice(ImmutableString _original, Size _start, Size _stop) {
  Size			size   = _stop - _start;
  MutableString buffer = string_allocate(size + 1);
  MutableString result = strncpy(buffer, _original + _start, size);
  result[size]		   = '\0';
  return result;
}

THICC_NODISCARD MutableComparison string_compare(ImmutableString _left, ImmutableString _right) {
  if (string_is_empty(_left)) {
	if (string_is_empty(_right))
	  return THICC_EQUAL;
	return THICC_RIGHT_GREATER;
  }
  if (string_is_empty(_right))
	return THICC_LEFT_GREATER;
  return comparison_clamp(strcmp(_left, _right));
}

THICC_NODISCARD static MutableString
string_tokenise_helper(MutableString _string, ImmutableString _delimiter, MutableString* _state) {
  MutableString end;

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

THICC_NODISCARD MutableArray string_tokenise(MutableString _string, ImmutableString _delimiter) {
  MutableString state, position = _string;
  MutableString token  = string_tokenise_helper(position, _delimiter, &state);
  MutableArray	result = array_from_elements(0);

  while (token) {
	Let token_string = let_string(token);
	result			 = array_concatenate(result, array_from_elements(1, &token_string));
	token			 = string_tokenise_helper(THICC_NAUGHT, _delimiter, &state);
	unlet(token_string);
  }

  return result;
}

THICC_NODISCARD MutableString string_filter_and(ImmutableString _left, ImmutableString _right) {
  Size			buffer_length = string_length(_left);
  Size			filter_length = string_length(_right);
  MutableString buffer		  = string_allocate(buffer_length + sizeof(char));
  MutableSize	index = 0, jindex = 0;

  for (; index < buffer_length; ++index)
	for (; jindex < filter_length; ++jindex)
	  if (_left[index] == _right[jindex])
		buffer[index] = _left[index];

  return buffer;
}

THICC_NODISCARD MutableString string_filter_or(ImmutableString _left, ImmutableString _right) {
  Size			buffer_length = string_length(_left);
  Size			filter_length = string_length(_right);
  MutableString buffer		  = string_allocate(buffer_length);
  MutableSize	index = 0, jindex = 0;

  for (; index < buffer_length; ++index)
	for (; jindex < filter_length; ++jindex)
	  if (_left[index] != _right[jindex])
		buffer[index] = _left[index];

  return buffer;
}

THICC_NODISCARD MutableString string_filter_xor(ImmutableString _left, ImmutableString _right) {
  Size			  left_length	  = string_length(_left);
  Size			  right_length	  = string_length(_right);
  MutableString	  buffer		  = string_allocate(left_length + right_length + 1);
  Size			  shortest_length = THICC_MIN(left_length, right_length);
  Size			  longest_length  = THICC_MAX(left_length, right_length);
  ImmutableString longer_pointer  = THICC_LONGER_POINTER(left_length, _left, right_length, _right);
  MutableSize	  index = 0, jindex = 0;

  for (; index < longest_length; ++index) {
	if (index < shortest_length && _left[index] != _right[index]) {
	  buffer[jindex] = _left[index];
	  ++jindex;
	  buffer[jindex] = _right[index];
	  ++jindex;
	} else if (index >= shortest_length) {
	  buffer[jindex] = longer_pointer[index];
	  ++jindex;
	}
  }
  return buffer;
}

THICC_NODISCARD MutableString string_map_bit_not(ImmutableString _string) {
  Size			length = string_length(_string);
  MutableSize	index  = 0;
  MutableString copy   = string_allocate(length + 1);

  for (; index < length; ++index)
	copy[index] = (Character) !(CharacterPromotedType) _string[index];

  return copy;
}

THICC_NODISCARD MutableString string_map_bit_complement(ImmutableString _string) {
  Size			length = string_length(_string);
  MutableSize	index  = 0;
  MutableString copy   = string_allocate(length + 1);

  for (; index < length; ++index)
	copy[index] = (Character) ~(CharacterPromotedType) _string[index];

  return copy;
}

THICC_NODISCARD MutableString string_map_positive(ImmutableString _string) {
#if THICC_CHAR_SIGNED
  Size			length = string_length(_string);
  MutableSize	index  = 0;
  MutableString copy   = string_allocate(length + 1);

  for (; index < length; ++index)
	copy[index] = (Character) + (CharacterPromotedType) _string[index];

  return copy;
#else
  return string_copy(_string);
#endif
}

THICC_NODISCARD MutableString string_map_negative(ImmutableString _string) {
#if THICC_CHAR_SIGNED
  Size			length = string_length(_string);
  MutableSize	index  = 0;
  MutableString copy   = string_allocate(length + 1);

  for (; index < length; ++index)
	copy[index] = (Character) - (CharacterPromotedType) _string[index];

  copy[index] = '\0';
  return copy;
#else
  return string_copy(_string);
#endif
}

THICC_NODISCARD MutableString string_map_increment(MutableString _string) {
  Size		  length = string_length(_string);
  MutableSize index	 = 0;

  for (; index < length; ++index)
	++_string[index];

  return _string;
}

THICC_NODISCARD MutableString string_map_decrement(MutableString _string) {
  Size		  length = string_length(_string);
  MutableSize index	 = 0;

  for (; index < length; ++index)
	--_string[index];

  return _string;
}

THICC_NODISCARD MutableCharacter string_character_at(ImmutableString _string, Integer _index) {
  Integer size = (Integer) string_length(_string) - 1;

  if (_index >= 0l && _index < size)
	return _string[_index];

  if (_index >= size)
	return _string[size];

  return _string[labs(_index) > size ? 0l : size + _index];
}

THICC_NODISCARD MutableString string_concatenate(ImmutableString _left, ImmutableString _right) {
  MutableString buffer = string_allocate(string_length(_left) + string_length(_right));
  buffer			   = strcat(buffer, _left);
  buffer			   = strcat(buffer, _right);
  return buffer;
}

THICC_NODISCARD String string_find_substring(ImmutableString _haystack, ImmutableString _needle) {
  return strstr(_haystack, _needle);
}

THICC_NODISCARD MutableString string_remove_substring(ImmutableString _original, ImmutableString _substring) {
  Size			size		   = string_length(_original);
  Size			substring_size = string_length(_substring);
  MutableString buffer		   = string_allocate(size);
  MutableSize	index		   = 0;
  MutableSize	jindex		   = 0;
  for (; jindex < size; ++index, ++jindex) {
	if (_original[jindex] != *_substring)
	  buffer[index] = _original[jindex];
	else if (comparison_equal(memcmp(_original + index, _substring, substring_size)))
	  jindex += substring_size;
	else
	  buffer[index] = _original[jindex];
  }
  return buffer;
}

THICC_NODISCARD MutableString string_empty(void) {
  return THICC_NAUGHT;
}

THICC_NODISCARD MutableBoolean string_is_empty(ImmutableString _string) {
  return _string == THICC_NAUGHT || *_string == '\0';
}

THICC_NODISCARD MutableString string_from_characters(Size _size, ...) {
  va_list		list;
  MutableString buffer = string_allocate(_size + 1);
  MutableSize	index  = 0;
  va_start(list, _size);
  for (; index < _size; ++index) {
	buffer[index] = (Character) va_arg(list, CharacterPromotedType);
  }
  va_end(list);
  buffer[index] = '\0';
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
  sprintf(buffer, THICC_STRINGIFY(THICC_NATURAL_FORMAT), _number);
  return buffer;
}

THICC_NODISCARD MutableString string_from_integer(Integer _number) {
  MutableString buffer = string_allocate(characters_in_integer(_number));
  sprintf(buffer, THICC_STRINGIFY(THICC_INTEGER_FORMAT), _number);
  return buffer;
}

THICC_NODISCARD MutableString string_from_real(Real _number) {
  MutableString buffer = string_allocate(characters_in_real(_number));
  sprintf(buffer, THICC_STRINGIFY(THICC_REAL_FORMAT), _number);
  return buffer;
}

THICC_NODISCARD MutableString string_from_complex(Complex _number) {
  MutableString real_buffer		 = string_allocate(characters_in_real(_number.real));
  MutableString imaginary_buffer = string_allocate(characters_in_real(_number.imaginary) + 1); /* final i */
  MutableString result;
  sprintf(real_buffer, THICC_STRINGIFY(THICC_REAL_FORMAT), _number.real);
  sprintf(imaginary_buffer, THICC_STRINGIFY(THICC_IMAGINARY_FORMAT), _number.imaginary);
  result = string_concatenate(real_buffer, imaginary_buffer);
  free(real_buffer);
  free(imaginary_buffer);
  return result;
}

THICC_NODISCARD MutableString string_from_array(ImmutableArray _array) {
  MutableString buffer = "[";
  MutableString old;
  Size			length = array_length(_array);
  MutableSize	index  = 0;

  if (length != 0) {
	MutableString tail = as_string(_array[index]);
	buffer			   = string_concatenate(buffer, tail);
	free(tail);
	++index;

	if (index < length) {
	  old	 = buffer;
	  tail	 = ", ";
	  buffer = string_concatenate(buffer, tail);
	  free(old);
	}

	for (; index < length; ++index) {
	  old	 = buffer;
	  tail	 = as_string(_array[index]);
	  buffer = string_concatenate(buffer, tail);
	  free(old);
	  free(tail);

	  if ((index + 1) < length) {
		old	   = buffer;
		tail   = ", ";
		buffer = string_concatenate(buffer, tail);
		free(old);
	  }
	}

	tail   = "]";
	old	   = buffer;
	buffer = string_concatenate(buffer, tail);
	free(old);
	return buffer;
  }

  return string_copy("[]");
}

THICC_NODISCARD static MutableString string_from_object_helper(Let* _let) {
  if (rank(*_let) == function_rank)
	return string_copy("function_type");
  return as_string(*_let);
}

THICC_NODISCARD MutableString string_from_object(ImmutableObject _object) {
  ImmutableString indent			  = "\n\t\"";
  ImmutableString key_value_delimiter = "\": ";
  MutableString	  buffer			  = "{\n\t\"";
  MutableString	  old;
  Size			  size	 = object_size(_object);
  Array			  keys	 = root_keys_from_pointer(_object);
  Array			  values = root_values_from_pointer(_object);
  MutableSize	  index	 = 0;

  if (size != 0) {
	MutableString tail = string_from_object_helper(&keys[index]);

	buffer = string_concatenate(buffer, tail);
	old	   = buffer;
	buffer = string_concatenate(buffer, key_value_delimiter);
	free(old);
	free(tail);
	tail = string_from_object_helper(&values[index]);

	old	   = buffer;
	buffer = string_concatenate(buffer, tail);
	free(old);
	free(tail);
	++index;

	if (index < size) {
	  old	 = buffer;
	  buffer = string_concatenate(buffer, indent);
	  free(old);
	}

	for (; index < size; ++index) {
	  tail = string_from_object_helper(&keys[index]);

	  old	 = buffer;
	  buffer = string_concatenate(buffer, tail);
	  free(tail);
	  free(old);

	  old	 = buffer;
	  buffer = string_concatenate(buffer, key_value_delimiter);
	  free(old);

	  tail = string_from_object_helper(&values[index]);

	  old	 = buffer;
	  buffer = string_concatenate(buffer, tail);
	  free(old);
	  free(tail);

	  if ((index + 1) < size) {
		old	   = buffer;
		buffer = string_concatenate(buffer, indent);
		free(old);
	  }
	}

	tail   = "\n}";
	old	   = buffer;
	buffer = string_concatenate(buffer, tail);
	free(old);
	return buffer;
  }

  return string_copy("{}");
}

THICC_NODISCARD MutableNatural string_to_natural(ImmutableString _string) {
#if THICC_C89
  return strtoul(_string, THICC_NAUGHT, 0);
#else
  return strtoull(_string, THICC_NAUGHT, 0);
#endif
}

THICC_NODISCARD MutableInteger string_to_integer(ImmutableString _string) {
#if THICC_C89
  return strtol(_string, THICC_NAUGHT, 0);
#else
  return strtoll(_string, THICC_NAUGHT, 0);
#endif
}

THICC_NODISCARD MutableReal string_to_real(ImmutableString _string) {
#if THICC_C89
  return (Real) strtod(_string, THICC_NAUGHT);
#else
  return strtold(_string, THICC_NAUGHT);
#endif
}

THICC_NODISCARD MutableComplex string_to_complex(ImmutableString _string) {
  char const* const i = strchr(_string, 'i');
  MutableSize		mid_sign;
  MutableString		real_part;
  MutableComplex	result;

  if (!i)
	return cmplx(string_to_real(_string), 0.0l);

  mid_sign	= strcspn(_string + 1, "+-");
  real_part = string_copy_slice(_string, 0, mid_sign);

  result = cmplx(string_to_real(real_part), string_to_real(_string + mid_sign));
  free(real_part);
  return result;
}

#ifdef __cplusplus
}
#endif

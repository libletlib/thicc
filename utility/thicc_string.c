/*
 * TTTTTTTTTTTTTTTTTTTTTTThhhhhhh               iiii                              CCCCCCCCCCCCC
 * T:::::::::::::::::::::Th:::::h              i::::i                          CCC::::::::::::C
 * T:::::::::::::::::::::Th:::::h               iiii                         CC:::::::::::::::C
 * T:::::TT:::::::TT:::::Th:::::h                                           C:::::CCCCCCCC::::C
 * TTTTTT  T:::::T  TTTTTT h::::h hhhhh       iiiiiii     cccccccccccccccc C:::::C       CCCCCC
 *         T:::::T         h::::hh:::::hhh    i:::::i   cc:::::::::::::::cC:::::C
 *         T:::::T         h::::::::::::::hh   i::::i  c:::::::::::::::::cC:::::C
 *         T:::::T         h:::::::hhh::::::h  i::::i c:::::::cccccc:::::cC:::::C
 *         T:::::T         h::::::h   h::::::h i::::i c::::::c     cccccccC:::::C
 *         T:::::T         h:::::h     h:::::h i::::i c:::::c             C:::::C
 *         T:::::T         h:::::h     h:::::h i::::i c:::::c             C:::::C
 *         T:::::T         h:::::h     h:::::h i::::i c::::::c     ccccccc C:::::C       CCCCCC
 *       TT:::::::TT       h:::::h     h:::::hi::::::ic:::::::cccccc:::::c  C:::::CCCCCCCC::::C
 *       T:::::::::T       h:::::h     h:::::hi::::::i c:::::::::::::::::c   CC:::::::::::::::C
 *       T:::::::::T       h:::::h     h:::::hi::::::i  cc:::::::::::::::c     CCC::::::::::::C
 *       TTTTTTTTTTT       hhhhhhh     hhhhhhhiiiiiiii    cccccccccccccccc        CCCCCCCCCCCCC
 *
 * Copyright 2021 - 2022 Ville Rissanen
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
 * following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following
 * disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 * following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifdef __cplusplus
extern "C"
{
#endif

#include "thicc_string.h"
#include "../core/thicc_memory.h"
#include "../core/thicc_struct_let.h"
#include "thicc_comparison.h"
#include "thicc_math.h"
#include <float.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

	MutableSize string_length(ImmutableString _string) {
		return strlen(_string);
	}

	MutableString string_copy(ImmutableString _original) {
		MutableString buffer = string_allocate(string_length(_original));
		return strcpy(buffer, _original);
	}

	MutableString string_copy_slice(ImmutableString _original, Size _start, Size _stop) {
		Size size = _stop - _start;
		MutableString buffer = string_allocate(size);
		return strncpy(buffer, _original+_start, size);
	}

	MutableComparison string_compare(ImmutableString _left, ImmutableString _right) {
		if(string_is_empty(_left)) {
			if(string_is_empty(_right))
				return THICC_EQUAL;
			return THICC_RIGHT_GREATER;
		}
		if(string_is_empty(_right))
			return THICC_LEFT_GREATER;
		return comparison_clamp(strcmp(_left, _right));
	}

	MutableString string_filter_and(ImmutableString _left, ImmutableString _right) {
		Size buffer_length = string_length(_left);
		Size filter_length = string_length(_right);
		MutableString buffer = string_allocate(buffer_length + sizeof(char));
		MutableSize index = 0, jindex = 0;
		for (; index < buffer_length; ++index)
			for (; jindex < filter_length; ++jindex)
				if (_left[index] == _right[jindex])
					buffer[index] = _left[index];
		return buffer;
	}

	MutableString string_filter_or(ImmutableString _left, ImmutableString _right) {
		Size buffer_length = string_length(_left);
		Size filter_length = string_length(_right);
		MutableString buffer = string_allocate(buffer_length);
		MutableSize index = 0, jindex = 0;
		for(; index < buffer_length; ++index)
		{
			for (; jindex < filter_length; ++jindex)
			{
				if (_left[index] != _right[jindex])
					buffer[index] = _left[index];
			}
		}
		return buffer;
	}

	MutableString string_filter_xor(ImmutableString _left, ImmutableString _right) {
		Size left_length = string_length(_left);
		Size right_length = string_length(_right);
		MutableString buffer = string_allocate(left_length+right_length+1);
		Size shortest_length = THICC_MIN(left_length, right_length);
		Size longest_length = THICC_MAX(left_length, right_length);
		ImmutableString longer_pointer = THICC_LONGER_POINTER(left_length, _left, right_length, _right);
		MutableSize index = 0, jindex = 0;
		for(; index < longest_length; ++index)
		{
			if (index < shortest_length && _left[index] != _right[index]) {
				buffer[jindex] = _left[index];
				++jindex;
				buffer[jindex] = _right[index];
				++jindex;
			}
			else if(index >= shortest_length) {
				buffer[jindex] = longer_pointer[index];
				++jindex;
			}
		}
		return buffer;
	}

	MutableString string_map_bit_not(ImmutableString _string) {
		Size length = string_length(_string);
		MutableSize index = 0;
		MutableString copy = string_allocate(length + 1);
		for(; index < length; ++index) {
			copy[index] = (Character) ! (CharacterPromotedType) _string[index];
		}
		return copy;
	}

	MutableString string_map_bit_complement(ImmutableString _string) {
		Size length = string_length(_string);
		MutableSize index = 0;
		MutableString copy = string_allocate(length + 1);
		for(; index < length; ++index) {
			copy[index] = (Character) ~ (CharacterPromotedType) _string[index];
		}
		return copy;
	}

	MutableString string_map_positive(ImmutableString _string) {
#if THICC_IF(THICC_CHAR_SIGNED)
		Size length = string_length(_string);
		MutableSize index = 0;
		MutableString copy = string_allocate(length + 1);
		for(; index < length; ++index) {
			copy[index] = (Character) + (CharacterPromotedType) _string[index];
		}
		return copy;
#else
	    return string_copy(_string);
#endif
	}

	MutableString string_map_negative(ImmutableString _string) {
#if THICC_IF(THICC_CHAR_SIGNED)
		Size length = string_length(_string);
		MutableSize index = 0;
		MutableString copy = string_allocate(length + 1);
		for(; index < length; ++index) {
			copy[index] = (Character) - (CharacterPromotedType) _string[index];
		}
		copy[index] = '\0';
		return copy;
#else
	    return string_copy(_string);
#endif
	}

	MutableString string_map_increment(MutableString _string) {
		Size length = string_length(_string);
		MutableSize index = 0;
		for(; index < length; ++index)
			++_string[index];
		return _string;
	}

	MutableString string_map_decrement(MutableString _string) {
		Size length = string_length(_string);
		MutableSize index = 0;
		for(; index < length; ++index)
			--_string[index];
		return _string;
	}

	MutableCharacter string_character_at(ImmutableString _string, Long _index) {
		Long size = (Long) string_length(_string) - 1;
		if(_index >= 0l && _index < size)
			return _string[_index];
		if(_index >= size)
			return _string[size];
		return _string[labs(_index) > size ? 0l : size + _index];
	}

	MutableString string_concatenate(ImmutableString _left, ImmutableString _right) {
		MutableString buffer = string_allocate(string_length(_left)+ string_length(_right));
		buffer = strcat(buffer, _left);
		buffer = strcat(buffer, _right);
		return buffer;
	}

	String string_find_substring(ImmutableString _haystack, ImmutableString _needle) {
		return strstr(_haystack, _needle);
	}

	MutableString string_remove_substring(ImmutableString _original, ImmutableString _substring) {
		Size size = string_length(_original);
		Size substring_size = string_length(_substring);
		MutableString buffer = string_allocate(size);
		MutableSize index = 0;
		MutableSize jindex = 0;
		for(; jindex < size; ++index, ++jindex) {
			if(_original[jindex] != *_substring) {
				buffer[index] = _original[jindex];
			} else if(comparison_equal(memcmp(_original+index, _substring, substring_size))) {
				jindex += substring_size;
			} else {
				buffer[index] = _original[jindex];
			}
		}
		return buffer;
	}

	MutableString string_remove_characters(ImmutableString _original, ImmutableString _characters) {
		Size size = string_length(_original);
		Size characters_size = string_length(_characters);
		MutableString buffer = string_allocate(size);
		MutableSize index = 0;
		MutableSize jindex = 0;
		MutableSize kindex = 0;
		for(;index < size; ++index) {
			for(;jindex < characters_size; ++jindex) {
				if(_original[index] == _characters[jindex])
					goto skip;
			}
			buffer[kindex] = _original[index];
			++kindex;
		skip:
			continue;
		}
		return buffer;
	}

	MutableString string_empty(void) {
		return THICC_NOTHING;
	}

	MutableBoolean string_is_empty(ImmutableString _string) {
		return _string == THICC_NOTHING || *_string == '\0';
	}

	MutableString string_from_characters(Size _size, ...) {
		va_list list;
		MutableString buffer = string_allocate(_size + 1);
		MutableSize index = 0;
		va_start(list, _size);
		for(;index < _size; ++index) {
			buffer[index] = (Character) va_arg(list, CharacterPromotedType);
		}
		va_end(list);
		buffer[index] = '\0';
		return buffer;
	}

	MutableString string_from_signed_characters(Size _size, ...) {
		va_list list;
		MutableString buffer = string_allocate(_size + 1);
		MutableSize index = 0;
		va_start(list, _size);
		for(;index < _size; ++index) {
			buffer[index] = (Character) va_arg(list, Integer);
		}
		va_end(list);
		buffer[index] = '\0';
		return buffer;
	}

	MutableString string_from_unsigned_characters(Size _size, ...) {
		va_list list;
		MutableString buffer = string_allocate(_size + 1);
		MutableSize index = 0;
		va_start(list, _size);
		for(;index < _size; ++index) {
			buffer[index] = (Character) va_arg(list, UnsignedCharacterPromotedType);
		}
		va_end(list);
		buffer[index] = '\0';
		return buffer;
	}

	MutableSize characters_in_float(Float _number) {
		MutableFloatFmodStruct parts;
		MutableSize integral; // Zero needs a symbol too.
		Size fractional = FLT_DIG;
		parts = math_float_modf(_number);
		integral = (Size) THICC_MAX(1, THICC_FLOORF(THICC_LOG10F(parts.integral)));
		return integral + fractional + 2; // sign, full stop
	}

	MutableSize characters_in_double(Double _number) {
		MutableDoubleFmodStruct parts;
		MutableSize integral; // Zero needs a symbol too.
		Size fractional = DBL_DIG;
		parts = math_double_modf(_number);
		integral = (Size) THICC_MAX(1, THICC_FLOORD(THICC_LOG10D(parts.integral)));
		return integral + fractional + 2; // sign, full stop
	}

	MutableSize characters_in_long_double(LongDouble _number) {
		MutableLongDoubleFmodStruct parts;
		MutableSize integral; // Zero needs a symbol too.
		Size fractional = LDBL_DIG;
		parts = math_long_double_modf(_number);
		integral = (Size) THICC_MAX(1, THICC_FLOORL(THICC_LOG10L(parts.integral)));
		return integral + fractional + 2; // sign, full stop
	}

	MutableString string_from_integer(Integer _number) {
		MutableString buffer = string_allocate(THICC_CHARACTERS_IN_INTEGER(_number));
		sprintf(buffer, "%i", _number);
		return buffer;
	}

	MutableString string_from_unsigned_integer(UnsignedInteger _number) {
		MutableString buffer = string_allocate(THICC_CHARACTERS_IN_INTEGER(_number));
		sprintf(buffer, "%u", _number);
		return buffer;
	}

	MutableString string_from_long(Long _number) {
		MutableString buffer = string_allocate(THICC_CHARACTERS_IN_INTEGER(_number));
		sprintf(buffer, "%li", _number);
		return buffer;
	}

	MutableString string_from_unsigned_long(UnsignedLong _number) {
		MutableString buffer = string_allocate(THICC_CHARACTERS_IN_INTEGER(_number));
		sprintf(buffer, "%lu", _number);
		return buffer;
	}

	MutableString string_from_float(Float _number) {
		MutableString buffer = string_allocate(characters_in_float( _number));
		sprintf(buffer, "%g", (Double) _number);
		return buffer;
	}

	MutableString string_from_double(Double _number) {
		MutableString buffer = string_allocate(characters_in_double( _number));
		sprintf(buffer, "%g", _number);
		return buffer;
	}

	MutableString string_from_long_double(LongDouble _number) {
		MutableString buffer = string_allocate(characters_in_long_double( _number));
		sprintf(buffer, "%Lg", _number);
		return buffer;
	}

#if THICC_IF(THICC_C89)

	MutableLet string_to_number(ImmutableString _string) {
		char const* const full_stop = strchr(_string, '.');
		if(full_stop) {
			return let_long_double(THICC_STRING_TO_FLOATING_POINT(_string, NULL));
		} else {
			char const* const minus = strchr(_string, '-');
			if(minus) {
				return let_long(THICC_STRING_TO_INTEGER(_string, NULL));
			} else {
				return let_unsigned_long(THICC_STRING_TO_UNSIGNED_INTEGER(_string, NULL));
			}
		}
	}

#endif

#ifdef __cplusplus
}
#endif

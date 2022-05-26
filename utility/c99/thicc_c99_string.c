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

#include "thicc_c99_string.h"
#include "../../core/thicc_memory.h"
#include "../../core/thicc_struct_let.h"
#include "../thicc_math_typedef.h"
#include <complex.h>
#include <stdio.h>
#include <string.h>

#if THICC_IF(THICC_C_AT_LEAST(1999))

#if THICC_IF(THICC_HAS_COMPLEX)
	MutableLet string_to_number(ImmutableString _string) {
		char const* const full_stop = strchr(_string, '.');
		if(full_stop) {
			return let_long_double(THICC_STRING_TO_FLOATING_POINT(_string, NULL));
		} else {
			char const* const minus = strchr(_string, '-');
			if(minus) {
				return let_long_long(THICC_STRING_TO_INTEGER(_string, NULL));
			} else {
				return let_unsigned_long_long(THICC_STRING_TO_UNSIGNED_INTEGER(_string, NULL));
			}
		}
	}
#else
	MutableLet string_to_number(ImmutableString _string) {
		char const* const full_stop = strchr(_string, '.');
		if(full_stop) {
			return let_long_double(THICC_STRING_TO_FLOATING_POINT(_string, NULL));
		} else {
			char const* const minus = strchr(_string, '-');
			if(minus) {
				return let_long_long(THICC_STRING_TO_INTEGER(_string, NULL));
			} else {
				return let_unsigned_long_long(THICC_STRING_TO_UNSIGNED_INTEGER(_string, NULL));
			}
		}
	}
#endif

MutableString string_from_long_long(LongLong _number) {
	MutableString buffer = string_allocate(THICC_CHARACTERS_IN_INTEGER(_number));
	sprintf(buffer, "%lli", _number);
	return buffer;
}

MutableString string_from_unsigned_long_long(UnsignedLongLong _number) {
	MutableString buffer = string_allocate(THICC_CHARACTERS_IN_INTEGER(_number));
	sprintf(buffer, "%llu", _number);
	return buffer;
}

	#if THICC_IF(THICC_HAS_COMPLEX)
MutableSize characters_in_float_complex(FloatComplex _number) {
	return characters_in_float(crealf(_number)) + characters_in_float(cimagf(_number)) + 1; // Add one for imag i.
}

MutableSize characters_in_double_complex(DoubleComplex _number) {
	return characters_in_double(creal(_number)) + characters_in_double(cimag(_number)) + 1; // Add one for imag i.
}

MutableSize characters_in_long_double_complex(LongDoubleComplex _number) {
	return characters_in_long_double(creall(_number)) + characters_in_long_double(cimagl(_number)) + 1; // Add one for imag i.
}

MutableString string_from_float_complex(FloatComplex _number) {
	MutableString buffer = string_allocate(characters_in_float_complex(_number));
	ptrdiff_t real_length = 0;
	ptrdiff_t imaginary_length = 0;
	sprintf(buffer, "%g%tn", (Double) crealf(_number), &real_length);
	if(cimagf(_number) < +0.0f) {
		buffer[real_length] = '+';
		++real_length;
	}
	sprintf(buffer+real_length, "%g%tn", (Double) cimagf(_number), &imaginary_length);
	buffer[real_length+imaginary_length] = 'i';
	return buffer;
}

MutableString string_from_double_complex(DoubleComplex _number) {
	MutableString buffer = string_allocate(characters_in_double_complex(_number));
	ptrdiff_t real_length = 0;
	ptrdiff_t imaginary_length = 0;
	sprintf(buffer, "%g%tn", creal(_number), &real_length);
	if(cimag(_number) < +0.0) {
		buffer[real_length] = '+';
		++real_length;
	}
	sprintf(buffer+real_length, "%g%tn", cimag(_number), &imaginary_length);
	buffer[real_length+imaginary_length] = 'i';
	return buffer;
}

MutableString string_from_long_double_complex(LongDoubleComplex _number) {
	MutableString buffer = string_allocate(characters_in_long_double_complex(_number));
	ptrdiff_t real_length = 0;
	ptrdiff_t imaginary_length = 0;
	sprintf(buffer, "%Lg%tn", creall(_number), &real_length);
	if(cimagl(_number) < +0.0l) {
		buffer[real_length] = '+';
		++real_length;
	}
	sprintf(buffer+real_length, "%Lg%tn", cimagl(_number), &imaginary_length);
	buffer[real_length+imaginary_length] = 'i';
	return buffer;
}


	#endif

#endif

#ifdef __cplusplus
}
#endif

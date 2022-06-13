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

#include "thicc_c99_bit_or.h"
#include "../../core/thicc_struct_let.h"
#include "../../utility/c99/thicc_c99_complex.h"
#include "../../utility/thicc_float.h"

#if THICC_IF(THICC_C_AT_LEAST(1999))

	MutableLet long_long_bit_or(Let _left, Let _right) {
		return let_long_long(_left.value.long_long_type | _right.value.long_long_type);
	}

	MutableLet unsigned_long_long_bit_or(Let _left, Let _right) {
		return let_unsigned_long_long(_left.value.unsigned_long_long_type | _right.value.unsigned_long_long_type);
	}

#if THICC_IF(THICC_HAS_STD_COMPLEX)
	MutableLet float_complex_bit_or(Let _left, Let _right) {
		MutableFloatBytes left_real, right_real, left_imaginary, right_imaginary;
		left_real.real = crealf(_left.value.float_complex_type);
		right_real.real = crealf(_right.value.float_complex_type);
		left_imaginary.real = cimagf(_left.value.float_complex_type);
		right_imaginary.real = cimagf(_right.value.float_complex_type);
		return let_float_complex(THICC_COMPLEXF(float_byte_or(left_real, right_real).real, float_byte_or(left_imaginary, right_imaginary).real));
	}

	MutableLet double_complex_bit_or(Let _left, Let _right) {
		MutableDoubleBytes left_real, right_real, left_imaginary, right_imaginary;
		left_real.real = creal(_left.value.double_complex_type);
		right_real.real = creal(_right.value.double_complex_type);
		left_imaginary.real = cimag(_left.value.double_complex_type);
		right_imaginary.real = cimag(_right.value.double_complex_type);
		return let_double_complex(THICC_COMPLEXD(double_byte_or(left_real, right_real).real, double_byte_or(left_imaginary, right_imaginary).real));
	}

	MutableLet long_double_complex_bit_or(Let _left, Let _right) {
		MutableLongDoubleBytes left_real, right_real, left_imaginary, right_imaginary;
		left_real.real = creall(_left.value.long_double_complex_type);
		right_real.real = creall(_right.value.long_double_complex_type);
		left_imaginary.real = cimagl(_left.value.long_double_complex_type);
		right_imaginary.real = cimagl(_right.value.long_double_complex_type);
		return let_long_double_complex(THICC_COMPLEXL(long_double_byte_or(left_real, right_real).real, long_double_byte_or(left_imaginary, right_imaginary).real));
	}
#endif

#endif

#ifdef __cplusplus
}
#endif

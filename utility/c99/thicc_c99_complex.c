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

#include "thicc_c99_complex.h"

#if THICC_IF(THICC_HAS_STD_COMPLEX)

	MutableBoolean complex_float_equal(FloatComplex _left, FloatComplex _right) {
		if(math_float_equal(crealf(_left), crealf(_right)) && math_float_equal(cimagf(_left), cimagf(_right)))
			return THICC_YES;
		return THICC_NO;
	}

	MutableBoolean complex_double_equal(DoubleComplex _left, DoubleComplex _right) {
		if(math_double_equal(creal(_left), creal(_right)) && math_double_equal(cimag(_left), cimag(_right)))
			return THICC_YES;
		return THICC_NO;
	}

	MutableBoolean complex_long_double_equal(LongDoubleComplex _left, LongDoubleComplex _right) {
		if(math_long_double_equal(creall(_left), creall(_right)) && math_long_double_equal(cimagl(_left), cimagl(_right)))
			return THICC_YES;
		return THICC_NO;
	}

	MutableComparison complex_float_comparison(FloatComplex _left, FloatComplex _right) {
		if(complex_float_equal(_left, _right))
			return THICC_EQUAL;
		if(crealf(_left) > crealf(_right))
			return THICC_LEFT_GREATER;
		if(crealf(_right) > crealf(_left))
			return THICC_RIGHT_GREATER;
		if(cimagf(_left) > cimagf(_right))
			return THICC_LEFT_GREATER;
		return THICC_RIGHT_GREATER;
	}

	MutableComparison complex_double_comparison(DoubleComplex _left, DoubleComplex _right) {
		if(complex_double_equal(_left, _right))
			return THICC_EQUAL;
		if(creal(_left) > creal(_right))
			return THICC_LEFT_GREATER;
		if(creal(_right) > creal(_left))
			return THICC_RIGHT_GREATER;
		if(cimag(_left) > cimag(_right))
			return THICC_LEFT_GREATER;
		return THICC_RIGHT_GREATER;
	}

	MutableComparison complex_long_double_comparison(LongDoubleComplex _left, LongDoubleComplex _right) {
		if(complex_long_double_equal(_left, _right))
			return THICC_EQUAL;
		if(creall(_left) > creall(_right))
			return THICC_LEFT_GREATER;
		if(creall(_right) > creall(_left))
			return THICC_RIGHT_GREATER;
		if(cimagl(_left) > cimagl(_right))
			return THICC_LEFT_GREATER;
		return THICC_RIGHT_GREATER;
	}

#endif

#ifdef __cplusplus
}
#endif

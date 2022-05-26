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
#ifndef THICC_C99_COMPLEX_H
#define THICC_C99_COMPLEX_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "../../core/thicc_typedef.h"

#if THICC_IF(THICC_HAS_COMPLEX)
	#include <complex.h>
	#include "../thicc_math.h"
	#undef THICC_IMAGINARYF
	#undef THICC_IMAGINARYD
	#undef THICC_IMAGINARYL
	#if THICC_IF(THICC_HAS_IMAGINARY)
		#define THICC_IMAGINARYF ((Float)_Imaginary_I)
		#define THICC_IMAGINARYD ((DoubleComplex)_Imaginary_I)
		#define THICC_IMAGINARYL ((LongDoubleComplex)_Imaginary_I)
	#else
		#define THICC_IMAGINARYF ((Float)_Complex_I)
		#define THICC_IMAGINARYD ((DoubleComplex)_Complex_I)
		#define THICC_IMAGINARYL ((LongDoubleComplex)_Complex_I)
	#endif

	#undef THICC_COMPLEXF
	#undef THICC_COMPLEXD
	#undef THICC_COMPLEXL
	#if THICC_IF(THICC_C_AT_LEAST(2011))
		#define THICC_COMPLEXF(_real, _imaginary) CMPLXF(_real, _imaginary)
		#define THICC_COMPLEXD(_real, _imaginary) CMPLX(_real, _imaginary)
		#define THICC_COMPLEXL(_real, _imaginary) CMPLXL(_real, _imaginary)
	#else
		#define THICC_COMPLEXF(_real, _imaginary)                                                                      \
			((FloatComplex)(((Float)(_real)) + (THICC_IMAGINARYF) * ((Float)(_imaginary))))
		#define THICC_COMPLEXD(_real, _imaginary)                                                                      \
			((DoubleComplex)(((Double)(_real)) + (THICC_IMAGINARYD) * ((Double)(_imaginary))))
		#define THICC_COMPLEXL(_real, _imaginary)                                                                      \
			((LongDoubleComplex)(((LongDouble)(_real)) + (THICC_IMAGINARYL) * ((LongDouble)(_imaginary))))
	#endif

	#undef THICC_COMPLEX_POWERF
	#undef THICC_COMPLEX_POWERD
	#undef THICC_COMPLEX_POWERL
	#define THICC_COMPLEX_POWERF(_base, _exponent) (cpowf(_base, _exponent))
	#define THICC_COMPLEX_POWERD(_base, _exponent) (cpow(_base, _exponent))
	#define THICC_COMPLEX_POWERL(_base, _exponent) (cpowl(_base, _exponent))

	#undef THICC_COMPLEX_LOGARITHMF
	#undef THICC_COMPLEX_LOGARITHMD
	#undef THICC_COMPLEX_LOGARITHML
	#define THICC_COMPLEX_LOGARITHMF(_base, _anti_logarithm) (clogf(_anti_logarithm)/clogf(_base))
	#define THICC_COMPLEX_LOGARITHMD(_base, _anti_logarithm) (clog(_anti_logarithm)/clog(_base))
	#define THICC_COMPLEX_LOGARITHML(_base, _anti_logarithm) (clogl(_anti_logarithm)/clogl(_base))

	#undef THICC_COMPLEX_ROOTF
	#undef THICC_COMPLEX_ROOTD
	#undef THICC_COMPLEX_ROOTL
	#define THICC_COMPLEX_ROOTF(_degree, _radicand) (THICC_COMPLEX_POWERF(_degree, 1.0f / (_radicand)))
	#define THICC_COMPLEX_ROOTD(_degree, _radicand) (THICC_COMPLEX_POWERD(_degree, 1.0 / (_radicand)))
	#define THICC_COMPLEX_ROOTL(_degree, _radicand) (THICC_COMPLEX_POWERL(_degree, 1.0l / (_radicand)))

	MutableBoolean complex_float_equal(FloatComplex, FloatComplex);
	MutableBoolean complex_double_equal(DoubleComplex, DoubleComplex);
	MutableBoolean complex_long_double_equal(LongDoubleComplex, LongDoubleComplex);
	MutableComparison complex_float_comparison(FloatComplex, FloatComplex);
	MutableComparison complex_double_comparison(DoubleComplex, DoubleComplex);
	MutableComparison complex_long_double_comparison(LongDoubleComplex, LongDoubleComplex);
#endif

#ifdef __cplusplus
}
#endif

#endif//THICC_C99_COMPLEX_H

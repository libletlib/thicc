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

#ifndef THICC_MATH_TYPEDEF_H
#define THICC_MATH_TYPEDEF_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../core/thicc_typedef.h"
#include <math.h>

#undef THICC_FABSF
#undef THICC_FABSD
#undef THICC_FABSL
#define THICC_FABSD(_value) (fabs(_value))
#if THICC_IF(THICC_C89)
	#define THICC_FABSF(_value) ((Float) fabs((Double) (_value)))
	#define THICC_FABSL(_value) ((LongDouble) fabs((Double) (_value)))
#else
	#define THICC_FABSF(_value) (fabsf(_value))
	#define THICC_FABSL(_value) (fabsl(_value))
#endif

#undef THICC_FMODF
#undef THICC_FMODD
#undef THICC_FMODL
#define THICC_FMODD(_left, _right) (fmod(_left, _right))
#if THICC_IF(THICC_C89)
	#define THICC_FMODF(_left, _right) ((Float) THICC_FMODD((Double) (_left), (Double) (_right)))
	#define THICC_FMODL(_left, _right) ((LongDouble) THICC_FMODD((Double) (_left), (Double) (_right)))
#else
	#define THICC_FMODF(_left, _right) (fmodf(_left, _right))
	#define THICC_FMODL(_left, _right) (fmodl(_left, _right))
#endif

#undef THICC_POWERF
#undef THICC_POWERD
#undef THICC_POWERL
#define THICC_POWERD(_base, _exponent) (pow(_base, _exponent))
#if THICC_IF(THICC_C89)
	#define THICC_POWERF(_base, _exponent) ((Float) THICC_POWERD((Double) (_base), (Double) (_exponent)))
	#define THICC_POWERL(_base, _exponent) ((LongDouble) THICC_POWERD((Double) (_base), (Double) (_exponent)))
#else
	#define THICC_POWERF(_base, _exponent) (powf(_base, _exponent))
	#define THICC_POWERL(_base, _exponent) (powl(_base, _exponent))
#endif

#undef THICC_ROOTF
#undef THICC_ROOTD
#undef THICC_ROOTL
#define THICC_ROOTF(_degree, _radicand) (THICC_POWERF(_degree, 1.0f / (_radicand)))
#define THICC_ROOTD(_degree, _radicand) (THICC_POWERD(_degree, 1.0 / (_radicand)))
#define THICC_ROOTL(_degree, _radicand) (THICC_POWERL(_degree, 1.0l / (_radicand)))

#undef THICC_LOG10F
#undef THICC_LOG10D
#undef THICC_LOG10L
#define THICC_LOG10D(_anti_logarithm) (log10(_anti_logarithm))
#if THICC_IF(THICC_C89)
	#define THICC_LOG10F(_anti_logarithm) ((Float) THICC_LOG10D((Double) (_anti_logarithm)))
	#define THICC_LOG10L(_anti_logarithm) ((LongDouble) THICC_LOG10D((Double) (_anti_logarithm)))
#else
	#define THICC_LOG10F(_anti_logarithm) (log10f(_anti_logarithm))
	#define THICC_LOG10L(_anti_logarithm) (log10l(_anti_logarithm))
#endif

#undef THICC_LNF
#undef THICC_LND
#undef THICC_LNL
#define THICC_LND(_anti_logarithm) (log(_anti_logarithm))
#if THICC_IF(THICC_C89)
	#define THICC_LNF(_anti_logarithm) ((Float) THICC_LOG10D((Double) (_anti_logarithm)))
	#define THICC_LNL(_anti_logarithm) ((LongDouble) THICC_LOG10D((Double) (_anti_logarithm)))
#else
	#define THICC_LNF(_anti_logarithm) (logf(_anti_logarithm))
	#define THICC_LNL(_anti_logarithm) (logl(_anti_logarithm))
#endif

#undef THICC_LOGARITHMF
#undef THICC_LOGARITHMD
#undef THICC_LOGARITHML
#define THICC_LOGARITHMF(_base, _anti_logarithm) (THICC_LNF(_anti_logarithm) / THICC_LNF(_base))
#define THICC_LOGARITHMD(_base, _anti_logarithm) (THICC_LND(_anti_logarithm) / THICC_LND(_base))
#define THICC_LOGARITHML(_base, _anti_logarithm) (THICC_LNL(_anti_logarithm) / THICC_LNL(_base))

#undef THICC_FLOORF
#undef THICC_FLOORD
#undef THICC_FLOORL
#define THICC_FLOORD(_value) (floor(_value))
#if THICC_IF(THICC_C89)
	#define THICC_FLOORF(_value) ((Float) THICC_FLOORD((Double) (_value)))
	#define THICC_FLOORL(_value) ((LongDouble) THICC_FLOORD((Double) (_value)))
#else
	#define THICC_FLOORF(_value) (floorf(_value))
	#define THICC_FLOORL(_value) (floorl(_value))
#endif

#undef THICC_CEILF
#undef THICC_CEILD
#undef THICC_CEILL
#define THICC_CEILD(_value) (ceil(_value))
#if THICC_IF(THICC_C89)
#define THICC_CEILF(_value) ((Float) THICC_CEILD((Double) (_value)))
#define THICC_CEILL(_value) ((LongDouble) THICC_CEILD((Double) (_value)))
#else
#define THICC_CEILF(_value) ceilf(_value)
#define THICC_CEILL(_value) ceill(_value)
#endif

#undef THICC_ROUNDF
#undef THICC_ROUNDD
#undef THICC_ROUNDL
#if THICC_IF(THICC_C89)
#define THICC_ROUNDF(_value) math_float_round(_value)
#define THICC_ROUNDD(_value) math_double_round(_value)
#define THICC_ROUNDL(_value) math_long_double_round(_value)
#else
#define THICC_ROUNDF(_value) nearbyintf(_value)
#define THICC_ROUNDD(_value) nearbyint(_value)
#define THICC_ROUNDL(_value) nearbyintl(_value)
#endif

#undef THICC_MIN
#undef THICC_MAX
#define THICC_MIN(_left, _right) ((_left) > (_right) ? (_right) : (_left))
#define THICC_MAX(_left, _right) ((_left) < (_right) ? (_right) : (_left))

#undef THICC_SHORTER_POINTER
#undef THICC_LONGER_POINTER
#define THICC_SHORTER_POINTER(_left_length, _left_pointer, _right_length, _right_pointer) ( \
	(_left_length) > (_right_length) ? (_right_pointer) : (_left_pointer))
#define THICC_LONGER_POINTER(_left_length, _left_pointer, _right_length, _right_pointer) ( \
	(_left_length) < (_right_length) ? (_right_pointer) : (_left_pointer))

	typedef struct thicc_struct_float_fmod
	{
		MutableFloat integral;
		MutableFloat fractional;
	} MutableFloatFmodStruct;

	typedef struct thicc_struct_double_fmod
	{
		MutableDouble integral;
		MutableDouble fractional;
	} MutableDoubleFmodStruct;

	typedef struct thicc_struct_long_double_fmod
	{
		MutableLongDouble integral;
		MutableLongDouble fractional;
	} MutableLongDoubleFmodStruct;

	typedef MutableFloatFmodStruct const FloatFmodStruct;
	typedef MutableDoubleFmodStruct const DoubleFmodStruct;
	typedef MutableLongDoubleFmodStruct const LongDoubleFmodStruct;

#ifdef __cplusplus
}
#endif
#endif//THICC_MATH_TYPEDEF_H

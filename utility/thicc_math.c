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

#include "thicc_math.h"
#include <float.h>

#if THICC_IF(THICC_C89)

	MutableFloatFmodStruct math_float_modf(Float _float) {
		MutableDouble integral;
		Float fractional = (Float) modf((Double) _float, &integral);
		MutableFloatFmodStruct result;
		result.integral = (Float) integral;
		result.fractional = fractional;
		return result;
	}

	MutableDoubleFmodStruct math_double_modf(Double _double) {
		MutableDouble integral;
		Double fractional = modf(_double, &integral);
		MutableDoubleFmodStruct result;
		result.integral = integral;
		result.fractional = fractional;
		return result;
	}

	MutableLongDoubleFmodStruct math_long_double_modf(LongDouble _float) {
		MutableDouble integral;
		LongDouble fractional = (LongDouble) modf((Double) _float, &integral);
		MutableLongDoubleFmodStruct result;
		result.integral = (LongDouble) integral;
		result.fractional = fractional;
		return result;
	}

#endif

	MutableBoolean math_float_equal(Float _left, Float _right) {
		Float absolute_left = THICC_FABSF(_left), absolute_right = THICC_FABSF(_right);
		return THICC_FABSF(_left - _right)
		       <= ((absolute_left > absolute_right ? absolute_right : absolute_left)
		           * FLT_EPSILON);
	}

	MutableBoolean math_double_equal(Double _left, Double _right) {
		Double absolute_left = THICC_FABSD(_left), absolute_right = THICC_FABSD(_right);
		return THICC_FABSD(_left - _right)
		       <= ((absolute_left > absolute_right ? absolute_right : absolute_left)
		           * DBL_EPSILON);
	}

	MutableBoolean math_long_double_equal(LongDouble _left, LongDouble _right) {
		LongDouble absolute_left = THICC_FABSL(_left), absolute_right = THICC_FABSL(_right);
		return THICC_FABSL(_left - _right)
		       <= ((absolute_left > absolute_right ? absolute_right : absolute_left)
		           * LDBL_EPSILON);
	}

	MutableComparison math_float_comparison(Float _left, Float _right) {
		if(math_float_equal(_left, _right))
			return THICC_EQUAL;
		if(_left > _right)
			return THICC_LEFT_GREATER;
		if(_right > _left)
			return THICC_RIGHT_GREATER;
	}

	MutableComparison math_double_comparison(Double _left, Double _right) {
		if(math_double_equal(_left, _right))
			return THICC_EQUAL;
		if(_left > _right)
			return THICC_LEFT_GREATER;
		if(_right > _left)
			return THICC_RIGHT_GREATER;
	}

	MutableComparison math_long_double_comparison(LongDouble _left, LongDouble _right) {
		if(math_long_double_equal(_left, _right))
			return THICC_EQUAL;
		if(_left > _right)
			return THICC_LEFT_GREATER;
		if(_right > _left)
			return THICC_RIGHT_GREATER;
	}

	MutableFloat math_float_round(Float _float) {
		MutableFloatFmodStruct float_parts;
		switch(FLT_ROUNDS) {
			case 0: // Toward Zero
				return _float >= 0.0f ? THICC_FLOORF(_float) : THICC_CEILF(_float);
			case 1: // Toward Nearest
			nearest:
				float_parts = math_float_modf(_float);
				return float_parts.fractional >= 0.5f ? THICC_CEILF(_float) : float_parts.integral;
			case 2: // Towards Positive Infinity
				return THICC_CEILF(_float);
			case 3: // Towards Negative Infinity
				return THICC_FLOORF(_float);
			default:
				goto nearest;
		}
	}

	MutableDouble math_double_round(Double _double) {
		MutableDoubleFmodStruct parts;
		switch(FLT_ROUNDS) {
			case 0: // Toward Zero
				return _double >= 0.0 ? THICC_FLOORD(_double) : THICC_CEILD(_double);
			case 1: // Toward Nearest
			nearest:
				parts = math_double_modf(_double);
				return parts.fractional >= 0.5 ? THICC_CEILD(_double) : parts.integral;
			case 2: // Towards Positive Infinity
				return THICC_CEILD(_double);
			case 3: // Towards Negative Infinity
				return THICC_FLOORD(_double);
			default:
				goto nearest;
		}
	}

	MutableLongDouble math_long_double_round(LongDouble _long_double) {
		MutableLongDoubleFmodStruct parts;
		switch(FLT_ROUNDS) {
			case 0: // Toward Zero
				return _long_double >= 0.0l ? THICC_FLOORL(_long_double) : THICC_CEILL(_long_double);
			case 1: // Toward Nearest
			nearest:
				parts = math_long_double_modf(_long_double);
				return parts.fractional >= 0.5l ? THICC_CEILL(_long_double) : parts.integral;
			case 2: // Towards Positive Infinity
				return THICC_CEILL(_long_double);
			case 3: // Towards Negative Infinity
				return THICC_FLOORL(_long_double);
			default:
				goto nearest;
		}
	}

#ifdef __cplusplus
}
#endif

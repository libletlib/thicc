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
 * docs and/or other materials provided with the distribution.
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

#include "thicc_math.h"
#include <float.h>

THICC_NODISCARD MutableRealFmodStruct math_real_modf(Real _float) {
#if THICC_C89
  double				integral;
  Real					fractional = (Real) modf((double) _float, &integral);
  MutableRealFmodStruct result;
  result.integral	= (Real) integral;
  result.fractional = fractional;
  return result;
#else
  MutableReal			integral;
  Real					fractional = modfl(_float, &integral);
  MutableRealFmodStruct result;
  result.integral	= integral;
  result.fractional = fractional;
  return result;
#endif
}

#if THICC_C89
THICC_NODISCARD MutableReal math_real_round(Real _long_double) {
  MutableRealFmodStruct parts;
  switch (FLT_ROUNDS) {
	case 0: /* Toward Zero */
	  return _long_double >= 0.0l ? THICC_FLOOR(_long_double) : THICC_CEIL(_long_double);
	case 1: /* Toward Nearest */
	nearest:
	  parts = math_real_modf(_long_double);
	  return parts.fractional >= 0.5l ? THICC_CEIL(_long_double) : parts.integral;
	case 2: /* Towards Positive Infinity */
	  return THICC_CEIL(_long_double);
	case 3: /* Towards Negative Infinity */
	  return THICC_FLOOR(_long_double);
	default:
	  goto nearest;
  }
}
#endif

THICC_NODISCARD MutableBoolean math_real_equal(Real _left, Real _right) {
  Real absolute_left = THICC_FABS(_left), absolute_right = THICC_FABS(_right);
  return THICC_FABS(_left - _right) <=
		 ((absolute_left > absolute_right ? absolute_right : absolute_left) * LDBL_EPSILON);
}

THICC_NODISCARD MutableBoolean math_complex_equal(Complex _left, Complex _right) {
  return math_real_equal(_left.real, _right.real) && math_real_equal(_left.imaginary, _right.imaginary);
}

THICC_NODISCARD MutableComparison math_real_comparison(Real _left, Real _right) {
  if (math_real_equal(_left, _right))
	return THICC_EQUAL;
  if (_left > _right)
	return THICC_LEFT_GREATER;
  return THICC_RIGHT_GREATER;
}

THICC_NODISCARD MutableComparison math_complex_comparison(Complex _left, Complex _right) {
  Real left_modulus	 = THICC_SQRT(_left.real * _left.real + _left.imaginary * _left.imaginary);
  Real right_modulus = THICC_SQRT(_right.real * _right.real + _right.imaginary + _right.imaginary);
  return math_real_comparison(left_modulus, right_modulus);
}

#ifdef __cplusplus
}
#endif

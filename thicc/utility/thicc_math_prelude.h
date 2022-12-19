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
#ifndef THICC_THICC_MATH_PRELUDE_H
#define THICC_THICC_MATH_PRELUDE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../core/thicc_prelude.h"
#include "../core/thicc_struct_complex.h"
#include <math.h>

#undef THICC_ABS
#if THICC_C89
#define THICC_ABS(_value) (labs(_value))
#else
#define THICC_ABS(_value) (llabs(_value))
#endif

#undef THICC_FABS
#if THICC_C89
#define THICC_FABS(_value) ((Real) fabs((double) (_value)))
#else
#define THICC_FABS(_value) (fabsl(_value))
#endif

#undef THICC_FMOD
#if THICC_C89
#define THICC_FMOD(_left, _right) ((Real) fmod((double) (_left), (double) (_right)))
#else
#define THICC_FMOD(_left, _right) (fmodl(_left, _right))
#endif

#undef THICC_FLOOR
#if THICC_C89
#define THICC_FLOOR(_value) ((Real) floor((double) (_value)))
#else
#define THICC_FLOOR(_value) (floorl(_value))
#endif

#undef THICC_LOG10
#if THICC_C89
#define THICC_LOG10(_value) ((Real) log10((double) (_value)))
#else
#define THICC_LOG10(_value) log10l(_value)
#endif

#undef THICC_CEIL
#if THICC_C89
#define THICC_CEIL(_value) ((Real) ceil((double) (_value)))
#else
#define THICC_CEIL(_value) ceill(_value)
#endif

#undef THICC_ROUND
#if THICC_C89
MutableReal math_real_round(Real);
#define THICC_ROUND(_value) math_real_round(_value)
#else
#define THICC_ROUND(_value) nearbyintl(_value)
#endif

#undef THICC_POWER
#if THICC_C89
#define THICC_POWER(_base, _exponent) ((Real) THICC_POWERD((double) (_base), (double) (_exponent)))
#else
#define THICC_POWER(_base, _exponent) (powl(_base, _exponent))
#endif

#undef THICC_ROOT
#define THICC_ROOT(_degree, _radicand) (THICC_POWER(_degree, 1.0l / (_radicand)))

#undef THICC_SQRT
#if THICC_C89
#define THICC_SQRT(_degree) ((Real) sqrt((double) (_degree)))
#else
#define THICC_SQRT(_degree) (sqrtl(_degree))
#endif

#undef THICC_LN
#if THICC_C89
#define THICC_LN(_anti_logarithm) ((Real) THICC_LOG10D((double) (_anti_logarithm)))
#else
#define THICC_LN(_anti_logarithm) (logl(_anti_logarithm))
#endif

#undef THICC_LOGARITHM
#define THICC_LOGARITHM(_base, _anti_logarithm) (THICC_LN(_anti_logarithm) / THICC_LN(_base))

#undef THICC_MIN
#undef THICC_MAX
#define THICC_MIN(_left, _right) ((_left) > (_right) ? (_right) : (_left))
#define THICC_MAX(_left, _right) ((_left) < (_right) ? (_right) : (_left))

#undef THICC_SHORTER_POINTER
#undef THICC_LONGER_POINTER
#define THICC_SHORTER_POINTER(_left_length, _left_pointer, _right_length, _right_pointer) \
  ((_left_length) > (_right_length) ? (_right_pointer) : (_left_pointer))
#define THICC_LONGER_POINTER(_left_length, _left_pointer, _right_length, _right_pointer) \
  ((_left_length) < (_right_length) ? (_right_pointer) : (_left_pointer))

typedef struct thicc_struct_real_fmod {
  MutableReal integral;
  MutableReal fractional;
} MutableRealFmodStruct;

typedef MutableRealFmodStruct const RealFmodStruct;

#ifdef __cplusplus
}
#endif

#endif /* THICC_THICC_MATH_PRELUDE_H */

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

#include "thicc_complex.h"
#include "thicc_real.h"

THICC_NODISCARD MutableComplex complex_byte_and(Complex _left, Complex _right) {
  Real real_and		 = real_byte_and(_left.real, _right.real);
  Real imaginary_and = real_byte_and(_left.imaginary, _right.imaginary);
  return cmplx(real_and, imaginary_and);
}

THICC_NODISCARD MutableComplex complex_byte_or(Complex _left, Complex _right) {
  Real real_or		= real_byte_or(_left.real, _right.real);
  Real imaginary_or = real_byte_or(_left.imaginary, _right.imaginary);
  return cmplx(real_or, imaginary_or);
}

THICC_NODISCARD MutableComplex complex_byte_xor(Complex _left, Complex _right) {
  Real real_xor		 = real_byte_xor(_left.real, _right.real);
  Real imaginary_xor = real_byte_xor(_left.imaginary, _right.imaginary);
  return cmplx(real_xor, imaginary_xor);
}

THICC_NODISCARD MutableComplex complex_byte_complement(Complex _complex) {
  Real real_complement		= real_byte_complement(_complex.real);
  Real imaginary_complement = real_byte_complement(_complex.imaginary);
  return cmplx(real_complement, imaginary_complement);
}

#ifdef __cplusplus
}
#endif

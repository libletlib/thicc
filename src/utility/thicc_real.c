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

#include "thicc_real.h"
#include <string.h>

typedef struct thicc_struct_real_bytes {
  MutableReal	real;
  unsigned char bytes[sizeof(Real)];
} MutableRealBytes;
typedef MutableRealBytes const RealBytes;

THICC_NODISCARD static MutableRealBytes real_to_bytes(Real _real) {
  MutableRealBytes returnable;
  returnable.real = _real;
  return returnable;
}

THICC_NODISCARD MutableReal real_byte_and(Real _left, Real _right) {
  MutableRealBytes left = real_to_bytes(_left), right = real_to_bytes(_right), result_bytes;
  MutableSize	   index = 0;
  unsigned char	   result[sizeof(Real)];
  for (; index < sizeof(Real); ++index) {
	result[index] = left.bytes[index] & right.bytes[index];
  }
  memcpy(result_bytes.bytes, result, sizeof(Real));
  return result_bytes.real;
}

THICC_NODISCARD MutableReal real_byte_or(Real _left, Real _right) {
  MutableRealBytes left = real_to_bytes(_left), right = real_to_bytes(_right), result_bytes;
  MutableSize	   index = 0;
  unsigned char	   result[sizeof(Real)];
  for (; index < sizeof(Real); ++index) {
	result[index] = left.bytes[index] | right.bytes[index];
  }
  memcpy(result_bytes.bytes, result, sizeof(Real));
  return result_bytes.real;
}

THICC_NODISCARD MutableReal real_byte_xor(Real _left, Real _right) {
  MutableRealBytes left = real_to_bytes(_left), right = real_to_bytes(_right), result_bytes;
  MutableSize	   index = 0;
  unsigned char	   result[sizeof(Real)];
  for (; index < sizeof(Real); ++index) {
	result[index] = left.bytes[index] ^ right.bytes[index];
  }
  memcpy(result_bytes.bytes, result, sizeof(Real));
  return result_bytes.real;
}

THICC_NODISCARD MutableReal real_byte_complement(Real _bytes) {
  MutableRealBytes bytes = real_to_bytes(_bytes), result_bytes;
  MutableSize	   index = 0;
  unsigned char	   result[sizeof(Real)];
  for (; index < sizeof(Real); ++index) {
	result[index] = ~bytes.bytes[index];
  }
  memcpy(result_bytes.bytes, result, sizeof(Real));
  return result_bytes.real;
}

#ifdef __cplusplus
}
#endif

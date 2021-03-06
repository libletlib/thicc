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
#ifndef THICC_FLOAT_H
#define THICC_FLOAT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "../core/thicc_typedef.h"

typedef struct thicc_struct_float_bytes {
	MutableFloat real;
	unsigned char bytes[sizeof(float)];
} MutableFloatBytes;

typedef struct thicc_struct_double_bytes {
	MutableDouble real;
	unsigned char bytes[sizeof(double)];
} MutableDoubleBytes;

typedef struct thicc_struct_long_double_bytes {
	long double real;
	unsigned char bytes[sizeof(long double)];
} MutableLongDoubleBytes;

typedef MutableFloatBytes const FloatBytes;
typedef MutableDoubleBytes const DoubleBytes;
typedef MutableLongDoubleBytes  const LongDoubleBytes;

MutableFloatBytes float_byte_and(FloatBytes, FloatBytes);
MutableDoubleBytes double_byte_and(DoubleBytes, DoubleBytes);
MutableLongDoubleBytes long_double_byte_and(LongDoubleBytes, LongDoubleBytes);
MutableFloatBytes float_byte_or(FloatBytes, FloatBytes);
MutableDoubleBytes double_byte_or(DoubleBytes, DoubleBytes);
MutableLongDoubleBytes long_double_byte_or(LongDoubleBytes, LongDoubleBytes);
MutableFloatBytes float_byte_xor(FloatBytes, FloatBytes);
MutableDoubleBytes double_byte_xor(DoubleBytes, DoubleBytes);
MutableLongDoubleBytes long_double_byte_xor(LongDoubleBytes, LongDoubleBytes);
MutableFloatBytes float_byte_complement(FloatBytes);
MutableDoubleBytes double_byte_complement(DoubleBytes);
MutableLongDoubleBytes long_double_byte_complement(LongDoubleBytes);

#ifdef __cplusplus
}
#endif

#endif//THICC_FLOAT_H

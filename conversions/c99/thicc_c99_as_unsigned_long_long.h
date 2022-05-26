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
#ifndef THICC_C99_AS_UNSIGNED_LONG_LONG_H
#define THICC_C99_AS_UNSIGNED_LONG_LONG_H

#ifdef __cplusplus
	extern "C"
	{
#endif

#include "../../core/thicc_typedef.h"

#if THICC_IF(THICC_C_AT_LEAST(1999))

MutableUnsignedLongLong boolean_as_unsigned_long_long(Let);
MutableUnsignedLongLong character_as_unsigned_long_long(Let);
MutableUnsignedLongLong signed_character_as_unsigned_long_long(Let);
MutableUnsignedLongLong unsigned_character_as_unsigned_long_long(Let);
MutableUnsignedLongLong short_as_unsigned_long_long(Let);
MutableUnsignedLongLong unsigned_short_as_unsigned_long_long(Let);
MutableUnsignedLongLong integer_as_unsigned_long_long(Let);
MutableUnsignedLongLong unsigned_integer_as_unsigned_long_long(Let);
MutableUnsignedLongLong long_as_unsigned_long_long(Let);
MutableUnsignedLongLong unsigned_long_as_unsigned_long_long(Let);
MutableUnsignedLongLong long_long_as_unsigned_long_long(Let);
MutableUnsignedLongLong unsigned_long_long_as_unsigned_long_long(Let);
MutableUnsignedLongLong float_as_unsigned_long_long(Let);
MutableUnsignedLongLong double_as_unsigned_long_long(Let);
MutableUnsignedLongLong long_double_as_unsigned_long_long(Let);
#if THICC_IF(THICC_HAS_COMPLEX)
MutableUnsignedLongLong float_complex_as_unsigned_long_long(Let);
MutableUnsignedLongLong double_complex_as_unsigned_long_long(Let);
MutableUnsignedLongLong long_double_complex_as_unsigned_long_long(Let);
#endif
MutableUnsignedLongLong string_as_unsigned_long_long(Let);
MutableUnsignedLongLong subroutine_as_unsigned_long_long(Let);
MutableUnsignedLongLong function_as_unsigned_long_long(Let);
MutableUnsignedLongLong array_as_unsigned_long_long(Let);
MutableUnsignedLongLong object_as_unsigned_long_long(Let);

#endif

#ifdef __cplusplus
    }
#endif

#endif//THICC_C99_AS_UNSIGNED_LONG_LONG_H

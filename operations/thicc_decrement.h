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
#ifndef THICC_DECREMENT_H
#define THICC_DECREMENT_H

#ifdef __cplusplus
extern "C"
{
#endif
	
#include "../core/thicc_typedef.h"

	MutableLet boolean_decrement(MutableLet);
	MutableLet character_decrement(MutableLet);
	MutableLet signed_character_decrement(MutableLet);
	MutableLet unsigned_character_decrement(MutableLet);
	MutableLet short_decrement(MutableLet);
	MutableLet unsigned_short_decrement(MutableLet);
	MutableLet integer_decrement(MutableLet);
	MutableLet unsigned_integer_decrement(MutableLet);
	MutableLet long_decrement(MutableLet);
	MutableLet unsigned_long_decrement(MutableLet);
	MutableLet float_decrement(MutableLet);
	MutableLet double_decrement(MutableLet);
	MutableLet long_double_decrement(MutableLet);
	MutableLet string_decrement(MutableLet);
	MutableLet subroutine_decrement(MutableLet);
	MutableLet function_decrement(MutableLet);
	MutableLet array_decrement(MutableLet);
	MutableLet object_decrement(MutableLet);

#if THICC_IF(THICC_C_AT_LEAST(1999))
	#include "c99/thicc_c99_decrement.h"
#endif

#ifdef __cplusplus
}
#endif

#endif//THICC_DECREMENT_H

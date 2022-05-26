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

#include "thicc_rank.h"
#include "../core/thicc_interface.h"
#include "../core/thicc_struct_let.h"

	MutableBoolean rank_is_character(Let _let) {
		switch(rank(_let)) {
			case character_rank:
			case signed_character_rank:
			case unsigned_character_rank:
				return THICC_YES;
			default:
				return THICC_NO;
		}
	}

	MutableBoolean rank_is_numeric(Let _let) {
		switch(rank(_let)) {
			case short_rank:
			case unsigned_short_rank:
			case integer_rank:
			case unsigned_integer_rank:
			case long_rank:
			case unsigned_long_rank:
			case float_rank:
			case double_rank:
			case long_double_rank:
				return THICC_YES;
			default:
				return THICC_NO;
		}
	}

	MutableBoolean rank_is_integral(Let _let) {
		switch(rank(_let)) {
			case short_rank:
			case unsigned_short_rank:
			case integer_rank:
			case unsigned_integer_rank:
			case long_rank:
			case unsigned_long_rank:
				return THICC_YES;
			default:
				return THICC_NO;
		}
	}

	MutableBoolean rank_is_signed(Let _let) {
		switch(rank(_let)) {
#if (THICC_CHAR_SIGNED == THICC_YES)
			case character_rank:
#endif
			case signed_character_rank:
			case short_rank:
			case integer_rank:
			case long_rank:
			case float_rank:
			case double_rank:
			case long_double_rank:
				return THICC_YES;
			default:
				return THICC_NO;
		}
	}

	MutableBoolean rank_is_unsigned(Let _let) {
		switch(rank(_let)) {
#if (THICC_CHAR_UNSIGNED == THICC_YES)
			case character_rank:
#endif
			case unsigned_character_rank:
			case unsigned_short_rank:
			case unsigned_integer_rank:
			case unsigned_long_rank:
				return THICC_YES;
			default:
				return THICC_NO;
		}
	}

	MutableBoolean rank_is_floating_point(Let _let)  {
		switch(rank(_let)) {
			case float_rank:
			case double_rank:
			case long_double_rank:
				return THICC_YES;
			default:
				return THICC_NO;
		}
	}

	MutableBoolean rank_is_string(Let _let)  {
		if(rank(_let) == string_rank)
			return THICC_YES;
		else
			return THICC_NO;
	}

	MutableBoolean rank_is_invokable(Let _let)   {
		switch(rank(_let)) {
			case subroutine_rank:
			case function_rank:
				return THICC_YES;
			default:
				return THICC_NO;
		}
	}

	MutableBoolean rank_is_array(Let _let) {
		if(rank(_let) == array_rank)
			return THICC_YES;
		else
			return THICC_NO;
	}

	MutableBoolean rank_is_indexable(Let _let) {
		switch(rank(_let)) {
			case string_rank:
			case array_rank:
			case object_rank:
				return THICC_YES;
			default:
				return THICC_NO;
		}
	}

	MutableBoolean rank_is_object(Let _let) {
		if(rank(_let) == object_rank)
			return THICC_YES;
		else
			return THICC_NO;
	}

#ifdef __cplusplus
}
#endif

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

#include "thicc_c99_as_long_double_complex.h"
#include "../../core/thicc_interface.h"
#include "../../core/thicc_struct_let.h"
#include "../../utility/c99/thicc_c99_complex.h"
#include "../../utility/thicc_function.h"

#if THICC_IF(THICC_HAS_STD_COMPLEX)

	MutableLongDoubleComplex boolean_as_long_double_complex(Let _let) {
		return _let.value.boolean_type ? THICC_COMPLEXL(1.0l, 0.0l) : THICC_COMPLEXL(0.0l, 0.0l);
	}

	MutableLongDoubleComplex character_as_long_double_complex(Let _let) {
		return THICC_COMPLEXL(as_double(_let), 0.0l);
	}

	MutableLongDoubleComplex signed_character_as_long_double_complex(Let _let) {
		return THICC_COMPLEXL(as_double(_let), 0.0l);
	}

	MutableLongDoubleComplex unsigned_character_as_long_double_complex(Let _let) {
		return THICC_COMPLEXL(as_double(_let), 0.0l);
	}

	MutableLongDoubleComplex short_as_long_double_complex(Let _let) {
		return THICC_COMPLEXL(as_double(_let), 0.0l);
	}

	MutableLongDoubleComplex unsigned_short_as_long_double_complex(Let _let) {
		return THICC_COMPLEXL(as_double(_let), 0.0l);
	}

	MutableLongDoubleComplex integer_as_long_double_complex(Let _let) {
		return THICC_COMPLEXL(as_double(_let), 0.0l);
	}

	MutableLongDoubleComplex unsigned_integer_as_long_double_complex(Let _let) {
		return THICC_COMPLEXL(as_double(_let), 0.0l);
	}

	MutableLongDoubleComplex long_as_long_double_complex(Let _let) {
		return THICC_COMPLEXL(as_double(_let), 0.0l);
	}

	MutableLongDoubleComplex unsigned_long_as_long_double_complex(Let _let) {
		return THICC_COMPLEXL(as_double(_let), 0.0l);
	}

	MutableLongDoubleComplex long_long_as_long_double_complex(Let _let) {
		return THICC_COMPLEXL(as_double(_let), 0.0l);
	}

	MutableLongDoubleComplex unsigned_long_long_as_long_double_complex(Let _let) {
		return THICC_COMPLEXL(as_double(_let), 0.0l);
	}

	MutableLongDoubleComplex float_as_long_double_complex(Let _let) {
		return THICC_COMPLEXL(as_double(_let), 0.0l);
	}

	MutableLongDoubleComplex double_as_long_double_complex(Let _let) {
		return THICC_COMPLEXL(_let.value.double_type, 0.0l);
	}

	MutableLongDoubleComplex long_double_as_long_double_complex(Let _let) {
		return THICC_COMPLEXL(as_double(_let), 0.0l);
	}

	MutableLongDoubleComplex float_complex_as_long_double_complex(Let _let) {
		return (LongDoubleComplex) _let.value.float_complex_type;
	}

	MutableLongDoubleComplex double_complex_as_long_double_complex(Let _let) {
		return (LongDoubleComplex) _let.value.double_complex_type;
	}

	MutableLongDoubleComplex long_double_complex_as_long_double_complex(Let _let) {
		return _let.value.long_double_complex_type;
	}

	MutableLongDoubleComplex string_as_long_double_complex(Let _let) {
		return THICC_COMPLEXL(0.0l, 0.0l);
	}

	MutableLongDoubleComplex subroutine_as_long_double_complex(Let _let) {
		return THICC_COMPLEXL(0.0l, 0.0l);
	}

	MutableLongDoubleComplex function_as_long_double_complex(Let _let) {
		Let temporary = function_invoke(_let, let_empty());
		LongDoubleComplex result = as_long_double_complex(temporary);
		if(requires_free(temporary))
			unlet(temporary);
		return result;
	}

	MutableLongDoubleComplex array_as_long_double_complex(Let _let) {
		return as_long_double_complex(*array_view(_let));
	}

	MutableLongDoubleComplex object_as_long_double_complex(Let _let) {
		return *((LongDoubleComplex* THICC_RESTRICT) object_view(_let));
	}

#endif

#ifdef __cplusplus
}
#endif

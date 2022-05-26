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

#include "thicc_c99_as_double_complex.h"
#include "../../core/thicc_interface.h"
#include "../../core/thicc_struct_let.h"
#include "../../utility/c99/thicc_c99_complex.h"
#include "../../utility/thicc_function.h"

#if THICC_IF(THICC_HAS_COMPLEX)

	MutableDoubleComplex boolean_as_double_complex(Let _let) {
		return _let.value.boolean_type ? THICC_COMPLEXD(1.0, 0.0) : THICC_COMPLEXD(0.0, 0.0);
	}
	
	MutableDoubleComplex character_as_double_complex(Let _let) {
		return THICC_COMPLEXD(as_double(_let), 0.0);
	}

	MutableDoubleComplex signed_character_as_double_complex(Let _let) {
		return THICC_COMPLEXD(as_double(_let), 0.0);
	}

	MutableDoubleComplex unsigned_character_as_double_complex(Let _let) {
		return THICC_COMPLEXD(as_double(_let), 0.0);
	}

	MutableDoubleComplex short_as_double_complex(Let _let) {
		return THICC_COMPLEXD(as_double(_let), 0.0);
	}

	MutableDoubleComplex unsigned_short_as_double_complex(Let _let) {
		return THICC_COMPLEXD(as_double(_let), 0.0);
	}

	MutableDoubleComplex integer_as_double_complex(Let _let) {
		return THICC_COMPLEXD(as_double(_let), 0.0);
	}

	MutableDoubleComplex unsigned_integer_as_double_complex(Let _let) {
		return THICC_COMPLEXD(as_double(_let), 0.0);
	}

	MutableDoubleComplex long_as_double_complex(Let _let) {
		return THICC_COMPLEXD(as_double(_let), 0.0);
	}

	MutableDoubleComplex unsigned_long_as_double_complex(Let _let) {
		return THICC_COMPLEXD(as_double(_let), 0.0);
	}

	MutableDoubleComplex long_long_as_double_complex(Let _let) {
		return THICC_COMPLEXD(as_double(_let), 0.0);
	}

	MutableDoubleComplex unsigned_long_long_as_double_complex(Let _let) {
		return THICC_COMPLEXD(as_double(_let), 0.0);
	}

	MutableDoubleComplex float_as_double_complex(Let _let) {
		return THICC_COMPLEXD(as_double(_let), 0.0);
	}

	MutableDoubleComplex double_as_double_complex(Let _let) {
		return THICC_COMPLEXD(_let.value.double_type, 0.0);
	}

	MutableDoubleComplex long_double_as_double_complex(Let _let) {
		return THICC_COMPLEXD(as_double(_let), 0.0);
	}

	MutableDoubleComplex float_complex_as_double_complex(Let _let) {
		return (DoubleComplex) _let.value.float_complex_type;
	}

	MutableDoubleComplex double_complex_as_double_complex(Let _let) {
		return _let.value.double_complex_type;
	}

	MutableDoubleComplex long_double_complex_as_double_complex(Let _let) {
		return (DoubleComplex) _let.value.long_double_complex_type;
	}

	MutableDoubleComplex string_as_double_complex(Let _let) {
		return THICC_COMPLEXD(0.0, 0.0);
	}

	MutableDoubleComplex subroutine_as_double_complex(Let _let) {
		return THICC_COMPLEXD(0.0, 0.0);
	}

	MutableDoubleComplex function_as_double_complex(Let _let) {
		Let temporary = function_invoke(_let, let_empty());
		DoubleComplex result = as_double_complex(temporary);
		if(requires_free(temporary))
			unlet(temporary);
		return result;
	}

	MutableDoubleComplex array_as_double_complex(Let _let) {
		return as_double_complex(*array_view(_let));
	}

	MutableDoubleComplex object_as_double_complex(Let _let) {
		return *((DoubleComplex* THICC_RESTRICT) object_view(_let));
	}

#endif

#ifdef __cplusplus
}
#endif

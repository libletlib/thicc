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

#include "thicc_c99_struct_behaviour.h"
#include "../../conversions/c99/thicc_c99_as_boolean.h"
#include "../../conversions/c99/thicc_c99_as_long_long.h"
#include "../../conversions/c99/thicc_c99_as_unsigned_long_long.h"
#include "../../conversions/c99/thicc_c99_as_float_complex.h"
#include "../../conversions/c99/thicc_c99_as_double_complex.h"
#include "../../conversions/c99/thicc_c99_as_long_double_complex.h"
#include "../../conversions/thicc_as_array.h"
#include "../../conversions/thicc_as_character.h"
#include "../../conversions/thicc_as_double.h"
#include "../../conversions/thicc_as_float.h"
#include "../../conversions/thicc_as_function.h"
#include "../../conversions/thicc_as_integer.h"
#include "../../conversions/thicc_as_long.h"
#include "../../conversions/thicc_as_long_double.h"
#include "../../conversions/thicc_as_object.h"
#include "../../conversions/thicc_as_short.h"
#include "../../conversions/thicc_as_signed_character.h"
#include "../../conversions/thicc_as_string.h"
#include "../../conversions/thicc_as_subroutine.h"
#include "../../conversions/thicc_as_unsigned_character.h"
#include "../../conversions/thicc_as_unsigned_integer.h"
#include "../../conversions/thicc_as_unsigned_long.h"
#include "../../conversions/thicc_as_unsigned_short.h"
#include "../../operations/thicc_bit_and.h"
#include "../../operations/thicc_bit_complement.h"
#include "../../operations/thicc_bit_not.h"
#include "../../operations/thicc_bit_or.h"
#include "../../operations/thicc_bit_xor.h"
#include "../../operations/thicc_comparison.h"
#include "../../operations/thicc_difference.h"
#include "../../operations/thicc_index_of.h"
#include "../../operations/thicc_indirection.h"
#include "../../operations/thicc_logarithm.h"
#include "../../operations/thicc_modulo.h"
#include "../../operations/thicc_negative.h"
#include "../../operations/thicc_positive.h"
#include "../../operations/thicc_power.h"
#include "../../operations/thicc_product.h"
#include "../../operations/thicc_quotient.h"
#include "../../operations/thicc_root.h"
#include "../../operations/thicc_sum.h"
#include "../thicc_memory.h"

#if THICC_IF(THICC_C_AT_LEAST(1999))

	Behaviour long_long_behaviour = {long_long_rank,
	                                 stack_deallocate,
	                                 long_long_as_boolean,
	                                 long_long_as_character,
	                                 long_long_as_signed_character,
	                                 long_long_as_unsigned_character,
	                                 long_long_as_short,
	                                 long_long_as_unsigned_short,
	                                 long_long_as_integer,
	                                 long_long_as_unsigned_integer,
	                                 long_long_as_long,
	                                 long_long_as_unsigned_long,
	                                 long_long_as_long_long,
	                                 long_long_as_unsigned_long_long,
	                                 long_long_as_float,
	                                 long_long_as_double,
	                                 long_long_as_long_double,
	#if THICC_IF(THICC_HAS_COMPLEX)
	                                 long_long_as_float_complex,
	                                 long_long_as_double_complex,
	                                 long_long_as_long_double_complex,
	#endif
	                                 long_long_as_string,
	                                 long_long_as_subroutine,
	                                 long_long_as_function,
	                                 long_long_as_array,
	                                 long_long_as_object,
	                                 long_long_sum,
	                                 long_long_difference,
	                                 long_long_product,
	                                 long_long_quotient,
	                                 long_long_power,
	                                 long_long_modulo,
	                                 long_long_logarithm,
	                                 long_long_root,
	                                 long_long_bit_and,
	                                 long_long_bit_or,
	                                 long_long_bit_xor,
	                                 long_long_bit_not,
	                                 long_long_bit_complement,
	                                 long_long_index_of,
	                                 long_long_indirection,
	                                 long_long_negative,
	                                 long_long_positive,
	                                 long_long_comparison};

	Behaviour unsigned_long_long_behaviour = {unsigned_long_long_rank,
	                                          stack_deallocate,
	                                          unsigned_long_long_as_boolean,
	                                          unsigned_long_long_as_character,
	                                          unsigned_long_long_as_signed_character,
	                                          unsigned_long_long_as_unsigned_character,
	                                          unsigned_long_long_as_short,
	                                          unsigned_long_long_as_unsigned_short,
	                                          unsigned_long_long_as_integer,
	                                          unsigned_long_long_as_unsigned_integer,
	                                          unsigned_long_long_as_long,
	                                          unsigned_long_long_as_unsigned_long,
	                                          unsigned_long_long_as_long_long,
	                                          unsigned_long_long_as_unsigned_long_long,
	                                          unsigned_long_long_as_float,
	                                          unsigned_long_long_as_double,
	                                          unsigned_long_long_as_long_double,
	#if THICC_IF(THICC_HAS_COMPLEX)
	                                          unsigned_long_long_as_float_complex,
	                                          unsigned_long_long_as_double_complex,
	                                          unsigned_long_long_as_long_double_complex,
	#endif
	                                          unsigned_long_long_as_string,
	                                          unsigned_long_long_as_subroutine,
	                                          unsigned_long_long_as_function,
	                                          unsigned_long_long_as_array,
	                                          unsigned_long_long_as_object,
	                                          unsigned_long_long_sum,
	                                          unsigned_long_long_difference,
	                                          unsigned_long_long_product,
	                                          unsigned_long_long_quotient,
	                                          unsigned_long_long_power,
	                                          unsigned_long_long_modulo,
	                                          unsigned_long_long_logarithm,
	                                          unsigned_long_long_root,
	                                          unsigned_long_long_bit_and,
	                                          unsigned_long_long_bit_or,
	                                          unsigned_long_long_bit_xor,
	                                          unsigned_long_long_bit_not,
	                                          unsigned_long_long_bit_complement,
	                                          unsigned_long_long_index_of,
	                                          unsigned_long_long_indirection,
	                                          unsigned_long_long_negative,
	                                          unsigned_long_long_positive,
	                                          unsigned_long_long_comparison};

	#if THICC_IF(THICC_HAS_COMPLEX)
	Behaviour float_complex_behaviour = {float_complex_rank,
	                               stack_deallocate,
	                               float_complex_as_boolean,
	                               float_complex_as_character,
	                               float_complex_as_signed_character,
	                               float_complex_as_unsigned_character,
	                               float_complex_as_short,
	                               float_complex_as_unsigned_short,
	                               float_complex_as_integer,
	                               float_complex_as_unsigned_integer,
	                               float_complex_as_long,
	                               float_complex_as_unsigned_long,
	                               float_complex_as_long_long,
	                               float_complex_as_unsigned_long_long,
	                               float_complex_as_float,
	                               float_complex_as_double,
	                               float_complex_as_long_double,
	                               float_complex_as_float_complex,
	                               float_complex_as_double_complex,
	                               float_complex_as_long_double_complex,
	                               float_complex_as_string,
	                               float_complex_as_subroutine,
	                               float_complex_as_function,
	                               float_complex_as_array,
	                               float_complex_as_object,
	                               float_complex_sum,
	                               float_complex_difference,
	                               float_complex_product,
	                               float_complex_quotient,
	                               float_complex_power,
	                               float_complex_modulo,
	                               float_complex_logarithm,
	                               float_complex_root,
	                               float_complex_bit_and,
	                               float_complex_bit_or,
	                               float_complex_bit_xor,
	                               float_complex_bit_not,
	                               float_complex_bit_complement,
	                               float_complex_index_of,
	                               float_complex_indirection,
	                               float_complex_negative,
	                               float_complex_positive,
	                               float_complex_comparison};

	Behaviour double_complex_behaviour = {double_complex_rank,
	                                     stack_deallocate,
	                                     double_complex_as_boolean,
	                                     double_complex_as_character,
	                                     double_complex_as_signed_character,
	                                     double_complex_as_unsigned_character,
	                                     double_complex_as_short,
	                                     double_complex_as_unsigned_short,
	                                     double_complex_as_integer,
	                                     double_complex_as_unsigned_integer,
	                                     double_complex_as_long,
	                                     double_complex_as_unsigned_long,
	                                     double_complex_as_long_long,
	                                     double_complex_as_unsigned_long_long,
	                                     double_complex_as_float,
	                                     double_complex_as_double,
	                                     double_complex_as_long_double,
	                                     double_complex_as_float_complex,
	                                     double_complex_as_double_complex,
	                                     double_complex_as_long_double_complex,
	                                     double_complex_as_string,
	                                     double_complex_as_subroutine,
	                                     double_complex_as_function,
	                                     double_complex_as_array,
	                                     double_complex_as_object,
	                                     double_complex_sum,
	                                     double_complex_difference,
	                                     double_complex_product,
	                                     double_complex_quotient,
	                                     double_complex_power,
	                                     double_complex_modulo,
	                                     double_complex_logarithm,
	                                     double_complex_root,
	                                     double_complex_bit_and,
	                                     double_complex_bit_or,
	                                     double_complex_bit_xor,
	                                     double_complex_bit_not,
	                                     double_complex_bit_complement,
	                                     double_complex_index_of,
	                                     double_complex_indirection,
	                                     double_complex_negative,
	                                     double_complex_positive,
	                                     double_complex_comparison};

	Behaviour long_double_complex_behaviour = {long_double_complex_rank,
	                                     stack_deallocate,
	                                     long_double_complex_as_boolean,
	                                     long_double_complex_as_character,
	                                     long_double_complex_as_signed_character,
	                                     long_double_complex_as_unsigned_character,
	                                     long_double_complex_as_short,
	                                     long_double_complex_as_unsigned_short,
	                                     long_double_complex_as_integer,
	                                     long_double_complex_as_unsigned_integer,
	                                     long_double_complex_as_long,
	                                     long_double_complex_as_unsigned_long,
	                                     long_double_complex_as_long_long,
	                                     long_double_complex_as_unsigned_long_long,
	                                     long_double_complex_as_float,
	                                     long_double_complex_as_double,
	                                     long_double_complex_as_long_double,
	                                     long_double_complex_as_float_complex,
	                                     long_double_complex_as_double_complex,
	                                     long_double_complex_as_long_double_complex,
	                                     long_double_complex_as_string,
	                                     long_double_complex_as_subroutine,
	                                     long_double_complex_as_function,
	                                     long_double_complex_as_array,
	                                     long_double_complex_as_object,
	                                     long_double_complex_sum,
	                                     long_double_complex_difference,
	                                     long_double_complex_product,
	                                     long_double_complex_quotient,
	                                     long_double_complex_power,
	                                     long_double_complex_modulo,
	                                     long_double_complex_logarithm,
	                                     long_double_complex_root,
	                                     long_double_complex_bit_and,
	                                     long_double_complex_bit_or,
	                                     long_double_complex_bit_xor,
	                                     long_double_complex_bit_not,
	                                     long_double_complex_bit_complement,
	                                     long_double_complex_index_of,
	                                     long_double_complex_indirection,
	                                     long_double_complex_negative,
	                                     long_double_complex_positive,
	                                     long_double_complex_comparison};
	#endif

#endif

#ifdef __cplusplus
}
#endif

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

#include "thicc_struct_behaviour.h"
#include "../conversions/thicc_as_array.h"
#include "../conversions/thicc_as_character.h"
#include "../conversions/thicc_as_boolean.h"
#include "../conversions/thicc_as_double.h"
#include "../conversions/thicc_as_float.h"
#include "../conversions/thicc_as_function.h"
#include "../conversions/thicc_as_integer.h"
#include "../conversions/thicc_as_long.h"
#include "../conversions/thicc_as_long_double.h"
#include "../conversions/thicc_as_object.h"
#include "../conversions/thicc_as_short.h"
#include "../conversions/thicc_as_signed_character.h"
#include "../conversions/thicc_as_string.h"
#include "../conversions/thicc_as_subroutine.h"
#include "../conversions/thicc_as_unsigned_character.h"
#include "../conversions/thicc_as_unsigned_integer.h"
#include "../conversions/thicc_as_unsigned_long.h"
#include "../conversions/thicc_as_unsigned_short.h"
#include "../operations/thicc_bit_and.h"
#include "../operations/thicc_bit_complement.h"
#include "../operations/thicc_bit_not.h"
#include "../operations/thicc_bit_or.h"
#include "../operations/thicc_bit_xor.h"
#include "../operations/thicc_comparison.h"
#include "../operations/thicc_difference.h"
#include "../operations/thicc_index_of.h"
#include "../operations/thicc_indirection.h"
#include "../operations/thicc_logarithm.h"
#include "../operations/thicc_modulo.h"
#include "../operations/thicc_negative.h"
#include "../operations/thicc_positive.h"
#include "../operations/thicc_power.h"
#include "../operations/thicc_product.h"
#include "../operations/thicc_quotient.h"
#include "../operations/thicc_root.h"
#include "../operations/thicc_sum.h"
#include "thicc_memory.h"

#if THICC_IF(THICC_C_AT_LEAST(1999))
	#include "../conversions/c99/thicc_c99_as_boolean.h"
	#include "../conversions/c99/thicc_c99_as_long_long.h"
	#include "../conversions/c99/thicc_c99_as_unsigned_long_long.h"
#if THICC_IF(THICC_HAS_COMPLEX)
	#include "../conversions/c99/thicc_c99_as_float_complex.h"
	#include "../conversions/c99/thicc_c99_as_double_complex.h"
	#include "../conversions/c99/thicc_c99_as_long_double_complex.h"
#endif
#endif

	Behaviour boolean_behaviour = {boolean_rank,
	                               stack_deallocate,
	                               boolean_as_boolean,
	                               boolean_as_character,
	                               boolean_as_signed_character,
	                               boolean_as_unsigned_character,
	                               boolean_as_short,
	                               boolean_as_unsigned_short,
	                               boolean_as_integer,
	                               boolean_as_unsigned_integer,
	                               boolean_as_long,
	                               boolean_as_unsigned_long,
#if THICC_IF(THICC_C_AT_LEAST(1999))
	                               boolean_as_long_long,
	                               boolean_as_unsigned_long_long,
#endif
	                               boolean_as_float,
	                               boolean_as_double,
	                               boolean_as_long_double,
#if THICC_IF(THICC_HAS_COMPLEX)
	                               boolean_as_float_complex,
	                               boolean_as_double_complex,
	                               boolean_as_long_double_complex,
#endif
	                               boolean_as_string,
	                               boolean_as_subroutine,
	                               boolean_as_function,
	                               boolean_as_array,
	                               boolean_as_object,
	                               boolean_sum,
	                               boolean_difference,
	                               boolean_product,
	                               boolean_quotient,
	                               boolean_power,
	                               boolean_modulo,
	                               boolean_logarithm,
	                               boolean_root,
	                               boolean_bit_and,
	                               boolean_bit_or,
	                               boolean_bit_xor,
	                               boolean_bit_not,
	                               boolean_bit_complement,
	                               boolean_index_of,
	                               boolean_indirection,
	                               boolean_negative,
	                               boolean_positive,
	                               boolean_comparison};

	Behaviour character_behaviour = {character_rank,
	                                 stack_deallocate,
	                                 character_as_boolean,
	                                 character_as_character,
	                                 character_as_signed_character,
	                                 character_as_unsigned_character,
	                                 character_as_short,
	                                 character_as_unsigned_short,
	                                 character_as_integer,
	                                 character_as_unsigned_integer,
	                                 character_as_long,
	                                 character_as_unsigned_long,
#if THICC_IF(THICC_C_AT_LEAST(1999))
	                                 character_as_long_long,
	                                 character_as_unsigned_long_long,
#endif
	                                 character_as_float,
	                                 character_as_double,
	                                 character_as_long_double,
#if THICC_IF(THICC_HAS_COMPLEX)
	                                 character_as_float_complex,
	                                 character_as_double_complex,
	                                 character_as_long_double_complex,
#endif
	                                 character_as_string,
	                                 character_as_subroutine,
	                                 character_as_function,
	                                 character_as_array,
	                                 character_as_object,
	                                 character_sum,
	                                 character_difference,
	                                 character_product,
	                                 character_quotient,
	                                 character_power,
	                                 character_modulo,
	                                 character_logarithm,
	                                 character_root,
	                                 character_bit_and,
	                                 character_bit_or,
	                                 character_bit_xor,
	                                 character_bit_not,
	                                 character_bit_complement,
	                                 character_index_of,
	                                 character_indirection,
	                                 character_negative,
	                                 character_positive,
	                                 character_comparison};

	Behaviour signed_character_behaviour = {signed_character_rank,
	                                        stack_deallocate,
	                                        signed_character_as_boolean,
	                                        signed_character_as_character,
	                                        signed_character_as_signed_character,
	                                        signed_character_as_unsigned_character,
	                                        signed_character_as_short,
	                                        signed_character_as_unsigned_short,
	                                        signed_character_as_integer,
	                                        signed_character_as_unsigned_integer,
	                                        signed_character_as_long,
	                                        signed_character_as_unsigned_long,
#if THICC_IF(THICC_C_AT_LEAST(1999))
	                                        signed_character_as_long_long,
	                                        signed_character_as_unsigned_long_long,
#endif
	                                        signed_character_as_float,
	                                        signed_character_as_double,
	                                        signed_character_as_long_double,
#if THICC_IF(THICC_HAS_COMPLEX)
	                                        signed_character_as_float_complex,
	                                        signed_character_as_double_complex,
	                                        signed_character_as_long_double_complex,
#endif
	                                        signed_character_as_string,
	                                        signed_character_as_subroutine,
	                                        signed_character_as_function,
	                                        signed_character_as_array,
	                                        signed_character_as_object,
	                                        signed_character_sum,
	                                        signed_character_difference,
	                                        signed_character_product,
	                                        signed_character_quotient,
	                                        signed_character_power,
	                                        signed_character_modulo,
	                                        signed_character_logarithm,
	                                        signed_character_root,
	                                        signed_character_bit_and,
	                                        signed_character_bit_or,
	                                        signed_character_bit_xor,
	                                        signed_character_bit_not,
	                                        signed_character_bit_complement,
	                                        signed_character_index_of,
	                                        signed_character_indirection,
	                                        signed_character_negative,
	                                        signed_character_positive,
	                                        signed_character_comparison};

	Behaviour unsigned_character_behaviour = {unsigned_character_rank,
	                                          stack_deallocate,
	                                          unsigned_character_as_boolean,
	                                          unsigned_character_as_character,
	                                          unsigned_character_as_signed_character,
	                                          unsigned_character_as_unsigned_character,
	                                          unsigned_character_as_short,
	                                          unsigned_character_as_unsigned_short,
	                                          unsigned_character_as_integer,
	                                          unsigned_character_as_unsigned_integer,
	                                          unsigned_character_as_long,
	                                          unsigned_character_as_unsigned_long,
#if THICC_IF(THICC_C_AT_LEAST(1999))
	                                          unsigned_character_as_long_long,
	                                          unsigned_character_as_unsigned_long_long,
#endif
	                                          unsigned_character_as_float,
	                                          unsigned_character_as_double,
	                                          unsigned_character_as_long_double,
#if THICC_IF(THICC_HAS_COMPLEX)
	                                          unsigned_character_as_float_complex,
	                                          unsigned_character_as_double_complex,
	                                          unsigned_character_as_long_double_complex,
#endif
	                                          unsigned_character_as_string,
	                                          unsigned_character_as_subroutine,
	                                          unsigned_character_as_function,
	                                          unsigned_character_as_array,
	                                          unsigned_character_as_object,
	                                          unsigned_character_sum,
	                                          unsigned_character_difference,
	                                          unsigned_character_product,
	                                          unsigned_character_quotient,
	                                          unsigned_character_power,
	                                          unsigned_character_modulo,
	                                          unsigned_character_logarithm,
	                                          unsigned_character_root,
	                                          unsigned_character_bit_and,
	                                          unsigned_character_bit_or,
	                                          unsigned_character_bit_xor,
	                                          unsigned_character_bit_not,
	                                          unsigned_character_bit_complement,
	                                          unsigned_character_index_of,
	                                          unsigned_character_indirection,
	                                          unsigned_character_negative,
	                                          unsigned_character_positive,
	                                          unsigned_character_comparison};

	Behaviour short_behaviour = {short_rank,
	                             stack_deallocate,
	                             short_as_boolean,
	                             short_as_character,
	                             short_as_signed_character,
	                             short_as_unsigned_character,
	                             short_as_short,
	                             short_as_unsigned_short,
	                             short_as_integer,
	                             short_as_unsigned_integer,
	                             short_as_long,
	                             short_as_unsigned_long,
#if THICC_IF(THICC_C_AT_LEAST(1999))
	                             short_as_long_long,
	                             short_as_unsigned_long_long,
#endif
	                             short_as_float,
	                             short_as_double,
	                             short_as_long_double,
#if THICC_IF(THICC_HAS_COMPLEX)
	                             short_as_float_complex,
	                             short_as_double_complex,
	                             short_as_long_double_complex,
#endif
	                             short_as_string,
	                             short_as_subroutine,
	                             short_as_function,
	                             short_as_array,
	                             short_as_object,
	                             short_sum,
	                             short_difference,
	                             short_product,
	                             short_quotient,
	                             short_power,
	                             short_modulo,
	                             short_logarithm,
	                             short_root,
	                             short_bit_and,
	                             short_bit_or,
	                             short_bit_xor,
	                             short_bit_not,
	                             short_bit_complement,
	                             short_index_of,
	                             short_indirection,
	                             short_negative,
	                             short_positive,
	                             short_comparison};

	Behaviour unsigned_short_behaviour = {unsigned_short_rank,
	                                      stack_deallocate,
	                                      unsigned_short_as_boolean,
	                                      unsigned_short_as_character,
	                                      unsigned_short_as_signed_character,
	                                      unsigned_short_as_unsigned_character,
	                                      unsigned_short_as_short,
	                                      unsigned_short_as_unsigned_short,
	                                      unsigned_short_as_integer,
	                                      unsigned_short_as_unsigned_integer,
	                                      unsigned_short_as_long,
	                                      unsigned_short_as_unsigned_long,
#if THICC_IF(THICC_C_AT_LEAST(1999))
	                                      unsigned_short_as_long_long,
	                                      unsigned_short_as_unsigned_long_long,
#endif
	                                      unsigned_short_as_float,
	                                      unsigned_short_as_double,
	                                      unsigned_short_as_long_double,
#if THICC_IF(THICC_HAS_COMPLEX)
	                                      unsigned_short_as_float_complex,
	                                      unsigned_short_as_double_complex,
	                                      unsigned_short_as_long_double_complex,
#endif
	                                      unsigned_short_as_string,
	                                      unsigned_short_as_subroutine,
	                                      unsigned_short_as_function,
	                                      unsigned_short_as_array,
	                                      unsigned_short_as_object,
	                                      unsigned_short_sum,
	                                      unsigned_short_difference,
	                                      unsigned_short_product,
	                                      unsigned_short_quotient,
	                                      unsigned_short_power,
	                                      unsigned_short_modulo,
	                                      unsigned_short_logarithm,
	                                      unsigned_short_root,
	                                      unsigned_short_bit_and,
	                                      unsigned_short_bit_or,
	                                      unsigned_short_bit_xor,
	                                      unsigned_short_bit_not,
	                                      unsigned_short_bit_complement,
	                                      unsigned_short_index_of,
	                                      unsigned_short_indirection,
	                                      unsigned_short_negative,
	                                      unsigned_short_positive,
	                                      unsigned_short_comparison};

	Behaviour integer_behaviour = {integer_rank,
	                               stack_deallocate,
	                               integer_as_boolean,
	                               integer_as_character,
	                               integer_as_signed_character,
	                               integer_as_unsigned_character,
	                               integer_as_short,
	                               integer_as_unsigned_short,
	                               integer_as_integer,
	                               integer_as_unsigned_integer,
	                               integer_as_long,
	                               integer_as_unsigned_long,
#if THICC_IF(THICC_C_AT_LEAST(1999))
	                               integer_as_long_long,
	                               integer_as_unsigned_long_long,
#endif
	                               integer_as_float,
	                               integer_as_double,
	                               integer_as_long_double,
#if THICC_IF(THICC_HAS_COMPLEX)
	                               integer_as_float_complex,
	                               integer_as_double_complex,
	                               integer_as_long_double_complex,
#endif
	                               integer_as_string,
	                               integer_as_subroutine,
	                               integer_as_function,
	                               integer_as_array,
	                               integer_as_object,
	                               integer_sum,
	                               integer_difference,
	                               integer_product,
	                               integer_quotient,
	                               integer_power,
	                               integer_modulo,
	                               integer_logarithm,
	                               integer_root,
	                               integer_bit_and,
	                               integer_bit_or,
	                               integer_bit_xor,
	                               integer_bit_not,
	                               integer_bit_complement,
	                               integer_index_of,
	                               integer_indirection,
	                               integer_negative,
	                               integer_positive,
	                               integer_comparison};

	Behaviour unsigned_integer_behaviour = {unsigned_integer_rank,
	                                        stack_deallocate,
	                                        unsigned_integer_as_boolean,
	                                        unsigned_integer_as_character,
	                                        unsigned_integer_as_signed_character,
	                                        unsigned_integer_as_unsigned_character,
	                                        unsigned_integer_as_short,
	                                        unsigned_integer_as_unsigned_short,
	                                        unsigned_integer_as_integer,
	                                        unsigned_integer_as_unsigned_integer,
	                                        unsigned_integer_as_long,
	                                        unsigned_integer_as_unsigned_long,
#if THICC_IF(THICC_C_AT_LEAST(1999))
	                                        unsigned_integer_as_long_long,
	                                        unsigned_integer_as_unsigned_long_long,
#endif
	                                        unsigned_integer_as_float,
	                                        unsigned_integer_as_double,
	                                        unsigned_integer_as_long_double,
#if THICC_IF(THICC_HAS_COMPLEX)
	                                        unsigned_integer_as_float_complex,
	                                        unsigned_integer_as_double_complex,
	                                        unsigned_integer_as_long_double_complex,
#endif
	                                        unsigned_integer_as_string,
	                                        unsigned_integer_as_subroutine,
	                                        unsigned_integer_as_function,
	                                        unsigned_integer_as_array,
	                                        unsigned_integer_as_object,
	                                        unsigned_integer_sum,
	                                        unsigned_integer_difference,
	                                        unsigned_integer_product,
	                                        unsigned_integer_quotient,
	                                        unsigned_integer_power,
	                                        unsigned_integer_modulo,
	                                        unsigned_integer_logarithm,
	                                        unsigned_integer_root,
	                                        unsigned_integer_bit_and,
	                                        unsigned_integer_bit_or,
	                                        unsigned_integer_bit_xor,
	                                        unsigned_integer_bit_not,
	                                        unsigned_integer_bit_complement,
	                                        unsigned_integer_index_of,
	                                        unsigned_integer_indirection,
	                                        unsigned_integer_negative,
	                                        unsigned_integer_positive,
	                                        unsigned_integer_comparison};

	Behaviour long_behaviour = {long_rank,
	                            stack_deallocate,
	                            long_as_boolean,
	                            long_as_character,
	                            long_as_signed_character,
	                            long_as_unsigned_character,
	                            long_as_short,
	                            long_as_unsigned_short,
	                            long_as_integer,
	                            long_as_unsigned_integer,
	                            long_as_long,
	                            long_as_unsigned_long,
#if THICC_IF(THICC_C_AT_LEAST(1999))
	                            long_as_long_long,
	                            long_as_unsigned_long_long,
#endif
	                            long_as_float,
	                            long_as_double,
	                            long_as_long_double,
#if THICC_IF(THICC_HAS_COMPLEX)
	                            long_as_float_complex,
	                            long_as_double_complex,
	                            long_as_long_double_complex,
#endif
	                            long_as_string,
	                            long_as_subroutine,
	                            long_as_function,
	                            long_as_array,
	                            long_as_object,
	                            long_sum,
	                            long_difference,
	                            long_product,
	                            long_quotient,
	                            long_power,
	                            long_modulo,
	                            long_logarithm,
	                            long_root,
	                            long_bit_and,
	                            long_bit_or,
	                            long_bit_xor,
	                            long_bit_not,
	                            long_bit_complement,
	                            long_index_of,
	                            long_indirection,
	                            long_negative,
	                            long_positive,
	                            long_comparison};

	Behaviour unsigned_long_behaviour = {unsigned_long_rank,
	                                     stack_deallocate,
	                                     unsigned_long_as_boolean,
	                                     unsigned_long_as_character,
	                                     unsigned_long_as_signed_character,
	                                     unsigned_long_as_unsigned_character,
	                                     unsigned_long_as_short,
	                                     unsigned_long_as_unsigned_short,
	                                     unsigned_long_as_integer,
	                                     unsigned_long_as_unsigned_integer,
	                                     unsigned_long_as_long,
	                                     unsigned_long_as_unsigned_long,
#if THICC_IF(THICC_C_AT_LEAST(1999))
	                                     unsigned_long_as_long_long,
	                                     unsigned_long_as_unsigned_long_long,
#endif
	                                     unsigned_long_as_float,
	                                     unsigned_long_as_double,
	                                     unsigned_long_as_long_double,
#if THICC_IF(THICC_HAS_COMPLEX)
	                                     unsigned_long_as_float_complex,
	                                     unsigned_long_as_double_complex,
	                                     unsigned_long_as_long_double_complex,
#endif
	                                     unsigned_long_as_string,
	                                     unsigned_long_as_subroutine,
	                                     unsigned_long_as_function,
	                                     unsigned_long_as_array,
	                                     unsigned_long_as_object,
	                                     unsigned_long_sum,
	                                     unsigned_long_difference,
	                                     unsigned_long_product,
	                                     unsigned_long_quotient,
	                                     unsigned_long_power,
	                                     unsigned_long_modulo,
	                                     unsigned_long_logarithm,
	                                     unsigned_long_root,
	                                     unsigned_long_bit_and,
	                                     unsigned_long_bit_or,
	                                     unsigned_long_bit_xor,
	                                     unsigned_long_bit_not,
	                                     unsigned_long_bit_complement,
	                                     unsigned_long_index_of,
	                                     unsigned_long_indirection,
	                                     unsigned_long_negative,
	                                     unsigned_long_positive,
	                                     unsigned_long_comparison};

	Behaviour float_behaviour = {float_rank,
	                             stack_deallocate,
	                             float_as_boolean,
	                             float_as_character,
	                             float_as_signed_character,
	                             float_as_unsigned_character,
	                             float_as_short,
	                             float_as_unsigned_short,
	                             float_as_integer,
	                             float_as_unsigned_integer,
	                             float_as_long,
	                             float_as_unsigned_long,
#if THICC_IF(THICC_C_AT_LEAST(1999))
	                             float_as_long_long,
	                             float_as_unsigned_long_long,
#endif
	                             float_as_float,
	                             float_as_double,
	                             float_as_long_double,
#if THICC_IF(THICC_HAS_COMPLEX)
	                             float_as_float_complex,
	                             float_as_double_complex,
	                             float_as_long_double_complex,
#endif
	                             float_as_string,
	                             float_as_subroutine,
	                             float_as_function,
	                             float_as_array,
	                             float_as_object,
	                             float_sum,
	                             float_difference,
	                             float_product,
	                             float_quotient,
	                             float_power,
	                             float_modulo,
	                             float_logarithm,
	                             float_root,
	                             float_bit_and,
	                             float_bit_or,
	                             float_bit_xor,
	                             float_bit_not,
	                             float_bit_complement,
	                             float_index_of,
	                             float_indirection,
	                             float_negative,
	                             float_positive,
	                             float_comparison};

	Behaviour double_behaviour = {double_rank,
	                              stack_deallocate,
	                              double_as_boolean,
	                              double_as_character,
	                              double_as_signed_character,
	                              double_as_unsigned_character,
	                              double_as_short,
	                              double_as_unsigned_short,
	                              double_as_integer,
	                              double_as_unsigned_integer,
	                              double_as_long,
	                              double_as_unsigned_long,
#if THICC_IF(THICC_C_AT_LEAST(1999))
	                              double_as_long_long,
	                              double_as_unsigned_long_long,
#endif
	                              double_as_float,
	                              double_as_double,
	                              double_as_long_double,
#if THICC_IF(THICC_HAS_COMPLEX)
	                              double_as_float_complex,
	                              double_as_double_complex,
	                              double_as_long_double_complex,
#endif
	                              double_as_string,
	                              double_as_subroutine,
	                              double_as_function,
	                              double_as_array,
	                              double_as_object,
	                              double_sum,
	                              double_difference,
	                              double_product,
	                              double_quotient,
	                              double_power,
	                              double_modulo,
	                              double_logarithm,
	                              double_root,
	                              double_bit_and,
	                              double_bit_or,
	                              double_bit_xor,
	                              double_bit_not,
	                              double_bit_complement,
	                              double_index_of,
	                              double_indirection,
	                              double_negative,
	                              double_positive,
	                              double_comparison};

	Behaviour long_double_behaviour = {long_double_rank,
	                                   stack_deallocate,
	                                   long_double_as_boolean,
	                                   long_double_as_character,
	                                   long_double_as_signed_character,
	                                   long_double_as_unsigned_character,
	                                   long_double_as_short,
	                                   long_double_as_unsigned_short,
	                                   long_double_as_integer,
	                                   long_double_as_unsigned_integer,
	                                   long_double_as_long,
	                                   long_double_as_unsigned_long,
#if THICC_IF(THICC_C_AT_LEAST(1999))
	                                   long_double_as_long_long,
	                                   long_double_as_unsigned_long_long,
#endif
	                                   long_double_as_float,
	                                   long_double_as_double,
	                                   long_double_as_long_double,
#if THICC_IF(THICC_HAS_COMPLEX)
	                                   long_double_as_float_complex,
	                                   long_double_as_double_complex,
	                                   long_double_as_long_double_complex,
#endif
	                                   long_double_as_string,
	                                   long_double_as_subroutine,
	                                   long_double_as_function,
	                                   long_double_as_array,
	                                   long_double_as_object,
	                                   long_double_sum,
	                                   long_double_difference,
	                                   long_double_product,
	                                   long_double_quotient,
	                                   long_double_power,
	                                   long_double_modulo,
	                                   long_double_logarithm,
	                                   long_double_root,
	                                   long_double_bit_and,
	                                   long_double_bit_or,
	                                   long_double_bit_xor,
	                                   long_double_bit_not,
	                                   long_double_bit_complement,
	                                   long_double_index_of,
	                                   long_double_indirection,
	                                   long_double_negative,
	                                   long_double_positive,
	                                   long_double_comparison};

	Behaviour string_behaviour = {string_rank,
	                              string_deallocate,
	                              string_as_boolean,
	                              string_as_character,
	                              string_as_signed_character,
	                              string_as_unsigned_character,
	                              string_as_short,
	                              string_as_unsigned_short,
	                              string_as_integer,
	                              string_as_unsigned_integer,
	                              string_as_long,
	                              string_as_unsigned_long,
#if THICC_IF(THICC_C_AT_LEAST(1999))
	                              string_as_long_long,
	                              string_as_unsigned_long_long,
#endif
	                              string_as_float,
	                              string_as_double,
	                              string_as_long_double,
#if THICC_IF(THICC_HAS_COMPLEX)
	                              string_as_float_complex,
	                              string_as_double_complex,
	                              string_as_long_double_complex,
#endif
	                              string_as_string,
	                              string_as_subroutine,
	                              string_as_function,
	                              string_as_array,
	                              string_as_object,
	                              string_sum,
	                              string_difference,
	                              string_product,
	                              string_quotient,
	                              string_power,
	                              string_modulo,
	                              string_logarithm,
	                              string_root,
	                              string_bit_and,
	                              string_bit_or,
	                              string_bit_xor,
	                              string_bit_not,
	                              string_bit_complement,
	                              string_index_of,
	                              string_indirection,
	                              string_negative,
	                              string_positive,
	                              string_comparison};

	Behaviour subroutine_behaviour = {subroutine_rank,
	                                  stack_deallocate,
	                                  subroutine_as_boolean,
	                                  subroutine_as_character,
	                                  subroutine_as_signed_character,
	                                  subroutine_as_unsigned_character,
	                                  subroutine_as_short,
	                                  subroutine_as_unsigned_short,
	                                  subroutine_as_integer,
	                                  subroutine_as_unsigned_integer,
	                                  subroutine_as_long,
	                                  subroutine_as_unsigned_long,
#if THICC_IF(THICC_C_AT_LEAST(1999))
	                                  subroutine_as_long_long,
	                                  subroutine_as_unsigned_long_long,
#endif
	                                  subroutine_as_float,
	                                  subroutine_as_double,
	                                  subroutine_as_long_double,
#if THICC_IF(THICC_HAS_COMPLEX)
	                                  subroutine_as_float_complex,
	                                  subroutine_as_double_complex,
	                                  subroutine_as_long_double_complex,
#endif
	                                  subroutine_as_string,
	                                  subroutine_as_subroutine,
	                                  subroutine_as_function,
	                                  subroutine_as_array,
	                                  subroutine_as_object,
	                                  subroutine_sum,
	                                  subroutine_difference,
	                                  subroutine_product,
	                                  subroutine_quotient,
	                                  subroutine_power,
	                                  subroutine_modulo,
	                                  subroutine_logarithm,
	                                  subroutine_root,
	                                  subroutine_bit_and,
	                                  subroutine_bit_or,
	                                  subroutine_bit_xor,
	                                  subroutine_bit_not,
	                                  subroutine_bit_complement,
	                                  subroutine_index_of,
	                                  subroutine_indirection,
	                                  subroutine_negative,
	                                  subroutine_positive,
	                                  subroutine_comparison};

	Behaviour function_behaviour = {function_rank,
	                                stack_deallocate,
	                                function_as_boolean,
	                                function_as_character,
	                                function_as_signed_character,
	                                function_as_unsigned_character,
	                                function_as_short,
	                                function_as_unsigned_short,
	                                function_as_integer,
	                                function_as_unsigned_integer,
	                                function_as_long,
	                                function_as_unsigned_long,
#if THICC_IF(THICC_C_AT_LEAST(1999))
	                                function_as_long_long,
	                                function_as_unsigned_long_long,
#endif
	                                function_as_float,
	                                function_as_double,
	                                function_as_long_double,
#if THICC_IF(THICC_HAS_COMPLEX)
	                                function_as_float_complex,
	                                function_as_double_complex,
	                                function_as_long_double_complex,
#endif
	                                function_as_string,
	                                function_as_subroutine,
	                                function_as_function,
	                                function_as_array,
	                                function_as_object,
	                                function_sum,
	                                function_difference,
	                                function_product,
	                                function_quotient,
	                                function_power,
	                                function_modulo,
	                                function_logarithm,
	                                function_root,
	                                function_bit_and,
	                                function_bit_or,
	                                function_bit_xor,
	                                function_bit_not,
	                                function_bit_complement,
	                                function_index_of,
	                                function_indirection,
	                                function_negative,
	                                function_positive,
	                                function_comparison};

	Behaviour array_behaviour = {
	    array_rank,
	    array_deallocate,
	    array_as_boolean,
	    array_as_character,
	    array_as_signed_character,
	    array_as_unsigned_character,
	    array_as_short,
	    array_as_unsigned_short,
	    array_as_integer,
	    array_as_unsigned_integer,
	    array_as_long,
	    array_as_unsigned_long,
#if THICC_IF(THICC_C_AT_LEAST(1999))
	    array_as_long_long,
	    array_as_unsigned_long_long,
#endif
	    array_as_float,
	    array_as_double,
	    array_as_long_double,
#if THICC_IF(THICC_HAS_COMPLEX)
	    array_as_float_complex,
	    array_as_double_complex,
	    array_as_long_double_complex,
#endif
	    array_as_string,
	    array_as_subroutine,
	    array_as_function,
	    array_as_array,
	    array_as_object,
	    array_sum,
	    array_difference,
	    array_product,
	    array_quotient,
	    array_power,
	    array_modulo,
	    array_logarithm,
	    array_root,
	    array_bit_and,
	    array_bit_or,
	    array_bit_xor,
	    array_bit_not,
	    array_bit_complement,
	    array_index_of,
	    array_indirection,
	    array_negative,
	    array_positive,
	    array_comparison,
	};

	Behaviour object_behaviour = {object_rank,
	                              object_deallocate,
	                              object_as_boolean,
	                              object_as_character,
	                              object_as_signed_character,
	                              object_as_unsigned_character,
	                              object_as_short,
	                              object_as_unsigned_short,
	                              object_as_integer,
	                              object_as_unsigned_integer,
	                              object_as_long,
	                              object_as_unsigned_long,
#if THICC_IF(THICC_C_AT_LEAST(1999))
	                              object_as_long_long,
	                              object_as_unsigned_long_long,
#endif
	                              object_as_float,
	                              object_as_double,
	                              object_as_long_double,
#if THICC_IF(THICC_HAS_COMPLEX)
	                              object_as_float_complex,
	                              object_as_double_complex,
	                              object_as_long_double_complex,
#endif
	                              object_as_string,
	                              object_as_subroutine,
	                              object_as_function,
	                              object_as_array,
	                              object_as_object,
	                              object_sum,
	                              object_difference,
	                              object_product,
	                              object_quotient,
	                              object_power,
	                              object_modulo,
	                              object_logarithm,
	                              object_root,
	                              object_bit_and,
	                              object_bit_or,
	                              object_bit_xor,
	                              object_bit_not,
	                              object_bit_complement,
	                              object_index_of,
	                              object_indirection,
	                              object_negative,
	                              object_positive,
	                              object_comparison};

#ifdef __cplusplus
}
#endif

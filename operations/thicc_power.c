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

#include "thicc_power.h"
#include "../core/thicc_interface.h"
#include "../core/thicc_struct_let.h"
#include "../utility/thicc_function.h"
#include "../utility/thicc_math_typedef.h"

	MutableLet boolean_power(Let _left, Let _right) {
		return let_boolean((!_left.value.boolean_type && _right.value.boolean_type) ? THICC_NO : THICC_YES);
	}

	MutableLet character_power(Let _left, Let _right) {
#if THICC_IF(THICC_CHAR_SIGNED)
		if(_right.value.character_type >= 0) {
			MutableInteger result = 1, base = (Integer) _left.value.character_type, exponent = (Integer) _right.value.character_type;
			for THICC_FOREVER {
				if (exponent % 2)
					result *= base;
				exponent /= 2;
				if (!exponent)
					break;
				base *= base;
			}
			return let_character((Character) result);
		} else {
			return let_float(THICC_POWERF(as_float(_left), as_float(_right)));
		}
#else
	    MutableUnsignedInteger result = 1u, base = (UnsignedInteger) _left.value.character_type, exponent = (UnsignedInteger) _right.value.character_type;
	        for THICC_FOREVER {
			        if (exponent % 2u)
				        result *= base;
			        exponent /= 2u;
			        if (!exponent)
				        break;
			        base *= base;
		        }
	        return let_character((char) result);
#endif
	}
	
	MutableLet signed_character_power(Let _left, Let _right) {
		if(_right.value.signed_character_type >= 0) {
			MutableInteger result = 1, base = (Integer) _left.value.signed_character_type, exponent = (Integer) _right.value.signed_character_type;
			for THICC_FOREVER {
					if (exponent % 2)
						result *= base;
					exponent /= 2;
					if (!exponent)
						break;
					base *= base;
				}
			return let_signed_character((SignedCharacter) result);
		} else {
			return let_float(THICC_POWERF(as_float(_left), as_float(_right)));
		}
	}

	MutableLet unsigned_character_power(Let _left, Let _right) {
		MutableUnsignedInteger result = 1u, base = (UnsignedInteger) _left.value.unsigned_character_type, exponent = (UnsignedInteger) _right.value.unsigned_character_type;
		    for THICC_FOREVER {
				    if (exponent % 2u)
					    result *= base;
				    exponent /= 2u;
				    if (!exponent)
					    break;
				    base = base * base;
			    }
		    return let_unsigned_character((UnsignedCharacter) result);
	}
	
	MutableLet short_power(Let _left, Let _right) {
		if(_right.value.short_type >= 0) {
			MutableInteger result = 1, base = (Integer) _left.value.short_type, exponent = (Integer) _right.value.short_type;
			for THICC_FOREVER {
				if (exponent % 2)
					result *= base;
				exponent /= 2;
				if (!exponent)
					break;
				base *= base;
			}
			return let_short((Short) result);
		} else {
			return let_float(THICC_POWERF(as_float(_left), as_float(_right)));
		}
	}
	
	MutableLet unsigned_short_power(Let _left, Let _right) {
		MutableUnsignedInteger result = 1u, base = (UnsignedInteger) _left.value.unsigned_short_type, exponent = (UnsignedInteger) _right.value.unsigned_short_type;
		    for THICC_FOREVER {
				    if (exponent % 2u)
					    result *= base;
				    exponent /= 2u;
				    if (!exponent)
					    break;
				    base = base * base;
			    }
		    return let_unsigned_short((UnsignedShort) result);
	}

	MutableLet integer_power(Let _left, Let _right) {
		if(_right.value.integer_type >= 0) {
			MutableInteger result = 1, base = _left.value.integer_type, exponent = _right.value.integer_type;
			for THICC_FOREVER {
					if (exponent % 2)
						result *= base;
					exponent /= 2;
					if (!exponent)
						break;
					base *= base;
				}
			return let_integer(result);
		} else {
			return let_double(THICC_POWERD(as_double(_left), as_double(_right)));
		}
	}

	MutableLet unsigned_integer_power(Let _left, Let _right) {
		MutableUnsignedInteger result = 1u, base = _left.value.unsigned_integer_type, exponent = _right.value.unsigned_integer_type;
		    for THICC_FOREVER {
				    if (exponent % 2u)
					    result *= base;
				    exponent /= 2u;
				    if (!exponent)
					    break;
				    base = base * base;
			    }
		    return let_unsigned_integer(result);
	}

	MutableLet long_power(Let _left, Let _right) {
		if(_right.value.long_type >= 0l) {
			MutableLong result = 1l, base = _left.value.long_type, exponent = _right.value.long_type;
			for THICC_FOREVER {
					if (exponent % 2l)
						result *= base;
					exponent /= 2l;
					if (!exponent)
						break;
					base *= base;
				}
			return let_long(result);
		} else {
			return let_long_double(THICC_POWERL(as_long_double(_left), as_long_double(_right)));
		}
	}

	MutableLet unsigned_long_power(Let _left, Let _right) {
		MutableUnsignedLong result = 1ul, base = _left.value.unsigned_long_type, exponent = _right.value.unsigned_long_type;
		    for THICC_FOREVER {
				    if (exponent % 2ul)
					    result *= base;
				    exponent /= 2ul;
				    if (!exponent)
					    break;
				    base = base * base;
			    }
		    return let_unsigned_long(result);
	}

	MutableLet float_power(Let _left, Let _right) {
		return let_float(THICC_POWERF(_left.value.float_type, _right.value.float_type));
	}

	MutableLet double_power(Let _left, Let _right) {
		return let_double(THICC_POWERD(_left.value.double_type, _right.value.double_type));
	}

	MutableLet long_double_power(Let _left, Let _right) {
		return let_long_double(THICC_POWERL(_left.value.long_double_type, _right.value.long_double_type));
	}

	MutableLet string_power(Let _left, Let _right) {
		return let_empty(); /* TODO: Implement */
	}

	MutableLet subroutine_power(Let _left, Let _right) {
		return let_empty();
	}

	MutableLet function_power(Let _left, Let _right) {
		Let left_result = function_invoke(_left, let_empty());
		Let right_result = function_invoke(_right, let_empty());
		Let result = power(left_result, right_result);
		if(requires_free(right_result))
			unlet(right_result);
		if(requires_free(left_result))
			unlet(left_result);
		return result;
	}

	MutableLet array_power(Let _left, Let _right) {
		return let_empty(); /* TODO: Implement */
	}

	MutableLet object_power(Let _left, Let _right) {
		Let property_name = let_string("**");
		Let property = member(_left, property_name);
		unlet(property_name);
		if(let_is_empty(property) || !is_invokable(property))
			return let_empty();
		return invoke(property, 2, &_left, &_right);
	}

#ifdef __cplusplus
}
#endif

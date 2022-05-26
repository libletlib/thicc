//
// Created by Ville Rissanen on 13.5.2022.
//

#ifdef __cplusplus
extern "C"
{
#endif

#include "thicc_c99_as_long_long.h"
#include "../../core/thicc_interface.h"
#include "../../core/thicc_struct_let.h"
#include "../../utility/thicc_character.h"
#include "../../utility/thicc_function.h"
#include "../../utility/thicc_math_typedef.h"
#include <complex.h>

#if THICC_IF(THICC_C_AT_LEAST(1999))

	MutableLongLong boolean_as_long_long(Let _let) {
		return _let.value.boolean_type ? 1ll : 0ll;
	}

	MutableLongLong character_as_long_long(Let _let) {
		return (LongLong) character_to_number(_let.value.character_type);
	}

	MutableLongLong signed_character_as_long_long(Let _let) {
		return (LongLong) signed_character_to_number(_let.value.signed_character_type);
	}

	MutableLongLong unsigned_character_as_long_long(Let _let) {
		return (LongLong) unsigned_character_to_number(_let.value.unsigned_character_type);
	}

	MutableLongLong short_as_long_long(Let _let) {
		return (LongLong) _let.value.short_type;
	}

	MutableLongLong unsigned_short_as_long_long(Let _let) {
		return (LongLong) _let.value.unsigned_short_type;
	}

	MutableLongLong integer_as_long_long(Let _let) {
		return (LongLong) _let.value.integer_type;
	}

	MutableLongLong unsigned_integer_as_long_long(Let _let) {
		return (LongLong) _let.value.unsigned_integer_type;
	}

	MutableLongLong long_as_long_long(Let _let) {
		return _let.value.long_type;
	}

	MutableLongLong unsigned_long_as_long_long(Let _let) {
		return (LongLong) _let.value.unsigned_long_type;
	}

	MutableLongLong long_long_as_long_long(Let _let) {
		return _let.value.long_long_type;
	}

	MutableLongLong unsigned_long_long_as_long_long(Let _let) {
		return (LongLong) _let.value.unsigned_long_long_type;
	}

	MutableLongLong float_as_long_long(Let _let) {
		return (LongLong) _let.value.float_type;
	}

	MutableLongLong double_as_long_long(Let _let) {
		return (LongLong) _let.value.double_type;
	}

	MutableLongLong long_double_as_long_long(Let _let) {
		return (LongLong) _let.value.long_double_type;
	}

#if THICC_IF(THICC_HAS_COMPLEX)

	MutableLongLong float_complex_as_long_long(Let _let) {
		return (LongLong) (THICC_ROUNDF(cabsf(_let.value.float_complex_type)));
	}

	MutableLongLong double_complex_as_long_long(Let _let) {
		return (LongLong) (THICC_ROUNDD(cabs(_let.value.double_complex_type)));
	}

	MutableLongLong long_double_complex_as_long_long(Let _let) {
		return (LongLong) (THICC_ROUNDL(cabsl(_let.value.long_double_complex_type)));
	}

#endif

	MutableLongLong string_as_long_long(Let _let) {
		return (LongLong) *string_view(_let);
	}

	MutableLongLong subroutine_as_long_long(Let _let) {
		return 0ll;
	}

	MutableLongLong function_as_long_long(Let _let) {
		Let temporary = function_invoke(_let, let_empty());
		Long result = as_long(temporary);
		if(requires_free(temporary))
			unlet(temporary);
		return result;
	}

	MutableLongLong array_as_long_long(Let _let) {
		return as_long(*array_view(_let));
	}

	MutableLongLong object_as_long_long(Let _let) {
		return *((Long* THICC_RESTRICT) object_view(_let));
	}

#endif

#ifdef __cplusplus
}
#endif

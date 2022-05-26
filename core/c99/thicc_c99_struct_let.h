//
// Created by Ville Rissanen on 13.5.2022.
//

#ifndef THICC_C99_STRUCT_LET_H
#define THICC_C99_STRUCT_LET_H

#include "../thicc_struct_let.h"

#ifdef __cplusplus
	extern "C"
	{
#endif

#if THICC_IF(THICC_C_AT_LEAST(1999))

MutableLet let_long_long(LongLong);
MutableLet let_unsigned_long_long(UnsignedLongLong);
#if THICC_IF(THICC_HAS_COMPLEX)
MutableLet let_float_complex(FloatComplex);
MutableLet let_double_complex(DoubleComplex);
MutableLet let_long_double_complex(LongDoubleComplex);
#endif

#endif

#ifdef __cplusplus
    }
#endif

#endif//THICC_C99_STRUCT_LET_H

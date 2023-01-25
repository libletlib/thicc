/*
 *   ___       ___       ___       ___       ___
 *  /\  \     /\__\     /\  \     /\  \     /\  \
 *  \:\  \   /:/__/_   _\:\  \   /::\  \   /::\  \
 *  /::\__\ /::\/\__\ /\/::\__\ /:/\:\__\ /:/\:\__\
 * /:/\/__/ \/\::/  / \::/\/__/ \:\ \/__/ \:\ \/__/
 * \/__/      /:/  /   \:\__\    \:\__\    \:\__\
 *            \/__/     \/__/     \/__/     \/__/
 *
 * Copyright 2022 Ville Rissanen
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1.   Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *
 * 2.   Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the docs
 *      and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef THICC_THICC_FORTRAN_PRELUDE_H
#define THICC_THICC_FORTRAN_PRELUDE_H

#ifndef THICC_FORTRAN_VERSION
#define THICC_FORTRAN_VERSION 2003
#endif

#if (THICC_FORTRAN_VERSION == 2003)
#elif (THICC_FORTRAN_VERSION == 2008)
#elif (THICC_FORTRAN_VERSION == 2018)
#endif

#undef THICC_FORTRAN_AT_LEAST
#define THICC_FORTRAN_AT_LEAST(_version_year) (THICC_FORTRAN_VERSION >= (_version_year) ? 1 : 0)

#undef THICC_FORTRAN_IMPURE_ELEMENTAL
#if THICC_FORTRAN_AT_LEAST(2008)
#define THICC_FORTRAN_IMPURE_ELEMENTAL impure elemental
#else
#define THICC_FORTRAN_IMPURE_ELEMENTAL
#endif

#ifndef THICC_FORTRAN_C_VERSION
#define THICC_FORTRAN_C_VERSION 90
#endif

#if (THICC_FORTRAN_C_VERSION == 90)
#elif (THICC_FORTRAN_C_VERSION == 99)
#elif (THICC_FORTRAN_C_VERSION == 11)
#elif (THICC_FORTRAN_C_VERSION == 17)
#elif (THICC_FORTRAN_C_VERSION == 23)
#endif

#undef THICC_FORTRAN_C_AT_LEAST
#define THICC_FORTRAN_C_AT_LEAST(_version_year) (THICC_FORTRAN_C_VERSION >= (_version_year) ? 1 : 0)

#undef THICC_FORTRAN_INTEGER
#undef THICC_FORTRAN_REAL
#undef THICC_FORTRAN_COMPLEX
#if (THICC_FORTRAN_C_VERSION == 90)
#define THICC_FORTRAN_INTEGER c_long
#else
#define THICC_FORTRAN_INTEGER c_long_long
#endif
#define THICC_FORTRAN_REAL c_long_double
#define THICC_FORTRAN_COMPLEX c_long_double_complex

#endif /* THICC_THICC_FORTRAN_PRELUDE_H */

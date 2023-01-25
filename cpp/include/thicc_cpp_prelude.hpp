/*
 *   ___       ___       ___       ___       ___
 *  /\  \     /\__\     /\  \     /\  \     /\  \
 *  \:\  \   /:/__/_   _\:\  \   /::\  \   /::\  \
 *  /::\__\ /::\/\__\ /\/::\__\ /:/\:\__\ /:/\:\__\
 * /:/\/__/ \/\::/  / \::/\/__/ \:\ \/__/ \:\ \/__/
 * \/__/      /:/  /   \:\__\    \:\__\    \:\__\
 *            \/__/     \/__/     \/__/     \/__/
 *
 * Copyright 2022 - 2023 Ville Rissanen
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1.   Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *
 * 2.   Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef THICC_THICC_CPP_PRELUDE_HPP
#define THICC_THICC_CPP_PRELUDE_HPP

#include <thicc_prelude.h>

#undef THICC_CPP98
#undef THICC_CPP11
#undef THICC_CPP14
#undef THICC_CPP17
#undef THICC_CPP20
#undef THICC_CPP_VERSION
#if (__cplusplus < 201103L)
#define THICC_CPP98 THICC_YES
#define THICC_CPP11 THICC_NO
#define THICC_CPP14 THICC_NO
#define THICC_CPP17 THICC_NO
#define THICC_CPP20 THICC_NO
#define THICC_CPP_VERSION 1998
#elif (__cplusplus >= 201103L) && (__cplusplus < 201402L)
#define THICC_CPP98 THICC_NO
#define THICC_CPP11 THICC_YES
#define THICC_CPP14 THICC_NO
#define THICC_CPP17 THICC_NO
#define THICC_CPP20 THICC_NO
#define THICC_CPP_VERSION 2011
#elif (__cplusplus >= 201402L) && (__cplusplus < 201703L)
#define THICC_CPP98 THICC_NO
#define THICC_CPP11 THICC_NO
#define THICC_CPP14 THICC_YES
#define THICC_CPP17 THICC_NO
#define THICC_CPP20 THICC_NO
#define THICC_CPP_VERSION 2014
#elif (__cplusplus >= 201703L) && (__cplusplus < 202002L)
#define THICC_CPP98 THICC_NO
#define THICC_CPP11 THICC_NO
#define THICC_CPP14 THICC_NO
#define THICC_CPP17 THICC_YES
#define THICC_CPP20 THICC_NO
#define THICC_CPP_VERSION 2017
#elif (__cplusplus >= 202002L)
#define THICC_CPP98 THICC_NO
#define THICC_CPP11 THICC_NO
#define THICC_CPP14 THICC_NO
#define THICC_CPP17 THICC_NO
#define THICC_CPP20 THICC_YES
#define THICC_CPP_VERSION 2020
#endif

#undef THICC_CPP_AT_LEAST
#define THICC_CPP_AT_LEAST(_version_year) (THICC_CPP_VERSION >= (_version_year) ? THICC_YES : THICC_NO)

#undef THICC_CPP_UREF
#undef THICC_CPP_NOEXCEPT
#undef THICC_CPP_FINAL
#undef THICC_CPP_CONSTEXPR
#if THICC_CPP_AT_LEAST(2011)
#define THICC_CPP_UREF &&
#define THICC_CPP_NOEXCEPT noexcept
#define THICC_CPP_FINAL final
#define THICC_CPP_CONSTEXPR constexpr
#else
#define THICC_CPP_UREF const&
#define THICC_CPP_NOEXCEPT
#define THICC_CPP_FINAL
#define THICC_CPP_CONSTEXPR
#endif

#undef THICC_CPP_NODISCARD
#undef THICC_CPP_MAYBE_UNUSED
#if THICC_CPP_AT_LEAST(2017)
#define THICC_CPP_MAYBE_UNUSED [[maybe_unused]]
#define THICC_CPP_NODISCARD [[nodiscard]]
#else
#define THICC_CPP_MAYBE_UNUSED
#define THICC_CPP_NODISCARD
#endif

#undef THICC_STANDARD_BI_OPERATOR
#define THICC_STANDARD_BI_OPERATOR(_op, _op_name)                                                                \
  THICC_CPP_NODISCARD var& operator _op##=(var const& _right) THICC_CPP_NOEXCEPT {                               \
	return *this = _op_name(this->variable, _right.variable);                                                    \
  }                                                                                                              \
                                                                                                                 \
  template<typename Type>                                                                                        \
  THICC_CPP_NODISCARD var& operator _op##=(Type THICC_CPP_UREF _right) THICC_CPP_NOEXCEPT {                      \
	return *this = _op_name(this->variable, var(_right).variable);                                               \
  }                                                                                                              \
                                                                                                                 \
  template<typename Type>                                                                                        \
  THICC_CPP_NODISCARD friend var operator _op(var const& _left, Type THICC_CPP_UREF _right) THICC_CPP_NOEXCEPT { \
	return _op_name(_left.variable, var(_right).variable);                                                       \
  }                                                                                                              \
                                                                                                                 \
  template<typename Type>                                                                                        \
  THICC_CPP_NODISCARD friend var operator _op(Type THICC_CPP_UREF _left, var const& _right) THICC_CPP_NOEXCEPT { \
	return _op_name(var(_left).variable, _right.variable);                                                       \
  }                                                                                                              \
                                                                                                                 \
  THICC_CPP_NODISCARD var operator _op(var const& _right) const THICC_CPP_NOEXCEPT {                             \
	return _op_name(this->variable, _right.variable);                                                            \
  }                                                                                                              \
  THICC_CPP_NODISCARD var operator _op(var& _right) THICC_CPP_NOEXCEPT {                                         \
	return _op_name(this->variable, _right.variable);                                                            \
  }

#define lambda(_code)                                                                \
  [](THICC_CPP_MAYBE_UNUSED Let* _self, THICC_CPP_MAYBE_UNUSED Let* _args) -> Let* { \
	let self = backing::move(_self), args = backing::move(_args);                    \
	_code                                                                            \
  }

#define fn(_code)                                                            \
  (THICC_CPP_MAYBE_UNUSED Let * _self, THICC_CPP_MAYBE_UNUSED Let * _args) { \
	let self = backing::move(_self), args = backing::move(_args);            \
	_code                                                                    \
  }

#endif // THICC_THICC_CPP_PRELUDE_HPP

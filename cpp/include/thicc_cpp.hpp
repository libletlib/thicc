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
#ifndef THICC_THICC_CPP_HPP
#define THICC_THICC_CPP_HPP

#include <thicc.h>
#include <thicc_struct_var.h>
#include "thicc_cpp_prelude.hpp"
#include <ostream>

namespace thicc {
  class var;
  typedef var const let;

  namespace backing {
	inline var move(Let*) THICC_CPP_NOEXCEPT;

	template<class Type>
	inline THICC_CPP_CONSTEXPR Type* address_of(Type& _type) THICC_CPP_NOEXCEPT {
	  return reinterpret_cast<Type*>(&const_cast<char&>(reinterpret_cast<const volatile char&>(_type)));
	}
  }

  class var THICC_CPP_FINAL {
	friend inline var backing::move(Let*) THICC_CPP_NOEXCEPT;
	Let* variable;

  public:
	~var() THICC_CPP_NOEXCEPT {
	  unlet(this->variable);
	}

	var() THICC_CPP_NOEXCEPT : variable(let_empty()) {}
	var(bool _value) THICC_CPP_NOEXCEPT : variable(let_boolean(_value)) {}
	var(char _value) THICC_CPP_NOEXCEPT : variable(let_character(_value)) {}
	var(signed char _value) THICC_CPP_NOEXCEPT : variable(let_character(static_cast<Character>(_value))) {}
	var(unsigned char _value) THICC_CPP_NOEXCEPT : variable(let_character(static_cast<Character>(_value))) {}
	var(short _value) THICC_CPP_NOEXCEPT : variable(let_integer(static_cast<Integer>(_value))) {}
	var(unsigned short _value) THICC_CPP_NOEXCEPT : variable(let_natural(static_cast<Natural>(_value))) {}
	var(int _value) THICC_CPP_NOEXCEPT : variable(let_integer(static_cast<Integer>(_value))) {}
	var(unsigned int _value) THICC_CPP_NOEXCEPT : variable(let_natural(static_cast<Natural>(_value))) {}
	var(long _value) THICC_CPP_NOEXCEPT : variable(let_integer(static_cast<Integer>(_value))) {}
	var(unsigned long _value) THICC_CPP_NOEXCEPT : variable(let_natural(static_cast<Natural>(_value))) {}
	var(float _value) THICC_CPP_NOEXCEPT : variable(let_real(static_cast<Real>(_value))) {}
	var(double _value) THICC_CPP_NOEXCEPT : variable(let_real(static_cast<Real>(_value))) {}
	var(long double _value) THICC_CPP_NOEXCEPT : variable(let_real(_value)) {}
	var(char* _value) THICC_CPP_NOEXCEPT : variable(let_string(_value)) {}
	var(MutableString const& _value) THICC_CPP_NOEXCEPT : variable(let_string(_value.string)) {}
	var(MutableArray const& _value) THICC_CPP_NOEXCEPT : variable(let_array(_value)) {}
	var(MutableFunction _value) THICC_CPP_NOEXCEPT : variable(let_function(_value)) {}
	var(MutableObject _value) THICC_CPP_NOEXCEPT : variable(let_object(_value)) {}
	var(Let* _var) THICC_CPP_NOEXCEPT : variable(let_copy(_var)) {}

	var(var const& _other) THICC_CPP_NOEXCEPT : variable(let_copy(_other.variable)) {}

	template<typename Value>
	var& operator=(Value const& _other) THICC_CPP_NOEXCEPT;

	template<>
	var& operator=(var const& _other) THICC_CPP_NOEXCEPT;

	var& operator=(Let* _other) THICC_CPP_NOEXCEPT {
	  this->variable = let_copy(_other);
	  return *this;
	}

#if THICC_CPP_AT_LEAST(2011)
	explicit var(long long _value) : variable(let_integer(_value)) {}
	explicit var(unsigned long long _value) : variable(let_natural(_value)) {}

	var(var&& _other) noexcept : variable(let_move(const_cast<Var*>(_other.variable))) {}
	var& operator=(var&& _other) noexcept {
	  if(this != backing::address_of(_other))
		this->variable = let_move(const_cast<Var*>(_other.variable));
	  return *this;
	}
#endif

	var operator~() const THICC_CPP_NOEXCEPT {
	  return bit_complement(this->variable);
	}

	var operator!() const THICC_CPP_NOEXCEPT {
	  return bit_not(this->variable);
	}

	var operator*() const THICC_CPP_NOEXCEPT {
	  return indirection(this->variable);
	}

	var operator-() const THICC_CPP_NOEXCEPT {
	  return negative(this->variable);
	}

	var operator+() const THICC_CPP_NOEXCEPT {
	  return positive(this->variable);
	}

	var operator[](var const& _value) const THICC_CPP_NOEXCEPT {
	  return index_of(this->variable, _value.variable);
	}

	template<typename Value>
	var operator[](Value THICC_CPP_UREF _value) const THICC_CPP_NOEXCEPT {
	  return index_of(this->variable, var(_value).variable);
	}

	var operator[](var& _value) const THICC_CPP_NOEXCEPT {
	  return index_of(this->variable, _value.variable);
	}

	operator Let*() const {
	  return this->variable;
	}

	THICC_STANDARD_BI_OPERATOR(+, sum)
	THICC_STANDARD_BI_OPERATOR(-, difference)
	THICC_STANDARD_BI_OPERATOR(*, product)
	THICC_STANDARD_BI_OPERATOR(/, quotient)
	THICC_STANDARD_BI_OPERATOR(&, bit_and)
	THICC_STANDARD_BI_OPERATOR(|, bit_or)
	THICC_STANDARD_BI_OPERATOR(^, bit_xor)
	THICC_STANDARD_BI_OPERATOR(%, modulo)

	friend std::ostream& operator<<(std::ostream& _out, var const& _item) THICC_CPP_NOEXCEPT {
	  MutableString printable = as_string(_item.variable);
	  _out << printable.string;
	  free(printable.string);
	  return _out;
	}

	var operator()() const {
	  if(is_invokable(this->variable))
		return call(this->variable);
	  return let();
	}

	template<typename Type1>
	var operator()(Type1 THICC_CPP_UREF _type1) const {
	  if(is_invokable(this->variable)) {
		let temporary = let(_type1);
		return invoke(this->variable, 1, temporary.variable);
	  }
	  return var();
	}

	template<>
	var operator()(var const& _type1) const {
	  if(is_invokable(this->variable))
		return invoke(this->variable, 1, _type1.variable);
	  return var();
	}
  };

  namespace backing {
	inline var move(Let* _let) THICC_CPP_NOEXCEPT {
	  var result;
	  result.variable = let_move(const_cast<Var*>(_let));
	  return result;
	}
  }

  template<typename Value>
  var& var::operator=(Value const& _other) THICC_CPP_NOEXCEPT {
	return *this = var(_other);
  }

  template<>
  var& var::operator=(var const& _other) THICC_CPP_NOEXCEPT {
	this->variable = let_copy(_other.variable);
	return *this;
  }
}



#endif // THICC_THICC_CPP_HPP

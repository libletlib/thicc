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
 *      this list of conditions and the following disclaimer in the documentation
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

template<class Type>
inline Type* address_of(Type& _type) THICC_CPP_NOEXCEPT {
  return reinterpret_cast<Type*>(&const_cast<char&>(reinterpret_cast<const char&>(_type)));
}

class var THICC_CPP_FINAL {
	Var variable;

  public:
	virtual ~var() {
	  unlet_if_required(this->variable);
	}

	var() : variable(let_empty()) {}
	explicit var(bool _value) : variable(let_boolean(_value)) {}
	explicit var(char _value) : variable(let_character(_value)) {}
	explicit var(signed char _value) : variable(let_character((Character) _value)) {}
	explicit var(unsigned char _value) : variable(let_character((Character) _value)) {}
	explicit var(short _value) : variable(let_integer(_value)) {}
	explicit var(unsigned short _value) : variable(let_natural(_value)) {}
	explicit var(int _value) : variable(let_integer(_value)) {}
	explicit var(unsigned int _value) : variable(let_natural(_value)) {}
	explicit var(long _value) : variable(let_integer(_value)) {}
	explicit var(unsigned long _value) : variable(let_natural(_value)) {}
	explicit var(float _value) : variable(let_real(_value)) {}
	explicit var(double _value) : variable(let_real(_value)) {}
	explicit var(long double _value) : variable(let_real(_value)) {}
	explicit var(char* _value) : variable(let_string(_value)) {}
	explicit var(MutableString _value) : variable(let_string(_value.string)) {}
	explicit var(MutableArray _value) : variable(let_array(_value)) {}
	explicit var(MutableFunction _value) : variable(let_function(_value)) {}
	explicit var(MutableObject _value) : variable(let_object(_value)) {}
	explicit var(Var _var) : variable(_var) {}

	template<typename Value>
	var(Value const& _value) {
	  *this = var(_value);
	}

	var(var const& _other) : variable(let_copy(_other.variable)) {}

	var& operator=(var const& _other) {
	  this->variable = let_copy(_other.variable);
	  return *this;
	}

	template<typename Value>
	var& operator=(Value const& _other) {
	  return *this = var(_other);
	}

	template<>
	var& operator=(var const& _other) {
	  this->variable = let_copy(_other.variable);
	  return *this;
	}

#if THICC_CPP_AT_LEAST(2011)
	explicit var(long long _value) : variable(let_integer(_value)) {}
	explicit var(unsigned long long _value) : variable(let_natural(_value)) {}

	var(var&& _other) noexcept : variable(let_move(_other.variable)) {}
	var& operator=(var&& _other) noexcept {
	  if(this != address_of(_other)) {
		this->variable = let_move(_other.variable);
	  }
	  return *this;
	}
#endif

	var operator~() {
	  return var(bit_complement(this->variable));
	}

	var operator!() {
	  return var(bit_not(this->variable));
	}

	var operator*() {
	  return var(indirection(this->variable));
	}

	var operator-() {
	  return var(negative(this->variable));
	}

	var operator+() {
	  return var(positive(this->variable));
	}

	var operator[](var const& _value) {
	  return index_of(this->variable, _value.variable);
	}

	template<typename Value>
	var operator[](Value THICC_CPP_UREF _value) {
	  return this->operator[](var(_value));
	}

	var operator[](var& _value) {
	  return this->operator[](const_cast<var const&>(_value));
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
		Var printable = move_string(as_string(_item.variable));
		_out << string_view(printable);
		unlet(printable);
		return _out;
	}

	var operator()() {
		if(is_invokable(this->variable))
			return call(this->variable);
		return var();
	}
};

typedef var const let;

#endif // THICC_THICC_CPP_HPP

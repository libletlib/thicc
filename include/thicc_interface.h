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
#ifndef THICC_THICC_INTERFACE_H
#define THICC_THICC_INTERFACE_H

/**
 * \file thicc_interface.h
 * Includes declarations for most API elements not directly involved in creation or handling of ThicC internal data.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "thicc_prelude.h"
#include "thicc_struct_array.h"
#include "thicc_struct_complex.h"
#include "thicc_struct_string.h"
#include "thicc_struct_var.h"
#include <stdarg.h>

/**
 * \brief Return the rank of a Let. An empty Let has the rank of object_rank.
 * Refer to thicc_enum_rank.h for the enumeration values.
 * \param _let to evaluate rank of.
 * \return rank of the _let. If _let is empty, then its rank will be object_rank.
 */
MutableRank rank(Let* _let);
/**
 * \brief Convert a Let to another type of Let.
 * \param _let to cast.
 * \param _rank to cast to.
 * \return _let as converted to _rank type of Let.
 */
Let* cast(Let* _let, Rank _rank);
/**
 * \brief Free the memory owned by a Let.
 * Recursively frees all memory owned by various container types as well, such as `Array` or `Object`.
 * \param _let to free memory of.
 */
void unlet(Let* _let);
/**
 * \brief An empty function that returns an empty Let.
 * \param _self to pass function pointer to itself.
 * \param _args to pass arguments as an array of Let.
 * \return An empty Let.
 */
Let* empty_function(Let* _self, Let* _args);
/**
 * \brief Return a pointer to the memory owned by a Let as a C string.
 * \param _let to view memory of.
 * \return Memory of the Let as a C string.
 */
Character* string_view(Let* _let);
/**
 * \brief Return a pointer to the memory owned by a Let as an array of array of Lets.
 * \param _let to view memory of.
 * \return Memory of the Let as an array of arrays of Lets.
 */
Let* const* array_view(Let* _let);
/**
 * \brief Return a pointer to the memory owned by a Let as an object (an array of two arrays).
 * \param _let to view memory of.
 * \return Memory of the Let as an object (an array of two arrays).
 */
Object object_view(Let* _let);
/**
 * \brief Convert a Let to Boolean.
 * \param _let to convert to Boolean.
 * \return Boolean value of _let.
 */
MutableBoolean as_boolean(Let* _let);
/**
 * \brief Convert a Let to Character.
 * \param _let to convert to Character.
 * \return Character value of _let.
 */
MutableCharacter as_character(Let* _let);
/**
 * \brief Convert a Let to Natural.
 * \param _let to convert to Natural.
 * \return Natural value of _let.
 */
MutableNatural as_natural(Let* _let);
/**
 * \brief Convert a Let to Integer.
 * \param _let to convert to Integer.
 * \return Integer value of _let.
 */
MutableInteger as_integer(Let* _let);
/**
 * \brief Convert a Let to Real.
 * \param _let to convert to Real.
 * \return Real value of _let.
 */
MutableReal as_real(Let* _let);
/**
 * \brief Convert a Let to Complex.
 * \param _let to convert to Complex.
 * \return Complex value of _let.
 */
MutableComplex as_complex(Let* _let);
/**
 * \brief Convert a Let to String.
 * \param _let to convert to String.
 * \return String value of _let.
 */
MutableString as_string(Let* _let);
/**
 * \brief Convert a Let to Function.
 * \param _let to convert to Function.
 * \return Function value of _let.
 */
MutableFunction as_function(Let* _let);
/**
 * \brief Convert a Let to Array.
 * \param _let to convert to Array.
 * \return Array value of _let.
 */
MutableArray as_array(Let* _let);
/**
 * \brief Convert a Let to Object.
 * \param _let to convert to Object.
 * \return Object value of _let.
 */
MutableObject as_object(Let* _let);
/**
 * \brief Array from a raw Boolean array.
 * \param _size of the boolean array.
 * \param _array pointer to the array.
 * \return A Let array copy of the booleans of _array.
 */
Let* array_from_booleans(Size _size, Boolean* _array);
/**
 * \brief Array from a raw Character array.
 * \param _size of the character array.
 * \param _array pointer to the array.
 * \return A Let array copy of the characters of _array.
 */
Let* array_from_characters(Size _size, Character* _array);
/**
 * \brief Array from a raw Integer array.
 * \param _size of the integer array.
 * \param _array pointer to the array.
 * \return A Let array copy of the integers of _array.
 */
Let* array_from_integers(Size _size, Integer* _array);
/**
 * \brief Array from a raw Real array.
 * \param _size of the real array.
 * \param _array pointer to the array.
 * \return A Let array copy of the reals of _array.
 */
Let* array_from_reals(Size _size, Real* _array);
/**
 * \brief Array from a raw Complex array.
 * \param _size of the complex array.
 * \param _array pointer to the array.
 * \return A Let array copy of the complex's of _array.
 */
Let* array_from_complex(Size _size, Complex* _array);
/**
 * \brief Array from a raw String array.
 * \param _size of the string array.
 * \param _array pointer to the array.
 * \return A Let array copy of the strings of _array.
 */
Let* array_from_strings(Size _size, MutableCharacter** _array);
/**
 * \brief Construct an array of various Lets.
 * \param _size amount of Lets passed to this function
 * \param ... Lets to construct the array from.
 * \return Let of type array with a copy of the arguments passed to this function variadically.
 */
Let* array_of(Size _size, ...);
/**
 * \brief Construct a Let object from the given elements.
 * \param _size of the object, must be an even number.
 * \param ... the elements to construct the object from in the format of [key, value, key, value, ...].
 * \return A Let object made from the given variadic arguments.
 */
Let* object_of(Size _size, ...);
/**
 * \brief Invoke a Let function without arguments.
 * \param _invokable to invoke without arguments.
 * \return Result of the invocation.
 */
Let* call(Let* _invokable);
/**
 * \brief Invoke a Let function with arguments.
 * \param _invokable to invoke with arguments.
 * \param _size amount of arguments passed to function.
 * \param ... arguments to be passed to function.
 * \return Result of the invocation.
 */
Let* invoke(Let* _invokable, Size _size, ...);
/**
 * \brief Invoke a Let function with the arguments of a va_list.
 * \param _invokable to invoke with arguments.
 * \param _size amount of arguments in _list.
 * \param _list of arguments (as Let).
 * \return Result of the invocation.
 */
Let* invoke_from_list(Let* _invokable, Size _size, va_list _list);
/**
 * \brief Return a member of the object by its key.
 * \param _object to get member from.
 * \param _member key to retrieve.
 * \return A copy of the value by _member key in _object.
 */
Let* member(Let* _object, Let* _member);
/**
 * \brief Return the sum of two Lets.
 * As a binary operator, the types go through rank arbitration to determine which is the highest ranking type and
 * then the lower ranking type is cast to the same rank as the higher ranking type. Then the operation is executed
 * on the types of equal rank.
 *
 * Sum shortly by type:																								<br>
 * `Boolean`: AND gate. `THICC_YES` + `THICC_YES` = `THICC_YES`; `THICC_YES` + `THICC_NO` = `THICC_NO`.				<br>
 * `Character`: Form a two character string. `'a' + 'b' = "ab"`.													<br>
 * `Natural`: Normal plus operation.																				<br>
 * `Integer`: Normal plus operation.																				<br>
 * `Real`: Normal plus operation.																					<br>
 * `Complex`: Normal plus operation.																				<br>
 * `String`: `String` concatenation.																				<br>
 * `Function`: Functions are invoked with no arguments and operation is re-evaluated based on the result types.		<br>
 * `Array`: Array concatenation.																					<br>
 * `Object`: User implementable, otherwise an empty `Let`.															<br>
 *
 * \param _left side of the operation.
 * \param _right side of the operation.
 * \return the result of the operation.
 */
Let* sum(Let* _left, Let* _right);
/**
 * \brief Return the difference of two Lets.
 * As a binary operator, the types go through rank arbitration to determine which is the highest ranking type and
 * then the lower ranking type is cast to the same rank as the higher ranking type. Then the operation is executed
 * on the types of equal rank.
 *
 * Difference shortly by type:																						<br>
 * `Boolean`: AND gate, right hand side is negated. `THICC_YES` - (`THICC_NO` => `THICC_YES`) = `THICC_YES`.		<br>
 * `Character`: Treat as ASCII integers.																			<br>
 * `Natural`: Normal minus operation.																				<br>
 * `Integer`: Normal minus operation.																				<br>
 * `Real`: Normal minus operation.																					<br>
 * `Complex`: Normal minus operation.																				<br>
 * `String`: Remove right hand side substring from left hand side `String`.											<br>
 * `Function`: Functions are invoked with no arguments and operation is re-evaluated based on the result types.		<br>
 * `Array`: Remove right hand side subarray from left hand side array.												<br>
 * `Object`: User implementable, otherwise an empty `Let`.															<br>
 *
 * \param _left side of the operation.
 * \param _right side of the operation.
 * \return the result of the operation.
 */
Let* difference(Let* _left, Let* _right);
/**
 * \brief Return the quotient of two Lets.
 * As a binary operator, the types go through rank arbitration to determine which is the highest ranking type and
 * then the lower ranking type is cast to the same rank as the higher ranking type. Then the operation is executed
 * on the types of equal rank.
 *
 * Quotient shortly by type:																						<br>
 * `Boolean`: AND gate. `THICC_YES` / `THICC_YES` = `THICC_YES`; `THICC_YES` / `THICC_NO` = `THICC_NO`.				<br>
 * `Character`: Treat as ASCII integers, if the result would be a floating point number, its type will be `Real`.	<br>
 * `Natural`: Normal division operation, if the result would be a floating point number, its type will be `Real`.	<br>
 * `Integer`: Normal division operation, if the result would be a floating point number, its type will be `Real`.	<br>
 * `Real`: Normal division operation.																				<br>
 * `Complex`: Normal division operation.																			<br>
 * `String`: Filter left hand side `String` with the characters on the right hand side `String`.					<br>
 * `Function`: Functions are invoked with no arguments and operation is re-evaluated based on the result types.		<br>
 * `Array`: Filter left hand side `Array` with the elements on the right hand side `Array`.							<br>
 * `Object`: User implementable, otherwise an empty `Let`.															<br>
 *
 * \param _left side of the operation.
 * \param _right side of the operation.
 * \return the result of the operation.
 */
Let* quotient(Let* _left, Let* _right);
/**
 * \brief Return the modulo of two Lets.
 * As a binary operator, the types go through rank arbitration to determine which is the highest ranking type and
 * then the lower ranking type is cast to the same rank as the higher ranking type. Then the operation is executed
 * on the types of equal rank.
 *
 * Modulo shortly by type:																							<br>
 * `Boolean`: AND gate. `THICC_YES` % `THICC_YES` = `THICC_YES`; `THICC_YES` % `THICC_NO` = `THICC_NO`.				<br>
 * `Character`: Treat as ASCII integers.																			<br>
 * `Natural`: Normal modulo operation.																				<br>
 * `Integer`: Normal modulo operation.																				<br>
 * `Real`: Normal modulo operation.																					<br>
 * `Complex`: Normal modulo operation.																				<br>
 * `String`: Tokenise left hand side `String` into an `Array` based on tokens on the right hand side `String`.		<br>
 * `Function`: Functions are invoked with no arguments and operation is re-evaluated based on the result types.		<br>
 * `Array`: Zip into one `Array`.																					<br>
 * `Object`: User implementable, otherwise an empty `Let`.															<br>
 *
 * \param _left side of the operation.
 * \param _right side of the operation.
 * \return the result of the operation.
 */
Let* modulo(Let* _left, Let* _right);
/**
 * \brief Return the product of two Lets.
 * As a binary operator, the types go through rank arbitration to determine which is the highest ranking type and
 * then the lower ranking type is cast to the same rank as the higher ranking type. Then the operation is executed
 * on the types of equal rank.
 *
 * Product shortly by type:																							<br>
 * `Boolean`: AND gate. `THICC_YES` + `THICC_YES` = `THICC_YES`; `THICC_YES` + `THICC_NO` = `THICC_NO`.				<br>
 * `Character`: Treat as `sum(Let* _left, Let* _right)` operation.													<br>
 * `Natural`: Normal product operation.																				<br>
 * `Integer`: Normal product operation.																				<br>
 * `Real`: Normal product operation.																				<br>
 * `Complex`: Normal product operation.																				<br>
 * `String`: Treat as `sum(Let* _left, Let* _right)` operation.														<br>
 * `Function`: Functions are invoked with no arguments and operation is re-evaluated based on the result types.		<br>
 * `Array`: Treat as `sum(Let* _left, Let* _right)` operation.														<br>
 * `Object`: User implementable, otherwise an empty `Let`.															<br>
 *
 * \param _left side of the operation.
 * \param _right side of the operation.
 * \return the result of the operation.
 */
Let* product(Let* _left, Let* _right);
/**
 * \brief Return the binary AND of two Lets.
 * As a binary operator, the types go through rank arbitration to determine which is the highest ranking type and
 * then the lower ranking type is cast to the same rank as the higher ranking type. Then the operation is executed
 * on the types of equal rank.
 *
 * Bitwise AND shortly by type:																						<br>
 * `Boolean`: AND gate. `THICC_YES` + `THICC_YES` = `THICC_YES`; `THICC_YES` + `THICC_NO` = `THICC_NO`.				<br>
 * `Character`: Treat as ASCII integers.																			<br>
 * `Natural`: Normal bitwise AND operation.																			<br>
 * `Integer`: Normal bitwise AND operation.																			<br>
 * `Real`: Custom bitwise AND operation.																			<br>
 * `Complex`: Custom bitwise AND operation.																			<br>
 * `String`: Filter left hand side `String` to include only characters in the right hand side `String`.				<br>
 * `Function`: Functions are invoked with no arguments and operation is re-evaluated based on the result types.		<br>
 * `Array`: Filter left hand side `Array` to include only elements in the right hand side `Array`.					<br>
 * `Object`: User implementable, otherwise an empty `Let`.															<br>
 *
 * \param _left side of the operation.
 * \param _right side of the operation.
 * \return the result of the operation.
 */
Let* bit_and(Let* _left, Let* _right);
/**
 * \brief Return the binary OR of two Lets.
 * As a binary operator, the types go through rank arbitration to determine which is the highest ranking type and
 * then the lower ranking type is cast to the same rank as the higher ranking type. Then the operation is executed
 * on the types of equal rank.
 *
 * Bitwise OR shortly by type:																						<br>
 * `Boolean`: OR gate. `THICC_YES` + `THICC_YES` = `THICC_YES`; `THICC_YES` + `THICC_NO` = `THICC_YES`.				<br>
 * `Character`: Treat as ASCII integers.																			<br>
 * `Natural`: Normal bitwise OR operation.																			<br>
 * `Integer`: Normal bitwise OR operation.																			<br>
 * `Real`: Custom bitwise OR operation.																				<br>
 * `Complex`: Custom bitwise OR operation.																			<br>
 * `String`: Filter left hand side `String` to include only characters not in the right hand side `String`.			<br>
 * `Function`: Functions are invoked with no arguments and operation is re-evaluated based on the result types.		<br>
 * `Array`: Filter left hand side `Array` to include only elements not in the right hand side `Array`.				<br>
 * `Object`: User implementable, otherwise an empty `Let`.															<br>
 *
 * \param _left side of the operation.
 * \param _right side of the operation.
 * \return the result of the operation.
 */
Let* bit_or(Let* _left, Let* _right);
/**
 * \brief Return the binary XOR of two Lets.'
 * As a binary operator, the types go through rank arbitration to determine which is the highest ranking type and
 * then the lower ranking type is cast to the same rank as the higher ranking type. Then the operation is executed
 * on the types of equal rank.
 *
 * Bitwise XOR shortly by type:																						<br>
 * `Boolean`: XOR gate. `THICC_YES` + `THICC_YES` = `THICC_NO`; `THICC_YES` + `THICC_NO` = `THICC_YES`.				<br>
 * `Character`: Treat as ASCII integers.																			<br>
 * `Natural`: Normal bitwise XOR operation.																			<br>
 * `Integer`: Normal bitwise XOR operation.																			<br>
 * `Real`: Custom bitwise XOR operation.																			<br>
 * `Complex`: Custom bitwise XOR operation.																			<br>
 * `String`: Filter both `String`s to include only characters not in either `String`.								<br>
 * `Function`: Functions are invoked with no arguments and operation is re-evaluated based on the result types.		<br>
 * `Array`: Filter both `Array`s to include only elements not in either `Array`.									<br>
 * `Object`: User implementable, otherwise an empty `Let`.															<br>
 *
 * \param _left side of the operation.
 * \param _right side of the operation.
 * \return the result of the operation.
 */
Let* bit_xor(Let* _left, Let* _right);
/**
 * \brief Return the index of a Let.
 * The _index argument will be converted to the Integer type, unless it already is an integral type as defined by
 * `is_integral` function.
 *
 * Index-of shortly by type:																						<br>
 * `Boolean`: Return value.																							<br>
 * `Character`: Return value.																						<br>
 * `Natural`: Return digit in the number. Index can be negative or under-/overflow safely.							<br>
 * `Integer`: Return digit in the number. Index can be negative or under-/overflow safely.							<br>
 * `Real`: Return digit in the number. Index can be negative or under-/overflow safely.								<br>
 * `Complex`: Return digit in the real number part. Index can be negative or under-/overflow safely.				<br>
 * `String`: Return `Character` in the `String`. Index can be negative or under-/overflow safely.					<br>
 * `Function`: Functions are invoked with no arguments and operation is re-evaluated based on the result types.		<br>
 * `Array`: Return element in the `Array`. Index can be negative or under-/overflow safely.							<br>
 * `Object`: User implementable, otherwise an empty `Let`.															<br>
 *
 * \param _indexable to get element from.
 * \param _index to access.
 * \return element of _indexable at _index.
 */
Let* index_of(Let* _indexable, Let* _index);
/**
 * \brief Return the boolean NOT of a Let.
 *
 * Boolean NOT shortly by type:																						<br>
 * `Boolean`: Boolean negation of value.																			<br>
 * `Character`: Boolean negation of ASCII value.																	<br>
 * `Natural`: Boolean negation of value.																			<br>
 * `Integer`: Boolean negation of value.																			<br>
 * `Real`: Boolean negation of value.																				<br>
 * `Complex`: If not { .real = 0.0, .imaginary = 0.0 }, `THICC_YES`, otherwise `THICC_NO`.							<br>
 * `String`: Is the pointer `THICC_NAUGHT`?																			<br>
 * `Function`: Functions are invoked with no arguments and operation is re-evaluated based on the result types.		<br>
 * `Array`: Boolean negation of every element in `Array`.															<br>
 * `Object`: User implementable, otherwise an empty `Let`.															<br>
 *
 * \param _let to operate on.
 * \return Result of the operation.
 */
Let* bit_not(Let* _let);
/**
 * \brief Return the binary complement of a Let.
 *
 * Boolean complement shortly by type:																				<br>
 * `Boolean`: Same as `bit_not(Let* _let)`.																			<br>
 * `Character`: Binary complement of the ASCII value.																<br>
 * `Natural`: Binary complement of value.																			<br>
 * `Integer`: Binary complement of value.																			<br>
 * `Real`: Custom binary complement of value.																		<br>
 * `Complex`: Custom binary complement of value.																	<br>
 * `String`: Binary complement of every character of `String`.														<br>
 * `Function`: Functions are invoked with no arguments and operation is re-evaluated based on the result types.		<br>
 * `Array`: Binary complement of every element of `Array`.															<br>
 * `Object`: User implementable, otherwise an empty `Let`.															<br>
 *
 * \param _let to operate on.
 * \return Result of the operation.
 */
Let* bit_complement(Let* _let);
/**
 * \brief Return the indirection of a Let.
 *
 * Indirection shortly by type:																						<br>
 * `Boolean`: Return value.																							<br>
 * `Character`: Return value.																						<br>
 * `Natural`: Return value.																							<br>
 * `Integer`: Return value.																							<br>
 * `Real`: Return value.																							<br>
 * `Complex`: Return value.																							<br>
 * `String`: Return first `Character`.																				<br>
 * `Function`: Functions are invoked with no arguments and operation is re-evaluated based on the result types.		<br>
 * `Array`: Return first element.																					<br>
 * `Object`: User implementable, otherwise an empty `Let`.															<br>
 *
 * \param _let to operate on.
 * \return Result of the operation.
 */
Let* indirection(Let* _let);
/**
 * \brief Return the negative of a Let.
 *
 * Indirection shortly by type:																						<br>
 * `Boolean`: `THICC_NO`.																							<br>
 * `Character`: Return negative value, converting to a `Integer`, if `Character` is not a signed type.				<br>
 * `Natural`: Negative value as `Integer`.																			<br>
 * `Integer`: Negative value.																						<br>
 * `Real`: Negative value.																							<br>
 * `Complex`: Negative value.																						<br>
 * `String`: Negative value for each `Character` of the `String`.													<br>
 * `Function`: Functions are invoked with no arguments and operation is re-evaluated based on the result types.		<br>
 * `Array`: Negative value for each element of the `Array`.															<br>
 * `Object`: User implementable, otherwise an empty `Let`.															<br>
 *
 * \param _let to operate on.
 * \return Result of the operation.
 */
Let* negative(Let* _let);
/**
 * \brief Return the positive of a Let.
 *
 * Indirection shortly by type:																						<br>
 * `Boolean`: `THICC_YES`.																							<br>
 * `Character`: Positive value.																						<br>
 * `Natural`: Positive value.																						<br>
 * `Integer`: Positive value.																						<br>
 * `Real`: Positive value.																							<br>
 * `Complex`: Positive value.																						<br>
 * `String`: Positive value for each character of the `String`.														<br>
 * `Function`: Functions are invoked with no arguments and operation is re-evaluated based on the result types.		<br>
 * `Array`: Positive value for each element of the `Array`.															<br>
 * `Object`: User implementable, otherwise an empty `Let`.															<br>
 *
 * \param _let to operate on.
 * \return Result of the operation.
 */
Let* positive(Let* _let);
/**
 * \brief Return the comparison of two Lets.
 * As a binary operator, the types go through rank arbitration to determine which is the highest ranking type and
 * then the lower ranking type is cast to the same rank as the higher ranking type. Then the operation is executed
 * on the types of equal rank.
 * \param _left side of the operation.
 * \param _right side of the operation.
 * \return -1 if the left side is greater, 1 if the right side is greater and 0 if both sides are equal.
 */
MutableComparison compare(Let* _left, Let* _right);
/**
 * \brief Return the equality of two Lets.
 * As a binary operator, the types go through rank arbitration to determine which is the highest ranking type and
 * then the lower ranking type is cast to the same rank as the higher ranking type. Then the operation is executed
 * on the types of equal rank.
 * \param _left side of the operation.
 * \param _right side of the operation.
 * \return THICC_YES if _left and _right are equal, otherwise THICC_NO.
 */
MutableBoolean equal(Let* _left, Let* _right);
/**
 * \brief Return the greater than of two Lets.
 * As a binary operator, the types go through rank arbitration to determine which is the highest ranking type and
 * then the lower ranking type is cast to the same rank as the higher ranking type. Then the operation is executed
 * on the types of equal rank.
 * \param _left side of the operation.
 * \param _right side of the operation.
 * \return THICC_YES if _left is greater than _right, otherwise THICC_NO.
 */
MutableBoolean greater_than(Let* _left, Let* _right);
/**
 * \brief Return the less than of two Lets.
 * As a binary operator, the types go through rank arbitration to determine which is the highest ranking type and
 * then the lower ranking type is cast to the same rank as the higher ranking type. Then the operation is executed
 * on the types of equal rank.
 * \param _left side of the operation.
 * \param _right side of the operation.
 * \return THICC_YES if _left is less than _right, otherwise THICC_NO.
 */
MutableBoolean less_than(Let* _left, Let* _right);
/**
 * \brief Return the inequality of two Lets.
 * As a binary operator, the types go through rank arbitration to determine which is the highest ranking type and
 * then the lower ranking type is cast to the same rank as the higher ranking type. Then the operation is executed
 * on the types of equal rank.
 * \param _left side of the operation.
 * \param _right side of the operation.
 * \return THICC_YES if _left and _right are not equal, otherwise THICC_NO.
 */
MutableBoolean not_equal(Let* _left, Let* _right);
/**
 * \brief Return the length of a Let depending on the type.
 * \param _let to evaluate length of.
 * \return Length of _let.
 */
MutableSize length(Let* _let);
/**
 * \brief Is the given Let a character type?
 * \param _let to evaluate.
 * \return True, if _let is a character type, otherwise false.
 */
MutableBoolean is_character(Let* _let);
/**
 * \brief Is the given Let a numeric type?
 * \param _let to evaluate.
 * \return True, if _let is a numeric type, otherwise false.
 */
MutableBoolean is_numeric(Let* _let);
/**
 * \brief Is the given Let a integral type?
 * \param _let to evaluate.
 * \return True, if _let is a integral type, otherwise false.
 */
MutableBoolean is_integral(Let* _let);
/**
 * \brief Is the given Let an unsigned type?
 * \param _let to evaluate.
 * \return True, if _let is an unsigned type, otherwise false.
 */
MutableBoolean is_unsigned(Let* _let);
/**
 * \brief Is the given Let a signed type?
 * \param _let to evaluate.
 * \return True, if _let is a signed type, otherwise false.
 */
MutableBoolean is_signed(Let* _let);
/**
 * \brief Is the given Let a floating point type?
 * \param _let to evaluate.
 * \return True, if _let is a floating point type, otherwise false.
 */
MutableBoolean is_floating_point(Let* _let);
/**
 * \brief Is the given Let a string type?
 * \param _let to evaluate.
 * \return True, if _let is a string type, otherwise false.
 */
MutableBoolean is_string(Let* _let);
/**
 * \brief Is the given Let an invocable type?
 * \param _let to evaluate.
 * \return True, if _let is an invocable type, otherwise false.
 */
MutableBoolean is_invokable(Let* _let);
/**
 * \brief Is the given Let an array type?
 * \param _let to evaluate.
 * \return True, if _let is an array type, otherwise false.
 */
MutableBoolean is_array(Let* _let);
/**
 * \brief Is the given Let an object type?
 * \param _let to evaluate.
 * \return True, if _let is an object type, otherwise false.
 */
MutableBoolean is_object(Let* _let);
/**
 * \brief Is the given Let an indexable type?
 * \param _let to evaluate.
 * \return True, if _let is an indexable type, otherwise false.
 */
MutableBoolean is_indexable(Let* _let);

#ifdef __cplusplus
}
#endif

#endif /* THICC_THICC_INTERFACE_H */

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
#ifdef __cplusplus
extern "C" {
#endif

#include "thicc_as_object.h"
#include "../utility/thicc_object.h"
#include <thicc_interface.h>
#include <thicc_struct_var.h>

THICC_NODISCARD MutableObject boolean_as_object(THICC_MAYBE_UNUSED Let* _let) {
  Let*			key	   = let_string("boolean");
  MutableObject result = object_compose(2, key, _let);
  unlet(key);
  return result;
}

THICC_NODISCARD MutableObject character_as_object(THICC_MAYBE_UNUSED Let* _let) {
  Let*			key	   = let_string("character");
  MutableObject result = object_compose(2, key, _let);
  unlet(key);
  return result;
}

THICC_NODISCARD MutableObject natural_as_object(THICC_MAYBE_UNUSED Let* _let) {
  Let*			key	   = let_string("natural");
  MutableObject result = object_compose(2, key, _let);
  unlet(key);
  return result;
}

THICC_NODISCARD MutableObject integer_as_object(THICC_MAYBE_UNUSED Let* _let) {
  Let*			key	   = let_string("integer");
  MutableObject result = object_compose(2, key, _let);
  unlet(key);
  return result;
}

THICC_NODISCARD MutableObject real_as_object(THICC_MAYBE_UNUSED Let* _let) {
  Let*			key	   = let_string("real");
  MutableObject result = object_compose(2, key, _let);
  unlet(key);
  return result;
}

THICC_NODISCARD MutableObject complex_as_object(THICC_MAYBE_UNUSED Let* _let) {
  Let*			key	   = let_string("complex");
  MutableObject result = object_compose(2, key, _let);
  unlet(key);
  return result;
}

THICC_NODISCARD MutableObject string_as_object(THICC_MAYBE_UNUSED Let* _let) {
  Let*			key	   = let_string("string");
  MutableObject result = object_compose(2, key, _let);
  unlet(key);
  return result;
}

THICC_NODISCARD MutableObject function_as_object(THICC_MAYBE_UNUSED Let* _let) {
  Let*			key	   = let_string("function");
  MutableObject result = object_compose(2, key, _let);
  unlet(key);
  return result;
}

THICC_NODISCARD MutableObject array_as_object(THICC_MAYBE_UNUSED Let* _let) {
  Let*			key	   = let_string("array");
  MutableObject result = object_compose(2, key, _let);
  unlet(key);
  return result;
}

THICC_NODISCARD MutableObject object_as_object(Let* _let) {
  return object_copy(object_view(_let));
}

#ifdef __cplusplus
}
#endif

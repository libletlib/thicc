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
 * 2.   Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
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

#include "thicc_memory.h"
#include <thicc_struct_array.h>
#include <thicc_struct_string.h>
#include <thicc_interface.h>
#include <stdlib.h>
#include "thicc_struct_object.h"

THICC_NODISCARD static void* allocate(Size _size) {
  return calloc(_size, 1);
}

static void deallocate(void* const _pointer) {
  free(_pointer);
}

THICC_NODISCARD MutableString string_allocate(Size _length) {
  MutableString string = string_empty();
  string.string = allocate(_length);
  return string;
}

THICC_NODISCARD MutableArray array_allocate(Size _length) {
  MutableArray array = array_empty();
  array.array		 = allocate(_length * sizeof(Var));
  return array;
}

THICC_NODISCARD MutableObject object_allocate(void) {
  return allocate(sizeof(struct thicc_struct_object));
}

void stack_deallocate(THICC_MAYBE_UNUSED Let _let) { /* No-Op */
}

void string_deallocate(Let _let) {
  if (string_view(_let))
	deallocate((void*) _let.value.string_type.string);
}

void array_deallocate(Let _let) {
  if (array_view(_let)) {
	MutableSize index = 0;

	for (; index < _let.value.array_type.length; ++index)
	  unlet(array_view(_let)[index]);

	deallocate((void*) _let.value.array_type.array);
  }
}

void object_deallocate(Let _let) {
  if (object_view(_let)) {
	array_deallocate(((Root) _let.value.object_type)->members);
	deallocate(_let.value.object_type);
  }
}

#ifdef __cplusplus
}
#endif

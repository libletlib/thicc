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

#include "test.h"
#include <stdio.h>
#include <stdlib.h>

THICC_NODISCARD int test(void) {
  puts("I: Boolean tests...");
  assert(boolean_test());
  puts("I: Boolean tests OK!");
  puts("II: Character tests...");
  assert(character_test());
  puts("II: Character tests OK!");
  puts("III: Natural tests...");
  assert(natural_test());
  puts("III: Natural tests OK!");
  puts("IV: Integer tests...");
  assert(integer_test());
  puts("IV: Integer tests OK!");
  puts("V: Real tests...");
  assert(real_test());
  puts("V: Real tests OK!");
  puts("VI: Complex tests...");
  assert(complex_test());
  puts("VI: Complex tests OK!");
  puts("VII: String tests...");
  assert(string_test());
  puts("VII: String tests OK!");
  puts("VIII: Function tests...");
  assert(function_test());
  puts("VIII: Function tests OK!");
  puts("IX: Array tests...");
  assert(array_test());
  puts("IX: Array tests OK!");
  puts("X: Object tests...");
  assert(object_test());
  puts("X: Object tests OK!");
  return 1;
}

int main(void) {
  puts("Starting tests...");
  /*assert(test());*/
  puts("Tests OK!");
  return EXIT_SUCCESS;
}

#ifdef __cplusplus
}
#endif

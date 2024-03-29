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

#include <string.h>
#include <thicc_interface.h>
#include <thicc_struct_string.h>

THICC_NODISCARD MutableString string_empty(void) {
  MutableString string;
  string.string = THICC_NAUGHT;
  string.length = 0;
  return string;
}

THICC_NODISCARD MutableSize string_length(String _string) {
  return strlen(_string.string);
}

THICC_NODISCARD MutableString string_from_pointer(MutableCharacter* _string) {
  MutableString result;
  result.string = _string;
  result.length = string_length(result);
  return result;
}

THICC_NODISCARD MutableBoolean string_is_empty(String _string) {
  if (_string.string == THICC_NAUGHT || _string.length == 0)
	return THICC_YES;
  return THICC_NO;
}

#ifdef __cplusplus
}
#endif

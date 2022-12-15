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

#include "thicc_struct_object.h"
#include "thicc_interface.h"

THICC_NODISCARD Root root(Let _object) {
  return (Root) _object.value.object_type;
}

THICC_NODISCARD Array root_members(Let _object) {
  return array_view(root(_object)->members);
}

THICC_NODISCARD Array root_keys(Let _object) {
  return array_view(root_members(_object)[0]);
}

THICC_NODISCARD Array root_values(Let _object) {
  return array_view(root_members(_object)[1]);
}

THICC_NODISCARD Root root_from_pointer(ImmutableObject _object) {
  return (Root) _object;
}

THICC_NODISCARD Array root_members_from_pointer(ImmutableObject _object) {
  return array_view(root_from_pointer(_object)->members);
}

THICC_NODISCARD Array root_keys_from_pointer(ImmutableObject _object) {
  return array_view(root_members_from_pointer(_object)[0]);
}

THICC_NODISCARD Array root_values_from_pointer(ImmutableObject _object) {
  return array_view(root_members_from_pointer(_object)[1]);
}

#ifdef __cplusplus
}
#endif

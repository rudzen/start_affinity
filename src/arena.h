// Copyright (c) 2025 Rudy Alex Kohn
// See end of file for extended copyright information.

#pragma once

#include <cstdint>
#include <cstdlib>

/* Arena allocator structure */
struct Arena {
  char* memory;
  size_t size;
  size_t used;
};

namespace arena {

inline int arena_init(Arena* arena, const size_t size) {
  arena->memory = static_cast<char*>(std::malloc(size));
  if (!arena->memory)
    return 0;
  arena->size = size;
  arena->used = 0;
  return 1;
}

inline void* arena_alloc(Arena* arena, const size_t size) {
  if (arena->used + size > arena->size)
    return nullptr;
  void* result = arena->memory + arena->used;
  arena->used += size;
  return result;
}

inline void arena_free(Arena* arena) {
  if (arena->memory)
  {
    std::free(arena->memory);
    arena->memory = nullptr;
    arena->size   = 0;
    arena->used   = 0;
  }
}

inline void arena_reset(Arena* arena) {
  arena->used = 0;
}

}   // namespace arena

// StartAffinity - set application thread affinity to specific core(s)
// Copyright (C) 2025  Rudy Alex Kohn
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
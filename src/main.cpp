// Copyright (c) 2025 Rudy Alex Kohn
// Copyright (C) 2006 Adsci Engineering, LLC
// See end of file for extended copyright information.

#include "affinity.h"
#include "arena.h"
#include "args.h"
#include <cstdio>

int main(const int argc, char* argv[]) {

  Arena arena;

  /* Initialize arena with 4KB */
  if (!arena::arena_init(&arena, 4096))
  {
    printf("Failed to initialize memory arena\n");
    return 1;
  }

  char* filename;
  Cores cores;
  int result = 0;

  if (args::parse_args(&arena, argc, argv, &filename, &cores))
    result = affinity::run_start_affinity(filename, &cores);
  else
  {
    printf("Usage: %s -f <filename> <core0> [core1 ... coreN]\n", argv[0]);
    printf("  -f <filename>   : Executable to start (must exist)\n");
    printf("  <core0..N>      : CPU core numbers (0-31)\n");
    printf("Example: %s -f notepad.exe 0 1\n", argv[0]);
    result = 1;
  }

  arena::arena_free(&arena);
  return result;
}

// StartAffinity - set application thread affinity to specific core(s)
// Copyright (C) 2020-2025 Rudy Alex Kohn
// Copyright (C) 2006 Adsci Engineering, LLC
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
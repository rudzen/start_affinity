#include "args.h"
#include "affinity.h"
#include "arena.h"

#include <cstdio>
#include <cstring>

namespace {

int file_exists(const char* filename) {
  FILE* file = fopen(filename, "r");

  if (!file)
    return 0;

  fclose(file);
  return 1;
}

/// Parse string to integer with error checking
int parse_int(const char* str, int* result) {
  int x = 0;
  while (*str >= '0' && *str <= '9')
  {
    x = x * 10 + (*str - '0');
    ++str;
  }

  if (x < 0 || x > 31 || *str != '\0')
    return 0;

  *result = x;
  return 1;
}

}   // namespace

int args::parse_args(Arena* arena, int argc, char* argv[], char** filename, Cores* cores) {
  if (argc < 4)
    return 0; /* Need at least -f <filename> <core> */

  if (strcmp(argv[1], "-f") != 0)
    return 0;

  *filename = argv[2];
  if (!file_exists(*filename))
    return 0;

  if (!affinity::cores_init(arena, cores, argc - 3))
    return 0;

  for (int i = 3; i < argc; i++)
  {
    int core;
    if (!parse_int(argv[i], &core))
      return 0;
    if (!affinity::cores_add(cores, core))
      return 0;
  }

  return cores->count > 0;
}
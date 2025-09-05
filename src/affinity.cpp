// Copyright (c) 2025 Rudy Alex Kohn
// See end of file for extended copyright information.

#include "affinity.h"
#include <cstdio>
#include <processthreadsapi.h>
#include <windows.h>
#include <winbase.h>

namespace {

constexpr int is_set(const DWORD dw, const int bit) {
  return dw & bit;
}

constexpr DWORD set_bit(const DWORD dw, const int bit) {
  return dw | bit;
}

STARTUPINFO make_startup_info() {
  STARTUPINFO startup_info = {};
  startup_info.cb          = sizeof(STARTUPINFO);
  GetStartupInfo(&startup_info);
  return startup_info;
}

int tell_user_error() {
  const DWORD error = GetLastError();
  if (!error)
    return 0;

  LPVOID msg_buf;
  FormatMessage(
    FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
    nullptr,
    error,
    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
    (LPTSTR)&msg_buf,
    0,
    nullptr);

  OutputDebugString((LPCTSTR)msg_buf);
  printf("%s\n", (LPCTSTR)msg_buf);
  LocalFree(msg_buf);
  return (int)error;
}

}   // namespace

int affinity::cores_init(Arena* arena, Cores* cores, const int capacity) {
  cores->cores = (int*)arena::arena_alloc(arena, capacity * sizeof(int));
  if (!cores->cores)
    return 0;
  cores->count    = 0;
  cores->capacity = capacity;
  return 1;
}

int affinity::cores_add(Cores* cores, const int core) {
  if (cores->count >= cores->capacity)
    return 0;
  cores->cores[cores->count++] = core;
  return 1;
}

int affinity::run_start_affinity(const char* filename, const Cores* cores) {

  DWORD_PTR proc_mask   = 0;
  DWORD_PTR system_mask = 0;
  GetProcessAffinityMask(GetCurrentProcess(), &proc_mask, &system_mask);

  DWORD_PTR procs = 0;

  for (int i = 0; i < cores->count; i++)
  {
    const int b = cores->cores[i];
    if (b && is_set(system_mask, 1 << b))
      procs = set_bit(procs, 1 << b);
    else
      printf("Processor ID: %d is not valid, and will be ignored.\n", b);
  }

  SECURITY_ATTRIBUTES saProcess = {};
  SECURITY_ATTRIBUTES saThread  = {};

  saProcess.nLength              = sizeof(SECURITY_ATTRIBUTES);
  saThread.nLength               = sizeof(SECURITY_ATTRIBUTES);
  saProcess.lpSecurityDescriptor = nullptr;
  saThread.lpSecurityDescriptor  = nullptr;

  STARTUPINFO startupInfo         = make_startup_info();
  PROCESS_INFORMATION processInfo = {};

  if (!CreateProcess(
        nullptr,
        const_cast<char*>(filename),
        &saProcess,
        &saThread,
        TRUE,
        0,
        nullptr,
        nullptr,
        &startupInfo,
        &processInfo))
    return tell_user_error();

  SetProcessAffinityMask(processInfo.hProcess, procs);

  CloseHandle(processInfo.hProcess);
  CloseHandle(processInfo.hThread);
  return 0;
}

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
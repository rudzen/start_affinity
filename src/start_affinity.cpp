/*
 *  StartAffinity 1.4.0 (c) 2020 Rudy Alex Kohn
 *	rudzen@gmail.com
 *
 *  StartAffinity 1.3.1 (c) 2006 Adsci Engineering, LLC
 *	info@adsciengineering.com
 *
 *	This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */


#include <cstdio>
#include <string>
#include <string_view>
#include <numeric>

#include <windows.h>
#include <processthreadsapi.h>

#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>

#include "start_affinity.hpp"
#include "misc.hpp"

namespace
{

constexpr std::string_view processor_id_missing_msg = "Invalid processor id : ";

constexpr auto max_log_file_size = 1048576 * 5;
constexpr auto max_log_files     = 3;

std::shared_ptr<spdlog::logger> logger =
  spdlog::rotating_logger_mt("logger", "start_affinity_log.txt", max_log_file_size, max_log_files);

int tell_user_error()
{
  const auto error = GetLastError();
  if (!error)
    return 0;

  LPVOID msg_buf{};
  FormatMessage(
    FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
    nullptr,
    error,
    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
    reinterpret_cast<LPTSTR>(&msg_buf),
    0,
    nullptr);

  auto msg = std::string(static_cast<LPCTSTR>(msg_buf));

  fmt::print(stderr, msg);

  msg.erase(std::remove(msg.begin(), msg.end(), '\n'), msg.end());

  logger->error(msg);

  LocalFree(msg_buf);

  return error;
}

}   // namespace

int start_affinity::run(const ParserSettings *settings)
{

  if (settings->verify_os && !misc::is_valid_os())
  {
    logger->error("WinNT/2000/XP or newer is required!");
    return -1;
  }

  DWORD_PTR proc_mask{};
  DWORD_PTR system_mask{};

  GetProcessAffinityMask(GetCurrentProcess(), &proc_mask, &system_mask);

  DWORD_PTR procs{};

  for (const auto f : settings->processor_flags)
  {
    const auto b = 1 << f;
    if (misc::is_set(system_mask, b))
      procs = misc::set_bit(procs, b);
    else
    {
      fmt::print("{} {}\n", processor_id_missing_msg, b);
      logger->info("{} {}", processor_id_missing_msg, b);
    }
  }

  // handle the security attributes
  // lpSecurityDescriptor is set to null to force CreateProcess to use default descriptors
  SECURITY_ATTRIBUTES sa_process{
    .nLength = sizeof(SECURITY_ATTRIBUTES), .lpSecurityDescriptor = nullptr, .bInheritHandle = 0};
  SECURITY_ATTRIBUTES sa_thread{
    .nLength = sizeof(SECURITY_ATTRIBUTES), .lpSecurityDescriptor = nullptr, .bInheritHandle = 0};

  STARTUPINFO startup_info{};

  startup_info.cb = sizeof(STARTUPINFO);

  GetStartupInfo(&startup_info);

  PROCESS_INFORMATION process_info{};

  auto *file_name = const_cast<char *>(settings->file_name.c_str());

  if (!CreateProcess(nullptr, file_name, &sa_process, &sa_thread, 1, 0, nullptr, nullptr, &startup_info, &process_info))
    return tell_user_error();

  // set affinity mask
  SetProcessAffinityMask(process_info.hProcess, procs);

  // close handles
  CloseHandle(process_info.hProcess);
  CloseHandle(process_info.hThread);

  const auto accumulator = [](const std::string &a, const int b) {
    return a + ',' + std::to_string(b);
  };

  logger->info(
    "Started {} with affinity : {}",
    settings->file_name,
    std::accumulate(
      std::next(settings->processor_flags.begin(), 1), settings->processor_flags.end(),
      std::to_string(settings->processor_flags.front()), accumulator));

  return 0;
}

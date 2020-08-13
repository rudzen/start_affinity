#pragma once

#include <memory>
#include <string>
#include <vector>

struct ParserSettings final {
  std::string file_name{};
  std::vector<int> processor_flags{};
  bool verify_os{};
};

namespace cli {

std::unique_ptr<ParserSettings> make_parser(int argc, char **argv, const std::string &title);

}
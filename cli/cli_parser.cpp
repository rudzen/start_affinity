#include <CLI/CLI.hpp>
#include "cli_parser.hpp"

namespace
{

constexpr auto default_check_os = false;

constexpr auto min_cpu_val = 0;
constexpr auto max_cpu_val = 31;

} // namespace

struct CliParser final
{
  CliParser(const int argc, char **argv, const std::string &title) : argc_(argc), argv_(argv), app_(title)
  { }

  [[nodiscard]] const ParserSettings &parse();

private:
  int argc_;
  char **argv_;
  CLI::App app_;
  ParserSettings parser_settings_{};
};

const ParserSettings &CliParser::parse()
{

  app_.allow_windows_style_options();

  auto *const file_name = app_.add_option("-f,--file", parser_settings_.file_name, "Executable to launch with set affinity");
  file_name->required();
  file_name->check(CLI::ExistingFile);

  auto *const verify_os = app_.add_option("-c, --check_os", parser_settings_.verify_os);
  verify_os->default_val(&default_check_os);

  auto *const cpu_affinities = app_.add_option("--cpu", parser_settings_.processor_flags, "CPUs");
  
  cpu_affinities->required();
  cpu_affinities->check(CLI::Range(min_cpu_val, max_cpu_val));

  try
  {
    app_.parse(argc_, argv_);
  } catch (const CLI::ParseError &e)
  {
    app_.exit(e);
  }

  return parser_settings_;
}

namespace cli
{

std::unique_ptr<ParserSettings> make_parser(const int argc, char **argv, const std::string &title)
{

  return std::make_unique<ParserSettings>(CliParser(argc, argv, title).parse());
}

}   // namespace cli

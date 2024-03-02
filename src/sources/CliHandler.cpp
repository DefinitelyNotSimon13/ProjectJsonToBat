#include "CliHandler.hpp"
#include "config.hpp"
#include "LoggingWrapper.hpp"

#include <cstdlib>
#include <sstream>

namespace cli {
void CliHandler::printHelp()
{
    LOG_INFO << "Printing help...";
    std::cout << "Usage: " << PROJECT_NAME << " [options] [arguments]\n"
              << cli::BOLD << "Options:\n" << cli::RESET
              << "  -h, --help     Print this help message\n"
              << "  -v, --version  Print version information\n\n"
              << cli::BOLD << "Arguments:\n" << cli::RESET
              << "  <filename(s)>       The filename(s) of the JSON file(s) to process\n\n"
              << "More information can be found at: " << HOMEPAGE_URL << "\n"
              << "Authors: " << cli::ITALIC << AUTHORS << "\n" << cli::RESET
              << "\n" << DESCRIPTION << "\n";
    exit(0);
}
void CliHandler::printVersion()
{
    LOG_INFO << "Printing version...";
    std::stringstream version;
    version << MAJOR_VERSION << "." << MINOR_VERSION << "." << PATCH_VERSION;
    std::cout << PROJECT_NAME << " - Version " << version.str() << "\n";
    std::cout << "-h, --help for more information\n";
    exit(0);
}
}

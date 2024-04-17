#ifndef COMMANDLINEHANDLER_HPP
#define COMMANDLINEHANDLER_HPP

#include <getopt.h>
#include <string>
#include <vector>

/* TODO: Add documentation */
namespace cli {
class CommandLineHandler {
public:
    /* TODO: Add documentation */
    static void printHelp();
    /* TODO: Add documentation */
    static void printVersion();
    /* TODO: Add documentation */
    static void printCredits();
    /* TODO: Add documentation */
    static std::vector<std::string> parseArguments(int argc, char* argv[]);

private:
    /* TODO: Add documentation */
    CommandLineHandler();
    /* TODO: Add documentation */
    ~CommandLineHandler();
};

/* TODO:
 * - Add documentation
 * - Verbose mode (need to edit LogginWrapper)
 * - Print file after completion
 * - Output file location
 */
static const struct option options[] = {
    {"help", no_argument, nullptr, 'h'},
    {"version", no_argument, nullptr, 'V'},
    {"credits", no_argument, nullptr, 'c'},
    nullptr
    // Brief/verbose
    // Output dir
};

#ifdef IS_UNIX // CLI Formatting for Linux
static const std::string CLEAR_TERMINAL = "\033[2J\033[1;1H";
static const std::string RESET = "\033[0m";
static const std::string RED = "\033[0;31m";
static const std::string GREEN = "\033[0;32m";
static const std::string YELLOW = "\033[0;33m";
static const std::string BLUE = "\033[0;34m";
static const std::string MAGENTA = "\033[0;35m";
static const std::string CYAN = "\033[0;36m";
static const std::string WHITE = "\033[0;37m";
static const std::string BOLD = "\033[1m";
static const std::string UNDERLINE = "\033[4m";
static const std::string ITALIC = "\033[3m";
#elif defined(IS_WINDOWS) // Windows doesn't support ANSI escape codes the same way
static const std::string CLEAR_TERMINAL = "";
static const std::string RESET = "";
static const std::string RED = "";
static const std::string GREEN = "";
static const std::string YELLOW = "";
static const std::string BLUE = "";
static const std::string MAGENTA = "";
static const std::string CYAN = "";
static const std::string WHITE = "";
static const std::string BOLD = "";
static const std::string UNDERLINE = "";
static const std::string ITALIC = "";
#endif

} // namespace cli

#endif // COMMANDLINEHANDLER_HPP
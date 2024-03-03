#ifndef CLIHANDLER_HPP
#define CLIHANDLER_HPP

#include <string>
/**
 * \brief cli namespace
 * \details
 * The cli namespace contains all classes and functions related to the command
 * line interface.
 **/
namespace cli {

class CliHandler {
  public:
    /**
     * \brief Prints the help message
     * \details
     * The function prints the help message to the terminal and exits the program.
     **/
    static void printHelp();
    /**
     * \brief Prints the version information
     * \details
     * The function prints the version information to the terminal and exits the
     *program.
     **/
    static void printVersion();
};

#ifdef IS_UNIX
const static std::string CLEAR_TERMINAL = "\x1b[2J";
const static std::string RESET = "\x1b[0m";
const static std::string BOLD = "\x1b[1m";
const static std::string DIM = "\x1b[2m";
const static std::string ITALIC = "\x1b[3m";
const static std::string UNDERLINE = "\x1b[4m";
const static std::string BLINKING = "\x1b[5m";
const static std::string BLACK_FG = "\x1b[30m";
const static std::string RED_FG = "\x1b[31m";
const static std::string GREEN_FG = "\x1b[32m";
const static std::string YELLOW_FG = "\x1b[33m";
const static std::string BLUE_FG = "\x1b[34m";
const static std::string MAGENTA_FG = "\x1b[35m";
const static std::string CYAN_FG = "\x1b[36m";
const static std::string WHITE_FG = "\x1b[37m";
const static std::string RED_BG = "\x1b[41m";
const static std::string GREEN_BG = "\x1b[42m";
const static std::string YELLOW_BG = "\x1b[43m";
const static std::string BLUE_BG = "\x1b[44m";
const static std::string MAGENTA_BG = "\x1b[45m";
const static std::string CYAN_BG = "\x1b[46m";
const static std::string WHITE_BG = "\x1b[47m";
const static std::string ERROR = "\x1b[31m\x1b[1m";
#elif IS_WINDOWS
const static std::string CLEAR_TERMINAL = "";
const static std::string RESET = "";
const static std::string BOLD = "";
const static std::string DIM = "";
const static std::string ITALIC = "";
const static std::string UNDERLINE = "";
const static std::string BLINKING = "";
const static std::string BLACK_FG = "";
const static std::string RED_FG = "";
const static std::string GREEN_FG = "";
const static std::string YELLOW_FG = "";
const static std::string BLUE_FG = "";
const static std::string MAGENTA_FG = "";
const static std::string CYAN_FG = "";
const static std::string WHITE_FG = "";
const static std::string RED_BG = "";
const static std::string GREEN_BG = "";
const static std::string YELLOW_BG = "";
const static std::string BLUE_BG = "";
const static std::string MAGENTA_BG = "";
const static std::string CYAN_BG = "";
const static std::string WHITE_BG = "";
const static std::string ERROR = "";
#endif
} // namespace cli

#endif // CLIHANDLER_HPP

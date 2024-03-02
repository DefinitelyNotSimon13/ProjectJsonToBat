#ifndef STARTUPHANDLER_HPP
#define STARTUPHANDLER_HPP

#include <string>
#include <vector>

namespace utils {
/**
 * \brief Handles the startup of the program
 * \details
 * The class handles the startup of the program by initializing the easylogging++
 * library and parsing the options given to the program.
 **/
class StartupHandler {
  public:
    /**
     * \brief Initializes the easylogging++ library
     * \details
     * The function sets up the easylogging++ library with the default
     * configuration file.
     **/
    static void initEasylogging();
    /**
     * \brief Parses the options given to the program
     * \details
     * The function parses the options given to the program and returns them as a
     * vector of strings.
     *
     * \param argc The number of arguments
     * \param argv The arguments
     *
     * \note
     * If -h/--help or -v/--version is given, the function will not return
     * to main.
     *
     * \return std::vector<std::string> The parsed filenames
     **/
    static std::vector<std::string> parseOptions(int argc, char* argv[]);
};
} // namespace utils

#endif // STARTUPHANDLER_HPP

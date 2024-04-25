/**
 * @file Utils.cpp
 * @author Simon Blum
 * @date 2024-04-18
 * @version 0.1.5
 * @brief Implementation for the Utils class
 * @details
 * This file includes the implementation for the Utils class.
 *
 * @see src/include/utility/Utilities.hpp
 *
 * @copyright See LICENSE file
 */

#include "Utils.hpp"
#include "CommandLineHandler.hpp"
#include "Exceptions.hpp"
#include "config.hpp"

#include <LoggingWrapper.hpp>
#include <filesystem>
#include <fstream>
#include <string>

namespace utilities {
void Utils::setupEasyLogging(const std::string &configFile) {
    el::Configurations conf(configFile);
    el::Loggers::reconfigureAllLoggers(conf);
    LOG_INFO << "Running " << PROJECT_NAME << " v" << MAJOR_VERSION << "."
             << MINOR_VERSION << "." << PATCH_VERSION;
    LOG_INFO << "For more Information checkout " << HOMEPAGE_URL;
    LOG_INFO << "EasyLogging has been setup!";
}
bool Utils::checkIfFileExists(const std::string &fileName) {
    LOG_INFO << "Checking if file \"" << fileName << "\"exists...";
    std::ifstream file(fileName);
    return file.good();
}
bool Utils::checkFileEnding(const std::string_view &fileName) {
    return fileName.size() >= 5 && fileName.ends_with(".json");
}
bool Utils::askToContinue(const std::string &prompt) {
    std::string userInput;
    LOG_INFO << "Asking for user Confirmation to continue...";
    OUTPUT << cli::BOLD << prompt << cli::RESET;

    do {
        std::cin >> userInput;
        std::ranges::transform(userInput, userInput.begin(), ::tolower);

        if (userInput != "y" && userInput != "yes" && userInput != "n" &&
                userInput != "no") {
            LOG_INFO << "Wrong user input!";
            OUTPUT << cli::ITALIC << "Please enter Y/Yes or N/No!\n" << cli::RESET;
            continue;
        }

        break;
    } while (true);

    return userInput == "y" || userInput == "yes";
}
std::string &Utils::checkDirectory(std::string &directory) {
    if (!directory.empty() && directory.back() != '/' &&
            directory.back() != '\\') {
        directory += '/';
    }

    if (!std::filesystem::exists(directory)) {
        throw exceptions::NoSuchDirException(directory);
    }
    return directory;
}
} // namespace utilities
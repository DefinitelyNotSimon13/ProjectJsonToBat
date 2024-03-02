#include "BatchCreator.hpp"
#include "JsonData.hpp"
#include "JsonHandler.hpp"
#include "StartupHandler.hpp"
#include "CliHandler.hpp"

#include <LoggingWrapper.hpp>
#include <filesystem>
#include <jsoncpp/json.h>
#ifdef IS_UNIX
#include <getopt.h>
#elif IS_WINDOWS
#include <xgetopt.h>
#endif

INITIALIZE_EASYLOGGINGPP

/**
  * \brief Main function of the application
  * \details
  * The main function of the application. It parses the command line arguments
  * and creates a JSONHandler object for each file. It then creates a batchCreator
  * object and creates a batch file for each JSONHandler object.
  **/
int main(int argc, char* argv[])
{
    std::cout << cli::CLEAR_TERMINAL;
    // Setup easylogging++
    utils::StartupHandler::initEasylogging();
    LOG_INFO << "Starting application...\n";
    // Parse command line arguments

    // Check if a filename or other options are given
    if (argc < 2) {
        LOG_ERROR << "Usage: " << argv[0] << " <filename>\n";
        OUTPUT << "Exiting application...\n";
        return 1;
    }

    // Parse options and go through all filenames given
    for (const auto &filename : utils::StartupHandler::parseOptions(argc, argv)) {
        if (filename.empty()) {
            LOG_ERROR << "Filename cannot be empty!\n";
            OUTPUT << "Continuing with next file...\n\n";
            continue;
        }

        if (!std::filesystem::exists(filename)) {
            LOG_ERROR << "File: " << filename << " does not exist!\n";
            OUTPUT << "Continuing with next file...\n\n";
            continue;
        }

        OUTPUT << cli::UNDERLINE << "Processing file: " << cli::ITALIC << filename
               << cli::RESET << "\n";
        // Create JSONHandler object
        proJson::JsonHandler jsonHandler(filename);
        // Retrieve Data from JSONHandler object
        std::shared_ptr<proJson::JsonData> jsonData = jsonHandler.getJSONData();
        const std::string outputfile = jsonData->getOutputFile();
        OUTPUT << "- Creating Outputfile: " << cli::ITALIC << outputfile
               << cli::RESET << "\n";
        // Create batch file
        batch::BatchCreator batchCreator(jsonData);
        std::shared_ptr<std::ofstream> batchFile = batchCreator.createBatchFile();
        // Get path of batch file for output
        std::filesystem::path path = std::filesystem::current_path();
        OUTPUT << "- Batch file created at: " << cli::ITALIC << path.string() << "/"
               << outputfile << cli::RESET << "\n\n";
        batchFile->close();
    }

    OUTPUT << cli::GREEN_FG << "Done! Exiting application...\n" << cli::RESET;
    return 0;
}

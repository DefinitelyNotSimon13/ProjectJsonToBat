#include "StartupHandler.hpp"
#include "CliHandler.hpp"
#include "LoggingWrapper.hpp"

#include <easylogging++.h>
#include <getopt.h>

namespace utils {
void StartupHandler::initEasylogging()
{
    el::Configurations conf("conf/easylogging.conf");
    el::Loggers::reconfigureAllLoggers(conf);
}
std::vector<std::string> StartupHandler::parseOptions(int argc, char* argv[])
{
    LOG_INFO << "Parsing options...\n";
    int* verbose = nullptr;
    static const struct option long_options[] = { //NOSONAR
        {"verbose", no_argument, verbose, 1},
        {"brief", no_argument, verbose, 0},
        {"help", no_argument, nullptr, 'h'},
        {"version", no_argument, nullptr, 'v'},
        {"test", required_argument, nullptr, 0},
        nullptr
    };

    do {
        int optIndex = -1;
        std::unique_ptr<struct option> opt = nullptr;
        auto result = getopt_long(argc, argv, "hv", long_options, &optIndex);

        if (result == -1) {
            break;
        }

        switch (result) {
            case '?':
                LOG_ERROR << "Unknown option given\n";
                break;

            case 'h':
                LOG_INFO << "Help option given\n";
                cli::CliHandler::printHelp();
                break;

            case 'v':
                LOG_INFO << "Version option given\n";
                cli::CliHandler::printVersion();
                std::cout << "long V\n";

            case 0:
                LOG_INFO << "Option without short version given...\n";
                opt = std::make_unique<struct option>(long_options[optIndex]);
                LOG_INFO << "Option " << opt->name << " given\n";

                if (opt->has_arg == required_argument) {
                    LOG_INFO << "Argument: " << optarg << "\n";
                }

                break;

            default:
                LOG_ERROR << "Default case reached\n";
                break;
        }
    } while (true);

    LOG_INFO << "Parsing options done\n";
    LOG_INFO << "Setting verbose flag...\n";
    LOG_INFO << "Parsing other arguments ...\n";
    std::vector<std::string> files;

    while (optind < argc) {
        LOG_INFO << "File added: " << argv[optind] << "\n";
        files.emplace_back(argv[optind++]);
    }

    return files;
}
} // namespace utils

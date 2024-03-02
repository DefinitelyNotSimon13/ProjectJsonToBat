
#include "BatchCreator.hpp"
#include "LoggingWrapper.hpp"

#include <fstream>
#include <memory>
#include <sstream>
#include <utility>

namespace batch {

BatchCreator::BatchCreator(std::shared_ptr<proJson::JsonData> jsonData)
    : jsonData(std::move(jsonData))
{
    LOG_INFO << "Initializing BatchCreator...\n";
}

std::shared_ptr<std::ofstream> BatchCreator::createBatchFile()
{
    LOG_INFO << "Creating batch file...\n";
    this->batchFile = std::make_shared<std::ofstream>();
    this->batchFile->open(this->jsonData->getOutputFile());

    if (this->jsonData->getHideShell()) {
        this->writeHideShellStart();
    }

    this->writeShell();
    this->writeCommands();
    this->writeEnvironmentVariables();
    this->writePathValue();
    this->writeApplication();

    if (this->jsonData->getHideShell()) {
        this->writeHideShellEnd();
    }

    LOG_INFO << "Batch file created! Returning it...\n";
    return this->batchFile;
}

void BatchCreator::writeHideShellStart()
{
    LOG_INFO << "Writing hide shell start...\n";
    *this->batchFile << "@ECHO OFF\n";
}

void BatchCreator::writeHideShellEnd()
{
    LOG_INFO << "Writing hide shell end...\n";
    *this->batchFile << "@ECHO ON\n";
}

/// \bug Currently always opens new shell
void BatchCreator::writeShell()
{
    if (this->jsonData->getHideShell()) {
        LOG_INFO << "Writing closing shell after finish...\n";
        *this->batchFile << R"(START C:\Windows\System32\cmd.exe /C ")";
        return;
    }

    LOG_INFO << "Writing keeping shell open after finish...\n";
    *this->batchFile << R"(START C:\Windows\System32\cmd.exe /K ")";
}

void BatchCreator::writeCommands()
{
    for (const auto &command : this->jsonData->getCommands()) {
        LOG_INFO << "Writing command: " << command << "\n";
        *this->batchFile << "CALL " << command << " && ^\n";
    }
}

void BatchCreator::writeEnvironmentVariables()
{
    for (const auto &envVar : this->jsonData->getEnvironmentVariables()) {
        LOG_INFO << "Writing environment variable: " << std::get<0>(envVar) << "="
                 << std::get<1>(envVar) << "\n";
        *this->batchFile << "SET " << std::get<0>(envVar) << "="
                         << std::get<1>(envVar) << " && ^\n";
    }
}

void BatchCreator::writePathValue()
{
    std::stringstream additionalPaths;

    for (const auto &pathValue : this->jsonData->getPathValues()) {
        LOG_INFO << "Writing additional path value: " << pathValue << "\n";
        additionalPaths << pathValue << ";";
    }

    LOG_INFO << "Adding additional paths: " << additionalPaths.str() << "\n";
    *this->batchFile << "SET PATH=" << additionalPaths.str() << "%PATH%";
}

void BatchCreator::writeApplication()
{
    if (!this->jsonData->getApplication().has_value()) {
        LOG_INFO << "No application provided, writing to close shell...\n";
        *this->batchFile << "\"\r\n";
        return;
    }

    LOG_INFO << "Writing application: "
             << this->jsonData->getApplication().value() << "\n";
    *this->batchFile << " && ^\n"
                     << this->jsonData->getApplication().value() << "\"\r\n";
}
} // namespace batch

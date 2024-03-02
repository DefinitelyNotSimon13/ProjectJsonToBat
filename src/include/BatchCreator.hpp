#ifndef BATCHCREATOR_HPP
#define BATCHCREATOR_HPP

#include "JsonData.hpp"

#include <fstream>
#include <memory>

/**
 * \brief The batch namespace
 * \details
 * The batch namespace contains all classes and functions related to the batch
 * file creation.
 **/
namespace batch {
/**
 * \brief The BatchCreator class
 * \details
 * The class is used to create a batch file from the given json data.
 **/
class BatchCreator {
  public:
    /**
     * \brief Constructor
     * \details
     * The constructor takes a shared pointer to the json data and assigns it to
     * the corresponding member variable.
     * \param jsonData The json data
     **/
    explicit BatchCreator(std::shared_ptr<proJson::JsonData> jsonData);

    /**
     * \brief Creates the batch file
     * \details
     * The function creates the batch file and calls the functions to write the
     * necessary data to it.
     *
     *\return std::shared_ptr<std::ofstream> The batch file
     **/
    std::shared_ptr<std::ofstream> createBatchFile();

  private:
    std::shared_ptr<proJson::JsonData> jsonData;
    std::shared_ptr<std::ofstream> batchFile = nullptr;

    /**
     * \brief Writes the hide shell start to the batch file
     **/
    void writeHideShellStart();

    /**
     * \brief Writes the hide shell end to the batch file
     **/
    void writeHideShellEnd();

    /**
     * \brief Writes the shell to the batch file
     **/
    void writeShell();

    /**
     * \brief Writes the commands to the batch file
     **/
    void writeCommands();

    /**
     * \brief Writes the environment variables to the batch file
     **/
    void writeEnvironmentVariables();

    /**
     * \brief Writes the path values to the batch file
     **/
    void writePathValue();

    /**
     * \brief Writes the application to the batch file
     **/
    void writeApplication();
};
} // namespace batch

#endif // BATCHCREATOR_HPP

/**
 * @file JsonHandler.hpp
 * @author Sonia Sinacci, Elena Schwartzbach
 * @date 23.04.2024
 * @version 0.1.5
 * @brief This file contains the JsonHandler class
 *
 * @see parsing::JsonHandler
 *
 * @see src/sources/JsonHandler.cpp
 *
 * @copyright See LICENSE file
 */

#ifndef JSONHANDLER_HPP
#define JSONHANDLER_HPP

#include "FileData.hpp"
#include "LoggingWrapper.hpp"
#include <jsoncpp/json.h>

#include <memory>

/**
 * @namespace parsing
 * @brief The namespace containing everything relevant to parsing
 * @details
 * This namespace contains all relevant classes to parsing the json file
 * and creating the batch output.
 *
 * @see JsonHandler
 * @see FileData
 * @see KeyValidator
 * @see BatchCreator
 */
namespace parsing {

/**
 * @class JsonHandler
 * @brief This file reads all data from the json file.
 * @details
 * This file uses the jsoncpp library to parse all data from a json
 * file, validate it to some degree.
 *
 * @see https://github.com/open-source-parsers/jsoncpp
 */
class JsonHandler {
public:
    /**
     * @brief Constructor without arguments
     * @details
     * This constructor can be used to initialise an instance in an outer scope
     * and then assign it values from an inner scope.
     */
    JsonHandler() {
        LOG_INFO << "Initialising empty JsonHandler";
    }
    /**
     * @brief The constructor
     * @details
     * This constructor calls this->parseFile() when called.
     *
     * @param filename Name of the json file
     */
    explicit JsonHandler(const std::string &filename);
    /**
     * @brief Retrieve the data from the json file
     * @details
     * This method calls this->createFileData() needed to retrieve the values from
     * the Json::Value this->root and then returns a shared pointer to the
     * created FileData object.
     *
     * @return Pointer to the FileData Object with the parsed data from json
     */
    std::shared_ptr<FileData> getFileData();

private:
    /**
     * @brief Parses the given json file
     * @details
     * This method first creates a new Json::Value instance and then tries to
     * parse the given json file.
     * It then validates the keys of the instance using the KeyValidator class.
     *
     * @param filename The name of the file wich should be parsed
     * @return A shared pointer to the Json::Value instance
     *
     * @see KeyValidator::validateKeys()
     *
     * @throw exceptions::ParsingException
     * @throw exceptions::InvalidKeyException
     */
    [[nodiscard]] static std::shared_ptr<Json::Value>
    parseFile(const std::string &filename);
    /**
     * @brief Assigns the outputfile to this->data
     * @details
     * Retrieves the outputfile from Json::Value this->root and makes sure, that
     * the file doesn't already exist.
     *
     * @throw exceptions::FileExistsException
     */
    void assignOutputFile() const;
    /**
     * @brief Assigns the hideshell value to this->data
     * @details
     * Retrieves the value of the hideshell key from Json::Value this->root and
     * defaults to negative.
     */
    void assignHideShell() const;
    /**
     * @brief Assigns application to this->data
     * @details
     * Retrieves the value of the application key from Json::Value this->root and
     * defaults to an empty string.
     */
    void assignApplication() const;
    /**
     * @brief Assigns entries to this->data
     * @details
     * Goes through each of the entries from Json::Value this->root and
     * calls the relevant method depending on it's type.
     * All "type" keys should be valid by this point.
     *
     * @param entry Json::Value containing an array with entries
     *
     * @throw exceptions::UnreachableCodeException
     */
    void assignEntries() const;
    /**
     * @brief Assigns an command to this->data
     * @param entry The entry with the command
     */
    void assignCommand(const Json::Value &entry) const;
    /**
     * @brief Assigns an environmentVariable to this->data
     * @param entry The entry with the environmentVariable
     */
    void assignEnvironmentVariable(const Json::Value &entry) const;
    /**
     * @brief Assigns a path value to this->data
     * @param entry The entry with the path value
     */
    void assignPathValue(const Json::Value &entry) const;
    /**
     * @brief Creates the FileData instance
     * @details
     * Instantiates the FileData instance, calls all nessecary functions and
     * returns a shared pointer to it.
     *
     * @return Pointer to the created instance of FileData
     */
    std::shared_ptr<FileData> createFileData();
    std::shared_ptr<Json::Value> root;
    std::shared_ptr<FileData> data;
};
} // namespace parsing

#endif // JSONHANDLER_HPP

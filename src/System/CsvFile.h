#ifndef _DATA_LOGGER_H_
#define _DATA_LOGGER_H_

#include "Arduino.h"
#include "SD.h"

using namespace std;

/**
 * @brief Class to read and log data to a file on an SD Card in the CSV format. 
*/
class CsvFile {
    public:

        /**
         * @brief Creates a new CSV file with a given number of columns with the specified name and loads it.
         * - If file does not exist, create a new file.
         * - If file already exists, create a new file with a different name.
         * 
         * @param name File name
         * @param numColumns Number of columns of csv file
         * @param mode File operation mode (FILE_READ, FILE_WRITE etc)
         * @return True on success, false otherwise.
        */
        bool create(String name, int numColumns, int mode = FILE_WRITE);

        /**
         * @brief Load a CSV file with the specified name. 
         * - If file does not exist, create a new file.
         * - If file exists and has the correct number of columns specified, open file for appending.
         * - If file exists and has a different number of columns, create new file with a different name.
         * 
         * @param name File name
         * @param numColumns Number of columns of csv file
         * @param mode File operation mode (FILE_READ, FILE_WRITE etc)
         * @return True on success, false otherwise.
        */
        bool open(String name, int numColumns, int mode = FILE_WRITE);

        /**
         * @brief saves any csv data for current file to disk.
         * @return True on success, false otherwise.
         * @note this has a performance penalty, so only call when you absolutely need file to be on disk
        */
        bool saveToDisk();

        /**
         * @brief Close currently loaded file.
         * @return True on success, false otherwise.
         * @note make sure to call saveToDisk before closing
        */
        bool close();

        /**
         * @brief Writes header provided by String header to a blank CSV file.
         * @param header Header string
        */
        void setHeader(String header);

        /**
         * @brief Writes entry provided by String data to the loaded CSV file. If its the last entry of the row, start a new line.
         * @param data Single entry encoded as a string
        */
        void addEntry(String data);

        /**
         * @brief Writes row provided by String data to the loaded CSV file.
         * @param data Comma separated elements of a row encoded as a string
        */
        void addRow(String data);

        /**
         * @brief Returns number of columns in the currently loaded CSV file.
        */
        int getNumColumns();

        /**
         * @brief Returns current size of file
        */
        int getFileSize();

        /**
         * @brief Returns name of currently open file, or an empty string if no file is open.
        */
        String getFileName();

        /**
         * @brief Reads row of entries and returns as vector of string
         * @returns Vector of all entries in row
         * @return empty vector if end of file reached, or if CsvFile::_currentColumn != 0
        */
        std::vector<String> readRow();

        /**
         * @brief Read single string entry from row
         * @returns String with next entry in column CsvFile::_currentColumn
         * @return Empty string if end of file is reached
        */
        String readEntry();

    private:
        int _numColumns = 0;
        int _curColumn = 0; // current column
        String _fileName = "";
        File _curFile; // current file

        // determine how many columns are in the CSV file based on the header row
        int _computeNumColumns();
        // move file cursor to the next line
        void _seekNextLine();
        // check if we have reached the end of file in our currently open file
        bool _eofReached();
        // check if a character is legal for CSV entries
        inline bool _isValidEntry(char c);
};

#endif
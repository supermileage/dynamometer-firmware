#ifndef _DATA_LOGGER_H_
#define _DATA_LOGGER_H_

#include "Arduino.h"
#include "SD.h"

using namespace std;

//Class to log data to a file on an SD Card in the CSV format.
class CsvFile {
    public:

        /**
         * @brief Constructs a CsvFile object.
        */
        CsvFile(bool osync = false);

        ~CsvFile();

        /**
         * @brief Creates a new CSV file with a given number of columns with the specified name and loads it.
         * - If file does not exist, create a new file.
         * - If file already exists, create a new file with a different name.
         * @return True on success, false otherwise.
        */
        bool create(String name, int numColumns);

        /**
         * @brief Allows a user to load a CSV file located with the specified name. 
         * - If file does not exist, create a new file.
         * - If file exists and has the correct number of columns specified, open file for appending.
         * - If file exists and has a different number of columns, create new file with a different name.
         * @return True on success, false otherwise.
        */
        bool open(String name, int numColumns, int mode = FILE_WRITE);

        /**
         * @brief Saves any csv data for current file to disk.
         * @return True on success, false otherwise.
        */
        bool saveToDisk();

        /**
         * @brief Close currently loaded file.
         * @return True on success, false otherwise.
        */
        bool close();

        /**
         * @brief Writes header provided by String header to a blank CSV file.
        */
        void setHeader(String header);

        /**
         * @brief Writes entry provided by String data to the loaded CSV file. If its the last entry of the row, start a new line.
        */
        void addEntry(String data);

        /**
         * @brief Writes row provided by String data to the loaded CSV file.
        */
        void addRow(String data);

        /**
         * @brief Returns number of columns in the currently loaded CSV file.
        */
        int getNumColumns();

        /**
         * @brief Returns number of bytes in buffer.
        */
        int getBufferLength();

        /**
         * @brief Returns name of currently open file, or an empty string if no file is open.
        */
        String getFileName();

        /**
         * @brief reads row of entries and returns as vector of string
         * @returns vector of all entries in row
         * @note returns empty vector if end of file reached, or if CsvFile::_currentColumn != 0
        */
        std::vector<String> readRow();

        /**
         * @brief read single string entry from row
         * @returns string with next entry in column CsvFile::_currentColumn
         * @note returns empty string if end of file is reached
        */
        String readEntry();

        private:
        int _numColumns;
        int _curColumn;
        File _curFile;
        String _buffer;
        String _fileName;
        
        bool _osync;

        String _generateNewFileName(String name);
        int _computeNumColumns();
        void _seekNextLine();
        bool _eofReached();
};

#endif
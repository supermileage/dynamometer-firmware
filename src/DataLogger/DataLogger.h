#ifndef _DATA_LOGGER_H_
#define _DATA_LOGGER_H_

#include "Arduino.h"
#include "SD.h"

using namespace std;

//Class to log data to a file on an SD Card in the CSV format.
class DataLogger {
    public:

        /**
         * @brief Constructs a DataLogger object and begins access to the SDcard.
        */
        DataLogger(int pinNumber, bool osync = false);

        ~DataLogger();

        /**
         * @brief Creates a new CSV file with a given number of columns with the specified name and loads it. 
         * @return True on success, false otherwise.
        */
        bool create(String name, int numColumns);

        /**
         * @brief Allows a user to load a CSV file located with the specified name.
         * @return True on success, false otherwise.
        */
        bool open(String name, int numColumns);

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

        private:
        int _numColumns;
        int _curColumn;
        File _curFile;
        bool _fileValid;
        String _buffer;

        bool _osync;
};

#endif
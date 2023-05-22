#ifndef _DATA_LOGGER_H_
#define _DATA_LOGGER_H_

#include "Arduino.h"
#include "SPI.h"
#include <SD.h>
using namespace std;

//Class to log data to a file on an SD Card in the CSV format.
class DataLogger {
    public:

        //Constructs a DataLogger object and begins access to the SDcard.
        DataLogger(int pinNumber, bool O_SYNC_FLAG = false);

        ~DataLogger();

        //Creates a new CSV file with a given number of columns with the specified name and loads it.
        //Returns true on success, false otherwise.
        bool create(String name, int numColumns);

        //Allows a user to load a CSV file located with the specified name.
        //Returns true on success, false otherwise.
        bool open(String name, int numColumns);

        //Saves any csv data for current file to disk.
        bool saveToDisk();

        //Close currently loaded file.
        //Returns true on success, false otherwise.
        bool close();

        //Writes header provided by String header to a blank CSV file.
        void setHeader(String header);

        //Writes entry provided by String data to the loaded CSV file.
        //If its the last entry of the row, start a new line.
        void addEntry(String data);

        //Writes row provided by String data to the loaded CSV file.
        void addRow(String data);

        //Returns number of columns in the currently loaded CSV file.
        int getNumColumns();

        //Returns number of bytes in buffer.
        int getBufferLength();

        private:
        int _numColumns;
        int _curColumn;
        File* _curFilePtr;
        String _buffer;

        bool _O_SYNC;
};

#endif
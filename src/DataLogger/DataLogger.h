#ifndef _DATA_LOGGER_H_
#define _DATA_LOGGER_H_

#include "Arduino.h"
#include "SPI.h"
#include <SD.h>
#include <vector>
using namespace std;

//Class to log data to a file on an SD Card in the CSV format.
class DataLogger {
    public:

        //Constructs a DataLogger object and begins access to the SDcard.
        DataLogger(int pinNumber);

        ~DataLogger();

        //Creates a new CSV file with a given number of columns with the specified name and loads it.
        //Returns true on success, false otherwise.
        bool create(String name, int numColumns);

        //Allows a user to load a CSV file located with the specified name.
        //Returns true on success, false otherwise.
        bool open(String name);

        //Writes the provided vector of float values to the loaded CSV file as a new row.
        //The provided vector must be the same length as getNumColumns().
        //Each element of the vector will be a distinct column value in the CSV file.
        //Returns true on success, false otherwise.
        bool writeToLog(vector<float> values);

        //Close currently loaded file.
        //Returns true on success, false otherwise.
        bool close();

        //Writes header provided by String header to a blank CSV file.
        void setHeader(String header);

        //Writes row provided by String data the loaded CSV file.
        void addRow(String data);

        //Returns number of columns in the currently loaded CSV file.
        int getNumColumns();

        private:
        int _numColumns;
        File _curFile;
};

#endif
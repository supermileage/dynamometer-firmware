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

        //Creates a new CSV file at the with a given header at the specified path and loads it.
        //Each element of the vector will be a distinct column header in the CSV file.
        //Returns true on success, false otherwise.
        bool createCSV(String path, vector<String> header);

        //Allows a user to load a CSV file located at the specified path.
        //Returns true on success, false otherwise.
        bool loadCSV(String path);

        //Writes the provided vector of float values to the loaded CSV file as a new row.
        //The provided vector must be the same length as getNumColumns().
        //Each element of the vector will be a distinct column value in the CSV file.
        //Returns true on success, false otherwise.
        bool writeToLog(vector<float> values);

        //Close currently loaded file.
        //Returns true on success, false otherwise.
        bool close();

        //Returns number of columns in the currently loaded CSV file.
        int getNumColumns();

        private:
        int _numColumns;
        File _curFile;

        //Writes header provided by String vector to a blank CSV file.
        void setHeader(vector<String> header);

        //Writes header provided by float vector the loaded CSV file.
        void writeRow(vector<float> values);
};

#endif
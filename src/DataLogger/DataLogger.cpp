#include "settings.h"
#include "DataLogger.h"
#include <SD.h>
#include <iostream>
using namespace std;

//public methods:

DataLogger::DataLogger(int pinNumber, bool osync /*= false*/) {
    if (SD.begin(pinNumber, SPI1)) {
        DEBUG_SERIAL_LN("SD card is present & ready");
    } else {
        DEBUG_SERIAL_LN("SD card missing or failed");
    }

    _osync = osync;
}

DataLogger::~DataLogger(){};

bool DataLogger::create(String name, int numColumns) {
    // if file is already open, close that file
    if(_fileValid == true) {
        _curFile.close();
        _fileValid = false;
    }

    _curFile = SD.open(name, FILE_WRITE);
    _numColumns = numColumns;
    _curColumn = 0;
    _buffer = "";
    
    if (_curFile) {
        _fileValid = true;
        DEBUG_SERIAL_LN("Creating file successful");
        return true;
    } else {
        _fileValid = false;
        DEBUG_SERIAL_LN("Creating file failed.");
        return false;
    }
}

bool DataLogger::open(String name, int numColumns) {
    // if file is already open, close that file
    if(_fileValid == true) {
        _curFile.close();
        _fileValid = false;
    }

    _curColumn = 0;
    _buffer = "";

    // check if file exists
    if (SD.exists(name)) {
        // file already exists
        // open the file and see how many columns are in the csv file

        DEBUG_SERIAL_LN("Loading " + name);

        File _curFile = SD.open(name, FILE_WRITE | FILE_READ);
        
        // check if file opened successfully
        if (_curFile) {
            _fileValid = true;
            DEBUG_SERIAL_LN("Creating file successful");
            // continue with function
        } else {
            _fileValid = false;
            DEBUG_SERIAL_LN("Creating file failed.");
            return false;
        }

        // some variables to help identify how many columns in the first line
        int commaNum = 0;
        bool charactersPresent = false;
        bool escaped = false;

        int columnsInFile = 0;

        while (_curFile.available()) {
            char readChar = _curFile.read(); // char to hold a character that has been read

            if (readChar == ',') {
                commaNum++;
            } else if (readChar == '\n' || readChar == '\r') {
                escaped = true;
                break;
            } else {
                charactersPresent = true;
            }
        }

        // determine the number of columns
        if (commaNum > 0) {
            columnsInFile = commaNum + 1;
        } else if (charactersPresent) {
            columnsInFile = 1;
        } else {
            columnsInFile = 0;
        }

        DEBUG_SERIAL_LN("Counted " + (String)columnsInFile + " columns and reached end of row.");

        // check if the number of columns in the file match the number of columns specified
        if (columnsInFile == numColumns) {
            // file is good
            _numColumns = numColumns;
            return true;
        }
        // check if it is an empty file
        else if (_numColumns == 0 && escaped == false) {
            // file is empty
            _numColumns = numColumns;
            return true;
        } else {
            // file is not empty, and does not have the correct number of columns
            DEBUG_SERIAL_LN("Incorrect column number in file: " + name + ". Creating file with new name.");
            _curFile.close();
            _fileValid = false;
            
            // create new name for file

            // find extension (example: myFile.csv)
            int extensionIndex = name.lastIndexOf('.');
            String base = name.substring(0, extensionIndex == -1 ? name.length() : extensionIndex);
            String extension = extensionIndex == -1 ? "" : name.substring(extensionIndex + 1);
            base.trim();

            // find current file count (example: myFile(2).csv)
            int fileCountStart = base.lastIndexOf('(');
            int fileCountEnd = base.lastIndexOf(')');
            int count = 0;
            if (fileCountStart != -1 && fileCountEnd != -1 && fileCountEnd == base.length() - 1) {
                String countString = base.substring(fileCountStart + 1, fileCountEnd);
                bool numeric = true;
                
                // checks if all characters in countString are numeric
                for (size_t i = 0; i < countString.length(); i++) {
                    if (!isdigit(countString.charAt(i))) {
                        numeric = false;
                        break;
                    }
                }

                if (numeric) {
                    count = countString.toInt();
                    // take count out of file name
                    base = base.substring(0, fileCountStart);
                    base.trim();
                }
            }
            String newFileName = base + "(" + (count + 1) + ")" + (extension != "" ? "." + extension : "");
            return open(newFileName, numColumns);
        }
    } else {
        // file doesnt exist. create new file

        DEBUG_SERIAL_LN(name + " doesn't exist. Creating new file");
        return create(name, numColumns);
    }
}

bool DataLogger::saveToDisk() {
    if (_fileValid) {
        _curFile.print(_buffer);
        _buffer = "";
        DEBUG_SERIAL_LN("Write to file successful.");
        return true;
    } else {
        DEBUG_SERIAL_LN("Write to file failed.");
        return false;
    }
}

bool DataLogger::close() {
    if (_fileValid) {
        _curFile.close();
        _fileValid = false;

        DEBUG_SERIAL_LN("Closed loaded file.");
        return true;
    } else {
        DEBUG_SERIAL_LN("Failed to close loaded file.");
        return false;
    }
}

void DataLogger::setHeader(String header) {
    _buffer += header + "\r\n";
    DEBUG_SERIAL_LN("Added header " + header + " to buffer.");

    if (_osync)
        saveToDisk();
}

void DataLogger::addEntry(String data) {
    if (_curColumn == 0)
        _buffer += data;
    else
        _buffer += "," + data;

    _curColumn++;

    // check if we reached end of row
    if (_curColumn == _numColumns) {
        _buffer += "\r\n";
        _curColumn = 0;
    }

    DEBUG_SERIAL_LN("Added " + data + " to buffer.");
    _curColumn = 0;

    if (_osync)
        saveToDisk();
}

void DataLogger::addRow(String data) {
    _buffer += data + "\r\n";
    _curColumn = 0;
    DEBUG_SERIAL_LN("Added " + data + " to buffer.");

    if (_osync)
        saveToDisk();
}

int DataLogger::getNumColumns() {
    return _numColumns;
}

int DataLogger::getBufferLength() {
    return _buffer.length();
}
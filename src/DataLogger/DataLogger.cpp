#include "settings.h"
#include "DataLogger.h"
#include <SD.h>
#include <iostream>
#include <vector>
using namespace std;

//public methods:

DataLogger::DataLogger(int pinNumber)
{
    if (SD.begin(pinNumber, SPI1))
    {
        DEBUG_SERIAL_LN("SD card is present & ready");
    }
    else
    {
        DEBUG_SERIAL_LN("SD card missing or failed");
        while (1); // wait here forever
    }
}

DataLogger::~DataLogger(){};

bool DataLogger::createCSV(String path, vector<String> header)
{
    _curFile = SD.open(path, FILE_WRITE);
    _numColumns = sizeof(header);
    
    if (_curFile)
    {
        DEBUG_SERIAL_LN("Writing header to file.");
        setHeader(header);
        return true;
    }
    else
    {
        DEBUG_SERIAL_LN("Creating file failed.");
        return false;
    }
}

bool DataLogger::loadCSV(String path)
{
    int i = 0;
    File tempFile;

    if (!SD.exists(path))
    {
        DEBUG_SERIAL_LN(path + " doesn't exist.");
        return false;
    }

    DEBUG_SERIAL_LN("Loading " + path);
    tempFile = SD.open(path);

    while (tempFile.available())
    {
        char readChar = tempFile.read(); // char to hold a character that has been read

        if (readChar == ',')
        {
            i++;
            DEBUG_SERIAL_LN("Counted " + (String) i + " columns.");
        }

        if (readChar == '\n')
        {
            i++;
            _curFile = tempFile;
            _numColumns = i;
            DEBUG_SERIAL_LN("Counted " + (String) i + " columns and reached end of row.");
            return true; // reached the end of a row, so stop counting columns and return true
        }
    }

    _curFile = tempFile;
    _numColumns = i;
    DEBUG_SERIAL_LN("Counted no " + (String) i + " columns. Blank file.");
    return true; // if while loop is never entered, there are no bytes in the file. Loading succeeds but file is blank
}

bool DataLogger::writeToLog(vector<float> values)
{
    if (_curFile && _numColumns == sizeof(values))
    {
        DEBUG_SERIAL_LN("Writing " + (String) sizeof(values) + " to log.");
        writeRow(values);
        return true;
    }
    else
    {
        DEBUG_SERIAL_LN("Failed to write to log.");
        return false;
    }
}

bool DataLogger::close()
{
    if (_curFile)
    {
        _curFile.close();
        DEBUG_SERIAL_LN("Closed loaded file.");
        return true;
    }
    else
    {
        DEBUG_SERIAL_LN("Failed to close loaded file.");
        return false;
    }
}

int DataLogger::getNumColumns()
{
    return _numColumns;
}

//private methods:

void DataLogger::setHeader(vector<String> header)
{
    String formattedHeader = "";
    int n = 0;

    for (String colName : header)
    {
        if (n = 0)
        {
            formattedHeader + colName;
        }
        else
        {
            formattedHeader + "," + colName;
        }
        n++;
    }

    DEBUG_SERIAL_LN("Header is: " + formattedHeader);
    _curFile.println(formattedHeader);
    DEBUG_SERIAL_LN("Wrote header to file.");
}

void DataLogger::writeRow(vector<float> values)
{
    String formattedRow = "";
    int n = 0;

    for (float value : values)
    {
        if (n = 0)
        {
            formattedRow + value;
        }
        else
        {
            formattedRow + "," + value;
        }
        n++;
    }

    _curFile.println(formattedRow);
    DEBUG_SERIAL_LN("Wrote " + formattedRow + " to log.");
}

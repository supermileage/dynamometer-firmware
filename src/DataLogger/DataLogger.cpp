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

bool DataLogger::create(String name, int numColumns)
{
    _curFile = SD.open(name, FILE_WRITE);
    _numColumns = numColumns;
    
    if (_curFile)
    {
        DEBUG_SERIAL_LN("Creating file successful");
        return true;
    }
    else
    {
        DEBUG_SERIAL_LN("Creating file failed.");
        return false;
    }
}

bool DataLogger::open(String name)
{
    int i = 0;
    File tempFile;

    if (!SD.exists(name))
    {
        DEBUG_SERIAL_LN(name + " doesn't exist.");
        return false;
    }

    DEBUG_SERIAL_LN("Loading " + name);
    tempFile = SD.open(name);

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

void DataLogger::setHeader(String header)
{
    DEBUG_SERIAL_LN("Header is: " + header);
    _curFile.println(header);
    DEBUG_SERIAL_LN("Wrote header to file.");
}

void DataLogger::addRow(String data)
{
    _curFile.println(data);
    DEBUG_SERIAL_LN("Wrote " + data + " to log.");
}

int DataLogger::getNumColumns()
{
    return _numColumns;
}



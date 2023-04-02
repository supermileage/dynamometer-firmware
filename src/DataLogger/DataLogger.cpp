#include "settings.h"
#include "DataLogger.h"
#include <SD.h>
#include <iostream>
#include <vector>
using namespace std;

//public methods:

DataLogger::DataLogger(int pinNumber, bool O_SYNC = false)
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

    _O_SYNC = O_SYNC;
}

DataLogger::~DataLogger(){};

bool DataLogger::create(String name, int numColumns)
{
    _curFile = SD.open(name, FILE_WRITE);
    _numColumns = numColumns;
    _curColumn = 0;
    _buffer = "";
    
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
    _curColumn = 0;
    _buffer = "";

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

bool DataLogger::saveToDisk() {
    if (_curFile)
    {
        _curFile.print(_buffer);
        _buffer = "";
        DEBUG_SERIAL_LN("Write to file successful.");
        return true;
    }
    else
    {
        DEBUG_SERIAL_LN("Write to file failed.");
        return false;
    }
}

bool DataLogger::close()
{
    if (_curFile)
    {
        _curFile.close();
        _curFile = null; // sets _curFile to null so saveToDisk() doesnt try writing to a closed file
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
    _buffer += header + "\r\n";
    DEBUG_SERIAL_LN("Added header " + header + " to buffer.");

    if (_O_SYNC)
        saveToDisk();
}

void DataLogger::addEntry(String data)
{
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

    if (_O_SYNC)
        saveToDisk();
}

void DataLogger::addRow(String data)
{
    _buffer += data + "\r\n";
    _curColumn = 0;
    DEBUG_SERIAL_LN("Added " + data + " to buffer.");

    if (_O_SYNC)
        saveToDisk();
}

int DataLogger::getNumColumns()
{
    return _numColumns;
}

int DataLogger::getBufferLength() 
{
    return _buffer.length();
}
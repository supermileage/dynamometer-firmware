#include "settings.h"
#include "DataLogger.h"
#include <SD.h>
#include <iostream>
#include <vector>
using namespace std;

DataLogger::DataLogger(int pinNumber)
{
    SD.begin(pinNumber, SPI1);
};

DataLogger::~DataLogger(){};

bool DataLogger::createCSV(String path, vector<String> header)
{
    _curFile = SD.open(path, FILE_WRITE);
    _numColumns = sizeof(header);

    if (_curFile)
    {
        setHeader(header);
        return true;
    }
    else
    {
        return false;
    }
}

bool DataLogger::loadCSV(String path)
{
    // TODO: add logic to update _numColumns once new file is loaded.
    _curFile = SD.open(path, FILE_WRITE);

    return _curFile;
}

bool DataLogger::writeToLog(vector<float> values)
{
    if (_curFile && _numColumns == sizeof(values))
    {
        writeRow(values);
        return true;
    }
    else
    {
        return false;
    }
}

bool DataLogger::close()
{
    if (_curFile)
    {
        _curFile.close();
        return true;
    }
    else
    {
        return false;
    }
}

int DataLogger::getNumColumns()
{
    return _numColumns;
}

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

    _curFile.println(formattedHeader);
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
}

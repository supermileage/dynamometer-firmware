#include <vector>

#include "CsvFile.h"
#include "settings.h"
#include "system_util.h"

using namespace std;

//public methods:

bool CsvFile::create(String name, int numColumns, int mode) {
    // if file is already open, close that file
    if(_curFile) {
        _curFile.close();
    }

    // uniquify name if necessary
    name = system_util::uniquifyFilename(name);
    _numColumns = numColumns;
    _curColumn = 0;
    _fileName = name;
    _curFile = SD.open(name, mode);
    
    if (_curFile) {
        return true;
    } else {
        _numColumns = 0;
        _fileName = "";
        DEBUG_SERIAL_LN("Creating file failed");
        return false;
    }
}

bool CsvFile::open(String name, int numColumns, int mode) {
    // if file is already open, close that file
    if (_curFile) { 
        _curFile.close();
    }
    _numColumns = numColumns;
    _curColumn = 0;
    _fileName = "";
    _curFile = SD.open(name, mode);

    if (!_curFile) {
        // open failed
        _numColumns = 0;
        return false;
    } else if (_curFile.size() == 0) {
        // empty file
        _fileName = name;
        return true;
    } else if (_computeNumColumns() != numColumns) {
        // uniquify name if necessary
        name = system_util::uniquifyFilename(name);
        return open(name, numColumns, mode);
    } else {
        // file has correct number of columns
        _fileName = name;
        return true;
    }
}

bool CsvFile::saveToDisk() {
    if (_curFile) {
        _curFile.flush();
        return true;
    } else {
        DEBUG_SERIAL_LN("CsvFile: save failed -- no file currently open");
        return false;
    }
}

bool CsvFile::close() {
    if (_curFile) {
        _curFile.close();
        _numColumns = 0;
        _fileName = "";
        return true;
    } else {
        DEBUG_SERIAL_LN("CsvFile: failed to close loaded file.");
        return false;
    }
}

void CsvFile::setHeader(String header) {
    _curFile.print(header + "\r\n");
}

void CsvFile::addEntry(String data) {
    if (_curColumn == 0)
        _curFile.print(data);
    else
        _curFile.print("," + data);

    _curColumn++;

    // check if we reached end of row
    if (_curColumn == _numColumns) {
        _curFile.print("\r\n");
        _curColumn = 0;
    }
}

void CsvFile::addRow(String data) {
    if (_curColumn == 0)
        _curFile.print(data + "\r\n");
    else
        DEBUG_SERIAL_LN("CsvFile::addRow can only be called when _curColumn is 0");    
}

String CsvFile::readEntry() {
    String ret = "";
    if (_curFile && !_eofReached()) {
        while (_curFile.available()) {
            char c = (char)_curFile.read();
            if (!_isValidEntry(c)) {
                break;
            }
            ret += c;
        }
        if (++_curColumn == _numColumns) {
            _seekNextLine();
        }
    }
    return ret;
}

std::vector<String> CsvFile::readRow() {
    std::vector<String> vec;
    if (_curColumn != 0 || _eofReached()) {
        return vec;
    }
    for (int i = 0; i < _numColumns; i++) {
        String entry = readEntry();
        vec.push_back(entry);
    }
    return vec;
}

int CsvFile::getNumColumns() {
    return _numColumns;
}

int CsvFile::getFileSize() {
    return _curFile.size();
}

String CsvFile::getFileName() {
    if (_curFile)
        return _fileName;
    else
        return "";
}

int CsvFile::_computeNumColumns() {
    if (!_curFile) {
        return 0;
    }
    uint32_t temp = _curFile.position();
    _curFile.seek(0);
    String line = _curFile.readStringUntil('\n');

    int count = 0;
    bool alphaNumeric = false;
    for (uint16_t i = 0; i < line.length(); i++) {
        if (line[i] == ',') {
            alphaNumeric ? ++count : 0;
            alphaNumeric = false;
        } else if (isalnum(line[i])) {
            alphaNumeric = true;
        }
    }
    
    _curFile.seek(temp);
    alphaNumeric ? ++count : 0;
    return count;
}

void CsvFile::_seekNextLine() {
    if (!isalnum(_curFile.peek())) {
        while (_curFile.available()) {
            char c = (char)_curFile.read();
            if (c == '\n')
                break;
        }
    }
    _curColumn = 0;
}

bool CsvFile::_eofReached() {
    return _curFile.position() == _curFile.size();
}

bool CsvFile::_isValidEntry(char c) {
    return isalnum(c) || c == '.' || c == '-';
}

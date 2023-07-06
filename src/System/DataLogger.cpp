#include "CsvFile.h"
#include "settings.h"

using namespace std;

//public methods:

bool CsvFile::create(String name, int numColumns, int mode) {
    // if file is already open, close that file
    if(_curFile) {
        _curFile.close();
    }

    // uniquify name if necessary
    while (SD.exists(name)) {
        name = _generateNewFileName(name);
    }
    _numColumns = numColumns;
    _curColumn = 0;
    _buffer = "";
    _fileName = name;
    _curFile = SD.open(name, mode);
    
    if (_curFile) {
        DEBUG_SERIAL_LN("Creating file successful");
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
    _buffer = "";
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
        while (SD.exists(name)) {
            name = _generateNewFileName(name);
        }
        return open(name, numColumns, mode);
    } else {
        // file has correct number of columns
        _fileName = name;
        return true;
    }
}

bool CsvFile::saveToDisk() {
    if (_curFile) {
        _curFile.print(_buffer);
        _curFile.flush();
        _buffer = "";
        DEBUG_SERIAL_LN("Write to file successful.");
        return true;
    } else {
        DEBUG_SERIAL_LN("Write to file failed.");
        return false;
    }
}

bool CsvFile::close() {
    if (_curFile) {
        _curFile.close();
        _fileName = "";
        DEBUG_SERIAL_LN("Closed loaded file.");
        return true;
    } else {
        DEBUG_SERIAL_LN("Failed to close loaded file.");
        return false;
    }
}

void CsvFile::setHeader(String header) {
    _buffer += header + "\r\n";
    DEBUG_SERIAL_LN("Added header " + header + " to buffer.");
}

void CsvFile::addEntry(String data) {
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
}

void CsvFile::addRow(String data) {
    if (_curColumn == 0)
        _buffer += data + "\r\n";
    else
        _buffer += "," + data + "\r\n";
    
    _curColumn = 0;
    DEBUG_SERIAL_LN("Added " + data + " to buffer.");
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

int CsvFile::getBufferLength() {
    return _buffer.length();
}

String CsvFile::getFileName() {
    if (_curFile)
        return _fileName;
    else
        return "";
}

String CsvFile::_generateNewFileName(String name) {
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
    if (fileCountStart != -1 && fileCountEnd != -1 && fileCountEnd == (int)base.length() - 1) {
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
    return newFileName;
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

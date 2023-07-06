#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <iostream>

#include "SD.h"

MockSDClass SD;
HardwareSPI SPI1;

int FctrlHelper::fileOpen(const char* pathname, int flags, int mode) {
    return open(pathname, flags, mode);
}

ssize_t FctrlHelper::fileRead(int fd, char* buf, size_t count) {
    return read(fd, buf, count);
}

int FctrlHelper::fileWrite(int fd, const char* buf, size_t count) {
    return write(fd, buf, count);
}

int FctrlHelper::fileClose(int fd) {
    return close(fd);
}

bool MockSDClass::begin(uint8_t pin, HardwareSPI spi) {
    return true;
}

File MockSDClass::open(const String& fileName, int mode) {
    int flag = 0;
    if (mode == FILE_READ) {
        flag = O_RDONLY;
    } else if (mode == FILE_WRITE) {
        flag = O_RDWR | O_CREAT | O_APPEND;
    }

    int fd;
    if ((fd = FctrlHelper::fileOpen(fileName.c_str(), flag, 0666)) < 0) {
        std::cout << "error opening file " << fileName.c_str() << ": " << strerror(errno) << std::endl;
    }

    File file(fd);
    return file;
}

bool MockSDClass::exists(const String& filePath) {
    if (access(filePath.c_str(), F_OK) == 0) {
        return true;
    } else {
        return false;
    }
}

File::File(int fd) : _fd(fd) {
    _status = 0;
}

File::File() { }

int File::available() {
    if (_nextChar != NULL_CHAR) {
        return 1;
    }
    char c;
    _status = FctrlHelper::fileRead(_fd, &c, 1);
    _nextChar = (_status == EOF ? -1 : c);
    return (int)(_status > 0);
}

int File::read() {
    char ret = _nextChar;
    _nextChar = NULL_CHAR;
    return ret;
}

String File::readLine() {
    String ret = "";
    char cur = '\0';
    while (available() && cur != '\n') {
        cur = (char)read();
        ret += cur;
    }
    return ret;
}

void File::close() {
    if ((_status = FctrlHelper::fileClose(_fd)) < 0) {
        std::cout << "error closing file: " << strerror(errno) << std::endl;
    }
    _fd = -1;
}

size_t File::write(String buf) {
    return FctrlHelper::fileWrite(_fd, buf.c_str(), buf.length());
}

size_t File::position() {
    return lseek(_fd, 0, SEEK_CUR);
}

void File::seek(uint32_t pos) {
    lseek(_fd, pos, SEEK_SET);
}

int File::peek() {
    if (_nextChar == NULL_CHAR) {
        char c;
        _status = FctrlHelper::fileRead(_fd, &c, 1);
        _nextChar = c;
    }
    return (_status == EOF) ? -1 : _nextChar;
}

void File::flush() {
    fsync(_fd);
}

size_t File::size() {
    off_t temp = lseek(_fd, 0, SEEK_CUR);
    off_t ret = lseek(_fd, 0, SEEK_END);
    lseek(_fd, temp, SEEK_SET);
    return ret;
}

String File::readStringUntil(char terminator) {
    String line = "";
    int status = ~EOF;
    while (status != EOF) {
        char c;
        status = FctrlHelper::fileRead(_fd, &c, 1);
        if (c == terminator) {
            break;
        }
        line += c;
    } 
    return line;
}

File::operator bool() const {
    return _status >= 0 && _fd > 0;
}
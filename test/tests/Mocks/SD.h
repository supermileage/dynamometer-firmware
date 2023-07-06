#ifndef _MOCK_SD_H_
#define _MOCK_SD_H_

#include <fcntl.h>
#include "Arduino.h"

#undef FILE_READ
#define FILE_READ 0
#undef FILE_WRITE
#define FILE_WRITE 1
#undef EOF
#define EOF 0

#define NULL_CHAR -129

class File;

namespace FctrlHelper {
    int fileOpen(const char* pathname, int flags, int mode);
    int fileClose(int fd);
    ssize_t fileRead(int fd, char* buf, size_t count);
    int fileWrite(int fd, const char* buf, size_t count);
};

/**
 * @brief Dummy SPI class for testing
 */
class HardwareSPI { };

/**
 * @brief Mock SDClass for testing purposes
 */
class MockSDClass {
    public:
        bool begin(uint8_t pin, HardwareSPI spi);
        File open(const String& fileName, int mode = 0);
        bool exists(const String& filePath);
};

// Global objects for test
extern HardwareSPI SPI1;
extern MockSDClass SD;

/**
 * @brief Mock File class for testing purposes
 */
class File {
    public:
        File();
        File(int fd);
        int available();
        int read();
        String readLine();
        void close();
        size_t write(String buf);
        size_t position();
        void seek(uint32_t pos);
        int peek();
        size_t size();
        void flush();
        String readStringUntil(char terminator);
        operator bool() const;

    private:
        int _fd = -1;
        int _status = 0;
        int _nextChar = NULL_CHAR;
};

#endif
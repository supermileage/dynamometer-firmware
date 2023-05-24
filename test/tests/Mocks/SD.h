#ifndef _MOCK_SD_H_
#define _MOCK_SD_H_

#include "Arduino.h"

#undef FILE_READ
#define FILE_READ 0
#undef FILE_WRITE
#define FILE_WRITE 1

class File;

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
        int available();
        int read();
        void close();
        size_t print(String buf);
        operator bool() const;

    private:
        int _fd;
        int _status = -1;
};

#endif
#include "SD.h"

#include <fcntl.h>

MockSDClass SD;

bool MockSDClass::begin(uint8_t pin, HardwareSPI spi) {
    return true;
}

File MockSDClass::open(const String& fileName, int mode) {
    File file;
    return file;
}

bool MockSDClass::exists(const String& filePath) {
    return false;
}


int File::available() {
    return 0;
}

int File::read() {
    return 0;
}

void File::close() {

}

size_t File::print(String buf) {
    return 0;
}

HardwareSPI* HardwareSPI::_instance = nullptr;

HardwareSPI& HardwareSPI::instance() {
    if (!_instance) {
        _instance = new HardwareSPI();
    }
    return *_instance;
}
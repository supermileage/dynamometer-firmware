#include "ErrorHandler.h"
#include <string.h>

#define FORMATTED_MESSAGE_SIZE (sizeof("assert failed: (  )\n\t<,ln > in \n\n") + 2)

ErrorHandler* ErrorHandler::_instance = nullptr;
ErrorHandler& ErrorUtil = ErrorHandler::instance();

ErrorHandler& ErrorHandler::instance() {
    if (!_instance) {
        _instance = new ErrorHandler();
    }
    return *_instance;
}

void ErrorHandler::init(ErrorHandlingBehaviour behaviour) {
    if (behaviour == Log || behaviour == LogAndPrint) {
        _openLogFile();
    }
    _behaviour = behaviour;
}

void ErrorHandler::setBehaviour(ErrorHandlingBehaviour behaviour) {
    switch (behaviour) {
        case Log:
            _openLogFile();
            break;
        case Print:
            _closeLogFile();
            break;
        case LogAndPrint:
            _openLogFile();
            break;
        default:
            _closeLogFile();
            break;
    }
    _behaviour = behaviour;
}

void ErrorHandler::errorAssert(const char* file, int line, const char* func, const char* expression) {
    if (_behaviour == DoNothing) {
        return;
    }

    char* path = strstr(file, "src/");
    int len = strlen(path) + 4 + strlen(func) + strlen(expression) + FORMATTED_MESSAGE_SIZE;
    char* buf = new char[len + 1] { 0 };
    sprintf(buf, "assert failed: ( %s )\n\t<%s,ln %d> in %s\n\n", expression, path, line, func);
    
    switch (_behaviour) {
        case Log:
            _logError(buf);
            break;
        case Print:
            Serial.print(buf);
            break;
        case LogAndPrint:
            _logError(buf);
            Serial.print(buf);
            break;
        default:
            break;
    }
    delete[] buf;
}

void ErrorHandler::_logError(char* buf) {
    if (_logFile) {
        _logFile.write(buf, strlen(buf));
        _logFile.flush();
    }
}

void ErrorHandler::_openLogFile() {
    if (!_logFile) {
        _logFile = SD.open(String(ERROR_LOGFILE_PATH), O_TRUNC | O_CREAT | O_RDWR | O_SYNC);
        if (!_logFile) {
            DEBUG_SERIAL_LN("ErrorHandler: error creating file: " + String(ERROR_LOGFILE_PATH));
        }    
    } else {
        DEBUG_SERIAL_LN("ErrorHandler: log file already open");
    }
}

void ErrorHandler::_closeLogFile() {
    if (_logFile) {
        _logFile.close();
    }
}
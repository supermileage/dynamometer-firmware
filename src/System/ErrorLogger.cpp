#include "ErrorLogger.h"
#include <string.h>

#define FORMATTED_MESSAGE_SIZE (sizeof("assert failed: (  )\n\t<,ln > in \n\n") + 2)

ErrorLogger* ErrorLogger::_instance = nullptr;
ErrorLogger& ErrorUtil = ErrorLogger::instance();

ErrorLogger& ErrorLogger::instance() {
    if (!_instance) {
        _instance = new ErrorLogger();
    }
    return *_instance;
}

void ErrorLogger::init(ErrorHandlingBehaviour behaviour) {
    if (behaviour == Log || behaviour == LogAndPrint) {
        _openLogFile();
    }
    _behaviour = behaviour;
}

void ErrorLogger::setBehaviour(ErrorHandlingBehaviour behaviour) {
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

void ErrorLogger::errorAssert(const char* file, int line, const char* func, const char* expression) {
    if (_behaviour == DoNothing) {
        return;
    }

    char* path = strstr(file, "src/");
    int len = strlen(path) + 4 + strlen(func) + strlen(expression) + FORMATTED_MESSAGE_SIZE;
    char* buf = new char[len + 1] { 0 };
    sprintf(buf, "assert failed: ( %s )\n\t<%s,ln %d> in %s\n\n", expression, path, line, func);
    errorLog(buf);
    delete[] buf;
}

void ErrorLogger::errorLog(const char* buf) {
    switch (_behaviour) {
        case Log:
            _logToDisk(buf);
            break;
        case Print:
            Serial.print(buf);
            break;
        case LogAndPrint:
            _logToDisk(buf);
            Serial.print(buf);
            break;
        default:
            break;
    }
}

void ErrorLogger::_logToDisk(const char* buf) {
    if (_logFile) {
        _logFile.write(buf, strlen(buf));
        _logFile.flush();
    }
}

void ErrorLogger::_openLogFile() {
    if (!_logFile) {
        _logFile = SD.open(String(ERROR_LOGFILE_PATH), O_TRUNC | O_CREAT | O_RDWR | O_SYNC);
        if (!_logFile) {
            DEBUG_SERIAL_LN("ErrorLogger: error creating file: " + String(ERROR_LOGFILE_PATH));
        }    
    } else {
        DEBUG_SERIAL_LN("ErrorLogger: log file already open");
    }
}

void ErrorLogger::_closeLogFile() {
    if (_logFile) {
        _logFile.close();
    }
}
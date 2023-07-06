#ifndef _ERROR_HANDLER_H_
#define _ERROR_HANDLER_H_

#include "SD.h"
#include "settings.h"

class ErrorLogger;
extern ErrorLogger& ErrorUtil;

#if DYNO_ASSERT_EN
#define dyno_assert(__expr) ((__expr) ? (void)0 : ErrorUtil.errorAssert(__FILE__, __LINE__, \
                                __PRETTY_FUNCTION__, #__expr))
#define dyno_log(__buf)     ErrorUtil.errorLog(__buf)
#define dyno_log_str(__str) ErrorUtil.errorLog((__str).c_str())
#else
#define dyno_assert(__expr) { }
#define dyno_log(__buf) { }
#define dyno_log_str(__str) { }
#endif

class ErrorLogger {
    public:
        /* error handling */
        enum ErrorHandlingBehaviour { Log, Print, LogAndPrint, DoNothing };

        static ErrorLogger& instance();
        void init(ErrorHandlingBehaviour behaviour);
        void setBehaviour(ErrorHandlingBehaviour behaviour);
        void errorAssert(const char* file, int line, const char* func, const char* expression);
        void errorLog(const char* buf);

    private:
        static ErrorLogger* _instance;
        ErrorHandlingBehaviour _behaviour = DoNothing;
        File _logFile;

        ErrorLogger() { }
        void _logToDisk(const char* buf);
        void _openLogFile();
        void _closeLogFile();
};

#endif
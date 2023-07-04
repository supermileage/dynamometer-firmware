#ifndef _ERROR_HANDLER_H_
#define _ERROR_HANDLER_H_

#include "SD.h"
#include "settings.h"

class ErrorHandler;
extern ErrorHandler& ErrorUtil;

#if DYNO_ASSERT_EN
#define dyno_assert(__expr) ((__expr) ? (void)0 : ErrorUtil.errorAssert(__FILE__, __LINE__, \
                                __PRETTY_FUNCTION__, #__expr))
#else
#define dyno_assert(__expr) { }
#endif

class ErrorHandler {
    public:
        /* error handling */
        enum ErrorHandlingBehaviour { Log, Print, LogAndPrint, DoNothing };

        static ErrorHandler& instance();
        void init(ErrorHandlingBehaviour behaviour);
        void setBehaviour(ErrorHandlingBehaviour behaviour);
        void errorAssert(const char* file, int line, const char* func, const char* expression);

    private:
        static ErrorHandler* _instance;
        ErrorHandlingBehaviour _behaviour = DoNothing;
        File _logFile;

        ErrorHandler() { }
        void _logError(char* buf);
        void _openLogFile();
        void _closeLogFile();
};

#endif
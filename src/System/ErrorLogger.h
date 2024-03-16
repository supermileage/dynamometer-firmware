#ifndef _ERROR_HANDLER_H_
#define _ERROR_HANDLER_H_

#include "SD.h"
#include "settings.h"

class ErrorLogger;
extern ErrorLogger& ErrorUtil; // instance of ErrorLogger

#if DYNO_ASSERT_EN
    /// \brief Checks the value of an expression. If it is false, log an error message based on the current error logging behaviour.
    #define dyno_assert(__expr) ((__expr) ? (void)0 : ErrorUtil.errorAssert(__FILE__, __LINE__, \
                                    __PRETTY_FUNCTION__, #__expr))

    /// \brief Logs a message in a character buffer based on the current error logging behaviour.
    #define dyno_log(__buf)     ErrorUtil.errorLog(__buf)

    /// \brief Logs a message in a string based on the current error logging behaviour.
    #define dyno_log_str(__str) ErrorUtil.errorLog((__str).c_str())

#else
    #define dyno_assert(__expr) { }
    #define dyno_log(__buf) { }
    #define dyno_log_str(__str) { }
#endif


/**
 * @brief Class for global assertion and error logging helpers.
 * 
 * The "dyno_assert" macro is available globally to check assertions. 
 * The "dyno_log" and "dyno_log_str" macros are available for general purpose logging (for character buffers and strings respectively)
 * The following line is an example of an assertion:
 *      
 *      dyno_assert(velocity > 0);
 * 
 * This line will do nothing if velocity is greater than 0. 
 * However, if it is less than 0, the assertion will fail, and an action will trigger based on the current error logging behaviour.
*/
class ErrorLogger {
    public:

        /** @enum Error handling behaviors */
        enum ErrorHandlingBehaviour { 
            /** Log the error message in a file on the SD card */
            Log,
            /** Print the error message on the serial monitor */
            Print,
            /** Log the error message in a file, and print on serial */
            LogAndPrint,
            /** Do nothing */
            DoNothing
        };

        /**
         * @brief Returns ErrorLogger singleton. Creates an instance of ErrorLogger if it does not exist yet.
        */
        static ErrorLogger& instance();

        /**
         * @brief Initialization method. Sets the error logging behaviour.
         * @param behaviour Error logging behaviour
        */
        void init(ErrorHandlingBehaviour behaviour);

        /**
         * @brief Sets error logging behaviour
         * @param behaviour Error logging behaviour
        */
        void setBehaviour(ErrorHandlingBehaviour behaviour);

        /**
         * @brief Creates and logs an assertion error message.
         * @note This function is called when an assertion fails, but does not check the assertion.
         * 
         * @param file Name of the file from which the failed assertion occurred
         * @param line Line number of the failed assertion
         * @param func Function name from which the failed assertion occurred
         * @param expression Assertion expression that failed
        */
        void errorAssert(const char* file, int line, const char* func, const char* expression);

        /**
         * @brief Do error logging action (log to file, print to serial, etc) depending on current error logging behaviour.
         * @param buf Character buffer describing error message.
        */ 
        void errorLog(const char* buf);

    private:
        // ErrorLogger singleton
        static ErrorLogger* _instance;
        // behaviour of error logger
        ErrorHandlingBehaviour _behaviour = DoNothing;
        // file on the SD card to log errors
        File _logFile;

        // constructor
        ErrorLogger() { }
        // log character buffer to file
        void _logToDisk(const char* buf);
        // open error logging file
        void _openLogFile();
        // close error logging file
        void _closeLogFile();
};

#endif